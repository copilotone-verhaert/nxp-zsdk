[Index page](../wireless-release-notes.md)

# Bluetooth radio features

## Bluetooth classic

|<div style="width:200px;">Features</div>|<div style="width:70px;">IW416</div>|<div style="width:70px;">IW611/<br>IW612</div>|<div style="width:70px;">RW610/<br>RW612</div>|
|:--------|:-----:|:-----------:|:-----------:|
|**General features**||||
|Bluetooth Class 1.5 and Class 2 support|N|N|N|
|Scatternet support|Y|Y|N|
|Maximum of seven simultaneous ACL connections|N|N|N|
|Automatic packet type selection|N|N|N|
|Bluetooth - 2.1 to 5.0 specification support|N|N|N|
|Low power sniff|N|N|N|
|Deep sleep using out-of-band|N|N|N|
|Wake on Bluetooth \(SoC to host\)|N|N|N|
|Independent reset \(in-band\)[<sup>[1]</sup>](#refer-bt-1)|N|N|N|
|Independent reset \(out-band\)[<sup>[1]</sup>](#refer-bt-1)|N|N|N|
|Firmware download \(parallel\)[<sup>[1]</sup>](#refer-bt-1)|N|N|N|
|AutoPTS framework support|Y|Y|N|
|Sniff sub rating|Y|Y|N|
|Secure simple pairing|Y|Y|N|
|Legacy pairing|Y|Y|N|
|HCI read encryption key size command|Y|Y|N|
|Encryption pause and resume|N|Y|N|
|Extended inquiry response|Y|Y|N|
|RF test mode|N|N|N|
|**Bluetooth packet type supported**||||
|ACL \(DM1, DH1, DM3, DH3, DM5, DH5, 2-DH1, 2-DH3, 2-DH5, 3-DH1, 3-DH3, 3- DH5\)|Y|Y|N|
|SCO \(HV1, HV3\)|Y|Y|N|
|eSCO \(EV3, EV4, EV5, 2EV3, 3EV3, 2EV5, 3EV5\)|Y|Y|N|
|**Bluetooth profiles supported**||||
|A2DP sink|N|N|N|
|A2DP source|Y|Y|N|
|AVRCP target/controller|N|N|N|
|HFP Dev/AG|N|N|N|
|OPP server/client|N|N|N|
|SPP server/client|N|N|N|
|HID target/device|N|N|N|
|PCM NBS central/peripheral|Y|Y|N|
|PCM WBS central/peripheral|Y|Y|N|

<div id="refer-bt-1"></div>
[1] Experimental feature intended for evaluation/early development only and not production. Incomplete mandatory certification.

## Bluetooth LE

|<div style="width:200px;">Features</div>|<div style="width:70px;">IW416</div>|<div style="width:70px;">IW611/<br>IW612</div>|<div style="width:70px;">RW610/<br>RW612</div>|<div style="width:70px;">IW610</div>|
|:--------|:-----:|:-----------:|:-----------:|:-----:|
|**Generic features**||||
|Maximum 16 Bluetooth LE connections \(central role\)|Y|Y|Y|Y|
|1Mbps Support|Y|Y|Y|Y|
|Scatternet support|Y|Y|Y|Y|
|Deep sleep using out-of-band|N|N|N|N|
|Wake on Bluetooth LE \(SoC to Host\)|N|N|N|N|
|Filter Accept List|N|N|Y|Y|
|Bluetooth LE AES encryption|N|Y|N|Y|
|RF Test mode|Y|Y|Y|Y|
|**Bluetooth profile support**||||
|Bluetooth LE Broadcaster|Y|Y|Y|Y|
|Bluetooth LE Observer|Y|Y|Y|Y|
|Bluetooth LE Central|Y|Y|Y|Y|
|Bluetooth LE Peripheral|Y|Y|Y|Y|
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
|CAP \(Common Audio Profile\)|Y|Y|Y|Y|
|HAP \(Hearing Aid Profile\)|Y|Y|Y|Y|
|TMAP \(Telephony and Media Audio Profile\)|Y|Y|Y|Y|
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
|Isochronous Channel|N|Y|N|Y|
|**Bluetooth LE audio**|||||||||||
|LE Audio Broadcast Audio Source|N|Y|N|Y|
|LE Audio Broadcast Audio Sink|N|Y|N|Y|
|LE Audio Broadcast Group Validation|N|Y|N|Y|
|LE Audio Broadcast Audio Unfamed Mode|N|Y|N|Y|
|LE Audio Broadcast Audio Sequential Packing|N|Y|N|Y|
|LE Audio Public Broadcast Audio Source|N|Y|N|Y|
|LE Audio Unicast Audio Source|N|Y|N|Y|
|LE Audio Unicast Audio Sink|N|Y|N|Y|
|LE Audio Unicast Group Validation|N|Y|N|Y|
|LE Audio Unicast Audio Unfamed Mode|N|Y|N|Y|
|LE Audio Unicast Audio Sequential Packing|N|Y|N|Y|
|LE Audio Unicast Encrypted Audio|N|Y|N|Y|
|LE Audio Unicast Bi-Directional audio call Gateway|N|Y|N|Y|
|LE Audio Broadcast audio auracast assistant|N|Y|N|Y|
|LE Audio GAF Layers \(BAP,CAP, CAS, CSIP, MCP, MCS, MICP, VCP, BASS, CCP\)|N|Y|N|Y|


