[Index page](../getting-started-iw610-imxrt1060.md) \| [Software setup](../topics/software_setup.md)

# Software setup for Ubuntu

**Note:** Use Ubuntu version 22.04 LTS or later.

## Install the dependencies for Ubuntu

This section includes the steps to install some host dependencies using your package manager.

The current minimum required version for the main dependencies are shown in the table below.

|Tool|Minimum version|
|----|---------------|
|[CMake](https://cmake.org/)|3.20.5|
|[Python](https://www.python.org/)|3.12|
|[Devicetree compiler](https://www.devicetree.org/)|1.4.6|

Step 1 - Add the repository to your installation.

``` {#codeblock_m5d_t4k_cfc}
wget https://apt.kitware.com/kitware-archive.sh
sudo bash kitware-archive.sh
```

Step 2 - Install the required dependencies.

``` {#codeblock_oz1_54k_cfc}
sudo apt install --no-install-recommends git cmake ninja-build gperf \
ccache dfu-util device-tree-compiler wget \
python3-dev python3-pip python3-setuptools python3-tk python3-wheel xz-utils file \
make gcc gcc-multilib g++-multilib libsdl2-dev libmagic1
```

Step 3 - Verify the versions of the main dependencies installed on your system.

```
cmake --version
python3 --version
dtc –version
```
## Install LinkServer utility

LinkServer utility provides firmware updates to devices with MCU-Link architecture \(i.MX RT1060 EVKC\). The utility is also used to debug.

Step 1 - Download the LinkServer utility for Ubuntu.

Link: [LinkServer for Microcontrollers \| NXP Semiconductors](https://www.nxp.com/design/design-center/software/development-software/mcuxpresso-software-and-tools-/linkserver-for-microcontrollers:LINKERSERVER)

Step 2 - Install the utility.

```
chmod a+x LinkServer-24.12.21.x86_64.deb.bin
sudo ./ LinkServer-24.12.21.x86_64.deb.bin
```
## Install the serial console utility

The serial console tool is used to read out the demo application logs or to access the command prompt of the application on the computer connected to i.MX RT1060 EVKC board.

Step 1 - Download and install the terminal emulator software such as minicom.

```
# sudo apt-get install minicom
```

Step 2 - Configure the settings for serial console access.

```
# minicom -s
Serial Port Setup:
- /dev/ttyACMX serial port
- 115200 baud rate
- 8 data bits
- No parity
- One stop bit
- No flow control
```
## Get Zephyr and install Python dependencies for Ubuntu

This section includes the commands to clone Zephyr downstream and its [modules](https://docs.zephyrproject.org/latest/develop/modules.html) into a new [West](https://docs.zephyrproject.org/latest/develop/west/index.html) workspace. In this section, *zephyrproject* is the name of the workspace. Any name and location can be used.

Step 1 - Install the Python venv package.

```
sudo apt install python3-venv
```

Step 2 - Create a new virtual environment.

```
python3 -m venv ~/zephyrproject/.venv
```

Step 3 - Activate the virtual environment.

```
source ~/zephyrproject/.venv/bin/activate
```

Step 4 - Install west.

```
pip install west
```

Step 5 - Get the Zephyr source code.

```
west init zephyrproject -m https://github.com/nxp-zephyr/nxp-zsdk.git --mr nxp-v4.2.0
cd ~/zephyrproject
west update
```

Step 6 - Export a Zephyr CMake package. It allows CMake to load automatically the boilerplate code required to build Zephyr applications.

```
west zephyr-export’
```

Step 7 – Install Python dependencies.

```
pip install -r zephyr/scripts/requirements.txt
```
## Install the Zephyr SDK

The Zephyr software development kit \(SDK\) contains toolchains for each of Zephyr-supported architecture, including a compiler, assembler, linker, and other programs required to build Zephyr applications.

Step 1 - Install the Zephyr SDK.

```
cd ~/zephyrproject/zephyr
west sdk install
```

**Parent topic: **[Software setup](../topics/software_setup.md)

