#ifndef STUDENTVIEW_H
#define STUDENTVIEW_H

#include <QDialog>
#include "mainclasses.h"
#include <string>
using namespace std;

namespace Ui {
class studentview;
}

class studentview : public QDialog
{
    Q_OBJECT

public:
    explicit studentview(QWidget *parent = nullptr);
    explicit studentview(student* , QWidget *parent = nullptr  , int ind = 0);
    void update_view();
    ~studentview();

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_2_clicked();

private:
    Ui::studentview *ui;
    student *s;
    int index;

};

#endif // STUDENTVIEW_H
