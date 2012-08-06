#include "moply/gldrawer.h"

GLDrawer::GLDrawer(QWidget *parent, QGLFormat *format) :
    QGLWidget(*format, parent)
{
    _buttonMap[Qt::LeftButton] = 0;
    _buttonMap[Qt::MidButton] = 1;
    _buttonMap[Qt::RightButton] = 2;

    /* init pymol2 in python embedded */
    embPymol = new EmbPymol();
    glInit();

    embPymol->start();
    _pymolProcess();

    // set no external gui
    embPymol->cmdSet("internal_gui", 0);
    embPymol->cmdSet("internal_feedback", 0);
    embPymol->cmdButton("double_left", "None", "None");
    embPymol->cmdButton("single_right", "None", "None");

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
    embPymol->cmdButton("double_left", "None", "None");
    embPymol->cmdButton("single_right", "None", "None");

    embPymol->button(_buttonMap[event->button()], 0, event->x(), height() - event->y(), 0);
    _pymolProcess();
}

void GLDrawer::mouseReleaseEvent(QMouseEvent *event)
{
    embPymol->button(_buttonMap[event->button()], 1, event->x(), height() - event->y(), 0);
    _pymolProcess();
}

// file loading
void GLDrawer::loadFile(std::string fname)
{
    // trying to load a file
    embPymol->cmdLoad(fname);
    embPymol->reshape(width(), height(), 0);
}

// pymol specific methods
void GLDrawer::_pymolProcess()
{
    update();
}
