#include <Python.h>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Py_Initialize();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    int ret = a.exec();

    Py_Finalize();
    return ret;
}
