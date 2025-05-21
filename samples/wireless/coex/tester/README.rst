Coex Tester application
#######################

The Tester application uses binary protocol to control Zephyr stack and is aimed at
automated testing. It requires two serial ports to operate.
The first serial is used by Bluetooth Testing Protocol (BTP) to drive Bluetooth
stack. BTP commands and events are received and buffered for further processing
over the same serial.

BTP specification can be found in auto-pts project repository:
https://github.com/intel/auto-pts
The auto-pts is an automation framework for PTS Bluetooth testing tool provided
by Bluetooth SIG.

See https://docs.zephyrproject.org/latest/guides/bluetooth/index.html for full
documentation about how to use this test.


Supported Profiles and Services
*******************************

Host/Core
=========

* GAP
* GATT
* IAS
* L2CAP
* OTS
* SM

Building and Running
********************
west build -b rd_rw612_bga zsdk/samples/wireless/coex/tester
-d _build/rd_rw612_bga/coex_bt_tester_all -p
-- -DCONF_FILE="prj.conf overlay-wifi-nxp.conf overlay-ot-host-rcp-nxp.conf"

Flashing
********
west flash -d _build/coex_bt_tester_all

This sample can be found under :zsdk_file:`zsdk/samples/wireless/coex/tester`.
