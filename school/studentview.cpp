#include "studentview.h"
#include "ui_studentview.h"
#include<vector>
#include"mainclasses.h"
#include <fstream>
#include <string>
#include"editexam.h"
#include<QMessageBox>
using namespace std;

studentview::studentview(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::studentview)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
}

void studentview :: update_view(){
    ui->NC_lable->setText("Number of courses : " + (QString :: number(s->getTotalCourses())));
    ui->TA_label->setText("Total abscences : " + (QString :: number(s->getTotalAbsence())));
    ui->tableWidget->setRowCount(s->getTotalCourses());
    vector<course> c = s->get_courses();
    double totalAvg = 0 , totalcoef = 0;
    for (long i = 0; i <s->getTotalCourses() ; ++i) {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString(QString :: fromStdString( c[i].get_courseName()))));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString(QString :: fromStdString(to_string(c[i].get_absense())))));
        vector<exam> e = c[i].get_exams();
        double avg = 0;
        totalcoef += c[i].get_coef();
        for (int j = 0; j < 5; ++j) {
            avg += e[j].get_mark() * e[j].getPercentage() * 0.01;
        }
        totalAvg+= avg * c[i].get_coef();
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString(QString :: fromStdString(to_string(avg)))));
    }
    totalAvg /= totalcoef;
    ui->average->setText(QString(QString :: fromStdString(to_string(totalAvg))));

}

studentview::studentview(student* ss, QWidget *parent, int ind)
    : QDialog(parent)
    , ui(new Ui::studentview)
    , s(ss)
    , index(ind)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    ui->tableWidget->setCurrentCell(-1 , -1);
    ui->ID_label->setText(QString :: number(s->get_id()));
    ui->Name_label->setText(QString::fromStdString(s->get_name()));
    ui->Year_label->setText(QString :: number(s->get_year()));
    ui->Group_label->setText(QString :: number(s->get_group()));

    // Update the view
    update_view();
}


studentview::~studentview()
{
    delete ui;
}

void studentview::on_pushButton_clicked()
{
    close();
}

void studentview::on_tableWidget_cellClicked(int row, int column)
{
    if (column == 1) { // Check if the clicked cell is in the absence column
        QTableWidgetItem *currentItem = ui->tableWidget->item(row, column);
        if (currentItem) {
            QString text = currentItem->text();
            int value = text.toInt();
            ui->spinBox->setValue(value);
        }
    }
}


void studentview::on_spinBox_valueChanged(int arg1)
{
    long currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0 && currentRow < s->getTotalCourses()) {
        s->set_abscence(arg1 , currentRow);

        // Update the table widget with the new absence value
        vector<course> c = s->get_courses();
        ui->tableWidget->item(currentRow, 1)->setText(QString :: number(c[currentRow].get_absense()));
        string newline = to_string(s->get_year()) + ":";//this variable will store the new abscence of this student and it will used to change the corresponding abscenses of this student in abscence.csv file
        for (size_t i = 0; i < c.size(); ++i) {
            newline = newline + to_string(c[i].get_absense()) + ",";
        }
        changeLineInFile("abscence.csv" , index+1 , newline);
        QString totalA = "Total Abscence : " + QString :: number(s->getTotalAbsence());
        ui->TA_label->setText(totalA);
    }
    else{
        QMessageBox::warning(this, "Error", "Error, please select to edit abscence");
    }
}


void studentview::on_pushButton_2_clicked()
{
    long current = ui->tableWidget->currentRow();
    ui->tableWidget->setCurrentCell(-1 , 0);
    if(current>=0 && current < s->getTotalCourses()){
        EditExam *ee = new EditExam(s , current , index , this);
        ee->show();
    }
    else{
        QMessageBox :: warning(this , "Error" , "Error, select course to edit it's exam marks");
    }
}

