Coex shell application
######################

The Coex application uses binary protocol to control Zephyr stack and is aimed at
automated testing. It requires two serial ports to operate.

This application permits to send via shells :
  - Bluetooth commands
  - Thread commands
  - Wifi commands

Building and Running
********************
west build -b rd_rw612_bga zsdk/samples/wireless/coex/shell
-d _build/rd_rw612_bga/coex_bt_shell_all -p
-- -DCONF_FILE="prj.conf overlay-wifi-nxp.conf overlay-ot-host-rcp-nxp.conf"

Flashing
********
west flash -d _build/coex_bt_tester_all

This sample can be found under :zsdk_file:`zsdk/samples/wireless/coex/shell`.
