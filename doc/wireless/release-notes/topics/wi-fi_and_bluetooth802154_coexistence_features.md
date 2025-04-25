[Index page](../wireless-release-notes.md)

# Wi-Fi and Bluetooth/802.15.4 coexistence features

|Features|IW416|IW611/IW612|RW610/RW612|
|--------|-----|-----------|-----------|
|**BCA\_TDM separate antenna \[^1\] \(lower and higher isolation\)** <br> **1x1 Wi-Fi, \(Bluetooth+15.4 shared\)**||||
|STA + Bluetooth|N|N|N|
|Mobile AP + Bluetooth|N|N|N|
|Bluetooth LE + Wi-Fi|Y|N|Y|
|Bluetooth + Bluetooth LE + Wi-Fi|N|N|N|
|OpenThread + Bluetooth|N|N|N|
|OpenThread + Bluetooth LE \[^2\]|N|N|Y|
|OpenThread + Bluetooth + Bluetooth LE|N|N|N|
|OpenThread + Wi-Fi|N|N|Y|
|Bluetooth + OpenThread + Wi-Fi|N|N|N|
|Bluetooth LE + OpenThread + Wi-Fi|N|N|Y|
|Bluetooth + Bluetooth LE + OpenThread + Wi-Fi|N|N|N|
|Single antenna configuration|N|N|Y|
|External Coexistence PTA|N|N|Y|
|**BCA TDM coexistence mode \(shared antenna\)**|||||||
|STA + Bluetooth coexistence|N|N|N|
|STA + Bluetooth LE coexistence|Y|N|Y|
|STA + Bluetooth + Bluetooth LE coexistence|N|N|N|
|AP + Bluetooth coexistence|N|N|N|
|AP + Bluetooth LE coexistence|Y|N|Y|
|AP + Bluetooth + Bluetooth LE coexistence|N|N|N|

\[1\] Experimental feature intended for evaluation/early development only and not production. Incomplete mandatory certification.

\[2\] The narrow-band radio can be configured to support Bluetooth LE, 802.15.4, and to time-slice between Bluetooth LE and 802.15.4.

