// compile cmd: "c:\Programing Languages\LLVM\bin\gcc.exe" -Wall -shared -fPIC -I C:\Python312\include -o src/lib/subinterpreter.dll src/lib/src/subinterpreter.c -L C:\Python312\libs -lpython312
#include <Python.h>

static PyObject* create_sub_interpreter(PyObject *self, PyObject *args) {
    PyThreadState* interpreter_state = Py_NewInterpreter();
    if (interpreter_state == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to create new interpreter");
        return NULL;
    }
    return PyLong_FromVoidPtr(interpreter_state);
}

static PyObject* run_code(PyObject *self, PyObject *args) {
    PyThreadState* interpreter_state;
    const char* path_to_compiled_code;
    FILE* file;

    if (!PyArg_ParseTuple(args, "Ls", &interpreter_state, &path_to_compiled_code)) {
        return NULL;
    }

    PyThreadState* old_state = PyThreadState_Swap(interpreter_state);

    file = fopen(path_to_compiled_code, "r");
    if (file == NULL) {
        PyErr_SetString(PyExc_FileNotFoundError, "Cannot open file");
        PyThreadState_Swap(old_state);
        return NULL;
    }

    PyRun_SimpleFile(file, path_to_compiled_code);
    fclose(file);

    PyThreadState_Swap(old_state);

    Py_RETURN_NONE;
}


static PyObject* close_sub_interpreter(PyObject *self, PyObject *args) {
    PyThreadState* interpreter_state;

    if (!PyArg_ParseTuple(args, "L", &interpreter_state)) {
        return NULL;
    }

    PyThreadState_Swap(interpreter_state);
    Py_EndInterpreter(interpreter_state);

    Py_RETURN_NONE;
}

static PyMethodDef SubInterpreterMethods[] = {
    {"create_sub_interpreter", create_sub_interpreter, METH_NOARGS, "Create a new sub-interpreter"},
    {"run_code", run_code, METH_VARARGS, "Run code in a sub-interpreter"},
    {"close_sub_interpreter", close_sub_interpreter, METH_VARARGS, "Close a sub-interpreter"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef subinterpretermodule = {
    PyModuleDef_HEAD_INIT,
    "subinterpreter",
    NULL,
    -1,
    SubInterpreterMethods
};

PyMODINIT_FUNC PyInit_subinterpreter(void) {
    return PyModule_Create(&subinterpretermodule);
}


// match [/]+.*
// \/\*(\*(?!\/)|[^*])*\*\/

