#ifndef GLDRAWER_H
#define GLDRAWER_H

#include <QGLWidget>
#include <QMouseEvent>
#include <map>

class EmbPymol;

class GLDrawer : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDrawer(QWidget *parent = 0, QGLFormat *format = 0, int finalize = 0);
    ~GLDrawer();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    static QString getPymolFileSelector();

signals:
    
public slots:
    void _pymolProcess();
    void loadFile(std::string *fname);
    void render(bool enable, std::string type);
    void sequence(bool show);
    void quality(int level);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    EmbPymol *embPymol;

    std::map<int, int> _buttonMap;
};

#endif // GLDRAWER_H
