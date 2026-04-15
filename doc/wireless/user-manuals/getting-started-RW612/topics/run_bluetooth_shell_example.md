[Index page](../getting-started-RW612.md)

# Run a Bluetooth shell example

Ensure that the Bluetooth shell example is flashed onto the RW612 BGA board. Refer to [Build and flash examples](build_and_flash_examples.md).

This section describes how to initialize Bluetooth and scan to list the nearby devices.

## Bluetooth LE scan and connect

Command to initialize Bluetooth.

**Note:** Issue this command before any other Bluetooth LE command.

```
bt init
```

Sample output:

![](../images/sample-output-initialize-bluetooth.png)

Command to start scanning:

```
bt scan on
```

Command to stop scanning:

```
bt scan off
```

Sample output:

![](../images/sample-output-bt-scan-on.png)

Command to connect:

```
bt connect <address> <type>
```

|Parameter|Description|
|---------|-----------|
|`address`|The MAC address of the remote device|
|`type`|Address the type of the remote device<br> public = public device address<br> random = random device address|

Sample output:

![](../images/sample-output-bt-connect.png)



