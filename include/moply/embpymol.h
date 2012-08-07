#ifndef EMBPYMOL_H
#define EMBPYMOL_H

#include <Python.h>
#include <string>

class EmbPymol
{
public:
    EmbPymol();
    ~EmbPymol();
    static void printPyObject(PyObject *);
    static char* strPyObject(PyObject *);

    void start();
    void draw();
    void reshape(int w, int h, int f);
    bool idle();
    void drag(int x, int y, int modifiers);
    void button(int button, int state, int x, int y, int modifiers);

    void cmdSet(std::string *command, int arg);
    void cmdButton(std::string *command, std::string *arg1, std::string *arg2);
    void cmdLoad(std::string *fname);

protected:
    void initPymol();
    PyObject* callFunction(PyObject *pObj, const char *, PyObject* args=NULL);
    PyObject* loadModule(std::string *);
    PyObject* instantiateClass(std::string *, PyObject *);

private:
    PyObject *PyMOL;
    PyObject *Cmd;
};

#endif // EMBPYMOL_H
