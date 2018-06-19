---
layout: default
title: Gateways
---

# Gateways

## Description
This repository documents prototype nodes developed and used for LoRa WAN testing.


### What is a gateway?

The gateway (otherwise known as an access point) receives all LoRa radio packets sent by nodes within its range.
Any node can connect to any of the gateways, every LoRa gateway will pick up the nodes packet even if the gateway does not know the 
node.
Gateways typically have a range of between 10 and 15km depending on line of sight, antennas used and the density of interference in the area.  Typically the LoRa gateways are mounted outdoors at a high vantage point to get the best coverage, though some gateways can be indoors with the antenna facing or mounted outside.

The following are different gateways that we are using.


## Pi 2 / mCard AU915
<a href="raspberryPi2mCardGateway/README.md">Pi-2-mCard-AU915</a>

## The Things Network
<a href="iC880a-TTN-Gateway.md">iC880a-TTN</a>

## Loriot
<a href="loriot-VM-Linux-64-Gateway.md">Loriot-VM-Linux-64</a>

## Multitech Conduit
<a href="setupMultitechConduit/README.md">Set up from factory</a>

<a href="changingIpSettings/README.md">- Only need to use: if having issues connecting to Conduit, Network changes</a>

<a href="setUpNodeRed/README.md">Set up node red for use with mDot Box</a>

<a href="AccessingConduitLogs/README.md">Accessing the Conduit's Packet Forwarder logs</a>



<br /><br /><br />
----------------------------------
<script src="{{ site.baseurl }}/linkfixer.js"></script>
