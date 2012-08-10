#ifndef EMBPYMOL_H
#define EMBPYMOL_H

#include <Python.h>
#include <string>

class EmbPymol
{
public:
    EmbPymol(int finalize=0);
    ~EmbPymol();
    static void printPyObject(PyObject *);
    static char* strPyObject(PyObject *);
    static void lazyPyInit();
    static void lazyPyFinal();

    void start();
    void draw();
    void reshape(int w, int h, int f);
    bool idle();
    void drag(int x, int y, int modifiers);
    void button(int button, int state, int x, int y, int modifiers);
    void performance(int level);

    void cmdSet(std::string *command, int arg);
    void cmdButton(std::string *command, std::string *arg1, std::string *arg2);
    void cmdLoad(std::string *fname);
    void cmdReinit();

    // rendering options
    void cmdRendering(bool enable, std::string *name);

protected:
    void initPymol();
    PyObject* callFunction(PyObject *pObj, const char *, PyObject* args=NULL);
    PyObject* loadModule(std::string *);
    PyObject* instantiateClass(std::string *, PyObject *, PyObject *args);

private:
    PyObject *PyMOL;
    PyObject *Cmd;

    int finalize;
};

#endif // EMBPYMOL_H
