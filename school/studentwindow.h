#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include<vector>
#include"mainclasses.h"
using namespace std;

namespace Ui {
class studentwindow;
}

class studentwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit studentwindow(QWidget *parent = nullptr);
    ~studentwindow();
    void update();

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void assigneCourses(int);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_searchButton_clicked();

private:
    Ui::studentwindow *ui;
    vector<student> s;
};

#endif // STUDENTWINDOW_H
