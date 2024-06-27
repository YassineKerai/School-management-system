#ifndef ADDTEACHER_H
#define ADDTEACHER_H

#include <QDialog>
#include <QCheckBox>
#include <vector>
#include "mainclasses.h"
using namespace std;

namespace Ui {
class addteacher;
}

class addteacher : public QDialog
{
    Q_OBJECT

public:
    explicit addteacher(QWidget *parent = nullptr);
    explicit addteacher(vector<teacher>* , QWidget *parent = nullptr , int editIndex = -1);
    bool isIdUsed(int);

    ~addteacher();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::addteacher *ui;
    vector<QCheckBox*> checkboxes; // Vector to store pointers to checkboxes
    vector<teacher> *t;
    int editI;

    void createCheckboxes(); // Function to create checkboxes dynamically
};

#endif // ADDTEACHER_H
