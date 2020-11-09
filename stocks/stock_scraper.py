import finnhub
from datetime import datetime
import boto3

finnhub_client = finnhub.Client(api_key="bujgj1v48v6rigi00pt0")
s3_rss = boto3.resource('s3',
    aws_access_key_id='AKIA3F6VMOU5S3T37DY4',
    aws_secret_access_key = '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')

def main():
    
    s3_rss.meta.client.download_file('xitches','stocks.csv','/stocks.csv')
    
    f = open("stocks.csv","a")
    
    now = datetime.now().strftime("%m/%d/%Y %H:%M")
    f.write("APPLE,"     + str(finnhub_client.last_bid_ask('AAPL')['b']) + "," + now + "\n")
    f.write("TESLA,"     + str(finnhub_client.last_bid_ask('TSLA')['b']) + "," + now + "\n")
    f.write("AMAZON,"    + str(finnhub_client.last_bid_ask('AMZN')['b']) + "," + now + "\n")
    f.write("MICROSOFT," + str(finnhub_client.last_bid_ask('MSFT')['b']) + "," + now + "\n")
    
    
    f.close()
    
    s3_rss.meta.client.upload_file('/stocks.csv','xitches','stocks.csv')

if __name__=="__main__":
    main()
    
