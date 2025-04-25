[Index page](../wireless-release-notes.md)

# Wi-Fi radio features

## Client mode

<<<<<<< HEAD
<table>
<td>
	<th>Features</th><th>IW416</th><th>IW611/IW612</th><th>RW610/RW612</th>
</td>
<td><tr colspan="4"><b>main feature</b></tr>
</td>
<td>
	<tr>xx</tr><tr>Y</tr><tr>Y</tr><tr>Y</tr>
</td>


</table>


	</table>
|Features|IW416|IW611/IW612|RW610/RW612|
|--------|-----|------------|----------|
|**802.11n – High throughput**|||||||
=======
|Features|IW416|IW611/IW612|RW610/RW612|
|--------|-----|------------|----------|
|**802.11n – High throughput**||||
>>>>>>> 93c0198b9ce (testing the link to index page and fixed the file with Wi-Fi features)
|2.4 GHz band operation supported channel bandwidth: 20 MHz|Y|Y|Y|
|2.4 GHz band supported channel bandwidth: 40 MHz|Y|Y|N|
|5 GHz band supported channel bandwidth: 20 MHz|Y|Y|Y|
|5 GHz band supported channel bandwidth: 40 MHz|Y|Y|N|
|Short/long guard interval \(400 ns/800 ns\)|Y|Y|Y|
|802.11n data rates – Up to 72 Mbit/s \(MCS 0 to MCS 7\)|Y|Y|Y|
|802.11n data rates – Up to 150 Mbit/s \(MCS 0 to MCS 7\)|N|N|N|
|1 spatial stream \(1x1\)|Y|Y|Y|
|HT protection mechanisms|Y|Y|Y|
|Aggregated MAC protocol data unit \(A-MPDU\) TX/RX support|Y|Y|Y|
|Aggregated MAC service data unit \(A-MSDU\) -4k RX support|Y|Y|Y|
|TX MCS rate adaptation \(BGN\)|N|N|Y|
|RX low density parity check \(LDPC\)|N|N|N|
|**802.11 ac – Very high throughput**||||
|2.4 GHz band supported channel bandwidth: 20MHz|N|Y|Y|
|5 GHz band supported channel bandwidth: 20 MHz|N|Y|Y|
|5 GHz band supported channel bandwidth: 40 MHz|N|Y|N|
|5 GHz band supported channel bandwidth: 80 MHz|N|Y|N|
|802.11ac data rates – Up to 86.7 Mbps \(MCS0 to MCS 8\)|N|Y|Y|
|802.11ac data rates – Up to 433.3 Mbps \(MCS 0 to MCS 9\) – 1x1|N|Y|N|
|MU-MIMO Beamformee \(Explicit and Implicit\)|N|N|Y|
|RTS/CTS with BW signaling|N|N|N|
|Operation mode notification|N|N|N|
|Backward compatibility with non-VHT devices|N|Y|Y|
|TX VHT MCS rate adaptation|N|N|Y|
|**802.11ax – High efficiency**||||
|2.4 GHz band supported channel bandwidth: 20MHz|N|Y|Y|
|5 GHz band supported channel bandwidth: 20 MHz|N|Y|Y|
|5 GHz band supported channel bandwidth: 40 MHz|N|Y|N|
|5 GHz band supported channel bandwidths: 80 MHz|N|Y|N|
|OFDMA \(UL/DL, 106 RU\)|N|N|Y|
|OFDMA \(UL/DL, 484 RU\)|N|Y|N|
|1024 QAM|N|Y|N|
|Target wake time \(TWT\)|N|N|Y|
|802.11ax data rate – Up to 114.7 Mbps \(MCS0 to MCS9\)|N|Y|Y|
|802.11ax data rate – Up to 600 Mbps \(MCS0 to MCS11\)|N|Y|N|
|DCM|N|N|Y|
|ER \(extended range\)|N|N|Y|
|SU Beamforming|N|N|Y|
|OMI \(operating mode indication\)|N|N|Y|
|**802.11 a/b/g features**||||
|802.11 b/g data rates – Up to 54 Mbit/s|Y|Y|Y|
|802.11 a data rates – Up to 54 Mbit/s|Y|Y|Y|
|TX rate adaptation \(BG\)|Y|Y|Y|
|Fragmentation/defragmentation|N|N|Y|
|ERP protection, slot time, preamble|Y|N|Y|
|**802.11d**||||
|802.11d – Regulatory domain/operating class/country info|Y|Y|Y|
|**802.11e QoS**||||
|EDCA \[enhanced distributed channel access\] / WMM \(wireless multi-media\)|Y|N|Y|
|**802.11i security**||||
|Opensource WPA supplicant support|N|N|Y|
|WPA2-PSK AES \| WPA Supplicant|N|N|Y|
|WPA3-SAE \(simultaneous authentication of equals\) \| WPA supplicant|N|N|Y|
|WPA2+WPA3 PSK mixed mode \(WPA3 transition mode\) \| WPA supplicant|N|N|Y|
|Wi-Fi enhanced open – OWE \(opporturnistic wireless encryption\) \| WPA supplicant|N|N|Y|
|802.1x EAP authentication methods \| WPA supplicant \[^1\]|N|N|Y|
|WPA2-Enterprise mixed mode \| WPA supplicant|N|N|Y|
|WPA3-Enterprise \(Suite-B\) \|national security algorithm \(CSNA\) \| WPA supplicant|N|N|Y|
|802.11w – PMF \(protected management frames\) \| WPA supplicant|N|N|Y|
|Embedded supplicant support|Y|Y|Y|
|WPA2-PSK AES \| Embedded supplicant|Y|Y|Y|
|WPA+WPA2 PSK mixed mode \| Embedded supplicant|N|N|Y|
|WPA3-SAE \(simultaneous authentication of equals\) \| Embedded supplicant|Y|Y|Y|
|802.11w – PMF \(protected management frames\) \| Embedded supplicant|Y|Y|Y|
|Wi-Fi Roaming|Y|Y|Y|
|WPA3 Enterprise|N|N|N|
|**Power save mode**||||
|Deep sleep|Y|Y|Y|
|IEEE power save|Y|Y|Y|
|Host sleep/WoWLAN \(Inband\)|N|N|Y|
|Host sleep/WoWLAN \(Outband\)|N|N|N|
|U-APSD|N|N|Y|
|**802.11w – PMF \(protected management frames\)**||||
|PMF require and capable|N|N|Y|
|Unicast management frames – Encryption/decryption – using CCMP|N|N|Y|
|Broadcast management frames – Encryption/decryption – using BIP|N|N|Y|
|SA query request/response|N|N|N|
|PMF support using Embedded supplicant|Y|Y|Y|
|**DPP functionality**||||
|Wi-Fi easy connect\[^3\]|N|N|Y|
|**General features**||||
|Embedded supplicant|Y|Y|Y|
|Host sleep packet filtering|N|N|Y|
|Host-based supplicant|N|N|Y|
|Embedded MLME|Y|Y|Y|
|EDMAC – EU adaptivity support \(ETSI certification\)|N|Y|Y|
|IPv6 NS offload|N|N|N|
|FIPS|N|N|Y|
|TKIP\[^2\]|N|N|N|
|RF test mode|N|N|Y|
|802.11k|N|N|Y|
|802.11v|N|N|Y|
|802.11r|N|N|Y|
|DFS radar detection in slave mode \(follow AP\)|Y|Y|Y|
|Embedded roaming based on RSSI threshold beacon loss|Y|Y|Y|
|ARP offload|N|N|Y|
|Cloud keep alive|N|N|N|
|UNII-4 channel support|N|Y|Y|
|ClockSync using TSF|N|N|N|
|Auto reconnect|N|N|N|
|CSI \(channel state information\)|N|N|Y|
|Independent reset \(in-band\)\[^3\]|N|N|Y|
|Independent reset \(out-band\)\[^3\]|N|N|N|
|Wi-Fi agile multi band|N|N|Y|
|Network co-processor \(NCP\) mode\[^4\]|N|N|N|
|802.11mc – WLS \(Wi-Fi Location Service\)|N|N|N|
|802.11az|N|N|N|

\[1\] supported enterprise security options: TLS, TTLS, PEAP v0, PEAP v1

\[2\] As per Wi-Fi specification, connecting in TKIP security in non 802.11n mode is allowed.

\[3\] support available in host-base supplicant

\[4\] Refer to [3](references.md#item_um12133).

## AP mode

|Features|IW416|IW611/IW612|RW610/RW612|
|--------|-----|-----------|-----------|
|**802.11n – High throughput**||||
|2.4 GHz band operation supported channel bandwidth: 20 MHz|Y|Y|Y|
|2.4 GHz band supported channel bandwidth: 40 MHz|Y|Y|N|
|5 GHz band supported channel bandwidth: 20 MHz|Y|Y|Y|
|5 GHz band supported channel bandwidth: 40 MHz|Y|Y|N|
|Short/long guard interval \(400 ns/800 ns\)|Y|Y|Y|
|802.11n data rates – Up to 72 Mbit/s \(MCS 0 to MCS 7\)|Y|Y|Y|
|802.11n data rates – Up to 150 Mbit/s \(MCS 0 to MCS 7\)|N|N|N|
|1 spatial stream \(1x1\)|Y|Y|Y|
|HT protection mechanisms|Y|Y|Y|
|Aggregated MAC protocol data unit \(AMPDU\) RX support|Y|Y|Y|
|Aggregated MAC service data unit \(AMSDU\) – 4k RX support|Y|Y|Y|
|Max client support \(up to eight devices\)|Y|N|Y|
|TX MCS rate adaptation \(BGN\)|N|N|Y|
|RX low density parity check \(LDPC\)|N|N|N|
|**802.11ac – Very high throughput**||||
|5 GHz band supported channel bandwidth: 20 MHz|N|Y|Y|
|5 GHz band supported channel bandwidth: 40 MHz|N|Y|N|
|5 GHz band supported channel bandwidth: 80MHz|N|Y|N|
|Short/long guard interval \(400ns/800ns\)|N|Y|Y|
|802.11ac data rates – Up to 86.7 Mbps \(MCS0 to MCS 8\)|N|Y|Y|
|802.11ac data rates – Up to 433.3 Mbps \(MCS 0 to MCS 9\)|N|Y|N|
|802.11ac data rates – Up to 866.7 Mbps \(MCS 0 to MCS 9\)|N|N|N|
|Single user- Aggregated MAC protocol data unit \(SU-AMPDU\) aggregation|N|N|Y|
|RTS/CTS with BW signaling|N|N|N|
|Backward compatibility with non-VHT devices|N|Y|Y|
|TX VHT MCS rate adaptation|N|N|Y|
|MU-MIMO Beamformee \(explicit and implicit\)|N|N|Y|
|Operation mode notification|N|N|N|
|**802.11ax – High efficiency**||||
|2.4 GHz band operation \(20 MHz channel bandwidth\)|N|Y|Y|
|2.4 GHz band operation \(40 MHz channel bandwidth\)|N|Y|N|
|5 GHz band operation \(20MHz channel bandwidth\)|N|Y|Y|
|5 GHz band operation \(40MHz channel bandwidth\)|N|Y|N|
|5 GHz band operation \(80 MHz channel bandwidth\)|N|Y|N|
|**802.11d**||||
|802.11d – Regulatory domain/operating class/country info|Y|Y|Y|
|**802.11e – QoS**||||
|EDCA \[enhanced distributed channel access\] / WMM \(wireless multi-media\)|N|N|Y|
|**802.11i security**||||
|Hostapd support|N|N|Y|
|WPA2-PSK AES \| hostapd|N|N|Y|
|WPA3-SAE \(simultaneous authentication of equals\) \| Hostapd|N|N|Y|
|WPA2+WPA3 PSK mixed mode \(WPA3 transition mode\) \| Hostapd|N|N|Y|
|Wi-Fi Enhanced Open – OWE \(opporturnistic wireless encryption\) \| Hostapd|N|N|N|
|802.1x EAP authentication methods \| Hostapd \[^1\]|N|N|Y|
|WPA2-Enterprise mixed mode \| Hostapd|N|N|Y|
|WPA3-Enterprise \(Suite-B\) \|national security algorithm \(CSNA\) \| Hostapd|N|N|Y|
|802.11w – PMF \(protected management frames\) \| Hostapd|N|N|Y|
|Embedded Authenticator|Y|Y|Y|
|WPA2-PSK AES \| Embedded supplicant|Y|Y|Y|
|WPA+WPA2 PSK mixed mode \| Embedded supplicant|N|N|Y|
|WPA3-SAE \(simultaneous authentication of equals\) \| Embedded supplicant|Y|Y|Y|
|802.11w – PMF \(protected management frames\) \| Embedded supplicant|Y|Y|Y|
|**802.11y**||||
|Extended channel switch announcement \(ECSA\)|Y|N|Y|
|**802.11w – protected management frames \(PMF\)**||||
|PMF require and capable|N|N|Y|
|Unicast management frames - encryption/decryption – using CCMP|N|N|Y|
|Broadcast management frames - encryption/decryption – using BIP|N|N|Y|
|SA query request/response|N|N|N|
|**General features**||||
|Embedded authenticator|Y|Y|Y|
|Embedded MLME|Y|Y|Y|
|EU adaptivity support|Y|Y|Y|
|Automatic channel selection \(ACS\)|Y|Y|Y|
|External coexistence \(software interface\)|N|N|N|
|STBC RX|N|N|N|
|Independent reset \(in-band\)|N|N|Y|
|Network co-processor \(NCP\) mode|N|N|N|

\[1\] supported enterprise security options: TLS, TTLS, PEAP v0, and PEAP v1.

## AP-STA mode


|Featues|IW416|IW611/IW612|RW610/RW612|
|-------|-----|-----------|------------|
|**Simultaneous AP-STA operation \(same channel\)**||||
|AP-STA functionality|Y|Y|Y|
|**Software antenna diversity \(SAD\)**||||
|Software antenna diversity|Y|N|Y|
|**Generic**||||
|Firmware download \(parallel\)|N|N|N|

