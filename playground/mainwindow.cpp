#include "moply/gldrawer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadAction = new QAction(tr("&Load"), this);
    connect(loadAction, SIGNAL(triggered()), this, SLOT(load()));

    // add menu action
    fileMenu = ui->menuBar->addMenu(tr("&File"));
    fileMenu->addAction(loadAction);

    // set up QGLFormat
    QGLFormat *f = new QGLFormat();
    f->setStencil(true);
    f->setRgba(true);
    f->setDepth(true);
    f->setDoubleBuffer(true);

    drawer = new GLDrawer(this, f);
    ui->verticalLayout->insertWidget(0, drawer, 1, 0);

    connect(ui->loadFile, SIGNAL(clicked()), this, SLOT(load()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load()
{
    QString fname = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("Mol Files (*.pdb);;All Files (*)"));
    if (fname != "") {
        string _fname = fname.toUtf8().constData();
        drawer->loadFile(&_fname);
    }
    qDebug() << "load action triggered";
}
