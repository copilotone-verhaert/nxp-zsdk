[Index page](../wireless-release-notes.md)

# Wi-Fi and Bluetooth/802.15.4 coexistence features

|<div style="width:200px;">Features</div>|<div style="width:70px;">IW416</div>|<div style="width:70px;">IW611/<br>IW612</div>|<div style="width:70px;">RW610/<br>RW612</div>|<div style="width:70px;">IW610</div>|
|:--------|:-----:|:-----------:|:-----------:|:-----:|
|**BCA\_TDM separate antenna [<sup>[1]</sup>](#refer-coex-1) \(lower and higher isolation\)** <br> **1x1 Wi-Fi, \(Bluetooth+15.4 shared\)**||||
|STA + Bluetooth|N|N|N|N|
|Mobile AP + Bluetooth|N|N|N|N|
|Bluetooth LE + Wi-Fi|Y|N|Y|Y|
|Bluetooth + Bluetooth LE + Wi-Fi|N|N|N|N|
|OpenThread + Bluetooth|N|N|N|N|
|OpenThread + Bluetooth LE [<sup>[2]</sup>](#refer-coex-2)|N|N|N|N|
|OpenThread + Bluetooth + Bluetooth LE|N|N|N|N|
|OpenThread + Wi-Fi|N|N|N|N|
|Bluetooth + OpenThread + Wi-Fi|N|N|N|N|
|Bluetooth LE + OpenThread + Wi-Fi|N|N|N|N|
|Bluetooth + Bluetooth LE + OpenThread + Wi-Fi|N|N|N|N|
|Single antenna configuration|N|N|Y|Y|
|External Coexistence PTA|N|N|Y|Y|
|**BCA TDM coexistence mode \(shared antenna\)**|||||||
|STA + Bluetooth coexistence|N|N|N|N|
|STA + Bluetooth LE coexistence|Y|N|Y|Y|
|STA + Bluetooth + Bluetooth LE coexistence|N|N|N|N|
|AP + Bluetooth coexistence|N|N|N|N|
|AP + Bluetooth LE coexistence|Y|N|Y|Y|
|AP + Bluetooth + Bluetooth LE coexistence|N|N|N|N|

<div id="refer-coex-1"></div>
[1] Experimental feature intended for evaluation/early development only and not production. Incomplete mandatory certification.
<div id="refer-coex-2"></div>
[2] The narrow-band radio can be configured to support Bluetooth LE, 802.15.4, and to time-slice between Bluetooth LE and 802.15.4.

