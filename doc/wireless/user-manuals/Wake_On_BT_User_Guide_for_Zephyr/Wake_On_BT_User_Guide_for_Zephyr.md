# Wake-on-Bluetooth User Guide

## 0. Table of Contents
1. [Overview](#1-overview)
2. [Prerequisites](#2-prerequisites)
3. [Build Steps](#3-build-steps)
4. [Test Procedure](#4-test-procedure)
   - [4.1 Configure DUT and Start BLE Scanning](#41-configure-dut-and-start-ble-scanning)
   - [4.2 Configure REF and Start Directed Advertising](#42-configure-ref-and-start-directed-advertising)
5. [References](#5-references)

---

## 1. Overview

This guide describes how to validate the **Wake-on-Bluetooth** feature using NXP hosted wireless SoCs running on an **i.MX RT1060 EVKC** platform with **Zephyr**.

The feature is **disabled by default** and must be enabled using a dedicated `Kconfig` option. Optionally, the host platform LED0 can be enabled to visually indicate a wake-up event.

### Supported wireless SoCs
- **IW612**
- **IW610**
- **IW416**

### Wake-on-BT operation assumptions

- The host CPU is powered down, and the host stack is not running.
- The Wi-Fi/Bluetooth module is powered on, and the firmware is running.
- The host has a GPIO handler that monitors the GPIO interrupt by firmware.
- Upon a GPIO interrupt, the host is brought to a running state and the host stack is initialized.

### Example scenario
In a typical TV–remote-control scenario:
- The TV is in Standby mode but has Bluetooth LE scanning enabled.
- When the remote’s power button is pressed:
  - The remote sends **directed connectable Bluetooth LE advertising** contains TV’s MAC address.
  - The TV’s wireless SoC firmware detects this advertising and asserts the wake-up GPIO.
  - The host received GPIO toggling to wake and initialize the system.

---

## 2. Prerequisites

- **i.MX RT1060 EVKC** as DUT host
- DUT Hosted SoC EVK: **IW612/IW416/IW610**
- Jumper **J111** must be connected

**Note:**
The REF device side's prerequisites can match those of the DUT, or it can be replaced with any other Bluetooth device that supports the Bluetooth LE directed advertising feature. Both DUT and REF devices must have public MAC addresses programmed in OTP.

### Topology diagram
Take example of both DUT and REF devices use i.MX RT1060 EVKC as host platform:
<img src=./images/01.png alt="图片描述" width="300" height="200">

---

## 3. Build steps

### Build command of Bluetooth shell example for IW612/IW610/IW416

#### IW612
```bash
west build -p always -b mimxrt1060_evk@C/mimxrt1062/qspi -d shell_woble --shield nxp_m2_2el_wifi_bt .\tests\bluetooth\shell\ -DCONFIG_BT_NXP_CTRL_WAKE_ON_BT=y -DCONFIG_BT_NXP_CTRL_WAKE_ON_BT_LED_BLINK=y
```

#### IW610
```bash
west build -p always -b mimxrt1060_evk@C/mimxrt1062/qspi -d shell_woble --shield nxp_m2_2ll_wifi_bt .\tests\bluetooth\shell\ -DCONFIG_BT_NXP_CTRL_WAKE_ON_BT=y -DCONFIG_BT_NXP_CTRL_WAKE_ON_BT_LED_BLINK=y
```

#### IW416
```bash
west build -p always -b mimxrt1060_evk@C/mimxrt1062/qspi -d shell_woble --shield nxp_m2_1xk_wifi_bt .\tests\bluetooth\shell\ -DCONFIG_BT_NXP_CTRL_WAKE_ON_BT=y -DCONFIG_BT_NXP_CTRL_WAKE_ON_BT_LED_BLINK=y
```

**Note:**
If LED blink indication is not required, remove the `CONFIG_BT_NXP_CTRL_WAKE_ON_BT_LED_BLINK` option from the above command.

---

## 4. Test procedure

Flash the shell application to both DUT and REF devices.


## 4.1 Configure DUT and start Bluetooth LE scanning

### Step 1 — Reset DUT and configure filter accept list:

```bash
bt hci-cmd 0x03 0x03                     #Reset DUT
bt hci-cmd 0x03 0x0001 ffffffffffffffff  #Set event mask
bt hci-cmd 0x08 0x0001 ffffffffffffffff  #Set LE event mask
bt hci-cmd 0x08 0x0011 00<REF_MAC>       #Add Ref's MAC to DUT's filter accept list
```

### Step 2 — Configure wake-up GPIO for used SoCs

| SoC   | Wake GPIO Command |
|-------|--------------------|
| IW612 | `bt hci-cmd 0x3f 0x0053 031301FF` |
| IW610 | `bt hci-cmd 0x3f 0x0053 030501FF` |
| IW416 | `bt hci-cmd 0x3f 0x0053 030C01FF` |

### Step 3 — Enable Bluetooth LE scanning
```bash
bt hci-cmd 0x08 0x000B 01040004000001  # Set scan parameters
bt hci-cmd 0x08 0x000C 0100            # Enable scanning
```


## 4.2 Configure REF and start directed advertising

```bash
bt hci-cmd 0x03 0x0003                              #Reset REF
bt hci-cmd 0x08 0x0006 00020002040000<DUT_MAC>0703  #Set direct adv parameters
bt hci-cmd 0x08 0x0008 1F00998877665544332211009988776655443322110099887766554433221100  #set scan response data
bt hci-cmd 0x08 0x000A 01                           #Enable direct adv
```

### Expected result

- DUT receives REF’s directed connectable advertising packet.
- Firmware asserts the configured wake-up GPIO line.
- Host wakes up and initializes the BT stack.
- If the LED‑blink function is enabled, **LED0 blinks** to indicate a successful wake event, as shown in the picture below:

<img src=./images/02.png alt="图片描述" width="300" height="200">

## 5. References

- NXP Linux Host Wake-up Implementation using Bluetooth or Bluetooth Low Energy (LE) Application Note: [AN12849](https://www.nxp.com/docs/en/application-note/AN12849.pdf)
