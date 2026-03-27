/*
 * Copyright (c) 2025 NXP
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nxp_vendor_types.h"
#include "nxp_vendor_spinel.h"

#include <zephyr/logging/log.h>
#include <lib/spinel/radio_spinel.hpp>
#include <lib/spinel/spinel_decoder.hpp>
#include <string.h>

LOG_MODULE_REGISTER(nxp_vendor_spinel, LOG_LEVEL_DBG);

using namespace ot::Spinel;

// ============================================================================
// Access to RadioSpinel via platformGetRadioSpinel()
// ============================================================================
extern "C" void *platformGetRadioSpinel(void);

static RadioSpinel *GetRadioSpinel(void)
{
    RadioSpinel *radioSpinel = static_cast<RadioSpinel *>(platformGetRadioSpinel());

    if (radioSpinel == nullptr) {
        LOG_ERR("RadioSpinel not available");
    }

    return radioSpinel;
}

// ============================================================================
// Generic GET/SET wrappers
// ============================================================================
extern "C" otError nxp_vendor_spinel_get_utf8(spinel_prop_key_t aPropKey, char *aBuffer, size_t aBufferSize)
{

    RadioSpinel *radioSpinel = GetRadioSpinel();

    if (radioSpinel == nullptr || aBuffer == nullptr || aBufferSize == 0) {
        return OT_ERROR_INVALID_STATE;
    }

    memset(aBuffer, 0, aBufferSize);

    otError error = radioSpinel->Get(aPropKey, SPINEL_DATATYPE_UTF8_S, aBuffer, aBufferSize);

    if (error != OT_ERROR_NONE) {
        LOG_ERR("GET UTF8 0x%04x failed: %d", aPropKey, error);
    }

    return error;
}

extern "C" otError nxp_vendor_spinel_get_int8(spinel_prop_key_t aPropKey, int8_t *aValue)
{

    RadioSpinel *radioSpinel = GetRadioSpinel();

    if (radioSpinel == nullptr || aValue == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    otError error = radioSpinel->Get(aPropKey, SPINEL_DATATYPE_INT8_S, aValue);

    if (error != OT_ERROR_NONE) {
        LOG_ERR("GET INT8 0x%04x failed: %d", aPropKey, error);
    }

    return error;
}

extern "C" otError nxp_vendor_spinel_get_uint8(spinel_prop_key_t aPropKey, uint8_t * aValue)
{

    RadioSpinel *radioSpinel = GetRadioSpinel();

    if (radioSpinel == nullptr || aValue == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    otError error = radioSpinel->Get(aPropKey, SPINEL_DATATYPE_UINT8_S, aValue);

    if (error != OT_ERROR_NONE) {
        LOG_ERR("GET UINT8 0x%04x failed: %d", aPropKey, error);
    }

    return error;
}

extern "C" otError nxp_vendor_spinel_get_uint16(spinel_prop_key_t aPropKey, uint16_t *aValue)
{

    RadioSpinel *radioSpinel = GetRadioSpinel();

    if (radioSpinel == nullptr || aValue == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    otError error = radioSpinel->Get(aPropKey, SPINEL_DATATYPE_UINT16_S, aValue);

    if (error != OT_ERROR_NONE) {
        LOG_ERR("GET UINT16 0x%04x failed: %d", aPropKey, error);
    }

    return error;
}

extern "C" otError nxp_vendor_spinel_get_data(spinel_prop_key_t aPropKey, uint8_t *aBuffer,  uint16_t *aBufferSize)
{

    RadioSpinel *radioSpinel = GetRadioSpinel();

    if (radioSpinel == nullptr || aBuffer == nullptr || aBufferSize == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    const uint8_t *data = nullptr;
    uint16_t dataLen = 0;

    otError error = radioSpinel->Get(aPropKey, SPINEL_DATATYPE_DATA_S, &data, &dataLen);

    if (error == OT_ERROR_NONE && data != nullptr) {
        if (dataLen > *aBufferSize) {
            dataLen = *aBufferSize;
        }
        memcpy(aBuffer, data, dataLen);
        *aBufferSize = dataLen;
    } else {
        *aBufferSize = 0;
    }

    return error;
}

extern "C" otError nxp_vendor_spinel_set_int8(spinel_prop_key_t aPropKey, int8_t aValue)
{

    RadioSpinel *radioSpinel = GetRadioSpinel();

    if (radioSpinel == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    otError error = radioSpinel->Set(aPropKey, SPINEL_DATATYPE_INT8_S, aValue);

    if (error != OT_ERROR_NONE) {
        LOG_ERR("SET INT8 0x%04x failed: %d", aPropKey, error);
    }

    return error;
}

extern "C" otError nxp_vendor_spinel_set_uint8(spinel_prop_key_t aPropKey, uint8_t aValue)
{

    RadioSpinel *radioSpinel = GetRadioSpinel();

    if (radioSpinel == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    otError error = radioSpinel->Set(aPropKey, SPINEL_DATATYPE_UINT8_S, aValue);

    if (error != OT_ERROR_NONE) {
        LOG_ERR("SET UINT8 0x%04x failed: %d", aPropKey, error);
    }

    return error;
}

extern "C" otError nxp_vendor_spinel_set_data(spinel_prop_key_t aPropKey, const uint8_t *aData, uint16_t aDataLen)
{

    RadioSpinel *radioSpinel = GetRadioSpinel();

    if (radioSpinel == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    otError error = radioSpinel->Set(aPropKey, SPINEL_DATATYPE_DATA_S, aData, aDataLen);

    if (error != OT_ERROR_NONE) {
        LOG_ERR("SET DATA 0x%04x failed: %d", aPropKey, error);
    }

    return error;
}

// ============================================================================
// MFG Command (Manufacturing)
// ============================================================================

extern "C" otError otPlatRadioMfgCommand( const uint8_t *aPayload, uint16_t aPayloadLen, uint8_t *aResponse, uint16_t *aResponseLen)
{

    RadioSpinel *radioSpinel = GetRadioSpinel();

    if (radioSpinel == nullptr || aPayload == nullptr || aResponse == nullptr || aResponseLen == nullptr) {
        LOG_ERR("Invalid arguments");
        return OT_ERROR_INVALID_ARGS;
    }

    LOG_INF("Sending MFG command, payload len=%u", aPayloadLen);
    LOG_HEXDUMP_DBG(aPayload, aPayloadLen, "MFG payload:");

    // Pack payload into buffer for GetWithParam
    uint8_t buffer[256];
    spinel_ssize_t packed;

    packed = spinel_datatype_pack(buffer, sizeof(buffer),
                                   SPINEL_DATATYPE_DATA_S,
                                   aPayload, aPayloadLen);

    if (packed <= 0) {
        LOG_ERR("Failed to pack MFG payload");
        return OT_ERROR_FAILED;
    }

    // Send MFG command using GetWithParam
    uint16_t responseLen = *aResponseLen;

    otError error = radioSpinel->GetWithParam(
        SPINEL_PROP_VENDOR_NXP_MFG_CMD,
        buffer,
        static_cast<spinel_size_t>(packed),
        SPINEL_DATATYPE_DATA_S,
        aResponse,
        &responseLen
    );

    if (error == OT_ERROR_NONE) {
        *aResponseLen = responseLen;
        LOG_INF("MFG command response len=%u", responseLen);
        LOG_HEXDUMP_DBG(aResponse, responseLen, "MFG response:");
    } else {
        LOG_ERR("MFG command failed: %d", error);
    }

    return error;
}

// ============================================================================
// CCA Configuration
// ============================================================================

extern "C" otError otPlatRadioCcaConfigValue(spinel_prop_key_t aPropKey, otCCAModeConfig *aCcaCfg, uint8_t aSetFlag)
{
    RadioSpinel *radioSpinel = GetRadioSpinel();

    if (radioSpinel == nullptr || aCcaCfg == nullptr) {
        LOG_ERR("Invalid arguments");
        return OT_ERROR_INVALID_ARGS;
    }

    otError error;

    if (aSetFlag == 0) {
        // GET - WITH STRUCT wrapper
        uint8_t mode, cca1, cca2corr, cca2min;

        error = radioSpinel->Get(aPropKey,
                                 SPINEL_DATATYPE_STRUCT_S(
                                     SPINEL_DATATYPE_UINT8_S
                                     SPINEL_DATATYPE_UINT8_S
                                     SPINEL_DATATYPE_UINT8_S
                                     SPINEL_DATATYPE_UINT8_S
                                 ),
                                 &mode,
                                 &cca1,
                                 &cca2corr,
                                 &cca2min);

        if (error == OT_ERROR_NONE) {
            aCcaCfg->mCcaMode = mode;
            aCcaCfg->mCca1Threshold = cca1;
            aCcaCfg->mCca2CorrThreshold = cca2corr;
            aCcaCfg->mCca2MinNumOfCorrTh = cca2min;

            LOG_INF("GET CCA config:");
            LOG_INF("  mode=%u (0x%02x)", mode, mode);
            LOG_INF("  cca1=%u (0x%02x)", cca1, cca1);
            LOG_INF("  cca2corr=%u (0x%02x)", cca2corr, cca2corr);
            LOG_INF("  cca2min=%u (0x%02x)", cca2min, cca2min);
        } else {
            LOG_ERR("Failed to GET CCA config: %d", error);
        }
    } else {
        // SET - WITH STRUCT wrapper
        LOG_INF("Setting CCA config:");
        LOG_INF("  mode=%u (0x%02x)", aCcaCfg->mCcaMode, aCcaCfg->mCcaMode);
        LOG_INF("  cca1=%u (0x%02x)", aCcaCfg->mCca1Threshold, aCcaCfg->mCca1Threshold);
        LOG_INF("  cca2corr=%u (0x%02x)", aCcaCfg->mCca2CorrThreshold, aCcaCfg->mCca2CorrThreshold);
        LOG_INF("  cca2min=%u (0x%02x)", aCcaCfg->mCca2MinNumOfCorrTh, aCcaCfg->mCca2MinNumOfCorrTh);

        error = radioSpinel->Set(aPropKey,
                                 SPINEL_DATATYPE_STRUCT_S(
                                     SPINEL_DATATYPE_UINT8_S
                                     SPINEL_DATATYPE_UINT8_S
                                     SPINEL_DATATYPE_UINT8_S
                                     SPINEL_DATATYPE_UINT8_S
                                 ),
                                 aCcaCfg->mCcaMode,
                                 aCcaCfg->mCca1Threshold,
                                 aCcaCfg->mCca2CorrThreshold,
                                 aCcaCfg->mCca2MinNumOfCorrTh);

        if (error == OT_ERROR_NONE) {
            LOG_INF("SET CCA config success");
        } else {
            LOG_ERR("SET CCA config failed: %d", error);
        }
    }

    return error;
}

// ============================================================================
// Vendor hook for async notifications
// ============================================================================

namespace ot {
namespace Spinel {

otError RadioSpinel::VendorHandleValueIs(spinel_prop_key_t aPropKey)
{
    LOG_DBG("VendorHandleValueIs: 0x%04x", aPropKey);

    switch (aPropKey) {
    case SPINEL_PROP_VENDOR_NXP_GET_FW_VERSION_CMD:
    case SPINEL_PROP_VENDOR_NXP_MFG_CMD:
    case SPINEL_PROP_VENDOR_NXP_IR_CMD:
    case SPINEL_PROP_VENDOR_NXP_GET_SET_CCA_CONFIGURE_CMD:
        return OT_ERROR_NONE;
    default:
        return OT_ERROR_NOT_FOUND;
    }
}

} // namespace Spinel
} // namespace ot

// ============================================================================
// TX Power Limit - Single UINT8
// ============================================================================

extern "C" otError otPlatRadioSetTxPowerLimit(uint8_t aTxPowerLimit, bool aEnableCh26Clamp)
{

    RadioSpinel *radioSpinel = GetRadioSpinel();

    if (radioSpinel == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    // Validate range
    uint8_t powerValue = aTxPowerLimit & 0x7F;
    if (powerValue < 1 || powerValue > 20) {
        LOG_ERR("TX power limit out of range (1-20): %u", powerValue);
        return OT_ERROR_INVALID_ARGS;
    }

    // Encode: bits 0-6 = power, bit 7 = CH26 clamp
    uint8_t encodedValue = powerValue | (aEnableCh26Clamp ? 0x80 : 0x00);

    LOG_INF("Setting TX power limit:");
    LOG_INF("  Power: %u dBm", powerValue);
    LOG_INF("  CH26 clamp: %s", aEnableCh26Clamp ? "enabled" : "disabled");
    LOG_INF("  Encoded: 0x%02x", encodedValue);

    otError error = radioSpinel->Set(
        SPINEL_PROP_VENDOR_NXP_GET_SET_TXPOWERLIMIT_CMD,
        SPINEL_DATATYPE_UINT8_S,
        encodedValue
    );

    if (error == OT_ERROR_NONE) {
        LOG_INF("TX power limit set successfully");
    } else {
        LOG_ERR("Failed to set TX power limit: %d", error);
    }

    return error;
}

extern "C" otError otPlatRadioGetTxPowerLimit(uint8_t *aTxPowerLimit, bool *aEnableCh26Clamp)
{

    RadioSpinel *radioSpinel = GetRadioSpinel();

    if (radioSpinel == nullptr || aTxPowerLimit == nullptr || aEnableCh26Clamp == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    uint8_t encodedValue = 0;

    otError error = radioSpinel->Get(
        SPINEL_PROP_VENDOR_NXP_GET_SET_TXPOWERLIMIT_CMD,
        SPINEL_DATATYPE_UINT8_S,
        &encodedValue
    );

    if (error == OT_ERROR_NONE) {
        *aTxPowerLimit = encodedValue & 0x7F;
        *aEnableCh26Clamp = (encodedValue & 0x80) != 0;

        LOG_INF("GET TX power limit:");
        LOG_INF("  Power: %u dBm", *aTxPowerLimit);
        LOG_INF("  CH26 clamp: %s", *aEnableCh26Clamp ? "enabled" : "disabled");
        LOG_INF("  Raw: 0x%02x", encodedValue);
    } else {
        LOG_ERR("Failed to get TX power limit: %d", error);
    }

    return error;
}

// ============================================================================
// Set EUI64 - 8 bytes DATA
// ============================================================================

extern "C" otError otPlatRadioSetEui64(const uint8_t *aEui64)
{

    RadioSpinel *radioSpinel = GetRadioSpinel();

    if (radioSpinel == nullptr || aEui64 == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    LOG_INF("Setting EUI64:");
    LOG_HEXDUMP_INF(aEui64, 8, "  EUI64:");

    otError error = radioSpinel->Set(
        SPINEL_PROP_VENDOR_NXP_SET_EUI64_CMD,
        SPINEL_DATATYPE_DATA_S,
        aEui64,
        8
    );

    if (error == OT_ERROR_NONE) {
        LOG_INF("EUI64 set successfully");
    } else {
        LOG_ERR("Failed to set EUI64: %d", error);
    }

    return error;
}
