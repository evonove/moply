#include <moply/embpymol.h>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    int ret = a.exec();
    EmbPymol::lazyPyFinal();

    return ret;
}
