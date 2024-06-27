#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <QDialog>
#include "mainclasses.h"
#include <vector>
using namespace std;

namespace Ui {
class addstudent;
}

class addstudent : public QDialog
{
    Q_OBJECT

public:
    explicit addstudent(vector<student>* , QWidget *parent = nullptr, int editIndex = -1);
    explicit addstudent(QWidget *parent = nullptr);
    ~addstudent();

private slots:
    //void on_buttonBox_accepted();

    void on_pushButton_clicked();

    void on_cancel_button_clicked();
    bool isIdUsed(int);

private:
    Ui::addstudent *ui;
    vector<student> *s;
    int editI;
};

#endif // ADDSTUDENT_H
