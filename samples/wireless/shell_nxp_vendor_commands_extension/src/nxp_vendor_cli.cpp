/*
 * Copyright (c) 2025 NXP
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>
#include <openthread/cli.h>
#include <openthread/instance.h>
#include "nxp_vendor_commands.hpp"

LOG_MODULE_REGISTER(nxp_vendor_cli, LOG_LEVEL_INF);

extern "C" otInstance *openthread_get_default_instance(void);

// ============================================================================
// Macros
// ============================================================================

#ifndef OT_ARRAY_LENGTH
#define OT_ARRAY_LENGTH(aArray) (sizeof(aArray) / sizeof(aArray[0]))
#endif

// ============================================================================
// Helper: Get NxpVendorCommands instance
// ============================================================================

static ot::Nxp::NxpVendorCommands *GetNxpCommands(void)
{
    otInstance *instance = openthread_get_default_instance();
    ot::Nxp::NxpVendorCommands *nxpCmd = static_cast<ot::Nxp::NxpVendorCommands *>(nxp_vendor_commands_get_instance(instance));

    if (nxpCmd == nullptr) {
        otCliOutputFormat("Error: NXP vendor commands not initialized\r\n");
    }

    return nxpCmd;
}

// ============================================================================
// radio_nxp subcommands
// ============================================================================

static otError cmd_radio_nxp_ircmd(void *aContext, uint8_t aArgsLength, char *aArgs[])
{
    OT_UNUSED_VARIABLE(aContext);
    OT_UNUSED_VARIABLE(aArgsLength);
    OT_UNUSED_VARIABLE(aArgs);

    ot::Nxp::NxpVendorCommands *nxpCmd = GetNxpCommands();
    if (nxpCmd == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    return nxpCmd->ProcessIRCmd();
}

static otError cmd_radio_nxp_mfgcmd(void *aContext, uint8_t aArgsLength, char *aArgs[])
{
    OT_UNUSED_VARIABLE(aContext);

    ot::Nxp::NxpVendorCommands *nxpCmd = GetNxpCommands();
    if (nxpCmd == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    return nxpCmd->ProcessMfgCmd(aArgsLength, aArgs);
}

static otError cmd_radio_nxp_ccacfg(void *aContext, uint8_t aArgsLength, char *aArgs[])
{
    OT_UNUSED_VARIABLE(aContext);

    ot::Nxp::NxpVendorCommands *nxpCmd = GetNxpCommands();
    if (nxpCmd == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    return nxpCmd->ProcessCcaCfg(aArgsLength, aArgs);
}

static otError cmd_radio_nxp_fwversion(void *aContext, uint8_t aArgsLength, char *aArgs[])
{
    OT_UNUSED_VARIABLE(aContext);
    OT_UNUSED_VARIABLE(aArgsLength);
    OT_UNUSED_VARIABLE(aArgs);

    ot::Nxp::NxpVendorCommands *nxpCmd = GetNxpCommands();
    if (nxpCmd == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    return nxpCmd->ProcessFwVersion();
}

static otError cmd_radio_nxp_encrypt(void *aContext, uint8_t aArgsLength, char *aArgs[])
{
    OT_UNUSED_VARIABLE(aContext);

    ot::Nxp::NxpVendorCommands *nxpCmd = GetNxpCommands();
    if (nxpCmd == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    return nxpCmd->ProcessEncrypt(aArgsLength, aArgs);
}

static otError cmd_radio_nxp_decrypt(void *aContext, uint8_t aArgsLength, char *aArgs[])
{
    OT_UNUSED_VARIABLE(aContext);

    ot::Nxp::NxpVendorCommands *nxpCmd = GetNxpCommands();
    if (nxpCmd == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    return nxpCmd->ProcessDecrypt(aArgsLength, aArgs);
}

// ============================================================================
// radio_nxp command table
// ============================================================================

static const otCliCommand kRadioNxpSubCommands[] = {
    {"ircmd", cmd_radio_nxp_ircmd},
    {"mfgcmd", cmd_radio_nxp_mfgcmd},
    {"ccacfg", cmd_radio_nxp_ccacfg},
    {"fwversion", cmd_radio_nxp_fwversion},
    {"encrypt", cmd_radio_nxp_encrypt},
    {"decrypt", cmd_radio_nxp_decrypt},
};

// ============================================================================
// radio_nxp dispatcher
// ============================================================================

static otError cmd_radio_nxp(void *aContext, uint8_t aArgsLength, char *aArgs[])
{
    otError error = OT_ERROR_INVALID_COMMAND;

    if (aArgsLength == 0) {
        otCliOutputFormat("Usage: radio_nxp <subcommand>\r\n");
        otCliOutputFormat("Subcommands:\r\n");
        otCliOutputFormat("  ircmd       - Send IR command\r\n");
        otCliOutputFormat("  mfgcmd      - Manufacturing commands\r\n");
        otCliOutputFormat("  ccacfg      - Get/Set CCA configuration\r\n");
        otCliOutputFormat("  fwversion   - Get firmware version\r\n");
        otCliOutputFormat("  encrypt     - Encrypt data\r\n");
        otCliOutputFormat("  decrypt     - Decrypt data\r\n");
        return OT_ERROR_INVALID_ARGS;
    }

    // Find and execute subcommand
    for (size_t i = 0; i < OT_ARRAY_LENGTH(kRadioNxpSubCommands); i++) {
        if (strcmp(aArgs[0], kRadioNxpSubCommands[i].mName) == 0) {
            error = kRadioNxpSubCommands[i].mCommand(aContext, aArgsLength - 1, &aArgs[1]);
            break;
        }
    }

    if (error == OT_ERROR_INVALID_COMMAND) {
        otCliOutputFormat("Unknown subcommand: %s\r\n", aArgs[0]);
    }

    return error;
}

// ============================================================================
// Top-level commands
// ============================================================================

static otError cmd_seteui64(void *aContext, uint8_t aArgsLength, char *aArgs[])
{
    OT_UNUSED_VARIABLE(aContext);

    if (aArgsLength < 1) {
        otCliOutputFormat("Usage: seteui64 <eui64_hex>\r\n");
        otCliOutputFormat("Example: seteui64 0x0011223344556677\r\n");
        return OT_ERROR_INVALID_ARGS;
    }

    ot::Nxp::NxpVendorCommands *nxpCmd = GetNxpCommands();
    if (nxpCmd == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    return nxpCmd->ProcessSetEui64(aArgs[0]);
}

static otError cmd_txpwrlimit(void *aContext, uint8_t aArgsLength, char *aArgs[])
{
    OT_UNUSED_VARIABLE(aContext);

    ot::Nxp::NxpVendorCommands *nxpCmd = GetNxpCommands();
    if (nxpCmd == nullptr) {
        return OT_ERROR_INVALID_STATE;
    }

    return nxpCmd->ProcessTxPowerLimit(aArgsLength, aArgs);
}

// ============================================================================
// Top-level command table
// ============================================================================

static const otCliCommand kNxpCommands[] = {
    {"radio_nxp", cmd_radio_nxp},
    {"seteui64", cmd_seteui64},
    {"txpwrlimit", cmd_txpwrlimit},
};

// ============================================================================
// Initialization
// ============================================================================

extern "C" void nxp_vendor_cli_init(otInstance *aInstance)
{
    LOG_INF("Registering NXP vendor CLI commands");

    // Initialize NxpVendorCommands singleton
    (void)nxp_vendor_commands_get_instance(aInstance);

    otError error = otCliSetUserCommands(kNxpCommands,
                                          OT_ARRAY_LENGTH(kNxpCommands),
                                          aInstance);

    if (error == OT_ERROR_NONE) {
        LOG_INF("NXP Vendor Openthread CLI commands registered");
        LOG_INF("   - radio_nxp (with 6 subcommands)");
        LOG_INF("   - seteui64");
        LOG_INF("   - txpwrlimit");
    } else {
        LOG_ERR("Failed to register: %d", error);
    }
}

// ============================================================================
// Automatic initialization at boot using SYS_INIT
// ============================================================================

static int nxp_vendor_cli_sys_init(void)
{
    LOG_INF("NXP vendor CLI auto-initialization");

    // Wait a bit for OpenThread to initialize
    k_sleep(K_MSEC(100));

    otInstance *instance = openthread_get_default_instance();

    if (instance != NULL) {
        nxp_vendor_cli_init(instance);
        LOG_INF("NXP vendor commands auto-initialized successfully");
        return 0;
    } else {
        LOG_WRN("OpenThread instance not ready, will retry later");
        return -EAGAIN;
    }
}
// Initialize at APPLICATION level, after OpenThread initialization
SYS_INIT(nxp_vendor_cli_sys_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
