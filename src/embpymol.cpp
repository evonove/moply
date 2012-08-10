#include "moply/embpymol.h"
#include <QDebug>

using namespace std;

EmbPymol::EmbPymol(int finalize)
{
    // This Finalize the python interpreter on class destruction
    this->finalize = finalize;

    EmbPymol::lazyPyInit();

    // add custom pymol path to sys.path
    PyObject* sys = PyImport_ImportModule("sys");
    PyObject* path = PyObject_GetAttrString(sys, "path");

    // yes.. it's hardcoded!!!!
    PyList_Append(path, PyString_FromString("/home/syn/.virtualenvs/pymol/lib/python2.7/site-packages"));

    Py_DECREF(sys);
    Py_DECREF(path);

    // initialize pymol objects
    initPymol();
}

EmbPymol::~EmbPymol()
{
    Py_XDECREF(PyMOL);
    Py_XDECREF(Cmd);

    if (finalize) EmbPymol::lazyPyFinal();
}

/* pymol call wrappers */
void EmbPymol::start()
{
    callFunction(PyMOL, "start");
}

void EmbPymol::draw()
{
    callFunction(PyMOL, "draw");
}

void EmbPymol::reshape(int width, int height, int force)
{
    PyObject *args = Py_BuildValue("iii", width, height, force);
    callFunction(PyMOL, "reshape", args);

    Py_DECREF(args);
}

bool EmbPymol::idle()
{
    int ret;

    PyObject *pRet = callFunction(PyMOL, "idle");
    PyArg_Parse(pRet, "i", &ret);

    return ret;
}

void EmbPymol::drag(int x, int y, int modifiers)
{
    PyObject *args = Py_BuildValue("iii", x, y, modifiers);
    callFunction(PyMOL, "drag", args);

    Py_DECREF(args);
}

void EmbPymol::button(int button, int state, int x, int y, int modifiers)
{
    PyObject *args = Py_BuildValue("iiiii", button, state, x, y, modifiers);
    callFunction(PyMOL, "button", args);

    Py_DECREF(args);
}

void EmbPymol::cmdSet(string *command, int arg)
{
    PyObject *args = Py_BuildValue("si", command->c_str(), arg);
    callFunction(Cmd, "set", args);

    Py_DECREF(args);
}

void EmbPymol::cmdDo(string *command)
{
    PyObject *args = Py_BuildValue("(s)", command->c_str());
    callFunction(Cmd, "do", args);

    Py_DECREF(args);
}

void EmbPymol::cmdButton(string *command, string *arg1, string *arg2)
{
    PyObject *args = Py_BuildValue("sss", command->c_str(), arg1->c_str(), arg2->c_str());
    callFunction(Cmd, "button", args);

    Py_DECREF(args);
}

void EmbPymol::cmdLoad(string *fname)
{
    PyObject *args = Py_BuildValue("(s)", fname->c_str());
    callFunction(Cmd, "load", args);

    Py_XDECREF(args);
}

void EmbPymol::cmdReinit()
{
    callFunction(Cmd, "reinitialize");
}

// rendering options
void EmbPymol::cmdRendering(bool enable, string *name)
{
    string command = (enable) ? "show" : "hide";

    PyObject *args = Py_BuildValue("(s)", name->c_str());
    callFunction(Cmd, command.c_str(), args);

    Py_XDECREF(args);
}

PyObject* EmbPymol::callFunction(PyObject* pObj, const char *funcName, PyObject *args)
{
    // pObj and args are borrowed references
    PyObject *ret = NULL, *pFunc;

    pFunc = PyObject_GetAttrString(pObj, funcName);
    if (pFunc != NULL) {
        ret = PyObject_CallObject(pFunc, args);
        qDebug() << "call to function " << funcName << " with args: " << strPyObject(args);

        Py_DECREF(pFunc);
    }
    if (PyErr_Occurred())
        PyErr_Print();

    return ret;
}

/* init functions */
void EmbPymol::initPymol()
{
    string pymol2 = "pymol2";
    PyObject *pModule = loadModule(&pymol2);

    if (pModule != NULL) {
        PyObject *args = Py_BuildValue("(s)", "presentation");

        string className = "PyMOL";
        PyMOL = instantiateClass(&className, pModule, args); // borrowing a reference to pModule
        /* error check for missing PyMOL omitted */

        Cmd = PyObject_GetAttrString(PyMOL, "cmd");

        Py_DECREF(pModule);
    }
}

PyObject *EmbPymol::instantiateClass(string *className, PyObject *pModule, PyObject *args)
{
    PyObject *pClass, *pObj;

    pClass = PyObject_GetAttrString(pModule, className->c_str());
    if (pClass && PyClass_Check(pClass)) {
        pObj = PyInstance_New(pClass, args, NULL);

        Py_DECREF(pClass);

        return pObj;
    } else {
        PyErr_Print();
        qDebug() << "Can't find a class wiht name " << className;
    }

    Py_XDECREF(pClass);
    return NULL;
}

PyObject *EmbPymol::loadModule(string *moduleName)
{
    PyObject *pModule, *pName;
    pName = PyString_FromString(moduleName->c_str());

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule == NULL) {
        PyErr_Print();
        qDebug() << "Failed to load " << moduleName;
    }

    return pModule;
}

/* static methods */
void EmbPymol::printPyObject(PyObject *pyObj)
{
    qDebug() << "Your object is:\n" << strPyObject(pyObj);
}

char* EmbPymol::strPyObject(PyObject *pyObj)
{
    char* s = (char*) "";

    PyObject *objStr = PyObject_Str(pyObj);
    if (objStr != NULL) {
        s = PyString_AsString(objStr);
        Py_DECREF(objStr);
    }

    return s;
}

void EmbPymol::lazyPyInit()
{
    if (!Py_IsInitialized())
        Py_Initialize();
}

void EmbPymol::lazyPyFinal()
{
    if (Py_IsInitialized())
        Py_Finalize();
}

