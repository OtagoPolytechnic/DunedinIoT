import twitter
import time
import paho.mqtt.client as mqtt
import json
import base64


# python-twitter : https://python-twitter.readthedocs.io/en/latest/installation.html
# paho-mqtt 1.1: https://pypi.python.org/pypi/paho-mqtt/1.1

# set twitter app API values
# get tokens for your account https://python-twitter.readthedocs.io/en/latest/getting_started.html
api = twitter.Api(consumer_key="key goes inside quotes",
                  consumer_secret="key goes inside quotes",
                  access_token_key="key goes inside quotes",
                  access_token_secret="key goes inside quotes")

# MQTT Settings
mqtt_broker = "server.domain.org"  # the web address that will publish the MQTT data
mqtt_port = 0000  # web port to access MQTT_Broker
keep_alive_interval = 45  # number of seconds to keep the connection alive between pings
mqtt_topic = "application/99999/#"  # application ID as listed in Applications tab of LoRa server

# temperature threshold - for actual frost should be zero or one
temp_max = 30


# get data from MQTT
# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc) + ": (if it's 0, it's connected)")
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe(mqtt_topic)


# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    # print data
    print("MQTT Data Received...")
    print("MQTT Topic: " + msg.topic)
    print("Topic Data: " + str(msg.payload))
    message_json = json.loads(msg.payload)
    # extract and print the data I want
    data = message_json['data']
    # get the node's name - should be set as nodes street address
    location = message_json['nodeName']
    print("Node data: " + data)
    # decode the data
    data_b = decode_base64(data)
    # extract temperature
    # round down to 1dp for output
    temp_temp = float(data_b)
    temp = round(temp_temp, 1)
    # now tweet if it's necessary
    handle_temperature_tweet(temp, location)


# decodes string of base64 characters to a readable string
def decode_base64(data):
    datab = base64.b64decode(data).decode('utf-8')
    print("Data decoded: " + datab)
    return datab


# Trigger tweeting if temperature below threshold
def handle_temperature_tweet(temp, node_name):
    if temp < temp_max:
        message = time.strftime("%d/%m/%Y - %H:%M:%S: Ice warning at " + node_name + ": " + str(temp) + "C")
        # post message on twitter
        status = api.PostUpdate(message)
        # confirm sent
        print("%s just posted: %s" % (status.user.name, status.text))


# start script
client = mqtt.Client()
# event bindings
client.on_connect = on_connect
client.on_message = on_message
# now connect
client.connect(mqtt_broker, mqtt_port, keep_alive_interval)
# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
client.loop_forever()




