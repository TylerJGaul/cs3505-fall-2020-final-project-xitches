import requests
import json
import datetime
import csv 

result = requests.get('https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/4.5_week.geojson')
data = json.loads(result.text)

events = data["features"]

f = open("earthquakes.csv", "w")
 
for i in events:
	f.write("Location," + i["properties"]["place"] + "," + "\n")
	f.write("Magnitute," + str(i["properties"]["mag"]) + "," + "\n")
	myNumber = i["properties"]["time"]
	date = datetime.datetime.fromtimestamp(myNumber/1000.0)
	print(date)
	f.write("Time," + str(date) + "," + "\n")

f.close()
print(f)

