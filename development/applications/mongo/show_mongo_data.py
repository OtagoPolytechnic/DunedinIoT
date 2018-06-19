import datetime
import json
from pymongo import MongoClient

client = MongoClient()
db = client.duniot_database
mqtt_collection = db.node_data