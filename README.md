# Building a LoRaWAN network & replay attack

In this project we build a LoRaWAN network with one gateway and end-node which we connect to TTN(=The Things Network). After that we attempt a replay attack using an SDR(=Software Defined Radio)

## Hardware requirements

- TTN LoRa Gateway
- STM32 LoRa and Sigfox Discovery Kit + X-Nucleo IKSO1A2 expension board
- HackRF One SDR

## Software requirements
- Ubuntu 18.04 bionic amd64
- RiotOS

**NOTE: this repo already contains the modified files to send temperature and humidity data to TTN! If you want to start fresh please clone the RiotOS repo from GitHub under https://github.com/RIOT-OS/RIOT.git !**

This tutorial is based on this wiki page https://wiki.elvis.science/index.php?title=LoRaWAN_/_Riot-OS_Setup. You can either follow along there or take a few shortcuts with the provided files. If you clone this repo you have every file needed to flash the microcontroller.

To setup the TTN Indoor Gateway refer to this link https://www.thethingsindustries.com/docs/gateways/models/thethingsindoorgateway/.

## Steps
To install the needed packages easily just make the packages.sh file executeable and execute <br>
```sudo chmod +x packages.sh``` <br>
```./packages.sh```

Copy *gcc-arm-none-eabi-7-2018-q2-update* folder to your home directory.

Uninstall old packages <br>
```sudo apt remove binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi```

Add the toolchain to your path. This is really important! Without this you can't flash the microcontoller!

To find out your user and show your path variable <br>
```whoami```<br>
```echo $PATH```<br>
```export PATH="$PATH:/home/{YOUR USER}/gcc-arm-none-eabi-7-2018-q2-update/bin/"``` <br>

Set the rights for your username to be able to flash the application on the board and reboot. <br>

```sudo usermod -a -G dialout <username>```

Follow to tutorial on https://wiki.elvis.science/index.php?title=LoRaWAN_/_Riot-OS_Setup and see if you can flash the Hello World example. Useful links:
https://www.thethingsindustries.com/docs/gateways/models/thethingsindoorgateway/
https://www.thethingsindustries.com/docs/devices/adding-devices/



## Flashing the modified LoRa example code in the repo and explanation

Before we flash a small explanation to the code. The X-Nucleo IKSO1A2 board has a sensor named HTS221 which can measure the temperature and relative humidity. The IKSO1A2 interfaces with our STM32 board using the I2C protocol. The STM32 and IKSO1A2 are connected with the Arduino Uno R3 connectors.

```cd myRIOT/examples/lorawan```<br>
```make BOARD=b-l072z-lrwan1```<br>
```make BOARD=b-l072z-lrwan1 flash term```







