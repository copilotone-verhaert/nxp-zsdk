[Index page](../wireless-release-notes.md)

# IW416 release notes
## Package information

SDK version: v4.1.0
## Version information

Wireless SoC: IW416

Wi-Fi and Bluetooth/Bluetooth LE firmware version: 16.91.21.p142.5

-   16 - Major revision
-   91 - Feature pack
-   21 - Release version
-   p142.5- Patch number

## Host platform

i.MX RT1060 EVKC platform running Zephyr RTOS.

Host interfaces

-   Wi-Fi over SDIO \(SDIO 2.0 Support, SDIO clock frequency: 50 MHz\)
-   Bluetooth/Bluetooth LE over UART

Test tools

-   zperf
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
|Open Security|28|22|58|56|
|WPA2-AES|29|29|51|52|
|WPA3-SAE|29|30|51|55|


STA mode throughput - BGN Mode - 2.4 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|38|41|78|69|
|WPA2-AES|36|38|77|61|
|WPA3-SAE|36|38|81|64|

STA mode throughput - AN Mode - 5 GHz Band - 20 MHz ( HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|32|34|61|65|
|WPA2-AES|31|34|61|64|
|WPA3-SAE|31|34|61|64|

STA mode throughput - AN Mode - 5 GHz Band - 40 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|38|41|78|69|
|WPA2-AES|38|41|77|65|
|WPA3-SAE|38|40|83|67|

### Mobile AP throughput

External client: PCIE 88W9098

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|30|35|58|59|
|WPA2-AES|30|36|59|61|
|WPA3-SAE|30|35|57|59|

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|37|40|72|67|
|WPA2-AES|36|36|73|60|
|WPA3-SAE|34|38|80|61|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|31|22|38|37|
|WPA2-AES|29|23|38|36|
|WPA3-SAE|30|23|38|37|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|35|28|79|73|
|WPA2-AES|31|28|79|72|
|WPA3-SAE|32|27|79|71|

## EU conformance tests
EU Adaptivity test - EN 300 328 v2.1.1 \(for 2.4 GHz\)

EU Adaptivity test - EN 301 893 v2.1.1 \(for 5 GHz\)


## Known issues

|Component|Description|
|---------|-----------|
|Wi-Fi|-   The channel list for JP region does not support CH149 nor CH165 but the STAUT switches to those channel along with the uAP.|

