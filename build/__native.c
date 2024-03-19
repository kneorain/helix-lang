#include "init.c"
#include "getargs.c"
#include "getargsfast.c"
#include "int_ops.c"
#include "float_ops.c"
#include "str_ops.c"
#include "bytes_ops.c"
#include "list_ops.c"
#include "dict_ops.c"
#include "set_ops.c"
#include "tuple_ops.c"
#include "exc_ops.c"
#include "misc_ops.c"
#include "generic_ops.c"
#include "__native.h"
#include "__native_internal.h"

static PyObject *test_env_setup(PyTypeObject *type);
PyObject *CPyDef_test_env(void);

static PyObject *
test_env_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    if (type != CPyType_test_env) {
        PyErr_SetString(PyExc_TypeError, "interpreted classes cannot inherit from compiled");
        return NULL;
    }
    return test_env_setup(type);
}

static int
test_env_traverse(test___test_envObject *self, visitproc visit, void *arg)
{
    Py_VISIT(self->___mypyc_self__);
    Py_VISIT(self->_transpose);
    Py_VISIT(self->_multiply_matrix);
    Py_VISIT(self->_mat1);
    Py_VISIT(self->_mat2);
    return 0;
}

static int
test_env_clear(test___test_envObject *self)
{
    Py_CLEAR(self->___mypyc_self__);
    Py_CLEAR(self->_transpose);
    Py_CLEAR(self->_multiply_matrix);
    Py_CLEAR(self->_mat1);
    Py_CLEAR(self->_mat2);
    return 0;
}

static void
test_env_dealloc(test___test_envObject *self)
{
    PyObject_GC_UnTrack(self);
    CPy_TRASHCAN_BEGIN(self, test_env_dealloc)
    test_env_clear(self);
    Py_TYPE(self)->tp_free((PyObject *)self);
    CPy_TRASHCAN_END(self)
}

static CPyVTableItem test_env_vtable[1];
static bool
CPyDef_test_env_trait_vtable_setup(void)
{
    CPyVTableItem test_env_vtable_scratch[] = {
        NULL
    };
    memcpy(test_env_vtable, test_env_vtable_scratch, sizeof(test_env_vtable));
    return 1;
}

static PyMethodDef test_env_methods[] = {
    {"__setstate__", (PyCFunction)CPyPickle_SetState, METH_O, NULL},
    {"__getstate__", (PyCFunction)CPyPickle_GetState, METH_NOARGS, NULL},
    {NULL}  /* Sentinel */
};

static PyTypeObject CPyType_test_env_template_ = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "test_env",
    .tp_new = test_env_new,
    .tp_dealloc = (destructor)test_env_dealloc,
    .tp_traverse = (traverseproc)test_env_traverse,
    .tp_clear = (inquiry)test_env_clear,
    .tp_methods = test_env_methods,
    .tp_basicsize = sizeof(test___test_envObject),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HEAPTYPE | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC,
};
static PyTypeObject *CPyType_test_env_template = &CPyType_test_env_template_;

static PyObject *
test_env_setup(PyTypeObject *type)
{
    test___test_envObject *self;
    self = (test___test_envObject *)type->tp_alloc(type, 0);
    if (self == NULL)
        return NULL;
    self->vtable = test_env_vtable;
    return (PyObject *)self;
}

PyObject *CPyDef_test_env(void)
{
    PyObject *self = test_env_setup(CPyType_test_env);
    if (self == NULL)
        return NULL;
    return self;
}


static PyObject *CPyDunder___get__transpose_test_obj(PyObject *self, PyObject *instance, PyObject *owner) {
    instance = instance ? instance : Py_None;
    return CPyDef_transpose_test_obj_____get__(self, instance, owner);
}
static PyObject *transpose_test_obj_setup(PyTypeObject *type);
PyObject *CPyDef_transpose_test_obj(void);

static PyObject *
transpose_test_obj_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    if (type != CPyType_transpose_test_obj) {
        PyErr_SetString(PyExc_TypeError, "interpreted classes cannot inherit from compiled");
        return NULL;
    }
    return transpose_test_obj_setup(type);
}

static int
transpose_test_obj_traverse(test___transpose_test_objObject *self, visitproc visit, void *arg)
{
    Py_VISIT(self->___mypyc_env__);
    _PyObject_VisitManagedDict((PyObject *)self, visit, arg);
    return 0;
}

static int
transpose_test_obj_clear(test___transpose_test_objObject *self)
{
    Py_CLEAR(self->___mypyc_env__);
    _PyObject_ClearManagedDict((PyObject *)self);
    return 0;
}

static void
transpose_test_obj_dealloc(test___transpose_test_objObject *self)
{
    PyObject_GC_UnTrack(self);
    CPy_TRASHCAN_BEGIN(self, transpose_test_obj_dealloc)
    transpose_test_obj_clear(self);
    Py_TYPE(self)->tp_free((PyObject *)self);
    CPy_TRASHCAN_END(self)
}

static CPyVTableItem transpose_test_obj_vtable[2];
static bool
CPyDef_transpose_test_obj_trait_vtable_setup(void)
{
    CPyVTableItem transpose_test_obj_vtable_scratch[] = {
        (CPyVTableItem)CPyDef_transpose_test_obj_____call__,
        (CPyVTableItem)CPyDef_transpose_test_obj_____get__,
    };
    memcpy(transpose_test_obj_vtable, transpose_test_obj_vtable_scratch, sizeof(transpose_test_obj_vtable));
    return 1;
}

static PyObject *
transpose_test_obj_get___3_mypyc_env__(test___transpose_test_objObject *self, void *closure);
static int
transpose_test_obj_set___3_mypyc_env__(test___transpose_test_objObject *self, PyObject *value, void *closure);

static PyGetSetDef transpose_test_obj_getseters[] = {
    {"__mypyc_env__",
     (getter)transpose_test_obj_get___3_mypyc_env__, (setter)transpose_test_obj_set___3_mypyc_env__,
     NULL, NULL},
    {"__dict__", PyObject_GenericGetDict, PyObject_GenericSetDict},
    {NULL}  /* Sentinel */
};

static PyMethodDef transpose_test_obj_methods[] = {
    {"__call__",
     (PyCFunction)CPyPy_transpose_test_obj_____call__,
     METH_FASTCALL | METH_KEYWORDS, NULL},
    {"__get__",
     (PyCFunction)CPyPy_transpose_test_obj_____get__,
     METH_FASTCALL | METH_KEYWORDS, NULL},
    {"__setstate__", (PyCFunction)CPyPickle_SetState, METH_O, NULL},
    {"__getstate__", (PyCFunction)CPyPickle_GetState, METH_NOARGS, NULL},
    {NULL}  /* Sentinel */
};

static PyTypeObject CPyType_transpose_test_obj_template_ = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "transpose_test_obj",
    .tp_new = transpose_test_obj_new,
    .tp_dealloc = (destructor)transpose_test_obj_dealloc,
    .tp_traverse = (traverseproc)transpose_test_obj_traverse,
    .tp_clear = (inquiry)transpose_test_obj_clear,
    .tp_getset = transpose_test_obj_getseters,
    .tp_methods = transpose_test_obj_methods,
    .tp_call = PyVectorcall_Call,
    .tp_descr_get = CPyDunder___get__transpose_test_obj,
    .tp_basicsize = sizeof(test___transpose_test_objObject),
    .tp_vectorcall_offset = offsetof(test___transpose_test_objObject, vectorcall),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HEAPTYPE | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC | _Py_TPFLAGS_HAVE_VECTORCALL | Py_TPFLAGS_MANAGED_DICT,
};
static PyTypeObject *CPyType_transpose_test_obj_template = &CPyType_transpose_test_obj_template_;

static PyObject *
transpose_test_obj_setup(PyTypeObject *type)
{
    test___transpose_test_objObject *self;
    self = (test___transpose_test_objObject *)type->tp_alloc(type, 0);
    if (self == NULL)
        return NULL;
    self->vtable = transpose_test_obj_vtable;
    self->vectorcall = CPyPy_transpose_test_obj_____call__;
    return (PyObject *)self;
}

PyObject *CPyDef_transpose_test_obj(void)
{
    PyObject *self = transpose_test_obj_setup(CPyType_transpose_test_obj);
    if (self == NULL)
        return NULL;
    return self;
}

static PyObject *
transpose_test_obj_get___3_mypyc_env__(test___transpose_test_objObject *self, void *closure)
{
    if (unlikely(self->___mypyc_env__ == NULL)) {
        PyErr_SetString(PyExc_AttributeError,
            "attribute '__mypyc_env__' of 'transpose_test_obj' undefined");
        return NULL;
    }
    CPy_INCREF(self->___mypyc_env__);
    PyObject *retval = self->___mypyc_env__;
    return retval;
}

static int
transpose_test_obj_set___3_mypyc_env__(test___transpose_test_objObject *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_AttributeError,
            "'transpose_test_obj' object attribute '__mypyc_env__' cannot be deleted");
        return -1;
    }
    if (self->___mypyc_env__ != NULL) {
        CPy_DECREF(self->___mypyc_env__);
    }
    PyObject *tmp;
    if (likely(Py_TYPE(value) == CPyType_test_env))
        tmp = value;
    else {
        CPy_TypeError("test.test_env", value); 
        tmp = NULL;
    }
    if (!tmp)
        return -1;
    CPy_INCREF(tmp);
    self->___mypyc_env__ = tmp;
    return 0;
}

static PyObject *CPyDunder___get__multiply_matrix_test_obj(PyObject *self, PyObject *instance, PyObject *owner) {
    instance = instance ? instance : Py_None;
    return CPyDef_multiply_matrix_test_obj_____get__(self, instance, owner);
}
static PyObject *multiply_matrix_test_obj_setup(PyTypeObject *type);
PyObject *CPyDef_multiply_matrix_test_obj(void);

static PyObject *
multiply_matrix_test_obj_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    if (type != CPyType_multiply_matrix_test_obj) {
        PyErr_SetString(PyExc_TypeError, "interpreted classes cannot inherit from compiled");
        return NULL;
    }
    return multiply_matrix_test_obj_setup(type);
}

static int
multiply_matrix_test_obj_traverse(test___multiply_matrix_test_objObject *self, visitproc visit, void *arg)
{
    Py_VISIT(self->___mypyc_env__);
    _PyObject_VisitManagedDict((PyObject *)self, visit, arg);
    return 0;
}

static int
multiply_matrix_test_obj_clear(test___multiply_matrix_test_objObject *self)
{
    Py_CLEAR(self->___mypyc_env__);
    _PyObject_ClearManagedDict((PyObject *)self);
    return 0;
}

static void
multiply_matrix_test_obj_dealloc(test___multiply_matrix_test_objObject *self)
{
    PyObject_GC_UnTrack(self);
    CPy_TRASHCAN_BEGIN(self, multiply_matrix_test_obj_dealloc)
    multiply_matrix_test_obj_clear(self);
    Py_TYPE(self)->tp_free((PyObject *)self);
    CPy_TRASHCAN_END(self)
}

static CPyVTableItem multiply_matrix_test_obj_vtable[2];
static bool
CPyDef_multiply_matrix_test_obj_trait_vtable_setup(void)
{
    CPyVTableItem multiply_matrix_test_obj_vtable_scratch[] = {
        (CPyVTableItem)CPyDef_multiply_matrix_test_obj_____call__,
        (CPyVTableItem)CPyDef_multiply_matrix_test_obj_____get__,
    };
    memcpy(multiply_matrix_test_obj_vtable, multiply_matrix_test_obj_vtable_scratch, sizeof(multiply_matrix_test_obj_vtable));
    return 1;
}

static PyObject *
multiply_matrix_test_obj_get___3_mypyc_env__(test___multiply_matrix_test_objObject *self, void *closure);
static int
multiply_matrix_test_obj_set___3_mypyc_env__(test___multiply_matrix_test_objObject *self, PyObject *value, void *closure);

static PyGetSetDef multiply_matrix_test_obj_getseters[] = {
    {"__mypyc_env__",
     (getter)multiply_matrix_test_obj_get___3_mypyc_env__, (setter)multiply_matrix_test_obj_set___3_mypyc_env__,
     NULL, NULL},
    {"__dict__", PyObject_GenericGetDict, PyObject_GenericSetDict},
    {NULL}  /* Sentinel */
};

static PyMethodDef multiply_matrix_test_obj_methods[] = {
    {"__call__",
     (PyCFunction)CPyPy_multiply_matrix_test_obj_____call__,
     METH_FASTCALL | METH_KEYWORDS, NULL},
    {"__get__",
     (PyCFunction)CPyPy_multiply_matrix_test_obj_____get__,
     METH_FASTCALL | METH_KEYWORDS, NULL},
    {"__setstate__", (PyCFunction)CPyPickle_SetState, METH_O, NULL},
    {"__getstate__", (PyCFunction)CPyPickle_GetState, METH_NOARGS, NULL},
    {NULL}  /* Sentinel */
};

static PyTypeObject CPyType_multiply_matrix_test_obj_template_ = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "multiply_matrix_test_obj",
    .tp_new = multiply_matrix_test_obj_new,
    .tp_dealloc = (destructor)multiply_matrix_test_obj_dealloc,
    .tp_traverse = (traverseproc)multiply_matrix_test_obj_traverse,
    .tp_clear = (inquiry)multiply_matrix_test_obj_clear,
    .tp_getset = multiply_matrix_test_obj_getseters,
    .tp_methods = multiply_matrix_test_obj_methods,
    .tp_call = PyVectorcall_Call,
    .tp_descr_get = CPyDunder___get__multiply_matrix_test_obj,
    .tp_basicsize = sizeof(test___multiply_matrix_test_objObject),
    .tp_vectorcall_offset = offsetof(test___multiply_matrix_test_objObject, vectorcall),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HEAPTYPE | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC | _Py_TPFLAGS_HAVE_VECTORCALL | Py_TPFLAGS_MANAGED_DICT,
};
static PyTypeObject *CPyType_multiply_matrix_test_obj_template = &CPyType_multiply_matrix_test_obj_template_;

static PyObject *
multiply_matrix_test_obj_setup(PyTypeObject *type)
{
    test___multiply_matrix_test_objObject *self;
    self = (test___multiply_matrix_test_objObject *)type->tp_alloc(type, 0);
    if (self == NULL)
        return NULL;
    self->vtable = multiply_matrix_test_obj_vtable;
    self->vectorcall = CPyPy_multiply_matrix_test_obj_____call__;
    return (PyObject *)self;
}

PyObject *CPyDef_multiply_matrix_test_obj(void)
{
    PyObject *self = multiply_matrix_test_obj_setup(CPyType_multiply_matrix_test_obj);
    if (self == NULL)
        return NULL;
    return self;
}

static PyObject *
multiply_matrix_test_obj_get___3_mypyc_env__(test___multiply_matrix_test_objObject *self, void *closure)
{
    if (unlikely(self->___mypyc_env__ == NULL)) {
        PyErr_SetString(PyExc_AttributeError,
            "attribute '__mypyc_env__' of 'multiply_matrix_test_obj' undefined");
        return NULL;
    }
    CPy_INCREF(self->___mypyc_env__);
    PyObject *retval = self->___mypyc_env__;
    return retval;
}

static int
multiply_matrix_test_obj_set___3_mypyc_env__(test___multiply_matrix_test_objObject *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_AttributeError,
            "'multiply_matrix_test_obj' object attribute '__mypyc_env__' cannot be deleted");
        return -1;
    }
    if (self->___mypyc_env__ != NULL) {
        CPy_DECREF(self->___mypyc_env__);
    }
    PyObject *tmp;
    if (likely(Py_TYPE(value) == CPyType_test_env))
        tmp = value;
    else {
        CPy_TypeError("test.test_env", value); 
        tmp = NULL;
    }
    if (!tmp)
        return -1;
    CPy_INCREF(tmp);
    self->___mypyc_env__ = tmp;
    return 0;
}
static PyMethodDef module_methods[] = {
    {"test", (PyCFunction)CPyPy_test, METH_FASTCALL | METH_KEYWORDS, NULL /* docstring */},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "test",
    NULL, /* docstring */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    module_methods
};

PyMODINIT_FUNC PyInit_test(void)
{
    PyObject* modname = NULL;
    if (CPyModule_test_internal) {
        Py_INCREF(CPyModule_test_internal);
        return CPyModule_test_internal;
    }
    CPyModule_test_internal = PyModule_Create(&module);
    if (unlikely(CPyModule_test_internal == NULL))
        goto fail;
    modname = PyObject_GetAttrString((PyObject *)CPyModule_test_internal, "__name__");
    CPyStatic_globals = PyModule_GetDict(CPyModule_test_internal);
    if (unlikely(CPyStatic_globals == NULL))
        goto fail;
    CPyType_test_env = (PyTypeObject *)CPyType_FromTemplate((PyObject *)CPyType_test_env_template, NULL, modname);
    if (unlikely(!CPyType_test_env))
        goto fail;
    CPyType_transpose_test_obj = (PyTypeObject *)CPyType_FromTemplate((PyObject *)CPyType_transpose_test_obj_template, NULL, modname);
    if (unlikely(!CPyType_transpose_test_obj))
        goto fail;
    CPyType_multiply_matrix_test_obj = (PyTypeObject *)CPyType_FromTemplate((PyObject *)CPyType_multiply_matrix_test_obj_template, NULL, modname);
    if (unlikely(!CPyType_multiply_matrix_test_obj))
        goto fail;
    if (CPyGlobalsInit() < 0)
        goto fail;
    char result = CPyDef___top_level__();
    if (result == 2)
        goto fail;
    Py_DECREF(modname);
    return CPyModule_test_internal;
    fail:
    Py_CLEAR(CPyModule_test_internal);
    Py_CLEAR(modname);
    Py_CLEAR(CPyType_test_env);
    Py_CLEAR(CPyType_transpose_test_obj);
    Py_CLEAR(CPyType_multiply_matrix_test_obj);
    return NULL;
}

PyObject *CPyDef_transpose_test_obj_____get__(PyObject *cpy_r___mypyc_self__, PyObject *cpy_r_instance, PyObject *cpy_r_owner) {
    PyObject *cpy_r_r0;
    char cpy_r_r1;
    PyObject *cpy_r_r2;
    PyObject *cpy_r_r3;
    cpy_r_r0 = (PyObject *)&_Py_NoneStruct;
    cpy_r_r1 = cpy_r_instance == cpy_r_r0;
    if (!cpy_r_r1) goto CPyL2;
    CPy_INCREF(cpy_r___mypyc_self__);
    return cpy_r___mypyc_self__;
CPyL2: ;
    cpy_r_r2 = PyMethod_New(cpy_r___mypyc_self__, cpy_r_instance);
    if (cpy_r_r2 == NULL) goto CPyL4;
    return cpy_r_r2;
CPyL4: ;
    cpy_r_r3 = NULL;
    return cpy_r_r3;
}

PyObject *CPyPy_transpose_test_obj_____get__(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames) {
    PyObject *obj___mypyc_self__ = self;
    static const char * const kwlist[] = {"instance", "owner", 0};
    static CPyArg_Parser parser = {"OO:__get__", kwlist, 0};
    PyObject *obj_instance;
    PyObject *obj_owner;
    if (!CPyArg_ParseStackAndKeywordsSimple(args, nargs, kwnames, &parser, &obj_instance, &obj_owner)) {
        return NULL;
    }
    PyObject *arg___mypyc_self__ = obj___mypyc_self__;
    PyObject *arg_instance = obj_instance;
    PyObject *arg_owner = obj_owner;
    PyObject *retval = CPyDef_transpose_test_obj_____get__(arg___mypyc_self__, arg_instance, arg_owner);
    return retval;
fail: ;
    CPy_AddTraceback("test.py", "__get__", -1, CPyStatic_globals);
    return NULL;
}

PyObject *CPyDef_transpose_test_obj_____call__(PyObject *cpy_r___mypyc_self__, PyObject *cpy_r_matrix) {
    PyObject *cpy_r_r0;
    PyObject *cpy_r_r1;
    PyObject *cpy_r_r2;
    PyObject *cpy_r_r3;
    CPyPtr cpy_r_r4;
    int64_t cpy_r_r5;
    CPyTagged cpy_r_r6;
    CPyTagged cpy_r_r7;
    CPyTagged cpy_r_i;
    char cpy_r_r8;
    PyObject *cpy_r_r9;
    CPyPtr cpy_r_r10;
    int64_t cpy_r_r11;
    CPyTagged cpy_r_r12;
    CPyTagged cpy_r_r13;
    CPyTagged cpy_r_j;
    char cpy_r_r14;
    PyObject *cpy_r_r15;
    PyObject *cpy_r_r16;
    PyObject *cpy_r_r17;
    CPyTagged cpy_r_r18;
    PyObject *cpy_r_r19;
    int32_t cpy_r_r20;
    char cpy_r_r21;
    CPyTagged cpy_r_r22;
    int32_t cpy_r_r23;
    char cpy_r_r24;
    CPyTagged cpy_r_r25;
    PyObject *cpy_r_r26;
    cpy_r_r0 = ((test___transpose_test_objObject *)cpy_r___mypyc_self__)->___mypyc_env__;
    if (unlikely(cpy_r_r0 == NULL)) {
        CPy_AttributeError("test.py", "transpose", "transpose_test_obj", "__mypyc_env__", 4, CPyStatic_globals);
        goto CPyL18;
    }
    CPy_INCREF(cpy_r_r0);
    goto CPyL19;
CPyL1: ;
    cpy_r_r1 = PyList_New(0);
    if (unlikely(cpy_r_r1 == NULL)) {
        CPy_AddTraceback("test.py", "transpose", 5, CPyStatic_globals);
        goto CPyL18;
    }
    cpy_r_r2 = CPyList_GetItemShortBorrow(cpy_r_matrix, 0);
    if (unlikely(cpy_r_r2 == NULL)) {
        CPy_AddTraceback("test.py", "transpose", 5, CPyStatic_globals);
        goto CPyL20;
    }
    if (likely(PyList_Check(cpy_r_r2)))
        cpy_r_r3 = cpy_r_r2;
    else {
        CPy_TypeErrorTraceback("test.py", "transpose", 5, CPyStatic_globals, "list", cpy_r_r2);
        goto CPyL20;
    }
    cpy_r_r4 = (CPyPtr)&((PyVarObject *)cpy_r_r3)->ob_size;
    cpy_r_r5 = *(int64_t *)cpy_r_r4;
    cpy_r_r6 = cpy_r_r5 << 1;
    cpy_r_r7 = 0;
    cpy_r_i = cpy_r_r7;
CPyL5: ;
    cpy_r_r8 = (Py_ssize_t)cpy_r_r7 < (Py_ssize_t)cpy_r_r6;
    if (!cpy_r_r8) goto CPyL21;
    cpy_r_r9 = PyList_New(0);
    if (unlikely(cpy_r_r9 == NULL)) {
        CPy_AddTraceback("test.py", "transpose", 5, CPyStatic_globals);
        goto CPyL22;
    }
    cpy_r_r10 = (CPyPtr)&((PyVarObject *)cpy_r_matrix)->ob_size;
    cpy_r_r11 = *(int64_t *)cpy_r_r10;
    cpy_r_r12 = cpy_r_r11 << 1;
    cpy_r_r13 = 0;
    cpy_r_j = cpy_r_r13;
CPyL8: ;
    cpy_r_r14 = (Py_ssize_t)cpy_r_r13 < (Py_ssize_t)cpy_r_r12;
    if (!cpy_r_r14) goto CPyL23;
    cpy_r_r15 = CPyList_GetItemBorrow(cpy_r_matrix, cpy_r_j);
    if (unlikely(cpy_r_r15 == NULL)) {
        CPy_AddTraceback("test.py", "transpose", 5, CPyStatic_globals);
        goto CPyL24;
    }
    if (likely(PyList_Check(cpy_r_r15)))
        cpy_r_r16 = cpy_r_r15;
    else {
        CPy_TypeErrorTraceback("test.py", "transpose", 5, CPyStatic_globals, "list", cpy_r_r15);
        goto CPyL24;
    }
    cpy_r_r17 = CPyList_GetItem(cpy_r_r16, cpy_r_i);
    if (unlikely(cpy_r_r17 == NULL)) {
        CPy_AddTraceback("test.py", "transpose", 5, CPyStatic_globals);
        goto CPyL24;
    }
    if (likely(PyLong_Check(cpy_r_r17)))
        cpy_r_r18 = CPyTagged_FromObject(cpy_r_r17);
    else {
        CPy_TypeError("int", cpy_r_r17); cpy_r_r18 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r17);
    if (unlikely(cpy_r_r18 == CPY_INT_TAG)) {
        CPy_AddTraceback("test.py", "transpose", 5, CPyStatic_globals);
        goto CPyL24;
    }
    CPyTagged_DECREF(cpy_r_j);
    cpy_r_r19 = CPyTagged_StealAsObject(cpy_r_r18);
    cpy_r_r20 = PyList_Append(cpy_r_r9, cpy_r_r19);
    CPy_DECREF(cpy_r_r19);
    cpy_r_r21 = cpy_r_r20 >= 0;
    if (unlikely(!cpy_r_r21)) {
        CPy_AddTraceback("test.py", "transpose", 5, CPyStatic_globals);
        goto CPyL25;
    }
    cpy_r_r22 = cpy_r_r13 + 2;
    cpy_r_r13 = cpy_r_r22;
    cpy_r_j = cpy_r_r22;
    goto CPyL8;
CPyL15: ;
    cpy_r_r23 = PyList_Append(cpy_r_r1, cpy_r_r9);
    CPy_DECREF(cpy_r_r9);
    cpy_r_r24 = cpy_r_r23 >= 0;
    if (unlikely(!cpy_r_r24)) {
        CPy_AddTraceback("test.py", "transpose", 5, CPyStatic_globals);
        goto CPyL20;
    }
    cpy_r_r25 = cpy_r_r7 + 2;
    cpy_r_r7 = cpy_r_r25;
    cpy_r_i = cpy_r_r25;
    goto CPyL5;
CPyL17: ;
    return cpy_r_r1;
CPyL18: ;
    cpy_r_r26 = NULL;
    return cpy_r_r26;
CPyL19: ;
    CPy_DECREF(cpy_r_r0);
    goto CPyL1;
CPyL20: ;
    CPy_DecRef(cpy_r_r1);
    goto CPyL18;
CPyL21: ;
    CPyTagged_DECREF(cpy_r_i);
    goto CPyL17;
CPyL22: ;
    CPy_DecRef(cpy_r_r1);
    CPyTagged_DecRef(cpy_r_i);
    goto CPyL18;
CPyL23: ;
    CPyTagged_DECREF(cpy_r_i);
    CPyTagged_DECREF(cpy_r_j);
    goto CPyL15;
CPyL24: ;
    CPy_DecRef(cpy_r_r1);
    CPyTagged_DecRef(cpy_r_i);
    CPy_DecRef(cpy_r_r9);
    CPyTagged_DecRef(cpy_r_j);
    goto CPyL18;
CPyL25: ;
    CPy_DecRef(cpy_r_r1);
    CPyTagged_DecRef(cpy_r_i);
    CPy_DecRef(cpy_r_r9);
    goto CPyL18;
}

PyObject *CPyPy_transpose_test_obj_____call__(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames) {
    PyObject *obj___mypyc_self__ = self;
    static const char * const kwlist[] = {"matrix", 0};
    static CPyArg_Parser parser = {"O:__call__", kwlist, 0};
    PyObject *obj_matrix;
    if (!CPyArg_ParseStackAndKeywordsOneArg(args, PyVectorcall_NARGS(nargs), kwnames, &parser, &obj_matrix)) {
        return NULL;
    }
    PyObject *arg___mypyc_self__ = obj___mypyc_self__;
    PyObject *arg_matrix;
    if (likely(PyList_Check(obj_matrix)))
        arg_matrix = obj_matrix;
    else {
        CPy_TypeError("list", obj_matrix); 
        goto fail;
    }
    PyObject *retval = CPyDef_transpose_test_obj_____call__(arg___mypyc_self__, arg_matrix);
    return retval;
fail: ;
    CPy_AddTraceback("test.py", "transpose", 4, CPyStatic_globals);
    return NULL;
}

PyObject *CPyDef_multiply_matrix_test_obj_____get__(PyObject *cpy_r___mypyc_self__, PyObject *cpy_r_instance, PyObject *cpy_r_owner) {
    PyObject *cpy_r_r0;
    char cpy_r_r1;
    PyObject *cpy_r_r2;
    PyObject *cpy_r_r3;
    cpy_r_r0 = (PyObject *)&_Py_NoneStruct;
    cpy_r_r1 = cpy_r_instance == cpy_r_r0;
    if (!cpy_r_r1) goto CPyL2;
    CPy_INCREF(cpy_r___mypyc_self__);
    return cpy_r___mypyc_self__;
CPyL2: ;
    cpy_r_r2 = PyMethod_New(cpy_r___mypyc_self__, cpy_r_instance);
    if (cpy_r_r2 == NULL) goto CPyL4;
    return cpy_r_r2;
CPyL4: ;
    cpy_r_r3 = NULL;
    return cpy_r_r3;
}

PyObject *CPyPy_multiply_matrix_test_obj_____get__(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames) {
    PyObject *obj___mypyc_self__ = self;
    static const char * const kwlist[] = {"instance", "owner", 0};
    static CPyArg_Parser parser = {"OO:__get__", kwlist, 0};
    PyObject *obj_instance;
    PyObject *obj_owner;
    if (!CPyArg_ParseStackAndKeywordsSimple(args, nargs, kwnames, &parser, &obj_instance, &obj_owner)) {
        return NULL;
    }
    PyObject *arg___mypyc_self__ = obj___mypyc_self__;
    PyObject *arg_instance = obj_instance;
    PyObject *arg_owner = obj_owner;
    PyObject *retval = CPyDef_multiply_matrix_test_obj_____get__(arg___mypyc_self__, arg_instance, arg_owner);
    return retval;
fail: ;
    CPy_AddTraceback("test.py", "__get__", -1, CPyStatic_globals);
    return NULL;
}

PyObject *CPyDef_multiply_matrix_test_obj_____call__(PyObject *cpy_r___mypyc_self__, PyObject *cpy_r_matrix1, PyObject *cpy_r_matrix2) {
    PyObject *cpy_r_r0;
    CPyPtr cpy_r_r1;
    int64_t cpy_r_r2;
    PyObject *cpy_r_r3;
    CPyTagged cpy_r_r4;
    CPyPtr cpy_r_r5;
    int64_t cpy_r_r6;
    CPyTagged cpy_r_r7;
    char cpy_r_r8;
    PyObject *cpy_r_r9;
    PyObject *cpy_r_r10;
    PyObject *cpy_r_X_row;
    PyObject *cpy_r_r11;
    PyObject *cpy_r_r12;
    PyObject *cpy_r_r13;
    PyObject *cpy_r_r14;
    PyObject *cpy_r_r15;
    PyObject *cpy_r_r16;
    PyObject *cpy_r_r17;
    PyObject *cpy_r_r18;
    PyObject *cpy_r_r19;
    PyObject *cpy_r_r20;
    PyObject *cpy_r_r21;
    PyObject *cpy_r_r22;
    PyObject *cpy_r_Y_col;
    CPyTagged cpy_r_r23;
    CPyTagged cpy_r_r24;
    CPyTagged cpy_r_r25;
    CPyPtr cpy_r_r26;
    int64_t cpy_r_r27;
    CPyTagged cpy_r_r28;
    char cpy_r_r29;
    CPyPtr cpy_r_r30;
    int64_t cpy_r_r31;
    CPyTagged cpy_r_r32;
    char cpy_r_r33;
    PyObject *cpy_r_r34;
    CPyTagged cpy_r_r35;
    CPyTagged cpy_r_a;
    PyObject *cpy_r_r36;
    PyObject *cpy_r_b;
    PyObject *cpy_r_r37;
    PyObject *cpy_r_r38;
    PyObject *cpy_r_r39;
    PyObject *cpy_r_r40;
    CPyTagged cpy_r_r41;
    CPyTagged cpy_r_r42;
    CPyTagged cpy_r_r43;
    PyObject *cpy_r_r44;
    int32_t cpy_r_r45;
    char cpy_r_r46;
    char cpy_r_r47;
    char cpy_r_r48;
    CPyTagged cpy_r_r49;
    PyObject *cpy_r_r50;
    cpy_r_r0 = ((test___multiply_matrix_test_objObject *)cpy_r___mypyc_self__)->___mypyc_env__;
    if (unlikely(cpy_r_r0 == NULL)) {
        CPy_AttributeError("test.py", "multiply_matrix", "multiply_matrix_test_obj", "__mypyc_env__", 9, CPyStatic_globals);
        goto CPyL30;
    }
    CPy_INCREF(cpy_r_r0);
    goto CPyL31;
CPyL1: ;
    cpy_r_r1 = (CPyPtr)&((PyVarObject *)cpy_r_matrix1)->ob_size;
    cpy_r_r2 = *(int64_t *)cpy_r_r1;
    cpy_r_r3 = PyList_New(cpy_r_r2);
    if (unlikely(cpy_r_r3 == NULL)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL30;
    }
    cpy_r_r4 = 0;
CPyL3: ;
    cpy_r_r5 = (CPyPtr)&((PyVarObject *)cpy_r_matrix1)->ob_size;
    cpy_r_r6 = *(int64_t *)cpy_r_r5;
    cpy_r_r7 = cpy_r_r6 << 1;
    cpy_r_r8 = (Py_ssize_t)cpy_r_r4 < (Py_ssize_t)cpy_r_r7;
    if (!cpy_r_r8) goto CPyL29;
    cpy_r_r9 = CPyList_GetItemUnsafe(cpy_r_matrix1, cpy_r_r4);
    if (likely(PyList_Check(cpy_r_r9)))
        cpy_r_r10 = cpy_r_r9;
    else {
        CPy_TypeErrorTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals, "list", cpy_r_r9);
        goto CPyL32;
    }
    cpy_r_X_row = cpy_r_r10;
    cpy_r_r11 = PyList_New(0);
    if (unlikely(cpy_r_r11 == NULL)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL33;
    }
    cpy_r_r12 = CPyModule_builtins;
    cpy_r_r13 = CPyStatics[3]; /* 'zip' */
    cpy_r_r14 = CPyObject_GetAttr(cpy_r_r12, cpy_r_r13);
    if (unlikely(cpy_r_r14 == NULL)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL34;
    }
    cpy_r_r15 = PyList_New(0);
    if (unlikely(cpy_r_r15 == NULL)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL35;
    }
    cpy_r_r16 = CPyList_Extend(cpy_r_r15, cpy_r_matrix2);
    if (unlikely(cpy_r_r16 == NULL)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL36;
    } else
        goto CPyL37;
CPyL9: ;
    cpy_r_r17 = PyList_AsTuple(cpy_r_r15);
    CPy_DECREF(cpy_r_r15);
    if (unlikely(cpy_r_r17 == NULL)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL35;
    }
    cpy_r_r18 = PyDict_New();
    if (unlikely(cpy_r_r18 == NULL)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL38;
    }
    cpy_r_r19 = PyObject_Call(cpy_r_r14, cpy_r_r17, cpy_r_r18);
    CPy_DECREF(cpy_r_r14);
    CPy_DECREF(cpy_r_r17);
    CPy_DECREF(cpy_r_r18);
    if (unlikely(cpy_r_r19 == NULL)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL34;
    }
    cpy_r_r20 = PyObject_GetIter(cpy_r_r19);
    CPy_DECREF(cpy_r_r19);
    if (unlikely(cpy_r_r20 == NULL)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL34;
    }
CPyL13: ;
    cpy_r_r21 = PyIter_Next(cpy_r_r20);
    if (cpy_r_r21 == NULL) goto CPyL39;
    if (likely(PyTuple_Check(cpy_r_r21)))
        cpy_r_r22 = cpy_r_r21;
    else {
        CPy_TypeErrorTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals, "tuple", cpy_r_r21);
        goto CPyL40;
    }
    cpy_r_Y_col = cpy_r_r22;
    cpy_r_r23 = 0;
    cpy_r_r24 = 0;
    cpy_r_r25 = 0;
CPyL16: ;
    cpy_r_r26 = (CPyPtr)&((PyVarObject *)cpy_r_X_row)->ob_size;
    cpy_r_r27 = *(int64_t *)cpy_r_r26;
    cpy_r_r28 = cpy_r_r27 << 1;
    cpy_r_r29 = (Py_ssize_t)cpy_r_r24 < (Py_ssize_t)cpy_r_r28;
    if (!cpy_r_r29) goto CPyL41;
    cpy_r_r30 = (CPyPtr)&((PyVarObject *)cpy_r_Y_col)->ob_size;
    cpy_r_r31 = *(int64_t *)cpy_r_r30;
    cpy_r_r32 = cpy_r_r31 << 1;
    cpy_r_r33 = (Py_ssize_t)cpy_r_r25 < (Py_ssize_t)cpy_r_r32;
    if (!cpy_r_r33) goto CPyL41;
    cpy_r_r34 = CPyList_GetItemUnsafe(cpy_r_X_row, cpy_r_r24);
    if (likely(PyLong_Check(cpy_r_r34)))
        cpy_r_r35 = CPyTagged_FromObject(cpy_r_r34);
    else {
        CPy_TypeError("int", cpy_r_r34); cpy_r_r35 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r34);
    if (unlikely(cpy_r_r35 == CPY_INT_TAG)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL42;
    }
    cpy_r_a = cpy_r_r35;
    cpy_r_r36 = CPySequenceTuple_GetItem(cpy_r_Y_col, cpy_r_r25);
    if (unlikely(cpy_r_r36 == NULL)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL43;
    }
    cpy_r_b = cpy_r_r36;
    cpy_r_r37 = CPyTagged_StealAsObject(cpy_r_a);
    cpy_r_r38 = PyNumber_Multiply(cpy_r_r37, cpy_r_b);
    CPy_DECREF(cpy_r_r37);
    CPy_DECREF(cpy_r_b);
    if (unlikely(cpy_r_r38 == NULL)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL42;
    }
    cpy_r_r39 = CPyTagged_StealAsObject(cpy_r_r23);
    cpy_r_r40 = PyNumber_Add(cpy_r_r39, cpy_r_r38);
    CPy_DECREF(cpy_r_r39);
    CPy_DECREF(cpy_r_r38);
    if (unlikely(cpy_r_r40 == NULL)) {
        CPy_AddTraceback("test.py", "multiply_matrix", -1, CPyStatic_globals);
        goto CPyL44;
    }
    if (likely(PyLong_Check(cpy_r_r40)))
        cpy_r_r41 = CPyTagged_FromObject(cpy_r_r40);
    else {
        CPy_TypeError("int", cpy_r_r40); cpy_r_r41 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r40);
    if (unlikely(cpy_r_r41 == CPY_INT_TAG)) {
        CPy_AddTraceback("test.py", "multiply_matrix", -1, CPyStatic_globals);
        goto CPyL44;
    }
    cpy_r_r23 = cpy_r_r41;
    cpy_r_r42 = cpy_r_r24 + 2;
    cpy_r_r24 = cpy_r_r42;
    cpy_r_r43 = cpy_r_r25 + 2;
    cpy_r_r25 = cpy_r_r43;
    goto CPyL16;
CPyL25: ;
    cpy_r_r44 = CPyTagged_StealAsObject(cpy_r_r23);
    cpy_r_r45 = PyList_Append(cpy_r_r11, cpy_r_r44);
    CPy_DECREF(cpy_r_r44);
    cpy_r_r46 = cpy_r_r45 >= 0;
    if (unlikely(!cpy_r_r46)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL40;
    } else
        goto CPyL13;
CPyL26: ;
    cpy_r_r47 = CPy_NoErrOccured();
    if (unlikely(!cpy_r_r47)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL45;
    }
    cpy_r_r48 = CPyList_SetItemUnsafe(cpy_r_r3, cpy_r_r4, cpy_r_r11);
    if (unlikely(!cpy_r_r48)) {
        CPy_AddTraceback("test.py", "multiply_matrix", 10, CPyStatic_globals);
        goto CPyL32;
    }
    cpy_r_r49 = cpy_r_r4 + 2;
    cpy_r_r4 = cpy_r_r49;
    goto CPyL3;
CPyL29: ;
    return cpy_r_r3;
CPyL30: ;
    cpy_r_r50 = NULL;
    return cpy_r_r50;
CPyL31: ;
    CPy_DECREF(cpy_r_r0);
    goto CPyL1;
CPyL32: ;
    CPy_DecRef(cpy_r_r3);
    goto CPyL30;
CPyL33: ;
    CPy_DecRef(cpy_r_r3);
    CPy_DecRef(cpy_r_X_row);
    goto CPyL30;
CPyL34: ;
    CPy_DecRef(cpy_r_r3);
    CPy_DecRef(cpy_r_X_row);
    CPy_DecRef(cpy_r_r11);
    goto CPyL30;
CPyL35: ;
    CPy_DecRef(cpy_r_r3);
    CPy_DecRef(cpy_r_X_row);
    CPy_DecRef(cpy_r_r11);
    CPy_DecRef(cpy_r_r14);
    goto CPyL30;
CPyL36: ;
    CPy_DecRef(cpy_r_r3);
    CPy_DecRef(cpy_r_X_row);
    CPy_DecRef(cpy_r_r11);
    CPy_DecRef(cpy_r_r14);
    CPy_DecRef(cpy_r_r15);
    goto CPyL30;
CPyL37: ;
    CPy_DECREF(cpy_r_r16);
    goto CPyL9;
CPyL38: ;
    CPy_DecRef(cpy_r_r3);
    CPy_DecRef(cpy_r_X_row);
    CPy_DecRef(cpy_r_r11);
    CPy_DecRef(cpy_r_r14);
    CPy_DecRef(cpy_r_r17);
    goto CPyL30;
CPyL39: ;
    CPy_DECREF(cpy_r_X_row);
    CPy_DECREF(cpy_r_r20);
    goto CPyL26;
CPyL40: ;
    CPy_DecRef(cpy_r_r3);
    CPy_DecRef(cpy_r_X_row);
    CPy_DecRef(cpy_r_r11);
    CPy_DecRef(cpy_r_r20);
    goto CPyL30;
CPyL41: ;
    CPy_DECREF(cpy_r_Y_col);
    goto CPyL25;
CPyL42: ;
    CPy_DecRef(cpy_r_r3);
    CPy_DecRef(cpy_r_X_row);
    CPy_DecRef(cpy_r_r11);
    CPy_DecRef(cpy_r_r20);
    CPy_DecRef(cpy_r_Y_col);
    CPyTagged_DecRef(cpy_r_r23);
    goto CPyL30;
CPyL43: ;
    CPy_DecRef(cpy_r_r3);
    CPy_DecRef(cpy_r_X_row);
    CPy_DecRef(cpy_r_r11);
    CPy_DecRef(cpy_r_r20);
    CPy_DecRef(cpy_r_Y_col);
    CPyTagged_DecRef(cpy_r_r23);
    CPyTagged_DecRef(cpy_r_a);
    goto CPyL30;
CPyL44: ;
    CPy_DecRef(cpy_r_r3);
    CPy_DecRef(cpy_r_X_row);
    CPy_DecRef(cpy_r_r11);
    CPy_DecRef(cpy_r_r20);
    CPy_DecRef(cpy_r_Y_col);
    goto CPyL30;
CPyL45: ;
    CPy_DecRef(cpy_r_r3);
    CPy_DecRef(cpy_r_r11);
    goto CPyL30;
}

PyObject *CPyPy_multiply_matrix_test_obj_____call__(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames) {
    PyObject *obj___mypyc_self__ = self;
    static const char * const kwlist[] = {"matrix1", "matrix2", 0};
    static CPyArg_Parser parser = {"OO:__call__", kwlist, 0};
    PyObject *obj_matrix1;
    PyObject *obj_matrix2;
    if (!CPyArg_ParseStackAndKeywordsSimple(args, PyVectorcall_NARGS(nargs), kwnames, &parser, &obj_matrix1, &obj_matrix2)) {
        return NULL;
    }
    PyObject *arg___mypyc_self__ = obj___mypyc_self__;
    PyObject *arg_matrix1;
    if (likely(PyList_Check(obj_matrix1)))
        arg_matrix1 = obj_matrix1;
    else {
        CPy_TypeError("list", obj_matrix1); 
        goto fail;
    }
    PyObject *arg_matrix2;
    if (likely(PyList_Check(obj_matrix2)))
        arg_matrix2 = obj_matrix2;
    else {
        CPy_TypeError("list", obj_matrix2); 
        goto fail;
    }
    PyObject *retval = CPyDef_multiply_matrix_test_obj_____call__(arg___mypyc_self__, arg_matrix1, arg_matrix2);
    return retval;
fail: ;
    CPy_AddTraceback("test.py", "multiply_matrix", 9, CPyStatic_globals);
    return NULL;
}

PyObject *CPyDef_test(void) {
    PyObject *cpy_r_r0;
    PyObject *cpy_r_r1;
    PyObject *cpy_r_r2;
    PyObject *cpy_r_r3;
    PyObject *cpy_r_r4;
    CPyPtr cpy_r_r5;
    CPyPtr cpy_r_r6;
    CPyPtr cpy_r_r7;
    CPyPtr cpy_r_r8;
    PyObject *cpy_r_r9;
    PyObject *cpy_r_r10;
    PyObject *cpy_r_r11;
    PyObject *cpy_r_r12;
    CPyPtr cpy_r_r13;
    CPyPtr cpy_r_r14;
    CPyPtr cpy_r_r15;
    CPyPtr cpy_r_r16;
    PyObject *cpy_r_r17;
    PyObject *cpy_r_r18;
    PyObject *cpy_r_r19;
    PyObject *cpy_r_r20;
    CPyPtr cpy_r_r21;
    CPyPtr cpy_r_r22;
    CPyPtr cpy_r_r23;
    CPyPtr cpy_r_r24;
    PyObject *cpy_r_r25;
    CPyPtr cpy_r_r26;
    CPyPtr cpy_r_r27;
    CPyPtr cpy_r_r28;
    CPyPtr cpy_r_r29;
    PyObject *cpy_r_mat1;
    PyObject *cpy_r_r30;
    PyObject *cpy_r_r31;
    PyObject *cpy_r_r32;
    PyObject *cpy_r_r33;
    CPyPtr cpy_r_r34;
    CPyPtr cpy_r_r35;
    CPyPtr cpy_r_r36;
    CPyPtr cpy_r_r37;
    PyObject *cpy_r_r38;
    PyObject *cpy_r_r39;
    PyObject *cpy_r_r40;
    PyObject *cpy_r_r41;
    CPyPtr cpy_r_r42;
    CPyPtr cpy_r_r43;
    CPyPtr cpy_r_r44;
    CPyPtr cpy_r_r45;
    PyObject *cpy_r_r46;
    PyObject *cpy_r_r47;
    PyObject *cpy_r_r48;
    PyObject *cpy_r_r49;
    CPyPtr cpy_r_r50;
    CPyPtr cpy_r_r51;
    CPyPtr cpy_r_r52;
    CPyPtr cpy_r_r53;
    PyObject *cpy_r_r54;
    CPyPtr cpy_r_r55;
    CPyPtr cpy_r_r56;
    CPyPtr cpy_r_r57;
    CPyPtr cpy_r_r58;
    PyObject *cpy_r_mat2;
    PyObject *cpy_r_r59;
    char cpy_r_r60;
    PyObject *cpy_r_transpose;
    PyObject **cpy_r_r62;
    PyObject *cpy_r_r63;
    PyObject *cpy_r_r64;
    PyObject *cpy_r_r65;
    PyObject *cpy_r_r66;
    PyObject **cpy_r_r68;
    PyObject *cpy_r_r69;
    PyObject *cpy_r_r70;
    char cpy_r_r71;
    PyObject *cpy_r_multiply_matrix;
    PyObject **cpy_r_r73;
    PyObject *cpy_r_r74;
    PyObject *cpy_r_r75;
    PyObject *cpy_r_r76;
    PyObject *cpy_r_r77;
    PyObject **cpy_r_r79;
    PyObject *cpy_r_r80;
    PyObject *cpy_r_r81;
    PyObject *cpy_r_r82;
    cpy_r_r0 = CPyDef_test_env();
    if (unlikely(cpy_r_r0 == NULL)) {
        CPy_AddTraceback("test.py", "test", 1, CPyStatic_globals);
        goto CPyL20;
    }
    cpy_r_r1 = PyList_New(3);
    if (unlikely(cpy_r_r1 == NULL)) {
        CPy_AddTraceback("test.py", "test", 2, CPyStatic_globals);
        goto CPyL21;
    }
    cpy_r_r2 = CPyStatics[14]; /* 1 */
    cpy_r_r3 = CPyStatics[15]; /* 2 */
    cpy_r_r4 = CPyStatics[16]; /* 3 */
    cpy_r_r5 = (CPyPtr)&((PyListObject *)cpy_r_r1)->ob_item;
    cpy_r_r6 = *(CPyPtr *)cpy_r_r5;
    CPy_INCREF(cpy_r_r2);
    *(PyObject * *)cpy_r_r6 = cpy_r_r2;
    cpy_r_r7 = cpy_r_r6 + 8;
    CPy_INCREF(cpy_r_r3);
    *(PyObject * *)cpy_r_r7 = cpy_r_r3;
    cpy_r_r8 = cpy_r_r6 + 16;
    CPy_INCREF(cpy_r_r4);
    *(PyObject * *)cpy_r_r8 = cpy_r_r4;
    cpy_r_r9 = PyList_New(3);
    if (unlikely(cpy_r_r9 == NULL)) {
        CPy_AddTraceback("test.py", "test", 2, CPyStatic_globals);
        goto CPyL22;
    }
    cpy_r_r10 = CPyStatics[17]; /* 4 */
    cpy_r_r11 = CPyStatics[18]; /* 5 */
    cpy_r_r12 = CPyStatics[19]; /* 6 */
    cpy_r_r13 = (CPyPtr)&((PyListObject *)cpy_r_r9)->ob_item;
    cpy_r_r14 = *(CPyPtr *)cpy_r_r13;
    CPy_INCREF(cpy_r_r10);
    *(PyObject * *)cpy_r_r14 = cpy_r_r10;
    cpy_r_r15 = cpy_r_r14 + 8;
    CPy_INCREF(cpy_r_r11);
    *(PyObject * *)cpy_r_r15 = cpy_r_r11;
    cpy_r_r16 = cpy_r_r14 + 16;
    CPy_INCREF(cpy_r_r12);
    *(PyObject * *)cpy_r_r16 = cpy_r_r12;
    cpy_r_r17 = PyList_New(3);
    if (unlikely(cpy_r_r17 == NULL)) {
        CPy_AddTraceback("test.py", "test", 2, CPyStatic_globals);
        goto CPyL23;
    }
    cpy_r_r18 = CPyStatics[20]; /* 7 */
    cpy_r_r19 = CPyStatics[21]; /* 8 */
    cpy_r_r20 = CPyStatics[22]; /* 9 */
    cpy_r_r21 = (CPyPtr)&((PyListObject *)cpy_r_r17)->ob_item;
    cpy_r_r22 = *(CPyPtr *)cpy_r_r21;
    CPy_INCREF(cpy_r_r18);
    *(PyObject * *)cpy_r_r22 = cpy_r_r18;
    cpy_r_r23 = cpy_r_r22 + 8;
    CPy_INCREF(cpy_r_r19);
    *(PyObject * *)cpy_r_r23 = cpy_r_r19;
    cpy_r_r24 = cpy_r_r22 + 16;
    CPy_INCREF(cpy_r_r20);
    *(PyObject * *)cpy_r_r24 = cpy_r_r20;
    cpy_r_r25 = PyList_New(3);
    if (unlikely(cpy_r_r25 == NULL)) {
        CPy_AddTraceback("test.py", "test", 2, CPyStatic_globals);
        goto CPyL24;
    }
    cpy_r_r26 = (CPyPtr)&((PyListObject *)cpy_r_r25)->ob_item;
    cpy_r_r27 = *(CPyPtr *)cpy_r_r26;
    *(PyObject * *)cpy_r_r27 = cpy_r_r1;
    cpy_r_r28 = cpy_r_r27 + 8;
    *(PyObject * *)cpy_r_r28 = cpy_r_r9;
    cpy_r_r29 = cpy_r_r27 + 16;
    *(PyObject * *)cpy_r_r29 = cpy_r_r17;
    cpy_r_mat1 = cpy_r_r25;
    cpy_r_r30 = PyList_New(3);
    if (unlikely(cpy_r_r30 == NULL)) {
        CPy_AddTraceback("test.py", "test", 3, CPyStatic_globals);
        goto CPyL25;
    }
    cpy_r_r31 = CPyStatics[14]; /* 1 */
    cpy_r_r32 = CPyStatics[15]; /* 2 */
    cpy_r_r33 = CPyStatics[16]; /* 3 */
    cpy_r_r34 = (CPyPtr)&((PyListObject *)cpy_r_r30)->ob_item;
    cpy_r_r35 = *(CPyPtr *)cpy_r_r34;
    CPy_INCREF(cpy_r_r31);
    *(PyObject * *)cpy_r_r35 = cpy_r_r31;
    cpy_r_r36 = cpy_r_r35 + 8;
    CPy_INCREF(cpy_r_r32);
    *(PyObject * *)cpy_r_r36 = cpy_r_r32;
    cpy_r_r37 = cpy_r_r35 + 16;
    CPy_INCREF(cpy_r_r33);
    *(PyObject * *)cpy_r_r37 = cpy_r_r33;
    cpy_r_r38 = PyList_New(3);
    if (unlikely(cpy_r_r38 == NULL)) {
        CPy_AddTraceback("test.py", "test", 3, CPyStatic_globals);
        goto CPyL26;
    }
    cpy_r_r39 = CPyStatics[17]; /* 4 */
    cpy_r_r40 = CPyStatics[18]; /* 5 */
    cpy_r_r41 = CPyStatics[19]; /* 6 */
    cpy_r_r42 = (CPyPtr)&((PyListObject *)cpy_r_r38)->ob_item;
    cpy_r_r43 = *(CPyPtr *)cpy_r_r42;
    CPy_INCREF(cpy_r_r39);
    *(PyObject * *)cpy_r_r43 = cpy_r_r39;
    cpy_r_r44 = cpy_r_r43 + 8;
    CPy_INCREF(cpy_r_r40);
    *(PyObject * *)cpy_r_r44 = cpy_r_r40;
    cpy_r_r45 = cpy_r_r43 + 16;
    CPy_INCREF(cpy_r_r41);
    *(PyObject * *)cpy_r_r45 = cpy_r_r41;
    cpy_r_r46 = PyList_New(3);
    if (unlikely(cpy_r_r46 == NULL)) {
        CPy_AddTraceback("test.py", "test", 3, CPyStatic_globals);
        goto CPyL27;
    }
    cpy_r_r47 = CPyStatics[20]; /* 7 */
    cpy_r_r48 = CPyStatics[21]; /* 8 */
    cpy_r_r49 = CPyStatics[22]; /* 9 */
    cpy_r_r50 = (CPyPtr)&((PyListObject *)cpy_r_r46)->ob_item;
    cpy_r_r51 = *(CPyPtr *)cpy_r_r50;
    CPy_INCREF(cpy_r_r47);
    *(PyObject * *)cpy_r_r51 = cpy_r_r47;
    cpy_r_r52 = cpy_r_r51 + 8;
    CPy_INCREF(cpy_r_r48);
    *(PyObject * *)cpy_r_r52 = cpy_r_r48;
    cpy_r_r53 = cpy_r_r51 + 16;
    CPy_INCREF(cpy_r_r49);
    *(PyObject * *)cpy_r_r53 = cpy_r_r49;
    cpy_r_r54 = PyList_New(3);
    if (unlikely(cpy_r_r54 == NULL)) {
        CPy_AddTraceback("test.py", "test", 3, CPyStatic_globals);
        goto CPyL28;
    }
    cpy_r_r55 = (CPyPtr)&((PyListObject *)cpy_r_r54)->ob_item;
    cpy_r_r56 = *(CPyPtr *)cpy_r_r55;
    *(PyObject * *)cpy_r_r56 = cpy_r_r30;
    cpy_r_r57 = cpy_r_r56 + 8;
    *(PyObject * *)cpy_r_r57 = cpy_r_r38;
    cpy_r_r58 = cpy_r_r56 + 16;
    *(PyObject * *)cpy_r_r58 = cpy_r_r46;
    cpy_r_mat2 = cpy_r_r54;
    cpy_r_r59 = CPyDef_transpose_test_obj();
    if (unlikely(cpy_r_r59 == NULL)) {
        CPy_AddTraceback("test.py", "test", 4, CPyStatic_globals);
        goto CPyL29;
    }
    CPy_INCREF(cpy_r_r0);
    if (((test___transpose_test_objObject *)cpy_r_r59)->___mypyc_env__ != NULL) {
        CPy_DECREF(((test___transpose_test_objObject *)cpy_r_r59)->___mypyc_env__);
    }
    ((test___transpose_test_objObject *)cpy_r_r59)->___mypyc_env__ = cpy_r_r0;
    cpy_r_r60 = 1;
    if (unlikely(!cpy_r_r60)) {
        CPy_AddTraceback("test.py", "test", 4, CPyStatic_globals);
        goto CPyL30;
    }
    cpy_r_transpose = cpy_r_r59;
    PyObject *cpy_r_r61[1] = {cpy_r_mat1};
    cpy_r_r62 = (PyObject **)&cpy_r_r61;
    cpy_r_r63 = _PyObject_Vectorcall(cpy_r_transpose, cpy_r_r62, 1, 0);
    CPy_DECREF(cpy_r_transpose);
    if (unlikely(cpy_r_r63 == NULL)) {
        CPy_AddTraceback("test.py", "test", 7, CPyStatic_globals);
        goto CPyL29;
    }
    cpy_r_r64 = CPyModule_builtins;
    cpy_r_r65 = CPyStatics[4]; /* 'print' */
    cpy_r_r66 = CPyObject_GetAttr(cpy_r_r64, cpy_r_r65);
    if (unlikely(cpy_r_r66 == NULL)) {
        CPy_AddTraceback("test.py", "test", 7, CPyStatic_globals);
        goto CPyL31;
    }
    PyObject *cpy_r_r67[1] = {cpy_r_r63};
    cpy_r_r68 = (PyObject **)&cpy_r_r67;
    cpy_r_r69 = _PyObject_Vectorcall(cpy_r_r66, cpy_r_r68, 1, 0);
    CPy_DECREF(cpy_r_r66);
    if (unlikely(cpy_r_r69 == NULL)) {
        CPy_AddTraceback("test.py", "test", 7, CPyStatic_globals);
        goto CPyL31;
    } else
        goto CPyL32;
CPyL14: ;
    CPy_DECREF(cpy_r_r63);
    cpy_r_r70 = CPyDef_multiply_matrix_test_obj();
    if (unlikely(cpy_r_r70 == NULL)) {
        CPy_AddTraceback("test.py", "test", 9, CPyStatic_globals);
        goto CPyL29;
    }
    if (((test___multiply_matrix_test_objObject *)cpy_r_r70)->___mypyc_env__ != NULL) {
        CPy_DECREF(((test___multiply_matrix_test_objObject *)cpy_r_r70)->___mypyc_env__);
    }
    ((test___multiply_matrix_test_objObject *)cpy_r_r70)->___mypyc_env__ = cpy_r_r0;
    cpy_r_r71 = 1;
    if (unlikely(!cpy_r_r71)) {
        CPy_AddTraceback("test.py", "test", 9, CPyStatic_globals);
        goto CPyL33;
    }
    cpy_r_multiply_matrix = cpy_r_r70;
    PyObject *cpy_r_r72[2] = {cpy_r_mat1, cpy_r_mat2};
    cpy_r_r73 = (PyObject **)&cpy_r_r72;
    cpy_r_r74 = _PyObject_Vectorcall(cpy_r_multiply_matrix, cpy_r_r73, 2, 0);
    CPy_DECREF(cpy_r_multiply_matrix);
    if (unlikely(cpy_r_r74 == NULL)) {
        CPy_AddTraceback("test.py", "test", 12, CPyStatic_globals);
        goto CPyL34;
    }
    CPy_DECREF(cpy_r_mat1);
    CPy_DECREF(cpy_r_mat2);
    cpy_r_r75 = CPyModule_builtins;
    cpy_r_r76 = CPyStatics[4]; /* 'print' */
    cpy_r_r77 = CPyObject_GetAttr(cpy_r_r75, cpy_r_r76);
    if (unlikely(cpy_r_r77 == NULL)) {
        CPy_AddTraceback("test.py", "test", 12, CPyStatic_globals);
        goto CPyL35;
    }
    PyObject *cpy_r_r78[1] = {cpy_r_r74};
    cpy_r_r79 = (PyObject **)&cpy_r_r78;
    cpy_r_r80 = _PyObject_Vectorcall(cpy_r_r77, cpy_r_r79, 1, 0);
    CPy_DECREF(cpy_r_r77);
    if (unlikely(cpy_r_r80 == NULL)) {
        CPy_AddTraceback("test.py", "test", 12, CPyStatic_globals);
        goto CPyL35;
    } else
        goto CPyL36;
CPyL19: ;
    CPy_DECREF(cpy_r_r74);
    cpy_r_r81 = Py_None;
    CPy_INCREF(cpy_r_r81);
    return cpy_r_r81;
CPyL20: ;
    cpy_r_r82 = NULL;
    return cpy_r_r82;
CPyL21: ;
    CPy_DecRef(cpy_r_r0);
    goto CPyL20;
CPyL22: ;
    CPy_DecRef(cpy_r_r0);
    CPy_DecRef(cpy_r_r1);
    goto CPyL20;
CPyL23: ;
    CPy_DecRef(cpy_r_r0);
    CPy_DecRef(cpy_r_r1);
    CPy_DecRef(cpy_r_r9);
    goto CPyL20;
CPyL24: ;
    CPy_DecRef(cpy_r_r0);
    CPy_DecRef(cpy_r_r1);
    CPy_DecRef(cpy_r_r9);
    CPy_DecRef(cpy_r_r17);
    goto CPyL20;
CPyL25: ;
    CPy_DecRef(cpy_r_r0);
    CPy_DecRef(cpy_r_mat1);
    goto CPyL20;
CPyL26: ;
    CPy_DecRef(cpy_r_r0);
    CPy_DecRef(cpy_r_mat1);
    CPy_DecRef(cpy_r_r30);
    goto CPyL20;
CPyL27: ;
    CPy_DecRef(cpy_r_r0);
    CPy_DecRef(cpy_r_mat1);
    CPy_DecRef(cpy_r_r30);
    CPy_DecRef(cpy_r_r38);
    goto CPyL20;
CPyL28: ;
    CPy_DecRef(cpy_r_r0);
    CPy_DecRef(cpy_r_mat1);
    CPy_DecRef(cpy_r_r30);
    CPy_DecRef(cpy_r_r38);
    CPy_DecRef(cpy_r_r46);
    goto CPyL20;
CPyL29: ;
    CPy_DecRef(cpy_r_r0);
    CPy_DecRef(cpy_r_mat1);
    CPy_DecRef(cpy_r_mat2);
    goto CPyL20;
CPyL30: ;
    CPy_DecRef(cpy_r_r0);
    CPy_DecRef(cpy_r_mat1);
    CPy_DecRef(cpy_r_mat2);
    CPy_DecRef(cpy_r_r59);
    goto CPyL20;
CPyL31: ;
    CPy_DecRef(cpy_r_r0);
    CPy_DecRef(cpy_r_mat1);
    CPy_DecRef(cpy_r_mat2);
    CPy_DecRef(cpy_r_r63);
    goto CPyL20;
CPyL32: ;
    CPy_DECREF(cpy_r_r69);
    goto CPyL14;
CPyL33: ;
    CPy_DecRef(cpy_r_mat1);
    CPy_DecRef(cpy_r_mat2);
    CPy_DecRef(cpy_r_r70);
    goto CPyL20;
CPyL34: ;
    CPy_DecRef(cpy_r_mat1);
    CPy_DecRef(cpy_r_mat2);
    goto CPyL20;
CPyL35: ;
    CPy_DecRef(cpy_r_r74);
    goto CPyL20;
CPyL36: ;
    CPy_DECREF(cpy_r_r80);
    goto CPyL19;
}

PyObject *CPyPy_test(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames) {
    static const char * const kwlist[] = {0};
    static CPyArg_Parser parser = {":test", kwlist, 0};
    if (!CPyArg_ParseStackAndKeywordsNoArgs(args, nargs, kwnames, &parser)) {
        return NULL;
    }
    PyObject *retval = CPyDef_test();
    return retval;
fail: ;
    CPy_AddTraceback("test.py", "test", 1, CPyStatic_globals);
    return NULL;
}

char CPyDef___top_level__(void) {
    PyObject *cpy_r_r0;
    PyObject *cpy_r_r1;
    char cpy_r_r2;
    PyObject *cpy_r_r3;
    PyObject *cpy_r_r4;
    PyObject **cpy_r_r5;
    void *cpy_r_r7;
    void *cpy_r_r9;
    PyObject *cpy_r_r10;
    PyObject *cpy_r_r11;
    PyObject *cpy_r_r12;
    PyObject *cpy_r_r13;
    char cpy_r_r14;
    PyObject *cpy_r_r15;
    PyObject *cpy_r_r16;
    PyObject *cpy_r_r17;
    PyObject *cpy_r_r18;
    CPyTagged cpy_r_r19;
    PyObject *cpy_r_r20;
    PyObject *cpy_r_r21;
    PyObject *cpy_r_r22;
    int32_t cpy_r_r23;
    char cpy_r_r24;
    PyObject *cpy_r_r25;
    PyObject *cpy_r_r26;
    PyObject *cpy_r_r27;
    PyObject *cpy_r_r28;
    PyObject *cpy_r_r29;
    CPyTagged cpy_r_r30;
    PyObject *cpy_r_r31;
    PyObject *cpy_r_r32;
    PyObject *cpy_r_r33;
    int32_t cpy_r_r34;
    char cpy_r_r35;
    PyObject *cpy_r_r36;
    PyObject *cpy_r_r37;
    PyObject *cpy_r_r38;
    PyObject *cpy_r_r39;
    CPyTagged cpy_r_r40;
    PyObject *cpy_r_r41;
    PyObject *cpy_r_r42;
    PyObject *cpy_r_r43;
    CPyTagged cpy_r_r44;
    CPyTagged cpy_r_r45;
    PyObject *cpy_r_r46;
    PyObject *cpy_r_r47;
    PyObject *cpy_r_r48;
    PyObject *cpy_r_r49;
    PyObject *cpy_r_r50;
    PyObject *cpy_r_r51;
    PyObject **cpy_r_r53;
    PyObject *cpy_r_r54;
    char cpy_r_r55;
    cpy_r_r0 = CPyModule_builtins;
    cpy_r_r1 = (PyObject *)&_Py_NoneStruct;
    cpy_r_r2 = cpy_r_r0 != cpy_r_r1;
    if (cpy_r_r2) goto CPyL3;
    cpy_r_r3 = CPyStatics[5]; /* 'builtins' */
    cpy_r_r4 = PyImport_Import(cpy_r_r3);
    if (unlikely(cpy_r_r4 == NULL)) {
        CPy_AddTraceback("test.py", "<module>", -1, CPyStatic_globals);
        goto CPyL22;
    }
    CPyModule_builtins = cpy_r_r4;
    CPy_INCREF(CPyModule_builtins);
    CPy_DECREF(cpy_r_r4);
CPyL3: ;
    cpy_r_r5 = (PyObject **)&CPyModule_time;
    PyObject **cpy_r_r6[1] = {cpy_r_r5};
    cpy_r_r7 = (void *)&cpy_r_r6;
    int64_t cpy_r_r8[1] = {14};
    cpy_r_r9 = (void *)&cpy_r_r8;
    cpy_r_r10 = CPyStatics[24]; /* (('time', 'time', 'time'),) */
    cpy_r_r11 = CPyStatic_globals;
    cpy_r_r12 = CPyStatics[7]; /* 'test.py' */
    cpy_r_r13 = CPyStatics[8]; /* '<module>' */
    cpy_r_r14 = CPyImport_ImportMany(cpy_r_r10, cpy_r_r7, cpy_r_r11, cpy_r_r12, cpy_r_r13, cpy_r_r9);
    if (!cpy_r_r14) goto CPyL22;
    cpy_r_r15 = CPyModule_time;
    cpy_r_r16 = CPyStatics[9]; /* 'perf_counter_ns' */
    cpy_r_r17 = CPyObject_GetAttr(cpy_r_r15, cpy_r_r16);
    if (unlikely(cpy_r_r17 == NULL)) {
        CPy_AddTraceback("test.py", "<module>", 15, CPyStatic_globals);
        goto CPyL22;
    }
    cpy_r_r18 = _PyObject_Vectorcall(cpy_r_r17, 0, 0, 0);
    CPy_DECREF(cpy_r_r17);
    if (unlikely(cpy_r_r18 == NULL)) {
        CPy_AddTraceback("test.py", "<module>", 15, CPyStatic_globals);
        goto CPyL22;
    }
    if (likely(PyLong_Check(cpy_r_r18)))
        cpy_r_r19 = CPyTagged_FromObject(cpy_r_r18);
    else {
        CPy_TypeError("int", cpy_r_r18); cpy_r_r19 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r18);
    if (unlikely(cpy_r_r19 == CPY_INT_TAG)) {
        CPy_AddTraceback("test.py", "<module>", 15, CPyStatic_globals);
        goto CPyL22;
    }
    cpy_r_r20 = CPyStatic_globals;
    cpy_r_r21 = CPyStatics[10]; /* 'start' */
    cpy_r_r22 = CPyTagged_StealAsObject(cpy_r_r19);
    cpy_r_r23 = CPyDict_SetItem(cpy_r_r20, cpy_r_r21, cpy_r_r22);
    CPy_DECREF(cpy_r_r22);
    cpy_r_r24 = cpy_r_r23 >= 0;
    if (unlikely(!cpy_r_r24)) {
        CPy_AddTraceback("test.py", "<module>", 15, CPyStatic_globals);
        goto CPyL22;
    }
    cpy_r_r25 = CPyDef_test();
    if (unlikely(cpy_r_r25 == NULL)) {
        CPy_AddTraceback("test.py", "<module>", 16, CPyStatic_globals);
        goto CPyL22;
    } else
        goto CPyL23;
CPyL9: ;
    cpy_r_r26 = CPyModule_time;
    cpy_r_r27 = CPyStatics[9]; /* 'perf_counter_ns' */
    cpy_r_r28 = CPyObject_GetAttr(cpy_r_r26, cpy_r_r27);
    if (unlikely(cpy_r_r28 == NULL)) {
        CPy_AddTraceback("test.py", "<module>", 17, CPyStatic_globals);
        goto CPyL22;
    }
    cpy_r_r29 = _PyObject_Vectorcall(cpy_r_r28, 0, 0, 0);
    CPy_DECREF(cpy_r_r28);
    if (unlikely(cpy_r_r29 == NULL)) {
        CPy_AddTraceback("test.py", "<module>", 17, CPyStatic_globals);
        goto CPyL22;
    }
    if (likely(PyLong_Check(cpy_r_r29)))
        cpy_r_r30 = CPyTagged_FromObject(cpy_r_r29);
    else {
        CPy_TypeError("int", cpy_r_r29); cpy_r_r30 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r29);
    if (unlikely(cpy_r_r30 == CPY_INT_TAG)) {
        CPy_AddTraceback("test.py", "<module>", 17, CPyStatic_globals);
        goto CPyL22;
    }
    cpy_r_r31 = CPyStatic_globals;
    cpy_r_r32 = CPyStatics[11]; /* 'end' */
    cpy_r_r33 = CPyTagged_StealAsObject(cpy_r_r30);
    cpy_r_r34 = CPyDict_SetItem(cpy_r_r31, cpy_r_r32, cpy_r_r33);
    CPy_DECREF(cpy_r_r33);
    cpy_r_r35 = cpy_r_r34 >= 0;
    if (unlikely(!cpy_r_r35)) {
        CPy_AddTraceback("test.py", "<module>", 17, CPyStatic_globals);
        goto CPyL22;
    }
    cpy_r_r36 = CPyStatics[12]; /* 'Time: ' */
    cpy_r_r37 = CPyStatic_globals;
    cpy_r_r38 = CPyStatics[11]; /* 'end' */
    cpy_r_r39 = CPyDict_GetItem(cpy_r_r37, cpy_r_r38);
    if (unlikely(cpy_r_r39 == NULL)) {
        CPy_AddTraceback("test.py", "<module>", 18, CPyStatic_globals);
        goto CPyL22;
    }
    if (likely(PyLong_Check(cpy_r_r39)))
        cpy_r_r40 = CPyTagged_FromObject(cpy_r_r39);
    else {
        CPy_TypeError("int", cpy_r_r39); cpy_r_r40 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r39);
    if (unlikely(cpy_r_r40 == CPY_INT_TAG)) {
        CPy_AddTraceback("test.py", "<module>", 18, CPyStatic_globals);
        goto CPyL22;
    }
    cpy_r_r41 = CPyStatic_globals;
    cpy_r_r42 = CPyStatics[10]; /* 'start' */
    cpy_r_r43 = CPyDict_GetItem(cpy_r_r41, cpy_r_r42);
    if (unlikely(cpy_r_r43 == NULL)) {
        CPy_AddTraceback("test.py", "<module>", 18, CPyStatic_globals);
        goto CPyL24;
    }
    if (likely(PyLong_Check(cpy_r_r43)))
        cpy_r_r44 = CPyTagged_FromObject(cpy_r_r43);
    else {
        CPy_TypeError("int", cpy_r_r43); cpy_r_r44 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r43);
    if (unlikely(cpy_r_r44 == CPY_INT_TAG)) {
        CPy_AddTraceback("test.py", "<module>", 18, CPyStatic_globals);
        goto CPyL24;
    }
    cpy_r_r45 = CPyTagged_Subtract(cpy_r_r40, cpy_r_r44);
    CPyTagged_DECREF(cpy_r_r40);
    CPyTagged_DECREF(cpy_r_r44);
    cpy_r_r46 = CPyTagged_Str(cpy_r_r45);
    CPyTagged_DECREF(cpy_r_r45);
    if (unlikely(cpy_r_r46 == NULL)) {
        CPy_AddTraceback("test.py", "<module>", 18, CPyStatic_globals);
        goto CPyL22;
    }
    cpy_r_r47 = CPyStatics[13]; /* 'ns' */
    cpy_r_r48 = CPyStr_Build(3, cpy_r_r36, cpy_r_r46, cpy_r_r47);
    CPy_DECREF(cpy_r_r46);
    if (unlikely(cpy_r_r48 == NULL)) {
        CPy_AddTraceback("test.py", "<module>", 18, CPyStatic_globals);
        goto CPyL22;
    }
    cpy_r_r49 = CPyModule_builtins;
    cpy_r_r50 = CPyStatics[4]; /* 'print' */
    cpy_r_r51 = CPyObject_GetAttr(cpy_r_r49, cpy_r_r50);
    if (unlikely(cpy_r_r51 == NULL)) {
        CPy_AddTraceback("test.py", "<module>", 18, CPyStatic_globals);
        goto CPyL25;
    }
    PyObject *cpy_r_r52[1] = {cpy_r_r48};
    cpy_r_r53 = (PyObject **)&cpy_r_r52;
    cpy_r_r54 = _PyObject_Vectorcall(cpy_r_r51, cpy_r_r53, 1, 0);
    CPy_DECREF(cpy_r_r51);
    if (unlikely(cpy_r_r54 == NULL)) {
        CPy_AddTraceback("test.py", "<module>", 18, CPyStatic_globals);
        goto CPyL25;
    } else
        goto CPyL26;
CPyL21: ;
    CPy_DECREF(cpy_r_r48);
    return 1;
CPyL22: ;
    cpy_r_r55 = 2;
    return cpy_r_r55;
CPyL23: ;
    CPy_DECREF(cpy_r_r25);
    goto CPyL9;
CPyL24: ;
    CPyTagged_DecRef(cpy_r_r40);
    goto CPyL22;
CPyL25: ;
    CPy_DecRef(cpy_r_r48);
    goto CPyL22;
CPyL26: ;
    CPy_DECREF(cpy_r_r54);
    goto CPyL21;
}

int CPyGlobalsInit(void)
{
    static int is_initialized = 0;
    if (is_initialized) return 0;
    
    CPy_Init();
    CPyModule_test = Py_None;
    CPyModule_builtins = Py_None;
    CPyModule_time = Py_None;
    if (CPyStatics_Initialize(CPyStatics, CPyLit_Str, CPyLit_Bytes, CPyLit_Int, CPyLit_Float, CPyLit_Complex, CPyLit_Tuple, CPyLit_FrozenSet) < 0) {
        return -1;
    }
    is_initialized = 1;
    return 0;
}

PyObject *CPyStatics[25];
const char * const CPyLit_Str[] = {
    "\t\003zip\005print\bbuiltins\004time\atest.py\b<module>\017perf_counter_ns\005start\003end",
    "\002\006Time: \002ns",
    "",
};
const char * const CPyLit_Bytes[] = {
    "",
};
const char * const CPyLit_Int[] = {
    "\t1\0002\0003\0004\0005\0006\0007\0008\0009",
    "",
};
const double CPyLit_Float[] = {0};
const double CPyLit_Complex[] = {0};
const int CPyLit_Tuple[] = {2, 3, 6, 6, 6, 1, 23};
const int CPyLit_FrozenSet[] = {0};
CPyModule *CPyModule_test_internal = NULL;
CPyModule *CPyModule_test;
PyObject *CPyStatic_globals;
CPyModule *CPyModule_builtins;
CPyModule *CPyModule_time;
PyTypeObject *CPyType_test_env;
PyObject *CPyDef_test_env(void);
PyTypeObject *CPyType_transpose_test_obj;
PyObject *CPyDef_transpose_test_obj(void);
PyTypeObject *CPyType_multiply_matrix_test_obj;
PyObject *CPyDef_multiply_matrix_test_obj(void);
PyObject *CPyDef_transpose_test_obj_____get__(PyObject *cpy_r___mypyc_self__, PyObject *cpy_r_instance, PyObject *cpy_r_owner);
PyObject *CPyPy_transpose_test_obj_____get__(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
PyObject *CPyDef_transpose_test_obj_____call__(PyObject *cpy_r___mypyc_self__, PyObject *cpy_r_matrix);
PyObject *CPyPy_transpose_test_obj_____call__(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
PyObject *CPyDef_multiply_matrix_test_obj_____get__(PyObject *cpy_r___mypyc_self__, PyObject *cpy_r_instance, PyObject *cpy_r_owner);
PyObject *CPyPy_multiply_matrix_test_obj_____get__(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
PyObject *CPyDef_multiply_matrix_test_obj_____call__(PyObject *cpy_r___mypyc_self__, PyObject *cpy_r_matrix1, PyObject *cpy_r_matrix2);
PyObject *CPyPy_multiply_matrix_test_obj_____call__(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
PyObject *CPyDef_test(void);
PyObject *CPyPy_test(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
char CPyDef___top_level__(void);
