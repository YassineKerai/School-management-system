#ifndef EXAMWINDOW_H
#define EXAMWINDOW_H

#include <QMainWindow>

namespace Ui {
class ExamWindow;
}

class ExamWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExamWindow(QWidget *parent = nullptr);
    ~ExamWindow();

private:
    Ui::ExamWindow *ui;
};

#endif // EXAMWINDOW_H
