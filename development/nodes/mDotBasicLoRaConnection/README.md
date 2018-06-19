---
layout: default
title: Using an mDot to connect to a LoRa network over ABP (Activation by personalisation)
---

# Using an mDot to connect to a LoRa network over ABP (Activation by personalisation)


## Prep

Must already have mbed.org account set up.
If that is not done, see the Prep section of this file:
https://github.com/OtagoPolytechnic/DunedinIoT/blob/gh-pages/development/nodes/mDotHelloWorld/README.md


## Required Hardware

Multitech mDot - 915MHz

MultiTech mDot UDK board


## Wiring

Attach the mDot to the UDK, and attach a 900MHz antenna to the mDot.

<img src="mDotBasicLoRaConnectionPics/mdotudk.jpg" width="400px">


## Importing our example program

Go to: <a href="https://developer.mbed.org/users/kellybs1/code/mDot_LoRa_Connect_ABPA/">https://developer.mbed.org/users/kellybs1/code/mDot_LoRa_Connect_ABPA//</a>           

This program sends a simple text message to the gateway every ten seconds.

On the right of the screen, click "Import into Compiler".

<img src="mDotBasicLoRaConnectionPics/importintocompiler.jpg">

In the Compiler click to import the program as a program.

<img src="mDotBasicLoRaConnectionPics/importasprogram.jpg">

Near the top of the program, change the network setting values to match the settings required for your LoRaWAN.

<img src="mDotBasicLoRaConnectionPics/networksettings.jpg" width="700px">

If adaptive data rate is disabled, ie, `static bool adr = false;`

Scroll down to `dot->setTxDataRate(mDot::DR2);` and set your required data rate.

Click "Compile" and download the bin file when prompted.

<img src="mDotBasicLoRaConnectionPics/savebin.jpg">


## Load program onto mDot

Attach the mDot to the UDK board, and attach the UDK to a PC via USB.

The mDot should appear in the pc as a flash drive would for example "MULTITECH (F:)".

Copy the binary file to this drive. The mDot might automatically restart automatically, but if it does not, press the Reset button on the UDK.

## Seeing debug info on a PC over USB

On Windows you must install serial-USB driver from here: <a href="http://www.st.com/en/embedded-software/stsw-link009.html">http://www.st.com/en/embedded-software/stsw-link009.html</a>

Open a serial terminal. I used the Arduino IDE's serial monitor set to the correct COM port (this varies depending on the machine) at 9600 baud.

If the application runs correctly and the serial monitor is configured correctly you should see debugging output, and be recieving packets at the gateway.

