# Monitoring

## Scenario
- The device(s) will send the random data(as measurements) over MQTT to the device-gateway
    - Topic : Device name
    - Data : Any string
- The device-gateway handle these data from the device(s)

## Compilation

### Dependencies

It depends the sofware packages below:
- cmake >= 3.10.0
- paho.mqtt.c == v1.3.8
- paho.mqtt.cpp == v1.2.0

It is tested on mosquitto v1.4.15.

Then simply run the "build.sh"

### For Developer
- clang-tidy-9 : Used as a code formatter.
- vallgrind : Checked the memory leaks.

## Usage

### Running gateway:

```bash 
./run_gateway.sh 
```

To check the memory leaks on gateway:
```bash 
./memcheck.sh
```
Then the mem-check-result.txt file will be created for output of valgrind.

### Running device(s)

```bash 
./run_device.sh client1
```

