import finnhub
from datetime import datetime
import boto3

# Create client variable for finnhub financial API. Used to pull real-time stock data.
finnhub_client = finnhub.Client(api_key="bujgj1v48v6rigi00pt0")

# Resourse variable for accessing Amazon S3 EBS service. Hard coded access_keys for transparency. Will be replaced in a later implementation.
s3_rss = boto3.resource('s3',
    aws_access_key_id='AKIA3F6VMOU5S3T37DY4',
    aws_secret_access_key = 'z5XyJnX/pbAv8MuKp6ukKZSVem08409wFXdjD48N')

# main function
def main():
    try:
        # Download the existing stocks.csv file.
        s3_rss.meta.client.download_file('xitches','stocks.csv','/stocks.csv')
    
        # Append the existing stocks.csv file with the new stock bid prices and timestamps. 
        f = open("stocks.csv","a")
        # Declare timestamp variable value and formatting.
        now = datetime.now().strftime("%m/%d/%Y %H:%M")
    
        # Pull data from finnhub and write to stocks.csv.
        f.write("APPLE,"     + str(finnhub_client.last_bid_ask('AAPL')['b']) + "," + now + "\n")
        f.write("TESLA,"     + str(finnhub_client.last_bid_ask('TSLA')['b']) + "," + now + "\n")
        f.write("AMAZON,"    + str(finnhub_client.last_bid_ask('AMZN')['b']) + "," + now + "\n")
        f.write("MICROSOFT," + str(finnhub_client.last_bid_ask('MSFT')['b']) + "," + now + "\n")
        
        f.close()
        
        # Upload new stocks.csv file to S3. Write over the existing stocks.csv file in S3 because this new file is already appended.
        s3_rss.meta.client.upload_file('/stocks.csv','xitches','stocks.csv')
    
    except:
        print("Stocks.csv file not found.)
    
    
# entry point for the program. Calls main.
if __name__=="__main__":
    main()
    
