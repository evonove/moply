#include "moply/gldrawer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QSignalMapper>

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
    drawer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->horizontalLayout->insertWidget(0, drawer, 1, 0);

    connect(ui->loadFile, SIGNAL(clicked()), this, SLOT(load()));

    signalMapper = new QSignalMapper(this);

    // mapping components to commands
    signalMapper->setMapping(ui->meshBox, "mesh");
    signalMapper->setMapping(ui->ribbonBox, "ribbon");
    signalMapper->setMapping(ui->linesBox, "lines");
    signalMapper->setMapping(ui->cartoonBox, "cartoon");
    signalMapper->setMapping(ui->nbBox, "nonbonded");
    signalMapper->setMapping(ui->surfaceBox, "surface");
    signalMapper->setMapping(ui->sticksBox, "sticks");

    // connecting checkboxes
    connect(ui->meshBox, SIGNAL(toggled(bool)), signalMapper, SLOT(map()));
    connect(ui->ribbonBox, SIGNAL(toggled(bool)), signalMapper, SLOT(map()));
    connect(ui->linesBox, SIGNAL(toggled(bool)), signalMapper, SLOT(map()));
    connect(ui->cartoonBox, SIGNAL(toggled(bool)), signalMapper, SLOT(map()));
    connect(ui->nbBox, SIGNAL(toggled(bool)), signalMapper, SLOT(map()));
    connect(ui->surfaceBox, SIGNAL(toggled(bool)), signalMapper, SLOT(map()));
    connect(ui->sticksBox, SIGNAL(toggled(bool)), signalMapper, SLOT(map()));

    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(render(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load()
{
    ui->linesBox->setChecked(true);
    ui->nbBox->setChecked(true);
    ui->meshBox->setChecked(false);
    ui->cartoonBox->setChecked(false);
    ui->ribbonBox->setChecked(false);
    ui->surfaceBox->setChecked(false);
    ui->sticksBox->setChecked(false);

    QString fname = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("Mol Files (*.pdb);;All Files (*)"));
    if (fname != "") {
        string _fname = fname.toUtf8().constData();
        drawer->loadFile(&_fname);
    }
    qDebug() << "load action triggered";
}

void MainWindow::render(QString str)
{
    QCheckBox *qcb = (QCheckBox*) signalMapper->mapping(str);
    drawer->render(qcb->isChecked(), str.toUtf8().constData());
}
