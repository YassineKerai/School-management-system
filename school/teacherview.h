#ifndef TEACHERVIEW_H
#define TEACHERVIEW_H

#include <QDialog>
#include "mainclasses.h"
#include <string>
using namespace std;

namespace Ui {
class teacherview;
}

class teacherview : public QDialog
{
    Q_OBJECT

public:
    explicit teacherview(QWidget *parent = nullptr);
    explicit teacherview(teacher* , QWidget *parent = nullptr);

    ~teacherview();

private slots:
    void on_pushButton_clicked();

private:
    Ui::teacherview *ui;
    teacher *t;
};

#endif // TEACHERVIEW_H
