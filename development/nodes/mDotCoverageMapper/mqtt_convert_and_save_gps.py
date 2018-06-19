
import paho.mqtt.client as mqtt
import json
import base64
import csv

# paho-mqtt 1.1: https://pypi.python.org/pypi/paho-mqtt/1.1


# MQTT Settings
mqtt_broker = "iot.op-bit.nz"  # the web address that will publish the MQTT data
mqtt_port = 1883  # web port to access MQTT_Broker
keep_alive_interval = 45  # number of seconds to keep the connection alive between pings

# application ID as listed in Applications tab of LoRa server
# Node DEVEUI as listed in Ndoe Confirguration tab
# application ID as listed in Applications -> application_name -> Node Configuration tab on LoRa Server
# susbscribe to rx data
mqtt_topic = "application/5/node/0000000000000020/rx"
#


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
    location = message_json['nodeName']
    print("Node data: " + data)
    # decode the data
    data_b = decode_base64(data)
    print("Data decoded: " + data_b)

    #split the string
    data_b.replace(" ", "") #remove whitespace
    lat = data_b.split(',')[0]    #split on comma
    lon = data_b.split(',')[1]

    print("Node lat: " + lat)
    print("Node lon: " + lon)
    lat = parse_gps_data(lat)
    lon = parse_gps_data(lon)
    location_str = lat + ", " + lon
    print("Location: " + location_str)
    write_location(location_str)


# This method converts the input to deciaml degrees, anumber readable by google maps
def parse_gps_data(data):

    if data[len(data)-1] == 'E':
        first_nums = data[:3]
    else:
        first_nums = data[:2]

    rest_of_nums = data[2:len(data)-1]
    print("first_nums: ", str(first_nums))
    print("rest_of_nums: ", str(rest_of_nums))

    calculated_gps = float(first_nums) + (float(rest_of_nums)/60)

    print("lat_lon: ", str(calculated_gps))
    calculated_gps_str = str(calculated_gps)

    # get the index of the decimal

    #original_decimal = data.index('.')
    # get index of where the new decimal needs to go
    #new_decimal = original_decimal - 2
    #new_data_string = data.replace(".", "")
    #lat_lon = new_data_string[:new_decimal] + '.' + new_data_string[new_decimal:]



    if data[len(data)-1] == 'S':
            calculated_gps_str = "-" + calculated_gps_str
    else:
        if data[len(data)-1] == 'W':
            calculated_gps_str = "-" + calculated_gps_str

    # remove last character
    #lat_lon = lat_lon[:-1]
    return calculated_gps_str


# This method writes the location to the csv
def write_location(location_str):
    with open('gps.csv', 'a', newline='') as csvfile:
        gpswriter = csv.writer(csvfile, delimiter=' ')
        gpswriter.writerow([location_str])


# decodes string of base64 characters to a readable string
def decode_base64(data):
    datab = base64.b64decode(data).decode('utf-8')
    return datab


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
