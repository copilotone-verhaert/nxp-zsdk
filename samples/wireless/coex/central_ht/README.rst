Coex Central Health Thermometer application
###########################################

.. zephyr:code-sample:: ble_central_ht
   :name: Health Thermometer (Central)
   :relevant-api: bluetooth

   Connect to a Bluetooth LE health thermometer sensor and read temperature measurements.

Overview
********

Similar to the :zephyr:code-sample:`ble_central` sample, except that this
application specifically looks for health thermometer sensor and reports the
die temperature readings once connected.

Requirements
************

* BlueZ running on the host, or
* A board with Bluetooth LE support

Building and Running
********************
west build -b rd_rw612_bga zsdk/samples/wireless/coex/central_ht
-d _build/rd_rw612_bga/coex_bt_central_all -p
-- -DCONF_FILE="prj.conf overlay-wifi-nxp.conf overlay-ot-host-rcp-nxp.conf"

Flashing
********
west flash -d _build/coex_bt_central_all

This sample can be found under :zsdk_file:`zsdk/samples/wireless/coex/central_ht`.
