[Index page](../wireless-release-notes.md)

# IW611/IW612 release notes

## Package information

SDK version: v4.2.0

## Version information

Wireless SoC: IW611/IW612

Wi-Fi and Bluetooth/Bluetooth LE firmware version: 18.99.3.p25.11

-   18 - Major revision
-   99 - Feature pack
-   3 - Release version
-   p25.11 - Patch number

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
|Open Security|39|39|74|76|
|WPA2-AES|37|35|74|75|
|WPA3-SAE|38|35|74|75|

STA mode throughput - BGN Mode - 2.4 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|48|44|90|103|
|WPA2-AES|47|44|85|102|
|WPA3-SAE|49|44|89|102|

STA mode throughput - AN Mode - 5 GHz Band - 20 MHz ( HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|39|39|76|77|
|WPA2-AES|37|40|76|76|
|WPA3-SAE|39|40|76|76|


STA mode throughput - AN Mode - 5 GHz Band - 40 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|48|47|90|104|
|WPA2-AES|48|47|88|103|
|WPA3-SAE|48|46|89|106|

STA mode throughput - VHT Mode - 2.4 GHz Band - 20 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|37|41|76|77|
|WPA2-AES|37|40|76|76|
|WPA3-SAE|37|40|76|76|

STA mode throughput - VHT Mode - 2.4 GHz Band - 40 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|49|47|89|105|
|WPA2-AES|49|47|89|104|
|WPA3-SAE|48|46|87|104|

STA mode throughput - VHT Mode - 5 GHz Band - 20 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|37|41|76|77|
|WPA2-AES|37|40|76|76|
|WPA3-SAE|37|40|76|76|

STA mode throughput - VHT Mode - 5 GHz Band - 40 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|49|47|89|105|
|WPA2-AES|49|47|89|104|
|WPA3-SAE|48|46|87|104|

STA mode throughput - VHT Mode - 5 GHz Band - 80 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|52|46|91|103|
|WPA2-AES|51|46|90|104|
|WPA3-SAE|51|46|91|103|

STA mode throughput - HE Mode - 2.4 GHz Band - 20 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|43|43|88|102|
|WPA2-AES|42|40|88|96|
|WPA3-SAE|42|37|86|96|

STA mode throughput - HE Mode - 2.4 GHz Band - 40 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|49|44|90|101|
|WPA2-AES|49|43|89|102|
|WPA3-SAE|49|43|88|102|

STA mode throughput - HE Mode - 5 GHz Band - 20 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|45|43|89|104|
|WPA2-AES|42|43|89|103|
|WPA3-SAE|42|44|90|103|

STA mode throughput - HE Mode - 5 GHz Band - 40 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|49|45|90|104|
|WPA2-AES|50|45|89|104|
|WPA3-SAE|49|45|91|101|

STA mode throughput - HE Mode - 5 GHz Band - 80 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|51|47|88|101|
|WPA2-AES|51|45|91|101|
|WPA3-SAE|50|46|91|100|

### Mobile AP throughput

External client: Apple MacBook Air

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|-------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|32|35|59|57|
|WPA2-AES|32|36|59|57|
|WPA3-SAE|33|35|58|58|

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|38|45|87|87|
|WPA2-AES|38|46|87|90|
|WPA3-SAE|38|46|87|88|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|34|40|63|63|
|WPA2-AES|35|39|63|63|
|WPA3-SAE|33|37|59|62|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|42|49|89|104|
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
|Open Security|43|46|91|91|
|WPA2-AES|42|44|92|92|
|WPA3-SAE|40|46|92|93|

Mobile AP Mode Throughput - VHT Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|36|42|76|77|
|WPA2-AES|36|42|76|77|
|WPA3-SAE|36|42|76|77|

Mobile AP Mode Throughput - VHT Mode - 5 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|44|48|91|102|
|WPA2-AES|44|48|90|102|
|WPA3-SAE|44|48|91|101|

Mobile AP Mode Throughput - VHT Mode - 5 GHz Band - 80 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|47|49|91|103|
|WPA2-AES|47|50|91|103|
|WPA3-SAE|47|51|90|103|

Mobile AP Mode Throughput - HE Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|41|46|84|103|
|WPA2-AES|37|38|83|83|
|WPA3-SAE|35|41|86|90|

Mobile AP Mode Throughput - HE Mode - 2.4 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|42|49|89|104|
|WPA2-AES|43|47|91|104|
|WPA3-SAE|43|48|91|104|

Mobile AP Mode Throughput - HE Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|41|44|81|104|
|WPA2-AES|40|45|81|104|
|WPA3-SAE|40|43|80|104|

Mobile AP Mode Throughput - HE Mode - 5 GHz Band - 40 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|---------|-------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|43|45|90|104|
|WPA2-AES|42|46|89|105|
|WPA3-SAE|43|46|97|102|

Mobile AP Mode Throughput - HE Mode - 5 GHz Band - 80 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|43|47|91|105|
|WPA2-AES|42|48|91|103|
|WPA3-SAE|41|48|91|99|


## EU conformance tests
EU Adaptivity test - EN 300 328 v2.1.1 \(for 2.4 GHz\)

EU Adaptivity test - EN 301 893 v2.1.1 \(for 5 GHz\)

## Bug fixes and/or feature enhancements

### Firmware version: From 18.99.3.p21.154 to 18.99.3.p25.11

|Component|Description|
|---------|-----------|
|-|-|

## Known issues

|Component|Description|
|---------|-----------|
|ꟷ|ꟷ|


