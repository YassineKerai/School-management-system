#include "addcourse.h"
#include "ui_addcourse.h"
#include <vector>
#include "mainclasses.h"
#include <string>
#include <QMessageBox>
#include <exception>
#include "coursewindow.h"
#include <fstream>
using namespace std;

addcourse::addcourse(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addcourse)
{
    ui->setupUi(this);
}

addcourse :: addcourse(vector<course> *cc , QWidget *parent, int editIndex)
    : QDialog(parent)
    , ui(new Ui::addcourse)
    , c(cc)
    , editI(editIndex)
{
    ui->setupUi(this);

    if (editIndex != -1) {
        ui->QCY->setText(QString::number((*c)[editIndex].get_year()));
        ui->QCN->setText(QString::fromStdString((*c)[editIndex].get_courseName()));
        ui->QCC->setText(QString::number((*c)[editIndex].get_coef()));
        vector<exam> e = (*c)[editIndex].get_exams();
        ui->QFE->setText(QString::number(e[0].getPercentage()));
        ui->QMT->setText(QString::number(e[1].getPercentage()));
        ui->QT1->setText(QString::number(e[2].getPercentage()));
        ui->QT2->setText(QString::number(e[3].getPercentage()));
        ui->QT3->setText(QString::number(e[4].getPercentage()));

        ui->pushButton->setText("edit");
    }
}

addcourse::~addcourse()
{
    delete ui;
}

void addcourse::on_pushButton_2_clicked()
{
    close();
}


void addcourse::on_pushButton_clicked()
{
    try {
        if(ui->QCY->text().isEmpty() || ui->QCN->text().isEmpty() || ui->QCC->text().isEmpty()){
            throw runtime_error("Error, please fill all the sells");
        }
        else if(ui->QCY->text().toInt() <=0 || ui->QCY->text().toInt() >5){
            throw runtime_error("Error, course year can not be zero or negative or greater than 5");
        }
        else if (ui->QCC->text().toInt() <= 0) {
            throw runtime_error("Error, course coefficient can not be zero or negative");
        }
        else if (ui->QFE->text().toDouble() < 0 || ui->QFE->text().toDouble() > 100
                   || ui->QMT->text().toDouble() < 0 || ui->QMT->text().toDouble() > 100
                   || ui->QT1->text().toDouble() < 0 || ui->QT1->text().toDouble() > 100
                   || ui->QT2->text().toDouble() < 0 || ui->QT2->text().toDouble() > 100
                   || ui->QT3->text().toDouble() < 0 || ui->QT3->text().toDouble() > 100
                   || (ui->QFE->text().toDouble() + ui->QMT->text().toDouble() + ui->QT1->text().toDouble() + ui->QT2->text().toDouble() + ui->QT3->text().toDouble()) != 100 ) {
            throw runtime_error("Error, exam percentage are not valid (mybe the sum is not 100 or one of the percentage is negative)");
        }
    } catch (const runtime_error& error) {
        QMessageBox :: warning(this , "Error" , error.what());
        return;
    }

    if(editI==-1){
        if (ui->QCN->text()!="" && ui->QCY->text()!="" && ui->QCC->text()!="") {
            course temp;
            temp.set_year(ui->QCY->text().toInt());
            temp.set_courseName(ui->QCN->text().toStdString());
            temp.set_coef(ui->QCC->text().toInt());
            exam p[5];
            p[0].setPercentage(ui->QFE->text().toDouble());
            p[1].setPercentage(ui->QMT->text().toDouble());
            p[2].setPercentage(ui->QT1->text().toDouble());
            p[3].setPercentage(ui->QT2->text().toDouble());
            p[4].setPercentage(ui->QT3->text().toDouble());
            for (int i = 0; i < 5; ++i) {
                temp.add_exam(p[i]);
            }
            c->push_back(temp);
            ofstream CInfo("courseInfo.csv" , ios :: app);
            if (CInfo.is_open()) {
                    CInfo << temp.get_courseName() << ","
                      << temp.get_year() << ","
                      << temp.get_coef() << ",";
                for (auto const e : temp.get_exams()) {
                        CInfo << e.getPercentage() << ",";
                }
                CInfo << "\n";
                }
            CInfo.close();
        }
        if (parentWidget() != nullptr) {
            // parentWidget() returns a pointer to the parent widget (the first window)
            coursewindow *parentWindow = qobject_cast<coursewindow*>(parentWidget());
            if (parentWindow != nullptr) {
                parentWindow->update();
            }
        }
        close();
    }
    else{
        (*c)[editI].set_year(ui->QCY->text().toInt());
        (*c)[editI].set_courseName(ui->QCN->text().toStdString());
        (*c)[editI].set_coef(ui->QCC->text().toInt());
        (*c)[editI].editExamPercentage(0 , ui->QFE->text().toDouble());
        (*c)[editI].editExamPercentage(1 , ui->QMT->text().toDouble());
        (*c)[editI].editExamPercentage(2 , ui->QT1->text().toDouble());
        (*c)[editI].editExamPercentage(3 , ui->QT2->text().toDouble());
        (*c)[editI].editExamPercentage(4 , ui->QT3->text().toDouble());
        ofstream CInfo("courseInfo.csv");

        // Check if the file is open before proceeding
        if (CInfo.is_open()) {
            for (size_t i = 0; i < (c)->size(); ++i) {
                CInfo << (*c)[i].get_courseName() << ",";
                CInfo << (*c)[i].get_year() << ",";
                CInfo << (*c)[i].get_coef() << ",";
                for (auto const e : (*c)[i].get_exams()) {
                    CInfo << e.getPercentage() << ",";
                }
                CInfo << "\n";
            }

            // Close the file after writing
            CInfo.close();
    }
        if (parentWidget() != nullptr) {
            // parentWidget() returns a pointer to the parent widget (the first window)
            coursewindow *parentWindow = qobject_cast<coursewindow*>(parentWidget());
            if (parentWindow != nullptr) {
                parentWindow->update();
            }
        }
        close();
    }
}
