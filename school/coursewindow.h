#ifndef COURSEWINDOW_H
#define COURSEWINDOW_H

#include <QMainWindow>
#include<vector>
#include"mainclasses.h"
using namespace std;

namespace Ui {
class coursewindow;
}

class coursewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit coursewindow(QWidget *parent = nullptr);
    ~coursewindow();
    void update();

private slots:
    void on_pushButton_6_clicked();

    void on_add_button_clicked();

    void on_remove_button_clicked();

    void on_view_button_clicked();

    void on_searchButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::coursewindow *ui;
    vector<course> c;

};

#endif // COURSEWINDOW_H
