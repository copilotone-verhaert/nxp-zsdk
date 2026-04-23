/*
 * Copyright (c) 2025 NXP
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef NXP_VENDOR_COMMANDS_HPP_
#define NXP_VENDOR_COMMANDS_HPP_

#include <openthread/error.h>
#include <openthread/instance.h>
#include <stdint.h>
#include <fwk_platform_ot.h>

namespace ot {
namespace Nxp {

class NxpVendorCommands
{
public:
    explicit NxpVendorCommands(otInstance *aInstance);

    // Top-level commands
    otError ProcessTxPowerLimit(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessSetEui64(const char *aEui64Hex);
    otError ProcessCcaCfg(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessFwVersion(void);

    // Radio subcommands
    otError ProcessIRCmd(void);
    otError ProcessMfgCmd(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessEncrypt(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessDecrypt(uint8_t aArgsLength, char *aArgs[]);

private:
    otInstance *mInstance;
    // MFG helper functions
    otError MfgGetInt8(uint8_t aCmdId);
    otError MfgSetInt8(uint8_t aCmdId, const char *aValue, int8_t aMin, int8_t aMax);
    otError MfgUnmodulatedCW(uint8_t aArgsLength, char *aArgs[]);
    otError MfgGetRxResult(void);
    otError MfgStartRxTest(void);
    otError MfgBurstTx(uint8_t aArgsLength, char *aArgs[]);
    otError MfgContinuousCCA(uint8_t aArgsLength, char *aArgs[]);
    otError MfgPhyTxTestPsdu(uint8_t aArgsLength, char *aArgs[]);
    otError MfgSetGenericParam(uint8_t aArgsLength, char *aArgs[]);
    otError MfgGetSetLatency(uint8_t aArgsLength, char *aArgs[]);
    otError MfgGenericCommand(uint8_t aArgsLength, char *aArgs[]);

    bool mMfgEnabled;
    // Helper functions
    otError ParseHexString(const char *aHexString, uint8_t *aBuffer, uint8_t *aLength);
    otError ParseInteger(const char *aString, uint8_t *aValue);

};

} // namespace Nxp
} // namespace ot

#ifdef __cplusplus
extern "C" {
#endif

void *nxp_vendor_commands_get_instance(otInstance *aInstance);

#ifdef __cplusplus
}
#endif

#endif // NXP_VENDOR_COMMANDS_HPP_
