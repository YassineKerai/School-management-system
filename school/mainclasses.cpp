#include "mainclasses.h"
#include <string>
#include <vector>
#include"date.h"
#include<fstream>
#include<iostream>

using namespace std;
// Implementation for exam class
exam::exam() : mark(0) {}

void exam::set_mark(double m)
{
    mark = (m >= 0 && m <= 20) ? m : 0;
}

void exam::set_date(int m, int d, int y)
{
    exam_day.set_year(y);
    exam_day.set_mounth(m);
    exam_day.set_day(d);
}

Date exam::get_date() const
{
    return exam_day;
}

double exam::get_mark() const
{
    return mark;
}

float exam :: getPercentage() const{
    return examPercentage;
}

void exam :: setPercentage(double p){
    examPercentage = p;
}


// Implementation for course class
course::course() : year(0), absense(0) {}

void course::add_exam(exam e)
{
    ex.push_back(e);
}

void course::set_year(int y)
{
    year = (y >= 1 && y <= 5) ? y : 0;
}

void course::add_teach(string t)
{
    teach.push_back(t);
}

void course::set_absense(int a)
{
    absense = (a > 0) ? a : 0;
}

void course::set_courseName(string n)
{
    courseName = n;
}

vector<exam> course::get_exams() const
{
    return ex;
}

int course::get_year() const
{
    return year;
}

vector<string> course::get_teachers() const
{
    return teach;
}

void course :: clear_teacher_vector(){
    teach.clear();
}

int course::get_absense() const
{
    return absense;
}

string course::get_courseName() const
{
    return courseName;
}

void course:: set_coef(int c){
    coef = (c > 0)? c :0;
}

int course:: get_coef(){
    return coef;
}

void course:: editExamPercentage(int i , double p){
    ex[i].setPercentage(p);
}

void course:: editExamMark(int i , double m){
    ex[i].set_mark(m);
}

// Implementation for person class
person::person() : id(0), name("") {}

void person::set_id(int i)
{
    id = (i > 0) ? i : 0;
}

void person::set_name(string n)
{
    name = n;
}

void person::add_course(course c)
{
    Cour.push_back(c);
}

void person :: clear_course(){
   Cour.clear();
}

int person::get_id() const
{
    return id;
}

string person::get_name() const
{
    return name;
}

vector<course> person::get_courses() const
{
    return Cour;
}

// Implementation for teacher class
teacher::teacher() : prof_dev("")
{
    total_teachers++;
}

int teacher ::total_teachers = 0;

void teacher::set_prof_dev(string p)
{
    prof_dev = p;
}

int teacher::get_total_teachers()
{
    return total_teachers;
}

string teacher::get_prof_dev() const
{
    return prof_dev;
}

teacher::~teacher()
{
    total_teachers--;
}

// Implementation for student class
student::student() : year(0)
{
    total_students++;
}

int student ::total_students = 0;

void student::set_year(int y)
{
    year = (y >= 1 && y <= 5) ? y : 0;
}

void student :: set_abscence(int a , int i){
    Cour[i].set_absense(a);

}

int student::get_total_students()
{
    return total_students;
}

int student::get_year() const
{
    return year;
}

int student :: getTotalCourses(){
    return Cour.size();
}

int student :: getTotalAbsence(){
    int count = 0;
    for (int i = 0; i < Cour.size(); ++i) {
        count += Cour[i].get_absense();
    }
    return count;
}

void student ::  set_group(int g ){
    group = (g > 0 ) ? g : 0;
}

int student :: get_group(){
    return group;
}

student::~student()
{
    total_students--;
}

void student :: EditMark(double m , int ci , int ei){
    Cour[ci].editExamMark(ei , m);
}



int textSplit(string text, course segments[], char delimiter){
    int count = 0 , prev = 0 , seg_size = 0;
    for (int i = 0; i <= text.length(); i++)
    {
        if(text[i] == delimiter || i == text.length()) {
            if(prev==0)
                segments[count].set_courseName(text.substr(prev,seg_size)) ;
            else
                segments[count].set_courseName(text.substr(prev,seg_size-1)) ;
            prev = i+1;
            count++;
            seg_size = 0;
        }
        seg_size++;
    }
    return count;
}

int textSplit(string text, string segments[], char delimiter){
    int count = 0 , prev = 0 , seg_size = 0;
    for (int i = 0; i <= text.length(); i++)
    {
        if(text[i] == delimiter || i == text.length()) {
            if(prev==0)
                segments[count] = text.substr(prev,seg_size) ;
            else
                segments[count] = text.substr(prev,seg_size-1) ;
            prev = i+1;
            count++;
            seg_size = 0;
        }
        seg_size++;
    }
    return count;
}

int textSplit(string text, vector<string> &segments, char delimiter){
    int count = 0 , prev = 0 , seg_size = 0;
    for (int i = 0; i <= text.length(); i++)
    {
        if(text[i] == delimiter || i == text.length()) {
            if(prev==0)
                segments.push_back(text.substr(prev,seg_size)) ;
            else
                segments.push_back(text.substr(prev,seg_size-1)) ;
            prev = i+1;
            count++;
            seg_size = 0;
        }
        seg_size++;
    }
    return count;
}

// Function to get a specific line from a file
string getLineFromFile(const string& filePath, int lineNumber) {
    ifstream file(filePath);
    if (!file.is_open()) {
        return "";
    }

    string line;
    int currentLine = 1;
    while (getline(file, line)) {
        if (currentLine == lineNumber) {
            return line;
        }
        currentLine++;
    }
    // If the file has fewer lines than the requested line number
    return "";
}

bool changeLineInFile(const string& filePath, int lineNumber, const string& newLine) {
    ifstream file(filePath);
    vector<string> lines;
    string line;

    if (!file.is_open()) {
        // File does not exist, create a new one
        ofstream outFile(filePath);
        if (!outFile.is_open()) {
            cerr << "Unable to create file: " << filePath << endl;
            return false;
        }
        // Close the newly created file as we will reopen it later for writing
        outFile.close();
    } else {
        // File exists, read its contents
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }

    // Check if the line number is valid
    if (lineNumber <= 0) {
        cerr << "Invalid line number: " << lineNumber << endl;
        return false;
    }

    // Add new lines if the line number is greater than the current number of lines
    while (lineNumber > lines.size()) {
        lines.push_back("");
    }

    // Update the specified line
    lines[lineNumber - 1] = newLine;

    ofstream outFile(filePath);
    if (!outFile.is_open()) {
        cerr << "Unable to open file for writing: " << filePath << endl;
        return false;
    }

    for (const auto& l : lines) {
        outFile << l << "\n";
    }

    outFile.close();
    return true;
}
