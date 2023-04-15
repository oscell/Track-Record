#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString serverAddress = "192.168.181.153";
    MainWindow w(nullptr, serverAddress);
    w.show();
    return a.exec();
}
