#include "courseview.h"
#include "ui_courseview.h"
#include <string>
#include <mainclasses.h>
#include <fstream>
#include <vector>
courseview::courseview(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::courseview)
{
    ui->setupUi(this);
}

courseview::courseview(course *cc , QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::courseview) , c(cc)
{
    ui->setupUi(this);
    ui->QCN->setText(QString :: fromStdString(c->get_courseName()));
    ui->QCY->setText(QString :: number(c->get_year()));
    ui->QCC->setText(QString :: number(c->get_coef()));
    vector<exam> e = c->get_exams();
    ui->QFE->setText(QString::number(e[0].getPercentage()));
    ui->QMT->setText(QString::number(e[1].getPercentage()));
    ui->QT1->setText(QString::number(e[2].getPercentage()));
    ui->QT2->setText(QString::number(e[3].getPercentage()));
    ui->QT3->setText(QString::number(e[4].getPercentage()));
    ifstream Tcourses("teacherCourses.csv");
    ifstream TInfo("teacherInfo.csv");
    string line1,line2;
    if(Tcourses.is_open() && TInfo.is_open())
        while(getline(Tcourses , line1)){
            getline(TInfo , line2);
            string courses[15] , Tname[2];
            textSplit(line2 , Tname , ',');
            int size = textSplit(line1 , courses , ',');
            for (int i = 0; i < size; ++i) {
                if(c->get_courseName() == courses[i]){
                    c->add_teach(Tname[1]);
                }
            }
        }
    TInfo.close();
    Tcourses.close();
    vector<string> teach = c->get_teachers();
    c->clear_teacher_vector();//to remove duplicate when close the window and open it again
    for (int i = 0; i < teach.size(); ++i) {
        ui->listWidget->addItem(QString :: fromStdString(teach[i]));
    }
}

courseview::~courseview()
{
    delete ui;
}

void courseview::on_pushButton_clicked()
{
    close();
}

