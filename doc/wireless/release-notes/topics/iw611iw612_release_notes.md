[Index page](../wireless-release-notes.md)

# IW611/IW612 release notes

## Package information

SDK version: v4.1.0

## Version information

Wireless SoC: IW611/IW612

Wi-Fi and Bluetooth/Bluetooth LE firmware version: 18.99.3.p21.154

-   18 - Major revision
-   99 - Feature pack
-   3 - Release version
-   p21.154 - Patch number

## Host platform

i.MX RT1170 EVKB and i.MX RT1060 EVKC Platforms running Zephyr RTOS

Host interfaces

-   Wi-Fi over SDIO \(SDIO 2.0 support, SDIO clock frequency: 50 MHz\)
-   Bluetooth/Bluetooth LE over UART
-   802.15.4 over SPI \(IW612 only\)

Test tools

-   zperf

## Wi-Fi throughput

### Wi-Fi throughput test setup

-   Environment: Shield Room - Over the Air
-   Access Point: Asus AX88u
-   DUT: IW612 Murata \(Module: 2EL M.2\) with EVK-MIMXRT1060 EVKC platform
-   DUT Power Source: External power supply
-   Client: SDIO IW612
-   Channel: 6 \| 36
-   Wi-Fi application: wifi\_wpa\_supplicant
-   Compiler used to build application: armgcc
-   Compiler Version gcc-arm-none-eabi-13.2
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


The throughput numbers are captured with default configurations using *wifi\_wpa\_supplicant*sample application.

### STA throughput

External AP: Asus AX88u

STA mode throughput - BGN Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|33|38|59|63|
|WPA2-AES|33|37|58|63|
|WPA3-SAE|33|37|59|62|

STA mode throughput - BGN Mode - 2.4 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|38|46|88|92|
|WPA2-AES|38|46|87|92|
|WPA3-SAE|38|46|91|94|

STA mode throughput - AN Mode - 5 GHz Band - 20 MHz ( HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|33|38|59|63|
|WPA2-AES|33|37|58|63|
|WPA3-SAE|33|37|59|62|


STA mode throughput - AN Mode - 5 GHz Band - 40 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|38|46|88|92|
|WPA2-AES|38|46|87|92|
|WPA3-SAE|38|46|87|94|

STA mode throughput - VHT Mode - 2.4 GHz Band - 20 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|34|40|74|75|
|WPA2-AES|34|39|74|73|
|WPA3-SAE|34|39|73|74|

STA mode throughput - VHT Mode - 2.4 GHz Band - 40 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|41|47|92|93|
|WPA2-AES|39|46|91|93|
|WPA3-SAE|40|46|92|93|

STA mode throughput - VHT Mode - 5 GHz Band - 20 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|35|40|75|76|
|WPA2-AES|35|39|74|74|
|WPA3-SAE|35|40|74|75|

STA mode throughput - VHT Mode - 5 GHz Band - 40 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|42|48|92|92|
|WPA2-AES|43|47|92|94|
|WPA3-SAE|42|46|92|92|

STA mode throughput - VHT Mode - 5 GHz Band - 80 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|42|49|92|93|
|WPA2-AES|41|49|92|92|
|WPA3-SAE|42|49|92|94|

STA mode throughput - HE Mode - 2.4 GHz Band - 20 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|36|42|87|90|
|WPA2-AES|35|42|87|91|
|WPA3-SAE|35|41|86|90|

STA mode throughput - HE Mode - 2.4 GHz Band - 40 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|41|45|90|91|
|WPA2-AES|41|45|89|90|
|WPA3-SAE|40|44|89|91|

STA mode throughput - HE Mode - 5 GHz Band - 20 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|40|44|90|89|
|WPA2-AES|39|42|89|89|
|WPA3-SAE|39|42|89|92|

STA mode throughput - HE Mode - 5 GHz Band - 40 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|43|45|92|94|
|WPA2-AES|42|46|92|94|
|WPA3-SAE|43|46|91|90|

STA mode throughput - HE Mode - 5 GHz Band - 80 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|43|49|93|92|
|WPA2-AES|43|48|92|92|
|WPA3-SAE|41|48|92|92|

### Mobile AP throughput

External client: Apple MacBook Air

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|-------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|33|38|59|63|
|WPA2-AES|33|37|58|63|
|WPA3-SAE|33|37|59|62|

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Direction|TX|RX|TX|RX|
|Open Security|38|46|88|92|
|WPA2-AES|38|46|87|92|
|WPA3-SAE|38|46|91|94|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|33|38|59|63|
|WPA2-AES|33|37|58|63|
|WPA3-SAE|33|37|59|62|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|38|46|88|92|
|WPA2-AES|38|46|87|92|
|WPA3-SAE|38|46|87|94|

Mobile AP Mode Throughput - VHT Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|34|40|74|75|
|WPA2-AES|34|39|74|73|
|WPA3-SAE|34|39|73|74|

Mobile AP Mode Throughput - VHT Mode - 2.4 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|41|47|92|93|
|WPA2-AES|39|46|91|93|
|WPA3-SAE|40|46|92|93|

Mobile AP Mode Throughput - VHT Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|35|40|75|76|
|WPA2-AES|35|39|74|74|
|WPA3-SAE|35|40|74|75|

Mobile AP Mode Throughput - VHT Mode - 5 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|42|48|92|92|
|WPA2-AES|43|47|92|94|
|WPA3-SAE|42|46|92|92|

Mobile AP Mode Throughput - VHT Mode - 5 GHz Band - 80 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|42|49|92|93|
|WPA2-AES|41|49|92|92|
|WPA3-SAE|42|49|92|94|

Mobile AP Mode Throughput - HE Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|36|42|87|90|
|WPA2-AES|35|42|87|91|
|WPA3-SAE|35|41|86|90|

Mobile AP Mode Throughput - HE Mode - 2.4 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|41|45|90|91|
|WPA2-AES|41|45|89|90|
|WPA3-SAE|40|44|89|91|

Mobile AP Mode Throughput - HE Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|40|44|90|89|
|WPA2-AES|39|42|89|89|
|WPA3-SAE|39|42|89|92|

Mobile AP Mode Throughput - HE Mode - 5 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|43|45|92|94|
|WPA2-AES|42|46|92|94|
|WPA3-SAE|43|46|91|90|

Mobile AP Mode Throughput - HE Mode - 5 GHz Band - 80 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|43|49|93|92|
|WPA2-AES|43|48|92|92|
|WPA3-SAE|41|48|92|92|


## EU conformance tests
EU Adaptivity test - EN 300 328 v2.1.1 \(for 2.4 GHz\)

EU Adaptivity test - EN 301 893 v2.1.1 \(for 5 GHz\)

## Known issues

|Component|Description|
|---------|-----------|
|ꟷ|ꟷ|


