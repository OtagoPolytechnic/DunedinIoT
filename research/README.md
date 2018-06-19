---
layout: default
title: Research
---

<hr class="large">

<div id="researchImgContainer">
<h1 id="Research"><strong> Research </strong></h1>
<img id="researchImg" src="{{ site.baseurl }}/img/communication.png" alt="default" >
<p id="researchtxtMain"> <br>
Research into one of the main areas of IoT, looking at the Gateway devices and how they could be utilized for our own work. <br><br> 

We also considered server side stuff and on how to input commands to gather data from the server, then storing the data for later use. <br><br> 

We looked into what LoRa is advantages and disadvantages comparisons with similar technology. <br><br>

What IoT is itself what it stands for and examples of IoT devices where IoT can be applied to. <br><br><br>
</p>
</div>
<br>
<br>
<hr class="large">

<h2>Gateway</h2> 
<p id="researchTxt">IoT gateways perform several critical functions such as device connectivity, protocol translation, data filtering and processing, security, updating, management. <br> These are the devices we thought of using or are using:</p>
<button class="button" style="vertical-align:middle" onclick="GatewayBtn()"><span>Gateway </span></button>

<h2>Server</h2>
<p id="researchTxt">The online server acts as a generic proxy and routes messages between devices and browsers. The IoT protocol used in this application is called SMQ, which provides one-to-one communication</p>
<button class="button" style="vertical-align:middle" onclick="ServerBtn()"><span>Server </span></button>

<h2>LoRaWAN</h2>
<p id="researchTxt">LoRaWAN is a Low Power Wide Area Network (LPWAN) specification intended for wireless battery operated Things in a regional, national or global network.</p>
<button class="button" style="vertical-align:middle" onclick="LoRaWANBtn()"><span>LoRaWAN </span></button>

<h2>Internet of Things</h2>
<p id="researchTxt">The interconnection via the Internet of computing devices embedded in everyday objects, enabling them to send and receive data.</p>
<button class="button" style="vertical-align:middle" onclick="IoTBtn()"><span>IOT </span></button>

<script>
function GatewayBtn() {
    window.location.assign("{{ site.baseurl }}/research/gateway/README.html")
}

function ServerBtn() {
    window.location.assign("{{ site.baseurl }}/research/accessingServerData/README.html")
}

function LoRaWANBtn() {
    window.location.assign("{{ site.baseurl }}/research/loraQA")
}

function IoTBtn() {
    window.location.assign("{{ site.baseurl }}/research/iotQA")
}

</script>

