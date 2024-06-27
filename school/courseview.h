#ifndef COURSEVIEW_H
#define COURSEVIEW_H

#include <QDialog>
#include "mainclasses.h"
#include <string>
using namespace std;

namespace Ui {
class courseview;
}

class courseview : public QDialog
{
    Q_OBJECT

public:
    explicit courseview(QWidget *parent = nullptr);
    explicit courseview(course *cc , QWidget *parent = nullptr );

    ~courseview();

private slots:
    void on_pushButton_clicked();

private:
    Ui::courseview *ui;
    course *c;
};

#endif // COURSEVIEW_H
