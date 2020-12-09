#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>

#include "increment_date.h"

using namespace std;

// argv[1] = start date
// argv[2] = number of days (in movie)
int main(int argc, char *argv[])
{
    //input files
    /*
    std::ifstream covid("./../data/COVIDWebscrape.csv");
    std::ifstream earthquakes("./../data/earthquakes.csv");
    std::ifstream stocks("./../data/stocks.csv");
    //std::ifstream trends("./../data/twitter_trends.csv");
    std::ifstream weather("./../data/tempOutput.csv");
    
    //if(!crypto.is_open()) throw std::runtime_error("Could not open crypto");
    if(!covid.is_open()) throw std::runtime_error("Could not open covid");
    if(!earthquakes.is_open()) throw std::runtime_error("Could not open earthquakes");
    if(!stocks.is_open()) throw std::runtime_error("Could not open stocks");
    //if(!trends.is_open()) throw std::runtime_error("Could not open trends");
    if(!weather.is_open()) throw std::runtime_error("Could not open weather");
    */
    
    string crypt_def = "no crypto data";
    string covid_def = "no covid data";
    string earthquakes_def = "no earthquake data";
    string stocks_def = "no stock data";
    string trends_def = "no twitter data";
    string weather_def = "no weather data";
    
    int days = atoi(argv[2]);
    string date(argv[1]);
    string curr_time;
    
    string line, curr_token;
    
    std::ofstream output("output.csv");
    bool found = false;
    
    for(int i = 0; i < days; i++)
    {
        
        for(int j = 0; j < 24; j++)
        {
            
            if( j < 10)
            {
                curr_time = "0";
                curr_time += to_string(j);
                curr_time += ":";
            }
            else
            {
                curr_time = to_string(j);
                curr_time += ":";
            }
                
            
            //-------------------------------CRYPTO----------------------------------------
            std::ifstream crypto("./../data/bitcoin_data.csv");
            found = false;
            while(std::getline(crypto, line))
            {   
               
                if (line.find(date) != std::string::npos) {
                    

                    
                    if (line.find(curr_time) != std::string::npos) 
                    {
                        
                        std::stringstream ss(line);
                        
                        while(std::getline(ss, curr_token, ','))
                        {
                            if (curr_token.find("price") != std::string::npos)
                            {
                                crypt_def = date + "-" + to_string(j) + "\\:00 BTC = $" + curr_token.substr(9,8) ;
                                output << crypt_def << "\n";
                                found = true;
                                break;
                            }
                            
                        }
                        break;
                    }
                }
            }
            crypto.close();
            if(found == false)
            {
              output << crypt_def << "\n";  
            }
            
            
            //--------------------------------COVID----------------------------------
    
            std::ifstream covid("./../data/COVIDWebscrape.csv");
            found = false;
            while(std::getline(covid, line))
            {   

                if (line.find(date) != std::string::npos) {
                    std::stringstream ss(line);
                    std::getline(ss, curr_token, ',');
                    covid_def = date + "-" + to_string(j) + "\\:00 Case count = " + curr_token;
                    output << covid_def << "\n";
                    found = true;
                    break;
                }
        
            }
            covid.close();
            if(found == false)
            {
              output << covid_def << "\n";  
            }
            
            //-------------------------------EARTHQUAKES-------------------------------------
            
            std::ifstream earthquakes("./../data/earthquakes.csv");
            found = false;
            while(std::getline(earthquakes, line))
            {   
                if (line.find(date) != std::string::npos) 
                {
                    if (line.find(curr_time) != std::string::npos) 
                    {
                        std::stringstream ss(line);
                
                        std::getline(ss, curr_token, ',');
                        earthquakes_def = date + "-" + to_string(j) + "\\:00 Location\\: " + curr_token + " |";
                        std::getline(ss, curr_token, ',');
                        earthquakes_def += " Magnitute\\: " + curr_token;
                
                        output << earthquakes_def << "\n";
                        found = true;
                        break;
                    }
                }
            }
            earthquakes.close();
            if (found == false)
            {
                output << earthquakes_def << "\n";
            }
            
            
            // ------------------------------- STOCKS -------------------------------
            std::ifstream stocks("./../data/stocks.csv");
            found = false;
            while(std::getline(stocks,line))
            {
                if(line.find(date) != std::string::npos)
                {
                    if(line.find(curr_time) != std::string::npos)
                    {
                        // Output stream with all 4 stocks and prices
                        std::stringstream stocks_stream;
                        
                        // for loop to iterate through the next 4 lines
                        for(int i = 0; i < 4; i++)
                        {
                            // line as a string stream
                            std::stringstream ss(line);
                            std::getline(ss, curr_token, ',');
                            stocks_stream << curr_token << "- ";
                            std::getline(ss, curr_token, ',');
                            stocks_stream << "$" << curr_token << " ";
                            
                            std::getline(stocks,line);
                        }
                        stocks_def = date + "-" + to_string(j) + "\\:00 " + stocks_stream.str();
                        output << stocks_def << '\n';
                        found = true;
                        break;
                        
                    }
                }
            }
            stocks.close();
            if(found == false)
            {
              output << stocks_def << "\n";  
            }
            
            // ---------------------------------TWITTER----------------------------------
            std::ifstream trends("./../data/twitter_trends.csv");
            found = false;
            while(std::getline(trends, line))
            {
                if (line.find(date) != std::string::npos) 
                {
                    //std::cout << "this line contains the date" << '\n';
                    
                    if (line.find(curr_time) != std::string::npos) 
                    {
                        
                        std::getline(trends, line);
                        //std::stringstream ss(line);
                        
                        trends_def = date + "-" + to_string(j) + "\\:00 Current Trending Hashtag- " + line;
                        
                        output << trends_def << "\n";
                        found = true;

                        
                    }
                }
            }
            trends.close();
            if(found == false)
            {
              output << trends_def << "\n";  
            }
            
            // ------------------------------- WEATHER -------------------------------
            std::ifstream weather("./../data/tempOutput.csv");
            found = false;
            while(std::getline(weather,line))
            {
                if(line.find(date) != std::string::npos)
                {
                    if(line.find(curr_time) != std::string::npos)
                    {
                        std::stringstream ss(line);
                        std::getline(ss,curr_token, ',');
                        std::getline(ss,curr_token, ',');
                        
                        //this is the temperature
                        found = true;
                        std::string temperature = "Temperature at this hour is " + curr_token;
                        string file_name = "icon";
                        file_name += date.substr(0,2) + date.substr(3,2) + date.substr(6,4) + curr_time.substr(0,2) + "00.png";
                        weather_def = file_name; //date + "-" + to_string(j) + "\\:00 " + temperature;
                        output << weather_def << '\n';
                        break;
                    }
                }
            }
            weather.close();
            if(found == false)
            {
              output << weather_def << "\n";  
            }
            
            // output << " ---------------------------------------------------------------------" << "\n";
        }
        
        date = increment_date(date);
    }

     
}
