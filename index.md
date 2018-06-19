---

redirect_from: "/ThingsNetworkDunedin/"
layout: default
title: Home
---
<br/>

<h1 id= "deviceheader">Our Mission</h1>

To research and develop an open LoRaWAN consisting of one or more gateway devices, multiple sensor devices, and a central server. All of this in the central Dunedin area, to provide access to user data for use in custom mobile/web/desktop applications. We want to record the data retrieved from our multiple sensors into a database to build statistical graphs to cross reference the data with the locations of the other sensors.
<br/>

### Current Status:
Planning to buy and build the enclosures for the gateway.
Deciding on the top-level domain name for the server.

### Future Plan:
Build the gateways and have them up and working by week 8.

<hr class="medium">

## Network Infrastructure

The overall infratructure of this system consists of multiple nodes (sensors) connected to their local gateway which will pass through the dedicated frequencies through the LoRaWAN network. This data will then be sent to the central server to be stored in the database and reviewed upon at a later time.



<center> 
<h2>Network Diagram </h2>
</center>
<br/>

<img src="https://otagopolytechnic.github.io/DunedinIoT/img/NetworkDiagram.png" class="img-responsive">

<hr class="medium">

<section id="services" class="services bg-primary text-white"> 

<div class="container">
        <div class="row text-center">
          <div class="col-lg-10 mx-auto">
            <div class="row">
              <div class="col-md-3 col-sm-6">
                <div class="service-item">
                  <span class="fa-stack fa-4x">
                    <i class="fa fa-circle fa-stack-2x"></i>
                    <i class="fa fa-cloud fa-stack-1x text-primary"></i>
                  </span>
                  <h4>
                    <strong>Github</strong>
                  </h4>
                  <p>View on Github</p>
                  <a href="{{ site.github.repository_url }}" class="btn btn-light">View</a>
                </div>
              </div>
              <div class="col-md-3 col-sm-6">
                <div class="service-item">
                  <span class="fa-stack fa-4x">
                    <i class="fa fa-circle fa-stack-2x"></i>
                    <i class="fa fa-compass fa-stack-1x text-primary"></i>
                  </span>
                  <h4>
                    <strong>Development</strong>
                  </h4>
                  <p>Development process</p>
                  <a href="development/README.html" class="btn btn-light">View</a>
                </div>
              </div>
              <div class="col-md-3 col-sm-6">
                <div class="service-item">
                  <span class="fa-stack fa-4x">
                    <i class="fa fa-circle fa-stack-2x"></i>
                    <i class="fa fa-flask fa-stack-1x text-primary"></i>
                  </span>
                  <h4>
                    <strong>Research</strong>
                  </h4>
                  <p>Research into IoT</p>
                  <a href="{{ site.baseurl }}/research/README.html" class="btn btn-light">View</a>
                </div>
              </div>
              <div class="col-md-3 col-sm-6">
                <div class="service-item">
                  <span class="fa-stack fa-4x">
                    <i class="fa fa-circle fa-stack-2x"></i>
                    <i class="fa fa-shield fa-stack-1x text-primary"></i>
                  </span>
                  <h4>
                    <strong>About Us</strong>
                  </h4>
                  <p>Information about the Team</p>
                  <a href="#" class="btn btn-light">View</a>
                </div>
              </div>
            </div>
            <!-- /.row (nested) -->
          </div>
          <!-- /.col-lg-10 -->
        </div>
        <!-- /.row -->
      </div>
      <!-- /.container -->
    </section>

  <br/>

## What is the Internet of Things?
The Internet of Things is the inter-networking of devices such as smart devices, sensors, software, and other items embedded with electronics.
Connecting these devices to a network creates the Internet of Things and enables the collection and exchange of data between devices and server. 
This data can then be used accessed and used by an end user. Although very similar, this is not to be confused by wifi. The IoT uses slightly 
different technology to achieve *this*. Our Iot solution is implemented using LoRaWAN.
<br/>
<br/>
<hr class="medium">

## LoRaWAN Network
LoRaWAN is a low-power, long-range wide area network standard devised by the LoRa Alliance.
It is intended for long-life, battery operated sensor devices to communicate sensed data to a central server via one or more internet-connected gateway devices capable of receiving radio transmissions. LoRaWAN targets key requirements of the IoT such as secure bi-directional communication, mobility and localisation services. The main reason we want to use LoRaWAN is because of its Low Power Long Range capability. There are other technologies that offer this functionality, however we have chosen to use LoRa because of how it is open source.
<br/>
<br/>


### Advantages and disadvantages of LoRa vs other technologies

#### LoRa vs LoRaWAN
LoRaWAN includes the network layer opposed to LoRa which only contains the link layer protocol so it's possible to send information to any Base Station already connected to a cloud patform.
LoraWAN modules potentially work in different frequencies by only connecting the right antenna into the appropriate socket. LoRa modules are also cheaper than LoRaWAN's ones.  

#### LoRa vs Sigfox

Sigfox has a small limitation with their technology, for example how it send data back to the sensor is very limited and is possible for signal interference to be an issue.
LoRa is a large open source non-profit association.
LoRa and Sigfox share similar functionality in that it's primarily for uplink-only applications with multiple end-points. 
The main difference between Sigfox and LoRa is the fact that Sigfox uses narrowband transmission where LoRa spreads out information via different frequency channels using encyrpted messages. This improves the capacity of the gateway as the messages are less likely to collides and interfere with one another. 
<br/>

#### LoRa vs Cellular

LoRa trumps Cellular in terms of battery consuption. For example, the LTE Cat-1 (Cellular network) battery life time for 200 mAH is 1.5 years where LoRaWAN is up to 9 years.
LoRa is developed to work only with IoT devices which needs best in class battery life. 
<br/>

#### LoRa vs WiFi

In terms of range, WiFI has a typical range of reaching around 3 metres where LoRa can reach up to 15 kms. An advantage of WiFi is that many consumer devices already support WiFi which means that the service is readily available to the many potential users in the city. 


<hr class="medium">
