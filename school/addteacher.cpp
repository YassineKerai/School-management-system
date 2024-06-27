#include "addteacher.h"
#include "ui_addteacher.h"
#include <fstream>
#include <string>
#include "mainclasses.h"
#include<QMessageBox>
#include<exception>
#include <QCheckBox>
#include "teacherwindow.h"
#include <vector>
using namespace std;

addteacher::addteacher(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addteacher)
{
    ui->setupUi(this);
}

addteacher::addteacher(vector<teacher>* tt, QWidget *parent, int editIndex)
    : QDialog(parent)
    , ui(new Ui::addteacher)
    , t(tt)
    , editI(editIndex)
{
    ui->setupUi(this);
    createCheckboxes(); // Call the function to create checkboxes
    if (editIndex != -1) {
        ui->QID->setText(QString::number((*t)[editIndex].get_id()));
        QString profDev = QString::fromStdString((*t)[editIndex].get_prof_dev());
        profDev = profDev.trimmed(); // Remove leading and trailing whitespace, including newline characters
        ui->QPD->setText(profDev);
        //ui->QPD->setText(QString::fromStdString((*t)[editIndex].get_prof_dev()));
        ui->QName->setText(QString::fromStdString((*t)[editIndex].get_name()));
        ui->pushButton->setText("edit");
        vector<course> temp = (*t)[editIndex].get_courses();
        for (int i = 0; i < checkboxes.size(); ++i) {
            for (int j = 0; j < temp.size() ; ++j) {
                if (temp[j].get_courseName() == checkboxes[i]->text().toStdString()) {
                    checkboxes[i]->setChecked(true);
                }
            }
        }
    }
}

addteacher::~addteacher()
{
    delete ui;
    for (auto checkbox : checkboxes) {
        delete checkbox; // Delete each dynamically allocated checkbox
    }
}

void addteacher::on_pushButton_2_clicked()
{
    close();
}

void addteacher::createCheckboxes()
{
    ifstream checkcourse("courseInfo.csv");
    string line , Cinfo[8];
    if (checkcourse.is_open()) {
        while (getline(checkcourse, line)) {
            textSplit(line , Cinfo , ',');
            QCheckBox *checkbox = new QCheckBox(QString::fromStdString(Cinfo[0]), this); // Dynamically allocate QCheckBox
            ui->verticalLayout->addWidget(checkbox);
            checkboxes.push_back(checkbox); // Store the pointer to the checkbox
        }
    }
}

bool addteacher :: isIdUsed(int id){
    for (int i = 0; i < t->size(); ++i) {
        if(id == (*t)[i].get_id() && i != editI)
            return true;
    }
    return false;
}

void addteacher::on_pushButton_clicked()
{
    try {
        if(ui->QID->text().isEmpty() || ui->QName->text().isEmpty()){
            throw runtime_error("Error, please fill all the sells (id and name are mondatory)");
        }
        else if (ui->QID->text().toInt() < 0 || isIdUsed(ui->QID->text().toInt())) {
            throw runtime_error("Error, the id can not be used twice or be negative");
        }
    } catch (const runtime_error& error) {
        QMessageBox :: warning(this , "Error" , error.what());
        return;
    }

    if (editI == -1) {
        if (!ui->QID->text().isEmpty() && !ui->QName->text().isEmpty() && !ui->QPD->toPlainText().isEmpty()) {
            teacher temp;
            temp.set_id(ui->QID->text().toInt());
            temp.set_name(ui->QName->text().toStdString());
            temp.set_prof_dev(ui->QPD->toPlainText().toStdString());

            ofstream TInfo("teacherInfo.csv", ios::app);
            if (TInfo.is_open()) {
                TInfo << temp.get_id() << ",";
                TInfo << temp.get_name() << "\n";
            }
            TInfo.close();
            ofstream TPD("teacherProfessionalDevelopment.txt", ios::app);
            if (TPD.is_open()) {
                TPD << temp.get_prof_dev() << "\n---\n";
            }
            TPD.close();
            //update the table and total students
            ofstream TC("teacherCourses.csv", ios::app);
            if (TC.is_open()) {
                for (auto checkbox : checkboxes) {
                    if (checkbox->isChecked()) {
                        course c;
                        c.set_courseName(checkbox->text().toStdString());
                        temp.add_course(c);
                        TC << checkbox->text().toStdString() << ",";
                    }
                }
                TC << "\n";
                TC.close();
            }
            t->push_back(temp);

            if (parentWidget() != nullptr) {
                // parentWidget() returns a pointer to the parent widget (the first window)
                teacherwindow *parentWindow = qobject_cast<teacherwindow*>(parentWidget());
                if (parentWindow != nullptr) {
                    parentWindow->update();
                }
            }
            close();
        }
    } else {
        (*t)[editI].set_id(ui->QID->text().toInt());
        (*t)[editI].set_prof_dev(ui->QPD->toPlainText().toStdString());
        (*t)[editI].set_name(ui->QName->text().toStdString());
        (*t)[editI].clear_course();
        for (auto checkbox : checkboxes) {
            if (checkbox->isChecked()) {
                course c;
                c.set_courseName(checkbox->text().toStdString());
                (*t)[editI].add_course(c);
            }
        }
        ofstream TInfo("teacherInfo.csv");
        ofstream TPD("teacherProfessionalDevelopment.txt");
        ofstream TC("teacherCourses.csv");

        // Check if all files are open before proceeding
        if (TInfo.is_open() && TPD.is_open() && TC.is_open()) {
            // Rewrite the teacher data to the files, excluding the removed student
            for (size_t i = 0; i < (*t).size(); ++i) {
                TInfo << (*t)[i].get_id() << ",";
                TInfo << (*t)[i].get_name() << "\n";
                TPD << (*t)[i].get_prof_dev() << "\n---\n";
                vector<course> temp = (*t)[i].get_courses();
                for (int j = 0; j < temp.size(); ++j) {
                    if(temp[j].get_courseName() != "")
                        TC << temp[j].get_courseName() << ",";
                }
                TC << "\n";
            }
            // Close the files after writing
            TInfo.close();
            TPD.close();
            TC.close();
        }
        if (parentWidget() != nullptr) {
            // parentWidget() returns a pointer to the parent widget (the first window)
            teacherwindow *parentWindow = qobject_cast<teacherwindow*>(parentWidget());
            if (parentWindow != nullptr) {
                parentWindow->update();
            }
        }
        close();
    }
}
