#include "coursewindow.h"
#include "ui_coursewindow.h"
#include "mainwindow.h"
#include "addcourse.h"
#include<vector>
#include"mainclasses.h"
#include <fstream>
#include<iostream>
#include<QMessageBox>
#include<string>
#include "courseview.h"
using namespace std;
void coursewindow :: update(){
    ui->tableWidget->setRowCount(c.size());
    for (int i = 0; i < c.size(); ++i) {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString(QString :: fromStdString( c[i].get_courseName()))));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString(QString :: fromStdString( to_string(c[i].get_year())))));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString(QString :: fromStdString( to_string(c[i].get_coef())))));
    }
    QString labelText = "Total Courses: " + QString::number(c.size());
    ui->QTotalC->setText(labelText);
}
coursewindow::coursewindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::coursewindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    ui->searchButton->setIcon(QIcon("../img/search icone.png"));

    string line;
    ifstream CInfo("courseInfo.csv");//name year coef examPercentages(final midterm test 1 2 3)
    if (CInfo.is_open()) {
        while(getline(CInfo , line)) {
            string info[9];
            textSplit(line , info , ',');
            course newcourse;
            newcourse.set_courseName(info[0]);
            newcourse.set_year(stoi(info[1]));
            newcourse.set_coef(stoi(info[2]));
            exam p[5];
            for (int i = 0; i < 5; ++i) {
                p[i].setPercentage(stoi(info[i+3]));
                newcourse.add_exam(p[i]);
            }
            c.push_back(newcourse);
        }
        CInfo.close();
    }
    update();
}

coursewindow::~coursewindow()
{
    delete ui;
}

void coursewindow::on_pushButton_6_clicked()
{
    MainWindow* mw = new MainWindow();
    mw->show();
    close();
}
void coursewindow::on_add_button_clicked()
{
    addcourse* ac = new addcourse(&c , this ,  ui->tableWidget->currentRow());
    ui->tableWidget->setCurrentCell(-1,0);
    ac->show();
    update();
}

//remove button
void coursewindow::on_remove_button_clicked()
{
    long current = ui->tableWidget->currentRow();
    ui->tableWidget->setCurrentCell(-1 , 0);
    if (current >= 0 && current < c.size()) {
        int courseYear = c[current].get_year();//this is to remove the course from the abscence and examMark files
        string courseName = c[current].get_courseName();// this is to remove the course from teacherCourse file
        c.erase(c.begin() + current);

        // Open the file for reading and writing
        ofstream CInfo("courseInfo.csv");

        // Check if the file is open before proceeding
        int count2 = 0; // count of how many courses of the same year of the removed course
        if (CInfo.is_open()) {
            // Rewrite the student data to the file, excluding the removed student
            for (size_t i = 0; i < c.size(); ++i) {
                CInfo << c[i].get_courseName() << ",";
                CInfo << c[i].get_year() << ",";
                CInfo << c[i].get_coef() << ",";
                for (auto const e : c[i].get_exams()) {
                    CInfo << e.getPercentage() << ",";
                }
                CInfo << "\n";
                if(c[i].get_year() == courseYear && i< current)
                    count2++;
            }

            // Close the file after writing
            CInfo.close();
        }
        ifstream Abscences("abscence.csv");
        ifstream EMarks("examMarks.csv");
        string line , segments[2] , line2 , segments2[2];
        int count = 1;
        //remove abscences
        while(getline(Abscences , line)){
            if(!line.empty()){
            textSplit(line , segments , ':');//first field is of year and the second is of abscences
            if (to_string(courseYear) == segments[0] ) {
                vector<string> abscence;
                textSplit(segments[1] , abscence , ',');
                string newline = to_string(courseYear) + ":";
                for (int i = 0; i < abscence.size(); ++i) {
                    if(i != count2  ){
                        if(abscence[i] != "")
                            newline += abscence[i] + ",";
                    }
                }
                changeLineInFile("abscence.csv" , count , newline);
            }
            }
            count++;
        }
        //remove exam marks
        count = 1;
        while(getline(EMarks , line2)){
            if(!line2.empty()){
            textSplit(line2 , segments2 , ':');
            if (to_string(courseYear) == segments2[0] ) {
                vector<string> MarksField;
                textSplit(segments2[1] , MarksField , ',');
                string newline = to_string(courseYear) + ":";
                for (int i = 0; i < MarksField.size(); ++i) {
                    if(i != count2  ){
                        if(MarksField[i] != "")
                            newline += MarksField[i] + ",";
                    }
                }
                changeLineInFile("examMarks.csv" , count , newline);
            }
            }
            count++;

        }

        ifstream TCourse("teacherCourses.csv");
        string Line , temp;
        vector<string> newLines , Segments;
        while(getline(TCourse , Line)){
            temp = "";
            textSplit(Line , Segments , ',');
            for (const string n : Segments) {
                if( n != courseName ){
                    temp = temp + n + ",";
                }
            }
            newLines.push_back(temp);
        }
        TCourse.close();
        //rewrite the lines again
        ofstream tCourse("teacherCourses.csv");
        if(tCourse.is_open()){
            for (int i = 0; i < newLines.size(); ++i) {
                tCourse << newLines[i] << "\n";
            }
        }
        tCourse.close();
        

        update(); // Update the table or list view displaying students
        current = -1;
    }
    else{
        QMessageBox::warning(this, "Error", "Error, please select to remove");
    }
}


void coursewindow::on_view_button_clicked()
{
    long current = ui->tableWidget->currentRow();
    ui->tableWidget->setCurrentCell(-1 , 0);
    if (current >= 0 && current < c.size()) {
        courseview *cv = new courseview(&(c[current]) , this);
        cv->show();
    }

}


void coursewindow::on_searchButton_clicked()
{
    if(ui->search->text().isEmpty()){
        QMessageBox :: warning(this , "Error" , "Error, enter the Id to search for it");
        for (int i = 0; i < c.size(); ++i) {
            ui->tableWidget->showRow(i);
        }
    }
    else{
        for (int i = 0; i < c.size(); ++i) {
            if(ui->search->text().toStdString() != c[i].get_courseName()){
                ui->tableWidget->hideRow(i);
            }
            else{
                ui->tableWidget->showRow(i);
            }
        }
    }
}


void coursewindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "1"){
        for (int i = 0; i < c.size(); ++i) {
            if(c[i].get_year()!=1){
                ui->tableWidget->hideRow(i);
            }
            else{
                ui->tableWidget->showRow(i);
            }
        }
    }
    else if(arg1 == "2"){
        for (int i = 0; i < c.size(); ++i) {
            if(c[i].get_year()!=2){
                ui->tableWidget->hideRow(i);
            }
            else{
                ui->tableWidget->showRow(i);
            }
        }
    }
    else if(arg1 == "3"){
        for (int i = 0; i < c.size(); ++i) {
            if(c[i].get_year()!=3){
                ui->tableWidget->hideRow(i);
            }
            else{
                ui->tableWidget->showRow(i);
            }
        }
    }
    else if(arg1 == "4"){
        for (int i = 0; i < c.size(); ++i) {
            if(c[i].get_year()!=4){
                ui->tableWidget->hideRow(i);
            }
            else{
                ui->tableWidget->showRow(i);
            }
        }
    }
    else if(arg1 == "5"){
        for (int i = 0; i < c.size(); ++i) {
            if(c[i].get_year()!=5){
                ui->tableWidget->hideRow(i);
            }
            else{
                ui->tableWidget->showRow(i);
            }
        }
    }
    else{
        for (int i = 0; i < c.size(); ++i) {
            ui->tableWidget->showRow(i);
        }
    }
}

