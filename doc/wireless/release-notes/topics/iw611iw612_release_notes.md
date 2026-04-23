[Index page](../wireless-release-notes.md)

# IW611/IW612 release notes

## Package information

SDK version: v4.4.0

## Version information

Wireless SoC: IW611/IW612

Wi-Fi and Bluetooth/Bluetooth LE firmware version: 18.99.8.p25

-   18 - Major revision
-   99 - Feature pack
-   8 - Release version
-   p25 - Patch number

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

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|35|45|61|63|
|WPA2-AES|35|44|61|61|
|WPA3-SAE|35|44|61|62|

STA mode throughput - BGN Mode - 2.4 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|38|56|79|102|
|WPA2-AES|37|55|80|102|
|WPA3-SAE|37|52|78|104|

STA mode throughput - AN Mode - 5 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|37|47|63|65|
|WPA2-AES|37|46|63|64|
|WPA3-SAE|37|46|63|64|

STA mode throughput - AN Mode - 5 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|36|58|78|105|
|WPA2-AES|36|57|79|99|
|WPA3-SAE|37|58|79|102|

STA mode throughput - VHT Mode - 2.4 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|37|41|76|77|
|WPA2-AES|37|40|76|76|
|WPA3-SAE|37|40|76|76|

STA mode throughput - VHT Mode - 2.4 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|49|47|89|105|
|WPA2-AES|49|47|89|104|
|WPA3-SAE|48|46|87|104|

STA mode throughput - VHT Mode - 5 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|38|51|76|77|
|WPA2-AES|37|50|76|76|
|WPA3-SAE|37|50|76|37|

STA mode throughput - VHT Mode - 5 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|36|58|78|98|
|WPA2-AES|36|56|78|103|
|WPA3-SAE|36|54|79|98|

STA mode throughput - VHT Mode - 5 GHz Band - 80 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|35|58|79|103|
|WPA2-AES|35|60|81|103|
|WPA3-SAE|36|58|79|103|

STA mode throughput - HE Mode - 2.4 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|36|51|79|88|
|WPA2-AES|36|51|79|94|
|WPA3-SAE|36|51|95|95|

STA mode throughput - HE Mode - 2.4 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|37|54|79|103|
|WPA2-AES|36|54|79|100|
|WPA3-SAE|36|54|79|100|

STA mode throughput - HE Mode - 5 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|37|56|80|98|
|WPA2-AES|37|57|80|103|
|WPA3-SAE|37|57|80|102|

STA mode throughput - HE Mode - 5 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|36|57|79|101|
|WPA2-AES|36|55|79|102|
|WPA3-SAE|36|57|80|101|

STA mode throughput - HE Mode - 5 GHz Band - 80 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|36|59|79|95|
|WPA2-AES|36|59|80|101|
|WPA3-SAE|35|58|79|101|

### Mobile AP throughput

External client: Apple MacBook Air

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|-------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|33|38|59|63|
|WPA2-AES|33|39|58|63|
|WPA3-SAE|33|38|59|62|

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|38|47|72|68|
|WPA2-AES|38|43|71|67|
|WPA3-SAE|38|42|71|70|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|33|39|59|63|
|WPA2-AES|33|38|58|63|
|WPA3-SAE|33|37|59|62|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|38|48|78|72|
|WPA2-AES|38|46|77|73|
|WPA3-SAE|38|49|77|74|

Mobile AP Mode Throughput - VHT Mode - 2.4 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|40|45|62|59|
|WPA2-AES|39|40|60|54|
|WPA3-SAE|39|45|60|62|

Mobile AP Mode Throughput - VHT Mode - 2.4 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|43|46|91|91|
|WPA2-AES|42|44|92|92|
|WPA3-SAE|40|46|92|93|

Mobile AP Mode Throughput - VHT Mode - 5 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|36|42|76|77|
|WPA2-AES|36|42|76|77|
|WPA3-SAE|36|42|76|77|

Mobile AP Mode Throughput - VHT Mode - 5 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|42|50|75|74|
|WPA2-AES|43|48|72|73|
|WPA3-SAE|42|51|73|71|

Mobile AP Mode Throughput - VHT Mode - 5 GHz Band - 80 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|43|51|72|74|
|WPA2-AES|41|52|71|75|
|WPA3-SAE|42|52|73|72|

Mobile AP Mode Throughput - HE Mode - 2.4 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|45|42|79|80|
|WPA2-AES|44|38|79|79|
|WPA3-SAE|45|44|79|78|

Mobile AP Mode Throughput - HE Mode - 2.4 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|45|49|79|79|
|WPA2-AES|45|45|79|82|
|WPA3-SAE|46|43|80|83|

Mobile AP Mode Throughput - HE Mode - 5 GHz Band - 20 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|46|53|79|72|
|WPA2-AES|45|52|79|71|
|WPA3-SAE|46|51|79|73|

Mobile AP Mode Throughput - HE Mode - 5 GHz Band - 40 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|47|45|81|78|
|WPA2-AES|46|47|79|83|
|WPA3-SAE|46|46|79|78|

Mobile AP Mode Throughput - HE Mode - 5 GHz Band - 80 MHz

| Protocol      | TCP (Mbit/s) | TCP (Mbit/s) | UDP (Mbit/s) | UDP (Mbit/s) |
|:--------------|:-------------:|:-------------:|:-------------:|:-------------:|
|Direction|TX|RX|TX|RX|
|Open Security|46|51|79|82|
|WPA2-AES|46|51|79|78|
|WPA3-SAE|47|52|82|72|


## EU conformance tests
EU Adaptivity test - EN 300 328 v2.1.1 \(for 2.4 GHz\)

EU Adaptivity test - EN 301 893 v2.1.1 \(for 5 GHz\)

## Bug fixes and/or feature enhancements

### Firmware version: From 18.99.3.p21.154 to 18.99.3.p25.11

|Component|Description|
|---------|-----------|
|-|-|

### Firmware version: From 18.99.3.p25.11 to 18.99.3.p26.7

|Component|Description|
|---------|-----------|
|-|-|

### Firmware version: From 18.99.3.p26.7 to 18.99.8.p7
|Component|Description|
|---------|-----------|
|Wi-Fi|Invoking csi-param-header sta 2 results in an RX ring buffer overflow, preventing termination of the CSI dump|

### Firmware version: From 18.99.8.p7 to 18.99.8.p25
|Component|Description|
|---------|-----------|
|Wi-Fi|<ul><li>The device under test (DUT), when enrolled as a STA, could enter a hang state during DPP initiator authentication with the AP due to a command response timeout (command 0x00, length 70, sequence number 0x16</ul></li><ul><li>The DUT could enter a hang state during STA connection when configured with Suite‑B EC / WPA3‑Enterprise (ECC, EAP‑TLS) security, due to a command response timeout (0x240)</ul></li><ul><li>The DUT could encounter an assertion failure leading to a kernel panic intermittently during long‑duration performance testing in uAP mode.</ul></li><ul><li>Enabled MbedTLS 4.x</ul></li>|

## Known issues

|Component|Description|
|---------|-----------|
|-|-|


