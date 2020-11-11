# import needed libraries
import requests
import json 
from pathlib import Path
from datetime import datetime 
import boto3
import config as cfg

# saves the url
url = "https://api.covidtracking.com/v1/states/ut/current.json"

# get requests for the data at the url
response = requests.get(url)

# save the json to a variable
json_data = json.loads(response.text)

# get the positive case cout
positive = json_data["positiveCasesViral"]

# resourse variable for accessing Amazon S3 EBS service (config file has login credentials)
s3_rss = boto3.resource('s3',
    aws_access_key_id = cfg.myconfig["AccessKey"],
    aws_secret_access_key =  cfg.myconfig["Secret Access Key"])

def main():
    try:
        # grabs the older version of the .csv
        s3_rss.meta.client.download_file('bucketbucketbucket2','COVIDWebscrape.csv','COVIDWebscrape.csv')
    
        # appends to the COVID file  
        f = open("COVIDWebscrape.csv","a")
        
        # declare timestamp variable value and formatting.
        currentTime = datetime.now().strftime("%m/%d/%Y %H:%M")
    
        # pulls the data from the json we parsed earlier 
        f.write(str(positive) + "," + currentTime + "\n")
        
        # close the file 
        f.close()

        # uploads a new version of the file 
        s3_rss.meta.client.upload_file('COVIDWebscrape.csv','bucketbucketbucket2','COVIDWebscrape.csv')
    
    except:
        # I could technically make a new file here since it wasn't found at download but I don't want to possibly
        # overwrite my data by accident if something else causes the exception
        print("File not found.")
    
    
if __name__=="__main__":
    main()