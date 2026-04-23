/*
 * Copyright (c) 2025 NXP
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef NXP_VENDOR_SPINEL_H
#define NXP_VENDOR_SPINEL_H

#include <openthread/error.h>
#include <openthread/instance.h>
#include <lib/spinel/spinel.h>
#include <stdint.h>
#include <stdbool.h>

#include "nxp_vendor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* NXP vendor property definitions*/
#define SPINEL_PROP_VENDOR_NXP_GET_TX_POWER              (SPINEL_PROP_VENDOR__BEGIN + 0x100)
#define SPINEL_PROP_VENDOR_NXP_SET_TX_POWER              (SPINEL_PROP_VENDOR__BEGIN + 0x101)
#define SPINEL_PROP_VENDOR_NXP_GET_RSSI                  (SPINEL_PROP_VENDOR__BEGIN + 0x102)
#define SPINEL_PROP_VENDOR_NXP_GET_CHIP_INFO             (SPINEL_PROP_VENDOR__BEGIN + 0x103)
#define SPINEL_PROP_VENDOR_NXP_IR_CMD                    (SPINEL_PROP_VENDOR__BEGIN + 0x101)
#define SPINEL_PROP_VENDOR_NXP_SET_EUI64_CMD             (SPINEL_PROP_VENDOR__BEGIN + 0x10A)
#define SPINEL_PROP_VENDOR_NXP_GET_SET_TXPOWERLIMIT_CMD  (SPINEL_PROP_VENDOR__BEGIN + 0x10B)
#define SPINEL_PROP_VENDOR_NXP_GET_SET_CCA_CONFIGURE_CMD (SPINEL_PROP_VENDOR__BEGIN + 0x10C)
#define SPINEL_PROP_VENDOR_NXP_GET_FW_VERSION_CMD        (SPINEL_PROP_VENDOR__BEGIN + 0x10D)
#define SPINEL_PROP_VENDOR_NXP_MFG_CMD                   (SPINEL_PROP_VENDOR__BEGIN + 0x3FF)

/* -------------------------------------------------------------------------- */
/*                             Private definitions                            */
/* -------------------------------------------------------------------------- */
#define MFG_CMD_ACTION_GET 0
#define MFG_CMD_ACTION_SET 1

#define MFG_CMD_GET_SET_CHANNEL 0x0b       /* 11 */
#define MFG_CMD_GET_SET_TXPOWER 0x0f       /* 15 */
#define MFG_CMD_CONTINUOUS_TX 0x11         /* 17 */
#define MFG_CMD_UNMODULATED_CW_TX 0x12     /* 18 */
#define MFG_CMD_GET_SET_PAYLOAD_SIZE 0x14  /* 20 */
#define MFG_CMD_GET_RX_RESULT 0x1f         /* 31 */
#define MFG_CMD_START_RX_TEST 0x20         /* 32 */
#define MFG_CMD_BURST_TX 0x21              /* 33 */
#define MFG_CMD_DUTY_CYCLE_TX 0x23         /* 35 */
#define MFG_CMD_GET_SET_CCA_THRESHOLD 0x2F /* 47 */
#define MFG_CMD_CONTINUOUS_CCA_TEST 0X31   /* 49 */
#define MFG_CMD_GET_CCA_STATUS 0x32        /* 50 */
#define MFG_CMD_CONTINUOUS_ED_TEST 0x37    /* 55 */
#define MFG_CMD_GET_ED_VALUE 0x38          /* 56 */
#define MFG_CMD_PHY_TX_TEST_PSDU 0x39      /* 57 */
#define MFG_CMD_PHY_RX_TX_ACK_TEST 0x3A    /* 58 */
#define MFG_CMD_SET_GENERIC_PARAM 0x3B     /* 59 */
#define MFG_CMD_GET_SET_LATENCY 0x3C       /* 60 */
#define MFG_CMD_BRIC_ENCRYPT 0x46          /* 70 */
#define MFG_CMD_BRIC_DECRYPT 0x47          /* 71 */
#define MFG_CMD_CRASH_SIMULATION 0x48      /* 72 */
#define MFG_CMD_GENERIC 0xFF               /* 255*/

/* Crypto constants */
#define SETUP_AUTHTAGLEN        10

/* ============================================================================*/
/* Generic GET/SET wrappers*/
/* ============================================================================*/

otError nxp_vendor_spinel_get_utf8(spinel_prop_key_t aPropKey, char *aBuffer, size_t aBufferSize);

otError nxp_vendor_spinel_get_int8(spinel_prop_key_t aPropKey, int8_t *aValue);

otError nxp_vendor_spinel_get_uint8(spinel_prop_key_t aPropKey, uint8_t *aValue);

otError nxp_vendor_spinel_get_uint16(spinel_prop_key_t aPropKey, uint16_t *aValue);

otError nxp_vendor_spinel_get_data(spinel_prop_key_t aPropKey, uint8_t *aBuffer,
									uint16_t *aBufferSize);

otError nxp_vendor_spinel_set_int8(spinel_prop_key_t aPropKey, int8_t aValue);

otError nxp_vendor_spinel_set_uint8(spinel_prop_key_t aPropKey, uint8_t aValue);

otError nxp_vendor_spinel_set_data(spinel_prop_key_t aPropKey, const uint8_t *aData,
									uint16_t aDataLen);

/* ============================================================================*/
/* MFG Command (Manufacturing)*/
/* ============================================================================*/
otError otPlatRadioMfgCommand(const uint8_t *aPayload, uint16_t aPayloadLen, uint8_t *aResponse,
								uint16_t *aResponseLen);

/* ============================================================================*/
/* CCA Configuration*/
/* ============================================================================*/
otError otPlatRadioCcaConfigValue(spinel_prop_key_t aPropKey, otCCAModeConfig *aCcaCfg,
									uint8_t aSetFlag);

/* ============================================================================*/
/* TX Power Limit*/
/* ============================================================================*/
otError otPlatRadioSetTxPowerLimit(uint8_t aTxPowerLimit, bool aEnableCh26Clamp);

otError otPlatRadioGetTxPowerLimit(uint8_t *aTxPowerLimit, bool *aEnableCh26Clamp);

/* ============================================================================*/
/* Set EUI64*/
/* ============================================================================*/
otError otPlatRadioSetEui64(const uint8_t *aEui64);

#ifdef __cplusplus
}
#endif

#endif /* NXP_VENDOR_SPINEL_H */
