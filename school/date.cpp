#include "date.h"
#include <iostream>
using namespace std;

void Date::print() {
    cout << month << '-' << day << '-' << year << endl;
}

void Date :: set_day(int x){
    if (x > MounthDay())
    {
        day = 1;
    }
    else day = x;
}


void Date :: set_mounth(int x){
    if (x<13 && x>0)
    {
        month  = x;
    }
    else x = 1;
}

void Date :: set_year(int x){
    if (x>0)
    {
        year  = x;
    }
    else year = 1990;
}
//checking is in the setters functions
Date::Date( int m , int d , int y) {
    set_mounth(m);
    set_year(y);
    set_day(d);
}
Date :: Date( ){}


int Date :: get_day(){
    return day;
}

int Date :: get_mounth(){
    return month;
}

int Date :: get_year(){
    return year;
}

bool Date :: is_leap(){
    if (year%4 == 0 && year%100 != 0)
    {
        return true;
    }
    else return false;
}

int Date :: MounthDay(){
    if (month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
    {
        return 31;
    }
    else if(month==2){
        if (is_leap())
        {
            return 29;
        }
        else return 28;
    }
    else return 30;


}

void Date :: increment(){
    if (day != MounthDay())
    {
        day++;
    }
    else{
        if (month == 12)
        {
            day = 1;
            month = 1;
            year++;
        }
        else{
            day = 1;
            month++;
        }
    }
}
