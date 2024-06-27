#include "studentwindow.h"
#include "mainwindow.h"
#include "ui_studentwindow.h"
#include "addstudent.h"
#include <vector>
#include "mainclasses.h"
#include<fstream>
#include<string>
#include<QString>
#include <cstdio>
#include<QMessageBox>
#include "studentview.h"
using namespace std;

void studentwindow :: update(){
    ui->tableWidget->setRowCount(s.size());
    for (size_t i = 0; i <s.size() ; ++i) {
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString(QString :: fromStdString( s[i].get_name()))));
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString(QString :: fromStdString(to_string(s[i].get_id())))));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString(QString :: fromStdString(to_string(s[i].get_year())))));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString(QString :: fromStdString(to_string(s[i].get_group())))));
    }
    QString labelText = "Total Students: " + QString::number(s.size());
    ui->totalS->setText(labelText);
}

studentwindow::studentwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::studentwindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    ui->searchButton->setIcon(QIcon("../img/search icone.png"));

    ifstream SInfo("studentInfo.csv");
    int count = 0;
    string line;
    if (SInfo.is_open()) {
        while (getline(SInfo , line)) {
            string studentInfo[4];
            textSplit(line , studentInfo , ',');
            student newStudent;  // Create a new student object
            newStudent.set_id(stoi(studentInfo[0]));
            newStudent.set_name(studentInfo[1]);
            newStudent.set_year(stoi(studentInfo[2]));
            newStudent.set_group(stoi(studentInfo[3]));
            s.push_back(newStudent);  // Add the new student to the vector
            assigneCourses(count);
            count++;
        }
        SInfo.close();
    }

    update();  // Update the tableWidget
}


studentwindow::~studentwindow()
{
    delete ui;
}

void studentwindow::on_pushButton_6_clicked()
{
    MainWindow *mw = new MainWindow();
    mw->show();
    close();
}

void studentwindow::on_pushButton_clicked()
{
    addstudent *aw = new addstudent(&s , this , ui->tableWidget->currentRow());
    ui->tableWidget->setCurrentCell(-1,0);
    aw->show();
    update();

}

//remove button
void studentwindow::on_pushButton_2_clicked()
{
    long current = ui->tableWidget->currentRow();
    ui->tableWidget->setCurrentCell(-1 , 0);
    if (current >= 0 && current < s.size()) {
        // Remove the student from the vector
        string abscenceFile = to_string(s[current].get_id()) + s[current].get_name() + ".txt";
        remove(abscenceFile.c_str());
        s.erase(s.begin() + current);
        // Open the files for reading and writing
        ofstream SInfo("studentInfo.csv");
        ofstream SAbscence("abscence.csv");
        ofstream EMarks("examMarks.csv");
        // Check if all files are open before proceeding
        if (SInfo.is_open()&&SAbscence.is_open() && EMarks.is_open()) {
            // Rewrite the student data to the files, excluding the removed student
            for (size_t i = 0; i < s.size(); ++i) {
                //the informations is stored like this id,name,year,group
                SInfo << s[i].get_id() << ",";
                SInfo << s[i].get_name() << ",";
                SInfo << s[i].get_year() << ",";
                SInfo << s[i].get_group() << "\n";
                //rewrite abscence file
                SAbscence << s[i].get_year() << ":";
                EMarks <<  s[i].get_year() << ":";
                for(const auto& ab : s[i].get_courses()){
                    SAbscence << ab.get_absense() << ",";
                    for (auto const e : ab.get_exams()) {
                        EMarks << e.get_mark() << "/";
                    }
                    EMarks << ",";
                }
                SAbscence << "\n";
                EMarks << "\n";
            }

            // Close the files after writing
            EMarks.close();
            SInfo.close();
            SAbscence.close();
        }
        update(); // Update the table or list view displaying students
        current = -1;
    }
    else{
        QMessageBox::warning(this, "Error", "Error, please select to remove");
    }
}

void studentwindow :: assigneCourses(int index){
    ifstream CInfo("courseInfo.csv");
    string line, cour[8]  , line2 , temp1[2] , temp2[2] , line3 , marks[6];
    vector<string> abscenses , markFields;

    //for abscence
    line2 = getLineFromFile("abscence.csv" , index+1);
    textSplit(line2 , temp1 , ':');
    textSplit(temp1[1] , abscenses , ',');

    //for exam marks
    //exam mark is stored in three field
    //first field is student year
    //second filed is exams of courses
    //third field is marks
    //like that:  1:1/2/3/4/5,1/2/3/4/5,
    line3 = getLineFromFile("examMarks.csv" , index+1);
    textSplit(line3 , temp2 , ':');
    textSplit(temp2[1] , markFields , ',');

    int count = 0 , count2 =0;
    if (CInfo.is_open()) {
        while (getline(CInfo, line)) {
            textSplit(line , cour , ',');
            if (stoi(cour[1]) == s[index].get_year()) {
                // Check if the course already exists
                bool courseExists = false;
                for (const auto& course :  s[index].get_courses()) {
                    if (course.get_courseName() == cour[0]) {
                        courseExists = true;
                        break;
                    }
                }
                // If the course doesn't exist, add it
                if (!courseExists) {
                    course newCourse;
                    newCourse.set_courseName(cour[0]);
                    exam p[5];
                    for (int i = 0; i < 5; ++i) {
                        p[i].setPercentage(stoi(cour[i+3]));
                        newCourse.add_exam(p[i]);
                    }
                    if(count < abscenses.size()-1){ // because abscence[size-1] is the end line "\n"
                        newCourse.set_absense(stoi(abscenses[count]));
                        count++;
                    }
                    else{
                        newCourse.set_absense(0);
                    }
                    if(count2 < markFields.size()-1){ // because markFields[size-1] is the end line "\n"
                        textSplit(markFields[count2] , marks , '/');
                        for (int i = 0; i < 5; ++i) {
                            newCourse.editExamMark(i , stod(marks[i]));
                            newCourse.editExamPercentage(i , stod(cour[i+3]));
                        }
                        count2++;
                    }
                    else{
                        for (int i = 0; i < 5; ++i) {
                            newCourse.editExamMark(i , 0);
                            newCourse.editExamPercentage(i , stod(cour[i+3]));
                        }
                    }

                    s[index].add_course(newCourse);
                }
            }
        }
        //abscencefile.close();
        CInfo.close();
    }
}

void studentwindow::on_pushButton_3_clicked()
{
    long current = ui->tableWidget->currentRow();
    ui->tableWidget->setCurrentCell(-1 , 0);
    if (current >= 0 && current < s.size()) {
        studentview *sv = new studentview(&(s[current]) , this , current);
        sv->show();
    }

}


void studentwindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "1"){
        for (size_t i = 0; i < s.size(); ++i) {
            if(s[i].get_year()!=1){
                ui->tableWidget->hideRow(i);
            }
            else{
                ui->tableWidget->showRow(i);
            }
        }
    }
    else if(arg1 == "2"){
        for (size_t i = 0; i < s.size(); ++i) {
            if(s[i].get_year()!=2){
                ui->tableWidget->hideRow(i);
            }
            else{
                ui->tableWidget->showRow(i);
            }
        }
    }
    else if(arg1 == "3"){
        for (size_t i = 0; i < s.size(); ++i) {
            if(s[i].get_year()!=3){
                ui->tableWidget->hideRow(i);
            }
            else{
                ui->tableWidget->showRow(i);
            }
        }
    }
    else if(arg1 == "4"){
        for (size_t i = 0; i < s.size(); ++i) {
            if(s[i].get_year()!=4){
                ui->tableWidget->hideRow(i);
            }
            else{
                ui->tableWidget->showRow(i);
            }
        }
    }
    else if(arg1 == "5"){
        for (size_t i = 0; i < s.size(); ++i) {
            if(s[i].get_year()!=5){
                ui->tableWidget->hideRow(i);
            }
            else{
                ui->tableWidget->showRow(i);
            }
        }
    }
    else{
        for (size_t i = 0; i < s.size(); ++i) {
                ui->tableWidget->showRow(i);
        }
    }
}


void studentwindow::on_searchButton_clicked()
{
    if(ui->search->text().isEmpty()){
        QMessageBox :: warning(this , "Error" , "Error, enter the Id to search for it");
        for (size_t i = 0; i < s.size(); ++i) {
            ui->tableWidget->showRow(i);
        }
    }
    else{
        for (size_t i = 0; i < s.size(); ++i) {
            if(ui->search->text().toInt() != s[i].get_id()){
                ui->tableWidget->hideRow(i);
            }
            else{
                ui->tableWidget->showRow(i);
            }
        }
    }
}

