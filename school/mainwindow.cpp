#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "studentwindow.h"
#include "teacherwindow.h"
#include "coursewindow.h"
#include"aboutapp.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    studentwindow *sw = new studentwindow();
    sw->show();
    close();

}


void MainWindow::on_pushButton_4_clicked()
{
    teacherwindow* tw = new teacherwindow();
    tw->show();
    close();
}


void MainWindow::on_pushButton_3_clicked()
{
    coursewindow* cw = new coursewindow();
    cw->show();
    close();
}


void MainWindow::on_pushButton_5_clicked()
{
    AboutApp *aa = new AboutApp(this);
    aa->show();
}

