---
layout: default

title: Home
---

# LoRa

The main intention for the use of LoRaWAN seems the be its Low Power Long Range Capability. There are many technologies out there that
implement this idea very well but we like LoRa because of how open source it is too. 


Primarily used for long range communication and is tailored for use by the Internet of Things. 
The multitech conduit will be our gateway for accommodating the LORaWan signal, and in turn will need to be 
configured with the correct frequencies for communication.
Depending on the region of operation, the transmit data rate is configurable from 0.25 kbps to 11 kbps, and affects both range 
and maximum payload size. Longest range is reached by using the lowest data rate and payload size. 
Conversely, achieving the highest data rate and payload size results in the shortest range.

### LoRa shield 

Used to send low bytes of data over a long range. Frequency Band: 915MHz/868 MHZ(ours I believe)/433 MHZ (Pre-configure in factory).
We can use Short range devices in the 915-928 MHZ range, which we currently do not have. 

### Multitech Conduit frequency

The conduit has a 915 MHZ primary band with 1-8 sub bands. 


For Australia, the soon to be released LoRaWAN 1.0.1 spec version will be 
somewhat similar to USA- 64 upstream channels from 915.2 to 927.8 MHz, 8 upstream channels from 915.9 to 927.1 MHz, 
and 8 downstream channels from 923.3 to 927.5 MHz.
With New Zealand’s band 915 to 928 MHz, is it a good choice to adopt Australia’s band and use equipment tailored for their market?


Between 915 and 920 MHz, the maximum allowable power is 0.0 dBW (1 W) and from 920 to 928 MHz it is 6.0 dBW (4 W). 
That makes the lower end of the New Zealand band difficult to use in practice.

[Useful Link](https://kotahi.net/radio-frequencies-bands-and-inspections/)

### mDot

Communication module, that is responsible for the incredible range of the conduit. Reckons it has a 16km range. 
2 km deep in building penetration. 

[Useful Link](https://developer.mbed.org/platforms/MTS-mDot-F411/)

## Advantages and Disadvantages of LoRa

### LoRa vs Sigfox

Sigfox and LoRa have been competitors in the LPWAN (Low-Power Network) for several years and here are some of the differences. 
Sigfox and LoRa work much the same, that is sending very small bits of data in small bursts over a very long range network for a very low power cost. 
These options are extremely ideal for things such as parking sensors, water meters or smart garbage. However, it appears sigfox has noted a small limitation
with their technology, and that is that sending data back to the sensor is severely limited and signal interference can be an issue (which 
could be a large barrier in our project)


The LoRa alliance is a large open source non-profit association. However it appears they have claimed to not be full open source as you need
the underlying chip to implement a full LoRaWAN stack which is only available via semtech.
LoRa seems the be the physical layer (the chip) while the software on the chip is what enables the power of the LoRa network. 


The functionality is similar to SigFox in that it’s primarily for uplink-only applications (data from sensors/devices to a gateway) 
with many end-points. Instead of using narrowband transmission, however, it spreads out information on different frequency channels and 
data rates using coded messages. These messages are less likely to collide and interfere with one another thereby increasing the capacity 
of the gateway. (This paragraph seems to indicate why our project group has chosen to use LoRa instead of sigfox with our circumstances).

[Useful Link](https://www.leverege.com/blogpost/iot-connectivity-comparison-lora-sigfox-rpma-lpwan-technologies)

### LoRa vs Cellular

There seems to be a large and well spoken difference between the two of these networks and that is the battery consumption. 
LoRa is used mainly in the IoT department which needs to be best in class for battery life, and cellular is not great for thigs 
such as that and that’s why we have chose to develop LoRa over the use of cellular. 

[Useful Link](http://www.3glteinfo.com/lora/lora-advantages/)

### LoRa vs WiFi

Wifi compared to LoRa isn't great in terms of range (biggest difference). With a typical Wifi range reaching around 32 metres trying to implement this 
into a large city network would need many stations with short distances between them and be very costly and impractical. One advantage is that many consumer devices already support
wifi and means that the service is readily available to the many potential users in the city.

[Useful Link](http://www.ceva-dsp.com/ourblog/game-of-iot-communication-protocols-lora-sigfox-nb-iot-wi-fi-will-there-be-a-sole-ruler/)

### LoRa vs LoRaWAN

LoRa contains only the link layer protocol and is perfect to be used in P2P communications between nodes. LoRa modules 
are a little cheaper that the LoRaWAN ones.
LoRaWAN includes the network layer too so it is possible to send the information to any Base Station already connected 
to a Cloud platform. LoRaWAN modules may work in different frequencies by just connecting the right antenna to its socket.

[Useful Link](http://www.libelium.com/development/waspmote/documentation/lora-vs-lorawan/)