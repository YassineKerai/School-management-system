#include "mainwindow.h"

#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile StyleSheetFile("./Remover.qss");
    StyleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(StyleSheetFile.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
