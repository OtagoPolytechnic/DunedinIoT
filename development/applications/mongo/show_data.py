import datetime
import json
from pymongo import MongoClient
from bson import json_util
import numpy as np
import matplotlib.pyplot as plt
import base64
import Tkinter

# example from https://plot.ly/python/line-charts/

client = MongoClient()
db = client.duniot_database
node_data = db.node_data

my_node = json_util.loads(json_util.dumps(node_data.find({"devEUI" : "0000000000000001"})))[0]["dataEntries"]
dates = []
datum = []
for entry in my_node:
    dates.append(entry["gwTime"])
    y = base64.b64decode(entry["data"]).split()[2]
    datum.append(float(y[2:]))

plt.xlabel('time')
plt.ylabel('temperature')
plt.plot(dates, datum)
plt.show()

# light, humidity, temperature