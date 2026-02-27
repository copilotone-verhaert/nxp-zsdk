[Index page](../Wi-Fi_Bluetooth_and_Thread_User_Manual_for_Zephyr.md)

# MFG bridge example

The MFG bridge example servers as a bridge between Windows NXP Labtool application and Wi-Fi/Bluetooth LE/802.15.4 radios for wireless calibration and RF test.

- Receive the command from Labtool running on a Windows system over UART port
- Pass the command to Wi-Fi/Bluetooth LE/802.15.4 firmware to process
- Return the command response back to Labtool

The exchanged commands and responses are transparent to the MFG bridge application. MFG bridge application must work with wireless chip manufacturing firmware. The labtool release is available to download from the Software category in the wireless chip product webpage. It includes Labtool Windows application and the manufacturing firmware for Wi-Fi, Bluetooth LE and 802.15.4 separately.

## Build MFG bridge example

The following command is used to build MFG bridge example.

```bash
west build -b mimxrt1060_evk@C samples/nxp_mfg_bridge -d [build_folder] --pristine -DEXTRA_CONF_FILE="[conf file]" --shield [shield name]
```

| Wireless chip |       Conf files       |    Shield name    |
| :-----------: | :--------------------: | :----------------: |
|     IW416     | nxp/overlay_IW416.conf | nxp_m2_1xk_wifi_bt |
|     IW612     | nxp/overlay_IW612.conf | nxp_m2_2el_wifi_bt |
|     IW610     | nxp/overlay_iw610.conf | nxp_m2_2ll_wifi_bt |

Before building the example, it is required to replace the default production firmware with MFG firmware from the Labtool release package.

| Wireless chip |      Firmware folder      |                  Shield name                  |
| :-----------: | :------------------------: | :-------------------------------------------: |
|     IW416     | hal/nxp/zephyr/blobs/IW416 | sdIW416_wlan.bin<br />sduartIW416_wlan_bt.bin |
|     IW612     | hal/nxp/zephyr/blobs/nw61x |   sd_nw61x.bin.se<br />sduart_nw61x.bin.se   |
|     IW610     | hal/nxp/zephyr/blobs/IW610 |   sd_iw610.bin.se<br />sduart_iw610.bin.se   |

## Run MFG bridge example

This example runs automatically in bridge mode and does not require any user interaction.

> **Note:** The UART port is used as a communication port between NXP Labtool and MFG firmware. Therefore, no console logs exist for the nxp_mfg_bridge application.

Labtool is a user interactive command-line application running on Windows. Different options are defined to control wireless chip internal Wi-Fi/Bluetooth LE/802.15.4 radios to transmit and receive. Option 88 is used to read back the manufacturing firmware version.

```bash
Name:           Dut labtool

Version:        2.0.0.35

Date:           Mar 11 2025 (10:04:04)

Note:

1. =========WiFi tool=============

2. =========BT   tool=============

3. =========15_4   tool=============

4. =========WiFi tool offline ====

Enter CMD 99 to Exit

Enter option: 1

Name:           DutApiClass

Interface:      EtherNet

Version:        2.0.0.35

Date:           Mar 11 2025 (10:03:38)

Note:

C:\labtool\setup.ini

Dut's IP 192.168.1.8:9930

Host's IP 192.168.1.13:9931

DutIf_UdpIp::delay 0

DutIf_UdpIp::vg_IfSpy 0

DutIf_InitConnection: 0x00000000

--------------------------------------------------------

IW610 NightHawk (802.11a/g/b/n/ac/ax) TEST MENU

--------------------------------------------------------

Enter option: 88

DLL Version : 2.0.0.35

LabTool Version: 2.0.0.35

FW Version:  18.80.5.43 Mfg Version: 2.0.0.63

SFW Version:  0.0.0.00  SHAL Version: 0.0.0.0

Cal Data Version : 0

SOC OR Version: 1.7      Customer ID:   0

RF OR Version:  0.7      Customer ID:   0
```
