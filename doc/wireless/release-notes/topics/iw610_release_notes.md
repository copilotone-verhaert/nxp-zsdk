[Index page](../wireless-release-notes.md)

# IW610 release notes

## Package information
SDK version: v4.3.0

## Version information

Wi-Fi and Bluetooth/Bluetooth LE firmware version firmware version: 18.99.5.p85

-   18 - Major revision
-   99 - Feature pack
-   5 - Release version
-   p85 - Patch number

## Host platform

i.MX RT1170 EVKB and i.MX RT1060 EVKC Platforms running Zephyr RTOS

Test tools

-   zperf

## Wi-Fi throughput
### Throughput test setup

-   Environment: Shield room - Over the Air
-   Access Point: Asus AX88u
-   DUT: IW610
-   External Client: PCIE 9098
-   Channel: 6 \| 36
-   Wi-Fi application: wifi\_cli
-   Compiler used to build application: armgcc
-   Compiler version gcc-arm-none-eabi-13.2
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
    UDP RX

    ```
    zperf udp download 5001
    ```

**Note:** The default rate is 100 Mbps.
### STA throughput

External AP: Asus AX88u

STA mode throughput - BGN Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|40|45|62|59|
|WPA2-AES|39|40|60|54|
|WPA3-SAE|39|45|60|62|

STA mode throughput - AN Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|41|45|64|63|
|WPA2-AES|40|42|62|58|
|WPA3-SAE|40|46|61|62|

STA mode throughput - VHT Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|43|48|73|73|
|WPA2-AES|42|47|73|73|
|WPA3-SAE|42|47|73|73|

STA mode throughput - VHT Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|43|51|74|74|
|WPA2-AES|44|51|75|74|
|WPA3-SAE|44|53|75|74|

STA mode throughput - HE Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|46|56|94|97|
|WPA2-AES|46|55|94|97|
|WPA3-SAE|45|55|95|98|

STA mode throughput - HE Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|48|58|97|100|
|WPA2-AES|46|52|97|94|
|WPA3-SAE|47|54|98|97|

### Mobile AP throughput

External client: PCIE 9098

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|40|43|57|58|
|WPA2-AES|39|42|58|58|
|WPA3-SAE|40|42|58|57|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|40|43|60|60|
|WPA2-AES|40|42|61|60|
|WPA3-SAE|40|42|61|60|

Mobile AP Mode Throughput - VHT Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|44|48|75|71|
|WPA2-AES|42|48|68|70|
|WPA3-SAE|43|48|68|71|

Mobile AP Mode Throughput - VHT Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|46|48|70|71|
|WPA2-AES|46|48|70|71|
|WPA3-SAE|46|48|70|71|

Mobile AP Mode Throughput - HE Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|44|42|90|90|
|WPA2-AES|44|41|92|90|
|WPA3-SAE|44|41|92|90|

Mobile AP Mode Throughput - HE Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|47|45|97|97|
|WPA2-AES|46|44|98|97|
|WPA3-SAE|46|44|98|96|

## Bug fixes and/or feature enhancements

### Firmware version: From 18.99.5.p71 to 18.99.5.p85

|Component|Description|
|---------|-----------|
|Coex|<ul><li>In the coex_Central_HT sample application, the system intermittently halts at various threads during execution</ul></li> <ul><li> Resolved an issue where the system could randomly halt in different threads during "coex_central_ht" default SDK example execution.</ul></li> <ul><li>Resolved an issue related to the system halt occurring during BLE bonding in "coex_bt_shell" SDK example. </ul></li> <ul><li>Fixed command response timeout for CMD 0x107</ul></li>|

## Known issues

|Component|Description|
|---------|-----------|
|—|—|


