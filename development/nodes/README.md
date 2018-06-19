---
layout: default
title: Prototype nodes
---

# Prototype nodes


## Description
This repository documents prototype nodes developed and used for LoRa WAN testing.


### What is a node?

A node is the "feet on the ground" of a LoRa network. It is a device primarily consisting of a sensor device, a LoRa network chip and a programmable "brain" such as an Arduino unit.

The node's job is to sense real world data and send it on to a LoRa gateway. The actual programmed behaviour of the node can vary widely, depending on power requirements, amount of data required, and how often the data should be sent.

The following examples are prototype development attempts, including how-tos for functions such as reading sensor data, using sleep functions, and USB debugging.

The examples are designed to be easy to build upon to develop future nodes.


### Arduino nodes

These examples catalogue our first attempts at building prototype nodes based on the Arduino.

[Dragino 868Mhz Temp/Humidity](dragino868TempHumid/README.md)

[Dragino 868Mhz Temp/Humidity/LDR](dragino868TempHumidLDR/README.md)

[Haxiot 915Mhz Test](haxiot915Test/README.md)

[Dragino 915Mhz Shield](dragino915Shield/README.md) 


### MDot development 

The Multitech mDot has become our node platform of choice due to ease of programming and building nodes due to community and manufacturer support, and official support for the NZ/AU frequencies the Dunedin IoT project is using.

For future building reference, the pin layout of the mDot model used is available <a href="https://github.com/OtagoPolytechnic/DunedinIoT/blob/gh-pages/development/nodes/mDot/mdot-pinout-5.png">here</a>

1. [mDot (HelloWorld by BK)](mDotHelloWorld/README.md)

2. [mDot (Using Analogue input)](mDotAnalogueLDR/README.md)

3. [mDot (Importing 3rd party sensor libraries)](mDotImportingLibrary/README.md)

4. [mDot (Using Analogue + Digital)](mDotDigitalandAnalogue/README.md)

5. [mDot (Basic LoRaWAN ABP connection)](mDotBasicLoRaConnection/README.md)

6. [mDot (Sleep/wake cycle example)](mDotSleepExample/README.md)

7. [mDot (Fully functional node)](mDotLoRaDHT22LDRSleep/README.md)


### Battery powered Nodes

[mDot (Battery powered Nodes)](mDotBattery/README.md)


### mDot/Python/Twitter Frost Alert

[mDot/Python/Twitter Frost Alert](mDotTwitterBot/README.md)


### mDot Key formatter

When generating new nodes on the Application Server and entering their session keys into their source code, the keys must be reformatted to a hexadecimal array. This program reformats the server generated key strings:

<a href="https://github.com/kellybs1/MDotKeyFormatter">https://github.com/kellybs1/MDotKeyFormatter</a>



<br /><br /><br />
----------------------------------
<script src="{{ site.baseurl }}/linkfixer.js"></script>
