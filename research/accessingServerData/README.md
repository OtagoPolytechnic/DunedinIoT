---
layout: default
title: Getting data from the server
---

# Document ways to see data from server

Start the gateway using:
Ensure the service `start.sh` is stopped you can check this using the command `ps –A`  
If the service is still running the you can stop it by using the command `sudo kill 647` (replace the 647 with the process id of `start.sh`)
Then the service needs to be restarted, change directory using `cd /opt/ttn-gateway/bin`
Then start the service `sudo sh start.sh`

One of the ways to get the data from the server you use the MQTT protocol.  MQTT allows clients to connect to a broker to publish messages (based on topics) and subscribe to topics.  This allows clients to get the data being sent and use it for an application.
For more information on MQTT please visit https://mosquitto.org/man/mqtt-7.html 

Get the data:
You can then subscribe from another computer using `mosquitto_sub -t "application/1/#" –v` to get the data.  The –t “…” is the MQTT topic to subscribe to in this case it will get the data from the application with the ID of 1.  The –v is a verbose output which will print the messages as topic payload


Different ways to see the data

To create a new user if required:
Login to https://10.118.0.93:8080/#/login?_k=9ifapi then click the users tab at the top right of the page. 


API – uses authentication
https://10.118.0.93:8080/api

To use the REST API you need a JWT (JSON Web Token)
See documentation at https://10.118.0.93:8080/api#!/Internal/Login for using a POST request to get a JWT.  You will need to pass the POST request your account username and password.

To get a list of applications you can use a GET request using the JWT previously requested as authorisation.  Documentation at https://10.118.0.93:8080/api#!/Application/List 



To subscribe to a topic an option is using a Mosquitto subscription the command for this is `mosquitto_sub -h 10.118.0.93 -t "application/1/#" –v`

Mosquitto is a message broker that uses the MQTT protocol.  Use mosquitto_pub to publish a message on a topic and exit.  Use mosquito_sub to subscribe to a topic and print the messages it receives.

Mobile application
On a mobile application the client uses an HtmlUrlConnection POST request to get the authenticated users JWT (JSON Web Token).  This can then be used to make further GET and POST requests.

Another alternative is to use a service such as LORIOT which is a paid service (though they offer a trail version) offering a backend server for gateway to connect to and limited front end for testing, it is designed to be connected to an existing application.  They allow for many ways to get the data such as using websockets, HTTP PUSH / REST, TLS Socket and MQTT directly from their platform or using cloud services such as IBM BlueMix, Microsoft Azure or Amazon Web Services.


