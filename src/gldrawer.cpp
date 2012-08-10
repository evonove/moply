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
    QString qs = "_ util.performance(%1)";

    string cmd = qs.arg(level).toStdString();
    embPymol->cmdDo(&cmd);
    _pymolProcess();
}

// pymol specific methods
void GLDrawer::_pymolProcess()
{
    update();
}
