#ifndef DATE_H
#define DATE_H

// Simple Date class
class Date {
public:

    Date();
    Date( int , int , int );
    void print();
    void set_day(int x);
    void set_year(int x);
    void set_mounth(int x);
    int get_day();
    int get_year();
    int get_mounth();

    void increment();
private:
    int month;
    int day;
    int year;
    bool is_leap();
    int MounthDay();
};

#endif // LAB2_DATE_H
