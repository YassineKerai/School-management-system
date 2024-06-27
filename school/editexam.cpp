#include "editexam.h"
#include "ui_editexam.h"
#include "mainclasses.h"
#include<exception>
#include<vector>
#include<QMessageBox>
#include"studentview.h"
#include<string>
using namespace  std;

EditExam::EditExam(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditExam)
{
    ui->setupUi(this);
}

EditExam::EditExam(student *t , int i , int Fi , QWidget *parent )
    : QDialog(parent) , ss(t) , ind(i) , fileIndex(Fi)
    , ui(new Ui::EditExam)
{
    ui->setupUi(this);
    vector<course> temp = ss->get_courses();
    vector<exam> e = temp[i].get_exams();

    string text = "Final exam (" + to_string(e[0].getPercentage()) + "%): ";
    ui->label->setText(QString :: fromStdString(text));
    text = "Midterm (" + to_string(e[1].getPercentage()) + "%): ";
    ui->label_2->setText(QString :: fromStdString(text));
    text = "Test 1 (" + to_string(e[2].getPercentage())  + "%): ";
    ui->label_3->setText(QString :: fromStdString(text));
    text = "Test 2 (" + to_string(e[3].getPercentage())  + "%): ";
    ui->label_4->setText(QString :: fromStdString(text));
    text = "Test 3 (" + to_string(e[4].getPercentage())  + "%): ";
    ui->label_5->setText(QString :: fromStdString(text));

    ui->QFE->setText( (QString :: number(e[0].get_mark()) ));
    ui->QMT->setText( (QString :: number(e[1].get_mark()) ));
    ui->QT1->setText( (QString :: number(e[2].get_mark()) ));
    ui->QT2->setText( (QString :: number(e[3].get_mark()) ));
    ui->QT3->setText( (QString :: number(e[4].get_mark()) ));

}

EditExam::~EditExam()
{
    delete ui;
}

void EditExam::on_pushButton_clicked()
{
    close();
}


void EditExam::on_pushButton_2_clicked()
{
    try {
        if(ui->QFE->text().toDouble() < 0 || ui->QFE->text().toDouble() > 20
            || ui->QMT->text().toDouble() < 0 || ui->QMT->text().toDouble() > 20
            || ui->QT2->text().toDouble() < 0 || ui->QT1->text().toDouble() > 20
            || ui->QT2->text().toDouble() < 0 || ui->QT2->text().toDouble() > 20
            || ui->QT3->text().toDouble() < 0 || ui->QT3->text().toDouble() > 20){
            throw runtime_error("Error, the mark can not be negative or greater than 20");
        }
    } catch (const runtime_error e) {
        QMessageBox :: warning(this , "Error" , e.what());
        return;
    }

    ss->EditMark(ui->QFE->text().toDouble() , ind , 0);
    ss->EditMark(ui->QMT->text().toDouble() , ind , 1);
    ss->EditMark(ui->QT1->text().toDouble() , ind , 2);
    ss->EditMark(ui->QT2->text().toDouble() , ind , 3);
    ss->EditMark(ui->QT3->text().toDouble() , ind , 4);


    string newLine = to_string(ss->get_year()) + ":";
    for (const course c : ss->get_courses()) {
        for (const exam e : c.get_exams()) {
            newLine += to_string(e.get_mark()) + "/";
        }
            newLine += ",";
    }
    changeLineInFile("examMarks.csv" , fileIndex+1 , newLine);

    if (parentWidget() != nullptr) {
        // parentWidget() returns a pointer to the parent widget (the first window)
        studentview *parentWindow = qobject_cast<studentview*>(parentWidget());
        if (parentWindow != nullptr) {
            parentWindow->update_view();
        }
    }
    close();

}

