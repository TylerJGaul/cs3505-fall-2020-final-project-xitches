#include "increment_date.h"

#include <string>
#include <sstream>
#include <iostream>

std::string increment_date(std::string date)
{
    std::stringstream output;
    std::string month, day, year, curr_token;
    std::stringstream ss(date);
    
    // first token: Month
    std::getline(ss, curr_token, '/');
    month = curr_token;
    // second token: Day
    std::getline(ss, curr_token, '/');
    day = curr_token;
    // third token: Year
    std::getline(ss, curr_token, '/');
    year = curr_token;
    
    std::stringstream dayStream, monthStream, yearStream;
    int dayInt, monthInt, yearInt;
    
    if(month.compare("04") == 0 || month.compare("06") == 0 || month.compare("09") == 0 || month.compare("11") == 0 ) //months with 30 days
    {
        if(day.compare("30") == 0) // increment month and day
        {
            day = "01";
            std::stringstream(month) >> monthInt;
            monthInt++;
            if (monthInt < 10) output << "0" << monthInt << "/" << day << "/" << year;
            else output << monthInt << "/" << day << "/" << year;
        }
        else // increment day
        {
            std::stringstream(day) >> dayInt;
            dayInt++;
            if(dayInt < 10) output << month << "/" << "0" << dayInt << "/" << year;
            else output << month << "/" << dayInt << "/" << year;
        }
        
    }
    else if(month.compare("02") == 0) // edge case for 28 days and potential leap year.
    {
        
        if(day.compare("28") == 0) // edge case for day increment
        {
            std::stringstream(year) >> yearInt;
            if (yearInt % 4 == 0) // leap year. Increment day to 29.
            {
                day = "29";
                output << month << "/" << day << "/" << year;
            }
            else // not leap year. increment month and day.
            {
                day = "01";
                month = "03";
                output << month << "/" << day << "/" << year;
            }
        }
        else if(day.compare("29") == 0) // increment month and day.
        {
            day = "01";
            month = "03";
            output << month << "/" << day << "/" << year;
        }
        else // increment day
        {
            std::stringstream(day) >> dayInt;
            dayInt++;
            if(dayInt < 10) output << month << "/" << "0" << dayInt << "/" << year;
            else output << month << "/" << dayInt << "/" << year;
        }
    }
    else if (month.compare("12") == 0) // possible edge case.
    {
        if(day.compare("31") == 0) // increment day, month, and year
        {
            std::stringstream(year) >> yearInt;
            yearInt++;
            day = "01";
            month = "01";
            output << month << "/" << day << "/" << yearInt;
        }
        else // increment day
        {
            std::stringstream(day) >> dayInt;
            dayInt++;
            if(dayInt < 10) output << month << "/" << "0" << dayInt << "/" << year;
            else output << month << "/" << dayInt << "/" << year;
        }
    }
    else
    {
        if(day.compare("31") == 0) //increment month and date.
        {
            std::stringstream(month) >> monthInt;
            monthInt++;
            day = "01";
            if(monthInt < 10) output << "0" << monthInt << "/" << day << "/" << year;
            else output << monthInt << "/" << day << "/" << year;
        }
        else //increment day.
        {
            std::stringstream(day) >> dayInt;
            dayInt++;
            if(dayInt < 10) output << month << "/" << "0" << dayInt << "/" << year;
            else output << month << "/" << dayInt << "/" << year;
        }
    }
    return output.str();
    
}
