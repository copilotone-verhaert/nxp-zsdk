[Index page](../wireless-release-notes.md)

# IW416 release notes
## Package information

SDK version: v4.2.0
## Version information

Wireless SoC: IW416

Wi-Fi and Bluetooth/Bluetooth LE firmware version: 16.92.21.p151.6

-   16 - Major revision
-   92 - Feature pack
-   21 - Release version
-   p151.6- Patch number

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

QDID: refer to 4.

Note: This release supports STAUT only certifications.

### Bluetooth controller certification
QDID: refer to 2.

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

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|32|37|45|64|
|WPA2-AES|33|29|58|43|
|WPA3-SAE|32|32|57|62|


STA mode throughput - BGN Mode - 2.4 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|42|46|78|90|
|WPA2-AES|43|44|75|92|
|WPA3-SAE|43|43|76|91|

STA mode throughput - AN Mode - 5 GHz Band - 20 MHz ( HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|34|36|59|58|
|WPA2-AES|33|38|59|60|
|WPA3-SAE|33|36|59|60|

STA mode throughput - AN Mode - 5 GHz Band - 40 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|47|47|83|91|
|WPA2-AES|46|45|79|91|
|WPA3-SAE|45|45|78|92|

### Mobile AP throughput

External client: PCIE 88W9098

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|33|38|59|63|
|WPA2-AES|32|38|59|62|
|WPA3-SAE|31|38|57|62|

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|35|40|76|93|
|WPA2-AES|34|40|78|95|
|WPA3-SAE|31|38|76|94|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|31|36|53|61|
|WPA2-AES|30|36|52|57|
|WPA3-SAE|33|38|59|64|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|38|44|77|96|
|WPA2-AES|32|39|78|93|
|WPA3-SAE|37|43|74|95|

## EU conformance tests
EU Adaptivity test - EN 300 328 v2.1.1 \(for 2.4 GHz\)

EU Adaptivity test - EN 301 893 v2.1.1 \(for 5 GHz\)

## Bug fixes and/or feature enhancements

### Firmware version: From 16.91.21.p142.5 to 16.92.21.p151.6

|Component|Description|
|---------|-----------|
|Wi-Fi|-   The channel list for JP region does not support CH149 nor CH165 but the STAUT switches to those channel along with the uAP.|

## Known issues

|Component|Description|
|---------|-----------|
|-|-|

