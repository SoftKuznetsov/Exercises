#include "mainwindow.h"

#include <QApplication>
#include <QFileInfo>

#include "mytcpserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
