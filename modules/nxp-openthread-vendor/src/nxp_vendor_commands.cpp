/*
 * Copyright (c) 2025 NXP
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nxp_vendor_commands.hpp"
#include "nxp_vendor_spinel.h"
#include "nxp_vendor_types.h"

#include <openthread/platform/radio.h>
#include <openthread/cli.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(nxp_vendor_cmd, LOG_LEVEL_DBG);

namespace ot {
namespace Nxp {

NxpVendorCommands::NxpVendorCommands(otInstance *aInstance)
    : mInstance(aInstance)
    , mMfgEnabled(false)
{
}

// ============================================================================
// Helper: Parse hex string to bytes
// ============================================================================
otError NxpVendorCommands::ParseHexString(const char *aHexString, uint8_t *aBuffer, uint8_t *aLength)
{
    otError error = OT_ERROR_NONE;
    size_t hexLen = strlen(aHexString);
    uint8_t maxLen = *aLength;

    if ((hexLen % 2) != 0) {
        error = OT_ERROR_INVALID_ARGS;
        goto exit;
    }

    if ((hexLen / 2) > maxLen) {
        error = OT_ERROR_NO_BUFS;
        goto exit;
    }

    *aLength = 0;

    for (size_t i = 0; i < hexLen; i += 2) {
        char byteStr[3] = {aHexString[i], aHexString[i + 1], '\0'};
        char *endPtr;
        long value = strtol(byteStr, &endPtr, 16);

        if (*endPtr != '\0') {
            error = OT_ERROR_INVALID_ARGS;
            goto exit;
        }

        aBuffer[*aLength] = static_cast<uint8_t>(value);
        (*aLength)++;
    }

exit:
    return error;
}

// ============================================================================
// Helper: Parse single hex/decimal value to uint8_t
// ============================================================================
otError NxpVendorCommands::ParseInteger(const char *aString, uint8_t *aValue)
{
    if (aString == nullptr || aValue == nullptr) {
        return OT_ERROR_INVALID_ARGS;
    }

    char *endPtr;
    long value;

    // Try hex first (with or without 0x prefix)
    if (strncmp(aString, "0x", 2) == 0 || strncmp(aString, "0X", 2) == 0) {
        value = strtol(aString, &endPtr, 16);
    } else {
        // Check if string contains hex digits (a-f)
        bool isHex = false;
        for (const char *p = aString; *p != '\0'; p++) {
            if ((*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F')) {
                isHex = true;
                break;
            }
        }

        if (isHex) {
            value = strtol(aString, &endPtr, 16);
        } else {
            value = strtol(aString, &endPtr, 10);
        }
    }

    // Accept signed values (-128 to 127)
    if (*endPtr != '\0' || value < -128 || value > 127) {
        return OT_ERROR_INVALID_ARGS;
    }

    *aValue = static_cast<uint8_t>(value);
    return OT_ERROR_NONE;
}

// ============================================================================
// TX Power Limit
// ============================================================================
otError NxpVendorCommands::ProcessTxPowerLimit(uint8_t aArgsLength, char *aArgs[])
{
    LOG_INF("ProcessTxPowerLimit");

    otError error = OT_ERROR_INVALID_ARGS;

    if (aArgsLength == 0) {
        // GET
        uint8_t powerLimit = 0;
        bool ch26Clamp = false;

        error = otPlatRadioGetTxPowerLimit(&powerLimit, &ch26Clamp);

        if (error == OT_ERROR_NONE) {
            otCliOutputFormat("TX Power Limit: %u dBm\r\n", powerLimit);
            otCliOutputFormat("CH26 Clamp: %s\r\n", ch26Clamp ? "enabled" : "disabled");
        }
    } else if (aArgsLength >= 1 && aArgsLength <= 2) {
        // SET
        uint8_t powerLimit = 0;

        error = ParseInteger(aArgs[0], &powerLimit);
        if (error != OT_ERROR_NONE) {
            otCliOutputFormat("Invalid power limit value\r\n");
            goto exit;
        }

        bool ch26Clamp = true; // Default: enabled

        if (aArgsLength == 2) {
            if (strcmp(aArgs[1], "disableRFCH26Clamp") == 0) {
                ch26Clamp = false;
            } else if (strcmp(aArgs[1], "enableRFCH26Clamp") == 0) {
                ch26Clamp = true;
            } else {
                otCliOutputFormat("Invalid CH26 clamp option\r\n");
                error = OT_ERROR_INVALID_ARGS;
                goto exit;
            }
        }

        error = otPlatRadioSetTxPowerLimit(powerLimit, ch26Clamp);

        if (error == OT_ERROR_NONE) {
            otCliOutputFormat("TX power limit set to: %u dBm\r\n", powerLimit);
        }
    } else {
        otCliOutputFormat("Usage: txpwrlimit [<limit> [enableRFCH26Clamp|disableRFCH26Clamp]]\r\n");
    }

exit:
    return error;
}

// ============================================================================
// Set EUI64
// ============================================================================
otError NxpVendorCommands::ProcessSetEui64(const char *aEui64Hex)
{
    LOG_INF("ProcessSetEui64: %s", aEui64Hex);

    otError error = OT_ERROR_INVALID_ARGS;

    if (aEui64Hex == nullptr) {
        return error;
    }

    const char *hex = aEui64Hex;
    size_t len = strlen(aEui64Hex);

    // Accept "0x..." or just "..."
    if (len == 18 && hex[0] == '0' && hex[1] == 'x') {
        hex = hex + 2;
        len = 16;
    }

    if (len != 16) {
        otCliOutputFormat("Invalid EUI64 format (expected 16 hex chars or 0x...)\r\n");
        return OT_ERROR_INVALID_ARGS;
    }

    uint8_t eui64[8];
    error = OT_ERROR_NONE;

    // Parse hex string to bytes
    for (uint32_t i = 0; (i < 8) && (error == OT_ERROR_NONE); i++) {
        eui64[i] = 0;
        for (uint32_t k = 0; k < 2; k++) {
            uint8_t byte = *hex++;

            if (byte >= '0' && byte <= '9')
                byte = byte - '0';
            else if (byte >= 'a' && byte <= 'f')
                byte = byte - 'a' + 10;
            else if (byte >= 'A' && byte <= 'F')
                byte = byte - 'A' + 10;
            else {
                error = OT_ERROR_INVALID_ARGS;
                break;
            }

            eui64[i] = (eui64[i] << 4) | (byte & 0xF);
        }
    }

    if (error == OT_ERROR_NONE) {
        error = otPlatRadioSetEui64(eui64);

        if (error == OT_ERROR_NONE) {
            otCliOutputFormat("EUI64 set successfully\r\n");
        }
    }

    return error;
}

// ============================================================================
// CCA Configuration
// ============================================================================
otError NxpVendorCommands::ProcessCcaCfg(uint8_t aArgsLength, char *aArgs[])
{
    otError error = OT_ERROR_NONE;

    if (aArgsLength == 0) {
        // GET - Format like i.MX
        otCCAModeConfig ccaCfg;

        error = otPlatRadioCcaConfigValue(
            SPINEL_PROP_VENDOR_NXP_GET_SET_CCA_CONFIGURE_CMD,
            &ccaCfg,
            0 // GET
        );

        if (error == OT_ERROR_NONE) {
            otCliOutputFormat("CCA Configuration:\r\n");
            otCliOutputFormat("CCA Mode type: CCA1=0x01, CCA2=0x02, CCA3=0x03[CCA1 AND CCA2], CCA3=0x04[CCA1 OR CCA2], NoCCA=0xFF: 0x%x\r\n",
                            ccaCfg.mCcaMode);
            otCliOutputFormat("CCA1 Threshold Value : 0x%x\r\n", ccaCfg.mCca1Threshold);
            otCliOutputFormat("CCA2 Correlation Threshold Value : 0x%x\r\n", ccaCfg.mCca2CorrThreshold);
            otCliOutputFormat("CCA2 Minimim Number of Correlation Threshold Value : 0x%x\r\n", ccaCfg.mCca2MinNumOfCorrTh);
        }
    } else if (aArgsLength >= 4) {
        // SET
        otCCAModeConfig ccaCfg;

        error = ParseInteger(aArgs[0], &ccaCfg.mCcaMode);
        if (error != OT_ERROR_NONE) {
            otCliOutputFormat("Invalid CCA mode\r\n");
            goto exit;
        }

        error = ParseInteger(aArgs[1], &ccaCfg.mCca1Threshold);
        if (error != OT_ERROR_NONE) {
            otCliOutputFormat("Invalid CCA1 threshold\r\n");
            goto exit;
        }

        error = ParseInteger(aArgs[2], &ccaCfg.mCca2CorrThreshold);
        if (error != OT_ERROR_NONE) {
            otCliOutputFormat("Invalid CCA2 corr threshold\r\n");
            goto exit;
        }

        error = ParseInteger(aArgs[3], &ccaCfg.mCca2MinNumOfCorrTh);
        if (error != OT_ERROR_NONE) {
            otCliOutputFormat("Invalid CCA2 min num corr\r\n");
            goto exit;
        }

        LOG_INF("Parsed CCA values:");
        LOG_INF("  mode=%u (0x%02x)", ccaCfg.mCcaMode, ccaCfg.mCcaMode);
        LOG_INF("  cca1=%u (0x%02x)", ccaCfg.mCca1Threshold, ccaCfg.mCca1Threshold);
        LOG_INF("  cca2corr=%u (0x%02x)", ccaCfg.mCca2CorrThreshold, ccaCfg.mCca2CorrThreshold);
        LOG_INF("  cca2min=%u (0x%02x)", ccaCfg.mCca2MinNumOfCorrTh, ccaCfg.mCca2MinNumOfCorrTh);

        error = otPlatRadioCcaConfigValue(
            SPINEL_PROP_VENDOR_NXP_GET_SET_CCA_CONFIGURE_CMD,
            &ccaCfg,
            1 // SET
        );

        if (error == OT_ERROR_NONE) {
            otCliOutputFormat("CCA configuration set successfully\r\n");
        }
    } else {
        error = OT_ERROR_INVALID_ARGS;
        otCliOutputFormat("Usage: ccacfg [<mode> <cca1> <cca2corr> <cca2min>]\r\n");
    }

exit:
    return error;
}

// ============================================================================
// FW Version
// ============================================================================
otError NxpVendorCommands::ProcessFwVersion(void)
{
    LOG_INF("ProcessGetFwVersion");

    char fwVersion[128];
    otError error = nxp_vendor_spinel_get_utf8(SPINEL_PROP_VENDOR_NXP_GET_FW_VERSION_CMD, fwVersion, sizeof(fwVersion)
    );

    if (error == OT_ERROR_NONE) {
        otCliOutputFormat("Firmware Version: %s\r\n", fwVersion);
    }

    return error;
}

// ============================================================================
// Independent Reset
// ============================================================================
otError NxpVendorCommands::ProcessIRCmd(void)
{
    LOG_INF("ProcessIRCmd - Resetting RCP");

    otError error = OT_ERROR_NONE;

    if (PLATFORM_ResetOt() < 0) {
        error = OT_ERROR_FAILED;
        otCliOutputFormat("Failed to reset RCP\r\n");
    } else {
        otCliOutputFormat("RCP reset successfully\r\n");
    }

    return error;
}

// ============================================================================
// Encrypt
// ============================================================================
otError NxpVendorCommands::ProcessEncrypt(uint8_t aArgsLength, char *aArgs[])
{
    otError error = OT_ERROR_INVALID_ARGS;

    if (aArgsLength < 3) {
        otCliOutputFormat("Usage: encrypt <key_hex> <nonce_hex> <plaintext_hex>\r\n");
        return error;
    }

    uint8_t key[16];
    uint8_t nonce[13];
    uint8_t plaintext[128];
    uint8_t keyLen = 16;
    uint8_t nonceLen = 13;
    uint8_t plaintextLen = sizeof(plaintext);

    // Parse key (16 bytes = 32 hex chars)
    error = ParseHexString(aArgs[0], key, &keyLen);
    if (error != OT_ERROR_NONE || keyLen != 16) {
        otCliOutputFormat("Invalid key (expected 32 hex chars)\r\n");
        return OT_ERROR_INVALID_ARGS;
    }

    // Parse nonce (13 bytes = 26 hex chars)
    error = ParseHexString(aArgs[1], nonce, &nonceLen);
    if (error != OT_ERROR_NONE || nonceLen != 13) {
        otCliOutputFormat("Invalid nonce (expected 26 hex chars)\r\n");
        return OT_ERROR_INVALID_ARGS;
    }

    // Parse plaintext
    error = ParseHexString(aArgs[2], plaintext, &plaintextLen);
    if (error != OT_ERROR_NONE) {
        otCliOutputFormat("Invalid plaintext\r\n");
        return error;
    }

	// Build MFG command payload
	uint8_t payload[256];
	uint8_t *p = payload;

	*p++ = 11;                      // Length placeholder
	*p++ = MFG_CMD_BRIC_ENCRYPT;    // Command ID (0x46)
	*p++ = 0;                       // Action: Use BRIC HW Crypto
	*p++ = 0;                       // Return code placeholder

	*p++ = 16;                      // Key length
	memcpy(p, key, 16);             // Key
	p += 16;

	*p++ = 13;                      // Nonce length
	memcpy(p, nonce, 13);           // Nonce
	p += 13;

	*p++ = plaintextLen;            // Plaintext length
	memcpy(p, plaintext, plaintextLen); // Plaintext
	p += plaintextLen;

	uint16_t payloadLen = p - payload;

    // Send command
    uint8_t response[256];
    uint16_t responseLen = sizeof(response);

    error = otPlatRadioMfgCommand(payload, payloadLen, response, &responseLen);

	if (error == OT_ERROR_NONE && responseLen > 33 && response[3] == 0) {
		// Response format: [len][cmd][action][status][Klen][Nlen][AuthTaglen][CTlen][BRIC_retval][padding][Tag][CT]


		uint8_t Klen = response[4];
		uint8_t Nlen = response[5];
		uint8_t AuthTaglen = response[6];
		uint8_t CTlen = response[7];
		uint32_t bricRetval = response[8] | (response[9] << 8) | (response[10] << 16) | (response[11] << 24);
		OT_UNUSED_VARIABLE(Klen);
		OT_UNUSED_VARIABLE(Nlen);

		if (bricRetval != 0) {
			otCliOutputFormat("BRIC encryption error: %u\r\n", bricRetval);
			error = OT_ERROR_FAILED;
		} else {
			// Skip to tag (after padding to 16-byte boundary)
			uint16_t tagOffset = 12 + ((16 - (12 % 16)) % 16);

			// Display Tag
			otCliOutputFormat("Tag: ");
			for (uint8_t i = 0; i < AuthTaglen; i++) {
				otCliOutputFormat("%02x", response[tagOffset + i]);
			}
			otCliOutputFormat("\r\n");

			// Skip to ciphertext (after tag + padding to 16-byte boundary)
			uint16_t ctOffset = tagOffset + AuthTaglen;
			ctOffset += ((16 - (ctOffset % 16)) % 16);

			// Display Ciphertext
			otCliOutputFormat("Ciphertext: ");
			for (uint8_t i = 0; i < CTlen; i++) {
				otCliOutputFormat("%02x", response[ctOffset + i]);
			}
			otCliOutputFormat("\r\n");
		}
	}
	else {
		otCliOutputFormat("Encryption failed\r\n");
		error = OT_ERROR_FAILED;
    }
    return error;
}

// ============================================================================
// Decrypt
// ============================================================================
otError NxpVendorCommands::ProcessDecrypt(uint8_t aArgsLength, char *aArgs[])
{
    otError error = OT_ERROR_INVALID_ARGS;

    if (aArgsLength < 4) {
        otCliOutputFormat("Usage: decrypt <key_hex> <nonce_hex> <ciphertext_hex> <tag_hex>\r\n");
        return error;
    }

    // Use static buffers to avoid stack overflow
    static uint8_t key[16];
    static uint8_t nonce[13];
    static uint8_t ciphertext[128];
    static uint8_t tag[SETUP_AUTHTAGLEN];
    static uint8_t payload[256];
    static uint8_t response[256];

    uint8_t keyLen = 16;
    uint8_t nonceLen = 13;
    uint8_t ciphertextLen = sizeof(ciphertext);
    uint8_t tagLen = SETUP_AUTHTAGLEN;

    // Parse key (16 bytes = 32 hex chars)
    error = ParseHexString(aArgs[0], key, &keyLen);
    if (error != OT_ERROR_NONE || keyLen != 16) {
        otCliOutputFormat("Invalid key (expected 32 hex chars)\r\n");
        return OT_ERROR_INVALID_ARGS;
    }

    // Parse nonce (13 bytes = 26 hex chars)
    error = ParseHexString(aArgs[1], nonce, &nonceLen);
    if (error != OT_ERROR_NONE || nonceLen != 13) {
        otCliOutputFormat("Invalid nonce (expected 26 hex chars)\r\n");
        return OT_ERROR_INVALID_ARGS;
    }

    // Parse ciphertext
    error = ParseHexString(aArgs[2], ciphertext, &ciphertextLen);
    if (error != OT_ERROR_NONE) {
        otCliOutputFormat("Invalid ciphertext\r\n");
        return error;
    }

    // Parse tag (10 bytes = 20 hex chars)
    error = ParseHexString(aArgs[3], tag, &tagLen);
    if (error != OT_ERROR_NONE || tagLen != SETUP_AUTHTAGLEN) {
        otCliOutputFormat("Invalid tag (expected 20 hex chars)\r\n");
        return OT_ERROR_INVALID_ARGS;
    }

	// Build MFG command payload
	uint8_t *p = payload;

	*p++ = 11;                      // Length placeholder
	*p++ = MFG_CMD_BRIC_DECRYPT;    // Command ID (0x47)
	*p++ = 0;                       // Action: Use BRIC HW Crypto
	*p++ = 0;                       // Return code placeholder

	*p++ = 16;                      // Key length
	memcpy(p, key, 16);             // Key
	p += 16;

	*p++ = 13;                      // Nonce length
	memcpy(p, nonce, 13);           // Nonce
	p += 13;

	*p++ = SETUP_AUTHTAGLEN;        // Tag length
	memcpy(p, tag, SETUP_AUTHTAGLEN); // Tag
	p += SETUP_AUTHTAGLEN;

	*p++ = ciphertextLen;           // Ciphertext length
	memcpy(p, ciphertext, ciphertextLen); // Ciphertext
	p += ciphertextLen;

	uint16_t payloadLen = p - payload;    uint16_t responseLen = sizeof(response);

    // Send MFG command
    error = otPlatRadioMfgCommand(payload, payloadLen, response, &responseLen);

    if (error == OT_ERROR_NONE && responseLen > 33 && response[3] == 0) {
        // Response format: [len][cmd][action][status][Klen][Nlen][AuthTaglen][PTlen][BRIC_retval][padding][plaintext]

        uint8_t Klen = response[4];
        uint8_t Nlen = response[5];
        uint8_t AuthTaglen = response[6];
        uint8_t PTlen = response[7];
        uint32_t bricRetval = response[8] | (response[9] << 8) | (response[10] << 16) | (response[11] << 24);

        OT_UNUSED_VARIABLE(Klen);
        OT_UNUSED_VARIABLE(Nlen);
        OT_UNUSED_VARIABLE(AuthTaglen);

        if (bricRetval != 0) {
            otCliOutputFormat("BRIC decryption error: %u\r\n", bricRetval);
            error = OT_ERROR_FAILED;
        } else {
            // Plaintext starts at offset 32 (after header + padding)
            uint16_t ptOffset = 32;

            // Display Plaintext
            otCliOutputFormat("Plaintext: ");
            for (uint8_t i = 0; i < PTlen; i++) {
                otCliOutputFormat("%02x", response[ptOffset + i]);
            }
            otCliOutputFormat("\r\n");
        }
    } else {
        otCliOutputFormat("Decryption failed\r\n");
        error = OT_ERROR_FAILED;
    }

    return error;
}

// ============================================================================
// Manufacturing command
// ============================================================================
otError NxpVendorCommands::ProcessMfgCmd(uint8_t aArgsLength, char *aArgs[])
{
    otError error = OT_ERROR_INVALID_ARGS;

	if (aArgsLength == 0) {
		otCliOutputFormat("Usage: mfgcmd <cmd_id> [args...]\r\n");
		otCliOutputFormat("\r\n");
		otCliOutputFormat("Manufacturing Commands:\r\n");
		otCliOutputFormat("  0/1              - Disable/Enable MFG mode\r\n");
		otCliOutputFormat("  11               - Get channel\r\n");
		otCliOutputFormat("  12 <ch>          - Set channel (11-26)\r\n");
		otCliOutputFormat("  15               - Get TX power\r\n");
		otCliOutputFormat("  16 <pwr>         - Set TX power (dBm)\r\n");
		otCliOutputFormat("  17 <0|1>         - Continuous TX (0=stop, 1=start)\r\n");
		otCliOutputFormat("  18 <0|1> [pwr] [ch] - Unmodulated CW (0=stop, 1=start)\r\n");
		otCliOutputFormat("  20               - Get payload size\r\n");
		otCliOutputFormat("  21 <size>        - Set payload size (17-116)\r\n");
		otCliOutputFormat("  31               - Get RX result\r\n");
		otCliOutputFormat("  32               - Start RX test\r\n");
		otCliOutputFormat("  33 <mode> <gap>  - Burst TX\r\n");
		otCliOutputFormat("  35 <0|1>         - Duty cycle TX\r\n");
		otCliOutputFormat("  47               - Get CCA threshold\r\n");
		otCliOutputFormat("  48 <val>         - Set CCA threshold\r\n");
		otCliOutputFormat("  49 <0|1> <mode>  - Continuous CCA test\r\n");
		otCliOutputFormat("  50               - Get CCA status\r\n");
		otCliOutputFormat("  55 <0|1>         - Continuous ED test\r\n");
		otCliOutputFormat("  56               - Get ED value\r\n");
		otCliOutputFormat("  57 <cnt> <gap> <ack> - PHY TX test PSDU\r\n");
		otCliOutputFormat("  58 <0|1>         - PHY RX/TX ACK test\r\n");
		otCliOutputFormat("  59 <seq> <pan> <dst> <src> - Set generic param\r\n");
		otCliOutputFormat("  60 <0|1> [args]  - Get/Set latency\r\n");
		otCliOutputFormat("  72               - Crash simulation\r\n");
		otCliOutputFormat("  255 <hex>        - Generic MFG command\r\n");
		return OT_ERROR_NONE;
	}

    uint8_t cmdId = static_cast<uint8_t>(atoi(aArgs[0]));

    // Enable/Disable MFG mode
    if (cmdId == 0 || cmdId == 1) {
        mMfgEnabled = (cmdId == 1);
        otCliOutputFormat("MFG mode %s\r\n", mMfgEnabled ? "enabled" : "disabled");
        return OT_ERROR_NONE;
    }

    // Check if MFG mode is enabled
    if (!mMfgEnabled) {
        otCliOutputFormat("MFG mode not enabled. Use: mfgcmd 1\r\n");
        return OT_ERROR_INVALID_STATE;
    }

    // Process MFG commands
    switch (cmdId) {
    case MFG_CMD_GET_SET_CHANNEL: // Get channel
        error = MfgGetInt8(MFG_CMD_GET_SET_CHANNEL);
        break;

    case MFG_CMD_GET_SET_CHANNEL+1: // Set channel
        if (aArgsLength >= 2) {
            error = MfgSetInt8(MFG_CMD_GET_SET_CHANNEL, aArgs[1], 11, 26);
        }
        break;

    case MFG_CMD_GET_SET_TXPOWER: // Get TX power
        error = MfgGetInt8(MFG_CMD_GET_SET_TXPOWER);
        break;

    case MFG_CMD_GET_SET_TXPOWER+1: // Set TX power
        if (aArgsLength >= 2) {
            error = MfgSetInt8(MFG_CMD_GET_SET_TXPOWER, aArgs[1], -20, 20);
        }
        break;

    case MFG_CMD_CONTINUOUS_TX: // Continuous TX
        if (aArgsLength >= 2) {
            error = MfgSetInt8(MFG_CMD_CONTINUOUS_TX, aArgs[1], 0, 1);
        }
        break;

    case MFG_CMD_UNMODULATED_CW_TX: // Unmodulated CW TX
        error = MfgUnmodulatedCW(aArgsLength, aArgs);
        break;

    case MFG_CMD_GET_SET_PAYLOAD_SIZE: // Get payload size
        error = MfgGetInt8(MFG_CMD_GET_SET_PAYLOAD_SIZE);
        break;

    case MFG_CMD_GET_SET_PAYLOAD_SIZE+1: // Set payload size
        if (aArgsLength >= 2) {
            error = MfgSetInt8(MFG_CMD_GET_SET_PAYLOAD_SIZE, aArgs[1], 17, 116);
        }
        break;

    case MFG_CMD_GET_RX_RESULT: // Get RX result
        error = MfgGetRxResult();
        break;

    case MFG_CMD_START_RX_TEST: // Start RX test
        error = MfgStartRxTest();
        break;

    case MFG_CMD_BURST_TX: // Burst TX
        error = MfgBurstTx(aArgsLength, aArgs);
        break;

    case MFG_CMD_DUTY_CYCLE_TX: // Duty cycle TX
        if (aArgsLength >= 2) {
            error = MfgSetInt8(MFG_CMD_DUTY_CYCLE_TX, aArgs[1], 0, 1);
        }
        break;

    case MFG_CMD_GET_SET_CCA_THRESHOLD: // Get CCA threshold
        error = MfgGetInt8(MFG_CMD_GET_SET_CCA_THRESHOLD);
        break;

    case MFG_CMD_GET_SET_CCA_THRESHOLD+1: // Set CCA threshold
        if (aArgsLength >= 2) {
            error = MfgSetInt8(MFG_CMD_GET_SET_CCA_THRESHOLD, aArgs[1], -110, 0);
        }
        break;

    case MFG_CMD_CONTINUOUS_CCA_TEST: // Continuous CCA test
        error = MfgContinuousCCA(aArgsLength, aArgs);
        break;

    case MFG_CMD_GET_CCA_STATUS: // Get CCA status
        error = MfgGetInt8(MFG_CMD_GET_CCA_STATUS);
        break;

    case MFG_CMD_CONTINUOUS_ED_TEST: // Continuous ED test
        if (aArgsLength >= 2) {
            error = MfgSetInt8(MFG_CMD_CONTINUOUS_ED_TEST, aArgs[1], 0, 1);
        }
        break;

    case MFG_CMD_GET_ED_VALUE: // Get ED value
        error = MfgGetInt8(MFG_CMD_GET_ED_VALUE);
        break;

	case MFG_CMD_PHY_TX_TEST_PSDU: // PHY TX test PSDU
		error = MfgPhyTxTestPsdu(aArgsLength, aArgs);
		break;

	case MFG_CMD_PHY_RX_TX_ACK_TEST: // PHY RX/TX ACK test
		if (aArgsLength >= 2) {
			error = MfgSetInt8(MFG_CMD_PHY_RX_TX_ACK_TEST, aArgs[1], 0, 1);
		}
		break;

	case MFG_CMD_SET_GENERIC_PARAM: // Set generic param
		error = MfgSetGenericParam(aArgsLength, aArgs);
		break;

	case MFG_CMD_GET_SET_LATENCY: // Get/Set latency
		error = MfgGetSetLatency(aArgsLength, aArgs);
		break;

	case MFG_CMD_CRASH_SIMULATION: // Crash simulation
		error = MfgGetInt8(MFG_CMD_CRASH_SIMULATION);
		break;

	case MFG_CMD_GENERIC: // Generic MFG command
		error = MfgGenericCommand(aArgsLength, aArgs);
    break;

    default:
        otCliOutputFormat("Unknown MFG command: %d\r\n", cmdId);
        error = OT_ERROR_NOT_IMPLEMENTED;
        break;
    }

    return error;
}
// ============================================================================
// MFG Helper Functions
// ============================================================================
otError NxpVendorCommands::MfgGetInt8(uint8_t aCmdId)
{
    static uint8_t payload[12];
    static uint8_t response[12];

    payload[0] = 11;
    payload[1] = aCmdId;
    payload[2] = MFG_CMD_ACTION_GET;
    payload[3] = 0;

    uint16_t responseLen = sizeof(response);
    otError error = otPlatRadioMfgCommand(payload, 12, response, &responseLen);

    if (error == OT_ERROR_NONE && responseLen >= 5 && response[3] == 0) {
        otCliOutputFormat("%d\r\n", static_cast<int8_t>(response[4]));
    }

    return error;
}

otError NxpVendorCommands::MfgSetInt8(uint8_t aCmdId, const char *aValue, int8_t aMin, int8_t aMax)
{
    int8_t value = static_cast<int8_t>(atoi(aValue));

    if (value < aMin || value > aMax) {
        otCliOutputFormat("Value out of range (%d-%d)\r\n", aMin, aMax);
        return OT_ERROR_INVALID_ARGS;
    }

    static uint8_t payload[12];
    static uint8_t response[12];

    payload[0] = 11;
    payload[1] = aCmdId;
    payload[2] = MFG_CMD_ACTION_SET;
    payload[3] = 0;
    payload[4] = static_cast<uint8_t>(value);

    uint16_t responseLen = sizeof(response);
    otError error = otPlatRadioMfgCommand(payload, 12, response, &responseLen);

    if (error == OT_ERROR_NONE && response[3] == 0) {
        otCliOutputFormat("Done\r\n");
    }

    return error;
}

otError NxpVendorCommands::MfgUnmodulatedCW(uint8_t aArgsLength, char *aArgs[])
{
    if (aArgsLength < 2) {
        return OT_ERROR_INVALID_ARGS;
    }

    uint8_t state = static_cast<uint8_t>(atoi(aArgs[1]));
    uint8_t power = 0;
    uint8_t channel = 11;

    if (state == 1 && aArgsLength >= 4) {
        power = static_cast<uint8_t>(atoi(aArgs[2]));
        channel = static_cast<uint8_t>(atoi(aArgs[3]));
    }

    static uint8_t payload[12];
    static uint8_t response[12];

    payload[0] = 11;
    payload[1] = MFG_CMD_UNMODULATED_CW_TX;
    payload[2] = MFG_CMD_ACTION_SET;
    payload[3] = 0;
    payload[4] = state;
    payload[5] = power;
    payload[6] = channel;

    uint16_t responseLen = sizeof(response);
    return otPlatRadioMfgCommand(payload, 12, response, &responseLen);
}

otError NxpVendorCommands::MfgGetRxResult(void)
{
    static uint8_t payload[12];
    static uint8_t response[12];

    payload[0] = 11;
    payload[1] = MFG_CMD_GET_RX_RESULT;
    payload[2] = MFG_CMD_ACTION_GET;
    payload[3] = 0;

    uint16_t responseLen = sizeof(response);
    otError error = otPlatRadioMfgCommand(payload, 12, response, &responseLen);

    if (error == OT_ERROR_NONE && responseLen >= 11 && response[3] == 0) {
        uint16_t rxPktCount = response[5] | (response[6] << 8);
        uint16_t totalPktCount = response[7] | (response[8] << 8);

        otCliOutputFormat("status: %d\r\n", response[4]);
        otCliOutputFormat("rx_pkt_count: %d\r\n", rxPktCount);
        otCliOutputFormat("total_pkt_count: %d\r\n", totalPktCount);
        otCliOutputFormat("rssi: %d\r\n", static_cast<int8_t>(response[9]));
        otCliOutputFormat("lqi: %d\r\n", response[10]);
    }

    return error;
}

otError NxpVendorCommands::MfgStartRxTest(void)
{
    static uint8_t payload[12];
    static uint8_t response[12];

    payload[0] = 11;
    payload[1] = MFG_CMD_START_RX_TEST;
    payload[2] = MFG_CMD_ACTION_SET;
    payload[3] = 0;

    uint16_t responseLen = sizeof(response);
    return otPlatRadioMfgCommand(payload, 12, response, &responseLen);
}

otError NxpVendorCommands::MfgBurstTx(uint8_t aArgsLength, char *aArgs[])
{
    if (aArgsLength < 3) {
        return OT_ERROR_INVALID_ARGS;
    }

    uint8_t mode = static_cast<uint8_t>(atoi(aArgs[1]));
    uint8_t gap = static_cast<uint8_t>(atoi(aArgs[2]));

    if (mode >= 8 || gap <= 5) {
        return OT_ERROR_INVALID_ARGS;
    }

    static uint8_t payload[12];
    static uint8_t response[12];

    payload[0] = 11;
    payload[1] = MFG_CMD_BURST_TX;
    payload[2] = MFG_CMD_ACTION_SET;
    payload[3] = 0;
    payload[4] = mode;
    payload[5] = gap;

    uint16_t responseLen = sizeof(response);
    return otPlatRadioMfgCommand(payload, 12, response, &responseLen);
}

otError NxpVendorCommands::MfgContinuousCCA(uint8_t aArgsLength, char *aArgs[])
{
    if (aArgsLength < 3) {
        return OT_ERROR_INVALID_ARGS;
    }

    uint8_t state = static_cast<uint8_t>(atoi(aArgs[1]));
    uint8_t mode = static_cast<uint8_t>(atoi(aArgs[2]));

    if (state >= 2 || mode >= 5) {
        return OT_ERROR_INVALID_ARGS;
    }

    static uint8_t payload[12];
    static uint8_t response[12];

    payload[0] = 11;
    payload[1] = MFG_CMD_CONTINUOUS_CCA_TEST;
    payload[2] = MFG_CMD_ACTION_SET;
    payload[3] = 0;
    payload[4] = state;
    payload[5] = mode;

    uint16_t responseLen = sizeof(response);
    return otPlatRadioMfgCommand(payload, 12, response, &responseLen);
}

otError NxpVendorCommands::MfgPhyTxTestPsdu(uint8_t aArgsLength, char *aArgs[])
{
    if (aArgsLength < 4) {
        otCliOutputFormat("Usage: mfgcmd 57 <count_opt> <gap> <ackEnable>\r\n");
        return OT_ERROR_INVALID_ARGS;
    }

    uint8_t count_opt = static_cast<uint8_t>(atoi(aArgs[1]));
    uint8_t gap = static_cast<uint8_t>(atoi(aArgs[2]));
    uint8_t ackEnable = static_cast<uint8_t>(atoi(aArgs[3]));

    if (count_opt >= 8 || gap <= 5 || ackEnable >= 2) {
        otCliOutputFormat("Invalid parameters\r\n");
        return OT_ERROR_INVALID_ARGS;
    }

    static uint8_t payload[12];
    static uint8_t response[12];

    payload[0] = 11;
    payload[1] = MFG_CMD_PHY_TX_TEST_PSDU;
    payload[2] = MFG_CMD_ACTION_SET;
    payload[3] = 0;
    payload[4] = count_opt;
    payload[5] = gap;
    payload[6] = ackEnable;

    uint16_t responseLen = sizeof(response);
    otError error = otPlatRadioMfgCommand(payload, 12, response, &responseLen);

    if (error == OT_ERROR_NONE && response[3] == 0) {
        otCliOutputFormat("Done\r\n");
    }

    return error;
}

otError NxpVendorCommands::MfgSetGenericParam(uint8_t aArgsLength, char *aArgs[])
{
    if (aArgsLength < 5) {
        otCliOutputFormat("Usage: mfgcmd 59 <seq_num> <panid_hex> <destaddr_hex> <srcaddr_hex>\r\n");
        return OT_ERROR_INVALID_ARGS;
    }

    uint8_t seqNum = static_cast<uint8_t>(atoi(aArgs[1]));
    uint16_t panid = static_cast<uint16_t>(strtol(aArgs[2], NULL, 16));
    uint16_t destaddr = static_cast<uint16_t>(strtol(aArgs[3], NULL, 16));
    uint16_t srcaddr = static_cast<uint16_t>(strtol(aArgs[4], NULL, 16));

    static uint8_t payload[12];
    static uint8_t response[12];

    payload[0] = 11;
    payload[1] = MFG_CMD_SET_GENERIC_PARAM;
    payload[2] = MFG_CMD_ACTION_SET;
    payload[3] = 0;
    payload[4] = seqNum;
    payload[5] = static_cast<uint8_t>(panid & 0xFF);
    payload[6] = static_cast<uint8_t>((panid >> 8) & 0xFF);
    payload[7] = static_cast<uint8_t>(destaddr & 0xFF);
    payload[8] = static_cast<uint8_t>((destaddr >> 8) & 0xFF);
    payload[9] = static_cast<uint8_t>(srcaddr & 0xFF);
    payload[10] = static_cast<uint8_t>((srcaddr >> 8) & 0xFF);

    uint16_t responseLen = sizeof(response);
    otError error = otPlatRadioMfgCommand(payload, 12, response, &responseLen);

    if (error == OT_ERROR_NONE && response[3] == 0) {
        otCliOutputFormat("Done\r\n");
    }

    return error;
}

otError NxpVendorCommands::MfgGetSetLatency(uint8_t aArgsLength, char *aArgs[])
{
    if (aArgsLength < 2) {
        otCliOutputFormat("Usage: mfgcmd 60 <get|set> [state] [tx_rx_toggle] [gpio] [panid_msb] [panid_lsb]\r\n");
        return OT_ERROR_INVALID_ARGS;
    }

    uint8_t action = static_cast<uint8_t>(atoi(aArgs[1]));

    static uint8_t payload[12];
    static uint8_t response[12];

    payload[0] = 11;
    payload[1] = MFG_CMD_GET_SET_LATENCY;
    payload[2] = action; // 0=GET, 1=SET
    payload[3] = 0;

    if (action == MFG_CMD_ACTION_SET && aArgsLength >= 7) {
        payload[4] = static_cast<uint8_t>(atoi(aArgs[2])); // State
        payload[5] = static_cast<uint8_t>(atoi(aArgs[3])); // TX/RX Toggle
        payload[6] = static_cast<uint8_t>(atoi(aArgs[4])); // GPIO number
        payload[7] = static_cast<uint8_t>(atoi(aArgs[5])); // PANID[15:8]
        payload[8] = static_cast<uint8_t>(atoi(aArgs[6])); // PANID[7:0]
    }

    uint16_t responseLen = sizeof(response);
    otError error = otPlatRadioMfgCommand(payload, 12, response, &responseLen);

    if (error == OT_ERROR_NONE && response[3] == 0) {
        if (action == MFG_CMD_ACTION_GET && responseLen >= 9) {
            otCliOutputFormat("State: %d\r\n", response[4]);
            otCliOutputFormat("TX/RX Toggle: %d\r\n", response[5]);
            otCliOutputFormat("GPIO number: %d\r\n", response[6]);
            otCliOutputFormat("PANID: 0x%04x\r\n", (response[7] << 8) | response[8]);
        } else {
            otCliOutputFormat("Done\r\n");
        }
    }

    return error;
}

otError NxpVendorCommands::MfgGenericCommand(uint8_t aArgsLength, char *aArgs[])
{
    if (aArgsLength < 2) {
        otCliOutputFormat("Usage: mfgcmd 255 <hex_payload>\r\n");
        return OT_ERROR_INVALID_ARGS;
    }

    static uint8_t payload[256];
    static uint8_t response[256];

    uint8_t payloadLen = sizeof(payload)-1;
    otError error = ParseHexString(aArgs[1], payload, &payloadLen);

    if (error != OT_ERROR_NONE) {
        otCliOutputFormat("Invalid hex payload\r\n");
        return error;
    }

    uint16_t responseLen = sizeof(response);
    error = otPlatRadioMfgCommand(payload, payloadLen, response, &responseLen);

    if (error == OT_ERROR_NONE) {
        otCliOutputFormat("Response: ");
        for (uint16_t i = 0; i < responseLen; i++) {
            otCliOutputFormat("%02x", response[i]);
        }
        otCliOutputFormat("\r\n");
    }

    return error;
}


} // namespace Nxp
} // namespace ot

// Singleton instance
static ot::Nxp::NxpVendorCommands *sNxpVendorCommands = nullptr;

extern "C" void *nxp_vendor_commands_get_instance(otInstance *aInstance)
{
    if (sNxpVendorCommands == nullptr && aInstance != nullptr) {
        sNxpVendorCommands = new ot::Nxp::NxpVendorCommands(aInstance);
    }
    return sNxpVendorCommands;
}
