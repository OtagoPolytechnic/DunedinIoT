
# Ubuntu Trusty (14.04) LoraMcard - Test gateway


## Prep:
* Install VirtualBox.
* In VirtualBox VM manager, install an Ubuntu 14.04 install as usual. Server version is fine unless you want a GUI.
* Plug Mcard/USB into PC.
* Select virtual machine, click settings, click USB, add a USB device filter for FDTI device.

-------------

1. Install 32 bit ftdi drivers to talk to the mCard:

`sudo apt-get install libftdi1:i386`

-------------

2. Install 32 SSL 1.0.2 installed, supplied by 3rd party repository:

`openssl version -a`
`sudo add-apt-repository ppa:0k53d-karl-f830m/openssl`
`sudo apt-get update`
`sudo apt-get install openssl`
`openssl version -a`

------------

3. Download the libmpsse source and compile/install :

`sudo apt-get install swig libftdi-dev python-dev`
`wget https://github.com/devttys0/libmpsse/archive/master.zip -O libmpsse.zip`
`unzip libmpsse.zip`
`cd libmpsse-master`
`cd src`
`./configure`
`make`
`sudo make install`

------------

4. Unplug card, power off VM, replug card, and power on VM.

------------

The gateway is now ready for packet forwarding software, for example:

5. To test with Loriot:

 Open a terminal and get the Loriot binary address (it's different for every server, this gateway is registered on us1.loriot.io )

`sudo mkdir /lrt`
`sudo chmod 777 /lrt`
`cd /lrt`
`wget http://us1.loriot.io/home/gwsw/loriot-linux-x64-mcard-USB-0-latest.bin -O loriot-gw`
`chmod +x loriot-gw`
`cd /lrt`
`sudo ./loriot-gw -f`


---------------

## Notable problems:
* Without SSL 1.0.2 there will be an error.
* Without install the i386 (32 bit) FTDI drivers there wiill be an error message about a missing .so file.
* Gateway terminal will log 404 errors if gateway MAC is not properly  registered with Loriot (or other provider).
* There was an error message and LIBMPSSE code saying "you could be running an incompatible version of the binary" after installing another LIBMPSSE version. That version was replaced with the version above and after restarting the hardware the gateway was active.


