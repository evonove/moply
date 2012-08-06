#include "moply/gldrawer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->script->setText("Hi");

    // trying the QGLWidget
    QGLFormat *f = new QGLFormat();
    f->setStencil(true);
    f->setRgba(true);
    f->setDepth(true);
    f->setDoubleBuffer(true);

    GLDrawer *w = new GLDrawer(this, f);
    ui->horizontalLayout->addWidget(w, 1, 0);
    w->loadFile("/home/syn/Scrivania/9LDT-a.pdb");

    GLDrawer *h = new GLDrawer(this, f);
    ui->horizontalLayout->addWidget(h, 1, 0);
    h->loadFile("/home/syn/Scrivania/1GOL.pdb");
}

MainWindow::~MainWindow()
{
    delete ui;
}
