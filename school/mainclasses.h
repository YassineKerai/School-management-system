#pragma once
#include <string>
#include <vector>
#include "date.h"
#include<fstream>
using namespace std;

// Forward declarations
class teacher;
class student;

class exam {
private:
    Date exam_day;
    double mark;
    float examPercentage;

public:
    exam();
    void set_mark(double);
    void set_date(int , int  , int);
    Date get_date() const; // Getter function for exam date
    double get_mark() const; // Getter function for exam mark
    float getPercentage() const;
    void setPercentage(double);
};

class course {
private:
    vector<exam> ex;
    int year;
    vector<string> teach;
    int absense;
    string courseName;
    int coef;

public:
    course();
    void add_exam(exam e);
    void set_year(int);
    void add_teach(string t);
    void set_absense(int);
    void set_courseName(string );
    vector<exam> get_exams() const; // Getter function for exams
    int get_year() const; // Getter function for course year
    vector<string> get_teachers() const; // Getter function for teachers
    int get_absense() const; // Getter function for course absense
    string get_courseName() const; // Getter function for course name
    void clear_teacher_vector();
    void set_coef(int);
    int get_coef();
    void editExamPercentage(int , double);
    void editExamMark(int , double);

};

class person {
protected:
    int id;
    string name;
    vector<course> Cour;

public:
    person();
    void set_id(int);
    void set_name(string);
    void add_course(course c);
    void clear_course();
    int get_id() const; // Getter function for person ID
    string get_name() const; // Getter function for person name
    vector<course> get_courses() const; // Getter function for courses
};

class teacher : public person {
private:
    string prof_dev;
    static int total_teachers;

public:
    teacher();
    void set_prof_dev(string);
    static int get_total_teachers();
    string get_prof_dev() const; // Getter function for professional development
    ~teacher();
};

class student : public person {
private:
    int year;
    static int total_students;
    int group;

public:
    student();
    void set_year(int);
    void set_abscence(int , int);
    static int get_total_students();
    int getTotalAbsence();
    int getTotalCourses();
    int get_year() const; // Getter function for student year
    void set_group(int);
    int get_group();
    //mark course index , exam index
    void EditMark(double , int , int);
    ~student();
};

int textSplit(string text, course segments[], char delimiter = ' ');
int textSplit(string text, string segments[], char delimiter = ' ');
int textSplit(string text, vector<string> &segments, char delimiter = ' ');
string getLineFromFile(const string& filePath, int lineNumber);
bool changeLineInFile(const string& filePath, int lineNumber, const string& newLine);
