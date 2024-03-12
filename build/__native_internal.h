#ifndef MYPYC_NATIVE_INTERNAL_H
#define MYPYC_NATIVE_INTERNAL_H
#include <Python.h>
#include <CPy.h>
#include "__native.h"

int CPyGlobalsInit(void);

extern PyObject *CPyStatics[25];
extern const char * const CPyLit_Str[];
extern const char * const CPyLit_Bytes[];
extern const char * const CPyLit_Int[];
extern const double CPyLit_Float[];
extern const double CPyLit_Complex[];
extern const int CPyLit_Tuple[];
extern const int CPyLit_FrozenSet[];
extern CPyModule *CPyModule_test_internal;
extern CPyModule *CPyModule_test;
extern PyObject *CPyStatic_globals;
extern CPyModule *CPyModule_builtins;
extern CPyModule *CPyModule_time;
extern PyTypeObject *CPyType_test_env;
extern PyObject *CPyDef_test_env(void);
extern PyTypeObject *CPyType_transpose_test_obj;
extern PyObject *CPyDef_transpose_test_obj(void);
extern PyTypeObject *CPyType_multiply_matrix_test_obj;
extern PyObject *CPyDef_multiply_matrix_test_obj(void);
extern PyObject *CPyDef_transpose_test_obj_____get__(PyObject *cpy_r___mypyc_self__, PyObject *cpy_r_instance, PyObject *cpy_r_owner);
extern PyObject *CPyPy_transpose_test_obj_____get__(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
extern PyObject *CPyDef_transpose_test_obj_____call__(PyObject *cpy_r___mypyc_self__, PyObject *cpy_r_matrix);
extern PyObject *CPyPy_transpose_test_obj_____call__(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
extern PyObject *CPyDef_multiply_matrix_test_obj_____get__(PyObject *cpy_r___mypyc_self__, PyObject *cpy_r_instance, PyObject *cpy_r_owner);
extern PyObject *CPyPy_multiply_matrix_test_obj_____get__(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
extern PyObject *CPyDef_multiply_matrix_test_obj_____call__(PyObject *cpy_r___mypyc_self__, PyObject *cpy_r_matrix1, PyObject *cpy_r_matrix2);
extern PyObject *CPyPy_multiply_matrix_test_obj_____call__(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
extern PyObject *CPyDef_test(void);
extern PyObject *CPyPy_test(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
extern char CPyDef___top_level__(void);
#endif
