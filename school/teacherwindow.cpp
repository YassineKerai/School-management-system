#include "teacherwindow.h"
#include "ui_teacherwindow.h"
#include "mainwindow.h"
#include <vector>
#include "mainclasses.h"
#include<fstream>
#include<string>
#include<QString>
#include<QMessageBox>
#include "addteacher.h"
#include "teacherview.h"
using namespace std;

void teacherwindow :: update(){
    ui->tableWidget->setRowCount(t.size());
    for (int i = 0; i < t.size(); ++i) {
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString(QString :: fromStdString( t[i].get_name()))));
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString(QString :: fromStdString( to_string(t[i].get_id())))));
    }
    QString labelText = "Total Teachers: " + QString::number(t.size());
    ui->QTotalT->setText(labelText);
}

teacherwindow::teacherwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::teacherwindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    ui->searchButton->setIcon(QIcon("../img/search icone.png"));

    ifstream TInfo("teacherInfo.csv");//id   name
    string line;
    if (TInfo.is_open()) {
        while (getline(TInfo , line)) {
            teacher newTeacher;
            string temp[2];
            textSplit(line , temp , ',');
            newTeacher.set_id(stoi(temp[0]));
            newTeacher.set_name(temp[1]);
            t.push_back(newTeacher);
        }
        TInfo.close();
    }

    ifstream TCourse("teacherCourses.csv");
    if (TCourse.is_open()) {
        for (int i = 0; i < t.size(); ++i) {
            getline(TCourse , line);
            course courses[15];
            int nc = textSplit(line , courses ,',');
            for (int j = 0; j < nc; ++j) {
                t[i].add_course(courses[j]);
            }
        }
    }
    ifstream TPD("teacherProfessionalDevelopment.txt");
    string temp = "";
    if (TPD.is_open()) {
        for (size_t i = 0; i < t.size(); ++i) {
            while(line != "---"){
                getline(TPD , line);
                if(line != "---" && line != "")
                    temp = temp + line +"\n";
            }
            t[i].set_prof_dev(temp);
            line = "";
            temp = "";
        }
        TPD.close();
    }
    update();
}

teacherwindow::~teacherwindow()
{
    delete ui;
}

void teacherwindow::on_pushButton_6_clicked()
{
    MainWindow* mw = new MainWindow();
    mw->show();
    close();
}


void teacherwindow::on_pushButton_3_clicked()
{
    addteacher* at = new addteacher(&t , this ,  ui->tableWidget->currentRow());
    ui->tableWidget->setCurrentCell(-1,0);
    at->show();
    update();
}
// year:1,2,3,4,5/1,2,3,4,5/


void teacherwindow::on_remove_button_clicked()
{
    long current = ui->tableWidget->currentRow();
    ui->tableWidget->setCurrentCell(-1 , 0);
    if (current >= 0 && current < t.size()) {
        // Remove the student from the vector
        t.erase(t.begin() + current);

        // Open the files for reading and writing
        ofstream TInfo("teacherInfo.csv");
        ofstream TPD("teacherProfessionalDevelopment.txt");
        ofstream TC("teacherCourses.csv");

        // Check if all files are open before proceeding
        if (TInfo.is_open() && TPD.is_open() && TC.is_open()) {
            // Rewrite the teacher data to the files, excluding the removed student
            for (size_t i = 0; i < t.size(); ++i) {
                TInfo << t[i].get_id() << ",";
                TInfo << t[i].get_name() << "\n";
                TPD << t[i].get_prof_dev() << "\n---\n";
                vector<course> temp = t[i].get_courses();
                for (int j = 0; j < temp.size(); ++j) {
                    TC << temp[j].get_courseName() << ",";
                }
                TC << "\n";
            }

            // Close the files after writing
            TInfo.close();
            TPD.close();
            TC.close();
        }

        update(); // Update the table or list view displaying students
        current = -1;
    }
    else{
        QMessageBox::warning(this, "Error", "Error, please select to remove");
    }
}


void teacherwindow::on_pushButton_clicked()
{
    long current = ui->tableWidget->currentRow();
    ui->tableWidget->setCurrentCell(-1 , 0);
    if (current >= 0 && current < t.size()) {
        teacherview *tv = new teacherview(&(t[current]) , this);
        tv->show();
    }

}


void teacherwindow::on_searchButton_clicked()
{
    if(ui->search->text().isEmpty()){
        QMessageBox :: warning(this , "Error" , "Error, enter the Id to search for it");
        for (int i = 0; i < t.size(); ++i) {
                ui->tableWidget->showRow(i);
        }
    }
    else{
        for (int i = 0; i < t.size(); ++i) {
            if(ui->search->text().toInt() != t[i].get_id()){
                ui->tableWidget->hideRow(i);
            }
            else{
                ui->tableWidget->showRow(i);
            }
        }
    }
}

