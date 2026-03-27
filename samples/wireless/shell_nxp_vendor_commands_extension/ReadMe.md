# NXP Vendor Commands Extension for OpenThread Shell

## Overview

This sample extends the OpenThread CLI shell with NXP-specific vendor commands for advanced radio control, manufacturing test modes, and hardware-specific features on NXP wireless SoCs (IW612, IW610, etc.).

The extension provides direct access to:
- Manufacturing (MFG) test commands
- CCA (Clear Channel Assessment) configuration
- Hardware encryption/decryption (BRIC)
- Independent reset control
- TX power limit configuration
- EUI64 programming
- Firmware version queries

## Architecture

### Component Structure

```
shell_nxp_vendor_commands_extension/
├── CMakeLists.txt
├── Kconfig
├── overlay_nxp_vendor.conf
├── radio_spinel.patch
├── ReadMe.md
├── src
│   ├── nxp_vendor_cli.cpp
│   ├── nxp_vendor_commands.cpp
│   ├── nxp_vendor_commands.hpp
│   ├── nxp_vendor_spinel.cpp
│   ├── nxp_vendor_spinel.h
│   └── nxp_vendor_types.h
└── zephyr
    └── module.yml
```

### Key Components

1. **zephyr/modules/openthread/platform/radio_spinel.cpp**
   - New API platformGetRadioSpinel to expose psRadioSpinel for external Zephyr module

2. **nxp_vendor_cli.cpp**
   - Registers OpenThread CLI commands using `otCliSetUserCommands()`
   - Auto-initializes via `SYS_INIT()` at boot
   - Dispatches commands to `NxpVendorCommands` class

3. **nxp_vendor_commands.cpp**
   - Implements high-level command logic
   - Parses arguments and validates input
   - Calls Spinel layer for RCP communication

4. **nxp_vendor_spinel.cpp**
   - Low-level Spinel protocol communication
   - Uses `RadioSpinel::Get()` and `RadioSpinel::Set()`
   - Handles data encoding/decoding

### Spinel Property Keys

Custom NXP vendor properties (defined in `nxp_vendor_types.h`):

```c
SPINEL_PROP_VENDOR_NXP_MFG_COMMAND      = 0x3C00
SPINEL_PROP_VENDOR_NXP_SET_EUI64        = 0x3C01
SPINEL_PROP_VENDOR_NXP_CCA_CONFIGURE    = 0x3C02
SPINEL_PROP_VENDOR_NXP_SET_TX_POWER_LIMIT = 0x3C03
...

```

## Building

### Zephyr environment setup
```bash
export ZEPHYR_FOLDER=~/zephyrproject/
export ZEPHYR_DOWNSTREAM=${ZEPHYR_FOLDER}/zephyr_downstream
export ZEPHYR_ZSDK=${ZEPHYR_DOWNSTREAM}/zsdk
export BOARD_NAME=frdm_rw612
export APP_NAME=shell

cd ${ZEPHYR_FOLDER}
python3 -m venv ${ZEPHYR_FOLDER}/.venv
source ${ZEPHYR_FOLDER}/.venv/bin/activate
pip install west
git config --global url.ssh://git@bitbucket.sw.nxp.com/mcucore/bifrost.git.insteadOf https://github.com/nxp-zephyr/bifrost
west init -m ssh://git@bitbucket.sw.nxp.com/mcucore/nxp-zsdk.git ${ZEPHYR_DOWNSTREAM}
cd ${ZEPHYR_DOWNSTREAM}
west update bifrost
python bifrost/scripts/init_env.py
west update
west zephyr-export
west packages pip --install
```

### Build Commands

```bash
cd ${ZEPHYR_DOWNSTREAM}
# clean build
west build -d build_${BOARD_NAME}_${APP_NAME}_nxp_extension -p -b ${BOARD_NAME} \
  zephyr/samples/net/openthread/${APP_NAME} \
  -- -DEXTRA_CONF_FILE="prj-ot-host.conf" \
     -DOVERLAY_CONFIG="${ZEPHYR_ZSDK}/samples/wireless/shell_nxp_vendor_commands_extension/overlay_nxp_vendor.conf" \
     -DEXTRA_ZEPHYR_MODULES="${ZEPHYR_ZSDK}/samples/wireless/shell_nxp_vendor_commands_extension"

# incremental build (e.g. after source code modification)
west build -d build_${BOARD_NAME}_${APP_NAME}_nxp_extension

# run menuconfig
west build -d build_${BOARD_NAME}_${APP_NAME}_nxp_extension -t menuconfig

# flash
west flash -d build_${BOARD_NAME}_${APP_NAME}_nxp_extension
```
## Features

### Automatic Initialization
Commands are automatically registered at boot using Zephyr's `SYS_INIT` mechanism - no manual initialization required.

### Available Commands

#### 1. `radio_nxp` - Main vendor command group

**Subcommands:**

- **`ircmd`** - Independent Reset Command
  ```bash
  ot radio_nxp ircmd
  ```
  Performs a hardware reset of the RCP (Radio Co-Processor).

- **`mfgcmd`** - Manufacturing Test Commands
  ```bash
  ot radio_nxp mfgcmd <cmd_id> [args...]
  ```

  Common MFG commands:
  ```bash
  # Enable MFG mode
  ot radio_nxp mfgcmd 1

  # Disable MFG mode
  ot radio_nxp mfgcmd 0

  # Set channel (e.g., channel 15)
  ot radio_nxp mfgcmd 12 15
  # Get channel
  ot radio_nxp mfgcmd 11

  # Set TX power (e.g., 10 dBm)
  ot radio_nxp mfgcmd 16 10
  # Get TX power
  ot radio_nxp mfgcmd 15

  # Start continuous TX
  ot radio_nxp mfgcmd 17 1

  # Start unmodulated CW TX
  ot radio_nxp mfgcmd 18 0

  # Start continuous RX
  ot radio_nxp mfgcmd 30 1

  # Get RX statistics
  ot radio_nxp mfgcmd 31

  # Continuous wave test
  ot radio_nxp mfgcmd 40 1

  # Get CCA status
  ot radio_nxp mfgcmd 50

  # Continuous ED (Energy Detection) test
  ot radio_nxp mfgcmd 55 1

  # Get ED value
  ot radio_nxp mfgcmd 56

  # PHY TX test PSDU (count, gap, ack)
  ot radio_nxp mfgcmd 57 100 10 1

  # PHY RX/TX ACK test
  ot radio_nxp mfgcmd 58 1

  # Set generic parameters (seq, pan, dst, src)
  ot radio_nxp mfgcmd 59 0x01 0x1234 0xFFFF 0x0001

  # Get/Set latency
  ot radio_nxp mfgcmd 60 0
  ot radio_nxp mfgcmd 60 1 <latency_us>

  # Crash simulation (for testing)
  ot radio_nxp mfgcmd 72

  # Generic MFG command (raw hex)
  ot radio_nxp mfgcmd 255 <hex_payload>
  ```

- **`ccacfg`** - CCA Configuration
  ```bash
  # Get current CCA configuration
  ot radio_nxp ccacfg

  # Set CCA configuration
  # mode: CCA mode (1=ED, 2=Carrier, 3=Both)
  # cca1: ED threshold (-100 to 0 dBm)
  # cca2corr: Correlation threshold (0-255)
  # cca2min: Min correlation count (0-255)
  ot radio_nxp ccacfg <mode> <cca1> <cca2corr> <cca2min>

  # Example: Set CCA mode 3, ED=-75dBm, corr=20, min=3
  ot radio_nxp ccacfg 3 -75 20 3
  ```

- **`fwversion`** - Get Firmware Version
  ```bash
  ot radio_nxp fwversion
  ```
  Displays the RCP firmware version string.

- **`encrypt`** - Hardware Encryption (BRIC)
  ```bash
  ot radio_nxp encrypt <key_hex> <nonce_hex> <plaintext_hex>

  # Example:
  ot radio_nxp encrypt 000102030405060708090a0b0c0d0e0f 000102030405060708090a0b0c 48656c6c6f20576f726c6421
  ```
  Returns ciphertext and authentication tag.

- **`decrypt`** - Hardware Decryption (BRIC)
  ```bash
  ot radio_nxp decrypt <key_hex> <nonce_hex> <ciphertext_hex> <tag_hex>

  # Example:
  ot radio_nxp decrypt 000102030405060708090a0b0c0d0e0f 000102030405060708090a0b0c 5e51d8e43c29aded28fb5786 53d2c4136b60b1c399d0
  ```
  Returns decrypted plaintext.

#### 2. `seteui64` - Set IEEE EUI-64 Address

```bash
# Set EUI64 with 0x prefix
ot seteui64 0x0011223344556677

# Set EUI64 without prefix
ot seteui64 0011223344556677
```

Permanently programs the device's IEEE 802.15.4 extended address.

#### 3. `txpwrlimit` - TX Power Limit Configuration

```bash
# Get current TX power limit
ot txpwrlimit

# Set TX power limit (in dBm)
ot txpwrlimit <power_dbm>

# Example: Set to 10 dBm
ot txpwrlimit 10
```

