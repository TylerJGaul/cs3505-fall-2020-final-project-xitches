import finnhub
from datetime import datetime

finnhub_client = finnhub.Client(api_key="bujgj1v48v6rigi00pt0")

def main():
    f = open("hello.csv","w")
    
    now = datetime.now().strftime("%m/%d/%Y %H:%M")
    f.write("APPLE,"     + str(finnhub_client.last_bid_ask('AAPL')['b']) + "," + now + "\n")
    f.write("TESLA,"     + str(finnhub_client.last_bid_ask('TSLA')['b']) + "," + now + "\n")
    f.write("AMAZON,"    + str(finnhub_client.last_bid_ask('AMZN')['b']) + "," + now + "\n")
    f.write("MICROSOFT," + str(finnhub_client.last_bid_ask('MSFT')['b']) + "," + now + "\n")
    
    
    f.close()

if __name__=="__main__":
    main()
    
