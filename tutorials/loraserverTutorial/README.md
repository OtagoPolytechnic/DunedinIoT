---
layout: default
title: LoRa Setup Tutorial
---

# LoRa Server tutorial
Welcome to the DunedinIoT LoRa Server tutorial. This page will guide you in setting up your own LoRa equipment with the DunedinIoT LoRa network.  
## Links  
[Create account](#create-account)  
[Log In](#log-in)  
[Organizations](#organizations)  
[Gateways](#gateways)
[Applications](#applications)  
[Nodes](#nodes)  
## Create Account 
To request an account, email [Otago Polytechnic Operations](mailto:op.ead.operations@gmail.com?Subject=New%20User), op.ead.operations@gmail.com. Provide your preferred username in the email. If a user already exists with the username, a similar username will be created. If you don't provide a username, one will be generated for you.  
You will get a response with your username and temporary password. It is highly recommended that you change your password when you first log in.
## Log In 
When you arrive at [dunediniot.op.ac.nz](https://dunediniot.op.ac.nz:8080) you will be presented with the login page.  
<img src="loraserverTutorialImages/login.png">
Type in your provided username and password and click 'Login'. If you forgot your username or password, email [Otago Polytechnic Operations](mailto:op.ead.operations@gmail.com?Subject=Forgot%20Password), op.ead.operations@gmail.com to request a new password.  
## Organizations
Organizations manage groups of [applications](#applications), [gateways](#gateways) and users. For example, Otago Polytechnic has their own organization to manage their applications, all of their gateways and the polytechnic students managing the network.  
An organization manages their own gateways and applications, so it is up to the administrators of each organization to make sure the applications and gateways are configured properly.  
You can view all Organizations by clicking on the Organizations link in the top navigatioin bar.  
<img src="loraserverTutorialImages/organizations.png">
Before you can upload data information, you need to create/join an organization.  To request a new organization email [Otago Polytechnic Operations](mailto:op.ead.operations@gmail.com?Subject=New%20Organization), op.ead.operations@gmail.com and specify your organization name. The user who creates the organization will be assigned admin permissions within the context of the organization.
Once you have an Organization, you can view all the data for your organization.  
To view your organization info, log in as an organization admin, click on Organizations and open the organization you own. You will be presented with the application page and can navigate between Applications, Gateways, Organization configuration, and Organization users.
<img src="loraserverTutorialImages/organizationInformation.png">
## Gateways
Gateways allow [nodes](#nodes) to send their data to the loraserver, as long as the server is in range.  
After logging in as an organization admin, click on Organizations and open the organization you own. Then click on Gateways to view the list og gateways you own.
<img src="loraserverTutorialImages/gateways.png">
You will be presented with the gateway creation form. The webpage will ask to know your position, this simply helps set the gateway location. You will need:  
- Gateway name: an organizationally unique name for the gateway. The name may only contain words, numbers and dashes.
- Gateway description: a short description of the gateway. This will let others know a bit more about the gateway sych as manufacture, location, purpose, whatever you feel is necessary.
- MAC Address: the EUI-64 hexadecimal address of the gateway device. __This is 16 hexadecimal symbols with no separation symbols.__ Each gateway comes with it's own MAC address.
- Channel-configuration: TODO
- Gateway altitude (optional): the number of meters above sea level of the gateway.
- Gateway location (optional): the latitude and longitude of the gateway, which can be easily positioned using the map
    - If the gateway has an on-board GPS, latitude longitude and altitude are set automatically.
<img src="loraserverTutorialImages/newGateway.png">

## Applications
Applications are groups of nodes that collect similar data. For example, the Otago Polytechnic organization has two applications: one that manage room temperatures in D block and one to manage soil-water levels around the gardens at polytechnic. It is an easy way to manage a lot of nodes, all sending their own data.  
Organization admins can create new applications and add nodes. To view your applicationa, login as an admin, click on Organizations and open the organization you own, then click on Applications.
When creating a new application, you will be presented with the application creation form. You will need:  
- Application name: an organizationally unique name for the application . The name may only contain words, numbers and dashes.
- Application description: a short description of the application. This will let others know a bit more about the application, the kind of data the application collects, or any information you consider relevant.
<img src="loraserverTutorialImages/newApplication.png">

The application needs its network settings configured. This will set the default configuration for nodes and their default activation method:  
To configure the netowrk settings, click on Application configuration -> Network settings.  
<img src="loraserverTutorialImages/applicationNetworkSettings.png">
There are two forms of activation:  
Over the air activation (OTAA) is a simple method that connects nodes to the network remotely using the LoRa network.  
Activation by personalisation (ABP) uses manual activation of the node and, when selected, disables OTAA.  
Nodes can either use the default application settings, or they can have individual network settings.  
After you have created and configured an application, you can create nodes and assign them to the application.  

## Nodes
Nodes are what LoRa is all about. The definition of a node is 'any device that can send data using the LoRaWAN specification'. Most often, these are Arduinos that have a LoRa shield that allows them to send data over the LoRa network.  
After you have set up your [organization](#organizations), [gateways](#gateways), and [application](#applications), you can begin adding your nodes.  
To add a node to the server, login as an admin, click on Organizations and open the organization you own. Then click on Applications and open the application you want to add the node to, then click Create Node.  
You will be presented with the node creation form. You will need:  
- node name: an organizationally unique name for the node . The name may only contain words, numbers and dashes.
- node description: a short description of the node. This will let others know a bit more about the node sych as manufacture, location, purpose, whatever you feel is necessary.
- Device EUI: the EUI-64 hexadecimal address of the node __This is 16 hexadecimal symbols with no separation symbols.__ This identifier makes each node unique. 
- Application EUI: the EUI-64 hexadecimal identifier for the application to identify the node. __This is 16 hexadecimal symbols with no separation symbols.__ This is a unique identifier used to group nodes.
<img src="loraserverTutorialImages/nodes.png">
If you are using OTAA, you will need:
- Application key: a 32 digit hexadecimal key that will be shared between the peripheral device and the network. It is used to determine the session keys. 

If you are using ABP, you will need:
- Device Address: The logical address used to identify the node on the network.
- Network Session Key: Encryption key between the node and the server used for transmissions and to validate the integrity of messages.
- Application Session Key: Encryption key between the node and the user (via the application) used for transmissions and to validate the integrity of messages.
<img src="loraserverTutorialImages/newNode.png">