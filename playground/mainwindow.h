#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <moply/gldrawer.h>
#include <QMainWindow>
#include <QSignalMapper>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void load();
    void render(QString str);
    
private:
    Ui::MainWindow *ui;
    GLDrawer *drawer;
    QAction *loadAction;
    QMenu *fileMenu;
    QSignalMapper *signalMapper;
};

#endif // MAINWINDOW_H
