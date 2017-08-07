---
layout: default

title: Home
---


## What is LoRa?

LoRa is a long range, low power, wireless platform that is the prevailing technology choice for building IoT networks worldwide. 

## What is the difference between LoRa and LoRaWAN? 

LoRa is a modulation technique that provides significantly longer range than competing technologies. LoRa is the physical layer, and LoRaWAN is a data link (MAC) protocol for a high capacity long range and low power star network. The LoRaWAN protocol is optimized for low cost, battery operated sensors and includes different classes of nodes to optimize the tradeoff between network latency and battery lifetime.

## Pros and Cons of LoRaWAN

Pros:

+ It uses 868 MHz/915 MHz ISM band swhich is available world wide.
+ It has very wide coverage range about 5km in urban areas and 15km in suburban areas
+ It consumes less power and hence battery will last for longer duration
+ Single LoRa Gateway device is designed to take care of 1000s of end devices or nodes
+ It is widely used for M2M/IoT applications
+ It uses LoRa modulation which has constant envelope modulation similar to FSK modulation type and hence available PA (power amplifier) stages having low cost and low power with high efficiency  can be used

Cons:

+ It can be used for applications requiring low data rate i.e. upto about 27 Kbps
+ LoRaWAN network size is limited based on parameter called as duty cycle. It is defined as percentage of time during which the channel can be occupied. This parameter arises from the regulation as key limiting factor for traffic served in the LoRaWAN network
+ It is not ideal candidate to be used for real time applications requiring lower latency and bounded jitter requirements

