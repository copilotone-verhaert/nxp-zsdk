/**
 *  Copyright 2023-2024 NXP
 *
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  @file  main.c
 *  @brief main file
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(mfg_bridge, LOG_LEVEL_ERR);

#include "fsl_common.h"
#if defined(RW610_SERIES) || defined(RW612_SERIES)
#include "fsl_adapter_imu.h"
#include "fsl_loader.h"
#include "fsl_ocotp.h"
#else
#ifdef CONFIG_BT_IND_DNLD
#include "fw_loader_uart.h"
#endif
#include "fwdnld_intf_abs.h"
#include "wlan.h"
#include "wifi.h"
#include "wm_net.h"
#include <osa.h>
#include "wifi-internal.h"
#include "wifi-sdio.h"
#include "fsl_lpuart.h"
#if (defined(MIMXRT1062_SERIES) || defined(MIMXRT1061_SERIES))
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/gpio.h>
#endif
#endif
#include "uart_rtos.h"

#ifndef PRINTF
#define PRINTF printk
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define UART_BUF_SIZE            2048
#define LABTOOL_PATTERN_HDR_LEN  4
#define LABTOOL_HCI_RESP_HDR_LEN 3

#define CHECKSUM_LEN             4
#define CRC32_POLY               0x04c11db7

/** Command type: WLAN */
#define TYPE_WLAN     0x0002
#define RET_TYPE_WLAN 1

/** Command type: BT */
#define TYPE_BT     0x0003
#define RET_TYPE_BT 2

/** Command type: 15.4 */
#define TYPE_15_4       0x0004
#define RET_TYPE_ZIGBEE 3

#if defined(RW610_SERIES) || defined(RW612_SERIES)
#define MLAN_TYPE_CMD   1
#define INTF_HEADER_LEN 4
#define SDIO_OUTBUF_LEN 2048
#endif

#define SDIOPKTTYPE_CMD 0x1
#define BUF_LEN         1024

#define WM_SUCCESS 0
#define WM_FAIL    1

#define UNUSED(x) (void)(x)

#define REMOTE_EPT_ADDR_BT     (40U)
#define LOCAL_EPT_ADDR_BT      (30U)
#define REMOTE_EPT_ADDR_ZIGBEE (20U)
#define LOCAL_EPT_ADDR_ZIGBEE  (10U)

#define WIFI_REG8(x)  (*(volatile unsigned char *)(x))
#define WIFI_REG16(x) (*(volatile unsigned short *)(x))
#define WIFI_REG32(x) (*(volatile unsigned int *)(x))

#define WIFI_WRITE_REG8(reg, val)  (WIFI_REG8(reg) = (val))
#define WIFI_WRITE_REG16(reg, val) (WIFI_REG16(reg) = (val))
#define WIFI_WRITE_REG32(reg, val) (WIFI_REG32(reg) = (val))

/* Set default mode of fw download */
#ifndef CONFIG_SUPPORT_WIFI
#define CONFIG_SUPPORT_WIFI
#endif
#ifndef CONFIG_SUPPORT_BLE
#define CONFIG_SUPPORT_BLE
#endif
#ifndef SUPPORT_IEEE802154
#define SUPPORT_IEEE802154
#endif

#define WLAN_FW_WAKE_STATUS_ADDR     (0x40031068U)

enum {
	MLAN_CARD_NOT_DETECTED = 3,
	MLAN_STATUS_FW_DNLD_FAILED,
	MLAN_STATUS_FW_NOT_DETECTED = 5,
	MLAN_STATUS_FW_NOT_READY,
	MLAN_STATUS_FW_XZ_FAILED,
	MLAN_CARD_CMD_TIMEOUT
};

#if (defined(MIMXRT1062_SERIES) || defined(MIMXRT1061_SERIES))
/* SPI related */
#define SPI_NODE         DT_NODELABEL(lpspi4)
#define ZIGBEE_RCP_NODE  DT_NODELABEL(zigbee_rcp)
#define I2C_NODE         DT_NODELABEL(lpi2c1)
#define IO_EXPANDER_NODE DT_NODELABEL(io_expander)
#define PLATFORM_IOEXP_I2C_ADDR_7BIT            0x20U
#define PLATFORM_IOEXP_CONFIGURATION_REG        0x03U
#define PLATFORM_IOEXP_CONFIGURATION_SPI_ENABLE 0xFEU
#define PLATFORM_CONFIG_DEFAULT_RESET_DELAY_MS  200U

/* IOMUXC GPR register definitions */
#define IOMUXC_GPR_BASE                          (0x400AC000u)

/* GPR26 - GPIO1 MUX selection */
#define IOMUXC_GPR26_OFFSET                      (0x68u)  /* GPR26 = GPR0 + 26*4 */
#define IOMUXC_GPR26_ADDR                        (IOMUXC_GPR_BASE + IOMUXC_GPR26_OFFSET)
#define GPIO_MUX1_GPIO_SEL_MASK                  (0x01080000U)  /* bits 19,24 */
#define GPIO_MUX1_GPIO_SEL(x)                    (((uint32_t)(x) << 19U) & GPIO_MUX1_GPIO_SEL_MASK)

/* GPR27 - GPIO2 MUX selection */
#define IOMUXC_GPR27_OFFSET                      (0x6Cu)  /* GPR27 = GPR0 + 27*4 */
#define IOMUXC_GPR27_ADDR                        (IOMUXC_GPR_BASE + IOMUXC_GPR27_OFFSET)
#define GPIO_MUX2_GPIO_SEL_MASK                  (0x10U)  /* bit 4 */
#define GPIO_MUX2_GPIO_SEL(x)                    (((uint32_t)(x) << 4U) & GPIO_MUX2_GPIO_SEL_MASK)

#define SPI_DEFAULT_SMALL_PACKET_SIZE (48U)
#define SPI_DEFAULT_RX_DATA_SIZE      (1024U)
#define SPI_DEFAULT_ALIGN_ALLOWANCE   (16U)
#define SPI_DEFAULT_RX_BUFF_LENGTH    (1024U)
#define SPI_DEFAULT_TX_BUFF_LENGTH    (1024U)

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#define pvPortMalloc k_malloc

struct uart_rtos_state uart_handle;

#if defined(CONFIG_SUPPORT_BT_UART)
struct uart_rtos_state bt_uart_handle;
#endif /*CONFIG_SUPPORT_BT_UART*/


#if defined(RW610_SERIES) || defined(RW612_SERIES)
struct k_timer g_wifi_cau_temperature_timer;

static IMUMC_HANDLE_DEFINE(bt_imumc_handle);
static IMUMC_HANDLE_DEFINE(zigbee_imumc_handle);
static hal_imumc_handle_t imumcHandleList[] = {(hal_imumc_handle_t)bt_imumc_handle,
					       (hal_imumc_handle_t)zigbee_imumc_handle};

uint32_t remote_ept_list[] = {REMOTE_EPT_ADDR_BT, REMOTE_EPT_ADDR_ZIGBEE};
uint32_t local_ept_list[] = {LOCAL_EPT_ADDR_BT, LOCAL_EPT_ADDR_ZIGBEE};
#endif

struct uart_cb { /* uart control block */
	int uart_fd;
	unsigned int crc32_table[256];
	unsigned char uart_buf[UART_BUF_SIZE]; /* uart buffer */
};

static struct uart_cb uartcb;
#if !defined(RW610_SERIES) && !defined(RW612_SERIES)
static struct uart_cb uartcb_bt;
#endif

#if defined(CONFIG_SUPPORT_BT_UART)
static struct uart_cb uartcb_bt;
#endif /*CONFIG_SUPPORT_BT_UART*/

/** UART start pattern*/
struct uart_header {
	/** pattern */
	short pattern;
	/** Command length */
	short length;
};

/** Labtool command header */
struct cmd_header {
	/** Command Type */
	short type;
	/** Command Sub-type */
	short sub_type;
	/** Command length (header+payload) */
	short length;
	/** Command status */
	short status;
	/** reserved */
	int reserved;
};

/** HostCmd_DS_COMMAND */
struct HostCmd_DS_COMMAND {
	/** Command Header : Command */
	uint16_t command;
	/** Command Header : Size */
	uint16_t size;
	/** Command Header : Sequence number */
	uint16_t seq_num;
	/** Command Header : Result */
	uint16_t result;
	/** Command Body */
};

/** IMUPkt/SDIOPkt only name difference, same definition */
struct SDIOPkt {
	uint16_t size;
	uint16_t pkttype;
	struct HostCmd_DS_COMMAND hostcmd;
};

static uint8_t *rx_buf;
static struct cmd_header last_cmd_hdr;
uint8_t *local_outbuf;
static struct SDIOPkt *sdiopkt;

uint8_t host_resp_buf[BUF_LEN];
uint32_t resp_buf_len, reqd_resp_len;

#if defined(CONFIG_NXP_MONOLITHIC_WIFI)
#if defined(RW610_SERIES) || defined(RW612_SERIES)
extern const uint32_t fw_cpu1[];
#define WIFI_FW_ADDRESS  (uint32_t)&fw_cpu1[0]
#else
extern const unsigned char *wlan_fw_bin;
extern const unsigned int wlan_fw_bin_len;
#endif
#else
#define WIFI_FW_ADDRESS  0U
#endif /*defined(CONFIG_NXP_MONOLITHIC_WIFI)*/

#if defined(CONFIG_NXP_MONOLITHIC_NBU)
extern const uint32_t fw_cpu2[];
#define COMBO_FW_ADDRESS (uint32_t)&fw_cpu2[0]
#define BLE_FW_ADDRESS   (uint32_t)&fw_cpu2[0]
#else
#define COMBO_FW_ADDRESS	0U
#define BLE_FW_ADDRESS		0U
#endif

#if (defined(MIMXRT1062_SERIES) || defined(MIMXRT1061_SERIES))
/* Spinel SPI frame header */
typedef struct __attribute__((__packed__)) spi_frame_hdr {
	unsigned char  bit0 : 1; /* must be 0 */
	unsigned char  bit1 : 1; /* must be 1 */
	unsigned char  reserve : 3;
	unsigned char  ccf : 1;
	unsigned char  crc : 1;
	unsigned char  rst : 1;
	unsigned short recv_len;
	unsigned short data_len;
} spi_frame_hdr;

typedef struct __attribute__((__packed__)) zigBee_spinel_cmd_hdr {
	uint8_t  TID:4;    /* Transaction ID */
	uint8_t  IID:2;    /* Interface ID */
	uint8_t  FLG:2;    /* Flags */
	uint16_t SPINEL_CMD_NUM;
	uint8_t  MFG_CMD_Payload_Length;
} zigBee_spinel_cmd_hdr;

/* Get SPI device from device tree */
#define SPI_NODE DT_NODELABEL(lpspi4)
#define ZIGBEE_RCP_SPI_FREQUENCY  2000000
#define ZIGBEE_RCP_SPI_CS_INDEX   0         /* CS0 */
static const struct device *spi_dev;

/* SPI configuration, static definition, initialize only once */
static struct spi_config spi_cfg = {
	.frequency = ZIGBEE_RCP_SPI_FREQUENCY,
	.operation = SPI_OP_MODE_MASTER |
				 SPI_TRANSFER_MSB |
				 SPI_WORD_SET(8) |
				 SPI_LINES_SINGLE,
	.slave = ZIGBEE_RCP_SPI_CS_INDEX,
};

static uint8_t spi_buff_rx[SPI_DEFAULT_RX_BUFF_LENGTH];
static uint8_t spi_buff_tx[SPI_DEFAULT_TX_BUFF_LENGTH];

static int zigbee_reset_flag = 1;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
#define SDK_VERSION "NXPSDK_v1.3.r13.p1"
#if (defined(MIMXRT1062_SERIES) || defined(MIMXRT1061_SERIES))
int set_spi_frame_hdr(spi_frame_hdr *pspihdr,
						unsigned char rst_flag,
						unsigned char crc_flag,
						unsigned char ccf_flag,
						unsigned short recv_len,
						unsigned short data_len)
{
	if (!pspihdr) {
		return -1;
	}
	memset(pspihdr, 0, sizeof(spi_frame_hdr));
	pspihdr->rst = rst_flag | zigbee_reset_flag;
	pspihdr->crc = crc_flag;
	pspihdr->ccf = ccf_flag;
	pspihdr->bit1 = 1;
	pspihdr->bit0 = 0;
	pspihdr->recv_len = max(recv_len, SPI_DEFAULT_SMALL_PACKET_SIZE);
	pspihdr->data_len = data_len;

	zigbee_reset_flag = 0;
	return 0;
}
#endif

static void uart_init_crc32(struct uart_cb *uartcb)
{
	int i, j;
	unsigned int c;

	for (i = 0; i < 256; ++i) {
		for (c = i << 24, j = 8; j > 0; --j) {
			c = c & 0x80000000 ? (c << 1) ^ CRC32_POLY : (c << 1);
		}
		uartcb->crc32_table[i] = c;
	}
}

static uint32_t uart_get_crc32(struct uart_cb *uart, int len, unsigned char *buf)
{
	unsigned int *crc32_table = uart->crc32_table;
	unsigned char *p;
	unsigned int crc;

	crc = 0xffffffff;

	for (p = buf; len > 0; ++p, --len) {
		crc = (crc << 8) ^ (crc32_table[(crc >> 24) ^ *p]);
	}
	return ~crc;
}

/*
 * send_response_to_uart() handles the response from the firmware.
 * This involves
 * 1. replacing the sdio header with the uart header
 * 2. computation of the crc of the payload
 * 3. sending it out to the uart
 */
static int send_response_to_uart(struct uart_cb *uart, const uint8_t *resp, int type
#if !defined(RW610_SERIES) && !defined(RW612_SERIES)
		, uint32_t reqd_resp_len
#endif
	)
{
	uint32_t bridge_chksum = 0;
	uint32_t msglen;
	int index;
	uint32_t payloadlen;
	struct uart_header *uart_hdr;
	int iface_len = 0;

#if defined(RW610_SERIES) || defined(RW612_SERIES)
	struct SDIOPkt *sdio = (struct SDIOPkt *)resp;

	if (type == 2) {
		/* This is because, the last byte of the sdio header
		 * (packet type) is also required by the labtool, to
		 * understand the type of packet and take appropriate action
		 */
		iface_len = INTF_HEADER_LEN - 1;
	} else {
		iface_len = INTF_HEADER_LEN;
	}

	payloadlen = sdio->size - iface_len;
#else
	payloadlen = reqd_resp_len;
#endif
	(void)memset(rx_buf, 0, BUF_LEN);
	(void)memcpy(rx_buf + sizeof(struct uart_header) + sizeof(struct cmd_header),
		     resp + iface_len, payloadlen);

	/* Added to send correct cmd header len */
	struct cmd_header *cmd_hdr;

	cmd_hdr = &last_cmd_hdr;
	cmd_hdr->length = payloadlen + sizeof(struct cmd_header);

	(void)memcpy(rx_buf + sizeof(struct uart_header), (uint8_t *)&last_cmd_hdr,
		     sizeof(struct cmd_header));

	uart_hdr = (struct uart_header *)rx_buf;
	uart_hdr->length = payloadlen + sizeof(struct cmd_header);
	uart_hdr->pattern = 0x5555;

	/* calculate CRC. The uart_header is excluded */
	msglen = payloadlen + sizeof(struct cmd_header);
	bridge_chksum = uart_get_crc32(uart, msglen, rx_buf + sizeof(struct uart_header));
	index = sizeof(struct uart_header) + msglen;

	rx_buf[index] = bridge_chksum & 0xff;
	rx_buf[index + 1] = (bridge_chksum & 0xff00) >> 8;
	rx_buf[index + 2] = (bridge_chksum & 0xff0000) >> 16;
	rx_buf[index + 3] = (bridge_chksum & 0xff000000) >> 24;

	/* write response to uart */
	uart_rtos_send(&uart_handle, rx_buf,
		       payloadlen + sizeof(struct cmd_header) + sizeof(struct uart_header) + 4);

	(void)memset(rx_buf, 0, BUF_LEN);

	return 0;
}

/*
 * check_command_complete() validates the command from the uart.
 * It checks for the signature in the header and the crc of the
 * payload. This assumes that the uart_buf is circular and data
 * can be wrapped.
 */
int check_command_complete(uint8_t *buf)
{
	struct uart_header *uarthdr;
	uint32_t msglen, endofmsgoffset;
	struct uart_cb *uart = &uartcb;
	int checksum = 0, bridge_checksum = 0;

	uarthdr = (struct uart_header *)buf;

	/* out of sync */
	if (uarthdr->pattern != 0x5555) {
		LOG_ERR("Pattern mismatch");
		return -WM_FAIL;
	}
	/* check crc */
	msglen = uarthdr->length;

	/* add 4 for checksum */
	endofmsgoffset = sizeof(struct uart_header) + msglen + 4;

	(void)memset((uint8_t *)local_outbuf, 0, sizeof(*local_outbuf));
	if (endofmsgoffset < UART_BUF_SIZE) {
		(void)memcpy((uint8_t *)local_outbuf, buf, endofmsgoffset);
	} else {
		(void)memcpy((uint8_t *)local_outbuf, buf, UART_BUF_SIZE);
		/* To do : check if copying method is correct */
		(void)memcpy((uint8_t *)local_outbuf + UART_BUF_SIZE, buf, endofmsgoffset);
	}

	checksum = *(int *)((uint8_t *)local_outbuf + sizeof(struct uart_header) + msglen);

	bridge_checksum =
		uart_get_crc32(uart, msglen, (uint8_t *)local_outbuf + sizeof(struct uart_header));
	if (checksum == bridge_checksum) {
		return WM_SUCCESS;
	}
	/* Reset local outbuf */
	(void)memset(local_outbuf, 0, BUF_LEN);

	return -WM_FAIL;
}

#if defined(RW610_SERIES) || defined(RW612_SERIES)
hal_imumc_status_t  wifi_send_imu_raw_data(uint8_t *data, uint32_t length)
{
	if (data == NULL || length == 0) {
		return kStatus_HAL_ImumcError;
	}

	if (kStatus_HAL_ImumcSuccess != (HAL_ImuSendCommand(kIMU_LinkCpu1Cpu3, data, length))) {
		return kStatus_HAL_ImumcError;
	}

	return kStatus_HAL_ImumcSuccess;
}

int imumc_raw_packet_send(uint8_t *buf, int m_len, uint8_t t_type)
{
	uint32_t payloadlen;

	struct cmd_header *cmd_hd = (struct cmd_header *)(buf + sizeof(struct uart_header));

	payloadlen = m_len - sizeof(struct uart_header) - sizeof(struct cmd_header) - 4;

	(void)memset(local_outbuf, 0, BUF_LEN);
	(void)memcpy(local_outbuf, buf + sizeof(struct uart_header) + sizeof(struct cmd_header),
		     payloadlen);

	(void)memcpy(&last_cmd_hdr, cmd_hd, sizeof(struct cmd_header));

	if (kStatus_HAL_ImumcSuccess !=
	    (HAL_ImumcSend((hal_imumc_handle_t)imumcHandleList[t_type - 2],
			   local_outbuf, payloadlen))) {
		return kStatus_HAL_ImumcError;
	}

	(void)memset(local_outbuf, 0, BUF_LEN);

	return t_type;
}
#endif

#if defined(CONFIG_SUPPORT_BT_UART)
static int bt_raw_packet_send(uint8_t *buf, int m_len)
{
	uint32_t payloadlen;

	struct cmd_header *cmd_hd = (struct cmd_header *)(buf + sizeof(struct uart_header));

	payloadlen = m_len - sizeof(struct uart_header) - sizeof(struct cmd_header) - 4;

	memset(local_outbuf, 0, BUF_LEN);
	memcpy(local_outbuf, buf + sizeof(struct uart_header) + sizeof(struct cmd_header),
			payloadlen);

	memcpy(&last_cmd_hdr, cmd_hd, sizeof(struct cmd_header));

	(void)uart_rtos_send(&bt_uart_handle, local_outbuf, payloadlen);

	memset(local_outbuf, 0, BUF_LEN);

	return RET_TYPE_BT;
}
#endif /*CONFIG_SUPPORT_BT_UART*/

#if (defined(MIMXRT1062_SERIES) || defined(MIMXRT1061_SERIES))
static int zigbee_raw_packet_send(uint8_t *buf, int m_len)
{
	uint32_t payloadlen;
	spi_frame_hdr *pspihdr;
	zigBee_spinel_cmd_hdr *pspinelhdr;
	int ret;

	memset(spi_buff_tx, 0, SPI_DEFAULT_TX_BUFF_LENGTH);
	memset(spi_buff_rx, 0, SPI_DEFAULT_RX_BUFF_LENGTH);

	pspihdr = (spi_frame_hdr *)spi_buff_tx;

	struct cmd_header *cmd_hd = (struct cmd_header *)(buf + sizeof(struct uart_header));

	pspinelhdr = (zigBee_spinel_cmd_hdr *)(buf +
			sizeof(struct uart_header) + sizeof(struct cmd_header));
	payloadlen = sizeof(zigBee_spinel_cmd_hdr) + pspinelhdr->MFG_CMD_Payload_Length;

	set_spi_frame_hdr(pspihdr, 0, 0, 0, payloadlen, payloadlen);

	memcpy(spi_buff_tx + sizeof(spi_frame_hdr),
			buf + sizeof(struct uart_header) + sizeof(struct cmd_header),
			payloadlen);
	memcpy(&last_cmd_hdr, cmd_hd, sizeof(struct cmd_header));

	/* Use Zephyr SPI API for transfer */
	struct spi_buf tx_buf = {
		.buf = spi_buff_tx,
		.len = SPI_DEFAULT_SMALL_PACKET_SIZE +
			sizeof(spi_frame_hdr) + SPI_DEFAULT_ALIGN_ALLOWANCE
	};
	struct spi_buf rx_buf = {
		.buf = spi_buff_rx,
		.len = SPI_DEFAULT_SMALL_PACKET_SIZE +
			sizeof(spi_frame_hdr) + SPI_DEFAULT_ALIGN_ALLOWANCE
	};

	const struct spi_buf_set tx_bufs = { .buffers = &tx_buf, .count = 1 };
	const struct spi_buf_set rx_bufs = { .buffers = &rx_buf, .count = 1 };

	ret = spi_transceive(spi_dev, &spi_cfg, &tx_bufs, &rx_bufs);
	if (ret != 0) {
		LOG_ERR("SPI transfer failed: %d", ret);
		return -1;
	}

	memset(spi_buff_tx, 0, SPI_DEFAULT_TX_BUFF_LENGTH);
	memset(spi_buff_rx, 0, SPI_DEFAULT_RX_BUFF_LENGTH);

	return RET_TYPE_ZIGBEE;
}
#endif

/*
 * process_input_cmd() sends command to the wlan
 * card
 */
int process_input_cmd(uint8_t *buf, int m_len)
{
	struct uart_header *uarthdr;
	int i, ret = -WM_FAIL;
	uint8_t *s, *d;
	struct cmd_header *cmd_hd = (struct cmd_header *)(buf + sizeof(uarthdr));

	if (cmd_hd->type == TYPE_WLAN) {
		(void)memset(local_outbuf, 0, BUF_LEN);
		sdiopkt = (struct SDIOPkt *)local_outbuf;

		uarthdr = (struct uart_header *)buf;
#if defined(RW610_SERIES) || defined(RW612_SERIES)
		/* sdiopkt = local_outbuf */
		sdiopkt->pkttype = SDIOPKTTYPE_CMD;

		sdiopkt->size = m_len - sizeof(struct cmd_header) + INTF_HEADER_LEN;
		d = (uint8_t *)local_outbuf + INTF_HEADER_LEN;
		s = (uint8_t *)buf + sizeof(struct uart_header) + sizeof(struct cmd_header);
#else
		d = (uint8_t *)local_outbuf;
		s = (uint8_t *)buf + sizeof(struct uart_header) + sizeof(struct cmd_header);
#endif

		for (i = 0; i < uarthdr->length - sizeof(struct cmd_header); i++) {
			if (s < buf + UART_BUF_SIZE) {
				*d++ = *s++;
			} else {
				s = buf;
				*d++ = *s++;
			}
		}

		d = (uint8_t *)&last_cmd_hdr;
		s = (uint8_t *)buf + sizeof(struct uart_header);

		for (i = 0; i < sizeof(struct cmd_header); i++) {
			if (s < buf + UART_BUF_SIZE) {
				*d++ = *s++;
			} else {
				s = buf;
				*d++ = *s++;
			}
		}
#if defined(RW610_SERIES) || defined(RW612_SERIES)
		wifi_send_imu_raw_data(local_outbuf,
					   (m_len - sizeof(struct cmd_header) + INTF_HEADER_LEN));
#endif
		ret = RET_TYPE_WLAN;
	} else if (cmd_hd->type == TYPE_BT) {
#if defined(RW610_SERIES) || defined(RW612_SERIES)
		ret = imumc_raw_packet_send(buf, m_len, RET_TYPE_BT);
#else
#if defined(CONFIG_SUPPORT_BT_UART)
		ret = bt_raw_packet_send(buf, m_len);
#endif /*CONFIG_SUPPORT_BT_UART*/
#endif
	} else if (cmd_hd->type == TYPE_15_4) {
#if defined(RW610_SERIES) || defined(RW612_SERIES)
		ret = imumc_raw_packet_send(buf, m_len, RET_TYPE_ZIGBEE);
#elif defined(MIMXRT1176_cm7_SERIES) || (defined(MIMXRT1062_SERIES) || defined(MIMXRT1061_SERIES))
		ret = zigbee_raw_packet_send(buf, m_len);
#endif
	}

	return ret;
}

#if defined(RW610_SERIES) || defined(RW612_SERIES)
void send_imumc_response_to_uart(uint8_t *resp, int msg_len)
{
	uint32_t bridge_chksum = 0;
	uint32_t msglen;
	int index;
	uint32_t payloadlen;
	struct uart_header *uart_hdr;
	struct uart_cb *uart = &uartcb;

	payloadlen = msg_len;

	(void)memset(rx_buf, 0, BUF_LEN);
	(void)memcpy(rx_buf + sizeof(struct uart_header) + sizeof(struct cmd_header), resp,
			payloadlen);

	/* Added to send correct cmd header len */
	struct cmd_header *cmd_hdr;

	cmd_hdr = &last_cmd_hdr;
	cmd_hdr->length = payloadlen + sizeof(struct cmd_header);

	(void)memcpy(rx_buf + sizeof(struct uart_header), (uint8_t *)&last_cmd_hdr,
			 sizeof(struct cmd_header));

	uart_hdr = (struct uart_header *)rx_buf;
	uart_hdr->length = payloadlen + sizeof(struct cmd_header);
	uart_hdr->pattern = 0x5555;

	/* calculate CRC. The uart_header is excluded */
	msglen = payloadlen + sizeof(struct cmd_header);
	bridge_chksum = uart_get_crc32(uart, msglen, rx_buf + sizeof(struct uart_header));
	index = sizeof(struct uart_header) + msglen;

	rx_buf[index] = bridge_chksum & 0xff;
	rx_buf[index + 1] = (bridge_chksum & 0xff00) >> 8;
	rx_buf[index + 2] = (bridge_chksum & 0xff0000) >> 16;
	rx_buf[index + 3] = (bridge_chksum & 0xff000000) >> 24;

	/* write response to uart */
	uart_rtos_send(&uart_handle, rx_buf,
			   payloadlen + sizeof(struct cmd_header) + sizeof(struct uart_header) + 4);

	(void)memset(rx_buf, 0, BUF_LEN);
}

/*
 * It waits on wlan card interrupts on account
 * of command responses are handled here. The response is
 * read and then sent through the uart to the Mfg application
 */
hal_imumc_status_t  read_wlan_resp(IMU_Msg_t *pImuMsg, uint32_t len)
{
	assert(pImuMsg != NULL);
	assert(len != 0);
	assert(pImuMsg->Hdr.type == IMU_MSG_COMMAND_RESPONSE);

	struct uart_cb *uart = &uartcb;

	send_response_to_uart(uart, (uint8_t *)(pImuMsg->PayloadPtr[0]), 1);

	return kStatus_HAL_ImumcSuccess;
}

hal_imumc_return_status_t read_imumc_resp(void *param, uint8_t *packet, uint32_t len)
{
	assert(packet != NULL);
	assert(len != 0);

	send_imumc_response_to_uart(packet, len);

	return kStatus_HAL_RL_RELEASE;
}

static hal_imumc_status_t  imu_wifi_config(void)
{
	hal_imumc_status_t  state = kStatus_HAL_ImumcSuccess;

	/* Assign IMU channel for CPU1-CPU3 communication */
	state = HAL_ImuInit(kIMU_LinkCpu1Cpu3);
	assert(kStatus_HAL_ImumcSuccess == state);

	HAL_ImuInstallCallback(kIMU_LinkCpu1Cpu3, read_wlan_resp, IMU_MSG_COMMAND_RESPONSE);

	return state;
}

#if (defined(CONFIG_SUPPORT_BLE)) || (defined(CONFIG_SUPPORT_IEEE802154))
static hal_imumc_status_t  imumc_config(uint32_t linkId)
{
	hal_imumc_status_t  state = kStatus_HAL_ImumcSuccess;

	hal_imumc_config_t  config = {0};
	/* Init IMUMC/IMU Channel */
	config.local_addr = local_ept_list[linkId];
	config.remote_addr = remote_ept_list[linkId];
	config.imuLink = kIMU_LinkCpu2Cpu3;
	state = HAL_ImumcInit((hal_imumc_handle_t)imumcHandleList[linkId], &config);
	assert(kStatus_HAL_ImumcSuccess == state);

	/* IMUMC install rx callback */
	state = HAL_ImumcInstallRxCallback((hal_imumc_handle_t)imumcHandleList[linkId],
					   read_imumc_resp, NULL);
	assert(kStatus_HAL_ImumcSuccess == state);

	return state;
}

static hal_imumc_status_t  imumc_init(void)
{
	uint32_t linkId;
	hal_imumc_status_t  state = kStatus_HAL_ImumcSuccess;

	/* Init IMUMC/IMU Channel */
#if defined(CONFIG_SUPPORT_BLE)
	linkId = 0;
	state = imumc_config(linkId);
#endif
#if defined(CONFIG_SUPPORT_IEEE802154)
	linkId = 1;
	state = imumc_config(linkId);
#endif

	return state;
}
#endif

static void wifi_cau_temperature_timer_cb(struct k_timer *timer)
{
	/* write CAU temperature to CPU1 when it is not sleeping */
	if ((WIFI_REG32(WLAN_FW_WAKE_STATUS_ADDR) & 0x0CU) != 0x0CU) {
		cau_temperature_write_to_firmware();
	}
}

extern void WL_MCI_WAKEUP0_DriverIRQHandler(void);
extern void BLE_MCI_WAKEUP0_DriverIRQHandler(void);
#else
static void send_bt_response_to_uart(struct uart_cb *uart_bt, int msg_len)
{
	uint32_t bridge_chksum = 0;
	uint32_t msglen;
	int index;
	uint32_t payloadlen;
	struct uart_header *uart_hdr;
	struct uart_cb *uart = &uartcb;
	struct cmd_header *cmd_hdr;

	payloadlen = msg_len;

	memset(rx_buf, 0, BUF_LEN);
	memcpy(rx_buf + sizeof(struct uart_header) + sizeof(struct cmd_header), uart_bt->uart_buf,
			payloadlen);

	/* Added to send correct cmd header len */
	cmd_hdr         = &last_cmd_hdr;
	cmd_hdr->length = payloadlen + sizeof(struct cmd_header);

	memcpy(rx_buf + sizeof(struct uart_header), (uint8_t *)&last_cmd_hdr,
			sizeof(struct cmd_header));

	uart_hdr          = (struct uart_header *)rx_buf;
	uart_hdr->length  = payloadlen + sizeof(struct cmd_header);
	uart_hdr->pattern = 0x5555;

	/* calculate CRC. The uart_header is excluded */
	msglen        = payloadlen + sizeof(struct cmd_header);
	bridge_chksum = uart_get_crc32(uart, msglen, rx_buf + sizeof(struct uart_header));
	index         = sizeof(struct uart_header) + msglen;

	rx_buf[index]     = bridge_chksum & 0xff;
	rx_buf[index + 1] = (bridge_chksum & 0xff00) >> 8;
	rx_buf[index + 2] = (bridge_chksum & 0xff0000) >> 16;
	rx_buf[index + 3] = (bridge_chksum & 0xff000000) >> 24;


	/* write response to uart */
	uart_rtos_send(&uart_handle, rx_buf,
			   payloadlen + sizeof(struct cmd_header) + sizeof(struct uart_header) + 4);

	memset(rx_buf, 0, BUF_LEN);
}

#if (defined(MIMXRT1062_SERIES) || defined(MIMXRT1061_SERIES))
void send_zigbee_response_to_uart(uint8_t *rxData, uint32_t payloadlen)
{
	uint32_t bridge_chksum = 0;
	int index;
	struct uart_header *uart_hdr;
	struct uart_cb *uart = &uartcb;

	(void)memset(rx_buf, 0, BUF_LEN);
	(void)memcpy(rx_buf + sizeof(struct uart_header) + sizeof(struct cmd_header),
				rxData, payloadlen);

	/* Set correct command header length */
	struct cmd_header *cmd_hdr = &last_cmd_hdr;

	cmd_hdr->length = payloadlen + sizeof(struct cmd_header);
	(void)memcpy(rx_buf + sizeof(struct uart_header), (uint8_t *)&last_cmd_hdr,
				sizeof(struct cmd_header));

	uart_hdr = (struct uart_header *)rx_buf;
	uart_hdr->length = payloadlen + sizeof(struct cmd_header);
	uart_hdr->pattern = 0x5555;

	/* Calculate CRC (exclude uart_header) */
	bridge_chksum = uart_get_crc32(uart, uart_hdr->length,
			rx_buf + sizeof(struct uart_header));
	index = sizeof(struct uart_header) + uart_hdr->length;

	rx_buf[index] = bridge_chksum & 0xff;
	rx_buf[index + 1] = (bridge_chksum & 0xff00) >> 8;
	rx_buf[index + 2] = (bridge_chksum & 0xff0000) >> 16;
	rx_buf[index + 3] = (bridge_chksum & 0xff000000) >> 24;

	/* Send response to UART */
	uart_rtos_send(&uart_handle, rx_buf,
				payloadlen + sizeof(struct cmd_header) +
				sizeof(struct uart_header) + CHECKSUM_LEN);
	(void)memset(rx_buf, 0, BUF_LEN);
}
#endif

static void read_bt_resp(void)
{
	struct uart_cb *uart_bt = &uartcb_bt;
	uint32_t msglen;
	uint32_t payloadlen = 0;
	uint32_t currentlen = 0;
	size_t uart_rx_len  = 0;
	int len;

	memset(uart_bt->uart_buf, 0, sizeof(uart_bt->uart_buf));

	do {
		len         = 0;
		uart_rx_len = 0;
		currentlen  = payloadlen;

		while (len != LABTOOL_HCI_RESP_HDR_LEN) {
			uart_rtos_recv(&bt_uart_handle, uart_bt->uart_buf + len + payloadlen,
					LABTOOL_HCI_RESP_HDR_LEN, &uart_rx_len);
			len += uart_rx_len;
		}

		msglen = uart_bt->uart_buf[currentlen + 2];
		payloadlen += LABTOOL_HCI_RESP_HDR_LEN;
		uart_rx_len = 0;
		len         = 0;

		while (len != msglen) {
			uart_rtos_recv(&bt_uart_handle, uart_bt->uart_buf + len + payloadlen,
					msglen - len, &uart_rx_len);
			len += uart_rx_len;
		}

		payloadlen += len;

	} while (uart_bt->uart_buf[currentlen + 1] != 0x0E);

	send_bt_response_to_uart(uart_bt, payloadlen);
	memset(uart_bt->uart_buf, 0, sizeof(uart_bt->uart_buf));
}
#endif

#if (defined(MIMXRT1062_SERIES) || defined(MIMXRT1061_SERIES))
void read_zigbee_resp(void)
{
	spi_frame_hdr *pspihdr;
	int ret;

	memset(spi_buff_rx, 0, SPI_DEFAULT_RX_BUFF_LENGTH);
	memset(spi_buff_tx, 0, SPI_DEFAULT_TX_BUFF_LENGTH);

	uint8_t *start = spi_buff_rx;
	const uint8_t *end = spi_buff_rx + SPI_DEFAULT_ALIGN_ALLOWANCE;
	unsigned short payload_length = 0;

	pspihdr = (spi_frame_hdr *)spi_buff_tx;
	set_spi_frame_hdr(pspihdr, 0, 0, 0, 0, 0);

	/* Use Zephyr SPI API */
	struct spi_buf tx_buf = {
		.buf = spi_buff_tx,
		.len = SPI_DEFAULT_RX_DATA_SIZE
	};
	struct spi_buf rx_buf = {
		.buf = spi_buff_rx,
		.len = SPI_DEFAULT_RX_DATA_SIZE
	};

	const struct spi_buf_set tx_bufs = { .buffers = &tx_buf, .count = 1 };
	const struct spi_buf_set rx_bufs = { .buffers = &rx_buf, .count = 1 };

	ret = spi_transceive(spi_dev, &spi_cfg, &tx_bufs, &rx_bufs);
	if (ret != 0) {
		LOG_ERR("SPI receive failed: %d", ret);
		return;
	}

	/* Skip alignment bytes to find valid frame header */
	while (start != end && (start[0] == 0xFF || start[0] == 0x00)) {
		start++;
	}

	payload_length = ((spi_frame_hdr *)start)->data_len;
	start += sizeof(spi_frame_hdr);

	send_zigbee_response_to_uart(start, payload_length);

	memset(spi_buff_rx, 0, SPI_DEFAULT_RX_BUFF_LENGTH);
	memset(spi_buff_tx, 0, SPI_DEFAULT_TX_BUFF_LENGTH);
}
#endif

#if (defined(MIMXRT1062_SERIES) || defined(MIMXRT1061_SERIES))
void ot_rcp_gpio_init(void)
{
	volatile uint32_t *gpr26_reg = (volatile uint32_t *)IOMUXC_GPR26_ADDR;
	*gpr26_reg = (*gpr26_reg & ~GPIO_MUX1_GPIO_SEL_MASK) | GPIO_MUX1_GPIO_SEL(0x00U);
	volatile uint32_t *gpr27_reg = (volatile uint32_t *)IOMUXC_GPR27_ADDR;
	*gpr27_reg = (*gpr27_reg & ~GPIO_MUX2_GPIO_SEL_MASK) | GPIO_MUX2_GPIO_SEL(0x00U);

	const struct device *gpio1 = DEVICE_DT_GET(DT_NODELABEL(gpio1));

	if (!device_is_ready(gpio1)) {
		return;
	}
	k_sleep(K_MSEC(10));
	gpio_pin_set(gpio1, 19, 1);
	gpio_pin_set(gpio1, 24, 1);
	k_sleep(K_MSEC(200));
}

static int platform_i2c_send(const struct device *i2c_dev, uint8_t address,
							uint8_t byte1, uint8_t byte2)
{
	uint8_t data[2] = {byte1, byte2};
	int ret = i2c_write(i2c_dev, data, sizeof(data), address);

	if (ret != 0) {
		LOG_ERR("I2C write failed: %d", ret);
		return ret;
	}
	return 0;
}

static int platform_io_expander_init(void)
{
	const struct device *i2c_dev;
	int ret;

	/* Get I2C device from device tree */
	i2c_dev = DEVICE_DT_GET(I2C_NODE);
	if (!device_is_ready(i2c_dev)) {
		LOG_ERR("I2C device not ready");
		return -ENODEV;
	}

	/* Wait for RCP chip startup */
	k_sleep(K_MSEC(PLATFORM_CONFIG_DEFAULT_RESET_DELAY_MS));

	/* Configure PCA9534 Configuration Register */
	ret = platform_i2c_send(i2c_dev,
						PLATFORM_IOEXP_I2C_ADDR_7BIT,
						PLATFORM_IOEXP_CONFIGURATION_REG,
						PLATFORM_IOEXP_CONFIGURATION_SPI_ENABLE);
	if (ret != 0) {
		LOG_ERR("Failed to configure IO Expander: %d", ret);
		return ret;
	}

	return 0;
}
#endif
/*
 * task_main() runs in a loop. It polls the uart ring buffer
 * checks it for a complete command and sends the command to the
 * wlan card
 */
static void task_main(void)
{
	int32_t result = 0;
	(void)result;

#if !defined(RW610_SERIES) && !defined(RW612_SERIES)
	result = wifi_init_fcc(wlan_fw_bin, wlan_fw_bin_len);
	if (result != 0) {
		switch (result) {
		case MLAN_CARD_CMD_TIMEOUT:
		case MLAN_CARD_NOT_DETECTED:
			result = -WIFI_ERROR_CARD_NOT_DETECTED;
			break;
		case MLAN_STATUS_FW_DNLD_FAILED:
			result = -WIFI_ERROR_FW_DNLD_FAILED;
			break;
		case MLAN_STATUS_FW_NOT_DETECTED:
			result = -WIFI_ERROR_FW_NOT_DETECTED;
			break;
		case MLAN_STATUS_FW_NOT_READY:
			result = -WIFI_ERROR_FW_NOT_READY;
			break;
		}
		PRINTF("sd_wifi_init failed, result:%d\r\n", result);
	}

	assert(result == WM_SUCCESS);
#endif

#if (defined(MIMXRT1062_SERIES) || defined(MIMXRT1061_SERIES))
	/* Waiting for the RCP chip starts up */
	k_sleep(K_MSEC(PLATFORM_CONFIG_DEFAULT_RESET_DELAY_MS));

	/* Configure IO Expander to enable SPI pins */
	result = platform_io_expander_init();
	if (result != 0) {
		LOG_ERR("Failed to configure IO Expander: %d", result);
		return;
	}

	/* Get SPI device from device tree */
	spi_dev = DEVICE_DT_GET(SPI_NODE);
	if (!device_is_ready(spi_dev)) {
		LOG_ERR("SPI device not ready");
		return;
	}
#endif

#if defined(RW610_SERIES) || defined(RW612_SERIES)
	/* Enable IMU/RPMSG IRQ */
	IRQ_CONNECT(72, 1, WL_MCI_WAKEUP0_DriverIRQHandler, 0, 0);
	irq_enable(72);

	IRQ_CONNECT(90, 1, BLE_MCI_WAKEUP0_DriverIRQHandler, 0, 0);
	irq_enable(90);

	/* Download firmware */
#if !defined(CONFIG_SUPPORT_WIFI) && !defined(CONFIG_SUPPORT_BLE) &&                               \
	!defined(CONFIG_SUPPORT_IEEE802154)
#error "One of CONFIG_SUPPORT_WIFI, CONFIG_SUPPORT_BLE and CONFIG_SUPPORT_IEEE802154\
				should be defined, or it will not download any formware!!"
#endif
#if defined(CONFIG_SUPPORT_WIFI)
	sb3_fw_reset(LOAD_WIFI_FIRMWARE, 1, WIFI_FW_ADDRESS);
#endif

	/* 15d4 single and 15d4+ble combo */
#if defined(CONFIG_SUPPORT_IEEE802154)
	sb3_fw_reset(LOAD_15D4_FIRMWARE, 1, COMBO_FW_ADDRESS);
#elif defined(CONFIG_SUPPORT_BLE)
	/* only ble, no 15d4 */
	sb3_fw_reset(LOAD_BLE_FIRMWARE, 1, BLE_FW_ADDRESS);
#endif

	/* Initialize WIFI Driver */
	imu_wifi_config();

#if defined(CONFIG_SUPPORT_BLE) || defined(CONFIG_SUPPORT_IEEE802154)
	/* Initialize rpmsg */
	imumc_init();
#endif

	k_timer_init(&g_wifi_cau_temperature_timer, wifi_cau_temperature_timer_cb, NULL);
	k_timer_start(&g_wifi_cau_temperature_timer, K_MSEC(5000), K_MSEC(5000));
#endif /*defined(RW610_SERIES) || defined(RW612_SERIES)*/

	/* Initialize uart */
	result = uart_rtos_init(&uart_handle);
	if (result < 0) {
		LOG_ERR("Failed to initialize uart");
		return;
	}
#if defined(CONFIG_SUPPORT_BT_UART)
	/* Initialize uart */
	result = bt_uart_rtos_init(&bt_uart_handle);
	if (result < 0) {
		LOG_ERR("Failed to initialize bt-uart");
		return;
	}
#endif /*CONFIG_SUPPORT_BT_UART*/

	local_outbuf = pvPortMalloc(SDIO_OUTBUF_LEN);

	if (local_outbuf == NULL) {
		LOG_ERR("Failed to allocate buffer");
		return;
	}
	rx_buf = pvPortMalloc(BUF_LEN);
	if (rx_buf == NULL) {
		LOG_ERR("Failed to allocate buffer");
		return;
	}

	struct uart_cb *uart = &uartcb;

	uart_init_crc32(uart);

	size_t uart_rx_len = 0;
	int len = 0;
	int msg_len = 0;

	while (1) {
		len = 0;
		msg_len = 0;
		uart_rx_len = 0;
		(void)memset(uart->uart_buf, 0, sizeof(uart->uart_buf));

		while (len != LABTOOL_PATTERN_HDR_LEN) {
			uart_rtos_recv(&uart_handle, uart->uart_buf + len, LABTOOL_PATTERN_HDR_LEN,
				       &uart_rx_len);
			len += uart_rx_len;
		}

		/* Length of the packet is indicated by byte[2] & byte[3] of
		 * the packet excluding header[4 bytes] + checksum [4 bytes]
		 */
		msg_len = (uart->uart_buf[3] << 8) + uart->uart_buf[2];
		len = 0;
		uart_rx_len = 0;
		while (len != msg_len + CHECKSUM_LEN) {
			uart_rtos_recv(&uart_handle, uart->uart_buf + LABTOOL_PATTERN_HDR_LEN + len,
				       msg_len + CHECKSUM_LEN - len, &uart_rx_len);
			len += uart_rx_len;
		}

		/* validate the command including checksum */
		if (check_command_complete(uart->uart_buf) == WM_SUCCESS) {
			/* send fw cmd over SDIO after
			 * stripping off uart header
			 */
			int ret = process_input_cmd(uart->uart_buf, msg_len + 8);
			(void)memset(uart->uart_buf, 0, sizeof(uart->uart_buf));
			memset(host_resp_buf, 0x00, BUF_LEN);
#if defined(RW610_SERIES) || defined(RW612_SERIES)
			UNUSED(ret);
#else
			if (ret == RET_TYPE_WLAN) {
				OSA_TimeDelay(60);
				int rv = wlan_send_hostcmd(local_outbuf, BUF_LEN, host_resp_buf,
						BUF_LEN, &reqd_resp_len);
				if (rv != WM_SUCCESS)
					PRINTF("Receive response failed\r\n");
				else {
					send_response_to_uart(uart, host_resp_buf, RET_TYPE_WLAN,
							reqd_resp_len);
				}
			} else if (ret == RET_TYPE_BT) {
				read_bt_resp();
			}
#if (defined(MIMXRT1062_SERIES) || defined(MIMXRT1061_SERIES))
			else if (ret == RET_TYPE_ZIGBEE) {
				k_sleep(K_MSEC(60));
				read_zigbee_resp();
			}
#endif
			else {
				/*unused*/
			}
#endif
		} else {
			(void)memset(uart_handle.rx.buffer, 0, BUFFER_SIZE);
			(void)memset(uart_handle.tx.buffer, 0, BUFFER_SIZE);
		}
	}
}

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

int main(void)
{
#if (defined(MIMXRT1062_SERIES) || defined(MIMXRT1061_SERIES))
	ot_rcp_gpio_init();
#endif
	task_main();
	return 0;
}
