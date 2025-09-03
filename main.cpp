#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();
    w->resize(700, 600);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    return a.exec();
}
