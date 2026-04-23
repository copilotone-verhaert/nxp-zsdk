[Index page](../wireless-release-notes.md)

# IW416 release notes
## Package information

SDK version: v4.4.0
## Version information

Wireless SoC: IW416

Wi-Fi and Bluetooth/Bluetooth LE firmware version: 16.92.21.p159

-   16 - Major revision
-   92 - Feature pack
-   21 - Release version
-   p159- Patch number

## Host platform

i.MX RT1060 EVKC platform running Zephyr RTOS.

Host interfaces

-   Wi-Fi over SDIO \(SDIO 2.0 Support, SDIO clock frequency: 50 MHz\)
-   Bluetooth/Bluetooth LE over UART

Test tools

-   zperf

## Wi-Fi and Bluetooth certification
The Wi-Fi and Bluetooth certification is obtained with the following combinations.

### WFA certifications
-   STA | 802.11n
-   STA | PMF
-   STA | FFD
-   STA | SVD
-   STA | WPA3 SAE (R3)
-   STA | QTT

QDID: [3] (references.md).

Note: This release supports STAUT only certifications.

### Bluetooth controller certification
QDID: [2] (references.md).

Note: QDID upgrade to Bluetooth Core Specification Version 5.4 is in progress.

## Wi-Fi throughput
### Throughput test setup

-   Environment: Shield room - Over the Air
-   Access Point: Asus AX88u
-   DUT: IW416 Murata \(Module: 1XK M.2\) with EVK-MIMXRT1060 EVKC platform
-   DUT Power Source: External power supply
-   Client: PCIE 9098
-   Channel: 6 \| 36
-   Wi-Fi application: wifi\_wpa\_supplicant
-   Compiler used to build application: armgcc
-   Compiler Version: gcc-arm-none-eabi-13.2
-   zperf commands used:

    TCP TX

    ```
    zperf tcp upload  5001 10 1470 114M
    ```

    TCP RX

    ```
    zperf tcp download 5001
    ```

    UDP TX

    ```
    zperf udp upload -a  5001 10 1470 114M ml
    ```

    **Note:** The default rate is 100 Mbps.

    UDP RX

    ```
    zperf udp download 5001
    ```
### STA throughput

External AP: Asus AX88u

STA mode throughput - BGN Mode - 2.4 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|38|42|61|56|
|WPA2-AES|36|42|61|56|
|WPA3-SAE|36|43|61|61|

STA mode throughput - BGN Mode - 2.4 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|42|60|75|89|
|WPA2-AES|39|58|75|88|
|WPA3-SAE|40|59|75|88|

STA mode throughput - AN Mode - 5 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|40|46|61|65|
|WPA2-AES|41|46|61|64|
|WPA3-SAE|41|46|61|64|

STA mode throughput - AN Mode - 5 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|42|60|74|90|
|WPA2-AES|44|59|75|90|
|WPA3-SAE|43|59|75|90|

### Mobile AP throughput

External client: PCIE 88W9098

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|44|43|58|56|
|WPA2-AES|44|44|58|56|
|WPA3-SAE|36|38|61|61|

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|44|56|58|89|
|WPA2-AES|43|53|58|88|
|WPA3-SAE|40|59|75|88|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|47|48|61|64|
|WPA2-AES|46|47|61|62|
|WPA3-SAE|46|47|61|63|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|52|55|75|91|
|WPA2-AES|52|55|74|84|
|WPA3-SAE|43|59|75|90|

## EU conformance tests
EU Adaptivity test - EN 300 328 v2.1.1 \(for 2.4 GHz\)

EU Adaptivity test - EN 301 893 v2.1.1 \(for 5 GHz\)

## Bug fixes and/or feature enhancements

### Firmware version: From 16.91.21.p142.5 to 16.92.21.p151.6

|Component|Description|
|---------|-----------|
|Wi-Fi|-   The channel list for JP region does not support CH149 nor CH165 but the STAUT switches to those channel along with the uAP.|

### Firmware version: From 16.91.21.p151.6 to 16.92.21.p153.4

|Component|Description|
|---------|-----------|
|Wi-Fi|-A significant number of link-layer packets are being dropped during data transmission   |

### Firmware version: From 16.91.21.p153.4 to 16.92.21.p159

|Component|Description|
|---------|-----------|
|Wi-Fi|Enabled MbedTLS 4.x|

## Known issues

|Component|Description|
|---------|-----------|
|-|-|

