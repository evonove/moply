#include "moply/gldrawer.h"
#include "moply/embpymol.h"

using namespace std;

GLDrawer::GLDrawer(QWidget *parent, QGLFormat *format, int finalize) :
    QGLWidget(*format, parent)
{
    _buttonMap[Qt::LeftButton] = 0;
    _buttonMap[Qt::MidButton] = 1;
    _buttonMap[Qt::RightButton] = 2;

    /* init pymol2 in python embedded */
    embPymol = new EmbPymol(finalize);
    glInit();

    embPymol->start();
    _pymolProcess();

    // set no external gui
    string c1 = "double_left";
    string c2 = "single_right";
    string x = "None";
    embPymol->cmdButton(&c1, &x, &x);
    embPymol->cmdButton(&c2, &x, &x);

    resizeGL(width(), height());
}

GLDrawer::~GLDrawer()
{
    delete embPymol;
}

QSize GLDrawer::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLDrawer::sizeHint() const
{
    return QSize(400, 400);
}

void GLDrawer::initializeGL()
{
}

void GLDrawer::resizeGL(int width, int height)
{
    embPymol->reshape(width, height, 1);
    _pymolProcess();
}

void GLDrawer::paintGL()
{
    glViewport(0, 0, width(), height());
    embPymol->idle();
    embPymol->draw();
}

// mouse events handling
void GLDrawer::mouseMoveEvent(QMouseEvent *event)
{
    embPymol->drag(event->x(), height() - event->y(), 0);
    _pymolProcess();
}

void GLDrawer::mousePressEvent(QMouseEvent *event)
{
    string c1 = "double_left";
    string c2 = "single_right";
    string x = "None";
    embPymol->cmdButton(&c1, &x, &x);
    embPymol->cmdButton(&c2, &x, &x);

    embPymol->button(_buttonMap[event->button()], 0, event->x(), height() - event->y(), 0);
    _pymolProcess();
}

void GLDrawer::mouseReleaseEvent(QMouseEvent *event)
{
    embPymol->button(_buttonMap[event->button()], 1, event->x(), height() - event->y(), 0);
    _pymolProcess();
}

// file loading
void GLDrawer::loadFile(std::string *fname)
{
    embPymol->cmdReinit();

    // trying to load a file
    embPymol->cmdLoad(fname);
    embPymol->reshape(width(), height(), 0);
}

void GLDrawer::render(bool enable, string type)
{
    embPymol->cmdRendering(enable, &type);
    _pymolProcess();
}

void GLDrawer::sequence(bool show)
{
    string cmd = "seq_view";
    embPymol->cmdSet(&cmd, show);
    _pymolProcess();
}

void GLDrawer::quality(int level)
{
    embPymol->performance(level);
    _pymolProcess();
}

// pymol specific methods
void GLDrawer::_pymolProcess()
{
    update();
}

// statics
QString GLDrawer::getPymolFileSelector()
{
    // TODO: follows the list of pymol accepted formats
    //    [("All Readable","*.pdb"),
    //                   ("All Readable","*.pdb1"),
    //                   ("All Readable","*.ccp4"),
    //                   ("All Readable","*.xplor"),
    //                   ("All Readable","*.mol"),
    //                   ("All Readable","*.mol2"),
    //                   ("All Readable","*.sdf"),
    //                   ("All Readable","*.xyz"),
    //                   ("All Readable","*.r3d"),
    //                   ("All Readable","*.cc1"),
    //                   ("All Readable","*.cc2"),
    //                   ("All Readable","*.ent"),
    //                   ("All Readable","*.dat"),
    //                   ("All Readable","*.out"),
    //                   ("All Readable","*.mmd"),
    //                   ("All Readable","*.mmod"),
    //                   ("All Readable","*.pse"),
    //                   ("All Readable","*.psw"),
    //                   ("All Readable","*.phi"),
    //                   ("All Readable","*.fld"),
    //                   ("All Readable","*.grd"),
    //                   ("All Readable","*.o"),
    //                   ("All Readable","*.omap"),
    //                   ("All Readable","*.brix"),
    //                   ("All Readable","*.dx"),
    //                   ("All Readable","*.pqr"),
    //                   ("All Readable","*.p5m"),
    //                   ("All Readable","*.p1m"),
    //                   ("All Readable","*.cube"),
    //                   ("All Readable","*.cif"),
    //                   ("All Readable","*.moe"), # proprietary format
    //                   ("All Readable","*.mae"), # proprietary format
    //                   ("All Readable","*.fasta"),
    //                   ("All Readable","*.aln"),
    //                   ("All Readable","*.acnt"),
    //                   #("All Readable","*.mtz"),
    //                   ("PDB File","*.pdb"),
    //                   ("PDB1 File","*.pdb1"),
    //                   ("All Files","*.*"),
    //                   ("All Files","*"),
    //                   ("PDB File","*.ent"),
    //                   ("PyMOL Session","*.pse"),
    //                   ("PyMOL Show","*.psw"),
    //                   ("CCP4 Map","*.ccp4"),
    //                   ("XPLOR Map","*.xplor"),
    //                   ("MOL2/Multi-MOL2","*.mol2"),
    //                   ("Macromodel File","*.dat"),
    //                   ("Macromodel File","*.out"),
    //                   ("Macromodel File","*.mmd"),
    //                   ("Macromodel File","*.mmod"),
    //   #                ("MTZ Reflection File","*.mtz"),
    //                   ("BRIX/O Map","*.o"),
    //                   ("BRIX/O Map","*.omap"),
    //                   ("BRIX/O Map","*.brix"),
    //                   ("CIF","*.cif"),
    //                   ("Gaussian Cube Map","*.cube"),
    //                   ("DX Map","*.dx"),
    //                   ("AVS (MEAD) Field","*.fld"),
    //                   ("MOL File","*.mol"),
    //                   ("MOE File","*.moe"), # proprietary format
    //                   ("MAE File","*.mae"), # proprietary format
    //                   ("ChemPy Model","*.pkl"),
    //                   ("Raster3D Scene","*.r3d"),
    //                   ("SDF File","*.sdf"),
    //                   ("ChemDraw3D File","*.cc1"),
    //                   ("ChemDraw3D File","*.cc2"),
    //                   ("XYZ File","*.xyz"),
    //                   ("Fasta File","*.fasta"),
    //                   ("CLUSTAL file","*.aln"),
    //                   ("ACNT Map","*.acnt"),
}
