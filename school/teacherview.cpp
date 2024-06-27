#include "teacherview.h"
#include "ui_teacherview.h"
#include<vector>
#include"mainclasses.h"
#include <string>
#include <QString>
using namespace std;

teacherview::teacherview(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::teacherview)
{
    ui->setupUi(this);
}
teacherview :: teacherview(teacher *tt, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::teacherview) , t(tt)
{
    ui->setupUi(this);

    ui->QID->setText(QString :: number(t->get_id()));
    ui->QName->setText(QString :: fromStdString(t->get_name()));
    ui->textBrowser->setText(QString :: fromStdString(t->get_prof_dev()));
    vector<course> c = t->get_courses();
    for (int i = 0; i < c.size(); ++i) {
        ui->listWidget->addItem(QString :: fromStdString(c[i].get_courseName()));
    }
}


teacherview::~teacherview()
{
    delete ui;
}

void teacherview::on_pushButton_clicked()
{
    close();
}

