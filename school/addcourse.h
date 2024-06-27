#ifndef ADDCOURSE_H
#define ADDCOURSE_H

#include <QDialog>
#include <vector>
#include "mainclasses.h"
#include <string>
using namespace std;

namespace Ui {
class addcourse;
}

class addcourse : public QDialog
{
    Q_OBJECT

public:
    explicit addcourse(QWidget *parent = nullptr);
    explicit addcourse(vector<course>* , QWidget *parent = nullptr , int editIndex = -1);

    ~addcourse();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::addcourse *ui;
    vector<course> *c;
    int editI;
};

#endif // ADDCOURSE_H
