[Index page](../wireless-release-notes.md)

# Bluetooth radio features

## Bluetooth classic

|Features|IW416|IW611/IW612|RW610/RW612|
|--------|-----|-----------|-----------|
|**General features**||||
|Bluetooth Class 1.5 and Class 2 support|N|N|N|
|Scatternet support|N|N|N|
|Maximum of seven simultaneous ACL connections|N|N|N|
|Automatic packet type selection|N|N|N|
|Bluetooth - 2.1 to 5.0 specification support|N|N|N|
|Low power sniff|N|N|N|
|Deep sleep using out-of-band|N|N|N|
|Wake on Bluetooth \(SoC to host\)|N|N|N|
|Independent reset \(in-band\)<sup>1</sup>|N|N|N|
|Independent reset \(out-band\)<sup>1</sup>|N|N|N|
|Firmware download \(parallel\)<sup>1</sup>|N|N|N|
|RF test mode|N|N|N|
|Auto PTS|Y|N|N|
|**Bluetooth packet type supported**||||
|ACL \(DM1, DH1, DM3, DH3, DM5, DH5, 2-DH1, 2-DH3, 2-DH5, 3-DH1, 3-DH3, 3- DH5\)|N|N|N|
|SCO \(HV1, HV3\)|N|N|N|
|eSCO \(EV3, EV4, EV5, 2EV3, 3EV3, 2EV5, 3EV5\)|N|N|N|
|**Bluetooth profiles supported**||||
|A2DP source/sink|N|N|N|
|AVRCP target/controller|N|N|N|
|HFP Dev/AG|N|N|N|
|OPP server/client|N|N|N|
|SPP server/client|N|N|N|
|HID target/device|N|N|N|
|PCM NBS central/peripheral|N|N|N|
|PCM WBS central/peripheral|N|N|N|

[1] Experimental feature intended for evaluation/early development only and not production. Incomplete mandatory certification.

## Bluetooth LE

|Features|IW416|IW611/IW612|RW610/RW612|IW610|
|--------|-----|-----------|-----------|-----|
|**Generic features**||||
|Maximum 16 Bluetooth LE connections \(central role\)|Y|Y|Y|Y|
|1Mbps Support|Y|Y|Y|Y|
|Deep sleep using out-of-band|N|N|N|N|
|Wake on Bluetooth LE \(SoC to Host\)|N|N|N|N|
|Filter Accept List|N|N|Y|Y|
|RF Test mode|Y| Y|Y|Y|
|Auto PTS|Y|N|N|
|**Bluetooth profile support**||||
|Bluetooth LE GATT|Y|Y|Y|Y|
|Bluetooth LE HID over GATT|N|Y|Y|Y|
|Bluetooth LE GAP|Y|Y|Y|Y|
|HRM \(Heart Rate Monitor Service\)|Y|Y|Y|Y|
|BT Home sensor template|Y|Y|Y|Y|
|Eddystone|Y|Y|Y|Y|
|iBeacon|Y|Y|Y|Y|
|CSC service \(Cycling Speed and Cadence\)|Y|Y|Y|Y|
|ESP \(Environmental Sensing Profile\)|Y|Y|Y|Y|
|NUS \(Nordic UART service\)|Y|Y|Y|Y|
|HTS \(Health Thermometer Service\)|Y|Y|Y|Y|
|DIS \(Device Information Service\)|Y|Y|Y|Y|
|OTS \(Object Transfer Service\)|Y|Y|Y|Y|
|**Bluetooth 4.0 support**||||
|Low Energy physical layer|Y|Y|Y|Y|
|Low Energy link layer|Y|Y|Y|Y|
|Enhancements to HCI for Low Energy|Y|Y|Y|Y|
|Low energy direct test mode|Y|Y|Y|Y|
|**Bluetooth 4.1 support**||||
|Low duty cycle directed advertising|Y|Y|Y|Y|
|Bluetooth LE dual mode topology|Y|Y|Y|Y|
|Bluetooth LE privacy v1.1|Y|Y|Y|Y|
|Bluetooth LE link layer topology|Y|Y|Y|Y|
|**Bluetooth 4.2 support**||||
|Bluetooth LE secure connection|N|N|N|N|
|Bluetooth LE link layer privacy v1.2|Y|Y|Y|Y|
|Bluetooth LE data length extension|Y|Y|Y|Y|
|Link layer extended scanner filter policies|Y|Y|Y|Y|
|**Bluetooth 5.0 support**||||
|Bluetooth LE 2 Mbps support|Y|Y|Y|Y|
|High duty cycle directed advertising|Y|Y|Y|Y|
|Low Energy advertising extension|Y|Y|Y|Y|
|Low Energy long range|Y|Y|Y|Y|
|Low Energy periodic advertisement|Y|Y|Y|Y|
|**Bluetooth 5.1 support**||||
|Control Length Extension|N|N|N|N|
|**Bluetooth 5.2 support**||||
|Low Energy power control|N|N|N|N|

