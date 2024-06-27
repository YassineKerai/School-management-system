#include "addstudent.h"
#include "ui_addstudent.h"
#include"mainclasses.h"
#include"mainclasses.h"
#include<fstream>
#include "studentwindow.h"
#include <cstdio>
#include<QMessageBox>
#include<exception>
#include <string>
using namespace std;



addstudent::addstudent(QWidget *parent )
    : QDialog(parent)
    , ui(new Ui::addstudent)
{
    ui->setupUi(this);
}

addstudent::addstudent(vector<student> *ss, QWidget *parent , int editIndex)
    : QDialog(parent)
    , ui(new Ui::addstudent) , s(ss) ,editI(editIndex)
{
    ui->setupUi(this);
    if(editIndex !=-1){
        ui->QID->setText(QString :: number((*s)[editIndex].get_id()));
        ui->QYear->setText(QString :: number((*s)[editIndex].get_year()));
        ui->QName->setText(QString :: fromStdString((*s)[editIndex].get_name()));
        ui->QGroup->setText(QString :: number((*s)[editIndex].get_group()));
        ui->pushButton->setText("edit");
    }
}

addstudent::~addstudent()
{
    delete ui;
}

bool addstudent :: isIdUsed(int id){
    for (int i = 0; i < s->size(); ++i) {
        if(id == (*s)[i].get_id() && i != editI)
            return true;
    }
    return false;
}

void addstudent::on_pushButton_clicked()
{
    try {
        if(ui->QID->text().isEmpty()|| ui->QName->text().isEmpty() || ui->QYear->text().isEmpty() || ui->QGroup->text().isEmpty()){
            throw runtime_error("Error, please fill all the sells");
        }
        else if (ui->QID->text().toInt() < 0 || isIdUsed(ui->QID->text().toInt())) {
            throw runtime_error("Error, the id can not be used twice or be negative");
        }
        else if (ui->QGroup->text().toInt() <= 0) {
            throw runtime_error("Error, the group can not be 0 or negative");
        }
        else if (ui->QYear->text().toInt() <= 0 || ui->QYear->text().toInt() > 5) {
            throw runtime_error("Error, the studied year can not be 0 or negative greater than 5");
        }
    } catch (const runtime_error& error) {
        QMessageBox :: warning(this , "Error" , error.what());
        return;
    }

    if(editI==-1){
        if (ui->QID->text()!="" && ui->QName->text()!="" && ui->QYear->text()!="" && ui->QGroup->text() != "") {
            student temp;
            temp.set_id(ui->QID->text().toInt());
            temp.set_name(ui->QName->text().toStdString());
            temp.set_year(ui->QYear->text().toInt());
            temp.set_group(ui->QGroup->text().toInt());
            s->push_back(temp);
            ofstream SInfo("studentInfo.csv" , ios::app);
            if (SInfo.is_open()) {
                SInfo << temp.get_id() << ",";
                SInfo << temp.get_name() << ",";
                SInfo << temp.get_year() << ",";
                SInfo << temp.get_group() << "\n";
            }
            SInfo.close();
            if (parentWidget() != nullptr) {
                // parentWidget() returns a pointer to the parent widget (the first window)
                studentwindow *parentWindow = qobject_cast<studentwindow*>(parentWidget());//downcasting
                if (parentWindow != nullptr) {
                    parentWindow->update();
                }
            }
            close();

        }
    }
    else{
        string prev_file = to_string((*s)[editI].get_id()) + (*s)[editI].get_name() + ".txt";
        (*s)[editI].set_id(ui->QID->text().toInt());
        (*s)[editI].set_year(ui->QYear->text().toInt());
        (*s)[editI].set_name(ui->QName->text().toStdString());
        (*s)[editI].set_group(ui->QGroup->text().toInt());
        ofstream SInfo("studentInfo.csv");
        // Check if all files are open before proceeding
        if (SInfo.is_open()) {
            // Rewrite the student data to the files, excluding the removed student
            for (size_t i = 0; i < s->size(); ++i) {
                //the informations is stored like this id,name,year,group
                SInfo << (*s)[i].get_id() << ",";
                SInfo << (*s)[i].get_name() << ",";
                SInfo << (*s)[i].get_year() << ",";
                SInfo << (*s)[i].get_group() << "\n";
            }

            // Close the files after writing
            SInfo.close();
            if (parentWidget() != nullptr) {
                // parentWidget() returns a pointer to the parent widget (the first window)
                studentwindow *parentWindow = qobject_cast<studentwindow*>(parentWidget());
                if (parentWindow != nullptr) {
                    parentWindow->update();
                }
            }
            close();
        }

    }
}

void addstudent::on_cancel_button_clicked()
{
    close();
}

