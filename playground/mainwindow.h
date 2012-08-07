#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <moply/gldrawer.h>

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
    
private:
    Ui::MainWindow *ui;
    GLDrawer *drawer;
    QAction *loadAction;
    QMenu *fileMenu;
};

#endif // MAINWINDOW_H
