#ifndef EDITEXAM_H
#define EDITEXAM_H

#include <QDialog>
#include<vector>
#include"mainclasses.h"

using namespace std;

namespace Ui {
class EditExam;
}

class EditExam : public QDialog
{
    Q_OBJECT

public:
    explicit EditExam(QWidget *parent = nullptr);
    explicit EditExam(student* , int i , int Fi , QWidget *parent = nullptr );
    ~EditExam();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::EditExam *ui;
    student *ss;
    int ind , fileIndex;
};

#endif // EDITEXAM_H
