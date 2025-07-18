[Index page](../wireless-release-notes.md)

# IW610 release notes

## Package information
SDK version: v4.2.0

## Version information

Wi-Fi and Bluetooth/Bluetooth LE firmware version firmware version: 18.99.5.p71

-   18 - Major revision
-   99 - Feature pack
-   5 - Release version
-   p71 - Patch number

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
|Open Security|40|47|59|64|
|WPA2-AES|40|46|62|63|
|WPA3-SAE|40|46|60|63|

STA mode throughput - AN Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|41|48|57|63|
|WPA2-AES|40|44|59|62|
|WPA3-SAE|41|46|59|61|

STA mode throughput - VHT Mode - 2.4 GHz Band - 20 MHz (HT)

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|43|50|74|74|
|WPA2-AES|43|50|71|73|
|WPA3-SAE|42|51|72|73|

STA mode throughput - VHT Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|45|51|76|78|
|WPA2-AES|45|52|74|77|
|WPA3-SAE|45|51|74|77|

STA mode throughput - HE Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|47|55|96|100|
|WPA2-AES|48|54|94|98|
|WPA3-SAE|48|54|94|99|

STA mode throughput - HE Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|50|57|101|103|
|WPA2-AES|50|56|99|102|
|WPA3-SAE|50|55|99|102|

### Mobile AP throughput

External client: PCIE 9098

Mobile AP Mode Throughput - BGN Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|45|48|62|62|
|WPA2-AES|44|48|60|62|
|WPA3-SAE|44|47|59|62|

Mobile AP Mode Throughput - AN Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|47|51|62|63|
|WPA2-AES|46|51|61|62|
|WPA3-SAE|46|51|61|63|

Mobile AP Mode Throughput - VHT Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|47|51|68|72|
|WPA2-AES|47|52|68|71|
|WPA3-SAE|47|51|69|71|

Mobile AP Mode Throughput - VHT Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|52|55|75|74|
|WPA2-AES|51|54|72|73|
|WPA3-SAE|51|53|72|73|

Mobile AP Mode Throughput - HE Mode - 2.4 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|54|57|95|99|
|WPA2-AES|54|56|96|98|
|WPA3-SAE|53|56|93|97|

Mobile AP Mode Throughput - HE Mode - 5 GHz Band - 20 MHz

|Protocol|TCP \(Mbit/s\)|  | UDP \(Mbit/s\)|  |
|--------|--------------|--|---------------|--|
|Direction|TX|RX|TX|RX|
|Open Security|55|53|100|96|
|WPA2-AES|56|52|98|96|
|WPA3-SAE|56|52|98|96|

## Known issues

|Component|Description|
|---------|-----------|
|—|—|


