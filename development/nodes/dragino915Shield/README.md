---
layout: default
title: Dragino LoRa Shield (915MHz)
---

# Dragino LoRa Shield (915MHz)

The Dragino LoRaShield is a popular example of an easy to use development/prototype board for use in LoRaWAN networks. The Dragino LoRaShield is an Arduino shield that provides the ability to function as either a LoRaWAN node, or a single channel LoRaWAN gateway. This documentation, and accompanying source code focusses solely on creating a development LoRaWAN node. The specific purpose of this repository (and guide) is to provide an example of the Dragino LoRaShield device operating on the standardised LoRaWAN frequencies for Australia and New Zealand... specifically the 915 MHz to 930 MHz frequency, more commonly known as *AU915*.

## Quick Start

1. Download this repo as a zip file
2. Add library to Arduino IDE using add a zip file functionality
3. Plug in Arduino with a Dragino LoRaShield attached
4. Optional: Edit source code */examples/Dragino_LoRaShield_AU915/Dragino_LoRaShield_AU915.ino* file to send different output/add code for sensors etc.
5. Select Upload to compile, then upload
6. View device is functioning correctly by viewing serial output
7. Done.


## Walkthrough

This section covers a complete and thorough walkthrough for installing an AU915 sketch onto and Arduino shield and operation of an attached Dragino LoRaShield. A *Windows 10 environment* is used for the walkthrough. However, the same process can easily be achieved on Linux, however, some of the instructions will vary.

### Hardware Overview

The [Dragino LoRaShield](http://www.dragino.com/products/module/item/102-lora-shield.html) is an affordable Arduino shield for prototype development of LoRaWAN devices. The device is excellent for a prototype node. The version used in this project in the US900 version - however, this device is not specifically supported for the AU915 specification. A photo of the device is included below for reference. 

![](resources/Lora_Shield_v1.4.jpg "Dragino LoraShield v1.4")

Attaching the LoRaWAN shield to an Arduino is a very simple process. Just plug the shield into the matching pins available. Plug and play! 

**NOTE:** Make sure you have the US900 version of the Dragino LoRaShield. The version information is available on the bottom of the PCB board. A box on the PCB should be ticked to illustrate the specific model.

### Setup Arduino IDE

Download and install the Arduino IDE. [These instructions for installation on Windows](https://www.arduino.cc/en/Guide/Windows) should provide enough information.

### Download Repo and Flash Arduino

This repo and the library can be added to the Arduino IDE library using a variety of methods. These are outlined below:

1. Clone [this](https://github.com/matthijskooijman/arduino-lmic) git repository into your sketchbook/libraries folder. In Windows the specific directory is `C:\Users\<username>\My Documents\Arduino\libraries\<library folder>`
2. Install it using the Arduino Library manager ("Sketch" -> "Include Library" -> "Manage Libraries...")
3. Download a zipfile from github using the "Download ZIP" button and install it using the Arduino IDE ("Sketch" -> "Include Library" -> "Add .ZIP Library...")

For more infomation on using Arduino libraries, see https://www.arduino.cc/en/Guide/Libraries.

Now we want to open the `Dragino_LoRaShield_AU915.ino` sketch file in the Arduino IDE. The sketch file is available in the `/examples` directory in this repo. This specific sketch file is a modified version of the original sketch provided with the Dragino LoRaShield provided on [the Dragino Wiki](http://wiki.dragino.com/index.php?title=Lora_Shield) for the US900 version, available directly from [here](https://github.com/dragino/Lora/blob/master/Lora%20Shield/Examples/lora_shield_ttn-915-fix-frequency/lora_shield_ttn-915-fix-frequency.ino).

Make sure your Arduino and LoRaShield are attached to the host computer via USB. Now, upload sketch to Arduino, by selecting "Upload" which will compile and upload the sketch to the device.

Finally, open serial monitor so we can view output from the device and ensure it is functioning correctly. Set the serial monitor baud to 115200. You should see output similar to that below:

```
Starting
Packet queued for freq: 916800000
132794: EV_TXCOMPLETE (includes waiting for RX windows)
Packet queued for freq: 917000000
1515422: EV_TXCOMPLETE (includes waiting for RX windows)
Packet queued for freq: 917200000
2898055: EV_TXCOMPLETE (includes waiting for RX windows)
Packet queued for freq: 917400000
4280688: EV_TXCOMPLETE (includes waiting for RX windows)
Packet queued for freq: 917600000
5663319: EV_TXCOMPLETE (includes waiting for RX windows)
Packet queued for freq: 917800000
7045951: EV_TXCOMPLETE (includes waiting for RX windows)
Packet queued for freq: 918000000
8428658: EV_TXCOMPLETE (includes waiting for RX windows)
Packet queued for freq: 918200000
9811291: EV_TXCOMPLETE (includes waiting for RX windows)
Packet queued for freq: 916800000
11193937: EV_TXCOMPLETE (includes waiting for RX windows)
```

In the output you should see packets queued for sending on 8 specific channels. Each channel is displayed as the frequency used when sending a packet. The node should send a packet, then the channel should either: 1) Move to the next channel; or 2) If at the end of the channel list, jump back to the first channel. In the listing above, packets started sending on channel 8 (916.8 MHz) and cycled throught the remaining 7 channels before looping back to channel 8 again.

### LoRaWAN Library Configuration

For the sake of complete documentation, this section summarises the changes made to the original source code used in this project. To reiterate, two sources were used to create the required files for this project:

1. [Fork of the LMIC project modified for use on Arduinos](https://github.com/matthijskooijman/arduino-lmic)
2. [Arduino sketch (.ino file) for the LoRaShield provide by Dragino](https://github.com/dragino/Lora/blob/master/Lora%20Shield/Examples/lora_shield_ttn-915-fix-frequency/lora_shield_ttn-915-fix-frequency.ino)

As summary of changes to the source code are:

1. Modify the LMIC fork to use the US915 frequency
2. Modify the LMIC fork US915 frquency to adhere to the AU915 standard
3. Modify the LMIC fork disableChannel() function to use the correct channel step
4. Modify the Arduino sketch to disable the correct channels (to only enable band 2 in AU915)

The changes made are more thoroughly documented in the following subsections.

### LMIC Fork

The LMIC library used in this project is a pre-existing fork of the IMB LoRaMAC-in-C. To quote the original author: the fork is _the IBM LMIC (LoraMAC-in-C) library, slightly modified to run in the Arduino environment, allowing using the SX1272, SX1276 tranceivers and compatible modules._ This section outlines the modifications to the library that have been made. Firstly, all modification have been made in the src folder, and sub-folder named lmic, as documented below:

```
Dragino_LoRaShield_Node_AU915/src/lmic
```

In `config.h` comment out line 8:

```
//#define CFG_eu868 1
```

In `config.h` uncomment line 9:

```
#define CFG_us915 1
```

This change specified that we should use the US915 specification. However, even though we just changed the frequency to US915 we will not use this specification... we just hijacked this definition for ease of implementation. Therefore, we need to update the ecisting US915 MHz code for the AU915 specification. In the `lorabase.h` file, change lines 117 to 126 to:

```
enum { US915_125kHz_UPFBASE = 915200000,
       US915_125kHz_UPFSTEP =    200000,
       US915_500kHz_UPFBASE = 915900000,
       US915_500kHz_UPFSTEP =   1600000,
       US915_500kHz_DNFBASE = 923300000,
       US915_500kHz_DNFSTEP =    600000
};
enum { US915_FREQ_MIN = 915000000,
       US915_FREQ_MAX = 928000000 };
```       

The above code sets a new minimum (915000000) and maximum (928000000) frequqncy to match the AU915 band 2 standard.

Now, we need to also make a small change in the `lmic.c` file. Change lines 776 to 779, from:

```
void LMIC_disableChannel (u1_t channel) {    
    if( channel < 72+MAX_XCHANNELS )        
    LMIC.channelMap[channel/4] &= ~(1<<(channel&0xF));
}
```

to:

```
void LMIC_disableChannel (u1_t channel) {
    if( channel < 72+MAX_XCHANNELS )        
    LMIC.channelMap[channel/16] &= ~(1<<(channel&0xF));
}
```

All done! That was all the changes required to the LMIC Arduino port to get the Dragino LoRaShield working in the AU915 standard.
       
### Arduino sketch for Dragino LoRaShield

The script in this project was derived from the original Dragino LoRaShield sketch provided on the Dragino Wiki. The sketch required a variety of modifications. However, the most important modification is the selection of channels. The sketch initialises the LoRaWAN chip on the shield and enables all channels by default. The snippet of code below demonstrates how to use a simple for loop to disable specific channels (0-7 and 16-72). Ultimately, this only leaves the AU915 band 2 channels enabled, that is, channels 8-15. The code modification if documented below:

```
// First, disable channels 0-7
for (int channel=0; channel<8; ++channel) {
  LMIC_disableChannel(channel);
}
// Now, disable channels 16-72 (is there 72 ??)
for (int channel=16; channel<72; ++channel) {
   LMIC_disableChannel(channel);
}
// This means only channels 8-15 are up
```

## Additional Resources

1. [http://www.instructables.com/id/Use-Lora-Shield-and-RPi-to-Build-a-LoRaWAN-Gateway/](http://www.instructables.com/id/Use-Lora-Shield-and-RPi-to-Build-a-LoRaWAN-Gateway/)
2. [http://wiki.dragino.com/index.php?title=Lora_Shield](http://wiki.dragino.com/index.php?title=Lora_Shield)
3. [https://www.thethingsnetwork.org/forum/t/ttn-australian-communities/4068/10](https://www.thethingsnetwork.org/forum/t/ttn-australian-communities/4068/10)
4. [https://www.thethingsnetwork.org/forum/t/lmic-node-dropped-packets/4400/9](https://www.thethingsnetwork.org/forum/t/lmic-node-dropped-packets/4400/9)