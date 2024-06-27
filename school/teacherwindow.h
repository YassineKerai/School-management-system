#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QMainWindow>
#include<vector>
#include"mainclasses.h"
using namespace std;

namespace Ui {
class teacherwindow;
}

class teacherwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit teacherwindow(QWidget *parent = nullptr);
    ~teacherwindow();
    void update();

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_remove_button_clicked();

    void on_pushButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::teacherwindow *ui;
    vector<teacher> t;
};

#endif // TEACHERWINDOW_H
