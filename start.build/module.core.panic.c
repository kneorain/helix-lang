/* Generated code for Python module 'core$panic'
 * created by Nuitka version 2.0.2
 *
 * This code is in part copyright 2023 Kay Hayen.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "nuitka/prelude.h"

#include "nuitka/unfreezing.h"

#include "__helpers.h"

/* The "module_core$panic" is a Python object pointer of module type.
 *
 * Note: For full compatibility with CPython, every module variable access
 * needs to go through it except for cases where the module cannot possibly
 * have changed in the mean time.
 */

PyObject *module_core$panic;
PyDictObject *moduledict_core$panic;

/* The declarations of module constants used, if any. */
static PyObject *mod_consts[293];
#ifndef __NUITKA_NO_ASSERT__
static Py_hash_t mod_consts_hash[293];
#endif

static PyObject *module_filename_obj = NULL;

/* Indicator if this modules private constants were created yet. */
static bool constants_created = false;

/* Function to create module private constants. */
static void createModuleConstants(PyThreadState *tstate) {
    if (constants_created == false) {
        loadConstantsBlob(tstate, &mod_consts[0], UNTRANSLATE("core.panic"));
        constants_created = true;

#ifndef __NUITKA_NO_ASSERT__
        for (int i = 0; i < 293; i++) {
            mod_consts_hash[i] = DEEP_HASH(tstate, mod_consts[i]);
        }
#endif
    }
}

// We want to be able to initialize the "__main__" constants in any case.
#if 0
void createMainModuleConstants(PyThreadState *tstate) {
    createModuleConstants(tstate);
}
#endif

/* Function to verify module private constants for non-corruption. */
#ifndef __NUITKA_NO_ASSERT__
void checkModuleConstants_core$panic(PyThreadState *tstate) {
    // The module may not have been used at all, then ignore this.
    if (constants_created == false) return;

    for (int i = 0; i < 293; i++) {
        assert(mod_consts_hash[i] == DEEP_HASH(tstate, mod_consts[i]));
        CHECK_OBJECT_DEEP(mod_consts[i]);
    }
}
#endif

// The module code objects.
static PyCodeObject *codeobj_a2676065e0c895da5b2c9b4d6277da45;
static PyCodeObject *codeobj_ead9b724b65ce3c43b718984fb92cd7f;
static PyCodeObject *codeobj_023af1584b736d71b82c14535d5153cb;
static PyCodeObject *codeobj_14702094d157de72a92e00898e7cc298;
static PyCodeObject *codeobj_ad821e1969a34aa46a58d160b9d25a85;
static PyCodeObject *codeobj_2edbc9deccd9aaf2cd319e276c33377e;
static PyCodeObject *codeobj_e1d27883b2455e4c949dff371c0a8ceb;
static PyCodeObject *codeobj_8318cdda338d5f423c718cf0c36f6739;
static PyCodeObject *codeobj_cfbb1fd5c2fa73ae6fa06e61890dd7dd;
static PyCodeObject *codeobj_45103d0afa02f9f8fd0f6e5356c4a2d9;
static PyCodeObject *codeobj_7bf646c481fc4ce8df0b213af78a07e9;

static void createModuleCodeObjects(void) {
    module_filename_obj = MAKE_RELATIVE_PATH(mod_consts[275]); CHECK_OBJECT(module_filename_obj);
    codeobj_a2676065e0c895da5b2c9b4d6277da45 = MAKE_CODE_OBJECT(module_filename_obj, 1, 0, mod_consts[276], mod_consts[276], NULL, NULL, 0, 0, 0);
    codeobj_ead9b724b65ce3c43b718984fb92cd7f = MAKE_CODE_OBJECT(module_filename_obj, 18, 0, mod_consts[165], mod_consts[165], mod_consts[277], NULL, 0, 0, 0);
    codeobj_023af1584b736d71b82c14535d5153cb = MAKE_CODE_OBJECT(module_filename_obj, 168, CO_OPTIMIZED | CO_NEWLOCALS, mod_consts[27], mod_consts[27], mod_consts[278], mod_consts[279], 1, 0, 0);
    codeobj_14702094d157de72a92e00898e7cc298 = MAKE_CODE_OBJECT(module_filename_obj, 182, CO_OPTIMIZED | CO_NEWLOCALS, mod_consts[29], mod_consts[29], mod_consts[280], mod_consts[281], 1, 0, 0);
    codeobj_ad821e1969a34aa46a58d160b9d25a85 = MAKE_CODE_OBJECT(module_filename_obj, 123, CO_OPTIMIZED | CO_NEWLOCALS, mod_consts[264], mod_consts[264], mod_consts[282], NULL, 1, 0, 0);
    codeobj_2edbc9deccd9aaf2cd319e276c33377e = MAKE_CODE_OBJECT(module_filename_obj, 195, CO_OPTIMIZED | CO_NEWLOCALS, mod_consts[32], mod_consts[32], mod_consts[283], mod_consts[284], 1, 0, 0);
    codeobj_e1d27883b2455e4c949dff371c0a8ceb = MAKE_CODE_OBJECT(module_filename_obj, 204, CO_OPTIMIZED | CO_NEWLOCALS, mod_consts[35], mod_consts[35], mod_consts[285], mod_consts[286], 2, 0, 0);
    codeobj_8318cdda338d5f423c718cf0c36f6739 = MAKE_CODE_OBJECT(module_filename_obj, 134, CO_OPTIMIZED | CO_NEWLOCALS | CO_VARARGS, mod_consts[274], mod_consts[274], mod_consts[287], NULL, 1, 2, 0);
    codeobj_cfbb1fd5c2fa73ae6fa06e61890dd7dd = MAKE_CODE_OBJECT(module_filename_obj, 259, CO_OPTIMIZED | CO_NEWLOCALS, mod_consts[41], mod_consts[41], mod_consts[288], mod_consts[289], 2, 0, 0);
    codeobj_45103d0afa02f9f8fd0f6e5356c4a2d9 = MAKE_CODE_OBJECT(module_filename_obj, 295, CO_OPTIMIZED | CO_NEWLOCALS, mod_consts[77], mod_consts[77], mod_consts[290], mod_consts[291], 1, 0, 0);
    codeobj_7bf646c481fc4ce8df0b213af78a07e9 = MAKE_CODE_OBJECT(module_filename_obj, 253, CO_OPTIMIZED | CO_NEWLOCALS, mod_consts[38], mod_consts[38], mod_consts[292], NULL, 1, 0, 0);
}

// The module function declarations.
NUITKA_CROSS_MODULE PyObject *impl___main__$$$function__5__mro_entries_conversion(PyThreadState *tstate, PyObject **python_pars);


static PyObject *MAKE_FUNCTION_core$panic$$$function__1_highlight_code(PyObject *annotations);


static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic(PyObject *kw_defaults, PyObject *annotations);


static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__1_calculate_skip_ammout(PyObject *annotations, struct Nuitka_CellObject **closure);


static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__2_count_spaces(PyObject *annotations, struct Nuitka_CellObject **closure);


static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__3_line_without_spaces(PyObject *annotations, struct Nuitka_CellObject **closure);


static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__4_mark_all(PyObject *annotations, struct Nuitka_CellObject **closure);


static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__5_s_u(PyObject *annotations);


static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__6_process_lines(PyObject *annotations, struct Nuitka_CellObject **closure);


static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__7_process_message(PyObject *annotations, struct Nuitka_CellObject **closure);


// The module function definitions.
static PyObject *impl_core$panic$$$function__1_highlight_code(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *par_code = python_pars[0];
    struct Nuitka_FrameObject *frame_ad821e1969a34aa46a58d160b9d25a85;
    NUITKA_MAY_BE_UNUSED char const *type_description_1 = NULL;
    PyObject *tmp_return_value = NULL;
    PyObject *exception_type = NULL;
    PyObject *exception_value = NULL;
    PyTracebackObject *exception_tb = NULL;
    NUITKA_MAY_BE_UNUSED int exception_lineno = 0;
    static struct Nuitka_FrameObject *cache_frame_ad821e1969a34aa46a58d160b9d25a85 = NULL;

    // Actual function body.
    if (isFrameUnusable(cache_frame_ad821e1969a34aa46a58d160b9d25a85)) {
        Py_XDECREF(cache_frame_ad821e1969a34aa46a58d160b9d25a85);

#if _DEBUG_REFCOUNTS
        if (cache_frame_ad821e1969a34aa46a58d160b9d25a85 == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_frame_ad821e1969a34aa46a58d160b9d25a85 = MAKE_FUNCTION_FRAME(tstate, codeobj_ad821e1969a34aa46a58d160b9d25a85, module_core$panic, sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_frame_ad821e1969a34aa46a58d160b9d25a85->m_type_description == NULL);
    frame_ad821e1969a34aa46a58d160b9d25a85 = cache_frame_ad821e1969a34aa46a58d160b9d25a85;

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackCompiledFrame(tstate, frame_ad821e1969a34aa46a58d160b9d25a85);
    assert(Py_REFCNT(frame_ad821e1969a34aa46a58d160b9d25a85) == 2);

    // Framed code:
    {
        PyObject *tmp_called_value_1;
        PyObject *tmp_args_element_value_1;
        PyObject *tmp_args_element_value_2;
        PyObject *tmp_args_element_value_3;
        tmp_called_value_1 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[0]);

        if (unlikely(tmp_called_value_1 == NULL)) {
            tmp_called_value_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[0]);
        }

        if (tmp_called_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 124;
            type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(par_code);
        tmp_args_element_value_1 = par_code;
        tmp_args_element_value_2 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[1]);

        if (unlikely(tmp_args_element_value_2 == NULL)) {
            tmp_args_element_value_2 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[1]);
        }

        if (tmp_args_element_value_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 124;
            type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_args_element_value_3 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[2]);

        if (unlikely(tmp_args_element_value_3 == NULL)) {
            tmp_args_element_value_3 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[2]);
        }

        if (tmp_args_element_value_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 124;
            type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        frame_ad821e1969a34aa46a58d160b9d25a85->m_frame.f_lineno = 124;
        {
            PyObject *call_args[] = {tmp_args_element_value_1, tmp_args_element_value_2, tmp_args_element_value_3};
            tmp_return_value = CALL_FUNCTION_WITH_ARGS3(tstate, tmp_called_value_1, call_args);
        }

        if (tmp_return_value == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 124;
            type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        goto frame_return_exit_1;
    }


    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto frame_no_exception_1;
    frame_return_exit_1:

    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto function_return_exit;
    frame_exception_exit_1:


    if (exception_tb == NULL) {
        exception_tb = MAKE_TRACEBACK(frame_ad821e1969a34aa46a58d160b9d25a85, exception_lineno);
    } else if (exception_tb->tb_frame != &frame_ad821e1969a34aa46a58d160b9d25a85->m_frame) {
        exception_tb = ADD_TRACEBACK(exception_tb, frame_ad821e1969a34aa46a58d160b9d25a85, exception_lineno);
    }

    // Attaches locals to frame if any.
    Nuitka_Frame_AttachLocals(
        frame_ad821e1969a34aa46a58d160b9d25a85,
        type_description_1,
        par_code
    );


    // Release cached frame if used for exception.
    if (frame_ad821e1969a34aa46a58d160b9d25a85 == cache_frame_ad821e1969a34aa46a58d160b9d25a85) {
#if _DEBUG_REFCOUNTS
        count_active_frame_cache_instances -= 1;
        count_released_frame_cache_instances += 1;
#endif
        Py_DECREF(cache_frame_ad821e1969a34aa46a58d160b9d25a85);
        cache_frame_ad821e1969a34aa46a58d160b9d25a85 = NULL;
    }

    assertFrameObject(frame_ad821e1969a34aa46a58d160b9d25a85);

    // Put the previous frame back on top.
    popFrameStack(tstate);

    // Return the error.
    goto function_exception_exit;
    frame_no_exception_1:;

    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;

function_exception_exit:
    CHECK_OBJECT(par_code);
    Py_DECREF(par_code);
    assert(exception_type);
    RESTORE_ERROR_OCCURRED(tstate, exception_type, exception_value, exception_tb);

    return NULL;

function_return_exit:
   // Function cleanup code if any.
    CHECK_OBJECT(par_code);
    Py_DECREF(par_code);

   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}


static PyObject *impl_core$panic$$$function__2_panic(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *par___error = python_pars[0];
    PyObject *par_file = python_pars[1];
    struct Nuitka_CellObject *par_line_no = Nuitka_Cell_New1(python_pars[2]);
    struct Nuitka_CellObject *par_mark = Nuitka_Cell_New1(python_pars[3]);
    struct Nuitka_CellObject *var_lines_to_print = Nuitka_Cell_NewEmpty();
    PyObject *var_name = NULL;
    PyObject *var_message = NULL;
    struct Nuitka_CellObject *var_lines = Nuitka_Cell_NewEmpty();
    struct Nuitka_CellObject *var_does_support_colors = Nuitka_Cell_NewEmpty();
    PyObject *var_top_section = NULL;
    PyObject *var_len_of_file = NULL;
    PyObject *var_final_line = NULL;
    struct Nuitka_CellObject *var_chars = Nuitka_Cell_NewEmpty();
    PyObject *var_sys = NULL;
    struct Nuitka_CellObject *var_red = Nuitka_Cell_NewEmpty();
    struct Nuitka_CellObject *var_bold_red = Nuitka_Cell_NewEmpty();
    struct Nuitka_CellObject *var_reset = Nuitka_Cell_NewEmpty();
    struct Nuitka_CellObject *var_gray = Nuitka_Cell_NewEmpty();
    struct Nuitka_CellObject *var_yellow = Nuitka_Cell_NewEmpty();
    PyObject *var_green = NULL;
    struct Nuitka_CellObject *var_calculate_skip_ammout = Nuitka_Cell_NewEmpty();
    struct Nuitka_CellObject *var_count_spaces = Nuitka_Cell_NewEmpty();
    struct Nuitka_CellObject *var_line_without_spaces = Nuitka_Cell_NewEmpty();
    PyObject *var_mark_all = NULL;
    struct Nuitka_CellObject *var_s_u = Nuitka_Cell_NewEmpty();
    PyObject *var_process_lines = NULL;
    PyObject *var_mid_section = NULL;
    struct Nuitka_CellObject *var_hex_code = Nuitka_Cell_NewEmpty();
    struct Nuitka_CellObject *var__hex_code = Nuitka_Cell_NewEmpty();
    PyObject *var_process_message = NULL;
    PyObject *var_len_of_halfs = NULL;
    PyObject *var_os = NULL;
    PyObject *outline_0_var_item = NULL;
    PyObject *outline_1_var_index = NULL;
    PyObject *outline_1_var_line = NULL;
    PyObject *tmp_listcomp$tuple_unpack_1__element_1 = NULL;
    PyObject *tmp_listcomp$tuple_unpack_1__element_2 = NULL;
    PyObject *tmp_listcomp$tuple_unpack_1__source_iter = NULL;
    PyObject *tmp_listcomp_1__$0 = NULL;
    PyObject *tmp_listcomp_1__contraction = NULL;
    PyObject *tmp_listcomp_1__iter_value_0 = NULL;
    PyObject *tmp_listcomp_2__$0 = NULL;
    PyObject *tmp_listcomp_2__contraction = NULL;
    PyObject *tmp_listcomp_2__iter_value_0 = NULL;
    PyObject *tmp_tuple_unpack_1__element_1 = NULL;
    PyObject *tmp_tuple_unpack_1__element_2 = NULL;
    PyObject *tmp_tuple_unpack_1__element_3 = NULL;
    PyObject *tmp_tuple_unpack_1__element_4 = NULL;
    PyObject *tmp_tuple_unpack_1__element_5 = NULL;
    PyObject *tmp_tuple_unpack_1__element_6 = NULL;
    PyObject *tmp_tuple_unpack_1__source_iter = NULL;
    struct Nuitka_FrameObject *frame_8318cdda338d5f423c718cf0c36f6739;
    NUITKA_MAY_BE_UNUSED char const *type_description_1 = NULL;
    NUITKA_MAY_BE_UNUSED nuitka_void tmp_unused;
    PyObject *exception_type = NULL;
    PyObject *exception_value = NULL;
    PyTracebackObject *exception_tb = NULL;
    NUITKA_MAY_BE_UNUSED int exception_lineno = 0;
    bool tmp_result;
    PyObject *exception_keeper_type_1;
    PyObject *exception_keeper_value_1;
    PyTracebackObject *exception_keeper_tb_1;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_1;
    PyObject *exception_keeper_type_2;
    PyObject *exception_keeper_value_2;
    PyTracebackObject *exception_keeper_tb_2;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_2;
    int tmp_res;
    PyObject *tmp_iterator_attempt;
    PyObject *exception_keeper_type_3;
    PyObject *exception_keeper_value_3;
    PyTracebackObject *exception_keeper_tb_3;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_3;
    PyObject *exception_keeper_type_4;
    PyObject *exception_keeper_value_4;
    PyTracebackObject *exception_keeper_tb_4;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_4;
    PyObject *exception_keeper_type_5;
    PyObject *exception_keeper_value_5;
    PyTracebackObject *exception_keeper_tb_5;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_5;
    PyObject *exception_keeper_type_6;
    PyObject *exception_keeper_value_6;
    PyTracebackObject *exception_keeper_tb_6;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_6;
    PyObject *exception_keeper_type_7;
    PyObject *exception_keeper_value_7;
    PyTracebackObject *exception_keeper_tb_7;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_7;
    PyObject *exception_keeper_type_8;
    PyObject *exception_keeper_value_8;
    PyTracebackObject *exception_keeper_tb_8;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_8;
    static struct Nuitka_FrameObject *cache_frame_8318cdda338d5f423c718cf0c36f6739 = NULL;
    PyObject *tmp_return_value = NULL;
    PyObject *exception_keeper_type_9;
    PyObject *exception_keeper_value_9;
    PyTracebackObject *exception_keeper_tb_9;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_9;

    // Actual function body.
    // Tried code:
    if (isFrameUnusable(cache_frame_8318cdda338d5f423c718cf0c36f6739)) {
        Py_XDECREF(cache_frame_8318cdda338d5f423c718cf0c36f6739);

#if _DEBUG_REFCOUNTS
        if (cache_frame_8318cdda338d5f423c718cf0c36f6739 == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_frame_8318cdda338d5f423c718cf0c36f6739 = MAKE_FUNCTION_FRAME(tstate, codeobj_8318cdda338d5f423c718cf0c36f6739, module_core$panic, sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_frame_8318cdda338d5f423c718cf0c36f6739->m_type_description == NULL);
    frame_8318cdda338d5f423c718cf0c36f6739 = cache_frame_8318cdda338d5f423c718cf0c36f6739;

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackCompiledFrame(tstate, frame_8318cdda338d5f423c718cf0c36f6739);
    assert(Py_REFCNT(frame_8318cdda338d5f423c718cf0c36f6739) == 2);

    // Framed code:
    {
        PyObject *tmp_called_instance_1;
        PyObject *tmp_call_result_1;
        tmp_called_instance_1 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[3]);

        if (unlikely(tmp_called_instance_1 == NULL)) {
            tmp_called_instance_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[3]);
        }

        if (tmp_called_instance_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 135;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 135;
        tmp_call_result_1 = CALL_METHOD_NO_ARGS(tstate, tmp_called_instance_1, mod_consts[4]);
        if (tmp_call_result_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 135;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        Py_DECREF(tmp_call_result_1);
    }
    {
        PyObject *tmp_assign_source_1;
        tmp_assign_source_1 = mod_consts[5];
        assert(Nuitka_Cell_GET(var_lines_to_print) == NULL);
        Py_INCREF(tmp_assign_source_1);
        PyCell_SET(var_lines_to_print, tmp_assign_source_1);

    }
    {
        PyObject *tmp_assign_source_2;
        // Tried code:
        {
            PyObject *tmp_assign_source_3;
            PyObject *tmp_iter_arg_1;
            CHECK_OBJECT(Nuitka_Cell_GET(par_mark));
            tmp_iter_arg_1 = Nuitka_Cell_GET(par_mark);
            tmp_assign_source_3 = MAKE_ITERATOR(tstate, tmp_iter_arg_1);
            if (tmp_assign_source_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 138;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto try_except_handler_2;
            }
            assert(tmp_listcomp_1__$0 == NULL);
            tmp_listcomp_1__$0 = tmp_assign_source_3;
        }
        {
            PyObject *tmp_assign_source_4;
            tmp_assign_source_4 = MAKE_LIST_EMPTY(0);
            assert(tmp_listcomp_1__contraction == NULL);
            tmp_listcomp_1__contraction = tmp_assign_source_4;
        }
        // Tried code:
        loop_start_1:;
        {
            PyObject *tmp_next_source_1;
            PyObject *tmp_assign_source_5;
            CHECK_OBJECT(tmp_listcomp_1__$0);
            tmp_next_source_1 = tmp_listcomp_1__$0;
            tmp_assign_source_5 = ITERATOR_NEXT(tmp_next_source_1);
            if (tmp_assign_source_5 == NULL) {
                if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                    goto loop_end_1;
                } else {

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                    type_description_1 = "oocccooccooococccccocccocooccooo";
                    exception_lineno = 138;
                    goto try_except_handler_3;
                }
            }

            {
                PyObject *old = tmp_listcomp_1__iter_value_0;
                tmp_listcomp_1__iter_value_0 = tmp_assign_source_5;
                Py_XDECREF(old);
            }

        }
        {
            PyObject *tmp_assign_source_6;
            CHECK_OBJECT(tmp_listcomp_1__iter_value_0);
            tmp_assign_source_6 = tmp_listcomp_1__iter_value_0;
            {
                PyObject *old = outline_0_var_item;
                outline_0_var_item = tmp_assign_source_6;
                Py_INCREF(outline_0_var_item);
                Py_XDECREF(old);
            }

        }
        {
            PyObject *tmp_append_list_1;
            PyObject *tmp_append_value_1;
            PyObject *tmp_unicode_arg_1;
            CHECK_OBJECT(tmp_listcomp_1__contraction);
            tmp_append_list_1 = tmp_listcomp_1__contraction;
            CHECK_OBJECT(outline_0_var_item);
            tmp_unicode_arg_1 = outline_0_var_item;
            tmp_append_value_1 = BUILTIN_UNICODE1(tmp_unicode_arg_1);
            if (tmp_append_value_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 138;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto try_except_handler_3;
            }
            tmp_result = LIST_APPEND1(tmp_append_list_1, tmp_append_value_1);
            if (tmp_result == false) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 138;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto try_except_handler_3;
            }
        }
        if (CONSIDER_THREADING(tstate) == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 138;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto try_except_handler_3;
        }
        goto loop_start_1;
        loop_end_1:;
        CHECK_OBJECT(tmp_listcomp_1__contraction);
        tmp_assign_source_2 = tmp_listcomp_1__contraction;
        Py_INCREF(tmp_assign_source_2);
        goto try_return_handler_3;
        NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
        return NULL;
        // Return handler code:
        try_return_handler_3:;
        CHECK_OBJECT(tmp_listcomp_1__$0);
        Py_DECREF(tmp_listcomp_1__$0);
        tmp_listcomp_1__$0 = NULL;
        CHECK_OBJECT(tmp_listcomp_1__contraction);
        Py_DECREF(tmp_listcomp_1__contraction);
        tmp_listcomp_1__contraction = NULL;
        Py_XDECREF(tmp_listcomp_1__iter_value_0);
        tmp_listcomp_1__iter_value_0 = NULL;
        goto try_return_handler_2;
        // Exception handler code:
        try_except_handler_3:;
        exception_keeper_type_1 = exception_type;
        exception_keeper_value_1 = exception_value;
        exception_keeper_tb_1 = exception_tb;
        exception_keeper_lineno_1 = exception_lineno;
        exception_type = NULL;
        exception_value = NULL;
        exception_tb = NULL;
        exception_lineno = 0;

        CHECK_OBJECT(tmp_listcomp_1__$0);
        Py_DECREF(tmp_listcomp_1__$0);
        tmp_listcomp_1__$0 = NULL;
        CHECK_OBJECT(tmp_listcomp_1__contraction);
        Py_DECREF(tmp_listcomp_1__contraction);
        tmp_listcomp_1__contraction = NULL;
        Py_XDECREF(tmp_listcomp_1__iter_value_0);
        tmp_listcomp_1__iter_value_0 = NULL;
        // Re-raise.
        exception_type = exception_keeper_type_1;
        exception_value = exception_keeper_value_1;
        exception_tb = exception_keeper_tb_1;
        exception_lineno = exception_keeper_lineno_1;

        goto try_except_handler_2;
        // End of try:
        NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
        return NULL;
        // Return handler code:
        try_return_handler_2:;
        Py_XDECREF(outline_0_var_item);
        outline_0_var_item = NULL;
        goto outline_result_1;
        // Exception handler code:
        try_except_handler_2:;
        exception_keeper_type_2 = exception_type;
        exception_keeper_value_2 = exception_value;
        exception_keeper_tb_2 = exception_tb;
        exception_keeper_lineno_2 = exception_lineno;
        exception_type = NULL;
        exception_value = NULL;
        exception_tb = NULL;
        exception_lineno = 0;

        Py_XDECREF(outline_0_var_item);
        outline_0_var_item = NULL;
        // Re-raise.
        exception_type = exception_keeper_type_2;
        exception_value = exception_keeper_value_2;
        exception_tb = exception_keeper_tb_2;
        exception_lineno = exception_keeper_lineno_2;

        goto outline_exception_1;
        // End of try:
        NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
        return NULL;
        outline_exception_1:;
        exception_lineno = 138;
        goto frame_exception_exit_1;
        outline_result_1:;
        {
            PyObject *old = Nuitka_Cell_GET(par_mark);
            PyCell_SET(par_mark, tmp_assign_source_2);
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_7;
        PyObject *tmp_expression_value_1;
        PyObject *tmp_expression_value_2;
        CHECK_OBJECT(par___error);
        tmp_expression_value_2 = par___error;
        tmp_expression_value_1 = LOOKUP_ATTRIBUTE_CLASS_SLOT(tstate, tmp_expression_value_2);
        if (tmp_expression_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 140;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_7 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_1, mod_consts[6]);
        Py_DECREF(tmp_expression_value_1);
        if (tmp_assign_source_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 140;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        assert(var_name == NULL);
        var_name = tmp_assign_source_7;
    }
    {
        PyObject *tmp_assign_source_8;
        PyObject *tmp_unicode_arg_2;
        CHECK_OBJECT(par___error);
        tmp_unicode_arg_2 = par___error;
        tmp_assign_source_8 = BUILTIN_UNICODE1(tmp_unicode_arg_2);
        if (tmp_assign_source_8 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 141;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        assert(var_message == NULL);
        var_message = tmp_assign_source_8;
    }
    {
        PyObject *tmp_assign_source_9;
        bool tmp_condition_result_1;
        PyObject *tmp_operand_value_1;
        PyObject *tmp_expression_value_3;
        PyObject *tmp_expression_value_4;
        PyObject *tmp_expression_value_5;
        PyObject *tmp_called_instance_2;
        CHECK_OBJECT(Nuitka_Cell_GET(par_line_no));
        tmp_operand_value_1 = Nuitka_Cell_GET(par_line_no);
        tmp_res = CHECK_IF_TRUE(tmp_operand_value_1);
        if (tmp_res == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 143;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_1 = (tmp_res == 0) ? true : false;
        if (tmp_condition_result_1 != false) {
            goto condexpr_true_1;
        } else {
            goto condexpr_false_1;
        }
        condexpr_true_1:;
        tmp_called_instance_2 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[7]);

        if (unlikely(tmp_called_instance_2 == NULL)) {
            tmp_called_instance_2 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[7]);
        }

        if (tmp_called_instance_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 143;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 143;
        tmp_expression_value_5 = CALL_METHOD_NO_ARGS(tstate, tmp_called_instance_2, mod_consts[8]);
        if (tmp_expression_value_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 143;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_expression_value_4 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_5, mod_consts[9]);
        Py_DECREF(tmp_expression_value_5);
        if (tmp_expression_value_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 143;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_expression_value_3 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_4, mod_consts[9]);
        Py_DECREF(tmp_expression_value_4);
        if (tmp_expression_value_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 143;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_9 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_3, mod_consts[10]);
        Py_DECREF(tmp_expression_value_3);
        if (tmp_assign_source_9 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 143;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        goto condexpr_end_1;
        condexpr_false_1:;
        CHECK_OBJECT(Nuitka_Cell_GET(par_line_no));
        tmp_assign_source_9 = Nuitka_Cell_GET(par_line_no);
        Py_INCREF(tmp_assign_source_9);
        condexpr_end_1:;
        {
            PyObject *old = Nuitka_Cell_GET(par_line_no);
            PyCell_SET(par_line_no, tmp_assign_source_9);
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_10;
        bool tmp_condition_result_2;
        PyObject *tmp_operand_value_2;
        PyObject *tmp_expression_value_6;
        PyObject *tmp_expression_value_7;
        PyObject *tmp_expression_value_8;
        PyObject *tmp_called_instance_3;
        CHECK_OBJECT(par_file);
        tmp_operand_value_2 = par_file;
        tmp_res = CHECK_IF_TRUE(tmp_operand_value_2);
        if (tmp_res == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 144;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_2 = (tmp_res == 0) ? true : false;
        if (tmp_condition_result_2 != false) {
            goto condexpr_true_2;
        } else {
            goto condexpr_false_2;
        }
        condexpr_true_2:;
        tmp_called_instance_3 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[7]);

        if (unlikely(tmp_called_instance_3 == NULL)) {
            tmp_called_instance_3 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[7]);
        }

        if (tmp_called_instance_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 144;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 144;
        tmp_expression_value_8 = CALL_METHOD_NO_ARGS(tstate, tmp_called_instance_3, mod_consts[8]);
        if (tmp_expression_value_8 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 144;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_expression_value_7 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_8, mod_consts[9]);
        Py_DECREF(tmp_expression_value_8);
        if (tmp_expression_value_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 144;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_expression_value_6 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_7, mod_consts[11]);
        Py_DECREF(tmp_expression_value_7);
        if (tmp_expression_value_6 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 144;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_10 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_6, mod_consts[12]);
        Py_DECREF(tmp_expression_value_6);
        if (tmp_assign_source_10 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 144;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        goto condexpr_end_2;
        condexpr_false_2:;
        CHECK_OBJECT(par_file);
        tmp_assign_source_10 = par_file;
        Py_INCREF(tmp_assign_source_10);
        condexpr_end_2:;
        {
            PyObject *old = par_file;
            assert(old != NULL);
            par_file = tmp_assign_source_10;
            Py_DECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_11;
        PyObject *tmp_expression_value_9;
        PyObject *tmp_called_instance_4;
        PyObject *tmp_open_filename_1;
        PyObject *tmp_open_mode_1;
        PyObject *tmp_subscript_value_1;
        PyObject *tmp_start_value_1;
        nuitka_bool tmp_condition_result_3;
        PyObject *tmp_cmp_expr_left_1;
        PyObject *tmp_cmp_expr_right_1;
        PyObject *tmp_sub_expr_left_1;
        PyObject *tmp_sub_expr_right_1;
        PyObject *tmp_sub_expr_left_2;
        PyObject *tmp_sub_expr_right_2;
        PyObject *tmp_stop_value_1;
        CHECK_OBJECT(par_file);
        tmp_open_filename_1 = par_file;
        tmp_open_mode_1 = mod_consts[13];
        tmp_called_instance_4 = BUILTIN_OPEN(tstate, tmp_open_filename_1, tmp_open_mode_1, NULL, NULL, NULL, NULL, NULL, NULL);
        if (tmp_called_instance_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 145;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 145;
        tmp_expression_value_9 = CALL_METHOD_NO_ARGS(tstate, tmp_called_instance_4, mod_consts[14]);
        Py_DECREF(tmp_called_instance_4);
        if (tmp_expression_value_9 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 145;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(Nuitka_Cell_GET(par_line_no));
        tmp_sub_expr_left_1 = Nuitka_Cell_GET(par_line_no);
        CHECK_OBJECT(Nuitka_Cell_GET(var_lines_to_print));
        tmp_sub_expr_right_1 = Nuitka_Cell_GET(var_lines_to_print);
        tmp_cmp_expr_left_1 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_1, tmp_sub_expr_right_1);
        if (tmp_cmp_expr_left_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_expression_value_9);

            exception_lineno = 145;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_cmp_expr_right_1 = mod_consts[15];
        tmp_condition_result_3 = RICH_COMPARE_GT_NBOOL_OBJECT_LONG(tmp_cmp_expr_left_1, tmp_cmp_expr_right_1);
        Py_DECREF(tmp_cmp_expr_left_1);
        if (tmp_condition_result_3 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_expression_value_9);

            exception_lineno = 145;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        if (tmp_condition_result_3 == NUITKA_BOOL_TRUE) {
            goto condexpr_true_3;
        } else {
            goto condexpr_false_3;
        }
        condexpr_true_3:;
        CHECK_OBJECT(Nuitka_Cell_GET(par_line_no));
        tmp_sub_expr_left_2 = Nuitka_Cell_GET(par_line_no);
        CHECK_OBJECT(Nuitka_Cell_GET(var_lines_to_print));
        tmp_sub_expr_right_2 = Nuitka_Cell_GET(var_lines_to_print);
        tmp_start_value_1 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_2, tmp_sub_expr_right_2);
        if (tmp_start_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_expression_value_9);

            exception_lineno = 145;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        goto condexpr_end_3;
        condexpr_false_3:;
        tmp_start_value_1 = mod_consts[15];
        Py_INCREF(tmp_start_value_1);
        condexpr_end_3:;
        CHECK_OBJECT(Nuitka_Cell_GET(par_line_no));
        tmp_stop_value_1 = Nuitka_Cell_GET(par_line_no);
        tmp_subscript_value_1 = MAKE_SLICE_OBJECT2(tmp_start_value_1, tmp_stop_value_1);
        Py_DECREF(tmp_start_value_1);
        assert(!(tmp_subscript_value_1 == NULL));
        tmp_assign_source_11 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_9, tmp_subscript_value_1);
        Py_DECREF(tmp_expression_value_9);
        Py_DECREF(tmp_subscript_value_1);
        if (tmp_assign_source_11 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 145;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        assert(Nuitka_Cell_GET(var_lines) == NULL);
        PyCell_SET(var_lines, tmp_assign_source_11);

    }
    {
        PyObject *tmp_assign_source_12;
        tmp_assign_source_12 = DICT_COPY(mod_consts[16]);
        assert(Nuitka_Cell_GET(var_chars) == NULL);
        PyCell_SET(var_chars, tmp_assign_source_12);

    }
    {
        PyObject *tmp_assign_source_13;
        tmp_assign_source_13 = IMPORT_HARD_SYS();
        assert(!(tmp_assign_source_13 == NULL));
        assert(var_sys == NULL);
        Py_INCREF(tmp_assign_source_13);
        var_sys = tmp_assign_source_13;
    }
    {
        PyObject *tmp_assign_source_14;
        PyObject *tmp_called_instance_5;
        tmp_called_instance_5 = Nuitka_SysGetObject("stdout");
        assert(!(tmp_called_instance_5 == NULL));
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 157;
        tmp_assign_source_14 = CALL_METHOD_NO_ARGS(tstate, tmp_called_instance_5, mod_consts[17]);
        if (tmp_assign_source_14 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 157;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        assert(Nuitka_Cell_GET(var_does_support_colors) == NULL);
        PyCell_SET(var_does_support_colors, tmp_assign_source_14);

    }
    {
        nuitka_bool tmp_condition_result_4;
        int tmp_truth_name_1;
        CHECK_OBJECT(Nuitka_Cell_GET(var_does_support_colors));
        tmp_truth_name_1 = CHECK_IF_TRUE(Nuitka_Cell_GET(var_does_support_colors));
        if (tmp_truth_name_1 == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 158;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_4 = tmp_truth_name_1 == 0 ? NUITKA_BOOL_FALSE : NUITKA_BOOL_TRUE;
        if (tmp_condition_result_4 == NUITKA_BOOL_TRUE) {
            goto branch_yes_1;
        } else {
            goto branch_no_1;
        }
    }
    branch_yes_1:;
    {
        PyObject *tmp_assign_source_15;
        tmp_assign_source_15 = mod_consts[18];
        assert(Nuitka_Cell_GET(var_red) == NULL);
        Py_INCREF(tmp_assign_source_15);
        PyCell_SET(var_red, tmp_assign_source_15);

    }
    {
        PyObject *tmp_assign_source_16;
        tmp_assign_source_16 = mod_consts[19];
        assert(Nuitka_Cell_GET(var_bold_red) == NULL);
        Py_INCREF(tmp_assign_source_16);
        PyCell_SET(var_bold_red, tmp_assign_source_16);

    }
    {
        PyObject *tmp_assign_source_17;
        tmp_assign_source_17 = mod_consts[20];
        assert(Nuitka_Cell_GET(var_reset) == NULL);
        Py_INCREF(tmp_assign_source_17);
        PyCell_SET(var_reset, tmp_assign_source_17);

    }
    {
        PyObject *tmp_assign_source_18;
        tmp_assign_source_18 = mod_consts[21];
        assert(Nuitka_Cell_GET(var_gray) == NULL);
        Py_INCREF(tmp_assign_source_18);
        PyCell_SET(var_gray, tmp_assign_source_18);

    }
    {
        PyObject *tmp_assign_source_19;
        tmp_assign_source_19 = mod_consts[22];
        assert(Nuitka_Cell_GET(var_yellow) == NULL);
        Py_INCREF(tmp_assign_source_19);
        PyCell_SET(var_yellow, tmp_assign_source_19);

    }
    {
        PyObject *tmp_assign_source_20;
        tmp_assign_source_20 = mod_consts[23];
        assert(var_green == NULL);
        Py_INCREF(tmp_assign_source_20);
        var_green = tmp_assign_source_20;
    }
    goto branch_end_1;
    branch_no_1:;
    {
        PyObject *tmp_assign_source_21;
        PyObject *tmp_iter_arg_2;
        tmp_iter_arg_2 = mod_consts[24];
        tmp_assign_source_21 = MAKE_ITERATOR_INFALLIBLE(tmp_iter_arg_2);
        assert(!(tmp_assign_source_21 == NULL));
        assert(tmp_tuple_unpack_1__source_iter == NULL);
        tmp_tuple_unpack_1__source_iter = tmp_assign_source_21;
    }
    // Tried code:
    // Tried code:
    {
        PyObject *tmp_assign_source_22;
        PyObject *tmp_unpack_1;
        CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
        tmp_unpack_1 = tmp_tuple_unpack_1__source_iter;
        tmp_assign_source_22 = UNPACK_NEXT(tstate, tmp_unpack_1, 0, 6);
        if (tmp_assign_source_22 == NULL) {
            if (!HAS_ERROR_OCCURRED(tstate)) {
                exception_type = PyExc_StopIteration;
                Py_INCREF(exception_type);
                exception_value = NULL;
                exception_tb = NULL;
            } else {
                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            }


            type_description_1 = "oocccooccooococccccocccocooccooo";
            exception_lineno = 166;
            goto try_except_handler_5;
        }
        assert(tmp_tuple_unpack_1__element_1 == NULL);
        tmp_tuple_unpack_1__element_1 = tmp_assign_source_22;
    }
    {
        PyObject *tmp_assign_source_23;
        PyObject *tmp_unpack_2;
        CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
        tmp_unpack_2 = tmp_tuple_unpack_1__source_iter;
        tmp_assign_source_23 = UNPACK_NEXT(tstate, tmp_unpack_2, 1, 6);
        if (tmp_assign_source_23 == NULL) {
            if (!HAS_ERROR_OCCURRED(tstate)) {
                exception_type = PyExc_StopIteration;
                Py_INCREF(exception_type);
                exception_value = NULL;
                exception_tb = NULL;
            } else {
                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            }


            type_description_1 = "oocccooccooococccccocccocooccooo";
            exception_lineno = 166;
            goto try_except_handler_5;
        }
        assert(tmp_tuple_unpack_1__element_2 == NULL);
        tmp_tuple_unpack_1__element_2 = tmp_assign_source_23;
    }
    {
        PyObject *tmp_assign_source_24;
        PyObject *tmp_unpack_3;
        CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
        tmp_unpack_3 = tmp_tuple_unpack_1__source_iter;
        tmp_assign_source_24 = UNPACK_NEXT(tstate, tmp_unpack_3, 2, 6);
        if (tmp_assign_source_24 == NULL) {
            if (!HAS_ERROR_OCCURRED(tstate)) {
                exception_type = PyExc_StopIteration;
                Py_INCREF(exception_type);
                exception_value = NULL;
                exception_tb = NULL;
            } else {
                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            }


            type_description_1 = "oocccooccooococccccocccocooccooo";
            exception_lineno = 166;
            goto try_except_handler_5;
        }
        assert(tmp_tuple_unpack_1__element_3 == NULL);
        tmp_tuple_unpack_1__element_3 = tmp_assign_source_24;
    }
    {
        PyObject *tmp_assign_source_25;
        PyObject *tmp_unpack_4;
        CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
        tmp_unpack_4 = tmp_tuple_unpack_1__source_iter;
        tmp_assign_source_25 = UNPACK_NEXT(tstate, tmp_unpack_4, 3, 6);
        if (tmp_assign_source_25 == NULL) {
            if (!HAS_ERROR_OCCURRED(tstate)) {
                exception_type = PyExc_StopIteration;
                Py_INCREF(exception_type);
                exception_value = NULL;
                exception_tb = NULL;
            } else {
                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            }


            type_description_1 = "oocccooccooococccccocccocooccooo";
            exception_lineno = 166;
            goto try_except_handler_5;
        }
        assert(tmp_tuple_unpack_1__element_4 == NULL);
        tmp_tuple_unpack_1__element_4 = tmp_assign_source_25;
    }
    {
        PyObject *tmp_assign_source_26;
        PyObject *tmp_unpack_5;
        CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
        tmp_unpack_5 = tmp_tuple_unpack_1__source_iter;
        tmp_assign_source_26 = UNPACK_NEXT(tstate, tmp_unpack_5, 4, 6);
        if (tmp_assign_source_26 == NULL) {
            if (!HAS_ERROR_OCCURRED(tstate)) {
                exception_type = PyExc_StopIteration;
                Py_INCREF(exception_type);
                exception_value = NULL;
                exception_tb = NULL;
            } else {
                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            }


            type_description_1 = "oocccooccooococccccocccocooccooo";
            exception_lineno = 166;
            goto try_except_handler_5;
        }
        assert(tmp_tuple_unpack_1__element_5 == NULL);
        tmp_tuple_unpack_1__element_5 = tmp_assign_source_26;
    }
    {
        PyObject *tmp_assign_source_27;
        PyObject *tmp_unpack_6;
        CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
        tmp_unpack_6 = tmp_tuple_unpack_1__source_iter;
        tmp_assign_source_27 = UNPACK_NEXT(tstate, tmp_unpack_6, 5, 6);
        if (tmp_assign_source_27 == NULL) {
            if (!HAS_ERROR_OCCURRED(tstate)) {
                exception_type = PyExc_StopIteration;
                Py_INCREF(exception_type);
                exception_value = NULL;
                exception_tb = NULL;
            } else {
                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            }


            type_description_1 = "oocccooccooococccccocccocooccooo";
            exception_lineno = 166;
            goto try_except_handler_5;
        }
        assert(tmp_tuple_unpack_1__element_6 == NULL);
        tmp_tuple_unpack_1__element_6 = tmp_assign_source_27;
    }
    {
        PyObject *tmp_iterator_name_1;
        CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
        tmp_iterator_name_1 = tmp_tuple_unpack_1__source_iter;
        // Check if iterator has left-over elements.
        CHECK_OBJECT(tmp_iterator_name_1); assert(HAS_ITERNEXT(tmp_iterator_name_1));

        tmp_iterator_attempt = (*Py_TYPE(tmp_iterator_name_1)->tp_iternext)(tmp_iterator_name_1);

        if (likely(tmp_iterator_attempt == NULL)) {
            PyObject *error = GET_ERROR_OCCURRED(tstate);

            if (error != NULL) {
                if (EXCEPTION_MATCH_BOOL_SINGLE(tstate, error, PyExc_StopIteration)) {
                    CLEAR_ERROR_OCCURRED(tstate);
                } else {
                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);

                    type_description_1 = "oocccooccooococccccocccocooccooo";
                    exception_lineno = 166;
                    goto try_except_handler_5;
                }
            }
        } else {
            Py_DECREF(tmp_iterator_attempt);

            exception_type = PyExc_ValueError;
            Py_INCREF(PyExc_ValueError);
            exception_value = mod_consts[25];
            Py_INCREF(exception_value);
            exception_tb = NULL;

            type_description_1 = "oocccooccooococccccocccocooccooo";
            exception_lineno = 166;
            goto try_except_handler_5;
        }
    }
    goto try_end_1;
    // Exception handler code:
    try_except_handler_5:;
    exception_keeper_type_3 = exception_type;
    exception_keeper_value_3 = exception_value;
    exception_keeper_tb_3 = exception_tb;
    exception_keeper_lineno_3 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
    Py_DECREF(tmp_tuple_unpack_1__source_iter);
    tmp_tuple_unpack_1__source_iter = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_3;
    exception_value = exception_keeper_value_3;
    exception_tb = exception_keeper_tb_3;
    exception_lineno = exception_keeper_lineno_3;

    goto try_except_handler_4;
    // End of try:
    try_end_1:;
    goto try_end_2;
    // Exception handler code:
    try_except_handler_4:;
    exception_keeper_type_4 = exception_type;
    exception_keeper_value_4 = exception_value;
    exception_keeper_tb_4 = exception_tb;
    exception_keeper_lineno_4 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(tmp_tuple_unpack_1__element_1);
    tmp_tuple_unpack_1__element_1 = NULL;
    Py_XDECREF(tmp_tuple_unpack_1__element_2);
    tmp_tuple_unpack_1__element_2 = NULL;
    Py_XDECREF(tmp_tuple_unpack_1__element_3);
    tmp_tuple_unpack_1__element_3 = NULL;
    Py_XDECREF(tmp_tuple_unpack_1__element_4);
    tmp_tuple_unpack_1__element_4 = NULL;
    Py_XDECREF(tmp_tuple_unpack_1__element_5);
    tmp_tuple_unpack_1__element_5 = NULL;
    Py_XDECREF(tmp_tuple_unpack_1__element_6);
    tmp_tuple_unpack_1__element_6 = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_4;
    exception_value = exception_keeper_value_4;
    exception_tb = exception_keeper_tb_4;
    exception_lineno = exception_keeper_lineno_4;

    goto frame_exception_exit_1;
    // End of try:
    try_end_2:;
    CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
    Py_DECREF(tmp_tuple_unpack_1__source_iter);
    tmp_tuple_unpack_1__source_iter = NULL;
    {
        PyObject *tmp_assign_source_28;
        CHECK_OBJECT(tmp_tuple_unpack_1__element_1);
        tmp_assign_source_28 = tmp_tuple_unpack_1__element_1;
        assert(Nuitka_Cell_GET(var_red) == NULL);
        Py_INCREF(tmp_assign_source_28);
        PyCell_SET(var_red, tmp_assign_source_28);

    }
    Py_XDECREF(tmp_tuple_unpack_1__element_1);
    tmp_tuple_unpack_1__element_1 = NULL;

    {
        PyObject *tmp_assign_source_29;
        CHECK_OBJECT(tmp_tuple_unpack_1__element_2);
        tmp_assign_source_29 = tmp_tuple_unpack_1__element_2;
        assert(Nuitka_Cell_GET(var_bold_red) == NULL);
        Py_INCREF(tmp_assign_source_29);
        PyCell_SET(var_bold_red, tmp_assign_source_29);

    }
    Py_XDECREF(tmp_tuple_unpack_1__element_2);
    tmp_tuple_unpack_1__element_2 = NULL;

    {
        PyObject *tmp_assign_source_30;
        CHECK_OBJECT(tmp_tuple_unpack_1__element_3);
        tmp_assign_source_30 = tmp_tuple_unpack_1__element_3;
        assert(Nuitka_Cell_GET(var_reset) == NULL);
        Py_INCREF(tmp_assign_source_30);
        PyCell_SET(var_reset, tmp_assign_source_30);

    }
    Py_XDECREF(tmp_tuple_unpack_1__element_3);
    tmp_tuple_unpack_1__element_3 = NULL;

    {
        PyObject *tmp_assign_source_31;
        CHECK_OBJECT(tmp_tuple_unpack_1__element_4);
        tmp_assign_source_31 = tmp_tuple_unpack_1__element_4;
        assert(Nuitka_Cell_GET(var_gray) == NULL);
        Py_INCREF(tmp_assign_source_31);
        PyCell_SET(var_gray, tmp_assign_source_31);

    }
    Py_XDECREF(tmp_tuple_unpack_1__element_4);
    tmp_tuple_unpack_1__element_4 = NULL;

    {
        PyObject *tmp_assign_source_32;
        CHECK_OBJECT(tmp_tuple_unpack_1__element_5);
        tmp_assign_source_32 = tmp_tuple_unpack_1__element_5;
        assert(Nuitka_Cell_GET(var_yellow) == NULL);
        Py_INCREF(tmp_assign_source_32);
        PyCell_SET(var_yellow, tmp_assign_source_32);

    }
    Py_XDECREF(tmp_tuple_unpack_1__element_5);
    tmp_tuple_unpack_1__element_5 = NULL;

    {
        PyObject *tmp_assign_source_33;
        CHECK_OBJECT(tmp_tuple_unpack_1__element_6);
        tmp_assign_source_33 = tmp_tuple_unpack_1__element_6;
        assert(var_green == NULL);
        Py_INCREF(tmp_assign_source_33);
        var_green = tmp_assign_source_33;
    }
    Py_XDECREF(tmp_tuple_unpack_1__element_6);
    tmp_tuple_unpack_1__element_6 = NULL;

    branch_end_1:;
    {
        PyObject *tmp_assign_source_34;
        PyObject *tmp_annotations_1;
        struct Nuitka_CellObject *tmp_closure_1[1];
        tmp_annotations_1 = DICT_COPY(mod_consts[26]);

        tmp_closure_1[0] = var_s_u;
        Py_INCREF(tmp_closure_1[0]);

        tmp_assign_source_34 = MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__1_calculate_skip_ammout(tmp_annotations_1, tmp_closure_1);

        assert(Nuitka_Cell_GET(var_calculate_skip_ammout) == NULL);
        PyCell_SET(var_calculate_skip_ammout, tmp_assign_source_34);

    }
    {
        PyObject *tmp_assign_source_35;
        PyObject *tmp_annotations_2;
        struct Nuitka_CellObject *tmp_closure_2[3];
        tmp_annotations_2 = DICT_COPY(mod_consts[26]);

        tmp_closure_2[0] = var_calculate_skip_ammout;
        Py_INCREF(tmp_closure_2[0]);
        tmp_closure_2[1] = var_does_support_colors;
        Py_INCREF(tmp_closure_2[1]);
        tmp_closure_2[2] = var_s_u;
        Py_INCREF(tmp_closure_2[2]);

        tmp_assign_source_35 = MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__2_count_spaces(tmp_annotations_2, tmp_closure_2);

        assert(Nuitka_Cell_GET(var_count_spaces) == NULL);
        PyCell_SET(var_count_spaces, tmp_assign_source_35);

    }
    {
        PyObject *tmp_assign_source_36;
        PyObject *tmp_annotations_3;
        struct Nuitka_CellObject *tmp_closure_3[2];
        tmp_annotations_3 = DICT_COPY(mod_consts[31]);

        tmp_closure_3[0] = var_calculate_skip_ammout;
        Py_INCREF(tmp_closure_3[0]);
        tmp_closure_3[1] = var_count_spaces;
        Py_INCREF(tmp_closure_3[1]);

        tmp_assign_source_36 = MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__3_line_without_spaces(tmp_annotations_3, tmp_closure_3);

        assert(Nuitka_Cell_GET(var_line_without_spaces) == NULL);
        PyCell_SET(var_line_without_spaces, tmp_assign_source_36);

    }
    {
        PyObject *tmp_assign_source_37;
        PyObject *tmp_annotations_4;
        struct Nuitka_CellObject *tmp_closure_4[11];
        tmp_annotations_4 = DICT_COPY(mod_consts[34]);

        tmp_closure_4[0] = var_bold_red;
        Py_INCREF(tmp_closure_4[0]);
        tmp_closure_4[1] = var_calculate_skip_ammout;
        Py_INCREF(tmp_closure_4[1]);
        tmp_closure_4[2] = var_chars;
        Py_INCREF(tmp_closure_4[2]);
        tmp_closure_4[3] = var_count_spaces;
        Py_INCREF(tmp_closure_4[3]);
        tmp_closure_4[4] = var_does_support_colors;
        Py_INCREF(tmp_closure_4[4]);
        tmp_closure_4[5] = var_line_without_spaces;
        Py_INCREF(tmp_closure_4[5]);
        tmp_closure_4[6] = var_lines;
        Py_INCREF(tmp_closure_4[6]);
        tmp_closure_4[7] = par_mark;
        Py_INCREF(tmp_closure_4[7]);
        tmp_closure_4[8] = var_red;
        Py_INCREF(tmp_closure_4[8]);
        tmp_closure_4[9] = var_reset;
        Py_INCREF(tmp_closure_4[9]);
        tmp_closure_4[10] = var_s_u;
        Py_INCREF(tmp_closure_4[10]);

        tmp_assign_source_37 = MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__4_mark_all(tmp_annotations_4, tmp_closure_4);

        assert(var_mark_all == NULL);
        var_mark_all = tmp_assign_source_37;
    }
    {
        PyObject *tmp_assign_source_38;
        PyObject *tmp_annotations_5;
        tmp_annotations_5 = DICT_COPY(mod_consts[37]);


        tmp_assign_source_38 = MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__5_s_u(tmp_annotations_5);

        assert(Nuitka_Cell_GET(var_s_u) == NULL);
        PyCell_SET(var_s_u, tmp_assign_source_38);

    }
    {
        PyObject *tmp_assign_source_39;
        PyObject *tmp_annotations_6;
        struct Nuitka_CellObject *tmp_closure_5[9];
        tmp_annotations_6 = DICT_COPY(mod_consts[40]);

        tmp_closure_5[0] = var_bold_red;
        Py_INCREF(tmp_closure_5[0]);
        tmp_closure_5[1] = var_chars;
        Py_INCREF(tmp_closure_5[1]);
        tmp_closure_5[2] = var_does_support_colors;
        Py_INCREF(tmp_closure_5[2]);
        tmp_closure_5[3] = var_gray;
        Py_INCREF(tmp_closure_5[3]);
        tmp_closure_5[4] = par_line_no;
        Py_INCREF(tmp_closure_5[4]);
        tmp_closure_5[5] = var_lines_to_print;
        Py_INCREF(tmp_closure_5[5]);
        tmp_closure_5[6] = var_red;
        Py_INCREF(tmp_closure_5[6]);
        tmp_closure_5[7] = var_reset;
        Py_INCREF(tmp_closure_5[7]);
        tmp_closure_5[8] = var_s_u;
        Py_INCREF(tmp_closure_5[8]);

        tmp_assign_source_39 = MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__6_process_lines(tmp_annotations_6, tmp_closure_5);

        assert(var_process_lines == NULL);
        var_process_lines = tmp_assign_source_39;
    }
    {
        PyObject *tmp_assign_source_40;
        PyObject *tmp_string_concat_values_1;
        PyObject *tmp_tuple_element_1;
        PyObject *tmp_format_value_1;
        PyObject *tmp_format_spec_1;
        if (Nuitka_Cell_GET(var_red) == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 274;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }

        tmp_format_value_1 = Nuitka_Cell_GET(var_red);
        tmp_format_spec_1 = mod_consts[44];
        tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_1, tmp_format_spec_1);
        if (tmp_tuple_element_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 274;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_string_concat_values_1 = MAKE_TUPLE_EMPTY(14);
        {
            PyObject *tmp_format_value_2;
            PyObject *tmp_dict_arg_value_1;
            PyObject *tmp_key_value_1;
            PyObject *tmp_format_spec_2;
            PyObject *tmp_format_value_3;
            PyObject *tmp_dict_arg_value_2;
            PyObject *tmp_key_value_2;
            PyObject *tmp_format_spec_3;
            PyObject *tmp_format_value_4;
            PyObject *tmp_format_spec_4;
            PyObject *tmp_format_value_5;
            PyObject *tmp_format_spec_5;
            PyObject *tmp_format_value_6;
            PyObject *tmp_format_spec_6;
            PyObject *tmp_format_value_7;
            PyObject *tmp_format_spec_7;
            PyObject *tmp_format_value_8;
            PyObject *tmp_mult_expr_left_1;
            PyObject *tmp_mult_expr_right_1;
            PyObject *tmp_dict_arg_value_3;
            PyObject *tmp_key_value_3;
            PyObject *tmp_sub_expr_left_3;
            PyObject *tmp_sub_expr_right_3;
            PyObject *tmp_sub_expr_left_4;
            PyObject *tmp_sub_expr_right_4;
            PyObject *tmp_sub_expr_left_5;
            PyObject *tmp_sub_expr_right_5;
            PyObject *tmp_len_arg_1;
            PyObject *tmp_format_spec_8;
            PyObject *tmp_format_value_9;
            PyObject *tmp_format_spec_9;
            PyObject *tmp_format_value_10;
            PyObject *tmp_format_spec_10;
            PyObject *tmp_format_value_11;
            PyObject *tmp_dict_arg_value_4;
            PyObject *tmp_key_value_4;
            PyObject *tmp_format_spec_11;
            PyObject *tmp_format_value_12;
            PyObject *tmp_format_spec_12;
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 0, tmp_tuple_element_1);
            CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
            tmp_dict_arg_value_1 = Nuitka_Cell_GET(var_chars);
            tmp_key_value_1 = mod_consts[45];
            tmp_format_value_2 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_1, tmp_key_value_1);
            if (tmp_format_value_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            tmp_format_spec_2 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_2, tmp_format_spec_2);
            Py_DECREF(tmp_format_value_2);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 1, tmp_tuple_element_1);
            CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
            tmp_dict_arg_value_2 = Nuitka_Cell_GET(var_chars);
            tmp_key_value_2 = mod_consts[46];
            tmp_format_value_3 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_2, tmp_key_value_2);
            if (tmp_format_value_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            tmp_format_spec_3 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_3, tmp_format_spec_3);
            Py_DECREF(tmp_format_value_3);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 2, tmp_tuple_element_1);
            if (Nuitka_Cell_GET(var_reset) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }

            tmp_format_value_4 = Nuitka_Cell_GET(var_reset);
            tmp_format_spec_4 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_4, tmp_format_spec_4);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 3, tmp_tuple_element_1);
            tmp_tuple_element_1 = mod_consts[48];
            PyTuple_SET_ITEM0(tmp_string_concat_values_1, 4, tmp_tuple_element_1);
            if (Nuitka_Cell_GET(var_bold_red) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[49]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }

            tmp_format_value_5 = Nuitka_Cell_GET(var_bold_red);
            tmp_format_spec_5 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_5, tmp_format_spec_5);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 5, tmp_tuple_element_1);
            CHECK_OBJECT(var_name);
            tmp_format_value_6 = var_name;
            tmp_format_spec_6 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_6, tmp_format_spec_6);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 6, tmp_tuple_element_1);
            tmp_tuple_element_1 = mod_consts[48];
            PyTuple_SET_ITEM0(tmp_string_concat_values_1, 7, tmp_tuple_element_1);
            if (Nuitka_Cell_GET(var_red) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[43]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }

            tmp_format_value_7 = Nuitka_Cell_GET(var_red);
            tmp_format_spec_7 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_7, tmp_format_spec_7);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 8, tmp_tuple_element_1);
            CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
            tmp_dict_arg_value_3 = Nuitka_Cell_GET(var_chars);
            tmp_key_value_3 = mod_consts[46];
            tmp_mult_expr_left_1 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_3, tmp_key_value_3);
            if (tmp_mult_expr_left_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            tmp_sub_expr_left_5 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

            if (unlikely(tmp_sub_expr_left_5 == NULL)) {
                tmp_sub_expr_left_5 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
            }

            if (tmp_sub_expr_left_5 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_mult_expr_left_1);

                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            tmp_sub_expr_right_5 = mod_consts[51];
            tmp_sub_expr_left_4 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_5, tmp_sub_expr_right_5);
            if (tmp_sub_expr_left_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_mult_expr_left_1);

                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            CHECK_OBJECT(var_name);
            tmp_len_arg_1 = var_name;
            tmp_sub_expr_right_4 = BUILTIN_LEN(tstate, tmp_len_arg_1);
            if (tmp_sub_expr_right_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_mult_expr_left_1);
                Py_DECREF(tmp_sub_expr_left_4);

                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            tmp_sub_expr_left_3 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_4, tmp_sub_expr_right_4);
            Py_DECREF(tmp_sub_expr_left_4);
            Py_DECREF(tmp_sub_expr_right_4);
            if (tmp_sub_expr_left_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_mult_expr_left_1);

                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            tmp_sub_expr_right_3 = mod_consts[52];
            tmp_mult_expr_right_1 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_3, tmp_sub_expr_right_3);
            Py_DECREF(tmp_sub_expr_left_3);
            if (tmp_mult_expr_right_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_mult_expr_left_1);

                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            tmp_format_value_8 = BINARY_OPERATION_MULT_OBJECT_OBJECT_OBJECT(tmp_mult_expr_left_1, tmp_mult_expr_right_1);
            Py_DECREF(tmp_mult_expr_left_1);
            Py_DECREF(tmp_mult_expr_right_1);
            if (tmp_format_value_8 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            tmp_format_spec_8 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_8, tmp_format_spec_8);
            Py_DECREF(tmp_format_value_8);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 9, tmp_tuple_element_1);
            if (Nuitka_Cell_GET(var_reset) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }

            tmp_format_value_9 = Nuitka_Cell_GET(var_reset);
            tmp_format_spec_9 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_9, tmp_format_spec_9);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 10, tmp_tuple_element_1);
            if (Nuitka_Cell_GET(var_red) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[43]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }

            tmp_format_value_10 = Nuitka_Cell_GET(var_red);
            tmp_format_spec_10 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_10, tmp_format_spec_10);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 11, tmp_tuple_element_1);
            CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
            tmp_dict_arg_value_4 = Nuitka_Cell_GET(var_chars);
            tmp_key_value_4 = mod_consts[53];
            tmp_format_value_11 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_4, tmp_key_value_4);
            if (tmp_format_value_11 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            tmp_format_spec_11 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_11, tmp_format_spec_11);
            Py_DECREF(tmp_format_value_11);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 12, tmp_tuple_element_1);
            if (Nuitka_Cell_GET(var_reset) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }

            tmp_format_value_12 = Nuitka_Cell_GET(var_reset);
            tmp_format_spec_12 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_12, tmp_format_spec_12);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 274;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 13, tmp_tuple_element_1);
        }
        goto tuple_build_noexception_1;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_1:;
        Py_DECREF(tmp_string_concat_values_1);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_1:;
        tmp_assign_source_40 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_1);
        Py_DECREF(tmp_string_concat_values_1);
        if (tmp_assign_source_40 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 274;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        assert(var_top_section == NULL);
        var_top_section = tmp_assign_source_40;
    }
    {
        PyObject *tmp_called_value_1;
        PyObject *tmp_call_result_2;
        PyObject *tmp_args_element_value_1;
        tmp_called_value_1 = LOOKUP_BUILTIN(mod_consts[54]);
        assert(tmp_called_value_1 != NULL);
        CHECK_OBJECT(var_top_section);
        tmp_args_element_value_1 = var_top_section;
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 276;
        tmp_call_result_2 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_1, tmp_args_element_value_1);
        if (tmp_call_result_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 276;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        Py_DECREF(tmp_call_result_2);
    }
    {
        PyObject *tmp_assign_source_41;
        // Tried code:
        {
            PyObject *tmp_assign_source_42;
            PyObject *tmp_iter_arg_3;
            PyObject *tmp_called_value_2;
            PyObject *tmp_args_element_value_2;
            tmp_called_value_2 = (PyObject *)&PyEnum_Type;
            CHECK_OBJECT(Nuitka_Cell_GET(var_lines));
            tmp_args_element_value_2 = Nuitka_Cell_GET(var_lines);
            frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 278;
            tmp_iter_arg_3 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_2, tmp_args_element_value_2);
            if (tmp_iter_arg_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 278;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto try_except_handler_6;
            }
            tmp_assign_source_42 = MAKE_ITERATOR(tstate, tmp_iter_arg_3);
            Py_DECREF(tmp_iter_arg_3);
            if (tmp_assign_source_42 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 278;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto try_except_handler_6;
            }
            assert(tmp_listcomp_2__$0 == NULL);
            tmp_listcomp_2__$0 = tmp_assign_source_42;
        }
        {
            PyObject *tmp_assign_source_43;
            tmp_assign_source_43 = MAKE_LIST_EMPTY(0);
            assert(tmp_listcomp_2__contraction == NULL);
            tmp_listcomp_2__contraction = tmp_assign_source_43;
        }
        // Tried code:
        loop_start_2:;
        {
            PyObject *tmp_next_source_2;
            PyObject *tmp_assign_source_44;
            CHECK_OBJECT(tmp_listcomp_2__$0);
            tmp_next_source_2 = tmp_listcomp_2__$0;
            tmp_assign_source_44 = ITERATOR_NEXT(tmp_next_source_2);
            if (tmp_assign_source_44 == NULL) {
                if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                    goto loop_end_2;
                } else {

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                    type_description_1 = "oocccooccooococccccocccocooccooo";
                    exception_lineno = 278;
                    goto try_except_handler_7;
                }
            }

            {
                PyObject *old = tmp_listcomp_2__iter_value_0;
                tmp_listcomp_2__iter_value_0 = tmp_assign_source_44;
                Py_XDECREF(old);
            }

        }
        // Tried code:
        {
            PyObject *tmp_assign_source_45;
            PyObject *tmp_iter_arg_4;
            CHECK_OBJECT(tmp_listcomp_2__iter_value_0);
            tmp_iter_arg_4 = tmp_listcomp_2__iter_value_0;
            tmp_assign_source_45 = MAKE_UNPACK_ITERATOR(tmp_iter_arg_4);
            if (tmp_assign_source_45 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 278;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto try_except_handler_8;
            }
            {
                PyObject *old = tmp_listcomp$tuple_unpack_1__source_iter;
                tmp_listcomp$tuple_unpack_1__source_iter = tmp_assign_source_45;
                Py_XDECREF(old);
            }

        }
        // Tried code:
        {
            PyObject *tmp_assign_source_46;
            PyObject *tmp_unpack_7;
            CHECK_OBJECT(tmp_listcomp$tuple_unpack_1__source_iter);
            tmp_unpack_7 = tmp_listcomp$tuple_unpack_1__source_iter;
            tmp_assign_source_46 = UNPACK_NEXT(tstate, tmp_unpack_7, 0, 2);
            if (tmp_assign_source_46 == NULL) {
                if (!HAS_ERROR_OCCURRED(tstate)) {
                    exception_type = PyExc_StopIteration;
                    Py_INCREF(exception_type);
                    exception_value = NULL;
                    exception_tb = NULL;
                } else {
                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                }


                type_description_1 = "oocccooccooococccccocccocooccooo";
                exception_lineno = 278;
                goto try_except_handler_9;
            }
            {
                PyObject *old = tmp_listcomp$tuple_unpack_1__element_1;
                tmp_listcomp$tuple_unpack_1__element_1 = tmp_assign_source_46;
                Py_XDECREF(old);
            }

        }
        {
            PyObject *tmp_assign_source_47;
            PyObject *tmp_unpack_8;
            CHECK_OBJECT(tmp_listcomp$tuple_unpack_1__source_iter);
            tmp_unpack_8 = tmp_listcomp$tuple_unpack_1__source_iter;
            tmp_assign_source_47 = UNPACK_NEXT(tstate, tmp_unpack_8, 1, 2);
            if (tmp_assign_source_47 == NULL) {
                if (!HAS_ERROR_OCCURRED(tstate)) {
                    exception_type = PyExc_StopIteration;
                    Py_INCREF(exception_type);
                    exception_value = NULL;
                    exception_tb = NULL;
                } else {
                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                }


                type_description_1 = "oocccooccooococccccocccocooccooo";
                exception_lineno = 278;
                goto try_except_handler_9;
            }
            {
                PyObject *old = tmp_listcomp$tuple_unpack_1__element_2;
                tmp_listcomp$tuple_unpack_1__element_2 = tmp_assign_source_47;
                Py_XDECREF(old);
            }

        }
        {
            PyObject *tmp_iterator_name_2;
            CHECK_OBJECT(tmp_listcomp$tuple_unpack_1__source_iter);
            tmp_iterator_name_2 = tmp_listcomp$tuple_unpack_1__source_iter;
            // Check if iterator has left-over elements.
            CHECK_OBJECT(tmp_iterator_name_2); assert(HAS_ITERNEXT(tmp_iterator_name_2));

            tmp_iterator_attempt = (*Py_TYPE(tmp_iterator_name_2)->tp_iternext)(tmp_iterator_name_2);

            if (likely(tmp_iterator_attempt == NULL)) {
                PyObject *error = GET_ERROR_OCCURRED(tstate);

                if (error != NULL) {
                    if (EXCEPTION_MATCH_BOOL_SINGLE(tstate, error, PyExc_StopIteration)) {
                        CLEAR_ERROR_OCCURRED(tstate);
                    } else {
                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);

                        type_description_1 = "oocccooccooococccccocccocooccooo";
                        exception_lineno = 278;
                        goto try_except_handler_9;
                    }
                }
            } else {
                Py_DECREF(tmp_iterator_attempt);

                exception_type = PyExc_ValueError;
                Py_INCREF(PyExc_ValueError);
                exception_value = mod_consts[55];
                Py_INCREF(exception_value);
                exception_tb = NULL;

                type_description_1 = "oocccooccooococccccocccocooccooo";
                exception_lineno = 278;
                goto try_except_handler_9;
            }
        }
        goto try_end_3;
        // Exception handler code:
        try_except_handler_9:;
        exception_keeper_type_5 = exception_type;
        exception_keeper_value_5 = exception_value;
        exception_keeper_tb_5 = exception_tb;
        exception_keeper_lineno_5 = exception_lineno;
        exception_type = NULL;
        exception_value = NULL;
        exception_tb = NULL;
        exception_lineno = 0;

        CHECK_OBJECT(tmp_listcomp$tuple_unpack_1__source_iter);
        Py_DECREF(tmp_listcomp$tuple_unpack_1__source_iter);
        tmp_listcomp$tuple_unpack_1__source_iter = NULL;
        // Re-raise.
        exception_type = exception_keeper_type_5;
        exception_value = exception_keeper_value_5;
        exception_tb = exception_keeper_tb_5;
        exception_lineno = exception_keeper_lineno_5;

        goto try_except_handler_8;
        // End of try:
        try_end_3:;
        goto try_end_4;
        // Exception handler code:
        try_except_handler_8:;
        exception_keeper_type_6 = exception_type;
        exception_keeper_value_6 = exception_value;
        exception_keeper_tb_6 = exception_tb;
        exception_keeper_lineno_6 = exception_lineno;
        exception_type = NULL;
        exception_value = NULL;
        exception_tb = NULL;
        exception_lineno = 0;

        Py_XDECREF(tmp_listcomp$tuple_unpack_1__element_1);
        tmp_listcomp$tuple_unpack_1__element_1 = NULL;
        Py_XDECREF(tmp_listcomp$tuple_unpack_1__element_2);
        tmp_listcomp$tuple_unpack_1__element_2 = NULL;
        // Re-raise.
        exception_type = exception_keeper_type_6;
        exception_value = exception_keeper_value_6;
        exception_tb = exception_keeper_tb_6;
        exception_lineno = exception_keeper_lineno_6;

        goto try_except_handler_7;
        // End of try:
        try_end_4:;
        CHECK_OBJECT(tmp_listcomp$tuple_unpack_1__source_iter);
        Py_DECREF(tmp_listcomp$tuple_unpack_1__source_iter);
        tmp_listcomp$tuple_unpack_1__source_iter = NULL;
        {
            PyObject *tmp_assign_source_48;
            CHECK_OBJECT(tmp_listcomp$tuple_unpack_1__element_1);
            tmp_assign_source_48 = tmp_listcomp$tuple_unpack_1__element_1;
            {
                PyObject *old = outline_1_var_index;
                outline_1_var_index = tmp_assign_source_48;
                Py_INCREF(outline_1_var_index);
                Py_XDECREF(old);
            }

        }
        Py_XDECREF(tmp_listcomp$tuple_unpack_1__element_1);
        tmp_listcomp$tuple_unpack_1__element_1 = NULL;

        {
            PyObject *tmp_assign_source_49;
            CHECK_OBJECT(tmp_listcomp$tuple_unpack_1__element_2);
            tmp_assign_source_49 = tmp_listcomp$tuple_unpack_1__element_2;
            {
                PyObject *old = outline_1_var_line;
                outline_1_var_line = tmp_assign_source_49;
                Py_INCREF(outline_1_var_line);
                Py_XDECREF(old);
            }

        }
        Py_XDECREF(tmp_listcomp$tuple_unpack_1__element_2);
        tmp_listcomp$tuple_unpack_1__element_2 = NULL;

        {
            PyObject *tmp_append_list_2;
            PyObject *tmp_append_value_2;
            PyObject *tmp_called_value_3;
            PyObject *tmp_args_element_value_3;
            PyObject *tmp_args_element_value_4;
            CHECK_OBJECT(tmp_listcomp_2__contraction);
            tmp_append_list_2 = tmp_listcomp_2__contraction;
            if (var_process_lines == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[41]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 278;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto try_except_handler_7;
            }

            tmp_called_value_3 = var_process_lines;
            CHECK_OBJECT(outline_1_var_line);
            tmp_args_element_value_3 = outline_1_var_line;
            CHECK_OBJECT(outline_1_var_index);
            tmp_args_element_value_4 = outline_1_var_index;
            frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 278;
            {
                PyObject *call_args[] = {tmp_args_element_value_3, tmp_args_element_value_4};
                tmp_append_value_2 = CALL_FUNCTION_WITH_ARGS2(tstate, tmp_called_value_3, call_args);
            }

            if (tmp_append_value_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 278;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto try_except_handler_7;
            }
            tmp_result = LIST_APPEND1(tmp_append_list_2, tmp_append_value_2);
            if (tmp_result == false) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 278;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto try_except_handler_7;
            }
        }
        if (CONSIDER_THREADING(tstate) == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 278;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto try_except_handler_7;
        }
        goto loop_start_2;
        loop_end_2:;
        CHECK_OBJECT(tmp_listcomp_2__contraction);
        tmp_assign_source_41 = tmp_listcomp_2__contraction;
        Py_INCREF(tmp_assign_source_41);
        goto try_return_handler_7;
        NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
        return NULL;
        // Return handler code:
        try_return_handler_7:;
        CHECK_OBJECT(tmp_listcomp_2__$0);
        Py_DECREF(tmp_listcomp_2__$0);
        tmp_listcomp_2__$0 = NULL;
        CHECK_OBJECT(tmp_listcomp_2__contraction);
        Py_DECREF(tmp_listcomp_2__contraction);
        tmp_listcomp_2__contraction = NULL;
        Py_XDECREF(tmp_listcomp_2__iter_value_0);
        tmp_listcomp_2__iter_value_0 = NULL;
        goto try_return_handler_6;
        // Exception handler code:
        try_except_handler_7:;
        exception_keeper_type_7 = exception_type;
        exception_keeper_value_7 = exception_value;
        exception_keeper_tb_7 = exception_tb;
        exception_keeper_lineno_7 = exception_lineno;
        exception_type = NULL;
        exception_value = NULL;
        exception_tb = NULL;
        exception_lineno = 0;

        CHECK_OBJECT(tmp_listcomp_2__$0);
        Py_DECREF(tmp_listcomp_2__$0);
        tmp_listcomp_2__$0 = NULL;
        CHECK_OBJECT(tmp_listcomp_2__contraction);
        Py_DECREF(tmp_listcomp_2__contraction);
        tmp_listcomp_2__contraction = NULL;
        Py_XDECREF(tmp_listcomp_2__iter_value_0);
        tmp_listcomp_2__iter_value_0 = NULL;
        // Re-raise.
        exception_type = exception_keeper_type_7;
        exception_value = exception_keeper_value_7;
        exception_tb = exception_keeper_tb_7;
        exception_lineno = exception_keeper_lineno_7;

        goto try_except_handler_6;
        // End of try:
        NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
        return NULL;
        // Return handler code:
        try_return_handler_6:;
        Py_XDECREF(outline_1_var_index);
        outline_1_var_index = NULL;
        Py_XDECREF(outline_1_var_line);
        outline_1_var_line = NULL;
        goto outline_result_2;
        // Exception handler code:
        try_except_handler_6:;
        exception_keeper_type_8 = exception_type;
        exception_keeper_value_8 = exception_value;
        exception_keeper_tb_8 = exception_tb;
        exception_keeper_lineno_8 = exception_lineno;
        exception_type = NULL;
        exception_value = NULL;
        exception_tb = NULL;
        exception_lineno = 0;

        Py_XDECREF(outline_1_var_index);
        outline_1_var_index = NULL;
        Py_XDECREF(outline_1_var_line);
        outline_1_var_line = NULL;
        // Re-raise.
        exception_type = exception_keeper_type_8;
        exception_value = exception_keeper_value_8;
        exception_tb = exception_keeper_tb_8;
        exception_lineno = exception_keeper_lineno_8;

        goto outline_exception_2;
        // End of try:
        NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
        return NULL;
        outline_exception_2:;
        exception_lineno = 278;
        goto frame_exception_exit_1;
        outline_result_2:;
        assert(var_mid_section == NULL);
        var_mid_section = tmp_assign_source_41;
    }
    {
        nuitka_bool tmp_condition_result_5;
        PyObject *tmp_cmp_expr_left_2;
        PyObject *tmp_cmp_expr_right_2;
        CHECK_OBJECT(Nuitka_Cell_GET(par_line_no));
        tmp_cmp_expr_left_2 = Nuitka_Cell_GET(par_line_no);
        tmp_cmp_expr_right_2 = mod_consts[56];
        tmp_condition_result_5 = RICH_COMPARE_NE_NBOOL_OBJECT_LONG(tmp_cmp_expr_left_2, tmp_cmp_expr_right_2);
        if (tmp_condition_result_5 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 280;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        if (tmp_condition_result_5 == NUITKA_BOOL_TRUE) {
            goto branch_yes_2;
        } else {
            goto branch_no_2;
        }
    }
    branch_yes_2:;
    {
        PyObject *tmp_called_value_4;
        PyObject *tmp_call_result_3;
        PyObject *tmp_args_element_value_5;
        PyObject *tmp_str_arg_value_1;
        PyObject *tmp_iterable_value_1;
        PyObject *tmp_expression_value_10;
        PyObject *tmp_subscript_value_2;
        tmp_called_value_4 = LOOKUP_BUILTIN(mod_consts[54]);
        assert(tmp_called_value_4 != NULL);
        tmp_str_arg_value_1 = mod_consts[57];
        CHECK_OBJECT(var_mid_section);
        tmp_expression_value_10 = var_mid_section;
        tmp_subscript_value_2 = mod_consts[58];
        tmp_iterable_value_1 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_10, tmp_subscript_value_2);
        if (tmp_iterable_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 280;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_args_element_value_5 = UNICODE_JOIN(tstate, tmp_str_arg_value_1, tmp_iterable_value_1);
        Py_DECREF(tmp_iterable_value_1);
        if (tmp_args_element_value_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 280;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 280;
        tmp_call_result_3 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_4, tmp_args_element_value_5);
        Py_DECREF(tmp_args_element_value_5);
        if (tmp_call_result_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 280;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        Py_DECREF(tmp_call_result_3);
    }
    branch_no_2:;
    {
        PyObject *tmp_called_value_5;
        PyObject *tmp_call_result_4;
        PyObject *tmp_args_element_value_6;
        PyObject *tmp_called_value_6;
        PyObject *tmp_args_element_value_7;
        PyObject *tmp_expression_value_11;
        PyObject *tmp_subscript_value_3;
        PyObject *tmp_args_element_value_8;
        PyObject *tmp_string_concat_values_2;
        PyObject *tmp_tuple_element_2;
        PyObject *tmp_format_value_13;
        PyObject *tmp_format_spec_13;
        tmp_called_value_5 = LOOKUP_BUILTIN(mod_consts[54]);
        assert(tmp_called_value_5 != NULL);
        CHECK_OBJECT(var_mark_all);
        tmp_called_value_6 = var_mark_all;
        CHECK_OBJECT(var_mid_section);
        tmp_expression_value_11 = var_mid_section;
        tmp_subscript_value_3 = mod_consts[59];
        tmp_args_element_value_7 = LOOKUP_SUBSCRIPT_CONST(tstate, tmp_expression_value_11, tmp_subscript_value_3, -1);
        if (tmp_args_element_value_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 281;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        if (Nuitka_Cell_GET(var_red) == NULL) {
            Py_DECREF(tmp_args_element_value_7);
            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 281;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }

        tmp_format_value_13 = Nuitka_Cell_GET(var_red);
        tmp_format_spec_13 = mod_consts[44];
        tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_13, tmp_format_spec_13);
        if (tmp_tuple_element_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_args_element_value_7);

            exception_lineno = 281;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_string_concat_values_2 = MAKE_TUPLE_EMPTY(5);
        {
            PyObject *tmp_format_value_14;
            PyObject *tmp_format_spec_14;
            PyObject *tmp_mult_expr_left_2;
            PyObject *tmp_mult_expr_right_2;
            PyObject *tmp_len_arg_2;
            PyObject *tmp_called_value_7;
            PyObject *tmp_expression_value_12;
            PyObject *tmp_unicode_arg_3;
            PyObject *tmp_args_element_value_9;
            PyObject *tmp_len_arg_3;
            PyObject *tmp_unicode_arg_4;
            PyObject *tmp_add_expr_left_1;
            PyObject *tmp_add_expr_right_1;
            PyObject *tmp_sub_expr_left_6;
            nuitka_digit tmp_sub_expr_right_6;
            PyObject *tmp_format_value_15;
            PyObject *tmp_format_spec_15;
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 0, tmp_tuple_element_2);
            tmp_tuple_element_2 = mod_consts[60];
            PyTuple_SET_ITEM0(tmp_string_concat_values_2, 1, tmp_tuple_element_2);
            if (Nuitka_Cell_GET(var_gray) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[61]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 281;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_2;
            }

            tmp_format_value_14 = Nuitka_Cell_GET(var_gray);
            tmp_format_spec_14 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_14, tmp_format_spec_14);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 281;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 2, tmp_tuple_element_2);
            tmp_mult_expr_left_2 = mod_consts[62];
            CHECK_OBJECT(Nuitka_Cell_GET(par_line_no));
            tmp_unicode_arg_3 = Nuitka_Cell_GET(par_line_no);
            tmp_expression_value_12 = BUILTIN_UNICODE1(tmp_unicode_arg_3);
            if (tmp_expression_value_12 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 281;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_2;
            }
            tmp_called_value_7 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_12, mod_consts[63]);
            Py_DECREF(tmp_expression_value_12);
            if (tmp_called_value_7 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 281;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_2;
            }
            CHECK_OBJECT(Nuitka_Cell_GET(par_line_no));
            tmp_add_expr_left_1 = Nuitka_Cell_GET(par_line_no);
            CHECK_OBJECT(Nuitka_Cell_GET(var_lines_to_print));
            tmp_sub_expr_left_6 = Nuitka_Cell_GET(var_lines_to_print);
            tmp_sub_expr_right_6 = 1;
            tmp_add_expr_right_1 = BINARY_OPERATION_SUB_OBJECT_LONG_DIGIT(tmp_sub_expr_left_6, tmp_sub_expr_right_6);
            assert(!(tmp_add_expr_right_1 == NULL));
            tmp_unicode_arg_4 = BINARY_OPERATION_ADD_OBJECT_OBJECT_LONG(tmp_add_expr_left_1, tmp_add_expr_right_1);
            Py_DECREF(tmp_add_expr_right_1);
            if (tmp_unicode_arg_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_called_value_7);

                exception_lineno = 281;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_2;
            }
            tmp_len_arg_3 = BUILTIN_UNICODE1(tmp_unicode_arg_4);
            Py_DECREF(tmp_unicode_arg_4);
            if (tmp_len_arg_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_called_value_7);

                exception_lineno = 281;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_2;
            }
            tmp_args_element_value_9 = BUILTIN_LEN(tstate, tmp_len_arg_3);
            Py_DECREF(tmp_len_arg_3);
            if (tmp_args_element_value_9 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_called_value_7);

                exception_lineno = 281;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_2;
            }
            frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 281;
            tmp_len_arg_2 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_7, tmp_args_element_value_9);
            Py_DECREF(tmp_called_value_7);
            Py_DECREF(tmp_args_element_value_9);
            if (tmp_len_arg_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 281;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_2;
            }
            tmp_mult_expr_right_2 = BUILTIN_LEN(tstate, tmp_len_arg_2);
            Py_DECREF(tmp_len_arg_2);
            if (tmp_mult_expr_right_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 281;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_2;
            }
            tmp_tuple_element_2 = BINARY_OPERATION_MULT_OBJECT_UNICODE_LONG(tmp_mult_expr_left_2, tmp_mult_expr_right_2);
            Py_DECREF(tmp_mult_expr_right_2);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 3, tmp_tuple_element_2);
            if (Nuitka_Cell_GET(var_reset) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 281;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_2;
            }

            tmp_format_value_15 = Nuitka_Cell_GET(var_reset);
            tmp_format_spec_15 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_15, tmp_format_spec_15);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 281;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 4, tmp_tuple_element_2);
        }
        goto tuple_build_noexception_2;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_2:;
        Py_DECREF(tmp_args_element_value_7);
        Py_DECREF(tmp_string_concat_values_2);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_2:;
        tmp_args_element_value_8 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_2);
        Py_DECREF(tmp_string_concat_values_2);
        if (tmp_args_element_value_8 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_args_element_value_7);

            exception_lineno = 281;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 281;
        {
            PyObject *call_args[] = {tmp_args_element_value_7, tmp_args_element_value_8};
            tmp_args_element_value_6 = CALL_FUNCTION_WITH_ARGS2(tstate, tmp_called_value_6, call_args);
        }

        Py_DECREF(tmp_args_element_value_7);
        Py_DECREF(tmp_args_element_value_8);
        if (tmp_args_element_value_6 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 281;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 281;
        tmp_call_result_4 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_5, tmp_args_element_value_6);
        Py_DECREF(tmp_args_element_value_6);
        if (tmp_call_result_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 281;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        Py_DECREF(tmp_call_result_4);
    }
    {
        PyObject *tmp_called_value_8;
        PyObject *tmp_call_result_5;
        PyObject *tmp_args_element_value_10;
        PyObject *tmp_string_concat_values_3;
        PyObject *tmp_tuple_element_3;
        PyObject *tmp_format_value_16;
        PyObject *tmp_format_spec_16;
        tmp_called_value_8 = LOOKUP_BUILTIN(mod_consts[54]);
        assert(tmp_called_value_8 != NULL);
        if (Nuitka_Cell_GET(var_red) == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 282;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }

        tmp_format_value_16 = Nuitka_Cell_GET(var_red);
        tmp_format_spec_16 = mod_consts[44];
        tmp_tuple_element_3 = BUILTIN_FORMAT(tstate, tmp_format_value_16, tmp_format_spec_16);
        if (tmp_tuple_element_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 282;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_string_concat_values_3 = MAKE_TUPLE_EMPTY(5);
        {
            PyObject *tmp_format_value_17;
            PyObject *tmp_dict_arg_value_5;
            PyObject *tmp_key_value_5;
            PyObject *tmp_format_spec_17;
            PyObject *tmp_format_value_18;
            PyObject *tmp_mult_expr_left_3;
            PyObject *tmp_mult_expr_right_3;
            PyObject *tmp_sub_expr_left_7;
            PyObject *tmp_sub_expr_right_7;
            PyObject *tmp_format_spec_18;
            PyObject *tmp_format_value_19;
            PyObject *tmp_dict_arg_value_6;
            PyObject *tmp_key_value_6;
            PyObject *tmp_format_spec_19;
            PyObject *tmp_format_value_20;
            PyObject *tmp_format_spec_20;
            PyTuple_SET_ITEM(tmp_string_concat_values_3, 0, tmp_tuple_element_3);
            CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
            tmp_dict_arg_value_5 = Nuitka_Cell_GET(var_chars);
            tmp_key_value_5 = mod_consts[64];
            tmp_format_value_17 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_5, tmp_key_value_5);
            if (tmp_format_value_17 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 282;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_3;
            }
            tmp_format_spec_17 = mod_consts[44];
            tmp_tuple_element_3 = BUILTIN_FORMAT(tstate, tmp_format_value_17, tmp_format_spec_17);
            Py_DECREF(tmp_format_value_17);
            if (tmp_tuple_element_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 282;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_3;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_3, 1, tmp_tuple_element_3);
            tmp_mult_expr_left_3 = mod_consts[48];
            tmp_sub_expr_left_7 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

            if (unlikely(tmp_sub_expr_left_7 == NULL)) {
                tmp_sub_expr_left_7 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
            }

            if (tmp_sub_expr_left_7 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 282;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_3;
            }
            tmp_sub_expr_right_7 = mod_consts[51];
            tmp_mult_expr_right_3 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_7, tmp_sub_expr_right_7);
            if (tmp_mult_expr_right_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 282;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_3;
            }
            tmp_format_value_18 = BINARY_OPERATION_MULT_OBJECT_UNICODE_OBJECT(tmp_mult_expr_left_3, tmp_mult_expr_right_3);
            Py_DECREF(tmp_mult_expr_right_3);
            if (tmp_format_value_18 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 282;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_3;
            }
            tmp_format_spec_18 = mod_consts[44];
            tmp_tuple_element_3 = BUILTIN_FORMAT(tstate, tmp_format_value_18, tmp_format_spec_18);
            Py_DECREF(tmp_format_value_18);
            if (tmp_tuple_element_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 282;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_3;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_3, 2, tmp_tuple_element_3);
            CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
            tmp_dict_arg_value_6 = Nuitka_Cell_GET(var_chars);
            tmp_key_value_6 = mod_consts[64];
            tmp_format_value_19 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_6, tmp_key_value_6);
            if (tmp_format_value_19 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 282;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_3;
            }
            tmp_format_spec_19 = mod_consts[44];
            tmp_tuple_element_3 = BUILTIN_FORMAT(tstate, tmp_format_value_19, tmp_format_spec_19);
            Py_DECREF(tmp_format_value_19);
            if (tmp_tuple_element_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 282;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_3;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_3, 3, tmp_tuple_element_3);
            if (Nuitka_Cell_GET(var_reset) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 282;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_3;
            }

            tmp_format_value_20 = Nuitka_Cell_GET(var_reset);
            tmp_format_spec_20 = mod_consts[44];
            tmp_tuple_element_3 = BUILTIN_FORMAT(tstate, tmp_format_value_20, tmp_format_spec_20);
            if (tmp_tuple_element_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 282;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_3;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_3, 4, tmp_tuple_element_3);
        }
        goto tuple_build_noexception_3;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_3:;
        Py_DECREF(tmp_string_concat_values_3);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_3:;
        tmp_args_element_value_10 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_3);
        Py_DECREF(tmp_string_concat_values_3);
        if (tmp_args_element_value_10 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 282;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 282;
        tmp_call_result_5 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_8, tmp_args_element_value_10);
        Py_DECREF(tmp_args_element_value_10);
        if (tmp_call_result_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 282;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        Py_DECREF(tmp_call_result_5);
    }
    {
        PyObject *tmp_assign_source_50;
        PyObject *tmp_called_instance_6;
        PyObject *tmp_args_element_value_11;
        PyObject *tmp_args_element_value_12;
        tmp_called_instance_6 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[65]);

        if (unlikely(tmp_called_instance_6 == NULL)) {
            tmp_called_instance_6 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[65]);
        }

        if (tmp_called_instance_6 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 285;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_args_element_value_11 = mod_consts[67];
        CHECK_OBJECT(var_message);
        tmp_args_element_value_12 = var_message;
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 285;
        {
            PyObject *call_args[] = {tmp_args_element_value_11, tmp_args_element_value_12};
            tmp_assign_source_50 = CALL_METHOD_WITH_ARGS2(
                tstate,
                tmp_called_instance_6,
                mod_consts[66],
                call_args
            );
        }

        if (tmp_assign_source_50 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 285;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        assert(Nuitka_Cell_GET(var_hex_code) == NULL);
        PyCell_SET(var_hex_code, tmp_assign_source_50);

    }
    {
        PyObject *tmp_assign_source_51;
        CHECK_OBJECT(Nuitka_Cell_GET(var_hex_code));
        tmp_assign_source_51 = Nuitka_Cell_GET(var_hex_code);
        assert(Nuitka_Cell_GET(var__hex_code) == NULL);
        Py_INCREF(tmp_assign_source_51);
        PyCell_SET(var__hex_code, tmp_assign_source_51);

    }
    {
        nuitka_bool tmp_condition_result_6;
        int tmp_truth_name_2;
        CHECK_OBJECT(Nuitka_Cell_GET(var_hex_code));
        tmp_truth_name_2 = CHECK_IF_TRUE(Nuitka_Cell_GET(var_hex_code));
        if (tmp_truth_name_2 == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 287;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_6 = tmp_truth_name_2 == 0 ? NUITKA_BOOL_FALSE : NUITKA_BOOL_TRUE;
        if (tmp_condition_result_6 == NUITKA_BOOL_TRUE) {
            goto branch_yes_3;
        } else {
            goto branch_no_3;
        }
    }
    branch_yes_3:;
    {
        PyObject *tmp_assign_source_52;
        PyObject *tmp_string_concat_values_4;
        PyObject *tmp_tuple_element_4;
        PyObject *tmp_format_value_21;
        PyObject *tmp_called_instance_7;
        PyObject *tmp_format_spec_21;
        CHECK_OBJECT(Nuitka_Cell_GET(var_hex_code));
        tmp_called_instance_7 = Nuitka_Cell_GET(var_hex_code);
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 288;
        tmp_format_value_21 = CALL_METHOD_WITH_SINGLE_ARG(
            tstate,
            tmp_called_instance_7,
            mod_consts[68],
            PyTuple_GET_ITEM(mod_consts[69], 0)
        );

        if (tmp_format_value_21 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 288;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_format_spec_21 = mod_consts[44];
        tmp_tuple_element_4 = BUILTIN_FORMAT(tstate, tmp_format_value_21, tmp_format_spec_21);
        Py_DECREF(tmp_format_value_21);
        if (tmp_tuple_element_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 288;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_string_concat_values_4 = MAKE_TUPLE_EMPTY(3);
        {
            PyObject *tmp_format_value_22;
            PyObject *tmp_called_instance_8;
            PyObject *tmp_format_spec_22;
            PyTuple_SET_ITEM(tmp_string_concat_values_4, 0, tmp_tuple_element_4);
            tmp_tuple_element_4 = mod_consts[70];
            PyTuple_SET_ITEM0(tmp_string_concat_values_4, 1, tmp_tuple_element_4);
            CHECK_OBJECT(Nuitka_Cell_GET(var_hex_code));
            tmp_called_instance_8 = Nuitka_Cell_GET(var_hex_code);
            frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 288;
            tmp_format_value_22 = CALL_METHOD_WITH_SINGLE_ARG(
                tstate,
                tmp_called_instance_8,
                mod_consts[68],
                PyTuple_GET_ITEM(mod_consts[71], 0)
            );

            if (tmp_format_value_22 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 288;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_4;
            }
            tmp_format_spec_22 = mod_consts[44];
            tmp_tuple_element_4 = BUILTIN_FORMAT(tstate, tmp_format_value_22, tmp_format_spec_22);
            Py_DECREF(tmp_format_value_22);
            if (tmp_tuple_element_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 288;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_4;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_4, 2, tmp_tuple_element_4);
        }
        goto tuple_build_noexception_4;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_4:;
        Py_DECREF(tmp_string_concat_values_4);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_4:;
        tmp_assign_source_52 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_4);
        Py_DECREF(tmp_string_concat_values_4);
        if (tmp_assign_source_52 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 288;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = Nuitka_Cell_GET(var_hex_code);
            PyCell_SET(var_hex_code, tmp_assign_source_52);
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_53;
        PyObject *tmp_called_value_9;
        PyObject *tmp_expression_value_13;
        PyObject *tmp_args_element_value_13;
        PyObject *tmp_string_concat_values_5;
        PyObject *tmp_tuple_element_5;
        PyObject *tmp_args_element_value_14;
        CHECK_OBJECT(var_message);
        tmp_expression_value_13 = var_message;
        tmp_called_value_9 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_13, mod_consts[72]);
        if (tmp_called_value_9 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 289;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_tuple_element_5 = mod_consts[73];
        tmp_string_concat_values_5 = MAKE_TUPLE_EMPTY(3);
        PyTuple_SET_ITEM0(tmp_string_concat_values_5, 0, tmp_tuple_element_5);
        CHECK_OBJECT(Nuitka_Cell_GET(var_hex_code));
        tmp_tuple_element_5 = Nuitka_Cell_GET(var_hex_code);
        PyTuple_SET_ITEM0(tmp_string_concat_values_5, 1, tmp_tuple_element_5);
        tmp_tuple_element_5 = mod_consts[74];
        PyTuple_SET_ITEM0(tmp_string_concat_values_5, 2, tmp_tuple_element_5);
        tmp_args_element_value_13 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_5);
        Py_DECREF(tmp_string_concat_values_5);
        if (tmp_args_element_value_13 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_called_value_9);

            exception_lineno = 289;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_args_element_value_14 = mod_consts[44];
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 289;
        {
            PyObject *call_args[] = {tmp_args_element_value_13, tmp_args_element_value_14};
            tmp_assign_source_53 = CALL_FUNCTION_WITH_ARGS2(tstate, tmp_called_value_9, call_args);
        }

        Py_DECREF(tmp_called_value_9);
        Py_DECREF(tmp_args_element_value_13);
        if (tmp_assign_source_53 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 289;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = var_message;
            assert(old != NULL);
            var_message = tmp_assign_source_53;
            Py_DECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_54;
        PyObject *tmp_string_concat_values_6;
        PyObject *tmp_tuple_element_6;
        PyObject *tmp_format_value_23;
        PyObject *tmp_format_spec_23;
        if (Nuitka_Cell_GET(var_red) == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 290;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }

        tmp_format_value_23 = Nuitka_Cell_GET(var_red);
        tmp_format_spec_23 = mod_consts[44];
        tmp_tuple_element_6 = BUILTIN_FORMAT(tstate, tmp_format_value_23, tmp_format_spec_23);
        if (tmp_tuple_element_6 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 290;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_string_concat_values_6 = MAKE_TUPLE_EMPTY(13);
        {
            PyObject *tmp_format_value_24;
            PyObject *tmp_dict_arg_value_7;
            PyObject *tmp_key_value_7;
            PyObject *tmp_format_spec_24;
            PyObject *tmp_format_value_25;
            PyObject *tmp_mult_expr_left_4;
            PyObject *tmp_mult_expr_right_4;
            PyObject *tmp_dict_arg_value_8;
            PyObject *tmp_key_value_8;
            PyObject *tmp_format_spec_25;
            PyObject *tmp_format_value_26;
            PyObject *tmp_format_spec_26;
            PyObject *tmp_format_value_27;
            PyObject *tmp_format_spec_27;
            PyObject *tmp_format_value_28;
            PyObject *tmp_mult_expr_left_5;
            PyObject *tmp_mult_expr_right_5;
            PyObject *tmp_dict_arg_value_9;
            PyObject *tmp_key_value_9;
            PyObject *tmp_sub_expr_left_8;
            PyObject *tmp_sub_expr_right_8;
            PyObject *tmp_sub_expr_left_9;
            PyObject *tmp_sub_expr_right_9;
            PyObject *tmp_sub_expr_left_10;
            PyObject *tmp_sub_expr_right_10;
            PyObject *tmp_len_arg_4;
            PyObject *tmp_format_spec_28;
            PyObject *tmp_format_value_29;
            PyObject *tmp_dict_arg_value_10;
            PyObject *tmp_key_value_10;
            PyObject *tmp_format_spec_29;
            PyObject *tmp_format_value_30;
            PyObject *tmp_format_spec_30;
            PyTuple_SET_ITEM(tmp_string_concat_values_6, 0, tmp_tuple_element_6);
            CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
            tmp_dict_arg_value_7 = Nuitka_Cell_GET(var_chars);
            tmp_key_value_7 = mod_consts[64];
            tmp_format_value_24 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_7, tmp_key_value_7);
            if (tmp_format_value_24 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            tmp_format_spec_24 = mod_consts[44];
            tmp_tuple_element_6 = BUILTIN_FORMAT(tstate, tmp_format_value_24, tmp_format_spec_24);
            Py_DECREF(tmp_format_value_24);
            if (tmp_tuple_element_6 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_6, 1, tmp_tuple_element_6);
            tmp_tuple_element_6 = mod_consts[48];
            PyTuple_SET_ITEM0(tmp_string_concat_values_6, 2, tmp_tuple_element_6);
            CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
            tmp_dict_arg_value_8 = Nuitka_Cell_GET(var_chars);
            tmp_key_value_8 = mod_consts[46];
            tmp_mult_expr_left_4 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_8, tmp_key_value_8);
            if (tmp_mult_expr_left_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            tmp_mult_expr_right_4 = mod_consts[51];
            tmp_format_value_25 = BINARY_OPERATION_MULT_OBJECT_OBJECT_LONG(tmp_mult_expr_left_4, tmp_mult_expr_right_4);
            Py_DECREF(tmp_mult_expr_left_4);
            if (tmp_format_value_25 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            tmp_format_spec_25 = mod_consts[44];
            tmp_tuple_element_6 = BUILTIN_FORMAT(tstate, tmp_format_value_25, tmp_format_spec_25);
            Py_DECREF(tmp_format_value_25);
            if (tmp_tuple_element_6 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_6, 3, tmp_tuple_element_6);
            tmp_tuple_element_6 = mod_consts[48];
            PyTuple_SET_ITEM0(tmp_string_concat_values_6, 4, tmp_tuple_element_6);
            if (Nuitka_Cell_GET(var_bold_red) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[49]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }

            tmp_format_value_26 = Nuitka_Cell_GET(var_bold_red);
            tmp_format_spec_26 = mod_consts[44];
            tmp_tuple_element_6 = BUILTIN_FORMAT(tstate, tmp_format_value_26, tmp_format_spec_26);
            if (tmp_tuple_element_6 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_6, 5, tmp_tuple_element_6);
            CHECK_OBJECT(Nuitka_Cell_GET(var_hex_code));
            tmp_tuple_element_6 = Nuitka_Cell_GET(var_hex_code);
            PyTuple_SET_ITEM0(tmp_string_concat_values_6, 6, tmp_tuple_element_6);
            if (Nuitka_Cell_GET(var_red) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[43]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }

            tmp_format_value_27 = Nuitka_Cell_GET(var_red);
            tmp_format_spec_27 = mod_consts[44];
            tmp_tuple_element_6 = BUILTIN_FORMAT(tstate, tmp_format_value_27, tmp_format_spec_27);
            if (tmp_tuple_element_6 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_6, 7, tmp_tuple_element_6);
            tmp_tuple_element_6 = mod_consts[48];
            PyTuple_SET_ITEM0(tmp_string_concat_values_6, 8, tmp_tuple_element_6);
            CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
            tmp_dict_arg_value_9 = Nuitka_Cell_GET(var_chars);
            tmp_key_value_9 = mod_consts[46];
            tmp_mult_expr_left_5 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_9, tmp_key_value_9);
            if (tmp_mult_expr_left_5 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            tmp_sub_expr_left_10 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

            if (unlikely(tmp_sub_expr_left_10 == NULL)) {
                tmp_sub_expr_left_10 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
            }

            if (tmp_sub_expr_left_10 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_mult_expr_left_5);

                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            tmp_sub_expr_right_10 = mod_consts[75];
            tmp_sub_expr_left_9 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_10, tmp_sub_expr_right_10);
            if (tmp_sub_expr_left_9 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_mult_expr_left_5);

                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            CHECK_OBJECT(Nuitka_Cell_GET(var_hex_code));
            tmp_len_arg_4 = Nuitka_Cell_GET(var_hex_code);
            tmp_sub_expr_right_9 = BUILTIN_LEN(tstate, tmp_len_arg_4);
            assert(!(tmp_sub_expr_right_9 == NULL));
            tmp_sub_expr_left_8 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_9, tmp_sub_expr_right_9);
            Py_DECREF(tmp_sub_expr_left_9);
            Py_DECREF(tmp_sub_expr_right_9);
            if (tmp_sub_expr_left_8 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_mult_expr_left_5);

                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            tmp_sub_expr_right_8 = mod_consts[75];
            tmp_mult_expr_right_5 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_8, tmp_sub_expr_right_8);
            Py_DECREF(tmp_sub_expr_left_8);
            if (tmp_mult_expr_right_5 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_mult_expr_left_5);

                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            tmp_format_value_28 = BINARY_OPERATION_MULT_OBJECT_OBJECT_OBJECT(tmp_mult_expr_left_5, tmp_mult_expr_right_5);
            Py_DECREF(tmp_mult_expr_left_5);
            Py_DECREF(tmp_mult_expr_right_5);
            if (tmp_format_value_28 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            tmp_format_spec_28 = mod_consts[44];
            tmp_tuple_element_6 = BUILTIN_FORMAT(tstate, tmp_format_value_28, tmp_format_spec_28);
            Py_DECREF(tmp_format_value_28);
            if (tmp_tuple_element_6 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_6, 9, tmp_tuple_element_6);
            tmp_tuple_element_6 = mod_consts[48];
            PyTuple_SET_ITEM0(tmp_string_concat_values_6, 10, tmp_tuple_element_6);
            CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
            tmp_dict_arg_value_10 = Nuitka_Cell_GET(var_chars);
            tmp_key_value_10 = mod_consts[64];
            tmp_format_value_29 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_10, tmp_key_value_10);
            if (tmp_format_value_29 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            tmp_format_spec_29 = mod_consts[44];
            tmp_tuple_element_6 = BUILTIN_FORMAT(tstate, tmp_format_value_29, tmp_format_spec_29);
            Py_DECREF(tmp_format_value_29);
            if (tmp_tuple_element_6 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_6, 11, tmp_tuple_element_6);
            if (Nuitka_Cell_GET(var_reset) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }

            tmp_format_value_30 = Nuitka_Cell_GET(var_reset);
            tmp_format_spec_30 = mod_consts[44];
            tmp_tuple_element_6 = BUILTIN_FORMAT(tstate, tmp_format_value_30, tmp_format_spec_30);
            if (tmp_tuple_element_6 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 290;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_5;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_6, 12, tmp_tuple_element_6);
        }
        goto tuple_build_noexception_5;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_5:;
        Py_DECREF(tmp_string_concat_values_6);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_5:;
        tmp_assign_source_54 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_6);
        Py_DECREF(tmp_string_concat_values_6);
        if (tmp_assign_source_54 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 290;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = Nuitka_Cell_GET(var_hex_code);
            PyCell_SET(var_hex_code, tmp_assign_source_54);
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_called_value_10;
        PyObject *tmp_call_result_6;
        PyObject *tmp_args_element_value_15;
        tmp_called_value_10 = LOOKUP_BUILTIN(mod_consts[54]);
        assert(tmp_called_value_10 != NULL);
        CHECK_OBJECT(Nuitka_Cell_GET(var_hex_code));
        tmp_args_element_value_15 = Nuitka_Cell_GET(var_hex_code);
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 291;
        tmp_call_result_6 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_10, tmp_args_element_value_15);
        if (tmp_call_result_6 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 291;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        Py_DECREF(tmp_call_result_6);
    }
    goto branch_end_3;
    branch_no_3:;
    {
        PyObject *tmp_called_value_11;
        PyObject *tmp_call_result_7;
        PyObject *tmp_args_element_value_16;
        PyObject *tmp_string_concat_values_7;
        PyObject *tmp_tuple_element_7;
        PyObject *tmp_format_value_31;
        PyObject *tmp_format_spec_31;
        tmp_called_value_11 = LOOKUP_BUILTIN(mod_consts[54]);
        assert(tmp_called_value_11 != NULL);
        if (Nuitka_Cell_GET(var_red) == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 293;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }

        tmp_format_value_31 = Nuitka_Cell_GET(var_red);
        tmp_format_spec_31 = mod_consts[44];
        tmp_tuple_element_7 = BUILTIN_FORMAT(tstate, tmp_format_value_31, tmp_format_spec_31);
        if (tmp_tuple_element_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 293;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_string_concat_values_7 = MAKE_TUPLE_EMPTY(7);
        {
            PyObject *tmp_format_value_32;
            PyObject *tmp_dict_arg_value_11;
            PyObject *tmp_key_value_11;
            PyObject *tmp_format_spec_32;
            PyObject *tmp_format_value_33;
            PyObject *tmp_mult_expr_left_6;
            PyObject *tmp_mult_expr_right_6;
            PyObject *tmp_dict_arg_value_12;
            PyObject *tmp_key_value_12;
            PyObject *tmp_sub_expr_left_11;
            PyObject *tmp_sub_expr_right_11;
            PyObject *tmp_format_spec_33;
            PyObject *tmp_format_value_34;
            PyObject *tmp_dict_arg_value_13;
            PyObject *tmp_key_value_13;
            PyObject *tmp_format_spec_34;
            PyObject *tmp_format_value_35;
            PyObject *tmp_format_spec_35;
            PyTuple_SET_ITEM(tmp_string_concat_values_7, 0, tmp_tuple_element_7);
            CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
            tmp_dict_arg_value_11 = Nuitka_Cell_GET(var_chars);
            tmp_key_value_11 = mod_consts[64];
            tmp_format_value_32 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_11, tmp_key_value_11);
            if (tmp_format_value_32 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 293;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_6;
            }
            tmp_format_spec_32 = mod_consts[44];
            tmp_tuple_element_7 = BUILTIN_FORMAT(tstate, tmp_format_value_32, tmp_format_spec_32);
            Py_DECREF(tmp_format_value_32);
            if (tmp_tuple_element_7 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 293;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_6;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_7, 1, tmp_tuple_element_7);
            tmp_tuple_element_7 = mod_consts[48];
            PyTuple_SET_ITEM0(tmp_string_concat_values_7, 2, tmp_tuple_element_7);
            CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
            tmp_dict_arg_value_12 = Nuitka_Cell_GET(var_chars);
            tmp_key_value_12 = mod_consts[46];
            tmp_mult_expr_left_6 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_12, tmp_key_value_12);
            if (tmp_mult_expr_left_6 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 293;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_6;
            }
            tmp_sub_expr_left_11 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

            if (unlikely(tmp_sub_expr_left_11 == NULL)) {
                tmp_sub_expr_left_11 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
            }

            if (tmp_sub_expr_left_11 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_mult_expr_left_6);

                exception_lineno = 293;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_6;
            }
            tmp_sub_expr_right_11 = mod_consts[75];
            tmp_mult_expr_right_6 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_11, tmp_sub_expr_right_11);
            if (tmp_mult_expr_right_6 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_mult_expr_left_6);

                exception_lineno = 293;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_6;
            }
            tmp_format_value_33 = BINARY_OPERATION_MULT_OBJECT_OBJECT_OBJECT(tmp_mult_expr_left_6, tmp_mult_expr_right_6);
            Py_DECREF(tmp_mult_expr_left_6);
            Py_DECREF(tmp_mult_expr_right_6);
            if (tmp_format_value_33 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 293;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_6;
            }
            tmp_format_spec_33 = mod_consts[44];
            tmp_tuple_element_7 = BUILTIN_FORMAT(tstate, tmp_format_value_33, tmp_format_spec_33);
            Py_DECREF(tmp_format_value_33);
            if (tmp_tuple_element_7 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 293;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_6;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_7, 3, tmp_tuple_element_7);
            tmp_tuple_element_7 = mod_consts[48];
            PyTuple_SET_ITEM0(tmp_string_concat_values_7, 4, tmp_tuple_element_7);
            CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
            tmp_dict_arg_value_13 = Nuitka_Cell_GET(var_chars);
            tmp_key_value_13 = mod_consts[64];
            tmp_format_value_34 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_13, tmp_key_value_13);
            if (tmp_format_value_34 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 293;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_6;
            }
            tmp_format_spec_34 = mod_consts[44];
            tmp_tuple_element_7 = BUILTIN_FORMAT(tstate, tmp_format_value_34, tmp_format_spec_34);
            Py_DECREF(tmp_format_value_34);
            if (tmp_tuple_element_7 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 293;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_6;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_7, 5, tmp_tuple_element_7);
            if (Nuitka_Cell_GET(var_reset) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 293;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_6;
            }

            tmp_format_value_35 = Nuitka_Cell_GET(var_reset);
            tmp_format_spec_35 = mod_consts[44];
            tmp_tuple_element_7 = BUILTIN_FORMAT(tstate, tmp_format_value_35, tmp_format_spec_35);
            if (tmp_tuple_element_7 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 293;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_6;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_7, 6, tmp_tuple_element_7);
        }
        goto tuple_build_noexception_6;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_6:;
        Py_DECREF(tmp_string_concat_values_7);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_6:;
        tmp_args_element_value_16 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_7);
        Py_DECREF(tmp_string_concat_values_7);
        if (tmp_args_element_value_16 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 293;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 293;
        tmp_call_result_7 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_11, tmp_args_element_value_16);
        Py_DECREF(tmp_args_element_value_16);
        if (tmp_call_result_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 293;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        Py_DECREF(tmp_call_result_7);
    }
    branch_end_3:;
    {
        PyObject *tmp_assign_source_55;
        PyObject *tmp_annotations_7;
        struct Nuitka_CellObject *tmp_closure_6[6];
        tmp_annotations_7 = DICT_COPY(mod_consts[76]);

        tmp_closure_6[0] = var__hex_code;
        Py_INCREF(tmp_closure_6[0]);
        tmp_closure_6[1] = var_chars;
        Py_INCREF(tmp_closure_6[1]);
        tmp_closure_6[2] = var_hex_code;
        Py_INCREF(tmp_closure_6[2]);
        tmp_closure_6[3] = var_red;
        Py_INCREF(tmp_closure_6[3]);
        tmp_closure_6[4] = var_reset;
        Py_INCREF(tmp_closure_6[4]);
        tmp_closure_6[5] = var_yellow;
        Py_INCREF(tmp_closure_6[5]);

        tmp_assign_source_55 = MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__7_process_message(tmp_annotations_7, tmp_closure_6);

        assert(var_process_message == NULL);
        var_process_message = tmp_assign_source_55;
    }
    {
        PyObject *tmp_called_value_12;
        PyObject *tmp_call_result_8;
        PyObject *tmp_args_element_value_17;
        PyObject *tmp_str_arg_value_2;
        PyObject *tmp_iterable_value_2;
        PyObject *tmp_called_value_13;
        PyObject *tmp_args_element_value_18;
        tmp_called_value_12 = LOOKUP_BUILTIN(mod_consts[54]);
        assert(tmp_called_value_12 != NULL);
        tmp_str_arg_value_2 = mod_consts[57];
        CHECK_OBJECT(var_process_message);
        tmp_called_value_13 = var_process_message;
        if (var_message == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[79]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 307;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }

        tmp_args_element_value_18 = var_message;
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 307;
        tmp_iterable_value_2 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_13, tmp_args_element_value_18);
        if (tmp_iterable_value_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 307;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_args_element_value_17 = UNICODE_JOIN(tstate, tmp_str_arg_value_2, tmp_iterable_value_2);
        Py_DECREF(tmp_iterable_value_2);
        if (tmp_args_element_value_17 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 307;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 307;
        tmp_call_result_8 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_12, tmp_args_element_value_17);
        Py_DECREF(tmp_args_element_value_17);
        if (tmp_call_result_8 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 307;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        Py_DECREF(tmp_call_result_8);
    }
    {
        PyObject *tmp_assign_source_56;
        PyObject *tmp_len_arg_5;
        PyObject *tmp_add_expr_left_2;
        PyObject *tmp_add_expr_right_2;
        PyObject *tmp_add_expr_left_3;
        PyObject *tmp_add_expr_right_3;
        PyObject *tmp_unicode_arg_5;
        CHECK_OBJECT(par_file);
        tmp_add_expr_left_3 = par_file;
        tmp_add_expr_right_3 = mod_consts[80];
        tmp_add_expr_left_2 = BINARY_OPERATION_ADD_OBJECT_OBJECT_UNICODE(tmp_add_expr_left_3, tmp_add_expr_right_3);
        if (tmp_add_expr_left_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 310;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(Nuitka_Cell_GET(par_line_no));
        tmp_unicode_arg_5 = Nuitka_Cell_GET(par_line_no);
        tmp_add_expr_right_2 = BUILTIN_UNICODE1(tmp_unicode_arg_5);
        if (tmp_add_expr_right_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_2);

            exception_lineno = 310;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_len_arg_5 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_2, tmp_add_expr_right_2);
        Py_DECREF(tmp_add_expr_left_2);
        Py_DECREF(tmp_add_expr_right_2);
        if (tmp_len_arg_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 310;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_56 = BUILTIN_LEN(tstate, tmp_len_arg_5);
        Py_DECREF(tmp_len_arg_5);
        if (tmp_assign_source_56 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 310;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        assert(var_len_of_file == NULL);
        var_len_of_file = tmp_assign_source_56;
    }
    {
        PyObject *tmp_assign_source_57;
        PyObject *tmp_int_arg_1;
        PyObject *tmp_sub_expr_left_12;
        PyObject *tmp_sub_expr_right_12;
        PyObject *tmp_truediv_expr_left_1;
        PyObject *tmp_truediv_expr_right_1;
        PyObject *tmp_sub_expr_left_13;
        PyObject *tmp_sub_expr_right_13;
        PyObject *tmp_truediv_expr_left_2;
        PyObject *tmp_truediv_expr_right_2;
        tmp_sub_expr_left_13 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

        if (unlikely(tmp_sub_expr_left_13 == NULL)) {
            tmp_sub_expr_left_13 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
        }

        if (tmp_sub_expr_left_13 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 311;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_sub_expr_right_13 = mod_consts[75];
        tmp_truediv_expr_left_1 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_13, tmp_sub_expr_right_13);
        if (tmp_truediv_expr_left_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 311;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_truediv_expr_right_1 = mod_consts[51];
        tmp_sub_expr_left_12 = BINARY_OPERATION_TRUEDIV_OBJECT_OBJECT_LONG(tmp_truediv_expr_left_1, tmp_truediv_expr_right_1);
        Py_DECREF(tmp_truediv_expr_left_1);
        if (tmp_sub_expr_left_12 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 311;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(var_len_of_file);
        tmp_truediv_expr_left_2 = var_len_of_file;
        tmp_truediv_expr_right_2 = mod_consts[51];
        tmp_sub_expr_right_12 = BINARY_OPERATION_TRUEDIV_OBJECT_OBJECT_OBJECT(tmp_truediv_expr_left_2, tmp_truediv_expr_right_2);
        if (tmp_sub_expr_right_12 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_sub_expr_left_12);

            exception_lineno = 311;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_int_arg_1 = BINARY_OPERATION_SUB_OBJECT_OBJECT_FLOAT(tmp_sub_expr_left_12, tmp_sub_expr_right_12);
        Py_DECREF(tmp_sub_expr_left_12);
        Py_DECREF(tmp_sub_expr_right_12);
        if (tmp_int_arg_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 311;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_57 = PyNumber_Int(tmp_int_arg_1);
        Py_DECREF(tmp_int_arg_1);
        if (tmp_assign_source_57 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 311;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        assert(var_len_of_halfs == NULL);
        var_len_of_halfs = tmp_assign_source_57;
    }
    {
        nuitka_bool tmp_condition_result_7;
        PyObject *tmp_cmp_expr_left_3;
        PyObject *tmp_cmp_expr_right_3;
        CHECK_OBJECT(var_len_of_halfs);
        tmp_cmp_expr_left_3 = var_len_of_halfs;
        tmp_cmp_expr_right_3 = mod_consts[51];
        tmp_condition_result_7 = RICH_COMPARE_LT_NBOOL_OBJECT_LONG(tmp_cmp_expr_left_3, tmp_cmp_expr_right_3);
        if (tmp_condition_result_7 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 313;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        if (tmp_condition_result_7 == NUITKA_BOOL_TRUE) {
            goto branch_yes_4;
        } else {
            goto branch_no_4;
        }
    }
    branch_yes_4:;
    {
        PyObject *tmp_assign_source_58;
        tmp_assign_source_58 = IMPORT_HARD_OS();
        assert(!(tmp_assign_source_58 == NULL));
        assert(var_os == NULL);
        Py_INCREF(tmp_assign_source_58);
        var_os = tmp_assign_source_58;
    }
    {
        PyObject *tmp_assign_source_59;
        PyObject *tmp_add_expr_left_4;
        PyObject *tmp_add_expr_right_4;
        PyObject *tmp_called_instance_9;
        PyObject *tmp_args_element_value_19;
        tmp_add_expr_left_4 = mod_consts[81];
        tmp_called_instance_9 = IMPORT_HARD_NTPATH();
        assert(!(tmp_called_instance_9 == NULL));
        CHECK_OBJECT(par_file);
        tmp_args_element_value_19 = par_file;
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 315;
        tmp_add_expr_right_4 = CALL_METHOD_WITH_SINGLE_ARG(tstate, tmp_called_instance_9, mod_consts[82], tmp_args_element_value_19);
        if (tmp_add_expr_right_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 315;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_59 = BINARY_OPERATION_ADD_OBJECT_UNICODE_OBJECT(tmp_add_expr_left_4, tmp_add_expr_right_4);
        Py_DECREF(tmp_add_expr_right_4);
        if (tmp_assign_source_59 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 315;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = par_file;
            assert(old != NULL);
            par_file = tmp_assign_source_59;
            Py_DECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_60;
        PyObject *tmp_len_arg_6;
        PyObject *tmp_add_expr_left_5;
        PyObject *tmp_add_expr_right_5;
        PyObject *tmp_add_expr_left_6;
        PyObject *tmp_add_expr_right_6;
        PyObject *tmp_unicode_arg_6;
        CHECK_OBJECT(par_file);
        tmp_add_expr_left_6 = par_file;
        tmp_add_expr_right_6 = mod_consts[80];
        tmp_add_expr_left_5 = BINARY_OPERATION_ADD_OBJECT_OBJECT_UNICODE(tmp_add_expr_left_6, tmp_add_expr_right_6);
        if (tmp_add_expr_left_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 316;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(Nuitka_Cell_GET(par_line_no));
        tmp_unicode_arg_6 = Nuitka_Cell_GET(par_line_no);
        tmp_add_expr_right_5 = BUILTIN_UNICODE1(tmp_unicode_arg_6);
        if (tmp_add_expr_right_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_5);

            exception_lineno = 316;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_len_arg_6 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_5, tmp_add_expr_right_5);
        Py_DECREF(tmp_add_expr_left_5);
        Py_DECREF(tmp_add_expr_right_5);
        if (tmp_len_arg_6 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 316;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_60 = BUILTIN_LEN(tstate, tmp_len_arg_6);
        Py_DECREF(tmp_len_arg_6);
        if (tmp_assign_source_60 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 316;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = var_len_of_file;
            assert(old != NULL);
            var_len_of_file = tmp_assign_source_60;
            Py_DECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_61;
        PyObject *tmp_int_arg_2;
        PyObject *tmp_sub_expr_left_14;
        PyObject *tmp_sub_expr_right_14;
        PyObject *tmp_truediv_expr_left_3;
        PyObject *tmp_truediv_expr_right_3;
        PyObject *tmp_sub_expr_left_15;
        PyObject *tmp_sub_expr_right_15;
        PyObject *tmp_truediv_expr_left_4;
        PyObject *tmp_truediv_expr_right_4;
        tmp_sub_expr_left_15 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

        if (unlikely(tmp_sub_expr_left_15 == NULL)) {
            tmp_sub_expr_left_15 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
        }

        if (tmp_sub_expr_left_15 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 317;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_sub_expr_right_15 = mod_consts[75];
        tmp_truediv_expr_left_3 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_15, tmp_sub_expr_right_15);
        if (tmp_truediv_expr_left_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 317;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_truediv_expr_right_3 = mod_consts[51];
        tmp_sub_expr_left_14 = BINARY_OPERATION_TRUEDIV_OBJECT_OBJECT_LONG(tmp_truediv_expr_left_3, tmp_truediv_expr_right_3);
        Py_DECREF(tmp_truediv_expr_left_3);
        if (tmp_sub_expr_left_14 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 317;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(var_len_of_file);
        tmp_truediv_expr_left_4 = var_len_of_file;
        tmp_truediv_expr_right_4 = mod_consts[51];
        tmp_sub_expr_right_14 = BINARY_OPERATION_TRUEDIV_OBJECT_OBJECT_OBJECT(tmp_truediv_expr_left_4, tmp_truediv_expr_right_4);
        if (tmp_sub_expr_right_14 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_sub_expr_left_14);

            exception_lineno = 317;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_int_arg_2 = BINARY_OPERATION_SUB_OBJECT_OBJECT_FLOAT(tmp_sub_expr_left_14, tmp_sub_expr_right_14);
        Py_DECREF(tmp_sub_expr_left_14);
        Py_DECREF(tmp_sub_expr_right_14);
        if (tmp_int_arg_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 317;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_61 = PyNumber_Int(tmp_int_arg_2);
        Py_DECREF(tmp_int_arg_2);
        if (tmp_assign_source_61 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 317;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = var_len_of_halfs;
            assert(old != NULL);
            var_len_of_halfs = tmp_assign_source_61;
            Py_DECREF(old);
        }

    }
    branch_no_4:;
    {
        PyObject *tmp_assign_source_62;
        PyObject *tmp_add_expr_left_7;
        PyObject *tmp_add_expr_right_7;
        PyObject *tmp_add_expr_left_8;
        PyObject *tmp_add_expr_right_8;
        PyObject *tmp_dict_arg_value_14;
        PyObject *tmp_key_value_14;
        PyObject *tmp_str_arg_value_3;
        PyObject *tmp_string_concat_values_8;
        PyObject *tmp_tuple_element_8;
        PyObject *tmp_width_value_1;
        PyObject *tmp_sub_expr_left_16;
        PyObject *tmp_sub_expr_right_16;
        PyObject *tmp_fillchar_value_1;
        PyObject *tmp_dict_arg_value_15;
        PyObject *tmp_key_value_15;
        PyObject *tmp_dict_arg_value_16;
        PyObject *tmp_key_value_16;
        CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
        tmp_dict_arg_value_14 = Nuitka_Cell_GET(var_chars);
        tmp_key_value_14 = mod_consts[83];
        tmp_add_expr_left_8 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_14, tmp_key_value_14);
        if (tmp_add_expr_left_8 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 319;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_tuple_element_8 = mod_consts[48];
        tmp_string_concat_values_8 = MAKE_TUPLE_EMPTY(5);
        {
            PyObject *tmp_format_value_36;
            PyObject *tmp_format_spec_36;
            PyObject *tmp_format_value_37;
            PyObject *tmp_format_spec_37;
            PyTuple_SET_ITEM0(tmp_string_concat_values_8, 0, tmp_tuple_element_8);
            if (par_file == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[84]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 319;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_7;
            }

            tmp_format_value_36 = par_file;
            tmp_format_spec_36 = mod_consts[44];
            tmp_tuple_element_8 = BUILTIN_FORMAT(tstate, tmp_format_value_36, tmp_format_spec_36);
            if (tmp_tuple_element_8 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 319;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_7;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_8, 1, tmp_tuple_element_8);
            tmp_tuple_element_8 = mod_consts[80];
            PyTuple_SET_ITEM0(tmp_string_concat_values_8, 2, tmp_tuple_element_8);
            CHECK_OBJECT(Nuitka_Cell_GET(par_line_no));
            tmp_format_value_37 = Nuitka_Cell_GET(par_line_no);
            tmp_format_spec_37 = mod_consts[44];
            tmp_tuple_element_8 = BUILTIN_FORMAT(tstate, tmp_format_value_37, tmp_format_spec_37);
            if (tmp_tuple_element_8 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 319;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_7;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_8, 3, tmp_tuple_element_8);
            tmp_tuple_element_8 = mod_consts[48];
            PyTuple_SET_ITEM0(tmp_string_concat_values_8, 4, tmp_tuple_element_8);
        }
        goto tuple_build_noexception_7;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_7:;
        Py_DECREF(tmp_add_expr_left_8);
        Py_DECREF(tmp_string_concat_values_8);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_7:;
        tmp_str_arg_value_3 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_8);
        Py_DECREF(tmp_string_concat_values_8);
        if (tmp_str_arg_value_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_8);

            exception_lineno = 319;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_sub_expr_left_16 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

        if (unlikely(tmp_sub_expr_left_16 == NULL)) {
            tmp_sub_expr_left_16 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
        }

        if (tmp_sub_expr_left_16 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_8);
            Py_DECREF(tmp_str_arg_value_3);

            exception_lineno = 319;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_sub_expr_right_16 = mod_consts[51];
        tmp_width_value_1 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_16, tmp_sub_expr_right_16);
        if (tmp_width_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_8);
            Py_DECREF(tmp_str_arg_value_3);

            exception_lineno = 319;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
        tmp_dict_arg_value_15 = Nuitka_Cell_GET(var_chars);
        tmp_key_value_15 = mod_consts[46];
        tmp_fillchar_value_1 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_15, tmp_key_value_15);
        if (tmp_fillchar_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_8);
            Py_DECREF(tmp_str_arg_value_3);
            Py_DECREF(tmp_width_value_1);

            exception_lineno = 319;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_right_8 = UNICODE_CENTER3(tstate, tmp_str_arg_value_3, tmp_width_value_1, tmp_fillchar_value_1);
        Py_DECREF(tmp_str_arg_value_3);
        Py_DECREF(tmp_width_value_1);
        Py_DECREF(tmp_fillchar_value_1);
        if (tmp_add_expr_right_8 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_8);

            exception_lineno = 319;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_left_7 = BINARY_OPERATION_ADD_OBJECT_OBJECT_UNICODE(tmp_add_expr_left_8, tmp_add_expr_right_8);
        Py_DECREF(tmp_add_expr_left_8);
        Py_DECREF(tmp_add_expr_right_8);
        if (tmp_add_expr_left_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 319;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(Nuitka_Cell_GET(var_chars));
        tmp_dict_arg_value_16 = Nuitka_Cell_GET(var_chars);
        tmp_key_value_16 = mod_consts[85];
        tmp_add_expr_right_7 = DICT_GET_ITEM_WITH_ERROR(tstate, tmp_dict_arg_value_16, tmp_key_value_16);
        if (tmp_add_expr_right_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_7);

            exception_lineno = 319;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_62 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_7, tmp_add_expr_right_7);
        Py_DECREF(tmp_add_expr_left_7);
        Py_DECREF(tmp_add_expr_right_7);
        if (tmp_assign_source_62 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 319;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        assert(var_final_line == NULL);
        var_final_line = tmp_assign_source_62;
    }
    {
        PyObject *tmp_assign_source_63;
        PyObject *tmp_string_concat_values_9;
        PyObject *tmp_tuple_element_9;
        PyObject *tmp_format_value_38;
        PyObject *tmp_format_spec_38;
        if (Nuitka_Cell_GET(var_red) == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 320;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }

        tmp_format_value_38 = Nuitka_Cell_GET(var_red);
        tmp_format_spec_38 = mod_consts[44];
        tmp_tuple_element_9 = BUILTIN_FORMAT(tstate, tmp_format_value_38, tmp_format_spec_38);
        if (tmp_tuple_element_9 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 320;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_string_concat_values_9 = MAKE_TUPLE_EMPTY(3);
        {
            PyObject *tmp_format_value_39;
            PyObject *tmp_format_spec_39;
            PyObject *tmp_format_value_40;
            PyObject *tmp_format_spec_40;
            PyTuple_SET_ITEM(tmp_string_concat_values_9, 0, tmp_tuple_element_9);
            CHECK_OBJECT(var_final_line);
            tmp_format_value_39 = var_final_line;
            tmp_format_spec_39 = mod_consts[44];
            tmp_tuple_element_9 = BUILTIN_FORMAT(tstate, tmp_format_value_39, tmp_format_spec_39);
            if (tmp_tuple_element_9 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 320;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_8;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_9, 1, tmp_tuple_element_9);
            if (Nuitka_Cell_GET(var_reset) == NULL) {

                FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 320;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_8;
            }

            tmp_format_value_40 = Nuitka_Cell_GET(var_reset);
            tmp_format_spec_40 = mod_consts[44];
            tmp_tuple_element_9 = BUILTIN_FORMAT(tstate, tmp_format_value_40, tmp_format_spec_40);
            if (tmp_tuple_element_9 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 320;
                type_description_1 = "oocccooccooococccccocccocooccooo";
                goto tuple_build_exception_8;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_9, 2, tmp_tuple_element_9);
        }
        goto tuple_build_noexception_8;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_8:;
        Py_DECREF(tmp_string_concat_values_9);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_8:;
        tmp_assign_source_63 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_9);
        Py_DECREF(tmp_string_concat_values_9);
        if (tmp_assign_source_63 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 320;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = var_final_line;
            assert(old != NULL);
            var_final_line = tmp_assign_source_63;
            Py_DECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_64;
        PyObject *tmp_add_expr_left_9;
        PyObject *tmp_add_expr_right_9;
        PyObject *tmp_add_expr_left_10;
        PyObject *tmp_add_expr_right_10;
        PyObject *tmp_add_expr_left_11;
        PyObject *tmp_add_expr_right_11;
        PyObject *tmp_add_expr_left_12;
        PyObject *tmp_add_expr_right_12;
        PyObject *tmp_add_expr_left_13;
        PyObject *tmp_add_expr_right_13;
        PyObject *tmp_add_expr_left_14;
        PyObject *tmp_add_expr_right_14;
        PyObject *tmp_add_expr_left_15;
        PyObject *tmp_add_expr_right_15;
        PyObject *tmp_add_expr_left_16;
        PyObject *tmp_add_expr_right_16;
        PyObject *tmp_add_expr_left_17;
        PyObject *tmp_add_expr_right_17;
        PyObject *tmp_add_expr_left_18;
        PyObject *tmp_add_expr_right_18;
        PyObject *tmp_expression_value_14;
        PyObject *tmp_str_arg_value_4;
        PyObject *tmp_sep_value_1;
        PyObject *tmp_subscript_value_4;
        PyObject *tmp_unicode_arg_7;
        PyObject *tmp_expression_value_15;
        PyObject *tmp_expression_value_16;
        PyObject *tmp_str_arg_value_5;
        PyObject *tmp_sep_value_2;
        PyObject *tmp_subscript_value_5;
        PyObject *tmp_subscript_value_6;
        PyObject *tmp_start_value_2;
        PyObject *tmp_len_arg_7;
        PyObject *tmp_unicode_arg_8;
        PyObject *tmp_stop_value_2;
        CHECK_OBJECT(var_final_line);
        tmp_str_arg_value_4 = var_final_line;
        if (par_file == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[84]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }

        tmp_sep_value_1 = par_file;
        tmp_expression_value_14 = UNICODE_SPLIT2(tstate, tmp_str_arg_value_4, tmp_sep_value_1);
        if (tmp_expression_value_14 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_subscript_value_4 = mod_consts[15];
        tmp_add_expr_left_18 = LOOKUP_SUBSCRIPT_CONST(tstate, tmp_expression_value_14, tmp_subscript_value_4, 0);
        Py_DECREF(tmp_expression_value_14);
        if (tmp_add_expr_left_18 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(var_green);
        tmp_add_expr_right_18 = var_green;
        tmp_add_expr_left_17 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_18, tmp_add_expr_right_18);
        Py_DECREF(tmp_add_expr_left_18);
        if (tmp_add_expr_left_17 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        if (par_file == NULL) {
            Py_DECREF(tmp_add_expr_left_17);
            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[84]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }

        tmp_add_expr_right_17 = par_file;
        tmp_add_expr_left_16 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_17, tmp_add_expr_right_17);
        Py_DECREF(tmp_add_expr_left_17);
        if (tmp_add_expr_left_16 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        if (Nuitka_Cell_GET(var_reset) == NULL) {
            Py_DECREF(tmp_add_expr_left_16);
            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[47]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }

        tmp_add_expr_right_16 = Nuitka_Cell_GET(var_reset);
        tmp_add_expr_left_15 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_16, tmp_add_expr_right_16);
        Py_DECREF(tmp_add_expr_left_16);
        if (tmp_add_expr_left_15 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        if (Nuitka_Cell_GET(var_gray) == NULL) {
            Py_DECREF(tmp_add_expr_left_15);
            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[61]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }

        tmp_add_expr_right_15 = Nuitka_Cell_GET(var_gray);
        tmp_add_expr_left_14 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_15, tmp_add_expr_right_15);
        Py_DECREF(tmp_add_expr_left_15);
        if (tmp_add_expr_left_14 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_right_14 = mod_consts[80];
        tmp_add_expr_left_13 = BINARY_OPERATION_ADD_OBJECT_OBJECT_UNICODE(tmp_add_expr_left_14, tmp_add_expr_right_14);
        Py_DECREF(tmp_add_expr_left_14);
        if (tmp_add_expr_left_13 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(var_green);
        tmp_add_expr_right_13 = var_green;
        tmp_add_expr_left_12 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_13, tmp_add_expr_right_13);
        Py_DECREF(tmp_add_expr_left_13);
        if (tmp_add_expr_left_12 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(Nuitka_Cell_GET(par_line_no));
        tmp_unicode_arg_7 = Nuitka_Cell_GET(par_line_no);
        tmp_add_expr_right_12 = BUILTIN_UNICODE1(tmp_unicode_arg_7);
        if (tmp_add_expr_right_12 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_12);

            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_left_11 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_12, tmp_add_expr_right_12);
        Py_DECREF(tmp_add_expr_left_12);
        Py_DECREF(tmp_add_expr_right_12);
        if (tmp_add_expr_left_11 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        if (Nuitka_Cell_GET(var_red) == NULL) {
            Py_DECREF(tmp_add_expr_left_11);
            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }

        tmp_add_expr_right_11 = Nuitka_Cell_GET(var_red);
        tmp_add_expr_left_10 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_11, tmp_add_expr_right_11);
        Py_DECREF(tmp_add_expr_left_11);
        if (tmp_add_expr_left_10 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(var_final_line);
        tmp_str_arg_value_5 = var_final_line;
        tmp_sep_value_2 = mod_consts[80];
        tmp_expression_value_16 = UNICODE_SPLIT2(tstate, tmp_str_arg_value_5, tmp_sep_value_2);
        if (tmp_expression_value_16 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_10);

            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_subscript_value_5 = mod_consts[56];
        tmp_expression_value_15 = LOOKUP_SUBSCRIPT_CONST(tstate, tmp_expression_value_16, tmp_subscript_value_5, 1);
        Py_DECREF(tmp_expression_value_16);
        if (tmp_expression_value_15 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_10);

            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(Nuitka_Cell_GET(par_line_no));
        tmp_unicode_arg_8 = Nuitka_Cell_GET(par_line_no);
        tmp_len_arg_7 = BUILTIN_UNICODE1(tmp_unicode_arg_8);
        if (tmp_len_arg_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_10);
            Py_DECREF(tmp_expression_value_15);

            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_start_value_2 = BUILTIN_LEN(tstate, tmp_len_arg_7);
        Py_DECREF(tmp_len_arg_7);
        if (tmp_start_value_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_10);
            Py_DECREF(tmp_expression_value_15);

            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_stop_value_2 = Py_None;
        tmp_subscript_value_6 = MAKE_SLICE_OBJECT2(tmp_start_value_2, tmp_stop_value_2);
        Py_DECREF(tmp_start_value_2);
        assert(!(tmp_subscript_value_6 == NULL));
        tmp_add_expr_right_10 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_15, tmp_subscript_value_6);
        Py_DECREF(tmp_expression_value_15);
        Py_DECREF(tmp_subscript_value_6);
        if (tmp_add_expr_right_10 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_10);

            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_left_9 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_10, tmp_add_expr_right_10);
        Py_DECREF(tmp_add_expr_left_10);
        Py_DECREF(tmp_add_expr_right_10);
        if (tmp_add_expr_left_9 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        if (Nuitka_Cell_GET(var_reset) == NULL) {
            Py_DECREF(tmp_add_expr_left_9);
            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[47]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }

        tmp_add_expr_right_9 = Nuitka_Cell_GET(var_reset);
        tmp_assign_source_64 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_9, tmp_add_expr_right_9);
        Py_DECREF(tmp_add_expr_left_9);
        if (tmp_assign_source_64 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 321;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = var_final_line;
            assert(old != NULL);
            var_final_line = tmp_assign_source_64;
            Py_DECREF(old);
        }

    }
    {
        PyObject *tmp_called_value_14;
        PyObject *tmp_call_result_9;
        PyObject *tmp_args_element_value_20;
        tmp_called_value_14 = LOOKUP_BUILTIN(mod_consts[54]);
        assert(tmp_called_value_14 != NULL);
        CHECK_OBJECT(var_final_line);
        tmp_args_element_value_20 = var_final_line;
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 324;
        tmp_call_result_9 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_14, tmp_args_element_value_20);
        if (tmp_call_result_9 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 324;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        Py_DECREF(tmp_call_result_9);
    }
    {
        PyObject *tmp_called_instance_10;
        PyObject *tmp_call_result_10;
        tmp_called_instance_10 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[3]);

        if (unlikely(tmp_called_instance_10 == NULL)) {
            tmp_called_instance_10 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[3]);
        }

        if (tmp_called_instance_10 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 326;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 326;
        tmp_call_result_10 = CALL_METHOD_NO_ARGS(tstate, tmp_called_instance_10, mod_consts[86]);
        if (tmp_call_result_10 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 326;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        Py_DECREF(tmp_call_result_10);
    }
    {
        PyObject *tmp_called_value_15;
        PyObject *tmp_call_result_11;
        tmp_called_value_15 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[87]);

        if (unlikely(tmp_called_value_15 == NULL)) {
            tmp_called_value_15 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[87]);
        }

        if (tmp_called_value_15 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 327;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        frame_8318cdda338d5f423c718cf0c36f6739->m_frame.f_lineno = 327;
        tmp_call_result_11 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_15, mod_consts[69]);

        if (tmp_call_result_11 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 327;
            type_description_1 = "oocccooccooococccccocccocooccooo";
            goto frame_exception_exit_1;
        }
        Py_DECREF(tmp_call_result_11);
    }


    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto frame_no_exception_1;
    frame_exception_exit_1:


    if (exception_tb == NULL) {
        exception_tb = MAKE_TRACEBACK(frame_8318cdda338d5f423c718cf0c36f6739, exception_lineno);
    } else if (exception_tb->tb_frame != &frame_8318cdda338d5f423c718cf0c36f6739->m_frame) {
        exception_tb = ADD_TRACEBACK(exception_tb, frame_8318cdda338d5f423c718cf0c36f6739, exception_lineno);
    }

    // Attaches locals to frame if any.
    Nuitka_Frame_AttachLocals(
        frame_8318cdda338d5f423c718cf0c36f6739,
        type_description_1,
        par___error,
        par_file,
        par_line_no,
        par_mark,
        var_lines_to_print,
        var_name,
        var_message,
        var_lines,
        var_does_support_colors,
        var_top_section,
        var_len_of_file,
        var_final_line,
        var_chars,
        var_sys,
        var_red,
        var_bold_red,
        var_reset,
        var_gray,
        var_yellow,
        var_green,
        var_calculate_skip_ammout,
        var_count_spaces,
        var_line_without_spaces,
        var_mark_all,
        var_s_u,
        var_process_lines,
        var_mid_section,
        var_hex_code,
        var__hex_code,
        var_process_message,
        var_len_of_halfs,
        var_os
    );


    // Release cached frame if used for exception.
    if (frame_8318cdda338d5f423c718cf0c36f6739 == cache_frame_8318cdda338d5f423c718cf0c36f6739) {
#if _DEBUG_REFCOUNTS
        count_active_frame_cache_instances -= 1;
        count_released_frame_cache_instances += 1;
#endif
        Py_DECREF(cache_frame_8318cdda338d5f423c718cf0c36f6739);
        cache_frame_8318cdda338d5f423c718cf0c36f6739 = NULL;
    }

    assertFrameObject(frame_8318cdda338d5f423c718cf0c36f6739);

    // Put the previous frame back on top.
    popFrameStack(tstate);

    // Return the error.
    goto try_except_handler_1;
    frame_no_exception_1:;
    tmp_return_value = Py_None;
    Py_INCREF(tmp_return_value);
    goto try_return_handler_1;
    NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
    return NULL;
    // Return handler code:
    try_return_handler_1:;
    Py_XDECREF(par_file);
    par_file = NULL;
    CHECK_OBJECT(par_line_no);
    Py_DECREF(par_line_no);
    par_line_no = NULL;
    CHECK_OBJECT(par_mark);
    Py_DECREF(par_mark);
    par_mark = NULL;
    CHECK_OBJECT(var_lines_to_print);
    Py_DECREF(var_lines_to_print);
    var_lines_to_print = NULL;
    CHECK_OBJECT(var_name);
    Py_DECREF(var_name);
    var_name = NULL;
    Py_XDECREF(var_message);
    var_message = NULL;
    CHECK_OBJECT(var_lines);
    Py_DECREF(var_lines);
    var_lines = NULL;
    CHECK_OBJECT(var_does_support_colors);
    Py_DECREF(var_does_support_colors);
    var_does_support_colors = NULL;
    CHECK_OBJECT(var_top_section);
    Py_DECREF(var_top_section);
    var_top_section = NULL;
    CHECK_OBJECT(var_len_of_file);
    Py_DECREF(var_len_of_file);
    var_len_of_file = NULL;
    CHECK_OBJECT(var_final_line);
    Py_DECREF(var_final_line);
    var_final_line = NULL;
    CHECK_OBJECT(var_chars);
    Py_DECREF(var_chars);
    var_chars = NULL;
    CHECK_OBJECT(var_sys);
    Py_DECREF(var_sys);
    var_sys = NULL;
    CHECK_OBJECT(var_red);
    Py_DECREF(var_red);
    var_red = NULL;
    CHECK_OBJECT(var_bold_red);
    Py_DECREF(var_bold_red);
    var_bold_red = NULL;
    CHECK_OBJECT(var_reset);
    Py_DECREF(var_reset);
    var_reset = NULL;
    CHECK_OBJECT(var_gray);
    Py_DECREF(var_gray);
    var_gray = NULL;
    CHECK_OBJECT(var_yellow);
    Py_DECREF(var_yellow);
    var_yellow = NULL;
    CHECK_OBJECT(var_green);
    Py_DECREF(var_green);
    var_green = NULL;
    CHECK_OBJECT(var_calculate_skip_ammout);
    Py_DECREF(var_calculate_skip_ammout);
    var_calculate_skip_ammout = NULL;
    CHECK_OBJECT(var_count_spaces);
    Py_DECREF(var_count_spaces);
    var_count_spaces = NULL;
    CHECK_OBJECT(var_line_without_spaces);
    Py_DECREF(var_line_without_spaces);
    var_line_without_spaces = NULL;
    CHECK_OBJECT(var_mark_all);
    Py_DECREF(var_mark_all);
    var_mark_all = NULL;
    CHECK_OBJECT(var_s_u);
    Py_DECREF(var_s_u);
    var_s_u = NULL;
    Py_XDECREF(var_process_lines);
    var_process_lines = NULL;
    CHECK_OBJECT(var_mid_section);
    Py_DECREF(var_mid_section);
    var_mid_section = NULL;
    CHECK_OBJECT(var_hex_code);
    Py_DECREF(var_hex_code);
    var_hex_code = NULL;
    CHECK_OBJECT(var__hex_code);
    Py_DECREF(var__hex_code);
    var__hex_code = NULL;
    CHECK_OBJECT(var_process_message);
    Py_DECREF(var_process_message);
    var_process_message = NULL;
    CHECK_OBJECT(var_len_of_halfs);
    Py_DECREF(var_len_of_halfs);
    var_len_of_halfs = NULL;
    Py_XDECREF(var_os);
    var_os = NULL;
    goto function_return_exit;
    // Exception handler code:
    try_except_handler_1:;
    exception_keeper_type_9 = exception_type;
    exception_keeper_value_9 = exception_value;
    exception_keeper_tb_9 = exception_tb;
    exception_keeper_lineno_9 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(par_file);
    par_file = NULL;
    CHECK_OBJECT(par_line_no);
    Py_DECREF(par_line_no);
    par_line_no = NULL;
    CHECK_OBJECT(par_mark);
    Py_DECREF(par_mark);
    par_mark = NULL;
    CHECK_OBJECT(var_lines_to_print);
    Py_DECREF(var_lines_to_print);
    var_lines_to_print = NULL;
    Py_XDECREF(var_name);
    var_name = NULL;
    Py_XDECREF(var_message);
    var_message = NULL;
    CHECK_OBJECT(var_lines);
    Py_DECREF(var_lines);
    var_lines = NULL;
    CHECK_OBJECT(var_does_support_colors);
    Py_DECREF(var_does_support_colors);
    var_does_support_colors = NULL;
    Py_XDECREF(var_top_section);
    var_top_section = NULL;
    Py_XDECREF(var_len_of_file);
    var_len_of_file = NULL;
    Py_XDECREF(var_final_line);
    var_final_line = NULL;
    CHECK_OBJECT(var_chars);
    Py_DECREF(var_chars);
    var_chars = NULL;
    Py_XDECREF(var_sys);
    var_sys = NULL;
    CHECK_OBJECT(var_red);
    Py_DECREF(var_red);
    var_red = NULL;
    CHECK_OBJECT(var_bold_red);
    Py_DECREF(var_bold_red);
    var_bold_red = NULL;
    CHECK_OBJECT(var_reset);
    Py_DECREF(var_reset);
    var_reset = NULL;
    CHECK_OBJECT(var_gray);
    Py_DECREF(var_gray);
    var_gray = NULL;
    CHECK_OBJECT(var_yellow);
    Py_DECREF(var_yellow);
    var_yellow = NULL;
    Py_XDECREF(var_green);
    var_green = NULL;
    CHECK_OBJECT(var_calculate_skip_ammout);
    Py_DECREF(var_calculate_skip_ammout);
    var_calculate_skip_ammout = NULL;
    CHECK_OBJECT(var_count_spaces);
    Py_DECREF(var_count_spaces);
    var_count_spaces = NULL;
    CHECK_OBJECT(var_line_without_spaces);
    Py_DECREF(var_line_without_spaces);
    var_line_without_spaces = NULL;
    Py_XDECREF(var_mark_all);
    var_mark_all = NULL;
    CHECK_OBJECT(var_s_u);
    Py_DECREF(var_s_u);
    var_s_u = NULL;
    Py_XDECREF(var_process_lines);
    var_process_lines = NULL;
    Py_XDECREF(var_mid_section);
    var_mid_section = NULL;
    CHECK_OBJECT(var_hex_code);
    Py_DECREF(var_hex_code);
    var_hex_code = NULL;
    CHECK_OBJECT(var__hex_code);
    Py_DECREF(var__hex_code);
    var__hex_code = NULL;
    Py_XDECREF(var_process_message);
    var_process_message = NULL;
    Py_XDECREF(var_len_of_halfs);
    var_len_of_halfs = NULL;
    Py_XDECREF(var_os);
    var_os = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_9;
    exception_value = exception_keeper_value_9;
    exception_tb = exception_keeper_tb_9;
    exception_lineno = exception_keeper_lineno_9;

    goto function_exception_exit;
    // End of try:

    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;

function_exception_exit:
    CHECK_OBJECT(par___error);
    Py_DECREF(par___error);
    assert(exception_type);
    RESTORE_ERROR_OCCURRED(tstate, exception_type, exception_value, exception_tb);

    return NULL;

function_return_exit:
   // Function cleanup code if any.
    CHECK_OBJECT(par___error);
    Py_DECREF(par___error);

   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}


static PyObject *impl_core$panic$$$function__2_panic$$$function__1_calculate_skip_ammout(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *par_line = python_pars[0];
    PyObject *var_output = NULL;
    PyObject *var_char = NULL;
    PyObject *tmp_for_loop_1__for_iterator = NULL;
    PyObject *tmp_for_loop_1__iter_value = NULL;
    struct Nuitka_FrameObject *frame_023af1584b736d71b82c14535d5153cb;
    NUITKA_MAY_BE_UNUSED char const *type_description_1 = NULL;
    PyObject *exception_type = NULL;
    PyObject *exception_value = NULL;
    PyTracebackObject *exception_tb = NULL;
    NUITKA_MAY_BE_UNUSED int exception_lineno = 0;
    bool tmp_result;
    PyObject *exception_keeper_type_1;
    PyObject *exception_keeper_value_1;
    PyTracebackObject *exception_keeper_tb_1;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_1;
    PyObject *tmp_return_value = NULL;
    static struct Nuitka_FrameObject *cache_frame_023af1584b736d71b82c14535d5153cb = NULL;
    PyObject *exception_keeper_type_2;
    PyObject *exception_keeper_value_2;
    PyTracebackObject *exception_keeper_tb_2;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_2;

    // Actual function body.
    {
        PyObject *tmp_assign_source_1;
        tmp_assign_source_1 = mod_consts[15];
        assert(var_output == NULL);
        Py_INCREF(tmp_assign_source_1);
        var_output = tmp_assign_source_1;
    }
    // Tried code:
    if (isFrameUnusable(cache_frame_023af1584b736d71b82c14535d5153cb)) {
        Py_XDECREF(cache_frame_023af1584b736d71b82c14535d5153cb);

#if _DEBUG_REFCOUNTS
        if (cache_frame_023af1584b736d71b82c14535d5153cb == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_frame_023af1584b736d71b82c14535d5153cb = MAKE_FUNCTION_FRAME(tstate, codeobj_023af1584b736d71b82c14535d5153cb, module_core$panic, sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_frame_023af1584b736d71b82c14535d5153cb->m_type_description == NULL);
    frame_023af1584b736d71b82c14535d5153cb = cache_frame_023af1584b736d71b82c14535d5153cb;

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackCompiledFrame(tstate, frame_023af1584b736d71b82c14535d5153cb);
    assert(Py_REFCNT(frame_023af1584b736d71b82c14535d5153cb) == 2);

    // Framed code:
    {
        nuitka_bool tmp_condition_result_1;
        PyObject *tmp_cmp_expr_left_1;
        PyObject *tmp_cmp_expr_right_1;
        PyObject *tmp_expression_value_1;
        PyObject *tmp_subscript_value_1;
        CHECK_OBJECT(par_line);
        tmp_expression_value_1 = par_line;
        tmp_subscript_value_1 = mod_consts[15];
        tmp_cmp_expr_left_1 = LOOKUP_SUBSCRIPT_CONST(tstate, tmp_expression_value_1, tmp_subscript_value_1, 0);
        if (tmp_cmp_expr_left_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 170;
            type_description_1 = "oooc";
            goto frame_exception_exit_1;
        }
        tmp_cmp_expr_right_1 = mod_consts[88];
        tmp_condition_result_1 = RICH_COMPARE_EQ_NBOOL_OBJECT_UNICODE(tmp_cmp_expr_left_1, tmp_cmp_expr_right_1);
        Py_DECREF(tmp_cmp_expr_left_1);
        if (tmp_condition_result_1 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 170;
            type_description_1 = "oooc";
            goto frame_exception_exit_1;
        }
        if (tmp_condition_result_1 == NUITKA_BOOL_TRUE) {
            goto branch_yes_1;
        } else {
            goto branch_no_1;
        }
    }
    branch_yes_1:;
    {
        PyObject *tmp_assign_source_2;
        PyObject *tmp_iadd_expr_left_1;
        nuitka_digit tmp_iadd_expr_right_1;
        CHECK_OBJECT(var_output);
        tmp_iadd_expr_left_1 = var_output;
        tmp_iadd_expr_right_1 = 1;
        tmp_result = INPLACE_OPERATION_ADD_LONG_DIGIT(&tmp_iadd_expr_left_1, tmp_iadd_expr_right_1);
        assert(!(tmp_result == false));
        tmp_assign_source_2 = tmp_iadd_expr_left_1;
        var_output = tmp_assign_source_2;

    }
    branch_no_1:;
    {
        PyObject *tmp_assign_source_3;
        PyObject *tmp_iter_arg_1;
        PyObject *tmp_called_value_1;
        PyObject *tmp_args_element_value_1;
        PyObject *tmp_expression_value_2;
        PyObject *tmp_subscript_value_2;
        if (Nuitka_Cell_GET(self->m_closure[0]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[38]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 172;
            type_description_1 = "oooc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_1 = Nuitka_Cell_GET(self->m_closure[0]);
        CHECK_OBJECT(par_line);
        tmp_expression_value_2 = par_line;
        tmp_subscript_value_2 = mod_consts[89];
        tmp_args_element_value_1 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_2, tmp_subscript_value_2);
        if (tmp_args_element_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 172;
            type_description_1 = "oooc";
            goto frame_exception_exit_1;
        }
        frame_023af1584b736d71b82c14535d5153cb->m_frame.f_lineno = 172;
        tmp_iter_arg_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_1, tmp_args_element_value_1);
        Py_DECREF(tmp_args_element_value_1);
        if (tmp_iter_arg_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 172;
            type_description_1 = "oooc";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_3 = MAKE_ITERATOR(tstate, tmp_iter_arg_1);
        Py_DECREF(tmp_iter_arg_1);
        if (tmp_assign_source_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 172;
            type_description_1 = "oooc";
            goto frame_exception_exit_1;
        }
        assert(tmp_for_loop_1__for_iterator == NULL);
        tmp_for_loop_1__for_iterator = tmp_assign_source_3;
    }
    // Tried code:
    loop_start_1:;
    {
        PyObject *tmp_next_source_1;
        PyObject *tmp_assign_source_4;
        CHECK_OBJECT(tmp_for_loop_1__for_iterator);
        tmp_next_source_1 = tmp_for_loop_1__for_iterator;
        tmp_assign_source_4 = ITERATOR_NEXT(tmp_next_source_1);
        if (tmp_assign_source_4 == NULL) {
            if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                goto loop_end_1;
            } else {

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                type_description_1 = "oooc";
                exception_lineno = 172;
                goto try_except_handler_2;
            }
        }

        {
            PyObject *old = tmp_for_loop_1__iter_value;
            tmp_for_loop_1__iter_value = tmp_assign_source_4;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_5;
        CHECK_OBJECT(tmp_for_loop_1__iter_value);
        tmp_assign_source_5 = tmp_for_loop_1__iter_value;
        {
            PyObject *old = var_char;
            var_char = tmp_assign_source_5;
            Py_INCREF(var_char);
            Py_XDECREF(old);
        }

    }
    {
        nuitka_bool tmp_condition_result_2;
        PyObject *tmp_cmp_expr_left_2;
        PyObject *tmp_cmp_expr_right_2;
        CHECK_OBJECT(var_char);
        tmp_cmp_expr_left_2 = var_char;
        tmp_cmp_expr_right_2 = mod_consts[48];
        tmp_condition_result_2 = RICH_COMPARE_EQ_NBOOL_OBJECT_UNICODE(tmp_cmp_expr_left_2, tmp_cmp_expr_right_2);
        if (tmp_condition_result_2 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 173;
            type_description_1 = "oooc";
            goto try_except_handler_2;
        }
        if (tmp_condition_result_2 == NUITKA_BOOL_TRUE) {
            goto branch_yes_2;
        } else {
            goto branch_no_2;
        }
    }
    branch_yes_2:;
    {
        PyObject *tmp_assign_source_6;
        PyObject *tmp_iadd_expr_left_2;
        PyObject *tmp_iadd_expr_right_2;
        if (var_output == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[90]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 174;
            type_description_1 = "oooc";
            goto try_except_handler_2;
        }

        tmp_iadd_expr_left_2 = var_output;
        tmp_iadd_expr_right_2 = mod_consts[56];
        tmp_result = INPLACE_OPERATION_ADD_OBJECT_LONG(&tmp_iadd_expr_left_2, tmp_iadd_expr_right_2);
        if (tmp_result == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 174;
            type_description_1 = "oooc";
            goto try_except_handler_2;
        }
        tmp_assign_source_6 = tmp_iadd_expr_left_2;
        var_output = tmp_assign_source_6;

    }
    goto branch_end_2;
    branch_no_2:;
    {
        nuitka_bool tmp_condition_result_3;
        PyObject *tmp_called_value_2;
        PyObject *tmp_expression_value_3;
        PyObject *tmp_call_result_1;
        int tmp_truth_name_1;
        CHECK_OBJECT(var_char);
        tmp_expression_value_3 = var_char;
        tmp_called_value_2 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_3, mod_consts[91]);
        if (tmp_called_value_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 175;
            type_description_1 = "oooc";
            goto try_except_handler_2;
        }
        frame_023af1584b736d71b82c14535d5153cb->m_frame.f_lineno = 175;
        tmp_call_result_1 = CALL_FUNCTION_NO_ARGS(tstate, tmp_called_value_2);
        Py_DECREF(tmp_called_value_2);
        if (tmp_call_result_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 175;
            type_description_1 = "oooc";
            goto try_except_handler_2;
        }
        tmp_truth_name_1 = CHECK_IF_TRUE(tmp_call_result_1);
        if (tmp_truth_name_1 == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_call_result_1);

            exception_lineno = 175;
            type_description_1 = "oooc";
            goto try_except_handler_2;
        }
        tmp_condition_result_3 = tmp_truth_name_1 == 0 ? NUITKA_BOOL_FALSE : NUITKA_BOOL_TRUE;
        Py_DECREF(tmp_call_result_1);
        if (tmp_condition_result_3 == NUITKA_BOOL_TRUE) {
            goto branch_yes_3;
        } else {
            goto branch_no_3;
        }
    }
    branch_yes_3:;
    {
        PyObject *tmp_assign_source_7;
        PyObject *tmp_iadd_expr_left_3;
        PyObject *tmp_iadd_expr_right_3;
        if (var_output == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[90]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 176;
            type_description_1 = "oooc";
            goto try_except_handler_2;
        }

        tmp_iadd_expr_left_3 = var_output;
        tmp_iadd_expr_right_3 = mod_consts[56];
        tmp_result = INPLACE_OPERATION_ADD_OBJECT_LONG(&tmp_iadd_expr_left_3, tmp_iadd_expr_right_3);
        if (tmp_result == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 176;
            type_description_1 = "oooc";
            goto try_except_handler_2;
        }
        tmp_assign_source_7 = tmp_iadd_expr_left_3;
        var_output = tmp_assign_source_7;

    }
    goto branch_end_3;
    branch_no_3:;
    {
        nuitka_bool tmp_condition_result_4;
        PyObject *tmp_cmp_expr_left_3;
        PyObject *tmp_cmp_expr_right_3;
        CHECK_OBJECT(var_char);
        tmp_cmp_expr_left_3 = var_char;
        tmp_cmp_expr_right_3 = mod_consts[92];
        tmp_condition_result_4 = RICH_COMPARE_EQ_NBOOL_OBJECT_UNICODE(tmp_cmp_expr_left_3, tmp_cmp_expr_right_3);
        if (tmp_condition_result_4 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 177;
            type_description_1 = "oooc";
            goto try_except_handler_2;
        }
        if (tmp_condition_result_4 == NUITKA_BOOL_TRUE) {
            goto branch_yes_4;
        } else {
            goto branch_no_4;
        }
    }
    branch_yes_4:;
    {
        PyObject *tmp_assign_source_8;
        PyObject *tmp_iadd_expr_left_4;
        PyObject *tmp_iadd_expr_right_4;
        if (var_output == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[90]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 178;
            type_description_1 = "oooc";
            goto try_except_handler_2;
        }

        tmp_iadd_expr_left_4 = var_output;
        tmp_iadd_expr_right_4 = mod_consts[56];
        tmp_result = INPLACE_OPERATION_ADD_OBJECT_LONG(&tmp_iadd_expr_left_4, tmp_iadd_expr_right_4);
        if (tmp_result == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 178;
            type_description_1 = "oooc";
            goto try_except_handler_2;
        }
        tmp_assign_source_8 = tmp_iadd_expr_left_4;
        var_output = tmp_assign_source_8;

    }
    goto loop_end_1;
    branch_no_4:;
    branch_end_3:;
    branch_end_2:;
    if (CONSIDER_THREADING(tstate) == false) {
        assert(HAS_ERROR_OCCURRED(tstate));

        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


        exception_lineno = 172;
        type_description_1 = "oooc";
        goto try_except_handler_2;
    }
    goto loop_start_1;
    loop_end_1:;
    goto try_end_1;
    // Exception handler code:
    try_except_handler_2:;
    exception_keeper_type_1 = exception_type;
    exception_keeper_value_1 = exception_value;
    exception_keeper_tb_1 = exception_tb;
    exception_keeper_lineno_1 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(tmp_for_loop_1__iter_value);
    tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_1__for_iterator);
    Py_DECREF(tmp_for_loop_1__for_iterator);
    tmp_for_loop_1__for_iterator = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_1;
    exception_value = exception_keeper_value_1;
    exception_tb = exception_keeper_tb_1;
    exception_lineno = exception_keeper_lineno_1;

    goto frame_exception_exit_1;
    // End of try:
    try_end_1:;
    Py_XDECREF(tmp_for_loop_1__iter_value);
    tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_1__for_iterator);
    Py_DECREF(tmp_for_loop_1__for_iterator);
    tmp_for_loop_1__for_iterator = NULL;
    if (var_output == NULL) {

        FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[90]);
        exception_tb = NULL;
        NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
        CHAIN_EXCEPTION(tstate, exception_value);

        exception_lineno = 180;
        type_description_1 = "oooc";
        goto frame_exception_exit_1;
    }

    tmp_return_value = var_output;
    Py_INCREF(tmp_return_value);
    goto frame_return_exit_1;


    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto frame_no_exception_1;
    frame_return_exit_1:

    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto try_return_handler_1;
    frame_exception_exit_1:


    if (exception_tb == NULL) {
        exception_tb = MAKE_TRACEBACK(frame_023af1584b736d71b82c14535d5153cb, exception_lineno);
    } else if (exception_tb->tb_frame != &frame_023af1584b736d71b82c14535d5153cb->m_frame) {
        exception_tb = ADD_TRACEBACK(exception_tb, frame_023af1584b736d71b82c14535d5153cb, exception_lineno);
    }

    // Attaches locals to frame if any.
    Nuitka_Frame_AttachLocals(
        frame_023af1584b736d71b82c14535d5153cb,
        type_description_1,
        par_line,
        var_output,
        var_char,
        self->m_closure[0]
    );


    // Release cached frame if used for exception.
    if (frame_023af1584b736d71b82c14535d5153cb == cache_frame_023af1584b736d71b82c14535d5153cb) {
#if _DEBUG_REFCOUNTS
        count_active_frame_cache_instances -= 1;
        count_released_frame_cache_instances += 1;
#endif
        Py_DECREF(cache_frame_023af1584b736d71b82c14535d5153cb);
        cache_frame_023af1584b736d71b82c14535d5153cb = NULL;
    }

    assertFrameObject(frame_023af1584b736d71b82c14535d5153cb);

    // Put the previous frame back on top.
    popFrameStack(tstate);

    // Return the error.
    goto try_except_handler_1;
    frame_no_exception_1:;
    NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
    return NULL;
    // Return handler code:
    try_return_handler_1:;
    Py_XDECREF(var_output);
    var_output = NULL;
    Py_XDECREF(var_char);
    var_char = NULL;
    goto function_return_exit;
    // Exception handler code:
    try_except_handler_1:;
    exception_keeper_type_2 = exception_type;
    exception_keeper_value_2 = exception_value;
    exception_keeper_tb_2 = exception_tb;
    exception_keeper_lineno_2 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(var_output);
    var_output = NULL;
    Py_XDECREF(var_char);
    var_char = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_2;
    exception_value = exception_keeper_value_2;
    exception_tb = exception_keeper_tb_2;
    exception_lineno = exception_keeper_lineno_2;

    goto function_exception_exit;
    // End of try:

    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;

function_exception_exit:
    CHECK_OBJECT(par_line);
    Py_DECREF(par_line);
    assert(exception_type);
    RESTORE_ERROR_OCCURRED(tstate, exception_type, exception_value, exception_tb);

    return NULL;

function_return_exit:
   // Function cleanup code if any.
    CHECK_OBJECT(par_line);
    Py_DECREF(par_line);

   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}


static PyObject *impl_core$panic$$$function__2_panic$$$function__2_count_spaces(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *par_line = python_pars[0];
    PyObject *var_skip_amount = NULL;
    PyObject *var_output = NULL;
    PyObject *var_index = NULL;
    PyObject *var_char = NULL;
    PyObject *tmp_for_loop_1__for_iterator = NULL;
    PyObject *tmp_for_loop_1__iter_value = NULL;
    PyObject *tmp_tuple_unpack_1__element_1 = NULL;
    PyObject *tmp_tuple_unpack_1__element_2 = NULL;
    PyObject *tmp_tuple_unpack_1__source_iter = NULL;
    struct Nuitka_FrameObject *frame_14702094d157de72a92e00898e7cc298;
    NUITKA_MAY_BE_UNUSED char const *type_description_1 = NULL;
    PyObject *exception_type = NULL;
    PyObject *exception_value = NULL;
    PyTracebackObject *exception_tb = NULL;
    NUITKA_MAY_BE_UNUSED int exception_lineno = 0;
    PyObject *tmp_iterator_attempt;
    PyObject *exception_keeper_type_1;
    PyObject *exception_keeper_value_1;
    PyTracebackObject *exception_keeper_tb_1;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_1;
    PyObject *exception_keeper_type_2;
    PyObject *exception_keeper_value_2;
    PyTracebackObject *exception_keeper_tb_2;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_2;
    bool tmp_result;
    PyObject *exception_keeper_type_3;
    PyObject *exception_keeper_value_3;
    PyTracebackObject *exception_keeper_tb_3;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_3;
    PyObject *tmp_return_value = NULL;
    static struct Nuitka_FrameObject *cache_frame_14702094d157de72a92e00898e7cc298 = NULL;
    PyObject *exception_keeper_type_4;
    PyObject *exception_keeper_value_4;
    PyTracebackObject *exception_keeper_tb_4;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_4;

    // Actual function body.
    // Tried code:
    if (isFrameUnusable(cache_frame_14702094d157de72a92e00898e7cc298)) {
        Py_XDECREF(cache_frame_14702094d157de72a92e00898e7cc298);

#if _DEBUG_REFCOUNTS
        if (cache_frame_14702094d157de72a92e00898e7cc298 == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_frame_14702094d157de72a92e00898e7cc298 = MAKE_FUNCTION_FRAME(tstate, codeobj_14702094d157de72a92e00898e7cc298, module_core$panic, sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_frame_14702094d157de72a92e00898e7cc298->m_type_description == NULL);
    frame_14702094d157de72a92e00898e7cc298 = cache_frame_14702094d157de72a92e00898e7cc298;

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackCompiledFrame(tstate, frame_14702094d157de72a92e00898e7cc298);
    assert(Py_REFCNT(frame_14702094d157de72a92e00898e7cc298) == 2);

    // Framed code:
    {
        PyObject *tmp_assign_source_1;
        PyObject *tmp_called_value_1;
        PyObject *tmp_args_element_value_1;
        if (Nuitka_Cell_GET(self->m_closure[0]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[27]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 186;
            type_description_1 = "oooooccc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_1 = Nuitka_Cell_GET(self->m_closure[0]);
        CHECK_OBJECT(par_line);
        tmp_args_element_value_1 = par_line;
        frame_14702094d157de72a92e00898e7cc298->m_frame.f_lineno = 186;
        tmp_assign_source_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_1, tmp_args_element_value_1);
        if (tmp_assign_source_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 186;
            type_description_1 = "oooooccc";
            goto frame_exception_exit_1;
        }
        assert(var_skip_amount == NULL);
        var_skip_amount = tmp_assign_source_1;
    }
    {
        PyObject *tmp_assign_source_2;
        tmp_assign_source_2 = mod_consts[15];
        assert(var_output == NULL);
        Py_INCREF(tmp_assign_source_2);
        var_output = tmp_assign_source_2;
    }
    {
        PyObject *tmp_assign_source_3;
        PyObject *tmp_iter_arg_1;
        PyObject *tmp_called_value_2;
        PyObject *tmp_args_element_value_2;
        PyObject *tmp_called_value_3;
        PyObject *tmp_args_element_value_3;
        tmp_called_value_2 = (PyObject *)&PyEnum_Type;
        if (Nuitka_Cell_GET(self->m_closure[2]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[38]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 188;
            type_description_1 = "oooooccc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_3 = Nuitka_Cell_GET(self->m_closure[2]);
        CHECK_OBJECT(par_line);
        tmp_args_element_value_3 = par_line;
        frame_14702094d157de72a92e00898e7cc298->m_frame.f_lineno = 188;
        tmp_args_element_value_2 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_3, tmp_args_element_value_3);
        if (tmp_args_element_value_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 188;
            type_description_1 = "oooooccc";
            goto frame_exception_exit_1;
        }
        frame_14702094d157de72a92e00898e7cc298->m_frame.f_lineno = 188;
        tmp_iter_arg_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_2, tmp_args_element_value_2);
        Py_DECREF(tmp_args_element_value_2);
        if (tmp_iter_arg_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 188;
            type_description_1 = "oooooccc";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_3 = MAKE_ITERATOR(tstate, tmp_iter_arg_1);
        Py_DECREF(tmp_iter_arg_1);
        if (tmp_assign_source_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 188;
            type_description_1 = "oooooccc";
            goto frame_exception_exit_1;
        }
        assert(tmp_for_loop_1__for_iterator == NULL);
        tmp_for_loop_1__for_iterator = tmp_assign_source_3;
    }
    // Tried code:
    loop_start_1:;
    {
        PyObject *tmp_next_source_1;
        PyObject *tmp_assign_source_4;
        CHECK_OBJECT(tmp_for_loop_1__for_iterator);
        tmp_next_source_1 = tmp_for_loop_1__for_iterator;
        tmp_assign_source_4 = ITERATOR_NEXT(tmp_next_source_1);
        if (tmp_assign_source_4 == NULL) {
            if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                goto loop_end_1;
            } else {

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                type_description_1 = "oooooccc";
                exception_lineno = 188;
                goto try_except_handler_2;
            }
        }

        {
            PyObject *old = tmp_for_loop_1__iter_value;
            tmp_for_loop_1__iter_value = tmp_assign_source_4;
            Py_XDECREF(old);
        }

    }
    // Tried code:
    {
        PyObject *tmp_assign_source_5;
        PyObject *tmp_iter_arg_2;
        CHECK_OBJECT(tmp_for_loop_1__iter_value);
        tmp_iter_arg_2 = tmp_for_loop_1__iter_value;
        tmp_assign_source_5 = MAKE_UNPACK_ITERATOR(tmp_iter_arg_2);
        if (tmp_assign_source_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 188;
            type_description_1 = "oooooccc";
            goto try_except_handler_3;
        }
        {
            PyObject *old = tmp_tuple_unpack_1__source_iter;
            tmp_tuple_unpack_1__source_iter = tmp_assign_source_5;
            Py_XDECREF(old);
        }

    }
    // Tried code:
    {
        PyObject *tmp_assign_source_6;
        PyObject *tmp_unpack_1;
        CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
        tmp_unpack_1 = tmp_tuple_unpack_1__source_iter;
        tmp_assign_source_6 = UNPACK_NEXT(tstate, tmp_unpack_1, 0, 2);
        if (tmp_assign_source_6 == NULL) {
            if (!HAS_ERROR_OCCURRED(tstate)) {
                exception_type = PyExc_StopIteration;
                Py_INCREF(exception_type);
                exception_value = NULL;
                exception_tb = NULL;
            } else {
                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            }


            type_description_1 = "oooooccc";
            exception_lineno = 188;
            goto try_except_handler_4;
        }
        {
            PyObject *old = tmp_tuple_unpack_1__element_1;
            tmp_tuple_unpack_1__element_1 = tmp_assign_source_6;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_7;
        PyObject *tmp_unpack_2;
        CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
        tmp_unpack_2 = tmp_tuple_unpack_1__source_iter;
        tmp_assign_source_7 = UNPACK_NEXT(tstate, tmp_unpack_2, 1, 2);
        if (tmp_assign_source_7 == NULL) {
            if (!HAS_ERROR_OCCURRED(tstate)) {
                exception_type = PyExc_StopIteration;
                Py_INCREF(exception_type);
                exception_value = NULL;
                exception_tb = NULL;
            } else {
                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            }


            type_description_1 = "oooooccc";
            exception_lineno = 188;
            goto try_except_handler_4;
        }
        {
            PyObject *old = tmp_tuple_unpack_1__element_2;
            tmp_tuple_unpack_1__element_2 = tmp_assign_source_7;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_iterator_name_1;
        CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
        tmp_iterator_name_1 = tmp_tuple_unpack_1__source_iter;
        // Check if iterator has left-over elements.
        CHECK_OBJECT(tmp_iterator_name_1); assert(HAS_ITERNEXT(tmp_iterator_name_1));

        tmp_iterator_attempt = (*Py_TYPE(tmp_iterator_name_1)->tp_iternext)(tmp_iterator_name_1);

        if (likely(tmp_iterator_attempt == NULL)) {
            PyObject *error = GET_ERROR_OCCURRED(tstate);

            if (error != NULL) {
                if (EXCEPTION_MATCH_BOOL_SINGLE(tstate, error, PyExc_StopIteration)) {
                    CLEAR_ERROR_OCCURRED(tstate);
                } else {
                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);

                    type_description_1 = "oooooccc";
                    exception_lineno = 188;
                    goto try_except_handler_4;
                }
            }
        } else {
            Py_DECREF(tmp_iterator_attempt);

            exception_type = PyExc_ValueError;
            Py_INCREF(PyExc_ValueError);
            exception_value = mod_consts[55];
            Py_INCREF(exception_value);
            exception_tb = NULL;

            type_description_1 = "oooooccc";
            exception_lineno = 188;
            goto try_except_handler_4;
        }
    }
    goto try_end_1;
    // Exception handler code:
    try_except_handler_4:;
    exception_keeper_type_1 = exception_type;
    exception_keeper_value_1 = exception_value;
    exception_keeper_tb_1 = exception_tb;
    exception_keeper_lineno_1 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
    Py_DECREF(tmp_tuple_unpack_1__source_iter);
    tmp_tuple_unpack_1__source_iter = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_1;
    exception_value = exception_keeper_value_1;
    exception_tb = exception_keeper_tb_1;
    exception_lineno = exception_keeper_lineno_1;

    goto try_except_handler_3;
    // End of try:
    try_end_1:;
    goto try_end_2;
    // Exception handler code:
    try_except_handler_3:;
    exception_keeper_type_2 = exception_type;
    exception_keeper_value_2 = exception_value;
    exception_keeper_tb_2 = exception_tb;
    exception_keeper_lineno_2 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(tmp_tuple_unpack_1__element_1);
    tmp_tuple_unpack_1__element_1 = NULL;
    Py_XDECREF(tmp_tuple_unpack_1__element_2);
    tmp_tuple_unpack_1__element_2 = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_2;
    exception_value = exception_keeper_value_2;
    exception_tb = exception_keeper_tb_2;
    exception_lineno = exception_keeper_lineno_2;

    goto try_except_handler_2;
    // End of try:
    try_end_2:;
    CHECK_OBJECT(tmp_tuple_unpack_1__source_iter);
    Py_DECREF(tmp_tuple_unpack_1__source_iter);
    tmp_tuple_unpack_1__source_iter = NULL;
    {
        PyObject *tmp_assign_source_8;
        CHECK_OBJECT(tmp_tuple_unpack_1__element_1);
        tmp_assign_source_8 = tmp_tuple_unpack_1__element_1;
        {
            PyObject *old = var_index;
            var_index = tmp_assign_source_8;
            Py_INCREF(var_index);
            Py_XDECREF(old);
        }

    }
    Py_XDECREF(tmp_tuple_unpack_1__element_1);
    tmp_tuple_unpack_1__element_1 = NULL;

    {
        PyObject *tmp_assign_source_9;
        CHECK_OBJECT(tmp_tuple_unpack_1__element_2);
        tmp_assign_source_9 = tmp_tuple_unpack_1__element_2;
        {
            PyObject *old = var_char;
            var_char = tmp_assign_source_9;
            Py_INCREF(var_char);
            Py_XDECREF(old);
        }

    }
    Py_XDECREF(tmp_tuple_unpack_1__element_2);
    tmp_tuple_unpack_1__element_2 = NULL;

    {
        nuitka_bool tmp_condition_result_1;
        PyObject *tmp_cmp_expr_left_1;
        PyObject *tmp_cmp_expr_right_1;
        CHECK_OBJECT(var_index);
        tmp_cmp_expr_left_1 = var_index;
        CHECK_OBJECT(var_skip_amount);
        tmp_cmp_expr_right_1 = var_skip_amount;
        tmp_condition_result_1 = RICH_COMPARE_LE_NBOOL_OBJECT_OBJECT(tmp_cmp_expr_left_1, tmp_cmp_expr_right_1);
        if (tmp_condition_result_1 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 189;
            type_description_1 = "oooooccc";
            goto try_except_handler_2;
        }
        if (tmp_condition_result_1 == NUITKA_BOOL_TRUE) {
            goto branch_yes_1;
        } else {
            goto branch_no_1;
        }
    }
    branch_yes_1:;
    goto loop_start_1;
    branch_no_1:;
    {
        nuitka_bool tmp_condition_result_2;
        PyObject *tmp_cmp_expr_left_2;
        PyObject *tmp_cmp_expr_right_2;
        CHECK_OBJECT(var_char);
        tmp_cmp_expr_left_2 = var_char;
        tmp_cmp_expr_right_2 = mod_consts[48];
        tmp_condition_result_2 = RICH_COMPARE_EQ_NBOOL_OBJECT_UNICODE(tmp_cmp_expr_left_2, tmp_cmp_expr_right_2);
        if (tmp_condition_result_2 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 190;
            type_description_1 = "oooooccc";
            goto try_except_handler_2;
        }
        if (tmp_condition_result_2 == NUITKA_BOOL_TRUE) {
            goto branch_yes_2;
        } else {
            goto branch_no_2;
        }
    }
    branch_yes_2:;
    {
        PyObject *tmp_assign_source_10;
        PyObject *tmp_iadd_expr_left_1;
        nuitka_digit tmp_iadd_expr_right_1;
        if (var_output == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[90]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 191;
            type_description_1 = "oooooccc";
            goto try_except_handler_2;
        }

        tmp_iadd_expr_left_1 = var_output;
        tmp_iadd_expr_right_1 = 1;
        tmp_result = INPLACE_OPERATION_ADD_LONG_DIGIT(&tmp_iadd_expr_left_1, tmp_iadd_expr_right_1);
        assert(!(tmp_result == false));
        tmp_assign_source_10 = tmp_iadd_expr_left_1;
        var_output = tmp_assign_source_10;

    }
    goto branch_end_2;
    branch_no_2:;
    goto loop_end_1;
    branch_end_2:;
    if (CONSIDER_THREADING(tstate) == false) {
        assert(HAS_ERROR_OCCURRED(tstate));

        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


        exception_lineno = 188;
        type_description_1 = "oooooccc";
        goto try_except_handler_2;
    }
    goto loop_start_1;
    loop_end_1:;
    goto try_end_3;
    // Exception handler code:
    try_except_handler_2:;
    exception_keeper_type_3 = exception_type;
    exception_keeper_value_3 = exception_value;
    exception_keeper_tb_3 = exception_tb;
    exception_keeper_lineno_3 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(tmp_for_loop_1__iter_value);
    tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_1__for_iterator);
    Py_DECREF(tmp_for_loop_1__for_iterator);
    tmp_for_loop_1__for_iterator = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_3;
    exception_value = exception_keeper_value_3;
    exception_tb = exception_keeper_tb_3;
    exception_lineno = exception_keeper_lineno_3;

    goto frame_exception_exit_1;
    // End of try:
    try_end_3:;
    Py_XDECREF(tmp_for_loop_1__iter_value);
    tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_1__for_iterator);
    Py_DECREF(tmp_for_loop_1__for_iterator);
    tmp_for_loop_1__for_iterator = NULL;
    {
        PyObject *tmp_add_expr_left_1;
        PyObject *tmp_add_expr_right_1;
        nuitka_bool tmp_condition_result_3;
        int tmp_truth_name_1;
        if (var_output == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[90]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 193;
            type_description_1 = "oooooccc";
            goto frame_exception_exit_1;
        }

        tmp_add_expr_left_1 = var_output;
        if (Nuitka_Cell_GET(self->m_closure[1]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[93]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 193;
            type_description_1 = "oooooccc";
            goto frame_exception_exit_1;
        }

        tmp_truth_name_1 = CHECK_IF_TRUE(Nuitka_Cell_GET(self->m_closure[1]));
        if (tmp_truth_name_1 == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 193;
            type_description_1 = "oooooccc";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_3 = tmp_truth_name_1 == 0 ? NUITKA_BOOL_FALSE : NUITKA_BOOL_TRUE;
        if (tmp_condition_result_3 == NUITKA_BOOL_TRUE) {
            goto condexpr_true_1;
        } else {
            goto condexpr_false_1;
        }
        condexpr_true_1:;
        tmp_add_expr_right_1 = mod_consts[56];
        goto condexpr_end_1;
        condexpr_false_1:;
        tmp_add_expr_right_1 = mod_consts[15];
        condexpr_end_1:;
        tmp_return_value = BINARY_OPERATION_ADD_OBJECT_LONG_LONG(tmp_add_expr_left_1, tmp_add_expr_right_1);
        assert(!(tmp_return_value == NULL));
        goto frame_return_exit_1;
    }


    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto frame_no_exception_1;
    frame_return_exit_1:

    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto try_return_handler_1;
    frame_exception_exit_1:


    if (exception_tb == NULL) {
        exception_tb = MAKE_TRACEBACK(frame_14702094d157de72a92e00898e7cc298, exception_lineno);
    } else if (exception_tb->tb_frame != &frame_14702094d157de72a92e00898e7cc298->m_frame) {
        exception_tb = ADD_TRACEBACK(exception_tb, frame_14702094d157de72a92e00898e7cc298, exception_lineno);
    }

    // Attaches locals to frame if any.
    Nuitka_Frame_AttachLocals(
        frame_14702094d157de72a92e00898e7cc298,
        type_description_1,
        par_line,
        var_skip_amount,
        var_output,
        var_index,
        var_char,
        self->m_closure[0],
        self->m_closure[2],
        self->m_closure[1]
    );


    // Release cached frame if used for exception.
    if (frame_14702094d157de72a92e00898e7cc298 == cache_frame_14702094d157de72a92e00898e7cc298) {
#if _DEBUG_REFCOUNTS
        count_active_frame_cache_instances -= 1;
        count_released_frame_cache_instances += 1;
#endif
        Py_DECREF(cache_frame_14702094d157de72a92e00898e7cc298);
        cache_frame_14702094d157de72a92e00898e7cc298 = NULL;
    }

    assertFrameObject(frame_14702094d157de72a92e00898e7cc298);

    // Put the previous frame back on top.
    popFrameStack(tstate);

    // Return the error.
    goto try_except_handler_1;
    frame_no_exception_1:;
    NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
    return NULL;
    // Return handler code:
    try_return_handler_1:;
    CHECK_OBJECT(var_skip_amount);
    Py_DECREF(var_skip_amount);
    var_skip_amount = NULL;
    Py_XDECREF(var_output);
    var_output = NULL;
    Py_XDECREF(var_index);
    var_index = NULL;
    Py_XDECREF(var_char);
    var_char = NULL;
    goto function_return_exit;
    // Exception handler code:
    try_except_handler_1:;
    exception_keeper_type_4 = exception_type;
    exception_keeper_value_4 = exception_value;
    exception_keeper_tb_4 = exception_tb;
    exception_keeper_lineno_4 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(var_skip_amount);
    var_skip_amount = NULL;
    Py_XDECREF(var_output);
    var_output = NULL;
    Py_XDECREF(var_index);
    var_index = NULL;
    Py_XDECREF(var_char);
    var_char = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_4;
    exception_value = exception_keeper_value_4;
    exception_tb = exception_keeper_tb_4;
    exception_lineno = exception_keeper_lineno_4;

    goto function_exception_exit;
    // End of try:

    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;

function_exception_exit:
    CHECK_OBJECT(par_line);
    Py_DECREF(par_line);
    assert(exception_type);
    RESTORE_ERROR_OCCURRED(tstate, exception_type, exception_value, exception_tb);

    return NULL;

function_return_exit:
   // Function cleanup code if any.
    CHECK_OBJECT(par_line);
    Py_DECREF(par_line);

   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}


static PyObject *impl_core$panic$$$function__2_panic$$$function__3_line_without_spaces(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *par_line = python_pars[0];
    PyObject *var_skip_amount = NULL;
    PyObject *var_spaces = NULL;
    PyObject *var_output = NULL;
    struct Nuitka_FrameObject *frame_2edbc9deccd9aaf2cd319e276c33377e;
    NUITKA_MAY_BE_UNUSED char const *type_description_1 = NULL;
    PyObject *exception_type = NULL;
    PyObject *exception_value = NULL;
    PyTracebackObject *exception_tb = NULL;
    NUITKA_MAY_BE_UNUSED int exception_lineno = 0;
    static struct Nuitka_FrameObject *cache_frame_2edbc9deccd9aaf2cd319e276c33377e = NULL;
    PyObject *tmp_return_value = NULL;
    PyObject *exception_keeper_type_1;
    PyObject *exception_keeper_value_1;
    PyTracebackObject *exception_keeper_tb_1;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_1;

    // Actual function body.
    // Tried code:
    if (isFrameUnusable(cache_frame_2edbc9deccd9aaf2cd319e276c33377e)) {
        Py_XDECREF(cache_frame_2edbc9deccd9aaf2cd319e276c33377e);

#if _DEBUG_REFCOUNTS
        if (cache_frame_2edbc9deccd9aaf2cd319e276c33377e == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_frame_2edbc9deccd9aaf2cd319e276c33377e = MAKE_FUNCTION_FRAME(tstate, codeobj_2edbc9deccd9aaf2cd319e276c33377e, module_core$panic, sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_frame_2edbc9deccd9aaf2cd319e276c33377e->m_type_description == NULL);
    frame_2edbc9deccd9aaf2cd319e276c33377e = cache_frame_2edbc9deccd9aaf2cd319e276c33377e;

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackCompiledFrame(tstate, frame_2edbc9deccd9aaf2cd319e276c33377e);
    assert(Py_REFCNT(frame_2edbc9deccd9aaf2cd319e276c33377e) == 2);

    // Framed code:
    {
        PyObject *tmp_assign_source_1;
        PyObject *tmp_called_value_1;
        PyObject *tmp_args_element_value_1;
        if (Nuitka_Cell_GET(self->m_closure[0]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[27]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 198;
            type_description_1 = "oooocc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_1 = Nuitka_Cell_GET(self->m_closure[0]);
        CHECK_OBJECT(par_line);
        tmp_args_element_value_1 = par_line;
        frame_2edbc9deccd9aaf2cd319e276c33377e->m_frame.f_lineno = 198;
        tmp_assign_source_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_1, tmp_args_element_value_1);
        if (tmp_assign_source_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 198;
            type_description_1 = "oooocc";
            goto frame_exception_exit_1;
        }
        assert(var_skip_amount == NULL);
        var_skip_amount = tmp_assign_source_1;
    }
    {
        PyObject *tmp_assign_source_2;
        PyObject *tmp_called_value_2;
        PyObject *tmp_args_element_value_2;
        if (Nuitka_Cell_GET(self->m_closure[1]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[29]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 199;
            type_description_1 = "oooocc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_2 = Nuitka_Cell_GET(self->m_closure[1]);
        CHECK_OBJECT(par_line);
        tmp_args_element_value_2 = par_line;
        frame_2edbc9deccd9aaf2cd319e276c33377e->m_frame.f_lineno = 199;
        tmp_assign_source_2 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_2, tmp_args_element_value_2);
        if (tmp_assign_source_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 199;
            type_description_1 = "oooocc";
            goto frame_exception_exit_1;
        }
        assert(var_spaces == NULL);
        var_spaces = tmp_assign_source_2;
    }
    {
        PyObject *tmp_assign_source_3;
        PyObject *tmp_expression_value_1;
        PyObject *tmp_subscript_value_1;
        PyObject *tmp_start_value_1;
        PyObject *tmp_add_expr_left_1;
        PyObject *tmp_add_expr_right_1;
        PyObject *tmp_stop_value_1;
        CHECK_OBJECT(par_line);
        tmp_expression_value_1 = par_line;
        CHECK_OBJECT(var_spaces);
        tmp_add_expr_left_1 = var_spaces;
        CHECK_OBJECT(var_skip_amount);
        tmp_add_expr_right_1 = var_skip_amount;
        tmp_start_value_1 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_1, tmp_add_expr_right_1);
        if (tmp_start_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 200;
            type_description_1 = "oooocc";
            goto frame_exception_exit_1;
        }
        tmp_stop_value_1 = Py_None;
        tmp_subscript_value_1 = MAKE_SLICE_OBJECT2(tmp_start_value_1, tmp_stop_value_1);
        Py_DECREF(tmp_start_value_1);
        assert(!(tmp_subscript_value_1 == NULL));
        tmp_assign_source_3 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_1, tmp_subscript_value_1);
        Py_DECREF(tmp_subscript_value_1);
        if (tmp_assign_source_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 200;
            type_description_1 = "oooocc";
            goto frame_exception_exit_1;
        }
        assert(var_output == NULL);
        var_output = tmp_assign_source_3;
    }


    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto frame_no_exception_1;
    frame_exception_exit_1:


    if (exception_tb == NULL) {
        exception_tb = MAKE_TRACEBACK(frame_2edbc9deccd9aaf2cd319e276c33377e, exception_lineno);
    } else if (exception_tb->tb_frame != &frame_2edbc9deccd9aaf2cd319e276c33377e->m_frame) {
        exception_tb = ADD_TRACEBACK(exception_tb, frame_2edbc9deccd9aaf2cd319e276c33377e, exception_lineno);
    }

    // Attaches locals to frame if any.
    Nuitka_Frame_AttachLocals(
        frame_2edbc9deccd9aaf2cd319e276c33377e,
        type_description_1,
        par_line,
        var_skip_amount,
        var_spaces,
        var_output,
        self->m_closure[0],
        self->m_closure[1]
    );


    // Release cached frame if used for exception.
    if (frame_2edbc9deccd9aaf2cd319e276c33377e == cache_frame_2edbc9deccd9aaf2cd319e276c33377e) {
#if _DEBUG_REFCOUNTS
        count_active_frame_cache_instances -= 1;
        count_released_frame_cache_instances += 1;
#endif
        Py_DECREF(cache_frame_2edbc9deccd9aaf2cd319e276c33377e);
        cache_frame_2edbc9deccd9aaf2cd319e276c33377e = NULL;
    }

    assertFrameObject(frame_2edbc9deccd9aaf2cd319e276c33377e);

    // Put the previous frame back on top.
    popFrameStack(tstate);

    // Return the error.
    goto try_except_handler_1;
    frame_no_exception_1:;
    CHECK_OBJECT(var_output);
    tmp_return_value = var_output;
    Py_INCREF(tmp_return_value);
    goto try_return_handler_1;
    NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
    return NULL;
    // Return handler code:
    try_return_handler_1:;
    CHECK_OBJECT(var_skip_amount);
    Py_DECREF(var_skip_amount);
    var_skip_amount = NULL;
    CHECK_OBJECT(var_spaces);
    Py_DECREF(var_spaces);
    var_spaces = NULL;
    CHECK_OBJECT(var_output);
    Py_DECREF(var_output);
    var_output = NULL;
    goto function_return_exit;
    // Exception handler code:
    try_except_handler_1:;
    exception_keeper_type_1 = exception_type;
    exception_keeper_value_1 = exception_value;
    exception_keeper_tb_1 = exception_tb;
    exception_keeper_lineno_1 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(var_skip_amount);
    var_skip_amount = NULL;
    Py_XDECREF(var_spaces);
    var_spaces = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_1;
    exception_value = exception_keeper_value_1;
    exception_tb = exception_keeper_tb_1;
    exception_lineno = exception_keeper_lineno_1;

    goto function_exception_exit;
    // End of try:

    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;

function_exception_exit:
    CHECK_OBJECT(par_line);
    Py_DECREF(par_line);
    assert(exception_type);
    RESTORE_ERROR_OCCURRED(tstate, exception_type, exception_value, exception_tb);

    return NULL;

function_return_exit:
   // Function cleanup code if any.
    CHECK_OBJECT(par_line);
    Py_DECREF(par_line);

   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}


static PyObject *impl_core$panic$$$function__2_panic$$$function__4_mark_all(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *par_line = python_pars[0];
    PyObject *par_mark_line = python_pars[1];
    PyObject *var_output = NULL;
    PyObject *var_marked = NULL;
    PyObject *var_skip_amount = NULL;
    PyObject *var_len_of_item = NULL;
    PyObject *var_output_line = NULL;
    PyObject *var_item = NULL;
    PyObject *var_index = NULL;
    PyObject *tmp_for_loop_1__for_iterator = NULL;
    PyObject *tmp_for_loop_1__iter_value = NULL;
    PyObject *tmp_for_loop_2__for_iterator = NULL;
    PyObject *tmp_for_loop_2__iter_value = NULL;
    PyObject *tmp_for_loop_3__for_iterator = NULL;
    PyObject *tmp_for_loop_3__iter_value = NULL;
    PyObject *tmp_for_loop_4__for_iterator = NULL;
    PyObject *tmp_for_loop_4__iter_value = NULL;
    struct Nuitka_FrameObject *frame_e1d27883b2455e4c949dff371c0a8ceb;
    NUITKA_MAY_BE_UNUSED char const *type_description_1 = NULL;
    PyObject *exception_type = NULL;
    PyObject *exception_value = NULL;
    PyTracebackObject *exception_tb = NULL;
    NUITKA_MAY_BE_UNUSED int exception_lineno = 0;
    bool tmp_result;
    PyObject *exception_keeper_type_1;
    PyObject *exception_keeper_value_1;
    PyTracebackObject *exception_keeper_tb_1;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_1;
    PyObject *exception_keeper_type_2;
    PyObject *exception_keeper_value_2;
    PyTracebackObject *exception_keeper_tb_2;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_2;
    PyObject *exception_keeper_type_3;
    PyObject *exception_keeper_value_3;
    PyTracebackObject *exception_keeper_tb_3;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_3;
    PyObject *exception_keeper_type_4;
    PyObject *exception_keeper_value_4;
    PyTracebackObject *exception_keeper_tb_4;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_4;
    int tmp_res;
    NUITKA_MAY_BE_UNUSED nuitka_void tmp_unused;
    PyObject *tmp_return_value = NULL;
    static struct Nuitka_FrameObject *cache_frame_e1d27883b2455e4c949dff371c0a8ceb = NULL;
    PyObject *exception_keeper_type_5;
    PyObject *exception_keeper_value_5;
    PyTracebackObject *exception_keeper_tb_5;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_5;

    // Actual function body.
    {
        PyObject *tmp_assign_source_1;
        tmp_assign_source_1 = MAKE_LIST_EMPTY(0);
        assert(var_output == NULL);
        var_output = tmp_assign_source_1;
    }
    {
        PyObject *tmp_assign_source_2;
        tmp_assign_source_2 = MAKE_LIST_EMPTY(0);
        assert(var_output_line == NULL);
        var_output_line = tmp_assign_source_2;
    }
    // Tried code:
    if (isFrameUnusable(cache_frame_e1d27883b2455e4c949dff371c0a8ceb)) {
        Py_XDECREF(cache_frame_e1d27883b2455e4c949dff371c0a8ceb);

#if _DEBUG_REFCOUNTS
        if (cache_frame_e1d27883b2455e4c949dff371c0a8ceb == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_frame_e1d27883b2455e4c949dff371c0a8ceb = MAKE_FUNCTION_FRAME(tstate, codeobj_e1d27883b2455e4c949dff371c0a8ceb, module_core$panic, sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_frame_e1d27883b2455e4c949dff371c0a8ceb->m_type_description == NULL);
    frame_e1d27883b2455e4c949dff371c0a8ceb = cache_frame_e1d27883b2455e4c949dff371c0a8ceb;

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackCompiledFrame(tstate, frame_e1d27883b2455e4c949dff371c0a8ceb);
    assert(Py_REFCNT(frame_e1d27883b2455e4c949dff371c0a8ceb) == 2);

    // Framed code:
    {
        PyObject *tmp_assign_source_3;
        PyObject *tmp_called_value_1;
        PyObject *tmp_expression_value_1;
        CHECK_OBJECT(par_line);
        tmp_expression_value_1 = par_line;
        tmp_called_value_1 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_1, mod_consts[94]);
        if (tmp_called_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 211;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        frame_e1d27883b2455e4c949dff371c0a8ceb->m_frame.f_lineno = 211;
        tmp_assign_source_3 = CALL_FUNCTION_NO_ARGS(tstate, tmp_called_value_1);
        Py_DECREF(tmp_called_value_1);
        if (tmp_assign_source_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 211;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = par_line;
            assert(old != NULL);
            par_line = tmp_assign_source_3;
            Py_DECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_4;
        PyObject *tmp_iadd_expr_left_1;
        PyObject *tmp_iadd_expr_right_1;
        PyObject *tmp_mult_expr_left_1;
        PyObject *tmp_mult_expr_right_1;
        PyObject *tmp_sub_expr_left_1;
        PyObject *tmp_sub_expr_right_1;
        PyObject *tmp_len_arg_1;
        PyObject *tmp_called_value_2;
        PyObject *tmp_args_element_value_1;
        PyObject *tmp_len_arg_2;
        PyObject *tmp_called_value_3;
        PyObject *tmp_args_element_value_2;
        CHECK_OBJECT(par_mark_line);
        tmp_iadd_expr_left_1 = par_mark_line;
        tmp_mult_expr_left_1 = mod_consts[48];
        if (Nuitka_Cell_GET(self->m_closure[10]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[38]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 213;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_2 = Nuitka_Cell_GET(self->m_closure[10]);
        CHECK_OBJECT(par_line);
        tmp_args_element_value_1 = par_line;
        frame_e1d27883b2455e4c949dff371c0a8ceb->m_frame.f_lineno = 213;
        tmp_len_arg_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_2, tmp_args_element_value_1);
        if (tmp_len_arg_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 213;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_sub_expr_left_1 = BUILTIN_LEN(tstate, tmp_len_arg_1);
        Py_DECREF(tmp_len_arg_1);
        if (tmp_sub_expr_left_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 213;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        if (Nuitka_Cell_GET(self->m_closure[10]) == NULL) {
            Py_DECREF(tmp_sub_expr_left_1);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[38]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 213;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_3 = Nuitka_Cell_GET(self->m_closure[10]);
        CHECK_OBJECT(par_mark_line);
        tmp_args_element_value_2 = par_mark_line;
        frame_e1d27883b2455e4c949dff371c0a8ceb->m_frame.f_lineno = 213;
        tmp_len_arg_2 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_3, tmp_args_element_value_2);
        if (tmp_len_arg_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_sub_expr_left_1);

            exception_lineno = 213;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_sub_expr_right_1 = BUILTIN_LEN(tstate, tmp_len_arg_2);
        Py_DECREF(tmp_len_arg_2);
        if (tmp_sub_expr_right_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_sub_expr_left_1);

            exception_lineno = 213;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_mult_expr_right_1 = BINARY_OPERATION_SUB_OBJECT_LONG_LONG(tmp_sub_expr_left_1, tmp_sub_expr_right_1);
        Py_DECREF(tmp_sub_expr_left_1);
        Py_DECREF(tmp_sub_expr_right_1);
        assert(!(tmp_mult_expr_right_1 == NULL));
        tmp_iadd_expr_right_1 = BINARY_OPERATION_MULT_OBJECT_UNICODE_LONG(tmp_mult_expr_left_1, tmp_mult_expr_right_1);
        Py_DECREF(tmp_mult_expr_right_1);
        assert(!(tmp_iadd_expr_right_1 == NULL));
        tmp_result = INPLACE_OPERATION_ADD_OBJECT_UNICODE(&tmp_iadd_expr_left_1, tmp_iadd_expr_right_1);
        Py_DECREF(tmp_iadd_expr_right_1);
        if (tmp_result == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 213;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_4 = tmp_iadd_expr_left_1;
        par_mark_line = tmp_assign_source_4;

    }
    {
        PyObject *tmp_assign_source_5;
        PyObject *tmp_list_arg_1;
        CHECK_OBJECT(par_mark_line);
        tmp_list_arg_1 = par_mark_line;
        tmp_assign_source_5 = MAKE_LIST(tstate, tmp_list_arg_1);
        if (tmp_assign_source_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 214;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = par_mark_line;
            assert(old != NULL);
            par_mark_line = tmp_assign_source_5;
            Py_DECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_6;
        tmp_assign_source_6 = Py_False;
        assert(var_marked == NULL);
        Py_INCREF(tmp_assign_source_6);
        var_marked = tmp_assign_source_6;
    }
    {
        PyObject *tmp_assign_source_7;
        PyObject *tmp_called_value_4;
        PyObject *tmp_args_element_value_3;
        if (Nuitka_Cell_GET(self->m_closure[1]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[27]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 217;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_4 = Nuitka_Cell_GET(self->m_closure[1]);
        CHECK_OBJECT(par_line);
        tmp_args_element_value_3 = par_line;
        frame_e1d27883b2455e4c949dff371c0a8ceb->m_frame.f_lineno = 217;
        tmp_assign_source_7 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_4, tmp_args_element_value_3);
        if (tmp_assign_source_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 217;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        assert(var_skip_amount == NULL);
        var_skip_amount = tmp_assign_source_7;
    }
    {
        nuitka_bool tmp_condition_result_1;
        int tmp_truth_name_1;
        if (Nuitka_Cell_GET(self->m_closure[7]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[95]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 219;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_truth_name_1 = CHECK_IF_TRUE(Nuitka_Cell_GET(self->m_closure[7]));
        if (tmp_truth_name_1 == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 219;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_1 = tmp_truth_name_1 == 0 ? NUITKA_BOOL_FALSE : NUITKA_BOOL_TRUE;
        if (tmp_condition_result_1 == NUITKA_BOOL_TRUE) {
            goto branch_yes_1;
        } else {
            goto branch_no_1;
        }
    }
    branch_yes_1:;
    {
        PyObject *tmp_assign_source_8;
        PyObject *tmp_iter_arg_1;
        if (Nuitka_Cell_GET(self->m_closure[7]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[95]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 220;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_iter_arg_1 = Nuitka_Cell_GET(self->m_closure[7]);
        tmp_assign_source_8 = MAKE_ITERATOR(tstate, tmp_iter_arg_1);
        if (tmp_assign_source_8 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 220;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        assert(tmp_for_loop_1__for_iterator == NULL);
        tmp_for_loop_1__for_iterator = tmp_assign_source_8;
    }
    // Tried code:
    loop_start_1:;
    {
        PyObject *tmp_next_source_1;
        PyObject *tmp_assign_source_9;
        CHECK_OBJECT(tmp_for_loop_1__for_iterator);
        tmp_next_source_1 = tmp_for_loop_1__for_iterator;
        tmp_assign_source_9 = ITERATOR_NEXT(tmp_next_source_1);
        if (tmp_assign_source_9 == NULL) {
            if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                goto loop_end_1;
            } else {

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                type_description_1 = "oooooooooccccccccccc";
                exception_lineno = 220;
                goto try_except_handler_2;
            }
        }

        {
            PyObject *old = tmp_for_loop_1__iter_value;
            tmp_for_loop_1__iter_value = tmp_assign_source_9;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_10;
        CHECK_OBJECT(tmp_for_loop_1__iter_value);
        tmp_assign_source_10 = tmp_for_loop_1__iter_value;
        {
            PyObject *old = var_item;
            var_item = tmp_assign_source_10;
            Py_INCREF(var_item);
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_11;
        PyObject *tmp_len_arg_3;
        CHECK_OBJECT(var_item);
        tmp_len_arg_3 = var_item;
        tmp_assign_source_11 = BUILTIN_LEN(tstate, tmp_len_arg_3);
        if (tmp_assign_source_11 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 221;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_2;
        }
        {
            PyObject *old = var_len_of_item;
            var_len_of_item = tmp_assign_source_11;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_12;
        PyObject *tmp_iter_arg_2;
        PyObject *tmp_xrange_low_1;
        PyObject *tmp_len_arg_4;
        if (par_line == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[96]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 222;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_2;
        }

        tmp_len_arg_4 = par_line;
        tmp_xrange_low_1 = BUILTIN_LEN(tstate, tmp_len_arg_4);
        if (tmp_xrange_low_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 222;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_2;
        }
        tmp_iter_arg_2 = BUILTIN_XRANGE1(tstate, tmp_xrange_low_1);
        Py_DECREF(tmp_xrange_low_1);
        if (tmp_iter_arg_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 222;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_2;
        }
        tmp_assign_source_12 = MAKE_ITERATOR(tstate, tmp_iter_arg_2);
        Py_DECREF(tmp_iter_arg_2);
        if (tmp_assign_source_12 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 222;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_2;
        }
        {
            PyObject *old = tmp_for_loop_2__for_iterator;
            tmp_for_loop_2__for_iterator = tmp_assign_source_12;
            Py_XDECREF(old);
        }

    }
    // Tried code:
    loop_start_2:;
    {
        PyObject *tmp_next_source_2;
        PyObject *tmp_assign_source_13;
        CHECK_OBJECT(tmp_for_loop_2__for_iterator);
        tmp_next_source_2 = tmp_for_loop_2__for_iterator;
        tmp_assign_source_13 = ITERATOR_NEXT(tmp_next_source_2);
        if (tmp_assign_source_13 == NULL) {
            if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                goto loop_end_2;
            } else {

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                type_description_1 = "oooooooooccccccccccc";
                exception_lineno = 222;
                goto try_except_handler_3;
            }
        }

        {
            PyObject *old = tmp_for_loop_2__iter_value;
            tmp_for_loop_2__iter_value = tmp_assign_source_13;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_14;
        CHECK_OBJECT(tmp_for_loop_2__iter_value);
        tmp_assign_source_14 = tmp_for_loop_2__iter_value;
        {
            PyObject *old = var_index;
            var_index = tmp_assign_source_14;
            Py_INCREF(var_index);
            Py_XDECREF(old);
        }

    }
    {
        nuitka_bool tmp_condition_result_2;
        PyObject *tmp_cmp_expr_left_1;
        PyObject *tmp_cmp_expr_right_1;
        CHECK_OBJECT(var_index);
        tmp_cmp_expr_left_1 = var_index;
        CHECK_OBJECT(var_skip_amount);
        tmp_cmp_expr_right_1 = var_skip_amount;
        tmp_condition_result_2 = RICH_COMPARE_LE_NBOOL_OBJECT_OBJECT(tmp_cmp_expr_left_1, tmp_cmp_expr_right_1);
        if (tmp_condition_result_2 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 223;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        if (tmp_condition_result_2 == NUITKA_BOOL_TRUE) {
            goto branch_yes_2;
        } else {
            goto branch_no_2;
        }
    }
    branch_yes_2:;
    goto loop_start_2;
    branch_no_2:;
    {
        nuitka_bool tmp_condition_result_3;
        PyObject *tmp_cmp_expr_left_2;
        PyObject *tmp_cmp_expr_right_2;
        PyObject *tmp_expression_value_2;
        PyObject *tmp_subscript_value_1;
        PyObject *tmp_start_value_1;
        PyObject *tmp_stop_value_1;
        PyObject *tmp_add_expr_left_1;
        PyObject *tmp_add_expr_right_1;
        PyObject *tmp_unicode_arg_1;
        if (par_line == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[96]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 224;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }

        tmp_expression_value_2 = par_line;
        CHECK_OBJECT(var_index);
        tmp_start_value_1 = var_index;
        CHECK_OBJECT(var_index);
        tmp_add_expr_left_1 = var_index;
        if (var_len_of_item == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[97]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 224;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }

        tmp_add_expr_right_1 = var_len_of_item;
        tmp_stop_value_1 = BINARY_OPERATION_ADD_OBJECT_OBJECT_LONG(tmp_add_expr_left_1, tmp_add_expr_right_1);
        if (tmp_stop_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 224;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        tmp_subscript_value_1 = MAKE_SLICE_OBJECT2(tmp_start_value_1, tmp_stop_value_1);
        Py_DECREF(tmp_stop_value_1);
        assert(!(tmp_subscript_value_1 == NULL));
        tmp_cmp_expr_left_2 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_2, tmp_subscript_value_1);
        Py_DECREF(tmp_subscript_value_1);
        if (tmp_cmp_expr_left_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 224;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        CHECK_OBJECT(var_item);
        tmp_unicode_arg_1 = var_item;
        tmp_cmp_expr_right_2 = BUILTIN_UNICODE1(tmp_unicode_arg_1);
        if (tmp_cmp_expr_right_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_cmp_expr_left_2);

            exception_lineno = 224;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        tmp_condition_result_3 = RICH_COMPARE_EQ_NBOOL_OBJECT_OBJECT(tmp_cmp_expr_left_2, tmp_cmp_expr_right_2);
        Py_DECREF(tmp_cmp_expr_left_2);
        Py_DECREF(tmp_cmp_expr_right_2);
        if (tmp_condition_result_3 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 224;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        if (tmp_condition_result_3 == NUITKA_BOOL_TRUE) {
            goto branch_yes_3;
        } else {
            goto branch_no_3;
        }
    }
    branch_yes_3:;
    {
        PyObject *tmp_assign_source_15;
        PyObject *tmp_add_expr_left_2;
        PyObject *tmp_add_expr_right_2;
        PyObject *tmp_add_expr_left_3;
        PyObject *tmp_add_expr_right_3;
        PyObject *tmp_expression_value_3;
        PyObject *tmp_subscript_value_2;
        PyObject *tmp_stop_value_2;
        PyObject *tmp_sub_expr_left_2;
        PyObject *tmp_sub_expr_right_2;
        PyObject *tmp_mult_expr_left_2;
        PyObject *tmp_mult_expr_right_2;
        PyObject *tmp_list_element_1;
        PyObject *tmp_string_concat_values_1;
        PyObject *tmp_tuple_element_1;
        PyObject *tmp_format_value_1;
        PyObject *tmp_format_spec_1;
        PyObject *tmp_expression_value_4;
        PyObject *tmp_subscript_value_3;
        PyObject *tmp_start_value_2;
        PyObject *tmp_add_expr_left_4;
        PyObject *tmp_add_expr_right_4;
        PyObject *tmp_sub_expr_left_3;
        PyObject *tmp_sub_expr_right_3;
        PyObject *tmp_stop_value_3;
        if (par_mark_line == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[98]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }

        tmp_expression_value_3 = par_mark_line;
        CHECK_OBJECT(var_index);
        tmp_sub_expr_left_2 = var_index;
        tmp_sub_expr_right_2 = mod_consts[51];
        tmp_stop_value_2 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_2, tmp_sub_expr_right_2);
        if (tmp_stop_value_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        tmp_subscript_value_2 = MAKE_SLICE_OBJECT1(tmp_stop_value_2);
        Py_DECREF(tmp_stop_value_2);
        assert(!(tmp_subscript_value_2 == NULL));
        tmp_add_expr_left_3 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_3, tmp_subscript_value_2);
        Py_DECREF(tmp_subscript_value_2);
        if (tmp_add_expr_left_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        if (Nuitka_Cell_GET(self->m_closure[0]) == NULL) {
            Py_DECREF(tmp_add_expr_left_3);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[49]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }

        tmp_format_value_1 = Nuitka_Cell_GET(self->m_closure[0]);
        tmp_format_spec_1 = mod_consts[44];
        tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_1, tmp_format_spec_1);
        if (tmp_tuple_element_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_3);

            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        tmp_string_concat_values_1 = MAKE_TUPLE_EMPTY(3);
        {
            PyObject *tmp_format_value_2;
            PyObject *tmp_format_spec_2;
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 0, tmp_tuple_element_1);
            tmp_tuple_element_1 = mod_consts[99];
            PyTuple_SET_ITEM0(tmp_string_concat_values_1, 1, tmp_tuple_element_1);
            if (Nuitka_Cell_GET(self->m_closure[9]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 226;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_1;
            }

            tmp_format_value_2 = Nuitka_Cell_GET(self->m_closure[9]);
            tmp_format_spec_2 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_2, tmp_format_spec_2);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 226;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 2, tmp_tuple_element_1);
        }
        goto tuple_build_noexception_1;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_1:;
        Py_DECREF(tmp_add_expr_left_3);
        Py_DECREF(tmp_string_concat_values_1);
        goto try_except_handler_3;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_1:;
        tmp_list_element_1 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_1);
        Py_DECREF(tmp_string_concat_values_1);
        if (tmp_list_element_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_3);

            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        tmp_mult_expr_left_2 = MAKE_LIST_EMPTY(1);
        PyList_SET_ITEM(tmp_mult_expr_left_2, 0, tmp_list_element_1);
        if (var_len_of_item == NULL) {
            Py_DECREF(tmp_add_expr_left_3);
            Py_DECREF(tmp_mult_expr_left_2);
            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[97]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }

        tmp_mult_expr_right_2 = var_len_of_item;
        tmp_add_expr_right_3 = BINARY_OPERATION_MULT_OBJECT_LIST_LONG(tmp_mult_expr_left_2, tmp_mult_expr_right_2);
        Py_DECREF(tmp_mult_expr_left_2);
        assert(!(tmp_add_expr_right_3 == NULL));
        tmp_add_expr_left_2 = BINARY_OPERATION_ADD_OBJECT_OBJECT_LIST(tmp_add_expr_left_3, tmp_add_expr_right_3);
        Py_DECREF(tmp_add_expr_left_3);
        Py_DECREF(tmp_add_expr_right_3);
        if (tmp_add_expr_left_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        if (par_mark_line == NULL) {
            Py_DECREF(tmp_add_expr_left_2);
            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[98]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }

        tmp_expression_value_4 = par_mark_line;
        CHECK_OBJECT(var_index);
        tmp_sub_expr_left_3 = var_index;
        tmp_sub_expr_right_3 = mod_consts[51];
        tmp_add_expr_left_4 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_3, tmp_sub_expr_right_3);
        if (tmp_add_expr_left_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_2);

            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        if (var_len_of_item == NULL) {
            Py_DECREF(tmp_add_expr_left_2);
            Py_DECREF(tmp_add_expr_left_4);
            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[97]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }

        tmp_add_expr_right_4 = var_len_of_item;
        tmp_start_value_2 = BINARY_OPERATION_ADD_OBJECT_OBJECT_LONG(tmp_add_expr_left_4, tmp_add_expr_right_4);
        Py_DECREF(tmp_add_expr_left_4);
        if (tmp_start_value_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_2);

            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        tmp_stop_value_3 = Py_None;
        tmp_subscript_value_3 = MAKE_SLICE_OBJECT2(tmp_start_value_2, tmp_stop_value_3);
        Py_DECREF(tmp_start_value_2);
        assert(!(tmp_subscript_value_3 == NULL));
        tmp_add_expr_right_2 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_4, tmp_subscript_value_3);
        Py_DECREF(tmp_subscript_value_3);
        if (tmp_add_expr_right_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_2);

            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        tmp_assign_source_15 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_2, tmp_add_expr_right_2);
        Py_DECREF(tmp_add_expr_left_2);
        Py_DECREF(tmp_add_expr_right_2);
        if (tmp_assign_source_15 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 226;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_3;
        }
        {
            PyObject *old = par_mark_line;
            par_mark_line = tmp_assign_source_15;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_16;
        tmp_assign_source_16 = Py_True;
        {
            PyObject *old = var_marked;
            var_marked = tmp_assign_source_16;
            Py_INCREF(var_marked);
            Py_XDECREF(old);
        }

    }
    branch_no_3:;
    if (CONSIDER_THREADING(tstate) == false) {
        assert(HAS_ERROR_OCCURRED(tstate));

        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


        exception_lineno = 222;
        type_description_1 = "oooooooooccccccccccc";
        goto try_except_handler_3;
    }
    goto loop_start_2;
    loop_end_2:;
    goto try_end_1;
    // Exception handler code:
    try_except_handler_3:;
    exception_keeper_type_1 = exception_type;
    exception_keeper_value_1 = exception_value;
    exception_keeper_tb_1 = exception_tb;
    exception_keeper_lineno_1 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(tmp_for_loop_2__iter_value);
    tmp_for_loop_2__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_2__for_iterator);
    Py_DECREF(tmp_for_loop_2__for_iterator);
    tmp_for_loop_2__for_iterator = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_1;
    exception_value = exception_keeper_value_1;
    exception_tb = exception_keeper_tb_1;
    exception_lineno = exception_keeper_lineno_1;

    goto try_except_handler_2;
    // End of try:
    try_end_1:;
    Py_XDECREF(tmp_for_loop_2__iter_value);
    tmp_for_loop_2__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_2__for_iterator);
    Py_DECREF(tmp_for_loop_2__for_iterator);
    tmp_for_loop_2__for_iterator = NULL;
    if (CONSIDER_THREADING(tstate) == false) {
        assert(HAS_ERROR_OCCURRED(tstate));

        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


        exception_lineno = 220;
        type_description_1 = "oooooooooccccccccccc";
        goto try_except_handler_2;
    }
    goto loop_start_1;
    loop_end_1:;
    goto try_end_2;
    // Exception handler code:
    try_except_handler_2:;
    exception_keeper_type_2 = exception_type;
    exception_keeper_value_2 = exception_value;
    exception_keeper_tb_2 = exception_tb;
    exception_keeper_lineno_2 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(tmp_for_loop_1__iter_value);
    tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_1__for_iterator);
    Py_DECREF(tmp_for_loop_1__for_iterator);
    tmp_for_loop_1__for_iterator = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_2;
    exception_value = exception_keeper_value_2;
    exception_tb = exception_keeper_tb_2;
    exception_lineno = exception_keeper_lineno_2;

    goto frame_exception_exit_1;
    // End of try:
    try_end_2:;
    Py_XDECREF(tmp_for_loop_1__iter_value);
    tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_1__for_iterator);
    Py_DECREF(tmp_for_loop_1__for_iterator);
    tmp_for_loop_1__for_iterator = NULL;
    {
        PyObject *tmp_assign_source_17;
        PyObject *tmp_list_arg_2;
        if (par_line == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[96]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 228;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_list_arg_2 = par_line;
        tmp_assign_source_17 = MAKE_LIST(tstate, tmp_list_arg_2);
        if (tmp_assign_source_17 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 228;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = par_line;
            par_line = tmp_assign_source_17;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_18;
        PyObject *tmp_iter_arg_3;
        if (Nuitka_Cell_GET(self->m_closure[7]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[95]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 229;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_iter_arg_3 = Nuitka_Cell_GET(self->m_closure[7]);
        tmp_assign_source_18 = MAKE_ITERATOR(tstate, tmp_iter_arg_3);
        if (tmp_assign_source_18 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 229;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        assert(tmp_for_loop_3__for_iterator == NULL);
        tmp_for_loop_3__for_iterator = tmp_assign_source_18;
    }
    // Tried code:
    loop_start_3:;
    {
        PyObject *tmp_next_source_3;
        PyObject *tmp_assign_source_19;
        CHECK_OBJECT(tmp_for_loop_3__for_iterator);
        tmp_next_source_3 = tmp_for_loop_3__for_iterator;
        tmp_assign_source_19 = ITERATOR_NEXT(tmp_next_source_3);
        if (tmp_assign_source_19 == NULL) {
            if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                goto loop_end_3;
            } else {

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                type_description_1 = "oooooooooccccccccccc";
                exception_lineno = 229;
                goto try_except_handler_4;
            }
        }

        {
            PyObject *old = tmp_for_loop_3__iter_value;
            tmp_for_loop_3__iter_value = tmp_assign_source_19;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_20;
        CHECK_OBJECT(tmp_for_loop_3__iter_value);
        tmp_assign_source_20 = tmp_for_loop_3__iter_value;
        {
            PyObject *old = var_item;
            var_item = tmp_assign_source_20;
            Py_INCREF(var_item);
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_21;
        PyObject *tmp_len_arg_5;
        CHECK_OBJECT(var_item);
        tmp_len_arg_5 = var_item;
        tmp_assign_source_21 = BUILTIN_LEN(tstate, tmp_len_arg_5);
        if (tmp_assign_source_21 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 230;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_4;
        }
        {
            PyObject *old = var_len_of_item;
            var_len_of_item = tmp_assign_source_21;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_22;
        PyObject *tmp_iter_arg_4;
        PyObject *tmp_xrange_low_2;
        PyObject *tmp_len_arg_6;
        if (par_line == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[96]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 231;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_4;
        }

        tmp_len_arg_6 = par_line;
        tmp_xrange_low_2 = BUILTIN_LEN(tstate, tmp_len_arg_6);
        if (tmp_xrange_low_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 231;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_4;
        }
        tmp_iter_arg_4 = BUILTIN_XRANGE1(tstate, tmp_xrange_low_2);
        Py_DECREF(tmp_xrange_low_2);
        if (tmp_iter_arg_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 231;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_4;
        }
        tmp_assign_source_22 = MAKE_ITERATOR(tstate, tmp_iter_arg_4);
        Py_DECREF(tmp_iter_arg_4);
        if (tmp_assign_source_22 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 231;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_4;
        }
        {
            PyObject *old = tmp_for_loop_4__for_iterator;
            tmp_for_loop_4__for_iterator = tmp_assign_source_22;
            Py_XDECREF(old);
        }

    }
    // Tried code:
    loop_start_4:;
    {
        PyObject *tmp_next_source_4;
        PyObject *tmp_assign_source_23;
        CHECK_OBJECT(tmp_for_loop_4__for_iterator);
        tmp_next_source_4 = tmp_for_loop_4__for_iterator;
        tmp_assign_source_23 = ITERATOR_NEXT(tmp_next_source_4);
        if (tmp_assign_source_23 == NULL) {
            if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                goto loop_end_4;
            } else {

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                type_description_1 = "oooooooooccccccccccc";
                exception_lineno = 231;
                goto try_except_handler_5;
            }
        }

        {
            PyObject *old = tmp_for_loop_4__iter_value;
            tmp_for_loop_4__iter_value = tmp_assign_source_23;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_24;
        CHECK_OBJECT(tmp_for_loop_4__iter_value);
        tmp_assign_source_24 = tmp_for_loop_4__iter_value;
        {
            PyObject *old = var_index;
            var_index = tmp_assign_source_24;
            Py_INCREF(var_index);
            Py_XDECREF(old);
        }

    }
    {
        nuitka_bool tmp_condition_result_4;
        PyObject *tmp_cmp_expr_left_3;
        PyObject *tmp_cmp_expr_right_3;
        CHECK_OBJECT(var_index);
        tmp_cmp_expr_left_3 = var_index;
        CHECK_OBJECT(var_skip_amount);
        tmp_cmp_expr_right_3 = var_skip_amount;
        tmp_condition_result_4 = RICH_COMPARE_LE_NBOOL_OBJECT_OBJECT(tmp_cmp_expr_left_3, tmp_cmp_expr_right_3);
        if (tmp_condition_result_4 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 232;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }
        if (tmp_condition_result_4 == NUITKA_BOOL_TRUE) {
            goto branch_yes_4;
        } else {
            goto branch_no_4;
        }
    }
    branch_yes_4:;
    goto loop_start_4;
    branch_no_4:;
    {
        nuitka_bool tmp_condition_result_5;
        PyObject *tmp_cmp_expr_left_4;
        PyObject *tmp_cmp_expr_right_4;
        PyObject *tmp_str_arg_value_1;
        PyObject *tmp_iterable_value_1;
        PyObject *tmp_expression_value_5;
        PyObject *tmp_subscript_value_4;
        PyObject *tmp_start_value_3;
        PyObject *tmp_stop_value_4;
        PyObject *tmp_add_expr_left_5;
        PyObject *tmp_add_expr_right_5;
        tmp_str_arg_value_1 = mod_consts[44];
        if (par_line == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[96]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 233;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }

        tmp_expression_value_5 = par_line;
        CHECK_OBJECT(var_index);
        tmp_start_value_3 = var_index;
        CHECK_OBJECT(var_index);
        tmp_add_expr_left_5 = var_index;
        if (var_len_of_item == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[97]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 233;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }

        tmp_add_expr_right_5 = var_len_of_item;
        tmp_stop_value_4 = BINARY_OPERATION_ADD_OBJECT_OBJECT_LONG(tmp_add_expr_left_5, tmp_add_expr_right_5);
        if (tmp_stop_value_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 233;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }
        tmp_subscript_value_4 = MAKE_SLICE_OBJECT2(tmp_start_value_3, tmp_stop_value_4);
        Py_DECREF(tmp_stop_value_4);
        assert(!(tmp_subscript_value_4 == NULL));
        tmp_iterable_value_1 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_5, tmp_subscript_value_4);
        Py_DECREF(tmp_subscript_value_4);
        if (tmp_iterable_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 233;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }
        tmp_cmp_expr_left_4 = UNICODE_JOIN(tstate, tmp_str_arg_value_1, tmp_iterable_value_1);
        Py_DECREF(tmp_iterable_value_1);
        if (tmp_cmp_expr_left_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 233;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }
        CHECK_OBJECT(var_item);
        tmp_cmp_expr_right_4 = var_item;
        tmp_condition_result_5 = RICH_COMPARE_EQ_NBOOL_UNICODE_OBJECT(tmp_cmp_expr_left_4, tmp_cmp_expr_right_4);
        Py_DECREF(tmp_cmp_expr_left_4);
        if (tmp_condition_result_5 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 233;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }
        if (tmp_condition_result_5 == NUITKA_BOOL_TRUE) {
            goto branch_yes_5;
        } else {
            goto branch_no_5;
        }
    }
    branch_yes_5:;
    {
        PyObject *tmp_ass_subvalue_1;
        PyObject *tmp_list_element_2;
        PyObject *tmp_string_concat_values_2;
        PyObject *tmp_tuple_element_2;
        PyObject *tmp_format_value_3;
        PyObject *tmp_format_spec_3;
        PyObject *tmp_ass_subscribed_1;
        PyObject *tmp_ass_subscript_1;
        PyObject *tmp_start_value_4;
        PyObject *tmp_stop_value_5;
        PyObject *tmp_add_expr_left_6;
        PyObject *tmp_add_expr_right_6;
        if (Nuitka_Cell_GET(self->m_closure[0]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[49]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 234;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }

        tmp_format_value_3 = Nuitka_Cell_GET(self->m_closure[0]);
        tmp_format_spec_3 = mod_consts[44];
        tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_3, tmp_format_spec_3);
        if (tmp_tuple_element_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 234;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }
        tmp_string_concat_values_2 = MAKE_TUPLE_EMPTY(3);
        {
            PyObject *tmp_format_value_4;
            PyObject *tmp_format_spec_4;
            PyObject *tmp_format_value_5;
            PyObject *tmp_format_spec_5;
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 0, tmp_tuple_element_2);
            CHECK_OBJECT(var_item);
            tmp_format_value_4 = var_item;
            tmp_format_spec_4 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_4, tmp_format_spec_4);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 234;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 1, tmp_tuple_element_2);
            if (Nuitka_Cell_GET(self->m_closure[9]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 234;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_2;
            }

            tmp_format_value_5 = Nuitka_Cell_GET(self->m_closure[9]);
            tmp_format_spec_5 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_5, tmp_format_spec_5);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 234;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 2, tmp_tuple_element_2);
        }
        goto tuple_build_noexception_2;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_2:;
        Py_DECREF(tmp_string_concat_values_2);
        goto try_except_handler_5;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_2:;
        tmp_list_element_2 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_2);
        Py_DECREF(tmp_string_concat_values_2);
        if (tmp_list_element_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 234;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }
        tmp_ass_subvalue_1 = MAKE_LIST_EMPTY(1);
        PyList_SET_ITEM(tmp_ass_subvalue_1, 0, tmp_list_element_2);
        if (par_line == NULL) {
            Py_DECREF(tmp_ass_subvalue_1);
            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[96]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 234;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }

        tmp_ass_subscribed_1 = par_line;
        CHECK_OBJECT(var_index);
        tmp_start_value_4 = var_index;
        CHECK_OBJECT(var_index);
        tmp_add_expr_left_6 = var_index;
        if (var_len_of_item == NULL) {
            Py_DECREF(tmp_ass_subvalue_1);
            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[97]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 234;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }

        tmp_add_expr_right_6 = var_len_of_item;
        tmp_stop_value_5 = BINARY_OPERATION_ADD_OBJECT_OBJECT_LONG(tmp_add_expr_left_6, tmp_add_expr_right_6);
        if (tmp_stop_value_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_ass_subvalue_1);

            exception_lineno = 234;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }
        tmp_ass_subscript_1 = MAKE_SLICE_OBJECT2(tmp_start_value_4, tmp_stop_value_5);
        Py_DECREF(tmp_stop_value_5);
        assert(!(tmp_ass_subscript_1 == NULL));
        tmp_result = SET_SUBSCRIPT(tstate, tmp_ass_subscribed_1, tmp_ass_subscript_1, tmp_ass_subvalue_1);
        Py_DECREF(tmp_ass_subscript_1);
        Py_DECREF(tmp_ass_subvalue_1);
        if (tmp_result == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 234;
            type_description_1 = "oooooooooccccccccccc";
            goto try_except_handler_5;
        }
    }
    goto loop_end_4;
    branch_no_5:;
    if (CONSIDER_THREADING(tstate) == false) {
        assert(HAS_ERROR_OCCURRED(tstate));

        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


        exception_lineno = 231;
        type_description_1 = "oooooooooccccccccccc";
        goto try_except_handler_5;
    }
    goto loop_start_4;
    loop_end_4:;
    goto try_end_3;
    // Exception handler code:
    try_except_handler_5:;
    exception_keeper_type_3 = exception_type;
    exception_keeper_value_3 = exception_value;
    exception_keeper_tb_3 = exception_tb;
    exception_keeper_lineno_3 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(tmp_for_loop_4__iter_value);
    tmp_for_loop_4__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_4__for_iterator);
    Py_DECREF(tmp_for_loop_4__for_iterator);
    tmp_for_loop_4__for_iterator = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_3;
    exception_value = exception_keeper_value_3;
    exception_tb = exception_keeper_tb_3;
    exception_lineno = exception_keeper_lineno_3;

    goto try_except_handler_4;
    // End of try:
    try_end_3:;
    Py_XDECREF(tmp_for_loop_4__iter_value);
    tmp_for_loop_4__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_4__for_iterator);
    Py_DECREF(tmp_for_loop_4__for_iterator);
    tmp_for_loop_4__for_iterator = NULL;
    if (CONSIDER_THREADING(tstate) == false) {
        assert(HAS_ERROR_OCCURRED(tstate));

        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


        exception_lineno = 229;
        type_description_1 = "oooooooooccccccccccc";
        goto try_except_handler_4;
    }
    goto loop_start_3;
    loop_end_3:;
    goto try_end_4;
    // Exception handler code:
    try_except_handler_4:;
    exception_keeper_type_4 = exception_type;
    exception_keeper_value_4 = exception_value;
    exception_keeper_tb_4 = exception_tb;
    exception_keeper_lineno_4 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(tmp_for_loop_3__iter_value);
    tmp_for_loop_3__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_3__for_iterator);
    Py_DECREF(tmp_for_loop_3__for_iterator);
    tmp_for_loop_3__for_iterator = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_4;
    exception_value = exception_keeper_value_4;
    exception_tb = exception_keeper_tb_4;
    exception_lineno = exception_keeper_lineno_4;

    goto frame_exception_exit_1;
    // End of try:
    try_end_4:;
    Py_XDECREF(tmp_for_loop_3__iter_value);
    tmp_for_loop_3__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_3__for_iterator);
    Py_DECREF(tmp_for_loop_3__for_iterator);
    tmp_for_loop_3__for_iterator = NULL;
    {
        PyObject *tmp_assign_source_25;
        PyObject *tmp_str_arg_value_2;
        PyObject *tmp_iterable_value_2;
        tmp_str_arg_value_2 = mod_consts[44];
        if (par_line == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[96]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 236;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_iterable_value_2 = par_line;
        tmp_assign_source_25 = UNICODE_JOIN(tstate, tmp_str_arg_value_2, tmp_iterable_value_2);
        if (tmp_assign_source_25 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 236;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = var_output_line;
            assert(old != NULL);
            var_output_line = tmp_assign_source_25;
            Py_DECREF(old);
        }

    }
    branch_no_1:;
    {
        bool tmp_condition_result_6;
        PyObject *tmp_operand_value_1;
        if (var_marked == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[100]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 238;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_operand_value_1 = var_marked;
        tmp_res = CHECK_IF_TRUE(tmp_operand_value_1);
        if (tmp_res == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 238;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_6 = (tmp_res == 0) ? true : false;
        if (tmp_condition_result_6 != false) {
            goto branch_yes_6;
        } else {
            goto branch_no_6;
        }
    }
    branch_yes_6:;
    {
        PyObject *tmp_assign_source_26;
        if (par_line == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[96]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 239;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_assign_source_26 = par_line;
        {
            PyObject *old = var_output_line;
            assert(old != NULL);
            var_output_line = tmp_assign_source_26;
            Py_INCREF(var_output_line);
            Py_DECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_27;
        PyObject *tmp_list_arg_3;
        PyObject *tmp_add_expr_left_7;
        PyObject *tmp_add_expr_right_7;
        PyObject *tmp_str_arg_value_3;
        PyObject *tmp_str_arg_value_4;
        PyObject *tmp_iterable_value_3;
        PyObject *tmp_expression_value_6;
        PyObject *tmp_subscript_value_5;
        tmp_str_arg_value_4 = mod_consts[44];
        if (par_mark_line == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[98]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 240;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_expression_value_6 = par_mark_line;
        tmp_subscript_value_5 = mod_consts[101];
        tmp_iterable_value_3 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_6, tmp_subscript_value_5);
        if (tmp_iterable_value_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 240;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_str_arg_value_3 = UNICODE_JOIN(tstate, tmp_str_arg_value_4, tmp_iterable_value_3);
        Py_DECREF(tmp_iterable_value_3);
        if (tmp_str_arg_value_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 240;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_left_7 = UNICODE_RSTRIP1(tstate, tmp_str_arg_value_3);
        Py_DECREF(tmp_str_arg_value_3);
        if (tmp_add_expr_left_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 240;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_right_7 = mod_consts[48];
        tmp_list_arg_3 = BINARY_OPERATION_ADD_OBJECT_UNICODE_UNICODE(tmp_add_expr_left_7, tmp_add_expr_right_7);
        Py_DECREF(tmp_add_expr_left_7);
        assert(!(tmp_list_arg_3 == NULL));
        tmp_assign_source_27 = MAKE_LIST(tstate, tmp_list_arg_3);
        Py_DECREF(tmp_list_arg_3);
        if (tmp_assign_source_27 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 240;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = par_mark_line;
            par_mark_line = tmp_assign_source_27;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_28;
        PyObject *tmp_iadd_expr_left_2;
        PyObject *tmp_iadd_expr_right_2;
        PyObject *tmp_add_expr_left_8;
        PyObject *tmp_add_expr_right_8;
        PyObject *tmp_add_expr_left_9;
        PyObject *tmp_add_expr_right_9;
        PyObject *tmp_mult_expr_left_3;
        PyObject *tmp_mult_expr_right_3;
        PyObject *tmp_called_value_5;
        PyObject *tmp_args_element_value_4;
        PyObject *tmp_mult_expr_left_4;
        PyObject *tmp_mult_expr_right_4;
        PyObject *tmp_list_element_3;
        PyObject *tmp_string_concat_values_3;
        PyObject *tmp_tuple_element_3;
        PyObject *tmp_format_value_6;
        PyObject *tmp_format_spec_6;
        PyObject *tmp_sub_expr_left_4;
        PyObject *tmp_sub_expr_right_4;
        PyObject *tmp_len_arg_7;
        PyObject *tmp_called_value_6;
        PyObject *tmp_args_element_value_5;
        PyObject *tmp_expression_value_7;
        PyObject *tmp_subscript_value_6;
        nuitka_bool tmp_condition_result_7;
        int tmp_truth_name_2;
        CHECK_OBJECT(par_mark_line);
        tmp_iadd_expr_left_2 = par_mark_line;
        tmp_add_expr_left_9 = MAKE_LIST1(mod_consts[102]);
        tmp_mult_expr_left_3 = MAKE_LIST1(mod_consts[48]);
        if (Nuitka_Cell_GET(self->m_closure[3]) == NULL) {
            Py_DECREF(tmp_add_expr_left_9);
            Py_DECREF(tmp_mult_expr_left_3);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[29]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_5 = Nuitka_Cell_GET(self->m_closure[3]);
        CHECK_OBJECT(var_output_line);
        tmp_args_element_value_4 = var_output_line;
        frame_e1d27883b2455e4c949dff371c0a8ceb->m_frame.f_lineno = 241;
        tmp_mult_expr_right_3 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_5, tmp_args_element_value_4);
        if (tmp_mult_expr_right_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_9);
            Py_DECREF(tmp_mult_expr_left_3);

            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_right_9 = BINARY_OPERATION_MULT_OBJECT_LIST_OBJECT(tmp_mult_expr_left_3, tmp_mult_expr_right_3);
        Py_DECREF(tmp_mult_expr_left_3);
        Py_DECREF(tmp_mult_expr_right_3);
        if (tmp_add_expr_right_9 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_9);

            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_left_8 = BINARY_OPERATION_ADD_OBJECT_LIST_OBJECT(tmp_add_expr_left_9, tmp_add_expr_right_9);
        Py_DECREF(tmp_add_expr_left_9);
        Py_DECREF(tmp_add_expr_right_9);
        if (tmp_add_expr_left_8 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        if (Nuitka_Cell_GET(self->m_closure[8]) == NULL) {
            Py_DECREF(tmp_add_expr_left_8);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_format_value_6 = Nuitka_Cell_GET(self->m_closure[8]);
        tmp_format_spec_6 = mod_consts[44];
        tmp_tuple_element_3 = BUILTIN_FORMAT(tstate, tmp_format_value_6, tmp_format_spec_6);
        if (tmp_tuple_element_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_8);

            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_string_concat_values_3 = MAKE_TUPLE_EMPTY(3);
        {
            PyObject *tmp_format_value_7;
            PyObject *tmp_format_spec_7;
            PyTuple_SET_ITEM(tmp_string_concat_values_3, 0, tmp_tuple_element_3);
            tmp_tuple_element_3 = mod_consts[62];
            PyTuple_SET_ITEM0(tmp_string_concat_values_3, 1, tmp_tuple_element_3);
            if (Nuitka_Cell_GET(self->m_closure[9]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 241;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_3;
            }

            tmp_format_value_7 = Nuitka_Cell_GET(self->m_closure[9]);
            tmp_format_spec_7 = mod_consts[44];
            tmp_tuple_element_3 = BUILTIN_FORMAT(tstate, tmp_format_value_7, tmp_format_spec_7);
            if (tmp_tuple_element_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 241;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_3;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_3, 2, tmp_tuple_element_3);
        }
        goto tuple_build_noexception_3;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_3:;
        Py_DECREF(tmp_add_expr_left_8);
        Py_DECREF(tmp_string_concat_values_3);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_3:;
        tmp_list_element_3 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_3);
        Py_DECREF(tmp_string_concat_values_3);
        if (tmp_list_element_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_8);

            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_mult_expr_left_4 = MAKE_LIST_EMPTY(1);
        PyList_SET_ITEM(tmp_mult_expr_left_4, 0, tmp_list_element_3);
        if (Nuitka_Cell_GET(self->m_closure[5]) == NULL) {
            Py_DECREF(tmp_add_expr_left_8);
            Py_DECREF(tmp_mult_expr_left_4);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[32]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_6 = Nuitka_Cell_GET(self->m_closure[5]);
        if (Nuitka_Cell_GET(self->m_closure[6]) == NULL) {
            Py_DECREF(tmp_add_expr_left_8);
            Py_DECREF(tmp_mult_expr_left_4);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[103]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_expression_value_7 = Nuitka_Cell_GET(self->m_closure[6]);
        tmp_subscript_value_6 = mod_consts[59];
        tmp_args_element_value_5 = LOOKUP_SUBSCRIPT_CONST(tstate, tmp_expression_value_7, tmp_subscript_value_6, -1);
        if (tmp_args_element_value_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_8);
            Py_DECREF(tmp_mult_expr_left_4);

            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        frame_e1d27883b2455e4c949dff371c0a8ceb->m_frame.f_lineno = 241;
        tmp_len_arg_7 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_6, tmp_args_element_value_5);
        Py_DECREF(tmp_args_element_value_5);
        if (tmp_len_arg_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_8);
            Py_DECREF(tmp_mult_expr_left_4);

            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_sub_expr_left_4 = BUILTIN_LEN(tstate, tmp_len_arg_7);
        Py_DECREF(tmp_len_arg_7);
        if (tmp_sub_expr_left_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_8);
            Py_DECREF(tmp_mult_expr_left_4);

            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        if (Nuitka_Cell_GET(self->m_closure[4]) == NULL) {
            Py_DECREF(tmp_add_expr_left_8);
            Py_DECREF(tmp_mult_expr_left_4);
            Py_DECREF(tmp_sub_expr_left_4);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[93]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_truth_name_2 = CHECK_IF_TRUE(Nuitka_Cell_GET(self->m_closure[4]));
        if (tmp_truth_name_2 == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_8);
            Py_DECREF(tmp_mult_expr_left_4);
            Py_DECREF(tmp_sub_expr_left_4);

            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_7 = tmp_truth_name_2 == 0 ? NUITKA_BOOL_FALSE : NUITKA_BOOL_TRUE;
        if (tmp_condition_result_7 == NUITKA_BOOL_TRUE) {
            goto condexpr_true_1;
        } else {
            goto condexpr_false_1;
        }
        condexpr_true_1:;
        tmp_sub_expr_right_4 = mod_consts[56];
        goto condexpr_end_1;
        condexpr_false_1:;
        tmp_sub_expr_right_4 = mod_consts[51];
        condexpr_end_1:;
        tmp_mult_expr_right_4 = BINARY_OPERATION_SUB_OBJECT_LONG_LONG(tmp_sub_expr_left_4, tmp_sub_expr_right_4);
        Py_DECREF(tmp_sub_expr_left_4);
        assert(!(tmp_mult_expr_right_4 == NULL));
        tmp_add_expr_right_8 = BINARY_OPERATION_MULT_OBJECT_LIST_LONG(tmp_mult_expr_left_4, tmp_mult_expr_right_4);
        Py_DECREF(tmp_mult_expr_left_4);
        Py_DECREF(tmp_mult_expr_right_4);
        assert(!(tmp_add_expr_right_8 == NULL));
        tmp_iadd_expr_right_2 = BINARY_OPERATION_ADD_OBJECT_OBJECT_LIST(tmp_add_expr_left_8, tmp_add_expr_right_8);
        Py_DECREF(tmp_add_expr_left_8);
        Py_DECREF(tmp_add_expr_right_8);
        if (tmp_iadd_expr_right_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_result = INPLACE_OPERATION_ADD_LIST_OBJECT(&tmp_iadd_expr_left_2, tmp_iadd_expr_right_2);
        Py_DECREF(tmp_iadd_expr_right_2);
        if (tmp_result == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 241;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_28 = tmp_iadd_expr_left_2;
        par_mark_line = tmp_assign_source_28;

    }
    {
        nuitka_bool tmp_condition_result_8;
        PyObject *tmp_cmp_expr_left_5;
        PyObject *tmp_cmp_expr_right_5;
        PyObject *tmp_len_arg_8;
        CHECK_OBJECT(par_mark_line);
        tmp_len_arg_8 = par_mark_line;
        tmp_cmp_expr_left_5 = BUILTIN_LEN(tstate, tmp_len_arg_8);
        if (tmp_cmp_expr_left_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 242;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_cmp_expr_right_5 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

        if (unlikely(tmp_cmp_expr_right_5 == NULL)) {
            tmp_cmp_expr_right_5 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
        }

        if (tmp_cmp_expr_right_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_cmp_expr_left_5);

            exception_lineno = 242;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_8 = RICH_COMPARE_GT_NBOOL_LONG_OBJECT(tmp_cmp_expr_left_5, tmp_cmp_expr_right_5);
        Py_DECREF(tmp_cmp_expr_left_5);
        if (tmp_condition_result_8 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 242;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        if (tmp_condition_result_8 == NUITKA_BOOL_TRUE) {
            goto branch_yes_7;
        } else {
            goto branch_no_7;
        }
    }
    branch_yes_7:;
    {
        PyObject *tmp_assign_source_29;
        PyObject *tmp_add_expr_left_10;
        PyObject *tmp_add_expr_right_10;
        PyObject *tmp_add_expr_left_11;
        PyObject *tmp_add_expr_right_11;
        PyObject *tmp_expression_value_8;
        PyObject *tmp_subscript_value_7;
        PyObject *tmp_stop_value_6;
        PyObject *tmp_sub_expr_left_5;
        PyObject *tmp_sub_expr_right_5;
        PyObject *tmp_list_element_4;
        PyObject *tmp_string_concat_values_4;
        PyObject *tmp_tuple_element_4;
        PyObject *tmp_format_value_8;
        PyObject *tmp_format_spec_8;
        CHECK_OBJECT(par_mark_line);
        tmp_expression_value_8 = par_mark_line;
        tmp_sub_expr_left_5 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

        if (unlikely(tmp_sub_expr_left_5 == NULL)) {
            tmp_sub_expr_left_5 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
        }

        if (tmp_sub_expr_left_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 243;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_sub_expr_right_5 = mod_consts[52];
        tmp_stop_value_6 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_5, tmp_sub_expr_right_5);
        if (tmp_stop_value_6 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 243;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_subscript_value_7 = MAKE_SLICE_OBJECT1(tmp_stop_value_6);
        Py_DECREF(tmp_stop_value_6);
        assert(!(tmp_subscript_value_7 == NULL));
        tmp_add_expr_left_11 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_8, tmp_subscript_value_7);
        Py_DECREF(tmp_subscript_value_7);
        if (tmp_add_expr_left_11 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 243;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_right_11 = MAKE_LIST1(mod_consts[48]);
        tmp_add_expr_left_10 = BINARY_OPERATION_ADD_OBJECT_OBJECT_LIST(tmp_add_expr_left_11, tmp_add_expr_right_11);
        Py_DECREF(tmp_add_expr_left_11);
        Py_DECREF(tmp_add_expr_right_11);
        if (tmp_add_expr_left_10 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 243;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        if (Nuitka_Cell_GET(self->m_closure[8]) == NULL) {
            Py_DECREF(tmp_add_expr_left_10);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 243;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_format_value_8 = Nuitka_Cell_GET(self->m_closure[8]);
        tmp_format_spec_8 = mod_consts[44];
        tmp_tuple_element_4 = BUILTIN_FORMAT(tstate, tmp_format_value_8, tmp_format_spec_8);
        if (tmp_tuple_element_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_10);

            exception_lineno = 243;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_string_concat_values_4 = MAKE_TUPLE_EMPTY(3);
        {
            PyObject *tmp_format_value_9;
            PyObject *tmp_expression_value_9;
            PyObject *tmp_subscript_value_8;
            PyObject *tmp_format_spec_9;
            PyObject *tmp_format_value_10;
            PyObject *tmp_format_spec_10;
            PyTuple_SET_ITEM(tmp_string_concat_values_4, 0, tmp_tuple_element_4);
            if (Nuitka_Cell_GET(self->m_closure[2]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[104]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 243;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_4;
            }

            tmp_expression_value_9 = Nuitka_Cell_GET(self->m_closure[2]);
            tmp_subscript_value_8 = mod_consts[64];
            tmp_format_value_9 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_9, tmp_subscript_value_8);
            if (tmp_format_value_9 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 243;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_4;
            }
            tmp_format_spec_9 = mod_consts[44];
            tmp_tuple_element_4 = BUILTIN_FORMAT(tstate, tmp_format_value_9, tmp_format_spec_9);
            Py_DECREF(tmp_format_value_9);
            if (tmp_tuple_element_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 243;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_4;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_4, 1, tmp_tuple_element_4);
            if (Nuitka_Cell_GET(self->m_closure[9]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 243;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_4;
            }

            tmp_format_value_10 = Nuitka_Cell_GET(self->m_closure[9]);
            tmp_format_spec_10 = mod_consts[44];
            tmp_tuple_element_4 = BUILTIN_FORMAT(tstate, tmp_format_value_10, tmp_format_spec_10);
            if (tmp_tuple_element_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 243;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_4;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_4, 2, tmp_tuple_element_4);
        }
        goto tuple_build_noexception_4;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_4:;
        Py_DECREF(tmp_add_expr_left_10);
        Py_DECREF(tmp_string_concat_values_4);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_4:;
        tmp_list_element_4 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_4);
        Py_DECREF(tmp_string_concat_values_4);
        if (tmp_list_element_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_10);

            exception_lineno = 243;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_right_10 = MAKE_LIST_EMPTY(1);
        PyList_SET_ITEM(tmp_add_expr_right_10, 0, tmp_list_element_4);
        tmp_assign_source_29 = BINARY_OPERATION_ADD_OBJECT_OBJECT_LIST(tmp_add_expr_left_10, tmp_add_expr_right_10);
        Py_DECREF(tmp_add_expr_left_10);
        Py_DECREF(tmp_add_expr_right_10);
        if (tmp_assign_source_29 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 243;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = par_mark_line;
            assert(old != NULL);
            par_mark_line = tmp_assign_source_29;
            Py_DECREF(old);
        }

    }
    goto branch_end_7;
    branch_no_7:;
    {
        PyObject *tmp_assign_source_30;
        PyObject *tmp_iadd_expr_left_3;
        PyObject *tmp_iadd_expr_right_3;
        PyObject *tmp_add_expr_left_12;
        PyObject *tmp_add_expr_right_12;
        PyObject *tmp_mult_expr_left_5;
        PyObject *tmp_mult_expr_right_5;
        PyObject *tmp_sub_expr_left_6;
        nuitka_digit tmp_sub_expr_right_6;
        PyObject *tmp_sub_expr_left_7;
        PyObject *tmp_sub_expr_right_7;
        PyObject *tmp_len_arg_9;
        PyObject *tmp_called_value_7;
        PyObject *tmp_args_element_value_6;
        PyObject *tmp_len_arg_10;
        PyObject *tmp_called_value_8;
        PyObject *tmp_args_element_value_7;
        PyObject *tmp_list_element_5;
        PyObject *tmp_string_concat_values_5;
        PyObject *tmp_tuple_element_5;
        PyObject *tmp_format_value_11;
        PyObject *tmp_format_spec_11;
        CHECK_OBJECT(par_mark_line);
        tmp_iadd_expr_left_3 = par_mark_line;
        tmp_mult_expr_left_5 = MAKE_LIST1(mod_consts[48]);
        if (Nuitka_Cell_GET(self->m_closure[10]) == NULL) {
            Py_DECREF(tmp_mult_expr_left_5);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[38]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 245;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_7 = Nuitka_Cell_GET(self->m_closure[10]);
        if (par_line == NULL) {
            Py_DECREF(tmp_mult_expr_left_5);
            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[96]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 245;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_args_element_value_6 = par_line;
        frame_e1d27883b2455e4c949dff371c0a8ceb->m_frame.f_lineno = 245;
        tmp_len_arg_9 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_7, tmp_args_element_value_6);
        if (tmp_len_arg_9 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_mult_expr_left_5);

            exception_lineno = 245;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_sub_expr_left_7 = BUILTIN_LEN(tstate, tmp_len_arg_9);
        Py_DECREF(tmp_len_arg_9);
        if (tmp_sub_expr_left_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_mult_expr_left_5);

            exception_lineno = 245;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        if (Nuitka_Cell_GET(self->m_closure[10]) == NULL) {
            Py_DECREF(tmp_mult_expr_left_5);
            Py_DECREF(tmp_sub_expr_left_7);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[38]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 245;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_8 = Nuitka_Cell_GET(self->m_closure[10]);
        CHECK_OBJECT(par_mark_line);
        tmp_args_element_value_7 = par_mark_line;
        frame_e1d27883b2455e4c949dff371c0a8ceb->m_frame.f_lineno = 245;
        tmp_len_arg_10 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_8, tmp_args_element_value_7);
        if (tmp_len_arg_10 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_mult_expr_left_5);
            Py_DECREF(tmp_sub_expr_left_7);

            exception_lineno = 245;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_sub_expr_right_7 = BUILTIN_LEN(tstate, tmp_len_arg_10);
        Py_DECREF(tmp_len_arg_10);
        if (tmp_sub_expr_right_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_mult_expr_left_5);
            Py_DECREF(tmp_sub_expr_left_7);

            exception_lineno = 245;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_sub_expr_left_6 = BINARY_OPERATION_SUB_OBJECT_LONG_LONG(tmp_sub_expr_left_7, tmp_sub_expr_right_7);
        Py_DECREF(tmp_sub_expr_left_7);
        Py_DECREF(tmp_sub_expr_right_7);
        assert(!(tmp_sub_expr_left_6 == NULL));
        tmp_sub_expr_right_6 = 1;
        tmp_mult_expr_right_5 = BINARY_OPERATION_SUB_OBJECT_LONG_DIGIT(tmp_sub_expr_left_6, tmp_sub_expr_right_6);
        Py_DECREF(tmp_sub_expr_left_6);
        assert(!(tmp_mult_expr_right_5 == NULL));
        tmp_add_expr_left_12 = BINARY_OPERATION_MULT_OBJECT_LIST_LONG(tmp_mult_expr_left_5, tmp_mult_expr_right_5);
        Py_DECREF(tmp_mult_expr_left_5);
        Py_DECREF(tmp_mult_expr_right_5);
        assert(!(tmp_add_expr_left_12 == NULL));
        if (Nuitka_Cell_GET(self->m_closure[8]) == NULL) {
            Py_DECREF(tmp_add_expr_left_12);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 245;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_format_value_11 = Nuitka_Cell_GET(self->m_closure[8]);
        tmp_format_spec_11 = mod_consts[44];
        tmp_tuple_element_5 = BUILTIN_FORMAT(tstate, tmp_format_value_11, tmp_format_spec_11);
        if (tmp_tuple_element_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_12);

            exception_lineno = 245;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_string_concat_values_5 = MAKE_TUPLE_EMPTY(3);
        {
            PyObject *tmp_format_value_12;
            PyObject *tmp_expression_value_10;
            PyObject *tmp_subscript_value_9;
            PyObject *tmp_format_spec_12;
            PyObject *tmp_format_value_13;
            PyObject *tmp_format_spec_13;
            PyTuple_SET_ITEM(tmp_string_concat_values_5, 0, tmp_tuple_element_5);
            if (Nuitka_Cell_GET(self->m_closure[2]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[104]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 245;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_5;
            }

            tmp_expression_value_10 = Nuitka_Cell_GET(self->m_closure[2]);
            tmp_subscript_value_9 = mod_consts[64];
            tmp_format_value_12 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_10, tmp_subscript_value_9);
            if (tmp_format_value_12 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 245;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_5;
            }
            tmp_format_spec_12 = mod_consts[44];
            tmp_tuple_element_5 = BUILTIN_FORMAT(tstate, tmp_format_value_12, tmp_format_spec_12);
            Py_DECREF(tmp_format_value_12);
            if (tmp_tuple_element_5 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 245;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_5;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_5, 1, tmp_tuple_element_5);
            if (Nuitka_Cell_GET(self->m_closure[9]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 245;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_5;
            }

            tmp_format_value_13 = Nuitka_Cell_GET(self->m_closure[9]);
            tmp_format_spec_13 = mod_consts[44];
            tmp_tuple_element_5 = BUILTIN_FORMAT(tstate, tmp_format_value_13, tmp_format_spec_13);
            if (tmp_tuple_element_5 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 245;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_5;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_5, 2, tmp_tuple_element_5);
        }
        goto tuple_build_noexception_5;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_5:;
        Py_DECREF(tmp_add_expr_left_12);
        Py_DECREF(tmp_string_concat_values_5);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_5:;
        tmp_list_element_5 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_5);
        Py_DECREF(tmp_string_concat_values_5);
        if (tmp_list_element_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_12);

            exception_lineno = 245;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_right_12 = MAKE_LIST_EMPTY(1);
        PyList_SET_ITEM(tmp_add_expr_right_12, 0, tmp_list_element_5);
        tmp_iadd_expr_right_3 = BINARY_OPERATION_ADD_OBJECT_LIST_LIST(tmp_add_expr_left_12, tmp_add_expr_right_12);
        Py_DECREF(tmp_add_expr_left_12);
        Py_DECREF(tmp_add_expr_right_12);
        assert(!(tmp_iadd_expr_right_3 == NULL));
        tmp_result = INPLACE_OPERATION_ADD_OBJECT_LIST(&tmp_iadd_expr_left_3, tmp_iadd_expr_right_3);
        Py_DECREF(tmp_iadd_expr_right_3);
        if (tmp_result == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 245;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_30 = tmp_iadd_expr_left_3;
        par_mark_line = tmp_assign_source_30;

    }
    branch_end_7:;
    {
        PyObject *tmp_assign_source_31;
        PyObject *tmp_str_arg_value_5;
        PyObject *tmp_iterable_value_4;
        tmp_str_arg_value_5 = mod_consts[44];
        CHECK_OBJECT(par_mark_line);
        tmp_iterable_value_4 = par_mark_line;
        tmp_assign_source_31 = UNICODE_JOIN(tstate, tmp_str_arg_value_5, tmp_iterable_value_4);
        if (tmp_assign_source_31 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 246;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = par_mark_line;
            assert(old != NULL);
            par_mark_line = tmp_assign_source_31;
            Py_DECREF(old);
        }

    }
    branch_no_6:;
    {
        PyObject *tmp_list_arg_value_1;
        PyObject *tmp_item_value_1;
        CHECK_OBJECT(var_output);
        tmp_list_arg_value_1 = var_output;
        if (var_output_line == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[105]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 248;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_item_value_1 = var_output_line;
        tmp_result = LIST_APPEND0(tmp_list_arg_value_1, tmp_item_value_1);
        assert(!(tmp_result == false));
    }
    {
        PyObject *tmp_list_arg_value_2;
        PyObject *tmp_item_value_2;
        PyObject *tmp_add_expr_left_13;
        PyObject *tmp_add_expr_right_13;
        PyObject *tmp_str_arg_value_6;
        PyObject *tmp_iterable_value_5;
        nuitka_bool tmp_condition_result_9;
        int tmp_truth_name_3;
        PyObject *tmp_string_concat_values_6;
        PyObject *tmp_tuple_element_6;
        CHECK_OBJECT(var_output);
        tmp_list_arg_value_2 = var_output;
        tmp_str_arg_value_6 = mod_consts[44];
        if (par_mark_line == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[98]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 249;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_iterable_value_5 = par_mark_line;
        tmp_add_expr_left_13 = UNICODE_JOIN(tstate, tmp_str_arg_value_6, tmp_iterable_value_5);
        if (tmp_add_expr_left_13 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 249;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        if (var_marked == NULL) {
            Py_DECREF(tmp_add_expr_left_13);
            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[100]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 249;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_truth_name_3 = CHECK_IF_TRUE(var_marked);
        if (tmp_truth_name_3 == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_13);

            exception_lineno = 249;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_9 = tmp_truth_name_3 == 0 ? NUITKA_BOOL_FALSE : NUITKA_BOOL_TRUE;
        if (tmp_condition_result_9 == NUITKA_BOOL_TRUE) {
            goto condexpr_true_2;
        } else {
            goto condexpr_false_2;
        }
        condexpr_true_2:;
        tmp_tuple_element_6 = mod_consts[106];
        tmp_string_concat_values_6 = MAKE_TUPLE_EMPTY(4);
        {
            PyObject *tmp_format_value_14;
            PyObject *tmp_format_spec_14;
            PyObject *tmp_format_value_15;
            PyObject *tmp_expression_value_11;
            PyObject *tmp_subscript_value_10;
            PyObject *tmp_format_spec_15;
            PyObject *tmp_format_value_16;
            PyObject *tmp_format_spec_16;
            PyTuple_SET_ITEM0(tmp_string_concat_values_6, 0, tmp_tuple_element_6);
            if (Nuitka_Cell_GET(self->m_closure[8]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[43]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 249;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_6;
            }

            tmp_format_value_14 = Nuitka_Cell_GET(self->m_closure[8]);
            tmp_format_spec_14 = mod_consts[44];
            tmp_tuple_element_6 = BUILTIN_FORMAT(tstate, tmp_format_value_14, tmp_format_spec_14);
            if (tmp_tuple_element_6 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 249;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_6;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_6, 1, tmp_tuple_element_6);
            if (Nuitka_Cell_GET(self->m_closure[2]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[104]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 249;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_6;
            }

            tmp_expression_value_11 = Nuitka_Cell_GET(self->m_closure[2]);
            tmp_subscript_value_10 = mod_consts[64];
            tmp_format_value_15 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_11, tmp_subscript_value_10);
            if (tmp_format_value_15 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 249;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_6;
            }
            tmp_format_spec_15 = mod_consts[44];
            tmp_tuple_element_6 = BUILTIN_FORMAT(tstate, tmp_format_value_15, tmp_format_spec_15);
            Py_DECREF(tmp_format_value_15);
            if (tmp_tuple_element_6 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 249;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_6;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_6, 2, tmp_tuple_element_6);
            if (Nuitka_Cell_GET(self->m_closure[9]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 249;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_6;
            }

            tmp_format_value_16 = Nuitka_Cell_GET(self->m_closure[9]);
            tmp_format_spec_16 = mod_consts[44];
            tmp_tuple_element_6 = BUILTIN_FORMAT(tstate, tmp_format_value_16, tmp_format_spec_16);
            if (tmp_tuple_element_6 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 249;
                type_description_1 = "oooooooooccccccccccc";
                goto tuple_build_exception_6;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_6, 3, tmp_tuple_element_6);
        }
        goto tuple_build_noexception_6;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_6:;
        Py_DECREF(tmp_add_expr_left_13);
        Py_DECREF(tmp_string_concat_values_6);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_6:;
        tmp_add_expr_right_13 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_6);
        Py_DECREF(tmp_string_concat_values_6);
        if (tmp_add_expr_right_13 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_13);

            exception_lineno = 249;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        goto condexpr_end_2;
        condexpr_false_2:;
        tmp_add_expr_right_13 = mod_consts[44];
        Py_INCREF(tmp_add_expr_right_13);
        condexpr_end_2:;
        tmp_item_value_2 = BINARY_OPERATION_ADD_OBJECT_UNICODE_UNICODE(tmp_add_expr_left_13, tmp_add_expr_right_13);
        Py_DECREF(tmp_add_expr_left_13);
        Py_DECREF(tmp_add_expr_right_13);
        assert(!(tmp_item_value_2 == NULL));
        tmp_result = LIST_APPEND1(tmp_list_arg_value_2, tmp_item_value_2);
        assert(!(tmp_result == false));
    }
    {
        PyObject *tmp_str_arg_value_7;
        PyObject *tmp_iterable_value_6;
        tmp_str_arg_value_7 = mod_consts[57];
        CHECK_OBJECT(var_output);
        tmp_iterable_value_6 = var_output;
        tmp_return_value = UNICODE_JOIN(tstate, tmp_str_arg_value_7, tmp_iterable_value_6);
        if (tmp_return_value == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 251;
            type_description_1 = "oooooooooccccccccccc";
            goto frame_exception_exit_1;
        }
        goto frame_return_exit_1;
    }


    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto frame_no_exception_1;
    frame_return_exit_1:

    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto try_return_handler_1;
    frame_exception_exit_1:


    if (exception_tb == NULL) {
        exception_tb = MAKE_TRACEBACK(frame_e1d27883b2455e4c949dff371c0a8ceb, exception_lineno);
    } else if (exception_tb->tb_frame != &frame_e1d27883b2455e4c949dff371c0a8ceb->m_frame) {
        exception_tb = ADD_TRACEBACK(exception_tb, frame_e1d27883b2455e4c949dff371c0a8ceb, exception_lineno);
    }

    // Attaches locals to frame if any.
    Nuitka_Frame_AttachLocals(
        frame_e1d27883b2455e4c949dff371c0a8ceb,
        type_description_1,
        par_line,
        par_mark_line,
        var_output,
        var_marked,
        var_skip_amount,
        var_len_of_item,
        var_output_line,
        var_item,
        var_index,
        self->m_closure[10],
        self->m_closure[1],
        self->m_closure[7],
        self->m_closure[0],
        self->m_closure[9],
        self->m_closure[3],
        self->m_closure[8],
        self->m_closure[5],
        self->m_closure[6],
        self->m_closure[4],
        self->m_closure[2]
    );


    // Release cached frame if used for exception.
    if (frame_e1d27883b2455e4c949dff371c0a8ceb == cache_frame_e1d27883b2455e4c949dff371c0a8ceb) {
#if _DEBUG_REFCOUNTS
        count_active_frame_cache_instances -= 1;
        count_released_frame_cache_instances += 1;
#endif
        Py_DECREF(cache_frame_e1d27883b2455e4c949dff371c0a8ceb);
        cache_frame_e1d27883b2455e4c949dff371c0a8ceb = NULL;
    }

    assertFrameObject(frame_e1d27883b2455e4c949dff371c0a8ceb);

    // Put the previous frame back on top.
    popFrameStack(tstate);

    // Return the error.
    goto try_except_handler_1;
    frame_no_exception_1:;
    NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
    return NULL;
    // Return handler code:
    try_return_handler_1:;
    Py_XDECREF(par_line);
    par_line = NULL;
    Py_XDECREF(par_mark_line);
    par_mark_line = NULL;
    CHECK_OBJECT(var_output);
    Py_DECREF(var_output);
    var_output = NULL;
    Py_XDECREF(var_marked);
    var_marked = NULL;
    CHECK_OBJECT(var_skip_amount);
    Py_DECREF(var_skip_amount);
    var_skip_amount = NULL;
    Py_XDECREF(var_len_of_item);
    var_len_of_item = NULL;
    Py_XDECREF(var_output_line);
    var_output_line = NULL;
    Py_XDECREF(var_item);
    var_item = NULL;
    Py_XDECREF(var_index);
    var_index = NULL;
    goto function_return_exit;
    // Exception handler code:
    try_except_handler_1:;
    exception_keeper_type_5 = exception_type;
    exception_keeper_value_5 = exception_value;
    exception_keeper_tb_5 = exception_tb;
    exception_keeper_lineno_5 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(par_line);
    par_line = NULL;
    Py_XDECREF(par_mark_line);
    par_mark_line = NULL;
    CHECK_OBJECT(var_output);
    Py_DECREF(var_output);
    var_output = NULL;
    Py_XDECREF(var_marked);
    var_marked = NULL;
    Py_XDECREF(var_skip_amount);
    var_skip_amount = NULL;
    Py_XDECREF(var_len_of_item);
    var_len_of_item = NULL;
    Py_XDECREF(var_output_line);
    var_output_line = NULL;
    Py_XDECREF(var_item);
    var_item = NULL;
    Py_XDECREF(var_index);
    var_index = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_5;
    exception_value = exception_keeper_value_5;
    exception_tb = exception_keeper_tb_5;
    exception_lineno = exception_keeper_lineno_5;

    goto function_exception_exit;
    // End of try:

    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;

function_exception_exit:

    assert(exception_type);
    RESTORE_ERROR_OCCURRED(tstate, exception_type, exception_value, exception_tb);

    return NULL;

function_return_exit:
   // Function cleanup code if any.


   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}


static PyObject *impl_core$panic$$$function__2_panic$$$function__5_s_u(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *par_line = python_pars[0];
    struct Nuitka_FrameObject *frame_7bf646c481fc4ce8df0b213af78a07e9;
    NUITKA_MAY_BE_UNUSED char const *type_description_1 = NULL;
    int tmp_res;
    PyObject *exception_type = NULL;
    PyObject *exception_value = NULL;
    PyTracebackObject *exception_tb = NULL;
    NUITKA_MAY_BE_UNUSED int exception_lineno = 0;
    PyObject *tmp_return_value = NULL;
    static struct Nuitka_FrameObject *cache_frame_7bf646c481fc4ce8df0b213af78a07e9 = NULL;

    // Actual function body.
    if (isFrameUnusable(cache_frame_7bf646c481fc4ce8df0b213af78a07e9)) {
        Py_XDECREF(cache_frame_7bf646c481fc4ce8df0b213af78a07e9);

#if _DEBUG_REFCOUNTS
        if (cache_frame_7bf646c481fc4ce8df0b213af78a07e9 == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_frame_7bf646c481fc4ce8df0b213af78a07e9 = MAKE_FUNCTION_FRAME(tstate, codeobj_7bf646c481fc4ce8df0b213af78a07e9, module_core$panic, sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_frame_7bf646c481fc4ce8df0b213af78a07e9->m_type_description == NULL);
    frame_7bf646c481fc4ce8df0b213af78a07e9 = cache_frame_7bf646c481fc4ce8df0b213af78a07e9;

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackCompiledFrame(tstate, frame_7bf646c481fc4ce8df0b213af78a07e9);
    assert(Py_REFCNT(frame_7bf646c481fc4ce8df0b213af78a07e9) == 2);

    // Framed code:
    {
        nuitka_bool tmp_condition_result_1;
        PyObject *tmp_isinstance_inst_1;
        PyObject *tmp_isinstance_cls_1;
        CHECK_OBJECT(par_line);
        tmp_isinstance_inst_1 = par_line;
        tmp_isinstance_cls_1 = (PyObject *)&PyList_Type;
        tmp_res = PyObject_IsInstance(tmp_isinstance_inst_1, tmp_isinstance_cls_1);
        if (tmp_res == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 255;
            type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_1 = (tmp_res != 0) ? NUITKA_BOOL_TRUE : NUITKA_BOOL_FALSE;
        if (tmp_condition_result_1 == NUITKA_BOOL_TRUE) {
            goto branch_yes_1;
        } else {
            goto branch_no_1;
        }
    }
    branch_yes_1:;
    {
        PyObject *tmp_list_arg_1;
        PyObject *tmp_called_value_1;
        PyObject *tmp_expression_value_1;
        PyObject *tmp_args_element_value_1;
        PyObject *tmp_args_element_value_2;
        PyObject *tmp_args_element_value_3;
        PyObject *tmp_str_arg_value_1;
        PyObject *tmp_iterable_value_1;
        tmp_expression_value_1 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[65]);

        if (unlikely(tmp_expression_value_1 == NULL)) {
            tmp_expression_value_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[65]);
        }

        if (tmp_expression_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 256;
            type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_called_value_1 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_1, mod_consts[107]);
        if (tmp_called_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 256;
            type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_args_element_value_1 = mod_consts[108];
        tmp_args_element_value_2 = mod_consts[44];
        tmp_str_arg_value_1 = mod_consts[44];
        CHECK_OBJECT(par_line);
        tmp_iterable_value_1 = par_line;
        tmp_args_element_value_3 = UNICODE_JOIN(tstate, tmp_str_arg_value_1, tmp_iterable_value_1);
        if (tmp_args_element_value_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_called_value_1);

            exception_lineno = 256;
            type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        frame_7bf646c481fc4ce8df0b213af78a07e9->m_frame.f_lineno = 256;
        {
            PyObject *call_args[] = {tmp_args_element_value_1, tmp_args_element_value_2, tmp_args_element_value_3};
            tmp_list_arg_1 = CALL_FUNCTION_WITH_ARGS3(tstate, tmp_called_value_1, call_args);
        }

        Py_DECREF(tmp_called_value_1);
        Py_DECREF(tmp_args_element_value_3);
        if (tmp_list_arg_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 256;
            type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_return_value = MAKE_LIST(tstate, tmp_list_arg_1);
        Py_DECREF(tmp_list_arg_1);
        if (tmp_return_value == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 256;
            type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        goto frame_return_exit_1;
    }
    branch_no_1:;
    {
        PyObject *tmp_called_instance_1;
        PyObject *tmp_args_element_value_4;
        PyObject *tmp_args_element_value_5;
        PyObject *tmp_args_element_value_6;
        tmp_called_instance_1 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[65]);

        if (unlikely(tmp_called_instance_1 == NULL)) {
            tmp_called_instance_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[65]);
        }

        if (tmp_called_instance_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 257;
            type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_args_element_value_4 = mod_consts[108];
        tmp_args_element_value_5 = mod_consts[44];
        CHECK_OBJECT(par_line);
        tmp_args_element_value_6 = par_line;
        frame_7bf646c481fc4ce8df0b213af78a07e9->m_frame.f_lineno = 257;
        {
            PyObject *call_args[] = {tmp_args_element_value_4, tmp_args_element_value_5, tmp_args_element_value_6};
            tmp_return_value = CALL_METHOD_WITH_ARGS3(
                tstate,
                tmp_called_instance_1,
                mod_consts[107],
                call_args
            );
        }

        if (tmp_return_value == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 257;
            type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        goto frame_return_exit_1;
    }


    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto frame_no_exception_1;
    frame_return_exit_1:

    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto function_return_exit;
    frame_exception_exit_1:


    if (exception_tb == NULL) {
        exception_tb = MAKE_TRACEBACK(frame_7bf646c481fc4ce8df0b213af78a07e9, exception_lineno);
    } else if (exception_tb->tb_frame != &frame_7bf646c481fc4ce8df0b213af78a07e9->m_frame) {
        exception_tb = ADD_TRACEBACK(exception_tb, frame_7bf646c481fc4ce8df0b213af78a07e9, exception_lineno);
    }

    // Attaches locals to frame if any.
    Nuitka_Frame_AttachLocals(
        frame_7bf646c481fc4ce8df0b213af78a07e9,
        type_description_1,
        par_line
    );


    // Release cached frame if used for exception.
    if (frame_7bf646c481fc4ce8df0b213af78a07e9 == cache_frame_7bf646c481fc4ce8df0b213af78a07e9) {
#if _DEBUG_REFCOUNTS
        count_active_frame_cache_instances -= 1;
        count_released_frame_cache_instances += 1;
#endif
        Py_DECREF(cache_frame_7bf646c481fc4ce8df0b213af78a07e9);
        cache_frame_7bf646c481fc4ce8df0b213af78a07e9 = NULL;
    }

    assertFrameObject(frame_7bf646c481fc4ce8df0b213af78a07e9);

    // Put the previous frame back on top.
    popFrameStack(tstate);

    // Return the error.
    goto function_exception_exit;
    frame_no_exception_1:;

    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;

function_exception_exit:
    CHECK_OBJECT(par_line);
    Py_DECREF(par_line);
    assert(exception_type);
    RESTORE_ERROR_OCCURRED(tstate, exception_type, exception_value, exception_tb);

    return NULL;

function_return_exit:
   // Function cleanup code if any.
    CHECK_OBJECT(par_line);
    Py_DECREF(par_line);

   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}


static PyObject *impl_core$panic$$$function__2_panic$$$function__6_process_lines(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *par_line = python_pars[0];
    PyObject *par_index = python_pars[1];
    PyObject *var_current_line_no = NULL;
    struct Nuitka_FrameObject *frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd;
    NUITKA_MAY_BE_UNUSED char const *type_description_1 = NULL;
    PyObject *exception_type = NULL;
    PyObject *exception_value = NULL;
    PyTracebackObject *exception_tb = NULL;
    NUITKA_MAY_BE_UNUSED int exception_lineno = 0;
    static struct Nuitka_FrameObject *cache_frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd = NULL;
    PyObject *tmp_return_value = NULL;
    PyObject *exception_keeper_type_1;
    PyObject *exception_keeper_value_1;
    PyTracebackObject *exception_keeper_tb_1;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_1;

    // Actual function body.
    // Tried code:
    if (isFrameUnusable(cache_frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd)) {
        Py_XDECREF(cache_frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd);

#if _DEBUG_REFCOUNTS
        if (cache_frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd = MAKE_FUNCTION_FRAME(tstate, codeobj_cfbb1fd5c2fa73ae6fa06e61890dd7dd, module_core$panic, sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd->m_type_description == NULL);
    frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd = cache_frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd;

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackCompiledFrame(tstate, frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd);
    assert(Py_REFCNT(frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd) == 2);

    // Framed code:
    {
        PyObject *tmp_assign_source_1;
        PyObject *tmp_add_expr_left_1;
        PyObject *tmp_add_expr_right_1;
        PyObject *tmp_add_expr_left_2;
        PyObject *tmp_add_expr_right_2;
        PyObject *tmp_sub_expr_left_1;
        PyObject *tmp_sub_expr_right_1;
        if (Nuitka_Cell_GET(self->m_closure[4]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[109]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 261;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_sub_expr_left_1 = Nuitka_Cell_GET(self->m_closure[4]);
        if (Nuitka_Cell_GET(self->m_closure[5]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[110]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 261;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_sub_expr_right_1 = Nuitka_Cell_GET(self->m_closure[5]);
        tmp_add_expr_left_2 = BINARY_OPERATION_SUB_OBJECT_OBJECT_OBJECT(tmp_sub_expr_left_1, tmp_sub_expr_right_1);
        if (tmp_add_expr_left_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 261;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_right_2 = mod_consts[56];
        tmp_add_expr_left_1 = BINARY_OPERATION_ADD_OBJECT_OBJECT_LONG(tmp_add_expr_left_2, tmp_add_expr_right_2);
        Py_DECREF(tmp_add_expr_left_2);
        if (tmp_add_expr_left_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 261;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(par_index);
        tmp_add_expr_right_1 = par_index;
        tmp_assign_source_1 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_1, tmp_add_expr_right_1);
        Py_DECREF(tmp_add_expr_left_1);
        if (tmp_assign_source_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 261;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        assert(var_current_line_no == NULL);
        var_current_line_no = tmp_assign_source_1;
    }
    {
        nuitka_bool tmp_condition_result_1;
        PyObject *tmp_cmp_expr_left_1;
        PyObject *tmp_cmp_expr_right_1;
        CHECK_OBJECT(var_current_line_no);
        tmp_cmp_expr_left_1 = var_current_line_no;
        tmp_cmp_expr_right_1 = mod_consts[56];
        tmp_condition_result_1 = RICH_COMPARE_LT_NBOOL_OBJECT_LONG(tmp_cmp_expr_left_1, tmp_cmp_expr_right_1);
        if (tmp_condition_result_1 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 262;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        if (tmp_condition_result_1 == NUITKA_BOOL_TRUE) {
            goto branch_yes_1;
        } else {
            goto branch_no_1;
        }
    }
    branch_yes_1:;
    {
        PyObject *tmp_assign_source_2;
        tmp_assign_source_2 = mod_consts[56];
        {
            PyObject *old = var_current_line_no;
            assert(old != NULL);
            var_current_line_no = tmp_assign_source_2;
            Py_INCREF(var_current_line_no);
            Py_DECREF(old);
        }

    }
    branch_no_1:;
    {
        nuitka_bool tmp_condition_result_2;
        int tmp_or_left_truth_1;
        nuitka_bool tmp_or_left_value_1;
        nuitka_bool tmp_or_right_value_1;
        PyObject *tmp_cmp_expr_left_2;
        PyObject *tmp_cmp_expr_right_2;
        PyObject *tmp_cmp_expr_left_3;
        PyObject *tmp_cmp_expr_right_3;
        CHECK_OBJECT(var_current_line_no);
        tmp_cmp_expr_left_2 = var_current_line_no;
        if (Nuitka_Cell_GET(self->m_closure[4]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[109]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 263;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_cmp_expr_right_2 = Nuitka_Cell_GET(self->m_closure[4]);
        tmp_or_left_value_1 = RICH_COMPARE_EQ_NBOOL_OBJECT_OBJECT(tmp_cmp_expr_left_2, tmp_cmp_expr_right_2);
        if (tmp_or_left_value_1 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 263;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_or_left_truth_1 = tmp_or_left_value_1 == NUITKA_BOOL_TRUE ? 1 : 0;
        if (tmp_or_left_truth_1 == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 263;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        if (tmp_or_left_truth_1 == 1) {
            goto or_left_1;
        } else {
            goto or_right_1;
        }
        or_right_1:;
        CHECK_OBJECT(var_current_line_no);
        tmp_cmp_expr_left_3 = var_current_line_no;
        tmp_cmp_expr_right_3 = mod_consts[56];
        tmp_or_right_value_1 = RICH_COMPARE_EQ_NBOOL_OBJECT_LONG(tmp_cmp_expr_left_3, tmp_cmp_expr_right_3);
        if (tmp_or_right_value_1 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 263;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_2 = tmp_or_right_value_1;
        goto or_end_1;
        or_left_1:;
        tmp_condition_result_2 = tmp_or_left_value_1;
        or_end_1:;
        if (tmp_condition_result_2 == NUITKA_BOOL_TRUE) {
            goto branch_yes_2;
        } else {
            goto branch_no_2;
        }
    }
    branch_yes_2:;
    {
        PyObject *tmp_assign_source_3;
        PyObject *tmp_str_arg_value_1;
        PyObject *tmp_string_concat_values_1;
        PyObject *tmp_tuple_element_1;
        PyObject *tmp_format_value_1;
        PyObject *tmp_format_spec_1;
        if (Nuitka_Cell_GET(self->m_closure[6]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 264;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_format_value_1 = Nuitka_Cell_GET(self->m_closure[6]);
        tmp_format_spec_1 = mod_consts[44];
        tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_1, tmp_format_spec_1);
        if (tmp_tuple_element_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 264;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_string_concat_values_1 = MAKE_TUPLE_EMPTY(8);
        {
            PyObject *tmp_format_value_2;
            PyObject *tmp_expression_value_1;
            PyObject *tmp_subscript_value_1;
            PyObject *tmp_format_spec_2;
            PyObject *tmp_format_value_3;
            PyObject *tmp_format_spec_3;
            PyObject *tmp_format_value_4;
            PyObject *tmp_called_value_1;
            PyObject *tmp_expression_value_2;
            PyObject *tmp_unicode_arg_1;
            PyObject *tmp_args_element_value_1;
            PyObject *tmp_len_arg_1;
            PyObject *tmp_unicode_arg_2;
            PyObject *tmp_format_spec_4;
            PyObject *tmp_format_value_5;
            PyObject *tmp_format_spec_5;
            PyObject *tmp_format_value_6;
            PyObject *tmp_format_spec_6;
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 0, tmp_tuple_element_1);
            if (Nuitka_Cell_GET(self->m_closure[1]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[104]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }

            tmp_expression_value_1 = Nuitka_Cell_GET(self->m_closure[1]);
            tmp_subscript_value_1 = mod_consts[64];
            tmp_format_value_2 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_1, tmp_subscript_value_1);
            if (tmp_format_value_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }
            tmp_format_spec_2 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_2, tmp_format_spec_2);
            Py_DECREF(tmp_format_value_2);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 1, tmp_tuple_element_1);
            if (Nuitka_Cell_GET(self->m_closure[0]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[49]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }

            tmp_format_value_3 = Nuitka_Cell_GET(self->m_closure[0]);
            tmp_format_spec_3 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_3, tmp_format_spec_3);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 2, tmp_tuple_element_1);
            tmp_tuple_element_1 = mod_consts[48];
            PyTuple_SET_ITEM0(tmp_string_concat_values_1, 3, tmp_tuple_element_1);
            CHECK_OBJECT(var_current_line_no);
            tmp_unicode_arg_1 = var_current_line_no;
            tmp_expression_value_2 = BUILTIN_UNICODE1(tmp_unicode_arg_1);
            if (tmp_expression_value_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }
            tmp_called_value_1 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_2, mod_consts[63]);
            Py_DECREF(tmp_expression_value_2);
            if (tmp_called_value_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }
            if (Nuitka_Cell_GET(self->m_closure[4]) == NULL) {
                Py_DECREF(tmp_called_value_1);
                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[109]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }

            tmp_unicode_arg_2 = Nuitka_Cell_GET(self->m_closure[4]);
            tmp_len_arg_1 = BUILTIN_UNICODE1(tmp_unicode_arg_2);
            if (tmp_len_arg_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_called_value_1);

                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }
            tmp_args_element_value_1 = BUILTIN_LEN(tstate, tmp_len_arg_1);
            Py_DECREF(tmp_len_arg_1);
            if (tmp_args_element_value_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_called_value_1);

                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }
            frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd->m_frame.f_lineno = 264;
            tmp_format_value_4 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_1, tmp_args_element_value_1);
            Py_DECREF(tmp_called_value_1);
            Py_DECREF(tmp_args_element_value_1);
            if (tmp_format_value_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }
            tmp_format_spec_4 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_4, tmp_format_spec_4);
            Py_DECREF(tmp_format_value_4);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 4, tmp_tuple_element_1);
            tmp_tuple_element_1 = mod_consts[111];
            PyTuple_SET_ITEM0(tmp_string_concat_values_1, 5, tmp_tuple_element_1);
            if (Nuitka_Cell_GET(self->m_closure[7]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }

            tmp_format_value_5 = Nuitka_Cell_GET(self->m_closure[7]);
            tmp_format_spec_5 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_5, tmp_format_spec_5);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 6, tmp_tuple_element_1);
            CHECK_OBJECT(par_line);
            tmp_format_value_6 = par_line;
            tmp_format_spec_6 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_6, tmp_format_spec_6);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 264;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 7, tmp_tuple_element_1);
        }
        goto tuple_build_noexception_1;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_1:;
        Py_DECREF(tmp_string_concat_values_1);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_1:;
        tmp_str_arg_value_1 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_1);
        Py_DECREF(tmp_string_concat_values_1);
        if (tmp_str_arg_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 264;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_3 = UNICODE_RSTRIP1(tstate, tmp_str_arg_value_1);
        Py_DECREF(tmp_str_arg_value_1);
        if (tmp_assign_source_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 264;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = par_line;
            assert(old != NULL);
            par_line = tmp_assign_source_3;
            Py_DECREF(old);
        }

    }
    goto branch_end_2;
    branch_no_2:;
    {
        PyObject *tmp_assign_source_4;
        PyObject *tmp_str_arg_value_2;
        PyObject *tmp_string_concat_values_2;
        PyObject *tmp_tuple_element_2;
        PyObject *tmp_format_value_7;
        PyObject *tmp_format_spec_7;
        if (Nuitka_Cell_GET(self->m_closure[6]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 266;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_format_value_7 = Nuitka_Cell_GET(self->m_closure[6]);
        tmp_format_spec_7 = mod_consts[44];
        tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_7, tmp_format_spec_7);
        if (tmp_tuple_element_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 266;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_string_concat_values_2 = MAKE_TUPLE_EMPTY(8);
        {
            PyObject *tmp_format_value_8;
            PyObject *tmp_expression_value_3;
            PyObject *tmp_subscript_value_2;
            PyObject *tmp_format_spec_8;
            PyObject *tmp_format_value_9;
            PyObject *tmp_format_spec_9;
            PyObject *tmp_format_value_10;
            PyObject *tmp_called_value_2;
            PyObject *tmp_expression_value_4;
            PyObject *tmp_unicode_arg_3;
            PyObject *tmp_args_element_value_2;
            PyObject *tmp_len_arg_2;
            PyObject *tmp_unicode_arg_4;
            PyObject *tmp_format_spec_10;
            PyObject *tmp_format_value_11;
            PyObject *tmp_format_spec_11;
            PyObject *tmp_format_value_12;
            PyObject *tmp_format_spec_12;
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 0, tmp_tuple_element_2);
            if (Nuitka_Cell_GET(self->m_closure[1]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[104]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }

            tmp_expression_value_3 = Nuitka_Cell_GET(self->m_closure[1]);
            tmp_subscript_value_2 = mod_consts[64];
            tmp_format_value_8 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_3, tmp_subscript_value_2);
            if (tmp_format_value_8 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }
            tmp_format_spec_8 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_8, tmp_format_spec_8);
            Py_DECREF(tmp_format_value_8);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 1, tmp_tuple_element_2);
            if (Nuitka_Cell_GET(self->m_closure[3]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[61]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }

            tmp_format_value_9 = Nuitka_Cell_GET(self->m_closure[3]);
            tmp_format_spec_9 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_9, tmp_format_spec_9);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 2, tmp_tuple_element_2);
            tmp_tuple_element_2 = mod_consts[48];
            PyTuple_SET_ITEM0(tmp_string_concat_values_2, 3, tmp_tuple_element_2);
            CHECK_OBJECT(var_current_line_no);
            tmp_unicode_arg_3 = var_current_line_no;
            tmp_expression_value_4 = BUILTIN_UNICODE1(tmp_unicode_arg_3);
            if (tmp_expression_value_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }
            tmp_called_value_2 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_4, mod_consts[63]);
            Py_DECREF(tmp_expression_value_4);
            if (tmp_called_value_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }
            if (Nuitka_Cell_GET(self->m_closure[4]) == NULL) {
                Py_DECREF(tmp_called_value_2);
                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[109]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }

            tmp_unicode_arg_4 = Nuitka_Cell_GET(self->m_closure[4]);
            tmp_len_arg_2 = BUILTIN_UNICODE1(tmp_unicode_arg_4);
            if (tmp_len_arg_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_called_value_2);

                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }
            tmp_args_element_value_2 = BUILTIN_LEN(tstate, tmp_len_arg_2);
            Py_DECREF(tmp_len_arg_2);
            if (tmp_args_element_value_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_called_value_2);

                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }
            frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd->m_frame.f_lineno = 266;
            tmp_format_value_10 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_2, tmp_args_element_value_2);
            Py_DECREF(tmp_called_value_2);
            Py_DECREF(tmp_args_element_value_2);
            if (tmp_format_value_10 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }
            tmp_format_spec_10 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_10, tmp_format_spec_10);
            Py_DECREF(tmp_format_value_10);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 4, tmp_tuple_element_2);
            tmp_tuple_element_2 = mod_consts[111];
            PyTuple_SET_ITEM0(tmp_string_concat_values_2, 5, tmp_tuple_element_2);
            if (Nuitka_Cell_GET(self->m_closure[7]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }

            tmp_format_value_11 = Nuitka_Cell_GET(self->m_closure[7]);
            tmp_format_spec_11 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_11, tmp_format_spec_11);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 6, tmp_tuple_element_2);
            CHECK_OBJECT(par_line);
            tmp_format_value_12 = par_line;
            tmp_format_spec_12 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_12, tmp_format_spec_12);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 266;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 7, tmp_tuple_element_2);
        }
        goto tuple_build_noexception_2;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_2:;
        Py_DECREF(tmp_string_concat_values_2);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_2:;
        tmp_str_arg_value_2 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_2);
        Py_DECREF(tmp_string_concat_values_2);
        if (tmp_str_arg_value_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 266;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_4 = UNICODE_RSTRIP1(tstate, tmp_str_arg_value_2);
        Py_DECREF(tmp_str_arg_value_2);
        if (tmp_assign_source_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 266;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = par_line;
            assert(old != NULL);
            par_line = tmp_assign_source_4;
            Py_DECREF(old);
        }

    }
    branch_end_2:;
    {
        nuitka_bool tmp_condition_result_3;
        PyObject *tmp_cmp_expr_left_4;
        PyObject *tmp_cmp_expr_right_4;
        PyObject *tmp_len_arg_3;
        PyObject *tmp_called_value_3;
        PyObject *tmp_args_element_value_3;
        PyObject *tmp_sub_expr_left_2;
        PyObject *tmp_sub_expr_right_2;
        if (Nuitka_Cell_GET(self->m_closure[8]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[38]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 268;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_3 = Nuitka_Cell_GET(self->m_closure[8]);
        CHECK_OBJECT(par_line);
        tmp_args_element_value_3 = par_line;
        frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd->m_frame.f_lineno = 268;
        tmp_len_arg_3 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_3, tmp_args_element_value_3);
        if (tmp_len_arg_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 268;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_cmp_expr_left_4 = BUILTIN_LEN(tstate, tmp_len_arg_3);
        Py_DECREF(tmp_len_arg_3);
        if (tmp_cmp_expr_left_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 268;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_sub_expr_left_2 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

        if (unlikely(tmp_sub_expr_left_2 == NULL)) {
            tmp_sub_expr_left_2 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
        }

        if (tmp_sub_expr_left_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_cmp_expr_left_4);

            exception_lineno = 268;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_sub_expr_right_2 = mod_consts[56];
        tmp_cmp_expr_right_4 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_2, tmp_sub_expr_right_2);
        if (tmp_cmp_expr_right_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_cmp_expr_left_4);

            exception_lineno = 268;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_3 = RICH_COMPARE_GT_NBOOL_LONG_OBJECT(tmp_cmp_expr_left_4, tmp_cmp_expr_right_4);
        Py_DECREF(tmp_cmp_expr_left_4);
        Py_DECREF(tmp_cmp_expr_right_4);
        if (tmp_condition_result_3 == NUITKA_BOOL_EXCEPTION) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 268;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        if (tmp_condition_result_3 == NUITKA_BOOL_TRUE) {
            goto branch_yes_3;
        } else {
            goto branch_no_3;
        }
    }
    branch_yes_3:;
    {
        PyObject *tmp_assign_source_5;
        PyObject *tmp_add_expr_left_3;
        PyObject *tmp_add_expr_right_3;
        PyObject *tmp_expression_value_5;
        PyObject *tmp_subscript_value_3;
        PyObject *tmp_stop_value_1;
        PyObject *tmp_add_expr_left_4;
        PyObject *tmp_add_expr_right_4;
        nuitka_bool tmp_condition_result_4;
        int tmp_truth_name_1;
        CHECK_OBJECT(par_line);
        tmp_expression_value_5 = par_line;
        tmp_add_expr_left_4 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

        if (unlikely(tmp_add_expr_left_4 == NULL)) {
            tmp_add_expr_left_4 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
        }

        if (tmp_add_expr_left_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 269;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        if (Nuitka_Cell_GET(self->m_closure[2]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[93]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 269;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_truth_name_1 = CHECK_IF_TRUE(Nuitka_Cell_GET(self->m_closure[2]));
        if (tmp_truth_name_1 == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 269;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_4 = tmp_truth_name_1 == 0 ? NUITKA_BOOL_FALSE : NUITKA_BOOL_TRUE;
        if (tmp_condition_result_4 == NUITKA_BOOL_TRUE) {
            goto condexpr_true_1;
        } else {
            goto condexpr_false_1;
        }
        condexpr_true_1:;
        tmp_add_expr_right_4 = mod_consts[112];
        goto condexpr_end_1;
        condexpr_false_1:;
        tmp_add_expr_right_4 = mod_consts[113];
        condexpr_end_1:;
        tmp_stop_value_1 = BINARY_OPERATION_ADD_OBJECT_OBJECT_LONG(tmp_add_expr_left_4, tmp_add_expr_right_4);
        if (tmp_stop_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 269;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_subscript_value_3 = MAKE_SLICE_OBJECT1(tmp_stop_value_1);
        Py_DECREF(tmp_stop_value_1);
        assert(!(tmp_subscript_value_3 == NULL));
        tmp_add_expr_left_3 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_5, tmp_subscript_value_3);
        Py_DECREF(tmp_subscript_value_3);
        if (tmp_add_expr_left_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 269;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_right_3 = mod_consts[114];
        tmp_assign_source_5 = BINARY_OPERATION_ADD_OBJECT_OBJECT_UNICODE(tmp_add_expr_left_3, tmp_add_expr_right_3);
        Py_DECREF(tmp_add_expr_left_3);
        if (tmp_assign_source_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 269;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = par_line;
            assert(old != NULL);
            par_line = tmp_assign_source_5;
            Py_DECREF(old);
        }

    }
    branch_no_3:;
    {
        PyObject *tmp_assign_source_6;
        PyObject *tmp_add_expr_left_5;
        PyObject *tmp_add_expr_right_5;
        PyObject *tmp_add_expr_left_6;
        PyObject *tmp_add_expr_right_6;
        PyObject *tmp_mult_expr_left_1;
        PyObject *tmp_mult_expr_right_1;
        PyObject *tmp_sub_expr_left_3;
        PyObject *tmp_sub_expr_right_3;
        PyObject *tmp_add_expr_left_7;
        nuitka_digit tmp_add_expr_right_7;
        PyObject *tmp_len_arg_4;
        PyObject *tmp_called_value_4;
        PyObject *tmp_args_element_value_4;
        PyObject *tmp_string_concat_values_3;
        PyObject *tmp_tuple_element_3;
        PyObject *tmp_format_value_13;
        PyObject *tmp_format_spec_13;
        if (par_line == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[96]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 271;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_add_expr_left_6 = par_line;
        tmp_mult_expr_left_1 = mod_consts[48];
        tmp_sub_expr_left_3 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

        if (unlikely(tmp_sub_expr_left_3 == NULL)) {
            tmp_sub_expr_left_3 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
        }

        if (tmp_sub_expr_left_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 271;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        if (Nuitka_Cell_GET(self->m_closure[8]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[38]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 271;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_called_value_4 = Nuitka_Cell_GET(self->m_closure[8]);
        if (par_line == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[96]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 271;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_args_element_value_4 = par_line;
        frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd->m_frame.f_lineno = 271;
        tmp_len_arg_4 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_4, tmp_args_element_value_4);
        if (tmp_len_arg_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 271;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_left_7 = BUILTIN_LEN(tstate, tmp_len_arg_4);
        Py_DECREF(tmp_len_arg_4);
        if (tmp_add_expr_left_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 271;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_right_7 = 1;
        tmp_sub_expr_right_3 = BINARY_OPERATION_ADD_OBJECT_LONG_DIGIT(tmp_add_expr_left_7, tmp_add_expr_right_7);
        Py_DECREF(tmp_add_expr_left_7);
        assert(!(tmp_sub_expr_right_3 == NULL));
        tmp_mult_expr_right_1 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_3, tmp_sub_expr_right_3);
        Py_DECREF(tmp_sub_expr_right_3);
        if (tmp_mult_expr_right_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 271;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_right_6 = BINARY_OPERATION_MULT_OBJECT_UNICODE_OBJECT(tmp_mult_expr_left_1, tmp_mult_expr_right_1);
        Py_DECREF(tmp_mult_expr_right_1);
        if (tmp_add_expr_right_6 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 271;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_add_expr_left_5 = BINARY_OPERATION_ADD_OBJECT_OBJECT_OBJECT(tmp_add_expr_left_6, tmp_add_expr_right_6);
        Py_DECREF(tmp_add_expr_right_6);
        if (tmp_add_expr_left_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 271;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        if (Nuitka_Cell_GET(self->m_closure[6]) == NULL) {
            Py_DECREF(tmp_add_expr_left_5);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 271;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }

        tmp_format_value_13 = Nuitka_Cell_GET(self->m_closure[6]);
        tmp_format_spec_13 = mod_consts[44];
        tmp_tuple_element_3 = BUILTIN_FORMAT(tstate, tmp_format_value_13, tmp_format_spec_13);
        if (tmp_tuple_element_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_5);

            exception_lineno = 271;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_string_concat_values_3 = MAKE_TUPLE_EMPTY(3);
        {
            PyObject *tmp_format_value_14;
            PyObject *tmp_expression_value_6;
            PyObject *tmp_subscript_value_4;
            PyObject *tmp_format_spec_14;
            PyObject *tmp_format_value_15;
            PyObject *tmp_format_spec_15;
            PyTuple_SET_ITEM(tmp_string_concat_values_3, 0, tmp_tuple_element_3);
            if (Nuitka_Cell_GET(self->m_closure[1]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[104]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 271;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_3;
            }

            tmp_expression_value_6 = Nuitka_Cell_GET(self->m_closure[1]);
            tmp_subscript_value_4 = mod_consts[64];
            tmp_format_value_14 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_6, tmp_subscript_value_4);
            if (tmp_format_value_14 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 271;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_3;
            }
            tmp_format_spec_14 = mod_consts[44];
            tmp_tuple_element_3 = BUILTIN_FORMAT(tstate, tmp_format_value_14, tmp_format_spec_14);
            Py_DECREF(tmp_format_value_14);
            if (tmp_tuple_element_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 271;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_3;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_3, 1, tmp_tuple_element_3);
            if (Nuitka_Cell_GET(self->m_closure[7]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 271;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_3;
            }

            tmp_format_value_15 = Nuitka_Cell_GET(self->m_closure[7]);
            tmp_format_spec_15 = mod_consts[44];
            tmp_tuple_element_3 = BUILTIN_FORMAT(tstate, tmp_format_value_15, tmp_format_spec_15);
            if (tmp_tuple_element_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 271;
                type_description_1 = "oooccccccccc";
                goto tuple_build_exception_3;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_3, 2, tmp_tuple_element_3);
        }
        goto tuple_build_noexception_3;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_3:;
        Py_DECREF(tmp_add_expr_left_5);
        Py_DECREF(tmp_string_concat_values_3);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_3:;
        tmp_add_expr_right_5 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_3);
        Py_DECREF(tmp_string_concat_values_3);
        if (tmp_add_expr_right_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_add_expr_left_5);

            exception_lineno = 271;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_6 = BINARY_OPERATION_ADD_OBJECT_OBJECT_UNICODE(tmp_add_expr_left_5, tmp_add_expr_right_5);
        Py_DECREF(tmp_add_expr_left_5);
        Py_DECREF(tmp_add_expr_right_5);
        if (tmp_assign_source_6 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 271;
            type_description_1 = "oooccccccccc";
            goto frame_exception_exit_1;
        }
        {
            PyObject *old = par_line;
            par_line = tmp_assign_source_6;
            Py_XDECREF(old);
        }

    }


    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto frame_no_exception_1;
    frame_exception_exit_1:


    if (exception_tb == NULL) {
        exception_tb = MAKE_TRACEBACK(frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd, exception_lineno);
    } else if (exception_tb->tb_frame != &frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd->m_frame) {
        exception_tb = ADD_TRACEBACK(exception_tb, frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd, exception_lineno);
    }

    // Attaches locals to frame if any.
    Nuitka_Frame_AttachLocals(
        frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd,
        type_description_1,
        par_line,
        par_index,
        var_current_line_no,
        self->m_closure[4],
        self->m_closure[5],
        self->m_closure[6],
        self->m_closure[1],
        self->m_closure[0],
        self->m_closure[7],
        self->m_closure[3],
        self->m_closure[8],
        self->m_closure[2]
    );


    // Release cached frame if used for exception.
    if (frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd == cache_frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd) {
#if _DEBUG_REFCOUNTS
        count_active_frame_cache_instances -= 1;
        count_released_frame_cache_instances += 1;
#endif
        Py_DECREF(cache_frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd);
        cache_frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd = NULL;
    }

    assertFrameObject(frame_cfbb1fd5c2fa73ae6fa06e61890dd7dd);

    // Put the previous frame back on top.
    popFrameStack(tstate);

    // Return the error.
    goto try_except_handler_1;
    frame_no_exception_1:;
    CHECK_OBJECT(par_line);
    tmp_return_value = par_line;
    Py_INCREF(tmp_return_value);
    goto try_return_handler_1;
    NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
    return NULL;
    // Return handler code:
    try_return_handler_1:;
    CHECK_OBJECT(par_line);
    Py_DECREF(par_line);
    par_line = NULL;
    CHECK_OBJECT(var_current_line_no);
    Py_DECREF(var_current_line_no);
    var_current_line_no = NULL;
    goto function_return_exit;
    // Exception handler code:
    try_except_handler_1:;
    exception_keeper_type_1 = exception_type;
    exception_keeper_value_1 = exception_value;
    exception_keeper_tb_1 = exception_tb;
    exception_keeper_lineno_1 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(par_line);
    par_line = NULL;
    Py_XDECREF(var_current_line_no);
    var_current_line_no = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_1;
    exception_value = exception_keeper_value_1;
    exception_tb = exception_keeper_tb_1;
    exception_lineno = exception_keeper_lineno_1;

    goto function_exception_exit;
    // End of try:

    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;

function_exception_exit:
    CHECK_OBJECT(par_index);
    Py_DECREF(par_index);
    assert(exception_type);
    RESTORE_ERROR_OCCURRED(tstate, exception_type, exception_value, exception_tb);

    return NULL;

function_return_exit:
   // Function cleanup code if any.
    CHECK_OBJECT(par_index);
    Py_DECREF(par_index);

   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}


static PyObject *impl_core$panic$$$function__2_panic$$$function__7_process_message(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *par_message = python_pars[0];
    PyObject *var_output = NULL;
    PyObject *var_textwrap = NULL;
    PyObject *var_line = NULL;
    PyObject *var_line2 = NULL;
    PyObject *outline_0_var_out = NULL;
    PyObject *tmp_for_loop_1__for_iterator = NULL;
    PyObject *tmp_for_loop_1__iter_value = NULL;
    PyObject *tmp_for_loop_2__for_iterator = NULL;
    PyObject *tmp_for_loop_2__iter_value = NULL;
    PyObject *tmp_listcomp_1__$0 = NULL;
    PyObject *tmp_listcomp_1__contraction = NULL;
    PyObject *tmp_listcomp_1__iter_value_0 = NULL;
    struct Nuitka_FrameObject *frame_45103d0afa02f9f8fd0f6e5356c4a2d9;
    NUITKA_MAY_BE_UNUSED char const *type_description_1 = NULL;
    PyObject *exception_type = NULL;
    PyObject *exception_value = NULL;
    PyTracebackObject *exception_tb = NULL;
    NUITKA_MAY_BE_UNUSED int exception_lineno = 0;
    bool tmp_result;
    NUITKA_MAY_BE_UNUSED nuitka_void tmp_unused;
    PyObject *exception_keeper_type_1;
    PyObject *exception_keeper_value_1;
    PyTracebackObject *exception_keeper_tb_1;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_1;
    PyObject *exception_keeper_type_2;
    PyObject *exception_keeper_value_2;
    PyTracebackObject *exception_keeper_tb_2;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_2;
    PyObject *tmp_return_value = NULL;
    PyObject *exception_keeper_type_3;
    PyObject *exception_keeper_value_3;
    PyTracebackObject *exception_keeper_tb_3;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_3;
    PyObject *exception_keeper_type_4;
    PyObject *exception_keeper_value_4;
    PyTracebackObject *exception_keeper_tb_4;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_4;
    static struct Nuitka_FrameObject *cache_frame_45103d0afa02f9f8fd0f6e5356c4a2d9 = NULL;
    PyObject *exception_keeper_type_5;
    PyObject *exception_keeper_value_5;
    PyTracebackObject *exception_keeper_tb_5;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_5;

    // Actual function body.
    {
        PyObject *tmp_assign_source_1;
        tmp_assign_source_1 = MAKE_LIST_EMPTY(0);
        assert(var_output == NULL);
        var_output = tmp_assign_source_1;
    }
    // Tried code:
    if (isFrameUnusable(cache_frame_45103d0afa02f9f8fd0f6e5356c4a2d9)) {
        Py_XDECREF(cache_frame_45103d0afa02f9f8fd0f6e5356c4a2d9);

#if _DEBUG_REFCOUNTS
        if (cache_frame_45103d0afa02f9f8fd0f6e5356c4a2d9 == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_frame_45103d0afa02f9f8fd0f6e5356c4a2d9 = MAKE_FUNCTION_FRAME(tstate, codeobj_45103d0afa02f9f8fd0f6e5356c4a2d9, module_core$panic, sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_type_description == NULL);
    frame_45103d0afa02f9f8fd0f6e5356c4a2d9 = cache_frame_45103d0afa02f9f8fd0f6e5356c4a2d9;

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackCompiledFrame(tstate, frame_45103d0afa02f9f8fd0f6e5356c4a2d9);
    assert(Py_REFCNT(frame_45103d0afa02f9f8fd0f6e5356c4a2d9) == 2);

    // Framed code:
    {
        PyObject *tmp_assign_source_2;
        PyObject *tmp_name_value_1;
        PyObject *tmp_globals_arg_value_1;
        PyObject *tmp_locals_arg_value_1;
        PyObject *tmp_fromlist_value_1;
        PyObject *tmp_level_value_1;
        tmp_name_value_1 = mod_consts[115];
        tmp_globals_arg_value_1 = (PyObject *)moduledict_core$panic;
        tmp_locals_arg_value_1 = Py_None;
        tmp_fromlist_value_1 = Py_None;
        tmp_level_value_1 = mod_consts[15];
        frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_frame.f_lineno = 299;
        tmp_assign_source_2 = IMPORT_MODULE5(tstate, tmp_name_value_1, tmp_globals_arg_value_1, tmp_locals_arg_value_1, tmp_fromlist_value_1, tmp_level_value_1);
        if (tmp_assign_source_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 299;
            type_description_1 = "ooooocccccc";
            goto frame_exception_exit_1;
        }
        assert(var_textwrap == NULL);
        var_textwrap = tmp_assign_source_2;
    }
    {
        nuitka_bool tmp_condition_result_1;
        int tmp_truth_name_1;
        if (Nuitka_Cell_GET(self->m_closure[2]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[116]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 300;
            type_description_1 = "ooooocccccc";
            goto frame_exception_exit_1;
        }

        tmp_truth_name_1 = CHECK_IF_TRUE(Nuitka_Cell_GET(self->m_closure[2]));
        if (tmp_truth_name_1 == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 300;
            type_description_1 = "ooooocccccc";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_1 = tmp_truth_name_1 == 0 ? NUITKA_BOOL_FALSE : NUITKA_BOOL_TRUE;
        if (tmp_condition_result_1 == NUITKA_BOOL_TRUE) {
            goto branch_yes_1;
        } else {
            goto branch_no_1;
        }
    }
    branch_yes_1:;
    {
        PyObject *tmp_assign_source_3;
        PyObject *tmp_iadd_expr_left_1;
        PyObject *tmp_iadd_expr_right_1;
        PyObject *tmp_string_concat_values_1;
        PyObject *tmp_tuple_element_1;
        CHECK_OBJECT(par_message);
        tmp_iadd_expr_left_1 = par_message;
        tmp_tuple_element_1 = mod_consts[117];
        tmp_string_concat_values_1 = MAKE_TUPLE_EMPTY(5);
        {
            PyObject *tmp_format_value_1;
            PyObject *tmp_called_instance_1;
            PyObject *tmp_format_spec_1;
            PyObject *tmp_format_value_2;
            PyObject *tmp_called_instance_2;
            PyObject *tmp_format_spec_2;
            PyTuple_SET_ITEM0(tmp_string_concat_values_1, 0, tmp_tuple_element_1);
            if (Nuitka_Cell_GET(self->m_closure[0]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[118]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 301;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_1;
            }

            tmp_called_instance_1 = Nuitka_Cell_GET(self->m_closure[0]);
            frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_frame.f_lineno = 301;
            tmp_format_value_1 = CALL_METHOD_WITH_SINGLE_ARG(
                tstate,
                tmp_called_instance_1,
                mod_consts[68],
                PyTuple_GET_ITEM(mod_consts[69], 0)
            );

            if (tmp_format_value_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 301;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_1;
            }
            tmp_format_spec_1 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_1, tmp_format_spec_1);
            Py_DECREF(tmp_format_value_1);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 301;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 1, tmp_tuple_element_1);
            tmp_tuple_element_1 = mod_consts[70];
            PyTuple_SET_ITEM0(tmp_string_concat_values_1, 2, tmp_tuple_element_1);
            if (Nuitka_Cell_GET(self->m_closure[0]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[118]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 301;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_1;
            }

            tmp_called_instance_2 = Nuitka_Cell_GET(self->m_closure[0]);
            frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_frame.f_lineno = 301;
            tmp_format_value_2 = CALL_METHOD_WITH_SINGLE_ARG(
                tstate,
                tmp_called_instance_2,
                mod_consts[68],
                PyTuple_GET_ITEM(mod_consts[71], 0)
            );

            if (tmp_format_value_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 301;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_1;
            }
            tmp_format_spec_2 = mod_consts[44];
            tmp_tuple_element_1 = BUILTIN_FORMAT(tstate, tmp_format_value_2, tmp_format_spec_2);
            Py_DECREF(tmp_format_value_2);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 301;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_1, 3, tmp_tuple_element_1);
            tmp_tuple_element_1 = mod_consts[119];
            PyTuple_SET_ITEM0(tmp_string_concat_values_1, 4, tmp_tuple_element_1);
        }
        goto tuple_build_noexception_1;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_1:;
        Py_DECREF(tmp_string_concat_values_1);
        goto frame_exception_exit_1;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_1:;
        tmp_iadd_expr_right_1 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_1);
        Py_DECREF(tmp_string_concat_values_1);
        if (tmp_iadd_expr_right_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 301;
            type_description_1 = "ooooocccccc";
            goto frame_exception_exit_1;
        }
        tmp_result = INPLACE_OPERATION_ADD_OBJECT_UNICODE(&tmp_iadd_expr_left_1, tmp_iadd_expr_right_1);
        Py_DECREF(tmp_iadd_expr_right_1);
        if (tmp_result == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 301;
            type_description_1 = "ooooocccccc";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_3 = tmp_iadd_expr_left_1;
        par_message = tmp_assign_source_3;

    }
    branch_no_1:;
    {
        PyObject *tmp_assign_source_4;
        PyObject *tmp_iter_arg_1;
        PyObject *tmp_called_value_1;
        PyObject *tmp_expression_value_1;
        CHECK_OBJECT(par_message);
        tmp_expression_value_1 = par_message;
        tmp_called_value_1 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_1, mod_consts[120]);
        if (tmp_called_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 302;
            type_description_1 = "ooooocccccc";
            goto frame_exception_exit_1;
        }
        frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_frame.f_lineno = 302;
        tmp_iter_arg_1 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_1, mod_consts[121]);

        Py_DECREF(tmp_called_value_1);
        if (tmp_iter_arg_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 302;
            type_description_1 = "ooooocccccc";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_4 = MAKE_ITERATOR(tstate, tmp_iter_arg_1);
        Py_DECREF(tmp_iter_arg_1);
        if (tmp_assign_source_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 302;
            type_description_1 = "ooooocccccc";
            goto frame_exception_exit_1;
        }
        assert(tmp_for_loop_1__for_iterator == NULL);
        tmp_for_loop_1__for_iterator = tmp_assign_source_4;
    }
    // Tried code:
    loop_start_1:;
    {
        PyObject *tmp_next_source_1;
        PyObject *tmp_assign_source_5;
        CHECK_OBJECT(tmp_for_loop_1__for_iterator);
        tmp_next_source_1 = tmp_for_loop_1__for_iterator;
        tmp_assign_source_5 = ITERATOR_NEXT(tmp_next_source_1);
        if (tmp_assign_source_5 == NULL) {
            if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                goto loop_end_1;
            } else {

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                type_description_1 = "ooooocccccc";
                exception_lineno = 302;
                goto try_except_handler_2;
            }
        }

        {
            PyObject *old = tmp_for_loop_1__iter_value;
            tmp_for_loop_1__iter_value = tmp_assign_source_5;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_6;
        CHECK_OBJECT(tmp_for_loop_1__iter_value);
        tmp_assign_source_6 = tmp_for_loop_1__iter_value;
        {
            PyObject *old = var_line;
            var_line = tmp_assign_source_6;
            Py_INCREF(var_line);
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_7;
        PyObject *tmp_iter_arg_2;
        PyObject *tmp_called_value_2;
        PyObject *tmp_expression_value_2;
        PyObject *tmp_args_element_value_1;
        PyObject *tmp_args_element_value_2;
        PyObject *tmp_sub_expr_left_1;
        PyObject *tmp_sub_expr_right_1;
        if (var_textwrap == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[115]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 303;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_2;
        }

        tmp_expression_value_2 = var_textwrap;
        tmp_called_value_2 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_2, mod_consts[122]);
        if (tmp_called_value_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 303;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_2;
        }
        CHECK_OBJECT(var_line);
        tmp_args_element_value_1 = var_line;
        tmp_sub_expr_left_1 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

        if (unlikely(tmp_sub_expr_left_1 == NULL)) {
            tmp_sub_expr_left_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
        }

        if (tmp_sub_expr_left_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_called_value_2);

            exception_lineno = 303;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_2;
        }
        tmp_sub_expr_right_1 = mod_consts[75];
        tmp_args_element_value_2 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_1, tmp_sub_expr_right_1);
        if (tmp_args_element_value_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_called_value_2);

            exception_lineno = 303;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_2;
        }
        frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_frame.f_lineno = 303;
        {
            PyObject *call_args[] = {tmp_args_element_value_1, tmp_args_element_value_2};
            tmp_iter_arg_2 = CALL_FUNCTION_WITH_ARGS2(tstate, tmp_called_value_2, call_args);
        }

        Py_DECREF(tmp_called_value_2);
        Py_DECREF(tmp_args_element_value_2);
        if (tmp_iter_arg_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 303;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_2;
        }
        tmp_assign_source_7 = MAKE_ITERATOR(tstate, tmp_iter_arg_2);
        Py_DECREF(tmp_iter_arg_2);
        if (tmp_assign_source_7 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 303;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_2;
        }
        {
            PyObject *old = tmp_for_loop_2__for_iterator;
            tmp_for_loop_2__for_iterator = tmp_assign_source_7;
            Py_XDECREF(old);
        }

    }
    // Tried code:
    loop_start_2:;
    {
        PyObject *tmp_next_source_2;
        PyObject *tmp_assign_source_8;
        CHECK_OBJECT(tmp_for_loop_2__for_iterator);
        tmp_next_source_2 = tmp_for_loop_2__for_iterator;
        tmp_assign_source_8 = ITERATOR_NEXT(tmp_next_source_2);
        if (tmp_assign_source_8 == NULL) {
            if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                goto loop_end_2;
            } else {

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                type_description_1 = "ooooocccccc";
                exception_lineno = 303;
                goto try_except_handler_3;
            }
        }

        {
            PyObject *old = tmp_for_loop_2__iter_value;
            tmp_for_loop_2__iter_value = tmp_assign_source_8;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_9;
        CHECK_OBJECT(tmp_for_loop_2__iter_value);
        tmp_assign_source_9 = tmp_for_loop_2__iter_value;
        {
            PyObject *old = var_line2;
            var_line2 = tmp_assign_source_9;
            Py_INCREF(var_line2);
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_called_value_3;
        PyObject *tmp_expression_value_3;
        PyObject *tmp_call_result_1;
        PyObject *tmp_args_element_value_3;
        PyObject *tmp_string_concat_values_2;
        PyObject *tmp_tuple_element_2;
        PyObject *tmp_format_value_3;
        PyObject *tmp_format_spec_3;
        if (var_output == NULL) {

            FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[90]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 304;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_3;
        }

        tmp_expression_value_3 = var_output;
        tmp_called_value_3 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_3, mod_consts[123]);
        if (tmp_called_value_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 304;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_3;
        }
        if (Nuitka_Cell_GET(self->m_closure[3]) == NULL) {
            Py_DECREF(tmp_called_value_3);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[43]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 304;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_3;
        }

        tmp_format_value_3 = Nuitka_Cell_GET(self->m_closure[3]);
        tmp_format_spec_3 = mod_consts[44];
        tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_3, tmp_format_spec_3);
        if (tmp_tuple_element_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_called_value_3);

            exception_lineno = 304;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_3;
        }
        tmp_string_concat_values_2 = MAKE_TUPLE_EMPTY(9);
        {
            PyObject *tmp_format_value_4;
            PyObject *tmp_expression_value_4;
            PyObject *tmp_subscript_value_1;
            PyObject *tmp_format_spec_4;
            PyObject *tmp_format_value_5;
            PyObject *tmp_format_spec_5;
            PyObject *tmp_format_value_6;
            PyObject *tmp_called_value_4;
            PyObject *tmp_expression_value_5;
            PyObject *tmp_args_element_value_4;
            PyObject *tmp_sub_expr_left_2;
            PyObject *tmp_sub_expr_right_2;
            PyObject *tmp_format_spec_6;
            PyObject *tmp_format_value_7;
            PyObject *tmp_format_spec_7;
            PyObject *tmp_format_value_8;
            PyObject *tmp_expression_value_6;
            PyObject *tmp_subscript_value_2;
            PyObject *tmp_format_spec_8;
            PyObject *tmp_format_value_9;
            PyObject *tmp_format_spec_9;
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 0, tmp_tuple_element_2);
            if (Nuitka_Cell_GET(self->m_closure[1]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[104]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }

            tmp_expression_value_4 = Nuitka_Cell_GET(self->m_closure[1]);
            tmp_subscript_value_1 = mod_consts[64];
            tmp_format_value_4 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_4, tmp_subscript_value_1);
            if (tmp_format_value_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }
            tmp_format_spec_4 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_4, tmp_format_spec_4);
            Py_DECREF(tmp_format_value_4);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 1, tmp_tuple_element_2);
            if (Nuitka_Cell_GET(self->m_closure[4]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }

            tmp_format_value_5 = Nuitka_Cell_GET(self->m_closure[4]);
            tmp_format_spec_5 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_5, tmp_format_spec_5);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 2, tmp_tuple_element_2);
            tmp_tuple_element_2 = mod_consts[48];
            PyTuple_SET_ITEM0(tmp_string_concat_values_2, 3, tmp_tuple_element_2);
            CHECK_OBJECT(var_line2);
            tmp_expression_value_5 = var_line2;
            tmp_called_value_4 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_5, mod_consts[124]);
            if (tmp_called_value_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }
            tmp_sub_expr_left_2 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50]);

            if (unlikely(tmp_sub_expr_left_2 == NULL)) {
                tmp_sub_expr_left_2 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[50]);
            }

            if (tmp_sub_expr_left_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_called_value_4);

                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }
            tmp_sub_expr_right_2 = mod_consts[75];
            tmp_args_element_value_4 = BINARY_OPERATION_SUB_OBJECT_OBJECT_LONG(tmp_sub_expr_left_2, tmp_sub_expr_right_2);
            if (tmp_args_element_value_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                Py_DECREF(tmp_called_value_4);

                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }
            frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_frame.f_lineno = 304;
            tmp_format_value_6 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_4, tmp_args_element_value_4);
            Py_DECREF(tmp_called_value_4);
            Py_DECREF(tmp_args_element_value_4);
            if (tmp_format_value_6 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }
            tmp_format_spec_6 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_6, tmp_format_spec_6);
            Py_DECREF(tmp_format_value_6);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 4, tmp_tuple_element_2);
            tmp_tuple_element_2 = mod_consts[48];
            PyTuple_SET_ITEM0(tmp_string_concat_values_2, 5, tmp_tuple_element_2);
            if (Nuitka_Cell_GET(self->m_closure[3]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[43]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }

            tmp_format_value_7 = Nuitka_Cell_GET(self->m_closure[3]);
            tmp_format_spec_7 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_7, tmp_format_spec_7);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 6, tmp_tuple_element_2);
            if (Nuitka_Cell_GET(self->m_closure[1]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[104]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }

            tmp_expression_value_6 = Nuitka_Cell_GET(self->m_closure[1]);
            tmp_subscript_value_2 = mod_consts[64];
            tmp_format_value_8 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_6, tmp_subscript_value_2);
            if (tmp_format_value_8 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }
            tmp_format_spec_8 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_8, tmp_format_spec_8);
            Py_DECREF(tmp_format_value_8);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 7, tmp_tuple_element_2);
            if (Nuitka_Cell_GET(self->m_closure[4]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }

            tmp_format_value_9 = Nuitka_Cell_GET(self->m_closure[4]);
            tmp_format_spec_9 = mod_consts[44];
            tmp_tuple_element_2 = BUILTIN_FORMAT(tstate, tmp_format_value_9, tmp_format_spec_9);
            if (tmp_tuple_element_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 304;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_2;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_2, 8, tmp_tuple_element_2);
        }
        goto tuple_build_noexception_2;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_2:;
        Py_DECREF(tmp_called_value_3);
        Py_DECREF(tmp_string_concat_values_2);
        goto try_except_handler_3;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_2:;
        tmp_args_element_value_3 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_2);
        Py_DECREF(tmp_string_concat_values_2);
        if (tmp_args_element_value_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_called_value_3);

            exception_lineno = 304;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_3;
        }
        frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_frame.f_lineno = 304;
        tmp_call_result_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_3, tmp_args_element_value_3);
        Py_DECREF(tmp_called_value_3);
        Py_DECREF(tmp_args_element_value_3);
        if (tmp_call_result_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 304;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_3;
        }
        Py_DECREF(tmp_call_result_1);
    }
    if (CONSIDER_THREADING(tstate) == false) {
        assert(HAS_ERROR_OCCURRED(tstate));

        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


        exception_lineno = 303;
        type_description_1 = "ooooocccccc";
        goto try_except_handler_3;
    }
    goto loop_start_2;
    loop_end_2:;
    goto try_end_1;
    // Exception handler code:
    try_except_handler_3:;
    exception_keeper_type_1 = exception_type;
    exception_keeper_value_1 = exception_value;
    exception_keeper_tb_1 = exception_tb;
    exception_keeper_lineno_1 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(tmp_for_loop_2__iter_value);
    tmp_for_loop_2__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_2__for_iterator);
    Py_DECREF(tmp_for_loop_2__for_iterator);
    tmp_for_loop_2__for_iterator = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_1;
    exception_value = exception_keeper_value_1;
    exception_tb = exception_keeper_tb_1;
    exception_lineno = exception_keeper_lineno_1;

    goto try_except_handler_2;
    // End of try:
    try_end_1:;
    Py_XDECREF(tmp_for_loop_2__iter_value);
    tmp_for_loop_2__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_2__for_iterator);
    Py_DECREF(tmp_for_loop_2__for_iterator);
    tmp_for_loop_2__for_iterator = NULL;
    if (CONSIDER_THREADING(tstate) == false) {
        assert(HAS_ERROR_OCCURRED(tstate));

        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


        exception_lineno = 302;
        type_description_1 = "ooooocccccc";
        goto try_except_handler_2;
    }
    goto loop_start_1;
    loop_end_1:;
    goto try_end_2;
    // Exception handler code:
    try_except_handler_2:;
    exception_keeper_type_2 = exception_type;
    exception_keeper_value_2 = exception_value;
    exception_keeper_tb_2 = exception_tb;
    exception_keeper_lineno_2 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(tmp_for_loop_1__iter_value);
    tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_1__for_iterator);
    Py_DECREF(tmp_for_loop_1__for_iterator);
    tmp_for_loop_1__for_iterator = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_2;
    exception_value = exception_keeper_value_2;
    exception_tb = exception_keeper_tb_2;
    exception_lineno = exception_keeper_lineno_2;

    goto frame_exception_exit_1;
    // End of try:
    try_end_2:;
    Py_XDECREF(tmp_for_loop_1__iter_value);
    tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(tmp_for_loop_1__for_iterator);
    Py_DECREF(tmp_for_loop_1__for_iterator);
    tmp_for_loop_1__for_iterator = NULL;
    {
        nuitka_bool tmp_condition_result_2;
        int tmp_truth_name_2;
        if (Nuitka_Cell_GET(self->m_closure[2]) == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[116]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 305;
            type_description_1 = "ooooocccccc";
            goto frame_exception_exit_1;
        }

        tmp_truth_name_2 = CHECK_IF_TRUE(Nuitka_Cell_GET(self->m_closure[2]));
        if (tmp_truth_name_2 == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 305;
            type_description_1 = "ooooocccccc";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_2 = tmp_truth_name_2 == 0 ? NUITKA_BOOL_FALSE : NUITKA_BOOL_TRUE;
        if (tmp_condition_result_2 == NUITKA_BOOL_TRUE) {
            goto branch_yes_2;
        } else {
            goto branch_no_2;
        }
    }
    branch_yes_2:;
    // Tried code:
    {
        PyObject *tmp_assign_source_10;
        PyObject *tmp_iter_arg_3;
        if (var_output == NULL) {

            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[90]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 305;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_4;
        }

        tmp_iter_arg_3 = var_output;
        tmp_assign_source_10 = MAKE_ITERATOR(tstate, tmp_iter_arg_3);
        if (tmp_assign_source_10 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 305;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_4;
        }
        assert(tmp_listcomp_1__$0 == NULL);
        tmp_listcomp_1__$0 = tmp_assign_source_10;
    }
    {
        PyObject *tmp_assign_source_11;
        tmp_assign_source_11 = MAKE_LIST_EMPTY(0);
        assert(tmp_listcomp_1__contraction == NULL);
        tmp_listcomp_1__contraction = tmp_assign_source_11;
    }
    // Tried code:
    loop_start_3:;
    {
        PyObject *tmp_next_source_3;
        PyObject *tmp_assign_source_12;
        CHECK_OBJECT(tmp_listcomp_1__$0);
        tmp_next_source_3 = tmp_listcomp_1__$0;
        tmp_assign_source_12 = ITERATOR_NEXT(tmp_next_source_3);
        if (tmp_assign_source_12 == NULL) {
            if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                goto loop_end_3;
            } else {

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                type_description_1 = "ooooocccccc";
                exception_lineno = 305;
                goto try_except_handler_5;
            }
        }

        {
            PyObject *old = tmp_listcomp_1__iter_value_0;
            tmp_listcomp_1__iter_value_0 = tmp_assign_source_12;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_13;
        CHECK_OBJECT(tmp_listcomp_1__iter_value_0);
        tmp_assign_source_13 = tmp_listcomp_1__iter_value_0;
        {
            PyObject *old = outline_0_var_out;
            outline_0_var_out = tmp_assign_source_13;
            Py_INCREF(outline_0_var_out);
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_append_list_1;
        PyObject *tmp_append_value_1;
        PyObject *tmp_called_value_5;
        PyObject *tmp_expression_value_7;
        PyObject *tmp_args_element_value_5;
        PyObject *tmp_string_concat_values_3;
        PyObject *tmp_tuple_element_3;
        PyObject *tmp_args_element_value_6;
        PyObject *tmp_string_concat_values_4;
        PyObject *tmp_tuple_element_4;
        PyObject *tmp_format_value_12;
        PyObject *tmp_format_spec_12;
        CHECK_OBJECT(tmp_listcomp_1__contraction);
        tmp_append_list_1 = tmp_listcomp_1__contraction;
        CHECK_OBJECT(outline_0_var_out);
        tmp_expression_value_7 = outline_0_var_out;
        tmp_called_value_5 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_7, mod_consts[72]);
        if (tmp_called_value_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 305;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_5;
        }
        tmp_tuple_element_3 = mod_consts[125];
        tmp_string_concat_values_3 = MAKE_TUPLE_EMPTY(5);
        {
            PyObject *tmp_format_value_10;
            PyObject *tmp_called_instance_3;
            PyObject *tmp_format_spec_10;
            PyObject *tmp_format_value_11;
            PyObject *tmp_called_instance_4;
            PyObject *tmp_format_spec_11;
            PyTuple_SET_ITEM0(tmp_string_concat_values_3, 0, tmp_tuple_element_3);
            if (Nuitka_Cell_GET(self->m_closure[0]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[118]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_3;
            }

            tmp_called_instance_3 = Nuitka_Cell_GET(self->m_closure[0]);
            frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_frame.f_lineno = 305;
            tmp_format_value_10 = CALL_METHOD_WITH_SINGLE_ARG(
                tstate,
                tmp_called_instance_3,
                mod_consts[68],
                PyTuple_GET_ITEM(mod_consts[69], 0)
            );

            if (tmp_format_value_10 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_3;
            }
            tmp_format_spec_10 = mod_consts[44];
            tmp_tuple_element_3 = BUILTIN_FORMAT(tstate, tmp_format_value_10, tmp_format_spec_10);
            Py_DECREF(tmp_format_value_10);
            if (tmp_tuple_element_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_3;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_3, 1, tmp_tuple_element_3);
            tmp_tuple_element_3 = mod_consts[70];
            PyTuple_SET_ITEM0(tmp_string_concat_values_3, 2, tmp_tuple_element_3);
            if (Nuitka_Cell_GET(self->m_closure[0]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[118]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_3;
            }

            tmp_called_instance_4 = Nuitka_Cell_GET(self->m_closure[0]);
            frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_frame.f_lineno = 305;
            tmp_format_value_11 = CALL_METHOD_WITH_SINGLE_ARG(
                tstate,
                tmp_called_instance_4,
                mod_consts[68],
                PyTuple_GET_ITEM(mod_consts[71], 0)
            );

            if (tmp_format_value_11 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_3;
            }
            tmp_format_spec_11 = mod_consts[44];
            tmp_tuple_element_3 = BUILTIN_FORMAT(tstate, tmp_format_value_11, tmp_format_spec_11);
            Py_DECREF(tmp_format_value_11);
            if (tmp_tuple_element_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_3;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_3, 3, tmp_tuple_element_3);
            tmp_tuple_element_3 = mod_consts[126];
            PyTuple_SET_ITEM0(tmp_string_concat_values_3, 4, tmp_tuple_element_3);
        }
        goto tuple_build_noexception_3;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_3:;
        Py_DECREF(tmp_called_value_5);
        Py_DECREF(tmp_string_concat_values_3);
        goto try_except_handler_5;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_3:;
        tmp_args_element_value_5 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_3);
        Py_DECREF(tmp_string_concat_values_3);
        if (tmp_args_element_value_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_called_value_5);

            exception_lineno = 305;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_5;
        }
        if (Nuitka_Cell_GET(self->m_closure[5]) == NULL) {
            Py_DECREF(tmp_called_value_5);
            Py_DECREF(tmp_args_element_value_5);
            FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[127]);
            exception_tb = NULL;
            NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
            CHAIN_EXCEPTION(tstate, exception_value);

            exception_lineno = 305;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_5;
        }

        tmp_format_value_12 = Nuitka_Cell_GET(self->m_closure[5]);
        tmp_format_spec_12 = mod_consts[44];
        tmp_tuple_element_4 = BUILTIN_FORMAT(tstate, tmp_format_value_12, tmp_format_spec_12);
        if (tmp_tuple_element_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_called_value_5);
            Py_DECREF(tmp_args_element_value_5);

            exception_lineno = 305;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_5;
        }
        tmp_string_concat_values_4 = MAKE_TUPLE_EMPTY(7);
        {
            PyObject *tmp_format_value_13;
            PyObject *tmp_called_instance_5;
            PyObject *tmp_format_spec_13;
            PyObject *tmp_format_value_14;
            PyObject *tmp_called_instance_6;
            PyObject *tmp_format_spec_14;
            PyObject *tmp_format_value_15;
            PyObject *tmp_format_spec_15;
            PyTuple_SET_ITEM(tmp_string_concat_values_4, 0, tmp_tuple_element_4);
            tmp_tuple_element_4 = mod_consts[125];
            PyTuple_SET_ITEM0(tmp_string_concat_values_4, 1, tmp_tuple_element_4);
            if (Nuitka_Cell_GET(self->m_closure[0]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[118]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_4;
            }

            tmp_called_instance_5 = Nuitka_Cell_GET(self->m_closure[0]);
            frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_frame.f_lineno = 305;
            tmp_format_value_13 = CALL_METHOD_WITH_SINGLE_ARG(
                tstate,
                tmp_called_instance_5,
                mod_consts[68],
                PyTuple_GET_ITEM(mod_consts[69], 0)
            );

            if (tmp_format_value_13 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_4;
            }
            tmp_format_spec_13 = mod_consts[44];
            tmp_tuple_element_4 = BUILTIN_FORMAT(tstate, tmp_format_value_13, tmp_format_spec_13);
            Py_DECREF(tmp_format_value_13);
            if (tmp_tuple_element_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_4;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_4, 2, tmp_tuple_element_4);
            tmp_tuple_element_4 = mod_consts[70];
            PyTuple_SET_ITEM0(tmp_string_concat_values_4, 3, tmp_tuple_element_4);
            if (Nuitka_Cell_GET(self->m_closure[0]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[118]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_4;
            }

            tmp_called_instance_6 = Nuitka_Cell_GET(self->m_closure[0]);
            frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_frame.f_lineno = 305;
            tmp_format_value_14 = CALL_METHOD_WITH_SINGLE_ARG(
                tstate,
                tmp_called_instance_6,
                mod_consts[68],
                PyTuple_GET_ITEM(mod_consts[71], 0)
            );

            if (tmp_format_value_14 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_4;
            }
            tmp_format_spec_14 = mod_consts[44];
            tmp_tuple_element_4 = BUILTIN_FORMAT(tstate, tmp_format_value_14, tmp_format_spec_14);
            Py_DECREF(tmp_format_value_14);
            if (tmp_tuple_element_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_4;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_4, 4, tmp_tuple_element_4);
            tmp_tuple_element_4 = mod_consts[126];
            PyTuple_SET_ITEM0(tmp_string_concat_values_4, 5, tmp_tuple_element_4);
            if (Nuitka_Cell_GET(self->m_closure[4]) == NULL) {

                FORMAT_UNBOUND_CLOSURE_ERROR(&exception_type, &exception_value, mod_consts[47]);
                exception_tb = NULL;
                NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
                CHAIN_EXCEPTION(tstate, exception_value);

                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_4;
            }

            tmp_format_value_15 = Nuitka_Cell_GET(self->m_closure[4]);
            tmp_format_spec_15 = mod_consts[44];
            tmp_tuple_element_4 = BUILTIN_FORMAT(tstate, tmp_format_value_15, tmp_format_spec_15);
            if (tmp_tuple_element_4 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 305;
                type_description_1 = "ooooocccccc";
                goto tuple_build_exception_4;
            }
            PyTuple_SET_ITEM(tmp_string_concat_values_4, 6, tmp_tuple_element_4);
        }
        goto tuple_build_noexception_4;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_4:;
        Py_DECREF(tmp_called_value_5);
        Py_DECREF(tmp_args_element_value_5);
        Py_DECREF(tmp_string_concat_values_4);
        goto try_except_handler_5;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_4:;
        tmp_args_element_value_6 = PyUnicode_Join(mod_consts[44], tmp_string_concat_values_4);
        Py_DECREF(tmp_string_concat_values_4);
        if (tmp_args_element_value_6 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_called_value_5);
            Py_DECREF(tmp_args_element_value_5);

            exception_lineno = 305;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_5;
        }
        frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_frame.f_lineno = 305;
        {
            PyObject *call_args[] = {tmp_args_element_value_5, tmp_args_element_value_6};
            tmp_append_value_1 = CALL_FUNCTION_WITH_ARGS2(tstate, tmp_called_value_5, call_args);
        }

        Py_DECREF(tmp_called_value_5);
        Py_DECREF(tmp_args_element_value_5);
        Py_DECREF(tmp_args_element_value_6);
        if (tmp_append_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 305;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_5;
        }
        tmp_result = LIST_APPEND1(tmp_append_list_1, tmp_append_value_1);
        if (tmp_result == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 305;
            type_description_1 = "ooooocccccc";
            goto try_except_handler_5;
        }
    }
    if (CONSIDER_THREADING(tstate) == false) {
        assert(HAS_ERROR_OCCURRED(tstate));

        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


        exception_lineno = 305;
        type_description_1 = "ooooocccccc";
        goto try_except_handler_5;
    }
    goto loop_start_3;
    loop_end_3:;
    CHECK_OBJECT(tmp_listcomp_1__contraction);
    tmp_return_value = tmp_listcomp_1__contraction;
    Py_INCREF(tmp_return_value);
    goto try_return_handler_5;
    NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
    return NULL;
    // Return handler code:
    try_return_handler_5:;
    CHECK_OBJECT(tmp_listcomp_1__$0);
    Py_DECREF(tmp_listcomp_1__$0);
    tmp_listcomp_1__$0 = NULL;
    CHECK_OBJECT(tmp_listcomp_1__contraction);
    Py_DECREF(tmp_listcomp_1__contraction);
    tmp_listcomp_1__contraction = NULL;
    Py_XDECREF(tmp_listcomp_1__iter_value_0);
    tmp_listcomp_1__iter_value_0 = NULL;
    goto try_return_handler_4;
    // Exception handler code:
    try_except_handler_5:;
    exception_keeper_type_3 = exception_type;
    exception_keeper_value_3 = exception_value;
    exception_keeper_tb_3 = exception_tb;
    exception_keeper_lineno_3 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    CHECK_OBJECT(tmp_listcomp_1__$0);
    Py_DECREF(tmp_listcomp_1__$0);
    tmp_listcomp_1__$0 = NULL;
    CHECK_OBJECT(tmp_listcomp_1__contraction);
    Py_DECREF(tmp_listcomp_1__contraction);
    tmp_listcomp_1__contraction = NULL;
    Py_XDECREF(tmp_listcomp_1__iter_value_0);
    tmp_listcomp_1__iter_value_0 = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_3;
    exception_value = exception_keeper_value_3;
    exception_tb = exception_keeper_tb_3;
    exception_lineno = exception_keeper_lineno_3;

    goto try_except_handler_4;
    // End of try:
    NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
    return NULL;
    // Return handler code:
    try_return_handler_4:;
    Py_XDECREF(outline_0_var_out);
    outline_0_var_out = NULL;
    goto outline_result_1;
    // Exception handler code:
    try_except_handler_4:;
    exception_keeper_type_4 = exception_type;
    exception_keeper_value_4 = exception_value;
    exception_keeper_tb_4 = exception_tb;
    exception_keeper_lineno_4 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(outline_0_var_out);
    outline_0_var_out = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_4;
    exception_value = exception_keeper_value_4;
    exception_tb = exception_keeper_tb_4;
    exception_lineno = exception_keeper_lineno_4;

    goto outline_exception_1;
    // End of try:
    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;
    outline_exception_1:;
    exception_lineno = 305;
    goto frame_exception_exit_1;
    outline_result_1:;
    goto frame_return_exit_1;
    branch_no_2:;
    if (var_output == NULL) {

        FORMAT_UNBOUND_LOCAL_ERROR(&exception_type, &exception_value, mod_consts[90]);
        exception_tb = NULL;
        NORMALIZE_EXCEPTION(tstate, &exception_type, &exception_value, &exception_tb);
        CHAIN_EXCEPTION(tstate, exception_value);

        exception_lineno = 306;
        type_description_1 = "ooooocccccc";
        goto frame_exception_exit_1;
    }

    tmp_return_value = var_output;
    Py_INCREF(tmp_return_value);
    goto frame_return_exit_1;


    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto frame_no_exception_1;
    frame_return_exit_1:

    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto try_return_handler_1;
    frame_exception_exit_1:


    if (exception_tb == NULL) {
        exception_tb = MAKE_TRACEBACK(frame_45103d0afa02f9f8fd0f6e5356c4a2d9, exception_lineno);
    } else if (exception_tb->tb_frame != &frame_45103d0afa02f9f8fd0f6e5356c4a2d9->m_frame) {
        exception_tb = ADD_TRACEBACK(exception_tb, frame_45103d0afa02f9f8fd0f6e5356c4a2d9, exception_lineno);
    }

    // Attaches locals to frame if any.
    Nuitka_Frame_AttachLocals(
        frame_45103d0afa02f9f8fd0f6e5356c4a2d9,
        type_description_1,
        par_message,
        var_output,
        var_textwrap,
        var_line,
        var_line2,
        self->m_closure[2],
        self->m_closure[0],
        self->m_closure[3],
        self->m_closure[1],
        self->m_closure[4],
        self->m_closure[5]
    );


    // Release cached frame if used for exception.
    if (frame_45103d0afa02f9f8fd0f6e5356c4a2d9 == cache_frame_45103d0afa02f9f8fd0f6e5356c4a2d9) {
#if _DEBUG_REFCOUNTS
        count_active_frame_cache_instances -= 1;
        count_released_frame_cache_instances += 1;
#endif
        Py_DECREF(cache_frame_45103d0afa02f9f8fd0f6e5356c4a2d9);
        cache_frame_45103d0afa02f9f8fd0f6e5356c4a2d9 = NULL;
    }

    assertFrameObject(frame_45103d0afa02f9f8fd0f6e5356c4a2d9);

    // Put the previous frame back on top.
    popFrameStack(tstate);

    // Return the error.
    goto try_except_handler_1;
    frame_no_exception_1:;
    NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
    return NULL;
    // Return handler code:
    try_return_handler_1:;
    CHECK_OBJECT(par_message);
    Py_DECREF(par_message);
    par_message = NULL;
    Py_XDECREF(var_output);
    var_output = NULL;
    Py_XDECREF(var_textwrap);
    var_textwrap = NULL;
    Py_XDECREF(var_line);
    var_line = NULL;
    Py_XDECREF(var_line2);
    var_line2 = NULL;
    goto function_return_exit;
    // Exception handler code:
    try_except_handler_1:;
    exception_keeper_type_5 = exception_type;
    exception_keeper_value_5 = exception_value;
    exception_keeper_tb_5 = exception_tb;
    exception_keeper_lineno_5 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(par_message);
    par_message = NULL;
    Py_XDECREF(var_output);
    var_output = NULL;
    Py_XDECREF(var_textwrap);
    var_textwrap = NULL;
    Py_XDECREF(var_line);
    var_line = NULL;
    Py_XDECREF(var_line2);
    var_line2 = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_5;
    exception_value = exception_keeper_value_5;
    exception_tb = exception_keeper_tb_5;
    exception_lineno = exception_keeper_lineno_5;

    goto function_exception_exit;
    // End of try:

    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;

function_exception_exit:

    assert(exception_type);
    RESTORE_ERROR_OCCURRED(tstate, exception_type, exception_value, exception_tb);

    return NULL;

function_return_exit:
   // Function cleanup code if any.


   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}



static PyObject *MAKE_FUNCTION_core$panic$$$function__1_highlight_code(PyObject *annotations) {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_core$panic$$$function__1_highlight_code,
        mod_consts[264],
#if PYTHON_VERSION >= 0x300
        NULL,
#endif
        codeobj_ad821e1969a34aa46a58d160b9d25a85,
        NULL,
#if PYTHON_VERSION >= 0x300
        NULL,
        annotations,
#endif
        module_core$panic,
        NULL,
        NULL,
        0
    );


    return (PyObject *)result;
}



static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic(PyObject *kw_defaults, PyObject *annotations) {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_core$panic$$$function__2_panic,
        mod_consts[274],
#if PYTHON_VERSION >= 0x300
        NULL,
#endif
        codeobj_8318cdda338d5f423c718cf0c36f6739,
        NULL,
#if PYTHON_VERSION >= 0x300
        kw_defaults,
        annotations,
#endif
        module_core$panic,
        NULL,
        NULL,
        0
    );


    return (PyObject *)result;
}



static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__1_calculate_skip_ammout(PyObject *annotations, struct Nuitka_CellObject **closure) {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_core$panic$$$function__2_panic$$$function__1_calculate_skip_ammout,
        mod_consts[27],
#if PYTHON_VERSION >= 0x300
        mod_consts[28],
#endif
        codeobj_023af1584b736d71b82c14535d5153cb,
        NULL,
#if PYTHON_VERSION >= 0x300
        NULL,
        annotations,
#endif
        module_core$panic,
        NULL,
        closure,
        1
    );


    return (PyObject *)result;
}



static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__2_count_spaces(PyObject *annotations, struct Nuitka_CellObject **closure) {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_core$panic$$$function__2_panic$$$function__2_count_spaces,
        mod_consts[29],
#if PYTHON_VERSION >= 0x300
        mod_consts[30],
#endif
        codeobj_14702094d157de72a92e00898e7cc298,
        NULL,
#if PYTHON_VERSION >= 0x300
        NULL,
        annotations,
#endif
        module_core$panic,
        NULL,
        closure,
        3
    );


    return (PyObject *)result;
}



static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__3_line_without_spaces(PyObject *annotations, struct Nuitka_CellObject **closure) {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_core$panic$$$function__2_panic$$$function__3_line_without_spaces,
        mod_consts[32],
#if PYTHON_VERSION >= 0x300
        mod_consts[33],
#endif
        codeobj_2edbc9deccd9aaf2cd319e276c33377e,
        NULL,
#if PYTHON_VERSION >= 0x300
        NULL,
        annotations,
#endif
        module_core$panic,
        NULL,
        closure,
        2
    );


    return (PyObject *)result;
}



static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__4_mark_all(PyObject *annotations, struct Nuitka_CellObject **closure) {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_core$panic$$$function__2_panic$$$function__4_mark_all,
        mod_consts[35],
#if PYTHON_VERSION >= 0x300
        mod_consts[36],
#endif
        codeobj_e1d27883b2455e4c949dff371c0a8ceb,
        NULL,
#if PYTHON_VERSION >= 0x300
        NULL,
        annotations,
#endif
        module_core$panic,
        NULL,
        closure,
        11
    );


    return (PyObject *)result;
}



static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__5_s_u(PyObject *annotations) {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_core$panic$$$function__2_panic$$$function__5_s_u,
        mod_consts[38],
#if PYTHON_VERSION >= 0x300
        mod_consts[39],
#endif
        codeobj_7bf646c481fc4ce8df0b213af78a07e9,
        NULL,
#if PYTHON_VERSION >= 0x300
        NULL,
        annotations,
#endif
        module_core$panic,
        NULL,
        NULL,
        0
    );


    return (PyObject *)result;
}



static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__6_process_lines(PyObject *annotations, struct Nuitka_CellObject **closure) {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_core$panic$$$function__2_panic$$$function__6_process_lines,
        mod_consts[41],
#if PYTHON_VERSION >= 0x300
        mod_consts[42],
#endif
        codeobj_cfbb1fd5c2fa73ae6fa06e61890dd7dd,
        NULL,
#if PYTHON_VERSION >= 0x300
        NULL,
        annotations,
#endif
        module_core$panic,
        NULL,
        closure,
        9
    );


    return (PyObject *)result;
}



static PyObject *MAKE_FUNCTION_core$panic$$$function__2_panic$$$function__7_process_message(PyObject *annotations, struct Nuitka_CellObject **closure) {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_core$panic$$$function__2_panic$$$function__7_process_message,
        mod_consts[77],
#if PYTHON_VERSION >= 0x300
        mod_consts[78],
#endif
        codeobj_45103d0afa02f9f8fd0f6e5356c4a2d9,
        NULL,
#if PYTHON_VERSION >= 0x300
        NULL,
        annotations,
#endif
        module_core$panic,
        NULL,
        closure,
        6
    );


    return (PyObject *)result;
}


extern void _initCompiledCellType();
extern void _initCompiledGeneratorType();
extern void _initCompiledFunctionType();
extern void _initCompiledMethodType();
extern void _initCompiledFrameType();

extern PyTypeObject Nuitka_Loader_Type;

#ifdef _NUITKA_PLUGIN_DILL_ENABLED
// Provide a way to create find a function via its C code and create it back
// in another process, useful for multiprocessing extensions like dill
extern void registerDillPluginTables(PyThreadState *tstate, char const *module_name, PyMethodDef *reduce_compiled_function, PyMethodDef *create_compiled_function);

static function_impl_code const function_table_core$panic[] = {
    impl_core$panic$$$function__2_panic$$$function__1_calculate_skip_ammout,
    impl_core$panic$$$function__2_panic$$$function__2_count_spaces,
    impl_core$panic$$$function__2_panic$$$function__3_line_without_spaces,
    impl_core$panic$$$function__2_panic$$$function__4_mark_all,
    impl_core$panic$$$function__2_panic$$$function__5_s_u,
    impl_core$panic$$$function__2_panic$$$function__6_process_lines,
    impl_core$panic$$$function__2_panic$$$function__7_process_message,
    impl_core$panic$$$function__1_highlight_code,
    impl_core$panic$$$function__2_panic,
    NULL
};

static PyObject *_reduce_compiled_function(PyObject *self, PyObject *args, PyObject *kwds) {
    PyObject *func;

    if (!PyArg_ParseTuple(args, "O:reduce_compiled_function", &func, NULL)) {
        return NULL;
    }

    if (Nuitka_Function_Check(func) == false) {
        PyThreadState *tstate = PyThreadState_GET();

        SET_CURRENT_EXCEPTION_TYPE0_STR(tstate, PyExc_TypeError, "not a compiled function");
        return NULL;
    }

    struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)func;

    int offset = Nuitka_Function_GetFunctionCodeIndex(function, function_table_core$panic);

    if (unlikely(offset == -1)) {
        PyThreadState *tstate = PyThreadState_GET();
#if 0
        PRINT_STRING("Looking for:");
        PRINT_ITEM(func);
        PRINT_NEW_LINE();
#endif
        SET_CURRENT_EXCEPTION_TYPE0_STR(tstate, PyExc_TypeError, "Cannot find compiled function in module.");
        return NULL;
    }

    PyObject *code_object_desc = MAKE_TUPLE_EMPTY(6);
    PyTuple_SET_ITEM0(code_object_desc, 0, function->m_code_object->co_filename);
    PyTuple_SET_ITEM0(code_object_desc, 1, function->m_code_object->co_name);
    PyTuple_SET_ITEM(code_object_desc, 2, PyLong_FromLong(function->m_code_object->co_firstlineno));
    PyTuple_SET_ITEM0(code_object_desc, 3, function->m_code_object->co_varnames);
    PyTuple_SET_ITEM(code_object_desc, 4, PyLong_FromLong(function->m_code_object->co_argcount));
    PyTuple_SET_ITEM(code_object_desc, 5, PyLong_FromLong(function->m_code_object->co_flags));

    CHECK_OBJECT_DEEP(code_object_desc);


    PyObject *result = MAKE_TUPLE_EMPTY(8);
    PyTuple_SET_ITEM(result, 0, PyLong_FromLong(offset));
    PyTuple_SET_ITEM(result, 1, code_object_desc);
    PyTuple_SET_ITEM0(result, 2, function->m_defaults);
#if PYTHON_VERSION >= 0x300
    PyTuple_SET_ITEM0(result, 3, function->m_kwdefaults ? function->m_kwdefaults : Py_None);
#else
    PyTuple_SET_ITEM0(result, 3, Py_None);
#endif
    PyTuple_SET_ITEM0(result, 4, function->m_doc != NULL ? function->m_doc : Py_None);

    if (offset == -5) {
        CHECK_OBJECT(function->m_constant_return_value);
        PyTuple_SET_ITEM0(result, 5, function->m_constant_return_value);
    } else {
        PyTuple_SET_ITEM0(result, 5, Py_None);
    }

#if PYTHON_VERSION >= 0x300
    PyTuple_SET_ITEM0(result, 6, function->m_qualname);
#else
    PyTuple_SET_ITEM0(result, 6, Py_None);
#endif

    PyObject *closure = PyObject_GetAttr(
        (PyObject *)function,
        const_str_plain___closure__
    );

    if (closure != Py_None) {
        for (Py_ssize_t i=0; i < PyTuple_GET_SIZE(closure); i++) {
            struct Nuitka_CellObject *cell = (struct Nuitka_CellObject *)PyTuple_GET_ITEM(closure, i);

            assert(Nuitka_Cell_Check((PyObject *)cell));

            PyTuple_SET_ITEM0(
                closure,
                i,
                cell->ob_ref
            );
        }
    }

    PyTuple_SET_ITEM(result, 7, closure);

    CHECK_OBJECT_DEEP(result);

    return result;
}

static PyMethodDef _method_def_reduce_compiled_function = {"reduce_compiled_function", (PyCFunction)_reduce_compiled_function,
                                                           METH_VARARGS, NULL};


static PyObject *_create_compiled_function(PyObject *self, PyObject *args, PyObject *kwds) {
    CHECK_OBJECT_DEEP(args);

    PyObject *function_index;
    PyObject *code_object_desc;
    PyObject *defaults;
    PyObject *kw_defaults;
    PyObject *doc;
    PyObject *constant_return_value;
    PyObject *function_qualname;
    PyObject *closure;

    if (!PyArg_ParseTuple(args, "OOOOOOOO:create_compiled_function", &function_index, &code_object_desc, &defaults, &kw_defaults, &doc, &constant_return_value, &function_qualname, &closure, NULL)) {
        return NULL;
    }

#if PYTHON_VERSION >= 0x300
    if (kw_defaults == Py_None) {
        kw_defaults = NULL;
    }
#endif

    return (PyObject *)Nuitka_Function_CreateFunctionViaCodeIndex(
        module_core$panic,
        function_qualname,
        function_index,
        code_object_desc,
        constant_return_value,
        defaults,
        kw_defaults,
        doc,
        closure,
        function_table_core$panic,
        sizeof(function_table_core$panic) / sizeof(function_impl_code)
    );
}

static PyMethodDef _method_def_create_compiled_function = {
    "create_compiled_function",
    (PyCFunction)_create_compiled_function,
    METH_VARARGS, NULL
};


#endif

// Internal entry point for module code.
PyObject *modulecode_core$panic(PyThreadState *tstate, PyObject *module, struct Nuitka_MetaPathBasedLoaderEntry const *loader_entry) {
    // Report entry to PGO.
    PGO_onModuleEntered("core$panic");

    // Store the module for future use.
    module_core$panic = module;

    // Modules can be loaded again in case of errors, avoid the init being done again.
    static bool init_done = false;

    if (init_done == false) {
#if defined(_NUITKA_MODULE) && 0
        // In case of an extension module loaded into a process, we need to call
        // initialization here because that's the first and potentially only time
        // we are going called.

        // Initialize the constant values used.
        _initBuiltinModule();
        createGlobalConstants(tstate);

        /* Initialize the compiled types of Nuitka. */
        _initCompiledCellType();
        _initCompiledGeneratorType();
        _initCompiledFunctionType();
        _initCompiledMethodType();
        _initCompiledFrameType();

        _initSlotCompare();
#if PYTHON_VERSION >= 0x270
        _initSlotIterNext();
#endif

        patchTypeComparison();

        // Enable meta path based loader if not already done.
#ifdef _NUITKA_TRACE
        PRINT_STRING("core$panic: Calling setupMetaPathBasedLoader().\n");
#endif
        setupMetaPathBasedLoader(tstate);

#if PYTHON_VERSION >= 0x300
        patchInspectModule(tstate);
#endif

#endif

        /* The constants only used by this module are created now. */
        NUITKA_PRINT_TRACE("core$panic: Calling createModuleConstants().\n");
        createModuleConstants(tstate);

        createModuleCodeObjects();

        init_done = true;
    }

#if defined(_NUITKA_MODULE) && 0
    PyObject *pre_load = IMPORT_EMBEDDED_MODULE(tstate, "core.panic" "-preLoad");
    if (pre_load == NULL) {
        return NULL;
    }
#endif

    // PRINT_STRING("in initcore$panic\n");

    moduledict_core$panic = MODULE_DICT(module_core$panic);

#ifdef _NUITKA_PLUGIN_DILL_ENABLED
    {
        char const *module_name_c;
        if (loader_entry != NULL) {
            module_name_c = loader_entry->name;
        } else {
            PyObject *module_name = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)const_str_plain___name__);
            module_name_c = Nuitka_String_AsString(module_name);
        }

        registerDillPluginTables(tstate, module_name_c, &_method_def_reduce_compiled_function, &_method_def_create_compiled_function);
    }
#endif

    // Set "__compiled__" to what version information we have.
    UPDATE_STRING_DICT0(
        moduledict_core$panic,
        (Nuitka_StringObject *)const_str_plain___compiled__,
        Nuitka_dunder_compiled_value
    );

    // Update "__package__" value to what it ought to be.
    {
#if 0
        UPDATE_STRING_DICT0(
            moduledict_core$panic,
            (Nuitka_StringObject *)const_str_plain___package__,
            mod_consts[44]
        );
#elif 0
        PyObject *module_name = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)const_str_plain___name__);

        UPDATE_STRING_DICT0(
            moduledict_core$panic,
            (Nuitka_StringObject *)const_str_plain___package__,
            module_name
        );
#else

#if PYTHON_VERSION < 0x300
        PyObject *module_name = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)const_str_plain___name__);
        char const *module_name_cstr = PyString_AS_STRING(module_name);

        char const *last_dot = strrchr(module_name_cstr, '.');

        if (last_dot != NULL) {
            UPDATE_STRING_DICT1(
                moduledict_core$panic,
                (Nuitka_StringObject *)const_str_plain___package__,
                PyString_FromStringAndSize(module_name_cstr, last_dot - module_name_cstr)
            );
        }
#else
        PyObject *module_name = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)const_str_plain___name__);
        Py_ssize_t dot_index = PyUnicode_Find(module_name, const_str_dot, 0, PyUnicode_GetLength(module_name), -1);

        if (dot_index != -1) {
            UPDATE_STRING_DICT1(
                moduledict_core$panic,
                (Nuitka_StringObject *)const_str_plain___package__,
                PyUnicode_Substring(module_name, 0, dot_index)
            );
        }
#endif
#endif
    }

    CHECK_OBJECT(module_core$panic);

    // For deep importing of a module we need to have "__builtins__", so we set
    // it ourselves in the same way than CPython does. Note: This must be done
    // before the frame object is allocated, or else it may fail.

    if (GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)const_str_plain___builtins__) == NULL) {
        PyObject *value = (PyObject *)builtin_module;

        // Check if main module, not a dict then but the module itself.
#if defined(_NUITKA_MODULE) || !0
        value = PyModule_GetDict(value);
#endif

        UPDATE_STRING_DICT0(moduledict_core$panic, (Nuitka_StringObject *)const_str_plain___builtins__, value);
    }

    UPDATE_STRING_DICT0(moduledict_core$panic, (Nuitka_StringObject *)const_str_plain___loader__, (PyObject *)&Nuitka_Loader_Type);

#if PYTHON_VERSION >= 0x340
// Set the "__spec__" value

#if 0
    // Main modules just get "None" as spec.
    UPDATE_STRING_DICT0(moduledict_core$panic, (Nuitka_StringObject *)const_str_plain___spec__, Py_None);
#else
    // Other modules get a "ModuleSpec" from the standard mechanism.
    {
        PyObject *bootstrap_module = getImportLibBootstrapModule();
        CHECK_OBJECT(bootstrap_module);

        PyObject *_spec_from_module = PyObject_GetAttrString(bootstrap_module, "_spec_from_module");
        CHECK_OBJECT(_spec_from_module);

        PyObject *spec_value = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, _spec_from_module, module_core$panic);
        Py_DECREF(_spec_from_module);

        // We can assume this to never fail, or else we are in trouble anyway.
        // CHECK_OBJECT(spec_value);

        if (spec_value == NULL) {
            PyErr_PrintEx(0);
            abort();
        }

// Mark the execution in the "__spec__" value.
        SET_ATTRIBUTE(tstate, spec_value, const_str_plain__initializing, Py_True);

        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)const_str_plain___spec__, spec_value);
    }
#endif
#endif

    // Temp variables if any
    PyObject *outline_0_var___class__ = NULL;
    PyObject *tmp_class_creation_1__bases = NULL;
    PyObject *tmp_class_creation_1__bases_orig = NULL;
    PyObject *tmp_class_creation_1__class_decl_dict = NULL;
    PyObject *tmp_class_creation_1__metaclass = NULL;
    PyObject *tmp_class_creation_1__prepared = NULL;
    PyObject *tmp_import_from_1__module = NULL;
    PyObject *tmp_import_from_2__module = NULL;
    PyObject *tmp_import_from_3__module = NULL;
    PyObject *tmp_import_from_4__module = NULL;
    struct Nuitka_FrameObject *frame_a2676065e0c895da5b2c9b4d6277da45;
    NUITKA_MAY_BE_UNUSED char const *type_description_1 = NULL;
    bool tmp_result;
    PyObject *exception_type = NULL;
    PyObject *exception_value = NULL;
    PyTracebackObject *exception_tb = NULL;
    NUITKA_MAY_BE_UNUSED int exception_lineno = 0;
    PyObject *exception_keeper_type_1;
    PyObject *exception_keeper_value_1;
    PyTracebackObject *exception_keeper_tb_1;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_1;
    PyObject *exception_keeper_type_2;
    PyObject *exception_keeper_value_2;
    PyTracebackObject *exception_keeper_tb_2;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_2;
    PyObject *exception_keeper_type_3;
    PyObject *exception_keeper_value_3;
    PyTracebackObject *exception_keeper_tb_3;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_3;
    PyObject *exception_keeper_type_4;
    PyObject *exception_keeper_value_4;
    PyTracebackObject *exception_keeper_tb_4;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_4;
    int tmp_res;
    PyObject *locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18 = NULL;
    PyObject *tmp_dictset_value;
    struct Nuitka_FrameObject *frame_ead9b724b65ce3c43b718984fb92cd7f_2;
    NUITKA_MAY_BE_UNUSED char const *type_description_2 = NULL;
    PyObject *exception_keeper_type_5;
    PyObject *exception_keeper_value_5;
    PyTracebackObject *exception_keeper_tb_5;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_5;
    PyObject *exception_keeper_type_6;
    PyObject *exception_keeper_value_6;
    PyTracebackObject *exception_keeper_tb_6;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_6;
    PyObject *exception_keeper_type_7;
    PyObject *exception_keeper_value_7;
    PyTracebackObject *exception_keeper_tb_7;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_7;
    PyObject *exception_keeper_type_8;
    PyObject *exception_keeper_value_8;
    PyTracebackObject *exception_keeper_tb_8;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_8;
    struct Nuitka_ExceptionStackItem exception_preserved_1;
    PyObject *exception_keeper_type_9;
    PyObject *exception_keeper_value_9;
    PyTracebackObject *exception_keeper_tb_9;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_9;

    // Module code.
    {
        PyObject *tmp_assign_source_1;
        tmp_assign_source_1 = Py_None;
        UPDATE_STRING_DICT0(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[128], tmp_assign_source_1);
    }
    {
        PyObject *tmp_assign_source_2;
        tmp_assign_source_2 = module_filename_obj;
        UPDATE_STRING_DICT0(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[129], tmp_assign_source_2);
    }
    frame_a2676065e0c895da5b2c9b4d6277da45 = MAKE_MODULE_FRAME(codeobj_a2676065e0c895da5b2c9b4d6277da45, module_core$panic);

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackCompiledFrame(tstate, frame_a2676065e0c895da5b2c9b4d6277da45);
    assert(Py_REFCNT(frame_a2676065e0c895da5b2c9b4d6277da45) == 2);

    // Framed code:
    {
        PyObject *tmp_assattr_value_1;
        PyObject *tmp_assattr_target_1;
        tmp_assattr_value_1 = module_filename_obj;
        tmp_assattr_target_1 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[130]);

        if (unlikely(tmp_assattr_target_1 == NULL)) {
            tmp_assattr_target_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[130]);
        }

        assert(!(tmp_assattr_target_1 == NULL));
        tmp_result = SET_ATTRIBUTE(tstate, tmp_assattr_target_1, mod_consts[131], tmp_assattr_value_1);
        if (tmp_result == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 1;

            goto frame_exception_exit_1;
        }
    }
    {
        PyObject *tmp_assattr_value_2;
        PyObject *tmp_assattr_target_2;
        tmp_assattr_value_2 = Py_True;
        tmp_assattr_target_2 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[130]);

        if (unlikely(tmp_assattr_target_2 == NULL)) {
            tmp_assattr_target_2 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[130]);
        }

        assert(!(tmp_assattr_target_2 == NULL));
        tmp_result = SET_ATTRIBUTE(tstate, tmp_assattr_target_2, mod_consts[132], tmp_assattr_value_2);
        if (tmp_result == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 1;

            goto frame_exception_exit_1;
        }
    }
    {
        PyObject *tmp_assign_source_3;
        tmp_assign_source_3 = Py_None;
        UPDATE_STRING_DICT0(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[133], tmp_assign_source_3);
    }
    {
        PyObject *tmp_assign_source_4;
        tmp_assign_source_4 = MAKE_DICT_EMPTY();
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[134], tmp_assign_source_4);
    }
    {
        PyObject *tmp_assign_source_5;
        PyObject *tmp_name_value_1;
        PyObject *tmp_globals_arg_value_1;
        PyObject *tmp_locals_arg_value_1;
        PyObject *tmp_fromlist_value_1;
        PyObject *tmp_level_value_1;
        tmp_name_value_1 = mod_consts[7];
        tmp_globals_arg_value_1 = (PyObject *)moduledict_core$panic;
        tmp_locals_arg_value_1 = Py_None;
        tmp_fromlist_value_1 = Py_None;
        tmp_level_value_1 = mod_consts[15];
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 1;
        tmp_assign_source_5 = IMPORT_MODULE5(tstate, tmp_name_value_1, tmp_globals_arg_value_1, tmp_locals_arg_value_1, tmp_fromlist_value_1, tmp_level_value_1);
        if (tmp_assign_source_5 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 1;

            goto frame_exception_exit_1;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[7], tmp_assign_source_5);
    }
    {
        PyObject *tmp_assign_source_6;
        tmp_assign_source_6 = IMPORT_HARD_OS();
        assert(!(tmp_assign_source_6 == NULL));
        UPDATE_STRING_DICT0(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[135], tmp_assign_source_6);
    }
    {
        PyObject *tmp_assign_source_7;
        tmp_assign_source_7 = Nuitka_SysGetObject("stdout");
        assert(!(tmp_assign_source_7 == NULL));
        UPDATE_STRING_DICT0(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[136], tmp_assign_source_7);
    }
    {
        PyObject *tmp_assign_source_8;
        tmp_assign_source_8 = IMPORT_HARD_TYPING();
        assert(!(tmp_assign_source_8 == NULL));
        assert(tmp_import_from_1__module == NULL);
        Py_INCREF(tmp_assign_source_8);
        tmp_import_from_1__module = tmp_assign_source_8;
    }
    // Tried code:
    {
        PyObject *tmp_assign_source_9;
        PyObject *tmp_import_name_from_1;
        CHECK_OBJECT(tmp_import_from_1__module);
        tmp_import_name_from_1 = tmp_import_from_1__module;
        if (PyModule_Check(tmp_import_name_from_1)) {
            tmp_assign_source_9 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_1,
                (PyObject *)moduledict_core$panic,
                mod_consts[137],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_9 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_1, mod_consts[137]);
        }

        if (tmp_assign_source_9 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 4;

            goto try_except_handler_1;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[137], tmp_assign_source_9);
    }
    {
        PyObject *tmp_assign_source_10;
        PyObject *tmp_import_name_from_2;
        CHECK_OBJECT(tmp_import_from_1__module);
        tmp_import_name_from_2 = tmp_import_from_1__module;
        if (PyModule_Check(tmp_import_name_from_2)) {
            tmp_assign_source_10 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_2,
                (PyObject *)moduledict_core$panic,
                mod_consts[138],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_10 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_2, mod_consts[138]);
        }

        if (tmp_assign_source_10 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 4;

            goto try_except_handler_1;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[138], tmp_assign_source_10);
    }
    goto try_end_1;
    // Exception handler code:
    try_except_handler_1:;
    exception_keeper_type_1 = exception_type;
    exception_keeper_value_1 = exception_value;
    exception_keeper_tb_1 = exception_tb;
    exception_keeper_lineno_1 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    CHECK_OBJECT(tmp_import_from_1__module);
    Py_DECREF(tmp_import_from_1__module);
    tmp_import_from_1__module = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_1;
    exception_value = exception_keeper_value_1;
    exception_tb = exception_keeper_tb_1;
    exception_lineno = exception_keeper_lineno_1;

    goto frame_exception_exit_1;
    // End of try:
    try_end_1:;
    CHECK_OBJECT(tmp_import_from_1__module);
    Py_DECREF(tmp_import_from_1__module);
    tmp_import_from_1__module = NULL;
    {
        PyObject *tmp_assign_source_11;
        PyObject *tmp_import_name_from_3;
        PyObject *tmp_name_value_2;
        PyObject *tmp_globals_arg_value_2;
        PyObject *tmp_locals_arg_value_2;
        PyObject *tmp_fromlist_value_2;
        PyObject *tmp_level_value_2;
        tmp_name_value_2 = mod_consts[139];
        tmp_globals_arg_value_2 = (PyObject *)moduledict_core$panic;
        tmp_locals_arg_value_2 = Py_None;
        tmp_fromlist_value_2 = mod_consts[140];
        tmp_level_value_2 = mod_consts[15];
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 5;
        tmp_import_name_from_3 = IMPORT_MODULE5(tstate, tmp_name_value_2, tmp_globals_arg_value_2, tmp_locals_arg_value_2, tmp_fromlist_value_2, tmp_level_value_2);
        if (tmp_import_name_from_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 5;

            goto frame_exception_exit_1;
        }
        if (PyModule_Check(tmp_import_name_from_3)) {
            tmp_assign_source_11 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_3,
                (PyObject *)moduledict_core$panic,
                mod_consts[141],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_11 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_3, mod_consts[141]);
        }

        Py_DECREF(tmp_import_name_from_3);
        if (tmp_assign_source_11 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 5;

            goto frame_exception_exit_1;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[141], tmp_assign_source_11);
    }
    {
        PyObject *tmp_assign_source_12;
        PyObject *tmp_name_value_3;
        PyObject *tmp_globals_arg_value_3;
        PyObject *tmp_locals_arg_value_3;
        PyObject *tmp_fromlist_value_3;
        PyObject *tmp_level_value_3;
        tmp_name_value_3 = mod_consts[65];
        tmp_globals_arg_value_3 = (PyObject *)moduledict_core$panic;
        tmp_locals_arg_value_3 = Py_None;
        tmp_fromlist_value_3 = Py_None;
        tmp_level_value_3 = mod_consts[15];
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 9;
        tmp_assign_source_12 = IMPORT_MODULE5(tstate, tmp_name_value_3, tmp_globals_arg_value_3, tmp_locals_arg_value_3, tmp_fromlist_value_3, tmp_level_value_3);
        if (tmp_assign_source_12 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 9;

            goto frame_exception_exit_1;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[65], tmp_assign_source_12);
    }
    {
        PyObject *tmp_assign_source_13;
        PyObject *tmp_import_name_from_4;
        PyObject *tmp_name_value_4;
        PyObject *tmp_globals_arg_value_4;
        PyObject *tmp_locals_arg_value_4;
        PyObject *tmp_fromlist_value_4;
        PyObject *tmp_level_value_4;
        tmp_name_value_4 = mod_consts[142];
        tmp_globals_arg_value_4 = (PyObject *)moduledict_core$panic;
        tmp_locals_arg_value_4 = Py_None;
        tmp_fromlist_value_4 = mod_consts[143];
        tmp_level_value_4 = mod_consts[15];
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 10;
        tmp_import_name_from_4 = IMPORT_MODULE5(tstate, tmp_name_value_4, tmp_globals_arg_value_4, tmp_locals_arg_value_4, tmp_fromlist_value_4, tmp_level_value_4);
        if (tmp_import_name_from_4 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 10;

            goto frame_exception_exit_1;
        }
        if (PyModule_Check(tmp_import_name_from_4)) {
            tmp_assign_source_13 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_4,
                (PyObject *)moduledict_core$panic,
                mod_consts[0],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_13 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_4, mod_consts[0]);
        }

        Py_DECREF(tmp_import_name_from_4);
        if (tmp_assign_source_13 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 10;

            goto frame_exception_exit_1;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[0], tmp_assign_source_13);
    }
    {
        PyObject *tmp_assign_source_14;
        PyObject *tmp_name_value_5;
        PyObject *tmp_globals_arg_value_5;
        PyObject *tmp_locals_arg_value_5;
        PyObject *tmp_fromlist_value_5;
        PyObject *tmp_level_value_5;
        tmp_name_value_5 = mod_consts[144];
        tmp_globals_arg_value_5 = (PyObject *)moduledict_core$panic;
        tmp_locals_arg_value_5 = Py_None;
        tmp_fromlist_value_5 = mod_consts[145];
        tmp_level_value_5 = mod_consts[15];
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 11;
        tmp_assign_source_14 = IMPORT_MODULE5(tstate, tmp_name_value_5, tmp_globals_arg_value_5, tmp_locals_arg_value_5, tmp_fromlist_value_5, tmp_level_value_5);
        if (tmp_assign_source_14 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 11;

            goto frame_exception_exit_1;
        }
        assert(tmp_import_from_2__module == NULL);
        tmp_import_from_2__module = tmp_assign_source_14;
    }
    // Tried code:
    {
        PyObject *tmp_assign_source_15;
        PyObject *tmp_import_name_from_5;
        CHECK_OBJECT(tmp_import_from_2__module);
        tmp_import_name_from_5 = tmp_import_from_2__module;
        if (PyModule_Check(tmp_import_name_from_5)) {
            tmp_assign_source_15 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_5,
                (PyObject *)moduledict_core$panic,
                mod_consts[146],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_15 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_5, mod_consts[146]);
        }

        if (tmp_assign_source_15 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 11;

            goto try_except_handler_2;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[146], tmp_assign_source_15);
    }
    {
        PyObject *tmp_assign_source_16;
        PyObject *tmp_import_name_from_6;
        CHECK_OBJECT(tmp_import_from_2__module);
        tmp_import_name_from_6 = tmp_import_from_2__module;
        if (PyModule_Check(tmp_import_name_from_6)) {
            tmp_assign_source_16 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_6,
                (PyObject *)moduledict_core$panic,
                mod_consts[147],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_16 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_6, mod_consts[147]);
        }

        if (tmp_assign_source_16 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 11;

            goto try_except_handler_2;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[147], tmp_assign_source_16);
    }
    goto try_end_2;
    // Exception handler code:
    try_except_handler_2:;
    exception_keeper_type_2 = exception_type;
    exception_keeper_value_2 = exception_value;
    exception_keeper_tb_2 = exception_tb;
    exception_keeper_lineno_2 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    CHECK_OBJECT(tmp_import_from_2__module);
    Py_DECREF(tmp_import_from_2__module);
    tmp_import_from_2__module = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_2;
    exception_value = exception_keeper_value_2;
    exception_tb = exception_keeper_tb_2;
    exception_lineno = exception_keeper_lineno_2;

    goto frame_exception_exit_1;
    // End of try:
    try_end_2:;
    CHECK_OBJECT(tmp_import_from_2__module);
    Py_DECREF(tmp_import_from_2__module);
    tmp_import_from_2__module = NULL;
    {
        PyObject *tmp_assign_source_17;
        PyObject *tmp_name_value_6;
        PyObject *tmp_globals_arg_value_6;
        PyObject *tmp_locals_arg_value_6;
        PyObject *tmp_fromlist_value_6;
        PyObject *tmp_level_value_6;
        tmp_name_value_6 = mod_consts[148];
        tmp_globals_arg_value_6 = (PyObject *)moduledict_core$panic;
        tmp_locals_arg_value_6 = Py_None;
        tmp_fromlist_value_6 = mod_consts[149];
        tmp_level_value_6 = mod_consts[15];
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 13;
        tmp_assign_source_17 = IMPORT_MODULE5(tstate, tmp_name_value_6, tmp_globals_arg_value_6, tmp_locals_arg_value_6, tmp_fromlist_value_6, tmp_level_value_6);
        if (tmp_assign_source_17 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 13;

            goto frame_exception_exit_1;
        }
        assert(tmp_import_from_3__module == NULL);
        tmp_import_from_3__module = tmp_assign_source_17;
    }
    // Tried code:
    {
        PyObject *tmp_assign_source_18;
        PyObject *tmp_import_name_from_7;
        CHECK_OBJECT(tmp_import_from_3__module);
        tmp_import_name_from_7 = tmp_import_from_3__module;
        if (PyModule_Check(tmp_import_name_from_7)) {
            tmp_assign_source_18 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_7,
                (PyObject *)moduledict_core$panic,
                mod_consts[150],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_18 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_7, mod_consts[150]);
        }

        if (tmp_assign_source_18 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 13;

            goto try_except_handler_3;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[150], tmp_assign_source_18);
    }
    {
        PyObject *tmp_assign_source_19;
        PyObject *tmp_import_name_from_8;
        CHECK_OBJECT(tmp_import_from_3__module);
        tmp_import_name_from_8 = tmp_import_from_3__module;
        if (PyModule_Check(tmp_import_name_from_8)) {
            tmp_assign_source_19 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_8,
                (PyObject *)moduledict_core$panic,
                mod_consts[151],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_19 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_8, mod_consts[151]);
        }

        if (tmp_assign_source_19 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 13;

            goto try_except_handler_3;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[151], tmp_assign_source_19);
    }
    {
        PyObject *tmp_assign_source_20;
        PyObject *tmp_import_name_from_9;
        CHECK_OBJECT(tmp_import_from_3__module);
        tmp_import_name_from_9 = tmp_import_from_3__module;
        if (PyModule_Check(tmp_import_name_from_9)) {
            tmp_assign_source_20 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_9,
                (PyObject *)moduledict_core$panic,
                mod_consts[152],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_20 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_9, mod_consts[152]);
        }

        if (tmp_assign_source_20 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 13;

            goto try_except_handler_3;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[152], tmp_assign_source_20);
    }
    goto try_end_3;
    // Exception handler code:
    try_except_handler_3:;
    exception_keeper_type_3 = exception_type;
    exception_keeper_value_3 = exception_value;
    exception_keeper_tb_3 = exception_tb;
    exception_keeper_lineno_3 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    CHECK_OBJECT(tmp_import_from_3__module);
    Py_DECREF(tmp_import_from_3__module);
    tmp_import_from_3__module = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_3;
    exception_value = exception_keeper_value_3;
    exception_tb = exception_keeper_tb_3;
    exception_lineno = exception_keeper_lineno_3;

    goto frame_exception_exit_1;
    // End of try:
    try_end_3:;
    CHECK_OBJECT(tmp_import_from_3__module);
    Py_DECREF(tmp_import_from_3__module);
    tmp_import_from_3__module = NULL;
    {
        PyObject *tmp_assign_source_21;
        PyObject *tmp_name_value_7;
        PyObject *tmp_globals_arg_value_7;
        PyObject *tmp_locals_arg_value_7;
        PyObject *tmp_fromlist_value_7;
        PyObject *tmp_level_value_7;
        tmp_name_value_7 = mod_consts[153];
        tmp_globals_arg_value_7 = (PyObject *)moduledict_core$panic;
        tmp_locals_arg_value_7 = Py_None;
        tmp_fromlist_value_7 = mod_consts[154];
        tmp_level_value_7 = mod_consts[15];
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 14;
        tmp_assign_source_21 = IMPORT_MODULE5(tstate, tmp_name_value_7, tmp_globals_arg_value_7, tmp_locals_arg_value_7, tmp_fromlist_value_7, tmp_level_value_7);
        if (tmp_assign_source_21 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 14;

            goto frame_exception_exit_1;
        }
        assert(tmp_import_from_4__module == NULL);
        tmp_import_from_4__module = tmp_assign_source_21;
    }
    // Tried code:
    {
        PyObject *tmp_assign_source_22;
        PyObject *tmp_import_name_from_10;
        CHECK_OBJECT(tmp_import_from_4__module);
        tmp_import_name_from_10 = tmp_import_from_4__module;
        if (PyModule_Check(tmp_import_name_from_10)) {
            tmp_assign_source_22 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_10,
                (PyObject *)moduledict_core$panic,
                mod_consts[155],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_22 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_10, mod_consts[155]);
        }

        if (tmp_assign_source_22 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 14;

            goto try_except_handler_4;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[155], tmp_assign_source_22);
    }
    {
        PyObject *tmp_assign_source_23;
        PyObject *tmp_import_name_from_11;
        CHECK_OBJECT(tmp_import_from_4__module);
        tmp_import_name_from_11 = tmp_import_from_4__module;
        if (PyModule_Check(tmp_import_name_from_11)) {
            tmp_assign_source_23 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_11,
                (PyObject *)moduledict_core$panic,
                mod_consts[156],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_23 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_11, mod_consts[156]);
        }

        if (tmp_assign_source_23 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 14;

            goto try_except_handler_4;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156], tmp_assign_source_23);
    }
    {
        PyObject *tmp_assign_source_24;
        PyObject *tmp_import_name_from_12;
        CHECK_OBJECT(tmp_import_from_4__module);
        tmp_import_name_from_12 = tmp_import_from_4__module;
        if (PyModule_Check(tmp_import_name_from_12)) {
            tmp_assign_source_24 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_12,
                (PyObject *)moduledict_core$panic,
                mod_consts[157],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_24 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_12, mod_consts[157]);
        }

        if (tmp_assign_source_24 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 14;

            goto try_except_handler_4;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[157], tmp_assign_source_24);
    }
    {
        PyObject *tmp_assign_source_25;
        PyObject *tmp_import_name_from_13;
        CHECK_OBJECT(tmp_import_from_4__module);
        tmp_import_name_from_13 = tmp_import_from_4__module;
        if (PyModule_Check(tmp_import_name_from_13)) {
            tmp_assign_source_25 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_13,
                (PyObject *)moduledict_core$panic,
                mod_consts[158],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_25 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_13, mod_consts[158]);
        }

        if (tmp_assign_source_25 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 14;

            goto try_except_handler_4;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158], tmp_assign_source_25);
    }
    {
        PyObject *tmp_assign_source_26;
        PyObject *tmp_import_name_from_14;
        CHECK_OBJECT(tmp_import_from_4__module);
        tmp_import_name_from_14 = tmp_import_from_4__module;
        if (PyModule_Check(tmp_import_name_from_14)) {
            tmp_assign_source_26 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_14,
                (PyObject *)moduledict_core$panic,
                mod_consts[159],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_26 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_14, mod_consts[159]);
        }

        if (tmp_assign_source_26 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 14;

            goto try_except_handler_4;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[159], tmp_assign_source_26);
    }
    {
        PyObject *tmp_assign_source_27;
        PyObject *tmp_import_name_from_15;
        CHECK_OBJECT(tmp_import_from_4__module);
        tmp_import_name_from_15 = tmp_import_from_4__module;
        if (PyModule_Check(tmp_import_name_from_15)) {
            tmp_assign_source_27 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_15,
                (PyObject *)moduledict_core$panic,
                mod_consts[160],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_27 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_15, mod_consts[160]);
        }

        if (tmp_assign_source_27 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 14;

            goto try_except_handler_4;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[160], tmp_assign_source_27);
    }
    {
        PyObject *tmp_assign_source_28;
        PyObject *tmp_import_name_from_16;
        CHECK_OBJECT(tmp_import_from_4__module);
        tmp_import_name_from_16 = tmp_import_from_4__module;
        if (PyModule_Check(tmp_import_name_from_16)) {
            tmp_assign_source_28 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_16,
                (PyObject *)moduledict_core$panic,
                mod_consts[161],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_28 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_16, mod_consts[161]);
        }

        if (tmp_assign_source_28 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 14;

            goto try_except_handler_4;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[161], tmp_assign_source_28);
    }
    {
        PyObject *tmp_assign_source_29;
        PyObject *tmp_import_name_from_17;
        CHECK_OBJECT(tmp_import_from_4__module);
        tmp_import_name_from_17 = tmp_import_from_4__module;
        if (PyModule_Check(tmp_import_name_from_17)) {
            tmp_assign_source_29 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_17,
                (PyObject *)moduledict_core$panic,
                mod_consts[162],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_29 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_17, mod_consts[162]);
        }

        if (tmp_assign_source_29 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 14;

            goto try_except_handler_4;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[162], tmp_assign_source_29);
    }
    {
        PyObject *tmp_assign_source_30;
        PyObject *tmp_import_name_from_18;
        CHECK_OBJECT(tmp_import_from_4__module);
        tmp_import_name_from_18 = tmp_import_from_4__module;
        if (PyModule_Check(tmp_import_name_from_18)) {
            tmp_assign_source_30 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_18,
                (PyObject *)moduledict_core$panic,
                mod_consts[163],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_30 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_18, mod_consts[163]);
        }

        if (tmp_assign_source_30 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 14;

            goto try_except_handler_4;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[163], tmp_assign_source_30);
    }
    goto try_end_4;
    // Exception handler code:
    try_except_handler_4:;
    exception_keeper_type_4 = exception_type;
    exception_keeper_value_4 = exception_value;
    exception_keeper_tb_4 = exception_tb;
    exception_keeper_lineno_4 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    CHECK_OBJECT(tmp_import_from_4__module);
    Py_DECREF(tmp_import_from_4__module);
    tmp_import_from_4__module = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_4;
    exception_value = exception_keeper_value_4;
    exception_tb = exception_keeper_tb_4;
    exception_lineno = exception_keeper_lineno_4;

    goto frame_exception_exit_1;
    // End of try:
    try_end_4:;
    CHECK_OBJECT(tmp_import_from_4__module);
    Py_DECREF(tmp_import_from_4__module);
    tmp_import_from_4__module = NULL;
    // Tried code:
    {
        PyObject *tmp_assign_source_31;
        PyObject *tmp_tuple_element_1;
        tmp_tuple_element_1 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[150]);

        if (unlikely(tmp_tuple_element_1 == NULL)) {
            tmp_tuple_element_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[150]);
        }

        if (tmp_tuple_element_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_5;
        }
        tmp_assign_source_31 = MAKE_TUPLE_EMPTY(1);
        PyTuple_SET_ITEM0(tmp_assign_source_31, 0, tmp_tuple_element_1);
        assert(tmp_class_creation_1__bases_orig == NULL);
        tmp_class_creation_1__bases_orig = tmp_assign_source_31;
    }
    {
        PyObject *tmp_assign_source_32;
        PyObject *tmp_dircall_arg1_1;
        CHECK_OBJECT(tmp_class_creation_1__bases_orig);
        tmp_dircall_arg1_1 = tmp_class_creation_1__bases_orig;
        Py_INCREF(tmp_dircall_arg1_1);

        {
            PyObject *dir_call_args[] = {tmp_dircall_arg1_1};
            tmp_assign_source_32 = impl___main__$$$function__5__mro_entries_conversion(tstate, dir_call_args);
        }
        if (tmp_assign_source_32 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_5;
        }
        assert(tmp_class_creation_1__bases == NULL);
        tmp_class_creation_1__bases = tmp_assign_source_32;
    }
    {
        PyObject *tmp_assign_source_33;
        tmp_assign_source_33 = MAKE_DICT_EMPTY();
        assert(tmp_class_creation_1__class_decl_dict == NULL);
        tmp_class_creation_1__class_decl_dict = tmp_assign_source_33;
    }
    {
        PyObject *tmp_assign_source_34;
        PyObject *tmp_metaclass_value_1;
        nuitka_bool tmp_condition_result_1;
        int tmp_truth_name_1;
        PyObject *tmp_type_arg_1;
        PyObject *tmp_expression_value_1;
        PyObject *tmp_subscript_value_1;
        PyObject *tmp_bases_value_1;
        CHECK_OBJECT(tmp_class_creation_1__bases);
        tmp_truth_name_1 = CHECK_IF_TRUE(tmp_class_creation_1__bases);
        if (tmp_truth_name_1 == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_5;
        }
        tmp_condition_result_1 = tmp_truth_name_1 == 0 ? NUITKA_BOOL_FALSE : NUITKA_BOOL_TRUE;
        if (tmp_condition_result_1 == NUITKA_BOOL_TRUE) {
            goto condexpr_true_1;
        } else {
            goto condexpr_false_1;
        }
        condexpr_true_1:;
        CHECK_OBJECT(tmp_class_creation_1__bases);
        tmp_expression_value_1 = tmp_class_creation_1__bases;
        tmp_subscript_value_1 = mod_consts[15];
        tmp_type_arg_1 = LOOKUP_SUBSCRIPT_CONST(tstate, tmp_expression_value_1, tmp_subscript_value_1, 0);
        if (tmp_type_arg_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_5;
        }
        tmp_metaclass_value_1 = BUILTIN_TYPE1(tmp_type_arg_1);
        Py_DECREF(tmp_type_arg_1);
        if (tmp_metaclass_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_5;
        }
        goto condexpr_end_1;
        condexpr_false_1:;
        tmp_metaclass_value_1 = (PyObject *)&PyType_Type;
        Py_INCREF(tmp_metaclass_value_1);
        condexpr_end_1:;
        CHECK_OBJECT(tmp_class_creation_1__bases);
        tmp_bases_value_1 = tmp_class_creation_1__bases;
        tmp_assign_source_34 = SELECT_METACLASS(tstate, tmp_metaclass_value_1, tmp_bases_value_1);
        Py_DECREF(tmp_metaclass_value_1);
        if (tmp_assign_source_34 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_5;
        }
        assert(tmp_class_creation_1__metaclass == NULL);
        tmp_class_creation_1__metaclass = tmp_assign_source_34;
    }
    {
        bool tmp_condition_result_2;
        PyObject *tmp_expression_value_2;
        CHECK_OBJECT(tmp_class_creation_1__metaclass);
        tmp_expression_value_2 = tmp_class_creation_1__metaclass;
        tmp_res = HAS_ATTR_BOOL2(tstate, tmp_expression_value_2, mod_consts[164]);
        if (tmp_res == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_5;
        }
        tmp_condition_result_2 = (tmp_res != 0) ? true : false;
        if (tmp_condition_result_2 != false) {
            goto branch_yes_1;
        } else {
            goto branch_no_1;
        }
    }
    branch_yes_1:;
    {
        PyObject *tmp_assign_source_35;
        PyObject *tmp_called_value_1;
        PyObject *tmp_expression_value_3;
        PyObject *tmp_args_value_1;
        PyObject *tmp_tuple_element_2;
        PyObject *tmp_kwargs_value_1;
        CHECK_OBJECT(tmp_class_creation_1__metaclass);
        tmp_expression_value_3 = tmp_class_creation_1__metaclass;
        tmp_called_value_1 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_3, mod_consts[164]);
        if (tmp_called_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_5;
        }
        tmp_tuple_element_2 = mod_consts[165];
        tmp_args_value_1 = MAKE_TUPLE_EMPTY(2);
        PyTuple_SET_ITEM0(tmp_args_value_1, 0, tmp_tuple_element_2);
        CHECK_OBJECT(tmp_class_creation_1__bases);
        tmp_tuple_element_2 = tmp_class_creation_1__bases;
        PyTuple_SET_ITEM0(tmp_args_value_1, 1, tmp_tuple_element_2);
        CHECK_OBJECT(tmp_class_creation_1__class_decl_dict);
        tmp_kwargs_value_1 = tmp_class_creation_1__class_decl_dict;
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 18;
        tmp_assign_source_35 = CALL_FUNCTION(tstate, tmp_called_value_1, tmp_args_value_1, tmp_kwargs_value_1);
        Py_DECREF(tmp_called_value_1);
        Py_DECREF(tmp_args_value_1);
        if (tmp_assign_source_35 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_5;
        }
        assert(tmp_class_creation_1__prepared == NULL);
        tmp_class_creation_1__prepared = tmp_assign_source_35;
    }
    {
        bool tmp_condition_result_3;
        PyObject *tmp_operand_value_1;
        PyObject *tmp_expression_value_4;
        CHECK_OBJECT(tmp_class_creation_1__prepared);
        tmp_expression_value_4 = tmp_class_creation_1__prepared;
        tmp_res = HAS_ATTR_BOOL2(tstate, tmp_expression_value_4, mod_consts[166]);
        if (tmp_res == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_5;
        }
        tmp_operand_value_1 = (tmp_res != 0) ? Py_True : Py_False;
        tmp_res = CHECK_IF_TRUE(tmp_operand_value_1);
        assert(!(tmp_res == -1));
        tmp_condition_result_3 = (tmp_res == 0) ? true : false;
        if (tmp_condition_result_3 != false) {
            goto branch_yes_2;
        } else {
            goto branch_no_2;
        }
    }
    branch_yes_2:;
    {
        PyObject *tmp_raise_type_1;
        PyObject *tmp_raise_value_1;
        PyObject *tmp_mod_expr_left_1;
        PyObject *tmp_mod_expr_right_1;
        PyObject *tmp_tuple_element_3;
        PyObject *tmp_expression_value_5;
        PyObject *tmp_name_value_8;
        PyObject *tmp_default_value_1;
        tmp_raise_type_1 = PyExc_TypeError;
        tmp_mod_expr_left_1 = mod_consts[167];
        CHECK_OBJECT(tmp_class_creation_1__metaclass);
        tmp_expression_value_5 = tmp_class_creation_1__metaclass;
        tmp_name_value_8 = mod_consts[6];
        tmp_default_value_1 = mod_consts[168];
        tmp_tuple_element_3 = BUILTIN_GETATTR(tstate, tmp_expression_value_5, tmp_name_value_8, tmp_default_value_1);
        if (tmp_tuple_element_3 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_5;
        }
        tmp_mod_expr_right_1 = MAKE_TUPLE_EMPTY(2);
        {
            PyObject *tmp_expression_value_6;
            PyObject *tmp_type_arg_2;
            PyTuple_SET_ITEM(tmp_mod_expr_right_1, 0, tmp_tuple_element_3);
            CHECK_OBJECT(tmp_class_creation_1__prepared);
            tmp_type_arg_2 = tmp_class_creation_1__prepared;
            tmp_expression_value_6 = BUILTIN_TYPE1(tmp_type_arg_2);
            assert(!(tmp_expression_value_6 == NULL));
            tmp_tuple_element_3 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_6, mod_consts[6]);
            Py_DECREF(tmp_expression_value_6);
            if (tmp_tuple_element_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 18;

                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_mod_expr_right_1, 1, tmp_tuple_element_3);
        }
        goto tuple_build_noexception_1;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_1:;
        Py_DECREF(tmp_mod_expr_right_1);
        goto try_except_handler_5;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_1:;
        tmp_raise_value_1 = BINARY_OPERATION_MOD_OBJECT_UNICODE_TUPLE(tmp_mod_expr_left_1, tmp_mod_expr_right_1);
        Py_DECREF(tmp_mod_expr_right_1);
        if (tmp_raise_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_5;
        }
        exception_type = tmp_raise_type_1;
        Py_INCREF(tmp_raise_type_1);
        exception_value = tmp_raise_value_1;
        exception_lineno = 18;
        RAISE_EXCEPTION_IMPLICIT(tstate, &exception_type, &exception_value, &exception_tb);

        goto try_except_handler_5;
    }
    branch_no_2:;
    goto branch_end_1;
    branch_no_1:;
    {
        PyObject *tmp_assign_source_36;
        tmp_assign_source_36 = MAKE_DICT_EMPTY();
        assert(tmp_class_creation_1__prepared == NULL);
        tmp_class_creation_1__prepared = tmp_assign_source_36;
    }
    branch_end_1:;
    {
        PyObject *tmp_assign_source_37;
        {
            PyObject *tmp_set_locals_1;
            CHECK_OBJECT(tmp_class_creation_1__prepared);
            tmp_set_locals_1 = tmp_class_creation_1__prepared;
            locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18 = tmp_set_locals_1;
            Py_INCREF(tmp_set_locals_1);
        }
        // Tried code:
        // Tried code:
        tmp_dictset_value = mod_consts[169];
        tmp_res = PyObject_SetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[170], tmp_dictset_value);
        if (tmp_res != 0) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_7;
        }
        tmp_dictset_value = mod_consts[165];
        tmp_res = PyObject_SetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[171], tmp_dictset_value);
        if (tmp_res != 0) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_7;
        }
        frame_ead9b724b65ce3c43b718984fb92cd7f_2 = MAKE_CLASS_FRAME(tstate, codeobj_ead9b724b65ce3c43b718984fb92cd7f, module_core$panic, NULL, sizeof(void *));

        // Push the new frame as the currently active one, and we should be exclusively
        // owning it.
        pushFrameStackCompiledFrame(tstate, frame_ead9b724b65ce3c43b718984fb92cd7f_2);
        assert(Py_REFCNT(frame_ead9b724b65ce3c43b718984fb92cd7f_2) == 2);

        // Framed code:
        tmp_dictset_value = mod_consts[172];
        tmp_res = PyObject_SetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[173], tmp_dictset_value);
        if (tmp_res != 0) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 19;
            type_description_2 = "o";
            goto frame_exception_exit_2;
        }
        tmp_dictset_value = MAKE_LIST1(mod_consts[172]);
        tmp_res = PyObject_SetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[174], tmp_dictset_value);
        Py_DECREF(tmp_dictset_value);
        if (tmp_res != 0) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 20;
            type_description_2 = "o";
            goto frame_exception_exit_2;
        }
        tmp_dictset_value = MAKE_LIST1(mod_consts[175]);
        tmp_res = PyObject_SetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[176], tmp_dictset_value);
        Py_DECREF(tmp_dictset_value);
        if (tmp_res != 0) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 21;
            type_description_2 = "o";
            goto frame_exception_exit_2;
        }
        tmp_dictset_value = mod_consts[177];
        tmp_res = PyObject_SetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[178], tmp_dictset_value);
        if (tmp_res != 0) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 22;
            type_description_2 = "o";
            goto frame_exception_exit_2;
        }
        tmp_dictset_value = mod_consts[179];
        tmp_res = PyObject_SetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[180], tmp_dictset_value);
        if (tmp_res != 0) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 23;
            type_description_2 = "o";
            goto frame_exception_exit_2;
        }
        {
            PyObject *tmp_dict_key_1;
            PyObject *tmp_dict_value_1;
            PyObject *tmp_list_element_1;
            PyObject *tmp_tuple_element_4;
            tmp_dict_key_1 = mod_consts[181];
            tmp_tuple_element_4 = mod_consts[182];
            tmp_list_element_1 = MAKE_TUPLE_EMPTY(2);
            PyTuple_SET_ITEM0(tmp_list_element_1, 0, tmp_tuple_element_4);
            tmp_tuple_element_4 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[156]);

            if (tmp_tuple_element_4 == NULL) {
                if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                    tmp_tuple_element_4 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156]);

                    if (unlikely(tmp_tuple_element_4 == NULL)) {
                        tmp_tuple_element_4 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[156]);
                    }

                    if (tmp_tuple_element_4 == NULL) {
                        assert(HAS_ERROR_OCCURRED(tstate));

                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                        exception_lineno = 27;
                        type_description_2 = "o";
                        goto tuple_build_exception_2;
                    }
                    Py_INCREF(tmp_tuple_element_4);
                } else {
                    goto tuple_build_exception_2;
                }
            }

            PyTuple_SET_ITEM(tmp_list_element_1, 1, tmp_tuple_element_4);
            goto tuple_build_noexception_2;
            // Exception handling pass through code for tuple_build:
            tuple_build_exception_2:;
            Py_DECREF(tmp_list_element_1);
            goto frame_exception_exit_2;
            // Finished with no exception for tuple_build:
            tuple_build_noexception_2:;
            tmp_dict_value_1 = MAKE_LIST_EMPTY(14);
            {
                PyObject *tmp_called_value_2;
                PyObject *tmp_called_value_3;
                PyObject *tmp_called_value_4;
                PyObject *tmp_called_value_5;
                PyObject *tmp_called_value_6;
                PyObject *tmp_called_value_7;
                PyObject *tmp_called_value_8;
                PyObject *tmp_called_value_9;
                PyObject *tmp_called_value_10;
                PyObject *tmp_called_value_11;
                PyObject *tmp_called_value_12;
                PyObject *tmp_called_value_13;
                PyObject *tmp_tuple_element_5;
                PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_1);
                tmp_called_value_2 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[152]);

                if (tmp_called_value_2 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_called_value_2 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[152]);

                        if (unlikely(tmp_called_value_2 == NULL)) {
                            tmp_called_value_2 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[152]);
                        }

                        if (tmp_called_value_2 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 28;
                            type_description_2 = "o";
                            goto list_build_exception_1;
                        }
                        Py_INCREF(tmp_called_value_2);
                    } else {
                        goto list_build_exception_1;
                    }
                }

                frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 28;
                tmp_list_element_1 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_2, mod_consts[183]);

                Py_DECREF(tmp_called_value_2);
                if (tmp_list_element_1 == NULL) {
                    assert(HAS_ERROR_OCCURRED(tstate));

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                    exception_lineno = 28;
                    type_description_2 = "o";
                    goto list_build_exception_1;
                }
                PyList_SET_ITEM(tmp_dict_value_1, 1, tmp_list_element_1);
                tmp_called_value_3 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[152]);

                if (tmp_called_value_3 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_called_value_3 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[152]);

                        if (unlikely(tmp_called_value_3 == NULL)) {
                            tmp_called_value_3 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[152]);
                        }

                        if (tmp_called_value_3 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 29;
                            type_description_2 = "o";
                            goto list_build_exception_1;
                        }
                        Py_INCREF(tmp_called_value_3);
                    } else {
                        goto list_build_exception_1;
                    }
                }

                frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 29;
                tmp_list_element_1 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_3, mod_consts[184]);

                Py_DECREF(tmp_called_value_3);
                if (tmp_list_element_1 == NULL) {
                    assert(HAS_ERROR_OCCURRED(tstate));

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                    exception_lineno = 29;
                    type_description_2 = "o";
                    goto list_build_exception_1;
                }
                PyList_SET_ITEM(tmp_dict_value_1, 2, tmp_list_element_1);
                tmp_called_value_4 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[152]);

                if (tmp_called_value_4 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_called_value_4 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[152]);

                        if (unlikely(tmp_called_value_4 == NULL)) {
                            tmp_called_value_4 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[152]);
                        }

                        if (tmp_called_value_4 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 30;
                            type_description_2 = "o";
                            goto list_build_exception_1;
                        }
                        Py_INCREF(tmp_called_value_4);
                    } else {
                        goto list_build_exception_1;
                    }
                }

                frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 30;
                tmp_list_element_1 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_4, mod_consts[185]);

                Py_DECREF(tmp_called_value_4);
                if (tmp_list_element_1 == NULL) {
                    assert(HAS_ERROR_OCCURRED(tstate));

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                    exception_lineno = 30;
                    type_description_2 = "o";
                    goto list_build_exception_1;
                }
                PyList_SET_ITEM(tmp_dict_value_1, 3, tmp_list_element_1);
                tmp_called_value_5 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[152]);

                if (tmp_called_value_5 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_called_value_5 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[152]);

                        if (unlikely(tmp_called_value_5 == NULL)) {
                            tmp_called_value_5 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[152]);
                        }

                        if (tmp_called_value_5 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 31;
                            type_description_2 = "o";
                            goto list_build_exception_1;
                        }
                        Py_INCREF(tmp_called_value_5);
                    } else {
                        goto list_build_exception_1;
                    }
                }

                frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 31;
                tmp_list_element_1 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_5, mod_consts[186]);

                Py_DECREF(tmp_called_value_5);
                if (tmp_list_element_1 == NULL) {
                    assert(HAS_ERROR_OCCURRED(tstate));

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                    exception_lineno = 31;
                    type_description_2 = "o";
                    goto list_build_exception_1;
                }
                PyList_SET_ITEM(tmp_dict_value_1, 4, tmp_list_element_1);
                tmp_called_value_6 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[152]);

                if (tmp_called_value_6 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_called_value_6 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[152]);

                        if (unlikely(tmp_called_value_6 == NULL)) {
                            tmp_called_value_6 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[152]);
                        }

                        if (tmp_called_value_6 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 32;
                            type_description_2 = "o";
                            goto list_build_exception_1;
                        }
                        Py_INCREF(tmp_called_value_6);
                    } else {
                        goto list_build_exception_1;
                    }
                }

                frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 32;
                tmp_list_element_1 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_6, mod_consts[187]);

                Py_DECREF(tmp_called_value_6);
                if (tmp_list_element_1 == NULL) {
                    assert(HAS_ERROR_OCCURRED(tstate));

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                    exception_lineno = 32;
                    type_description_2 = "o";
                    goto list_build_exception_1;
                }
                PyList_SET_ITEM(tmp_dict_value_1, 5, tmp_list_element_1);
                tmp_called_value_7 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[152]);

                if (tmp_called_value_7 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_called_value_7 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[152]);

                        if (unlikely(tmp_called_value_7 == NULL)) {
                            tmp_called_value_7 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[152]);
                        }

                        if (tmp_called_value_7 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 33;
                            type_description_2 = "o";
                            goto list_build_exception_1;
                        }
                        Py_INCREF(tmp_called_value_7);
                    } else {
                        goto list_build_exception_1;
                    }
                }

                frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 33;
                tmp_list_element_1 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_7, mod_consts[188]);

                Py_DECREF(tmp_called_value_7);
                if (tmp_list_element_1 == NULL) {
                    assert(HAS_ERROR_OCCURRED(tstate));

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                    exception_lineno = 33;
                    type_description_2 = "o";
                    goto list_build_exception_1;
                }
                PyList_SET_ITEM(tmp_dict_value_1, 6, tmp_list_element_1);
                tmp_called_value_8 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[152]);

                if (tmp_called_value_8 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_called_value_8 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[152]);

                        if (unlikely(tmp_called_value_8 == NULL)) {
                            tmp_called_value_8 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[152]);
                        }

                        if (tmp_called_value_8 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 34;
                            type_description_2 = "o";
                            goto list_build_exception_1;
                        }
                        Py_INCREF(tmp_called_value_8);
                    } else {
                        goto list_build_exception_1;
                    }
                }

                frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 34;
                tmp_list_element_1 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_8, mod_consts[189]);

                Py_DECREF(tmp_called_value_8);
                if (tmp_list_element_1 == NULL) {
                    assert(HAS_ERROR_OCCURRED(tstate));

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                    exception_lineno = 34;
                    type_description_2 = "o";
                    goto list_build_exception_1;
                }
                PyList_SET_ITEM(tmp_dict_value_1, 7, tmp_list_element_1);
                tmp_called_value_9 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[152]);

                if (tmp_called_value_9 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_called_value_9 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[152]);

                        if (unlikely(tmp_called_value_9 == NULL)) {
                            tmp_called_value_9 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[152]);
                        }

                        if (tmp_called_value_9 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 35;
                            type_description_2 = "o";
                            goto list_build_exception_1;
                        }
                        Py_INCREF(tmp_called_value_9);
                    } else {
                        goto list_build_exception_1;
                    }
                }

                frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 35;
                tmp_list_element_1 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_9, mod_consts[190]);

                Py_DECREF(tmp_called_value_9);
                if (tmp_list_element_1 == NULL) {
                    assert(HAS_ERROR_OCCURRED(tstate));

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                    exception_lineno = 35;
                    type_description_2 = "o";
                    goto list_build_exception_1;
                }
                PyList_SET_ITEM(tmp_dict_value_1, 8, tmp_list_element_1);
                tmp_called_value_10 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[152]);

                if (tmp_called_value_10 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_called_value_10 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[152]);

                        if (unlikely(tmp_called_value_10 == NULL)) {
                            tmp_called_value_10 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[152]);
                        }

                        if (tmp_called_value_10 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 36;
                            type_description_2 = "o";
                            goto list_build_exception_1;
                        }
                        Py_INCREF(tmp_called_value_10);
                    } else {
                        goto list_build_exception_1;
                    }
                }

                frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 36;
                tmp_list_element_1 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_10, mod_consts[191]);

                Py_DECREF(tmp_called_value_10);
                if (tmp_list_element_1 == NULL) {
                    assert(HAS_ERROR_OCCURRED(tstate));

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                    exception_lineno = 36;
                    type_description_2 = "o";
                    goto list_build_exception_1;
                }
                PyList_SET_ITEM(tmp_dict_value_1, 9, tmp_list_element_1);
                tmp_called_value_11 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[152]);

                if (tmp_called_value_11 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_called_value_11 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[152]);

                        if (unlikely(tmp_called_value_11 == NULL)) {
                            tmp_called_value_11 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[152]);
                        }

                        if (tmp_called_value_11 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 37;
                            type_description_2 = "o";
                            goto list_build_exception_1;
                        }
                        Py_INCREF(tmp_called_value_11);
                    } else {
                        goto list_build_exception_1;
                    }
                }

                frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 37;
                tmp_list_element_1 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_11, mod_consts[192]);

                Py_DECREF(tmp_called_value_11);
                if (tmp_list_element_1 == NULL) {
                    assert(HAS_ERROR_OCCURRED(tstate));

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                    exception_lineno = 37;
                    type_description_2 = "o";
                    goto list_build_exception_1;
                }
                PyList_SET_ITEM(tmp_dict_value_1, 10, tmp_list_element_1);
                tmp_called_value_12 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[152]);

                if (tmp_called_value_12 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_called_value_12 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[152]);

                        if (unlikely(tmp_called_value_12 == NULL)) {
                            tmp_called_value_12 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[152]);
                        }

                        if (tmp_called_value_12 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 38;
                            type_description_2 = "o";
                            goto list_build_exception_1;
                        }
                        Py_INCREF(tmp_called_value_12);
                    } else {
                        goto list_build_exception_1;
                    }
                }

                frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 38;
                tmp_list_element_1 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_12, mod_consts[193]);

                Py_DECREF(tmp_called_value_12);
                if (tmp_list_element_1 == NULL) {
                    assert(HAS_ERROR_OCCURRED(tstate));

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                    exception_lineno = 38;
                    type_description_2 = "o";
                    goto list_build_exception_1;
                }
                PyList_SET_ITEM(tmp_dict_value_1, 11, tmp_list_element_1);
                tmp_called_value_13 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[152]);

                if (tmp_called_value_13 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_called_value_13 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[152]);

                        if (unlikely(tmp_called_value_13 == NULL)) {
                            tmp_called_value_13 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[152]);
                        }

                        if (tmp_called_value_13 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 39;
                            type_description_2 = "o";
                            goto list_build_exception_1;
                        }
                        Py_INCREF(tmp_called_value_13);
                    } else {
                        goto list_build_exception_1;
                    }
                }

                frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 39;
                tmp_list_element_1 = CALL_FUNCTION_WITH_POSARGS1(tstate, tmp_called_value_13, mod_consts[194]);

                Py_DECREF(tmp_called_value_13);
                if (tmp_list_element_1 == NULL) {
                    assert(HAS_ERROR_OCCURRED(tstate));

                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                    exception_lineno = 39;
                    type_description_2 = "o";
                    goto list_build_exception_1;
                }
                PyList_SET_ITEM(tmp_dict_value_1, 12, tmp_list_element_1);
                tmp_tuple_element_5 = mod_consts[195];
                tmp_list_element_1 = MAKE_TUPLE_EMPTY(2);
                PyTuple_SET_ITEM0(tmp_list_element_1, 0, tmp_tuple_element_5);
                tmp_tuple_element_5 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[163]);

                if (tmp_tuple_element_5 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_tuple_element_5 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[163]);

                        if (unlikely(tmp_tuple_element_5 == NULL)) {
                            tmp_tuple_element_5 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[163]);
                        }

                        if (tmp_tuple_element_5 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 40;
                            type_description_2 = "o";
                            goto tuple_build_exception_3;
                        }
                        Py_INCREF(tmp_tuple_element_5);
                    } else {
                        goto tuple_build_exception_3;
                    }
                }

                PyTuple_SET_ITEM(tmp_list_element_1, 1, tmp_tuple_element_5);
                goto tuple_build_noexception_3;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_3:;
                Py_DECREF(tmp_list_element_1);
                goto list_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_3:;
                PyList_SET_ITEM(tmp_dict_value_1, 13, tmp_list_element_1);
            }
            goto list_build_noexception_1;
            // Exception handling pass through code for list_build:
            list_build_exception_1:;
            Py_DECREF(tmp_dict_value_1);
            goto frame_exception_exit_2;
            // Finished with no exception for list_build:
            list_build_noexception_1:;
            tmp_dictset_value = _PyDict_NewPresized( 14 );
            {
                PyObject *tmp_list_element_2;
                PyObject *tmp_tuple_element_6;
                PyObject *tmp_list_element_3;
                PyObject *tmp_tuple_element_7;
                PyObject *tmp_list_element_4;
                PyObject *tmp_tuple_element_9;
                PyObject *tmp_list_element_5;
                PyObject *tmp_tuple_element_13;
                PyObject *tmp_list_element_6;
                PyObject *tmp_tuple_element_18;
                PyObject *tmp_list_element_7;
                PyObject *tmp_tuple_element_23;
                PyObject *tmp_list_element_8;
                PyObject *tmp_tuple_element_34;
                PyObject *tmp_list_element_9;
                PyObject *tmp_tuple_element_37;
                PyObject *tmp_list_element_10;
                PyObject *tmp_tuple_element_38;
                PyObject *tmp_list_element_11;
                PyObject *tmp_tuple_element_39;
                PyObject *tmp_list_element_12;
                PyObject *tmp_tuple_element_42;
                PyObject *tmp_list_element_13;
                PyObject *tmp_tuple_element_44;
                PyObject *tmp_list_element_14;
                PyObject *tmp_tuple_element_45;
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
                tmp_dict_key_1 = mod_consts[196];
                tmp_tuple_element_6 = mod_consts[197];
                tmp_list_element_2 = MAKE_TUPLE_EMPTY(2);
                {
                    PyObject *tmp_expression_value_7;
                    PyTuple_SET_ITEM0(tmp_list_element_2, 0, tmp_tuple_element_6);
                    tmp_expression_value_7 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[155]);

                    if (tmp_expression_value_7 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_expression_value_7 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[155]);

                            if (unlikely(tmp_expression_value_7 == NULL)) {
                                tmp_expression_value_7 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[155]);
                            }

                            if (tmp_expression_value_7 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 43;
                                type_description_2 = "o";
                                goto tuple_build_exception_4;
                            }
                            Py_INCREF(tmp_expression_value_7);
                        } else {
                            goto tuple_build_exception_4;
                        }
                    }

                    tmp_tuple_element_6 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_7, mod_consts[198]);
                    Py_DECREF(tmp_expression_value_7);
                    if (tmp_tuple_element_6 == NULL) {
                        assert(HAS_ERROR_OCCURRED(tstate));

                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                        exception_lineno = 43;
                        type_description_2 = "o";
                        goto tuple_build_exception_4;
                    }
                    PyTuple_SET_ITEM(tmp_list_element_2, 1, tmp_tuple_element_6);
                }
                goto tuple_build_noexception_4;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_4:;
                Py_DECREF(tmp_list_element_2);
                goto dict_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_4:;
                tmp_dict_value_1 = MAKE_LIST_EMPTY(1);
                PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_2);
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
                tmp_dict_key_1 = mod_consts[199];
                tmp_tuple_element_7 = mod_consts[200];
                tmp_list_element_3 = MAKE_TUPLE_EMPTY(3);
                {
                    PyObject *tmp_expression_value_8;
                    PyTuple_SET_ITEM0(tmp_list_element_3, 0, tmp_tuple_element_7);
                    tmp_expression_value_8 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[155]);

                    if (tmp_expression_value_8 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_expression_value_8 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[155]);

                            if (unlikely(tmp_expression_value_8 == NULL)) {
                                tmp_expression_value_8 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[155]);
                            }

                            if (tmp_expression_value_8 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 46;
                                type_description_2 = "o";
                                goto tuple_build_exception_5;
                            }
                            Py_INCREF(tmp_expression_value_8);
                        } else {
                            goto tuple_build_exception_5;
                        }
                    }

                    tmp_tuple_element_7 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_8, mod_consts[201]);
                    Py_DECREF(tmp_expression_value_8);
                    if (tmp_tuple_element_7 == NULL) {
                        assert(HAS_ERROR_OCCURRED(tstate));

                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                        exception_lineno = 46;
                        type_description_2 = "o";
                        goto tuple_build_exception_5;
                    }
                    PyTuple_SET_ITEM(tmp_list_element_3, 1, tmp_tuple_element_7);
                    tmp_tuple_element_7 = mod_consts[202];
                    PyTuple_SET_ITEM0(tmp_list_element_3, 2, tmp_tuple_element_7);
                }
                goto tuple_build_noexception_5;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_5:;
                Py_DECREF(tmp_list_element_3);
                goto dict_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_5:;
                tmp_dict_value_1 = MAKE_LIST_EMPTY(2);
                {
                    PyObject *tmp_tuple_element_8;
                    PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_3);
                    tmp_tuple_element_8 = mod_consts[203];
                    tmp_list_element_3 = MAKE_TUPLE_EMPTY(3);
                    {
                        PyObject *tmp_expression_value_9;
                        PyTuple_SET_ITEM0(tmp_list_element_3, 0, tmp_tuple_element_8);
                        tmp_expression_value_9 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[155]);

                        if (tmp_expression_value_9 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_expression_value_9 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[155]);

                                if (unlikely(tmp_expression_value_9 == NULL)) {
                                    tmp_expression_value_9 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[155]);
                                }

                                if (tmp_expression_value_9 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                    exception_lineno = 47;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_6;
                                }
                                Py_INCREF(tmp_expression_value_9);
                            } else {
                                goto tuple_build_exception_6;
                            }
                        }

                        tmp_tuple_element_8 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_9, mod_consts[201]);
                        Py_DECREF(tmp_expression_value_9);
                        if (tmp_tuple_element_8 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 47;
                            type_description_2 = "o";
                            goto tuple_build_exception_6;
                        }
                        PyTuple_SET_ITEM(tmp_list_element_3, 1, tmp_tuple_element_8);
                        tmp_tuple_element_8 = mod_consts[202];
                        PyTuple_SET_ITEM0(tmp_list_element_3, 2, tmp_tuple_element_8);
                    }
                    goto tuple_build_noexception_6;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_6:;
                    Py_DECREF(tmp_list_element_3);
                    goto list_build_exception_2;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_6:;
                    PyList_SET_ITEM(tmp_dict_value_1, 1, tmp_list_element_3);
                }
                goto list_build_noexception_2;
                // Exception handling pass through code for list_build:
                list_build_exception_2:;
                Py_DECREF(tmp_dict_value_1);
                goto dict_build_exception_1;
                // Finished with no exception for list_build:
                list_build_noexception_2:;
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
                tmp_dict_key_1 = mod_consts[202];
                tmp_tuple_element_9 = mod_consts[204];
                tmp_list_element_4 = MAKE_TUPLE_EMPTY(2);
                {
                    PyObject *tmp_expression_value_10;
                    PyTuple_SET_ITEM0(tmp_list_element_4, 0, tmp_tuple_element_9);
                    tmp_expression_value_10 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[155]);

                    if (tmp_expression_value_10 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_expression_value_10 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[155]);

                            if (unlikely(tmp_expression_value_10 == NULL)) {
                                tmp_expression_value_10 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[155]);
                            }

                            if (tmp_expression_value_10 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 50;
                                type_description_2 = "o";
                                goto tuple_build_exception_7;
                            }
                            Py_INCREF(tmp_expression_value_10);
                        } else {
                            goto tuple_build_exception_7;
                        }
                    }

                    tmp_tuple_element_9 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_10, mod_consts[201]);
                    Py_DECREF(tmp_expression_value_10);
                    if (tmp_tuple_element_9 == NULL) {
                        assert(HAS_ERROR_OCCURRED(tstate));

                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                        exception_lineno = 50;
                        type_description_2 = "o";
                        goto tuple_build_exception_7;
                    }
                    PyTuple_SET_ITEM(tmp_list_element_4, 1, tmp_tuple_element_9);
                }
                goto tuple_build_noexception_7;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_7:;
                Py_DECREF(tmp_list_element_4);
                goto dict_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_7:;
                tmp_dict_value_1 = MAKE_LIST_EMPTY(4);
                {
                    PyObject *tmp_tuple_element_10;
                    PyObject *tmp_tuple_element_11;
                    PyObject *tmp_tuple_element_12;
                    PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_4);
                    tmp_tuple_element_10 = mod_consts[203];
                    tmp_list_element_4 = MAKE_TUPLE_EMPTY(3);
                    {
                        PyObject *tmp_expression_value_11;
                        PyTuple_SET_ITEM0(tmp_list_element_4, 0, tmp_tuple_element_10);
                        tmp_expression_value_11 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[155]);

                        if (tmp_expression_value_11 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_expression_value_11 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[155]);

                                if (unlikely(tmp_expression_value_11 == NULL)) {
                                    tmp_expression_value_11 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[155]);
                                }

                                if (tmp_expression_value_11 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                    exception_lineno = 51;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_8;
                                }
                                Py_INCREF(tmp_expression_value_11);
                            } else {
                                goto tuple_build_exception_8;
                            }
                        }

                        tmp_tuple_element_10 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_11, mod_consts[201]);
                        Py_DECREF(tmp_expression_value_11);
                        if (tmp_tuple_element_10 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 51;
                            type_description_2 = "o";
                            goto tuple_build_exception_8;
                        }
                        PyTuple_SET_ITEM(tmp_list_element_4, 1, tmp_tuple_element_10);
                        tmp_tuple_element_10 = mod_consts[205];
                        PyTuple_SET_ITEM0(tmp_list_element_4, 2, tmp_tuple_element_10);
                    }
                    goto tuple_build_noexception_8;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_8:;
                    Py_DECREF(tmp_list_element_4);
                    goto list_build_exception_3;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_8:;
                    PyList_SET_ITEM(tmp_dict_value_1, 1, tmp_list_element_4);
                    tmp_tuple_element_11 = mod_consts[206];
                    tmp_list_element_4 = MAKE_TUPLE_EMPTY(3);
                    {
                        PyObject *tmp_expression_value_12;
                        PyTuple_SET_ITEM0(tmp_list_element_4, 0, tmp_tuple_element_11);
                        tmp_expression_value_12 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[155]);

                        if (tmp_expression_value_12 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_expression_value_12 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[155]);

                                if (unlikely(tmp_expression_value_12 == NULL)) {
                                    tmp_expression_value_12 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[155]);
                                }

                                if (tmp_expression_value_12 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                    exception_lineno = 52;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_9;
                                }
                                Py_INCREF(tmp_expression_value_12);
                            } else {
                                goto tuple_build_exception_9;
                            }
                        }

                        tmp_tuple_element_11 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_12, mod_consts[201]);
                        Py_DECREF(tmp_expression_value_12);
                        if (tmp_tuple_element_11 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 52;
                            type_description_2 = "o";
                            goto tuple_build_exception_9;
                        }
                        PyTuple_SET_ITEM(tmp_list_element_4, 1, tmp_tuple_element_11);
                        tmp_tuple_element_11 = mod_consts[207];
                        PyTuple_SET_ITEM0(tmp_list_element_4, 2, tmp_tuple_element_11);
                    }
                    goto tuple_build_noexception_9;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_9:;
                    Py_DECREF(tmp_list_element_4);
                    goto list_build_exception_3;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_9:;
                    PyList_SET_ITEM(tmp_dict_value_1, 2, tmp_list_element_4);
                    tmp_tuple_element_12 = mod_consts[62];
                    tmp_list_element_4 = MAKE_TUPLE_EMPTY(2);
                    {
                        PyObject *tmp_expression_value_13;
                        PyTuple_SET_ITEM0(tmp_list_element_4, 0, tmp_tuple_element_12);
                        tmp_expression_value_13 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[155]);

                        if (tmp_expression_value_13 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_expression_value_13 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[155]);

                                if (unlikely(tmp_expression_value_13 == NULL)) {
                                    tmp_expression_value_13 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[155]);
                                }

                                if (tmp_expression_value_13 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                    exception_lineno = 53;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_10;
                                }
                                Py_INCREF(tmp_expression_value_13);
                            } else {
                                goto tuple_build_exception_10;
                            }
                        }

                        tmp_tuple_element_12 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_13, mod_consts[201]);
                        Py_DECREF(tmp_expression_value_13);
                        if (tmp_tuple_element_12 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 53;
                            type_description_2 = "o";
                            goto tuple_build_exception_10;
                        }
                        PyTuple_SET_ITEM(tmp_list_element_4, 1, tmp_tuple_element_12);
                    }
                    goto tuple_build_noexception_10;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_10:;
                    Py_DECREF(tmp_list_element_4);
                    goto list_build_exception_3;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_10:;
                    PyList_SET_ITEM(tmp_dict_value_1, 3, tmp_list_element_4);
                }
                goto list_build_noexception_3;
                // Exception handling pass through code for list_build:
                list_build_exception_3:;
                Py_DECREF(tmp_dict_value_1);
                goto dict_build_exception_1;
                // Finished with no exception for list_build:
                list_build_noexception_3:;
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
                tmp_dict_key_1 = mod_consts[208];
                tmp_tuple_element_13 = mod_consts[209];
                tmp_list_element_5 = MAKE_TUPLE_EMPTY(2);
                PyTuple_SET_ITEM0(tmp_list_element_5, 0, tmp_tuple_element_13);
                tmp_tuple_element_13 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[159]);

                if (tmp_tuple_element_13 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_tuple_element_13 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[159]);

                        if (unlikely(tmp_tuple_element_13 == NULL)) {
                            tmp_tuple_element_13 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[159]);
                        }

                        if (tmp_tuple_element_13 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 56;
                            type_description_2 = "o";
                            goto tuple_build_exception_11;
                        }
                        Py_INCREF(tmp_tuple_element_13);
                    } else {
                        goto tuple_build_exception_11;
                    }
                }

                PyTuple_SET_ITEM(tmp_list_element_5, 1, tmp_tuple_element_13);
                goto tuple_build_noexception_11;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_11:;
                Py_DECREF(tmp_list_element_5);
                goto dict_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_11:;
                tmp_dict_value_1 = MAKE_LIST_EMPTY(5);
                {
                    PyObject *tmp_tuple_element_14;
                    PyObject *tmp_tuple_element_15;
                    PyObject *tmp_tuple_element_16;
                    PyObject *tmp_tuple_element_17;
                    PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_5);
                    tmp_tuple_element_14 = mod_consts[210];
                    tmp_list_element_5 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_5, 0, tmp_tuple_element_14);
                    tmp_tuple_element_14 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[159]);

                    if (tmp_tuple_element_14 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_14 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[159]);

                            if (unlikely(tmp_tuple_element_14 == NULL)) {
                                tmp_tuple_element_14 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[159]);
                            }

                            if (tmp_tuple_element_14 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 57;
                                type_description_2 = "o";
                                goto tuple_build_exception_12;
                            }
                            Py_INCREF(tmp_tuple_element_14);
                        } else {
                            goto tuple_build_exception_12;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_5, 1, tmp_tuple_element_14);
                    goto tuple_build_noexception_12;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_12:;
                    Py_DECREF(tmp_list_element_5);
                    goto list_build_exception_4;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_12:;
                    PyList_SET_ITEM(tmp_dict_value_1, 1, tmp_list_element_5);
                    tmp_tuple_element_15 = mod_consts[211];
                    tmp_list_element_5 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_5, 0, tmp_tuple_element_15);
                    tmp_tuple_element_15 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[159]);

                    if (tmp_tuple_element_15 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_15 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[159]);

                            if (unlikely(tmp_tuple_element_15 == NULL)) {
                                tmp_tuple_element_15 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[159]);
                            }

                            if (tmp_tuple_element_15 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 58;
                                type_description_2 = "o";
                                goto tuple_build_exception_13;
                            }
                            Py_INCREF(tmp_tuple_element_15);
                        } else {
                            goto tuple_build_exception_13;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_5, 1, tmp_tuple_element_15);
                    goto tuple_build_noexception_13;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_13:;
                    Py_DECREF(tmp_list_element_5);
                    goto list_build_exception_4;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_13:;
                    PyList_SET_ITEM(tmp_dict_value_1, 2, tmp_list_element_5);
                    tmp_tuple_element_16 = mod_consts[212];
                    tmp_list_element_5 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_5, 0, tmp_tuple_element_16);
                    tmp_tuple_element_16 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[159]);

                    if (tmp_tuple_element_16 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_16 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[159]);

                            if (unlikely(tmp_tuple_element_16 == NULL)) {
                                tmp_tuple_element_16 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[159]);
                            }

                            if (tmp_tuple_element_16 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 59;
                                type_description_2 = "o";
                                goto tuple_build_exception_14;
                            }
                            Py_INCREF(tmp_tuple_element_16);
                        } else {
                            goto tuple_build_exception_14;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_5, 1, tmp_tuple_element_16);
                    goto tuple_build_noexception_14;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_14:;
                    Py_DECREF(tmp_list_element_5);
                    goto list_build_exception_4;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_14:;
                    PyList_SET_ITEM(tmp_dict_value_1, 3, tmp_list_element_5);
                    tmp_tuple_element_17 = mod_consts[213];
                    tmp_list_element_5 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_5, 0, tmp_tuple_element_17);
                    tmp_tuple_element_17 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[157]);

                    if (tmp_tuple_element_17 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_17 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[157]);

                            if (unlikely(tmp_tuple_element_17 == NULL)) {
                                tmp_tuple_element_17 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[157]);
                            }

                            if (tmp_tuple_element_17 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 60;
                                type_description_2 = "o";
                                goto tuple_build_exception_15;
                            }
                            Py_INCREF(tmp_tuple_element_17);
                        } else {
                            goto tuple_build_exception_15;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_5, 1, tmp_tuple_element_17);
                    goto tuple_build_noexception_15;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_15:;
                    Py_DECREF(tmp_list_element_5);
                    goto list_build_exception_4;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_15:;
                    PyList_SET_ITEM(tmp_dict_value_1, 4, tmp_list_element_5);
                }
                goto list_build_noexception_4;
                // Exception handling pass through code for list_build:
                list_build_exception_4:;
                Py_DECREF(tmp_dict_value_1);
                goto dict_build_exception_1;
                // Finished with no exception for list_build:
                list_build_noexception_4:;
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
                tmp_dict_key_1 = mod_consts[214];
                tmp_tuple_element_18 = mod_consts[215];
                tmp_list_element_6 = MAKE_TUPLE_EMPTY(2);
                {
                    PyObject *tmp_expression_value_14;
                    PyTuple_SET_ITEM0(tmp_list_element_6, 0, tmp_tuple_element_18);
                    tmp_expression_value_14 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                    if (tmp_expression_value_14 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_expression_value_14 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                            if (unlikely(tmp_expression_value_14 == NULL)) {
                                tmp_expression_value_14 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                            }

                            if (tmp_expression_value_14 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 63;
                                type_description_2 = "o";
                                goto tuple_build_exception_16;
                            }
                            Py_INCREF(tmp_expression_value_14);
                        } else {
                            goto tuple_build_exception_16;
                        }
                    }

                    tmp_tuple_element_18 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_14, mod_consts[216]);
                    Py_DECREF(tmp_expression_value_14);
                    if (tmp_tuple_element_18 == NULL) {
                        assert(HAS_ERROR_OCCURRED(tstate));

                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                        exception_lineno = 63;
                        type_description_2 = "o";
                        goto tuple_build_exception_16;
                    }
                    PyTuple_SET_ITEM(tmp_list_element_6, 1, tmp_tuple_element_18);
                }
                goto tuple_build_noexception_16;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_16:;
                Py_DECREF(tmp_list_element_6);
                goto dict_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_16:;
                tmp_dict_value_1 = MAKE_LIST_EMPTY(5);
                {
                    PyObject *tmp_tuple_element_19;
                    PyObject *tmp_tuple_element_20;
                    PyObject *tmp_tuple_element_21;
                    PyObject *tmp_tuple_element_22;
                    PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_6);
                    tmp_tuple_element_19 = mod_consts[217];
                    tmp_list_element_6 = MAKE_TUPLE_EMPTY(2);
                    {
                        PyObject *tmp_expression_value_15;
                        PyTuple_SET_ITEM0(tmp_list_element_6, 0, tmp_tuple_element_19);
                        tmp_expression_value_15 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                        if (tmp_expression_value_15 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_expression_value_15 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                                if (unlikely(tmp_expression_value_15 == NULL)) {
                                    tmp_expression_value_15 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                                }

                                if (tmp_expression_value_15 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                    exception_lineno = 64;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_17;
                                }
                                Py_INCREF(tmp_expression_value_15);
                            } else {
                                goto tuple_build_exception_17;
                            }
                        }

                        tmp_tuple_element_19 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_15, mod_consts[218]);
                        Py_DECREF(tmp_expression_value_15);
                        if (tmp_tuple_element_19 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 64;
                            type_description_2 = "o";
                            goto tuple_build_exception_17;
                        }
                        PyTuple_SET_ITEM(tmp_list_element_6, 1, tmp_tuple_element_19);
                    }
                    goto tuple_build_noexception_17;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_17:;
                    Py_DECREF(tmp_list_element_6);
                    goto list_build_exception_5;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_17:;
                    PyList_SET_ITEM(tmp_dict_value_1, 1, tmp_list_element_6);
                    tmp_tuple_element_20 = mod_consts[219];
                    tmp_list_element_6 = MAKE_TUPLE_EMPTY(2);
                    {
                        PyObject *tmp_expression_value_16;
                        PyTuple_SET_ITEM0(tmp_list_element_6, 0, tmp_tuple_element_20);
                        tmp_expression_value_16 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                        if (tmp_expression_value_16 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_expression_value_16 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                                if (unlikely(tmp_expression_value_16 == NULL)) {
                                    tmp_expression_value_16 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                                }

                                if (tmp_expression_value_16 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                    exception_lineno = 65;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_18;
                                }
                                Py_INCREF(tmp_expression_value_16);
                            } else {
                                goto tuple_build_exception_18;
                            }
                        }

                        tmp_tuple_element_20 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_16, mod_consts[218]);
                        Py_DECREF(tmp_expression_value_16);
                        if (tmp_tuple_element_20 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 65;
                            type_description_2 = "o";
                            goto tuple_build_exception_18;
                        }
                        PyTuple_SET_ITEM(tmp_list_element_6, 1, tmp_tuple_element_20);
                    }
                    goto tuple_build_noexception_18;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_18:;
                    Py_DECREF(tmp_list_element_6);
                    goto list_build_exception_5;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_18:;
                    PyList_SET_ITEM(tmp_dict_value_1, 2, tmp_list_element_6);
                    tmp_tuple_element_21 = mod_consts[220];
                    tmp_list_element_6 = MAKE_TUPLE_EMPTY(2);
                    {
                        PyObject *tmp_called_value_14;
                        PyObject *tmp_args_element_value_1;
                        PyObject *tmp_args_element_value_2;
                        PyObject *tmp_expression_value_17;
                        PyObject *tmp_args_element_value_3;
                        PyObject *tmp_args_element_value_4;
                        PyObject *tmp_expression_value_18;
                        PyObject *tmp_args_element_value_5;
                        PyTuple_SET_ITEM0(tmp_list_element_6, 0, tmp_tuple_element_21);
                        tmp_called_value_14 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[151]);

                        if (tmp_called_value_14 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_called_value_14 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[151]);

                                if (unlikely(tmp_called_value_14 == NULL)) {
                                    tmp_called_value_14 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[151]);
                                }

                                if (tmp_called_value_14 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                    exception_lineno = 66;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_19;
                                }
                                Py_INCREF(tmp_called_value_14);
                            } else {
                                goto tuple_build_exception_19;
                            }
                        }

                        tmp_args_element_value_1 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[156]);

                        if (tmp_args_element_value_1 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_args_element_value_1 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156]);

                                if (unlikely(tmp_args_element_value_1 == NULL)) {
                                    tmp_args_element_value_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[156]);
                                }

                                if (tmp_args_element_value_1 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                                    Py_DECREF(tmp_called_value_14);

                                    exception_lineno = 66;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_19;
                                }
                                Py_INCREF(tmp_args_element_value_1);
                            } else {
                                goto tuple_build_exception_19;
                            }
                        }

                        tmp_expression_value_17 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                        if (tmp_expression_value_17 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_expression_value_17 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                                if (unlikely(tmp_expression_value_17 == NULL)) {
                                    tmp_expression_value_17 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                                }

                                if (tmp_expression_value_17 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                                    Py_DECREF(tmp_called_value_14);
                                    Py_DECREF(tmp_args_element_value_1);

                                    exception_lineno = 66;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_19;
                                }
                                Py_INCREF(tmp_expression_value_17);
                            } else {
                                goto tuple_build_exception_19;
                            }
                        }

                        tmp_args_element_value_2 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_17, mod_consts[218]);
                        Py_DECREF(tmp_expression_value_17);
                        if (tmp_args_element_value_2 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                            Py_DECREF(tmp_called_value_14);
                            Py_DECREF(tmp_args_element_value_1);

                            exception_lineno = 66;
                            type_description_2 = "o";
                            goto tuple_build_exception_19;
                        }
                        tmp_args_element_value_3 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[161]);

                        if (tmp_args_element_value_3 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_args_element_value_3 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[161]);

                                if (unlikely(tmp_args_element_value_3 == NULL)) {
                                    tmp_args_element_value_3 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[161]);
                                }

                                if (tmp_args_element_value_3 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                                    Py_DECREF(tmp_called_value_14);
                                    Py_DECREF(tmp_args_element_value_1);
                                    Py_DECREF(tmp_args_element_value_2);

                                    exception_lineno = 66;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_19;
                                }
                                Py_INCREF(tmp_args_element_value_3);
                            } else {
                                goto tuple_build_exception_19;
                            }
                        }

                        tmp_expression_value_18 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                        if (tmp_expression_value_18 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_expression_value_18 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                                if (unlikely(tmp_expression_value_18 == NULL)) {
                                    tmp_expression_value_18 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                                }

                                if (tmp_expression_value_18 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                                    Py_DECREF(tmp_called_value_14);
                                    Py_DECREF(tmp_args_element_value_1);
                                    Py_DECREF(tmp_args_element_value_2);
                                    Py_DECREF(tmp_args_element_value_3);

                                    exception_lineno = 66;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_19;
                                }
                                Py_INCREF(tmp_expression_value_18);
                            } else {
                                goto tuple_build_exception_19;
                            }
                        }

                        tmp_args_element_value_4 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_18, mod_consts[218]);
                        Py_DECREF(tmp_expression_value_18);
                        if (tmp_args_element_value_4 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                            Py_DECREF(tmp_called_value_14);
                            Py_DECREF(tmp_args_element_value_1);
                            Py_DECREF(tmp_args_element_value_2);
                            Py_DECREF(tmp_args_element_value_3);

                            exception_lineno = 66;
                            type_description_2 = "o";
                            goto tuple_build_exception_19;
                        }
                        tmp_args_element_value_5 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[161]);

                        if (tmp_args_element_value_5 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_args_element_value_5 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[161]);

                                if (unlikely(tmp_args_element_value_5 == NULL)) {
                                    tmp_args_element_value_5 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[161]);
                                }

                                if (tmp_args_element_value_5 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                                    Py_DECREF(tmp_called_value_14);
                                    Py_DECREF(tmp_args_element_value_1);
                                    Py_DECREF(tmp_args_element_value_2);
                                    Py_DECREF(tmp_args_element_value_3);
                                    Py_DECREF(tmp_args_element_value_4);

                                    exception_lineno = 66;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_19;
                                }
                                Py_INCREF(tmp_args_element_value_5);
                            } else {
                                goto tuple_build_exception_19;
                            }
                        }

                        frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 66;
                        {
                            PyObject *call_args[] = {tmp_args_element_value_1, tmp_args_element_value_2, tmp_args_element_value_3, tmp_args_element_value_4, tmp_args_element_value_5};
                            tmp_tuple_element_21 = CALL_FUNCTION_WITH_ARGS5(tstate, tmp_called_value_14, call_args);
                        }

                        Py_DECREF(tmp_called_value_14);
                        Py_DECREF(tmp_args_element_value_1);
                        Py_DECREF(tmp_args_element_value_2);
                        Py_DECREF(tmp_args_element_value_3);
                        Py_DECREF(tmp_args_element_value_4);
                        Py_DECREF(tmp_args_element_value_5);
                        if (tmp_tuple_element_21 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 66;
                            type_description_2 = "o";
                            goto tuple_build_exception_19;
                        }
                        PyTuple_SET_ITEM(tmp_list_element_6, 1, tmp_tuple_element_21);
                    }
                    goto tuple_build_noexception_19;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_19:;
                    Py_DECREF(tmp_list_element_6);
                    goto list_build_exception_5;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_19:;
                    PyList_SET_ITEM(tmp_dict_value_1, 3, tmp_list_element_6);
                    tmp_tuple_element_22 = mod_consts[221];
                    tmp_list_element_6 = MAKE_TUPLE_EMPTY(2);
                    {
                        PyObject *tmp_expression_value_19;
                        PyTuple_SET_ITEM0(tmp_list_element_6, 0, tmp_tuple_element_22);
                        tmp_expression_value_19 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                        if (tmp_expression_value_19 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_expression_value_19 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                                if (unlikely(tmp_expression_value_19 == NULL)) {
                                    tmp_expression_value_19 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                                }

                                if (tmp_expression_value_19 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                    exception_lineno = 67;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_20;
                                }
                                Py_INCREF(tmp_expression_value_19);
                            } else {
                                goto tuple_build_exception_20;
                            }
                        }

                        tmp_tuple_element_22 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_19, mod_consts[218]);
                        Py_DECREF(tmp_expression_value_19);
                        if (tmp_tuple_element_22 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 67;
                            type_description_2 = "o";
                            goto tuple_build_exception_20;
                        }
                        PyTuple_SET_ITEM(tmp_list_element_6, 1, tmp_tuple_element_22);
                    }
                    goto tuple_build_noexception_20;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_20:;
                    Py_DECREF(tmp_list_element_6);
                    goto list_build_exception_5;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_20:;
                    PyList_SET_ITEM(tmp_dict_value_1, 4, tmp_list_element_6);
                }
                goto list_build_noexception_5;
                // Exception handling pass through code for list_build:
                list_build_exception_5:;
                Py_DECREF(tmp_dict_value_1);
                goto dict_build_exception_1;
                // Finished with no exception for list_build:
                list_build_noexception_5:;
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
                tmp_dict_key_1 = mod_consts[222];
                tmp_tuple_element_23 = mod_consts[223];
                tmp_list_element_7 = MAKE_TUPLE_EMPTY(2);
                PyTuple_SET_ITEM0(tmp_list_element_7, 0, tmp_tuple_element_23);
                tmp_tuple_element_23 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[156]);

                if (tmp_tuple_element_23 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_tuple_element_23 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156]);

                        if (unlikely(tmp_tuple_element_23 == NULL)) {
                            tmp_tuple_element_23 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[156]);
                        }

                        if (tmp_tuple_element_23 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 70;
                            type_description_2 = "o";
                            goto tuple_build_exception_21;
                        }
                        Py_INCREF(tmp_tuple_element_23);
                    } else {
                        goto tuple_build_exception_21;
                    }
                }

                PyTuple_SET_ITEM(tmp_list_element_7, 1, tmp_tuple_element_23);
                goto tuple_build_noexception_21;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_21:;
                Py_DECREF(tmp_list_element_7);
                goto dict_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_21:;
                tmp_dict_value_1 = MAKE_LIST_EMPTY(11);
                {
                    PyObject *tmp_tuple_element_24;
                    PyObject *tmp_tuple_element_25;
                    PyObject *tmp_tuple_element_26;
                    PyObject *tmp_tuple_element_27;
                    PyObject *tmp_tuple_element_28;
                    PyObject *tmp_tuple_element_29;
                    PyObject *tmp_tuple_element_30;
                    PyObject *tmp_tuple_element_31;
                    PyObject *tmp_tuple_element_32;
                    PyObject *tmp_tuple_element_33;
                    PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_7);
                    tmp_tuple_element_24 = mod_consts[224];
                    tmp_list_element_7 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_7, 0, tmp_tuple_element_24);
                    tmp_tuple_element_24 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[156]);

                    if (tmp_tuple_element_24 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_24 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156]);

                            if (unlikely(tmp_tuple_element_24 == NULL)) {
                                tmp_tuple_element_24 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[156]);
                            }

                            if (tmp_tuple_element_24 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 71;
                                type_description_2 = "o";
                                goto tuple_build_exception_22;
                            }
                            Py_INCREF(tmp_tuple_element_24);
                        } else {
                            goto tuple_build_exception_22;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_7, 1, tmp_tuple_element_24);
                    goto tuple_build_noexception_22;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_22:;
                    Py_DECREF(tmp_list_element_7);
                    goto list_build_exception_6;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_22:;
                    PyList_SET_ITEM(tmp_dict_value_1, 1, tmp_list_element_7);
                    tmp_tuple_element_25 = mod_consts[225];
                    tmp_list_element_7 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_7, 0, tmp_tuple_element_25);
                    tmp_tuple_element_25 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[156]);

                    if (tmp_tuple_element_25 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_25 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156]);

                            if (unlikely(tmp_tuple_element_25 == NULL)) {
                                tmp_tuple_element_25 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[156]);
                            }

                            if (tmp_tuple_element_25 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 72;
                                type_description_2 = "o";
                                goto tuple_build_exception_23;
                            }
                            Py_INCREF(tmp_tuple_element_25);
                        } else {
                            goto tuple_build_exception_23;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_7, 1, tmp_tuple_element_25);
                    goto tuple_build_noexception_23;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_23:;
                    Py_DECREF(tmp_list_element_7);
                    goto list_build_exception_6;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_23:;
                    PyList_SET_ITEM(tmp_dict_value_1, 2, tmp_list_element_7);
                    tmp_tuple_element_26 = mod_consts[226];
                    tmp_list_element_7 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_7, 0, tmp_tuple_element_26);
                    tmp_tuple_element_26 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[156]);

                    if (tmp_tuple_element_26 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_26 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156]);

                            if (unlikely(tmp_tuple_element_26 == NULL)) {
                                tmp_tuple_element_26 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[156]);
                            }

                            if (tmp_tuple_element_26 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 73;
                                type_description_2 = "o";
                                goto tuple_build_exception_24;
                            }
                            Py_INCREF(tmp_tuple_element_26);
                        } else {
                            goto tuple_build_exception_24;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_7, 1, tmp_tuple_element_26);
                    goto tuple_build_noexception_24;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_24:;
                    Py_DECREF(tmp_list_element_7);
                    goto list_build_exception_6;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_24:;
                    PyList_SET_ITEM(tmp_dict_value_1, 3, tmp_list_element_7);
                    tmp_tuple_element_27 = mod_consts[227];
                    tmp_list_element_7 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_7, 0, tmp_tuple_element_27);
                    tmp_tuple_element_27 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[156]);

                    if (tmp_tuple_element_27 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_27 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156]);

                            if (unlikely(tmp_tuple_element_27 == NULL)) {
                                tmp_tuple_element_27 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[156]);
                            }

                            if (tmp_tuple_element_27 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 74;
                                type_description_2 = "o";
                                goto tuple_build_exception_25;
                            }
                            Py_INCREF(tmp_tuple_element_27);
                        } else {
                            goto tuple_build_exception_25;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_7, 1, tmp_tuple_element_27);
                    goto tuple_build_noexception_25;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_25:;
                    Py_DECREF(tmp_list_element_7);
                    goto list_build_exception_6;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_25:;
                    PyList_SET_ITEM(tmp_dict_value_1, 4, tmp_list_element_7);
                    tmp_tuple_element_28 = mod_consts[228];
                    tmp_list_element_7 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_7, 0, tmp_tuple_element_28);
                    tmp_tuple_element_28 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[156]);

                    if (tmp_tuple_element_28 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_28 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156]);

                            if (unlikely(tmp_tuple_element_28 == NULL)) {
                                tmp_tuple_element_28 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[156]);
                            }

                            if (tmp_tuple_element_28 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 75;
                                type_description_2 = "o";
                                goto tuple_build_exception_26;
                            }
                            Py_INCREF(tmp_tuple_element_28);
                        } else {
                            goto tuple_build_exception_26;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_7, 1, tmp_tuple_element_28);
                    goto tuple_build_noexception_26;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_26:;
                    Py_DECREF(tmp_list_element_7);
                    goto list_build_exception_6;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_26:;
                    PyList_SET_ITEM(tmp_dict_value_1, 5, tmp_list_element_7);
                    tmp_tuple_element_29 = mod_consts[229];
                    tmp_list_element_7 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_7, 0, tmp_tuple_element_29);
                    tmp_tuple_element_29 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[156]);

                    if (tmp_tuple_element_29 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_29 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156]);

                            if (unlikely(tmp_tuple_element_29 == NULL)) {
                                tmp_tuple_element_29 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[156]);
                            }

                            if (tmp_tuple_element_29 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 76;
                                type_description_2 = "o";
                                goto tuple_build_exception_27;
                            }
                            Py_INCREF(tmp_tuple_element_29);
                        } else {
                            goto tuple_build_exception_27;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_7, 1, tmp_tuple_element_29);
                    goto tuple_build_noexception_27;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_27:;
                    Py_DECREF(tmp_list_element_7);
                    goto list_build_exception_6;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_27:;
                    PyList_SET_ITEM(tmp_dict_value_1, 6, tmp_list_element_7);
                    tmp_tuple_element_30 = mod_consts[230];
                    tmp_list_element_7 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_7, 0, tmp_tuple_element_30);
                    tmp_tuple_element_30 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[156]);

                    if (tmp_tuple_element_30 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_30 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156]);

                            if (unlikely(tmp_tuple_element_30 == NULL)) {
                                tmp_tuple_element_30 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[156]);
                            }

                            if (tmp_tuple_element_30 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 77;
                                type_description_2 = "o";
                                goto tuple_build_exception_28;
                            }
                            Py_INCREF(tmp_tuple_element_30);
                        } else {
                            goto tuple_build_exception_28;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_7, 1, tmp_tuple_element_30);
                    goto tuple_build_noexception_28;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_28:;
                    Py_DECREF(tmp_list_element_7);
                    goto list_build_exception_6;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_28:;
                    PyList_SET_ITEM(tmp_dict_value_1, 7, tmp_list_element_7);
                    tmp_tuple_element_31 = mod_consts[231];
                    tmp_list_element_7 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_7, 0, tmp_tuple_element_31);
                    tmp_tuple_element_31 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[156]);

                    if (tmp_tuple_element_31 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_31 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156]);

                            if (unlikely(tmp_tuple_element_31 == NULL)) {
                                tmp_tuple_element_31 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[156]);
                            }

                            if (tmp_tuple_element_31 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 78;
                                type_description_2 = "o";
                                goto tuple_build_exception_29;
                            }
                            Py_INCREF(tmp_tuple_element_31);
                        } else {
                            goto tuple_build_exception_29;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_7, 1, tmp_tuple_element_31);
                    goto tuple_build_noexception_29;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_29:;
                    Py_DECREF(tmp_list_element_7);
                    goto list_build_exception_6;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_29:;
                    PyList_SET_ITEM(tmp_dict_value_1, 8, tmp_list_element_7);
                    tmp_tuple_element_32 = mod_consts[232];
                    tmp_list_element_7 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_7, 0, tmp_tuple_element_32);
                    tmp_tuple_element_32 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[156]);

                    if (tmp_tuple_element_32 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_32 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156]);

                            if (unlikely(tmp_tuple_element_32 == NULL)) {
                                tmp_tuple_element_32 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[156]);
                            }

                            if (tmp_tuple_element_32 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 79;
                                type_description_2 = "o";
                                goto tuple_build_exception_30;
                            }
                            Py_INCREF(tmp_tuple_element_32);
                        } else {
                            goto tuple_build_exception_30;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_7, 1, tmp_tuple_element_32);
                    goto tuple_build_noexception_30;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_30:;
                    Py_DECREF(tmp_list_element_7);
                    goto list_build_exception_6;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_30:;
                    PyList_SET_ITEM(tmp_dict_value_1, 9, tmp_list_element_7);
                    tmp_tuple_element_33 = mod_consts[233];
                    tmp_list_element_7 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_7, 0, tmp_tuple_element_33);
                    tmp_tuple_element_33 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[160]);

                    if (tmp_tuple_element_33 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_33 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[160]);

                            if (unlikely(tmp_tuple_element_33 == NULL)) {
                                tmp_tuple_element_33 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[160]);
                            }

                            if (tmp_tuple_element_33 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 80;
                                type_description_2 = "o";
                                goto tuple_build_exception_31;
                            }
                            Py_INCREF(tmp_tuple_element_33);
                        } else {
                            goto tuple_build_exception_31;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_7, 1, tmp_tuple_element_33);
                    goto tuple_build_noexception_31;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_31:;
                    Py_DECREF(tmp_list_element_7);
                    goto list_build_exception_6;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_31:;
                    PyList_SET_ITEM(tmp_dict_value_1, 10, tmp_list_element_7);
                }
                goto list_build_noexception_6;
                // Exception handling pass through code for list_build:
                list_build_exception_6:;
                Py_DECREF(tmp_dict_value_1);
                goto dict_build_exception_1;
                // Finished with no exception for list_build:
                list_build_noexception_6:;
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
                tmp_dict_key_1 = mod_consts[234];
                tmp_tuple_element_34 = mod_consts[235];
                tmp_list_element_8 = MAKE_TUPLE_EMPTY(2);
                PyTuple_SET_ITEM0(tmp_list_element_8, 0, tmp_tuple_element_34);
                tmp_tuple_element_34 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[156]);

                if (tmp_tuple_element_34 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_tuple_element_34 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[156]);

                        if (unlikely(tmp_tuple_element_34 == NULL)) {
                            tmp_tuple_element_34 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[156]);
                        }

                        if (tmp_tuple_element_34 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 83;
                            type_description_2 = "o";
                            goto tuple_build_exception_32;
                        }
                        Py_INCREF(tmp_tuple_element_34);
                    } else {
                        goto tuple_build_exception_32;
                    }
                }

                PyTuple_SET_ITEM(tmp_list_element_8, 1, tmp_tuple_element_34);
                goto tuple_build_noexception_32;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_32:;
                Py_DECREF(tmp_list_element_8);
                goto dict_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_32:;
                tmp_dict_value_1 = MAKE_LIST_EMPTY(3);
                {
                    PyObject *tmp_tuple_element_35;
                    PyObject *tmp_tuple_element_36;
                    PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_8);
                    tmp_tuple_element_35 = mod_consts[236];
                    tmp_list_element_8 = MAKE_TUPLE_EMPTY(2);
                    {
                        PyObject *tmp_called_value_15;
                        PyObject *tmp_args_element_value_6;
                        PyObject *tmp_expression_value_20;
                        PyObject *tmp_args_element_value_7;
                        PyTuple_SET_ITEM0(tmp_list_element_8, 0, tmp_tuple_element_35);
                        tmp_called_value_15 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[151]);

                        if (tmp_called_value_15 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_called_value_15 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[151]);

                                if (unlikely(tmp_called_value_15 == NULL)) {
                                    tmp_called_value_15 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[151]);
                                }

                                if (tmp_called_value_15 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                    exception_lineno = 84;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_33;
                                }
                                Py_INCREF(tmp_called_value_15);
                            } else {
                                goto tuple_build_exception_33;
                            }
                        }

                        tmp_expression_value_20 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                        if (tmp_expression_value_20 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_expression_value_20 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                                if (unlikely(tmp_expression_value_20 == NULL)) {
                                    tmp_expression_value_20 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                                }

                                if (tmp_expression_value_20 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                                    Py_DECREF(tmp_called_value_15);

                                    exception_lineno = 84;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_33;
                                }
                                Py_INCREF(tmp_expression_value_20);
                            } else {
                                goto tuple_build_exception_33;
                            }
                        }

                        tmp_args_element_value_6 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_20, mod_consts[237]);
                        Py_DECREF(tmp_expression_value_20);
                        if (tmp_args_element_value_6 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                            Py_DECREF(tmp_called_value_15);

                            exception_lineno = 84;
                            type_description_2 = "o";
                            goto tuple_build_exception_33;
                        }
                        tmp_args_element_value_7 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[161]);

                        if (tmp_args_element_value_7 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_args_element_value_7 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[161]);

                                if (unlikely(tmp_args_element_value_7 == NULL)) {
                                    tmp_args_element_value_7 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[161]);
                                }

                                if (tmp_args_element_value_7 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                                    Py_DECREF(tmp_called_value_15);
                                    Py_DECREF(tmp_args_element_value_6);

                                    exception_lineno = 84;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_33;
                                }
                                Py_INCREF(tmp_args_element_value_7);
                            } else {
                                goto tuple_build_exception_33;
                            }
                        }

                        frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 84;
                        {
                            PyObject *call_args[] = {tmp_args_element_value_6, tmp_args_element_value_7};
                            tmp_tuple_element_35 = CALL_FUNCTION_WITH_ARGS2(tstate, tmp_called_value_15, call_args);
                        }

                        Py_DECREF(tmp_called_value_15);
                        Py_DECREF(tmp_args_element_value_6);
                        Py_DECREF(tmp_args_element_value_7);
                        if (tmp_tuple_element_35 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 84;
                            type_description_2 = "o";
                            goto tuple_build_exception_33;
                        }
                        PyTuple_SET_ITEM(tmp_list_element_8, 1, tmp_tuple_element_35);
                    }
                    goto tuple_build_noexception_33;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_33:;
                    Py_DECREF(tmp_list_element_8);
                    goto list_build_exception_7;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_33:;
                    PyList_SET_ITEM(tmp_dict_value_1, 1, tmp_list_element_8);
                    tmp_tuple_element_36 = mod_consts[238];
                    tmp_list_element_8 = MAKE_TUPLE_EMPTY(2);
                    {
                        PyObject *tmp_expression_value_21;
                        PyObject *tmp_expression_value_22;
                        PyTuple_SET_ITEM0(tmp_list_element_8, 0, tmp_tuple_element_36);
                        tmp_expression_value_22 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                        if (tmp_expression_value_22 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_expression_value_22 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                                if (unlikely(tmp_expression_value_22 == NULL)) {
                                    tmp_expression_value_22 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                                }

                                if (tmp_expression_value_22 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                    exception_lineno = 85;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_34;
                                }
                                Py_INCREF(tmp_expression_value_22);
                            } else {
                                goto tuple_build_exception_34;
                            }
                        }

                        tmp_expression_value_21 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_22, mod_consts[216]);
                        Py_DECREF(tmp_expression_value_22);
                        if (tmp_expression_value_21 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 85;
                            type_description_2 = "o";
                            goto tuple_build_exception_34;
                        }
                        tmp_tuple_element_36 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_21, mod_consts[239]);
                        Py_DECREF(tmp_expression_value_21);
                        if (tmp_tuple_element_36 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 85;
                            type_description_2 = "o";
                            goto tuple_build_exception_34;
                        }
                        PyTuple_SET_ITEM(tmp_list_element_8, 1, tmp_tuple_element_36);
                    }
                    goto tuple_build_noexception_34;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_34:;
                    Py_DECREF(tmp_list_element_8);
                    goto list_build_exception_7;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_34:;
                    PyList_SET_ITEM(tmp_dict_value_1, 2, tmp_list_element_8);
                }
                goto list_build_noexception_7;
                // Exception handling pass through code for list_build:
                list_build_exception_7:;
                Py_DECREF(tmp_dict_value_1);
                goto dict_build_exception_1;
                // Finished with no exception for list_build:
                list_build_noexception_7:;
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
                tmp_dict_key_1 = mod_consts[240];
                tmp_tuple_element_37 = mod_consts[241];
                tmp_list_element_9 = MAKE_TUPLE_EMPTY(2);
                {
                    PyObject *tmp_called_value_16;
                    PyObject *tmp_args_element_value_8;
                    PyObject *tmp_expression_value_23;
                    PyObject *tmp_args_element_value_9;
                    PyObject *tmp_expression_value_24;
                    PyTuple_SET_ITEM0(tmp_list_element_9, 0, tmp_tuple_element_37);
                    tmp_called_value_16 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[151]);

                    if (tmp_called_value_16 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_called_value_16 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[151]);

                            if (unlikely(tmp_called_value_16 == NULL)) {
                                tmp_called_value_16 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[151]);
                            }

                            if (tmp_called_value_16 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 88;
                                type_description_2 = "o";
                                goto tuple_build_exception_35;
                            }
                            Py_INCREF(tmp_called_value_16);
                        } else {
                            goto tuple_build_exception_35;
                        }
                    }

                    tmp_expression_value_23 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                    if (tmp_expression_value_23 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_expression_value_23 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                            if (unlikely(tmp_expression_value_23 == NULL)) {
                                tmp_expression_value_23 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                            }

                            if (tmp_expression_value_23 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                                Py_DECREF(tmp_called_value_16);

                                exception_lineno = 88;
                                type_description_2 = "o";
                                goto tuple_build_exception_35;
                            }
                            Py_INCREF(tmp_expression_value_23);
                        } else {
                            goto tuple_build_exception_35;
                        }
                    }

                    tmp_args_element_value_8 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_23, mod_consts[237]);
                    Py_DECREF(tmp_expression_value_23);
                    if (tmp_args_element_value_8 == NULL) {
                        assert(HAS_ERROR_OCCURRED(tstate));

                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                        Py_DECREF(tmp_called_value_16);

                        exception_lineno = 88;
                        type_description_2 = "o";
                        goto tuple_build_exception_35;
                    }
                    tmp_expression_value_24 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                    if (tmp_expression_value_24 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_expression_value_24 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                            if (unlikely(tmp_expression_value_24 == NULL)) {
                                tmp_expression_value_24 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                            }

                            if (tmp_expression_value_24 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                                Py_DECREF(tmp_called_value_16);
                                Py_DECREF(tmp_args_element_value_8);

                                exception_lineno = 88;
                                type_description_2 = "o";
                                goto tuple_build_exception_35;
                            }
                            Py_INCREF(tmp_expression_value_24);
                        } else {
                            goto tuple_build_exception_35;
                        }
                    }

                    tmp_args_element_value_9 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_24, mod_consts[218]);
                    Py_DECREF(tmp_expression_value_24);
                    if (tmp_args_element_value_9 == NULL) {
                        assert(HAS_ERROR_OCCURRED(tstate));

                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                        Py_DECREF(tmp_called_value_16);
                        Py_DECREF(tmp_args_element_value_8);

                        exception_lineno = 88;
                        type_description_2 = "o";
                        goto tuple_build_exception_35;
                    }
                    frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 88;
                    {
                        PyObject *call_args[] = {tmp_args_element_value_8, tmp_args_element_value_9};
                        tmp_tuple_element_37 = CALL_FUNCTION_WITH_ARGS2(tstate, tmp_called_value_16, call_args);
                    }

                    Py_DECREF(tmp_called_value_16);
                    Py_DECREF(tmp_args_element_value_8);
                    Py_DECREF(tmp_args_element_value_9);
                    if (tmp_tuple_element_37 == NULL) {
                        assert(HAS_ERROR_OCCURRED(tstate));

                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                        exception_lineno = 88;
                        type_description_2 = "o";
                        goto tuple_build_exception_35;
                    }
                    PyTuple_SET_ITEM(tmp_list_element_9, 1, tmp_tuple_element_37);
                }
                goto tuple_build_noexception_35;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_35:;
                Py_DECREF(tmp_list_element_9);
                goto dict_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_35:;
                tmp_dict_value_1 = MAKE_LIST_EMPTY(1);
                PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_9);
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
                tmp_dict_key_1 = mod_consts[242];
                tmp_tuple_element_38 = mod_consts[243];
                tmp_list_element_10 = MAKE_TUPLE_EMPTY(2);
                {
                    PyObject *tmp_called_value_17;
                    PyObject *tmp_args_element_value_10;
                    PyObject *tmp_expression_value_25;
                    PyObject *tmp_args_element_value_11;
                    PyTuple_SET_ITEM0(tmp_list_element_10, 0, tmp_tuple_element_38);
                    tmp_called_value_17 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[151]);

                    if (tmp_called_value_17 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_called_value_17 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[151]);

                            if (unlikely(tmp_called_value_17 == NULL)) {
                                tmp_called_value_17 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[151]);
                            }

                            if (tmp_called_value_17 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 91;
                                type_description_2 = "o";
                                goto tuple_build_exception_36;
                            }
                            Py_INCREF(tmp_called_value_17);
                        } else {
                            goto tuple_build_exception_36;
                        }
                    }

                    tmp_expression_value_25 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                    if (tmp_expression_value_25 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_expression_value_25 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                            if (unlikely(tmp_expression_value_25 == NULL)) {
                                tmp_expression_value_25 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                            }

                            if (tmp_expression_value_25 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                                Py_DECREF(tmp_called_value_17);

                                exception_lineno = 91;
                                type_description_2 = "o";
                                goto tuple_build_exception_36;
                            }
                            Py_INCREF(tmp_expression_value_25);
                        } else {
                            goto tuple_build_exception_36;
                        }
                    }

                    tmp_args_element_value_10 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_25, mod_consts[244]);
                    Py_DECREF(tmp_expression_value_25);
                    if (tmp_args_element_value_10 == NULL) {
                        assert(HAS_ERROR_OCCURRED(tstate));

                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                        Py_DECREF(tmp_called_value_17);

                        exception_lineno = 91;
                        type_description_2 = "o";
                        goto tuple_build_exception_36;
                    }
                    tmp_args_element_value_11 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[161]);

                    if (tmp_args_element_value_11 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_args_element_value_11 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[161]);

                            if (unlikely(tmp_args_element_value_11 == NULL)) {
                                tmp_args_element_value_11 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[161]);
                            }

                            if (tmp_args_element_value_11 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
                                Py_DECREF(tmp_called_value_17);
                                Py_DECREF(tmp_args_element_value_10);

                                exception_lineno = 91;
                                type_description_2 = "o";
                                goto tuple_build_exception_36;
                            }
                            Py_INCREF(tmp_args_element_value_11);
                        } else {
                            goto tuple_build_exception_36;
                        }
                    }

                    frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame.f_lineno = 91;
                    {
                        PyObject *call_args[] = {tmp_args_element_value_10, tmp_args_element_value_11};
                        tmp_tuple_element_38 = CALL_FUNCTION_WITH_ARGS2(tstate, tmp_called_value_17, call_args);
                    }

                    Py_DECREF(tmp_called_value_17);
                    Py_DECREF(tmp_args_element_value_10);
                    Py_DECREF(tmp_args_element_value_11);
                    if (tmp_tuple_element_38 == NULL) {
                        assert(HAS_ERROR_OCCURRED(tstate));

                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                        exception_lineno = 91;
                        type_description_2 = "o";
                        goto tuple_build_exception_36;
                    }
                    PyTuple_SET_ITEM(tmp_list_element_10, 1, tmp_tuple_element_38);
                }
                goto tuple_build_noexception_36;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_36:;
                Py_DECREF(tmp_list_element_10);
                goto dict_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_36:;
                tmp_dict_value_1 = MAKE_LIST_EMPTY(1);
                PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_10);
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
                tmp_dict_key_1 = mod_consts[245];
                tmp_tuple_element_39 = mod_consts[246];
                tmp_list_element_11 = MAKE_TUPLE_EMPTY(2);
                PyTuple_SET_ITEM0(tmp_list_element_11, 0, tmp_tuple_element_39);
                tmp_tuple_element_39 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[161]);

                if (tmp_tuple_element_39 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_tuple_element_39 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[161]);

                        if (unlikely(tmp_tuple_element_39 == NULL)) {
                            tmp_tuple_element_39 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[161]);
                        }

                        if (tmp_tuple_element_39 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 94;
                            type_description_2 = "o";
                            goto tuple_build_exception_37;
                        }
                        Py_INCREF(tmp_tuple_element_39);
                    } else {
                        goto tuple_build_exception_37;
                    }
                }

                PyTuple_SET_ITEM(tmp_list_element_11, 1, tmp_tuple_element_39);
                goto tuple_build_noexception_37;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_37:;
                Py_DECREF(tmp_list_element_11);
                goto dict_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_37:;
                tmp_dict_value_1 = MAKE_LIST_EMPTY(3);
                {
                    PyObject *tmp_tuple_element_40;
                    PyObject *tmp_tuple_element_41;
                    PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_11);
                    tmp_tuple_element_40 = mod_consts[247];
                    tmp_list_element_11 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_11, 0, tmp_tuple_element_40);
                    tmp_tuple_element_40 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[161]);

                    if (tmp_tuple_element_40 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_40 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[161]);

                            if (unlikely(tmp_tuple_element_40 == NULL)) {
                                tmp_tuple_element_40 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[161]);
                            }

                            if (tmp_tuple_element_40 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 95;
                                type_description_2 = "o";
                                goto tuple_build_exception_38;
                            }
                            Py_INCREF(tmp_tuple_element_40);
                        } else {
                            goto tuple_build_exception_38;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_11, 1, tmp_tuple_element_40);
                    goto tuple_build_noexception_38;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_38:;
                    Py_DECREF(tmp_list_element_11);
                    goto list_build_exception_8;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_38:;
                    PyList_SET_ITEM(tmp_dict_value_1, 1, tmp_list_element_11);
                    tmp_tuple_element_41 = mod_consts[248];
                    tmp_list_element_11 = MAKE_TUPLE_EMPTY(2);
                    PyTuple_SET_ITEM0(tmp_list_element_11, 0, tmp_tuple_element_41);
                    tmp_tuple_element_41 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[161]);

                    if (tmp_tuple_element_41 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_tuple_element_41 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[161]);

                            if (unlikely(tmp_tuple_element_41 == NULL)) {
                                tmp_tuple_element_41 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[161]);
                            }

                            if (tmp_tuple_element_41 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 96;
                                type_description_2 = "o";
                                goto tuple_build_exception_39;
                            }
                            Py_INCREF(tmp_tuple_element_41);
                        } else {
                            goto tuple_build_exception_39;
                        }
                    }

                    PyTuple_SET_ITEM(tmp_list_element_11, 1, tmp_tuple_element_41);
                    goto tuple_build_noexception_39;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_39:;
                    Py_DECREF(tmp_list_element_11);
                    goto list_build_exception_8;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_39:;
                    PyList_SET_ITEM(tmp_dict_value_1, 2, tmp_list_element_11);
                }
                goto list_build_noexception_8;
                // Exception handling pass through code for list_build:
                list_build_exception_8:;
                Py_DECREF(tmp_dict_value_1);
                goto dict_build_exception_1;
                // Finished with no exception for list_build:
                list_build_noexception_8:;
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
                tmp_dict_key_1 = mod_consts[249];
                tmp_tuple_element_42 = mod_consts[250];
                tmp_list_element_12 = MAKE_TUPLE_EMPTY(2);
                PyTuple_SET_ITEM0(tmp_list_element_12, 0, tmp_tuple_element_42);
                tmp_tuple_element_42 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[162]);

                if (tmp_tuple_element_42 == NULL) {
                    if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                        tmp_tuple_element_42 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[162]);

                        if (unlikely(tmp_tuple_element_42 == NULL)) {
                            tmp_tuple_element_42 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[162]);
                        }

                        if (tmp_tuple_element_42 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 100;
                            type_description_2 = "o";
                            goto tuple_build_exception_40;
                        }
                        Py_INCREF(tmp_tuple_element_42);
                    } else {
                        goto tuple_build_exception_40;
                    }
                }

                PyTuple_SET_ITEM(tmp_list_element_12, 1, tmp_tuple_element_42);
                goto tuple_build_noexception_40;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_40:;
                Py_DECREF(tmp_list_element_12);
                goto dict_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_40:;
                tmp_dict_value_1 = MAKE_LIST_EMPTY(2);
                {
                    PyObject *tmp_tuple_element_43;
                    PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_12);
                    tmp_tuple_element_43 = mod_consts[251];
                    tmp_list_element_12 = MAKE_TUPLE_EMPTY(2);
                    {
                        PyObject *tmp_expression_value_26;
                        PyTuple_SET_ITEM0(tmp_list_element_12, 0, tmp_tuple_element_43);
                        tmp_expression_value_26 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[162]);

                        if (tmp_expression_value_26 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_expression_value_26 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[162]);

                                if (unlikely(tmp_expression_value_26 == NULL)) {
                                    tmp_expression_value_26 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[162]);
                                }

                                if (tmp_expression_value_26 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                    exception_lineno = 102;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_41;
                                }
                                Py_INCREF(tmp_expression_value_26);
                            } else {
                                goto tuple_build_exception_41;
                            }
                        }

                        tmp_tuple_element_43 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_26, mod_consts[252]);
                        Py_DECREF(tmp_expression_value_26);
                        if (tmp_tuple_element_43 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 102;
                            type_description_2 = "o";
                            goto tuple_build_exception_41;
                        }
                        PyTuple_SET_ITEM(tmp_list_element_12, 1, tmp_tuple_element_43);
                    }
                    goto tuple_build_noexception_41;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_41:;
                    Py_DECREF(tmp_list_element_12);
                    goto list_build_exception_9;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_41:;
                    PyList_SET_ITEM(tmp_dict_value_1, 1, tmp_list_element_12);
                }
                goto list_build_noexception_9;
                // Exception handling pass through code for list_build:
                list_build_exception_9:;
                Py_DECREF(tmp_dict_value_1);
                goto dict_build_exception_1;
                // Finished with no exception for list_build:
                list_build_noexception_9:;
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
                tmp_dict_key_1 = mod_consts[253];
                tmp_tuple_element_44 = mod_consts[254];
                tmp_list_element_13 = MAKE_TUPLE_EMPTY(2);
                {
                    PyObject *tmp_expression_value_27;
                    PyTuple_SET_ITEM0(tmp_list_element_13, 0, tmp_tuple_element_44);
                    tmp_expression_value_27 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                    if (tmp_expression_value_27 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_expression_value_27 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                            if (unlikely(tmp_expression_value_27 == NULL)) {
                                tmp_expression_value_27 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                            }

                            if (tmp_expression_value_27 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 106;
                                type_description_2 = "o";
                                goto tuple_build_exception_42;
                            }
                            Py_INCREF(tmp_expression_value_27);
                        } else {
                            goto tuple_build_exception_42;
                        }
                    }

                    tmp_tuple_element_44 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_27, mod_consts[255]);
                    Py_DECREF(tmp_expression_value_27);
                    if (tmp_tuple_element_44 == NULL) {
                        assert(HAS_ERROR_OCCURRED(tstate));

                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                        exception_lineno = 106;
                        type_description_2 = "o";
                        goto tuple_build_exception_42;
                    }
                    PyTuple_SET_ITEM(tmp_list_element_13, 1, tmp_tuple_element_44);
                }
                goto tuple_build_noexception_42;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_42:;
                Py_DECREF(tmp_list_element_13);
                goto dict_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_42:;
                tmp_dict_value_1 = MAKE_LIST_EMPTY(1);
                PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_13);
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
                tmp_dict_key_1 = mod_consts[256];
                tmp_tuple_element_45 = mod_consts[257];
                tmp_list_element_14 = MAKE_TUPLE_EMPTY(2);
                {
                    PyObject *tmp_expression_value_28;
                    PyObject *tmp_expression_value_29;
                    PyTuple_SET_ITEM0(tmp_list_element_14, 0, tmp_tuple_element_45);
                    tmp_expression_value_29 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                    if (tmp_expression_value_29 == NULL) {
                        if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                            tmp_expression_value_29 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                            if (unlikely(tmp_expression_value_29 == NULL)) {
                                tmp_expression_value_29 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                            }

                            if (tmp_expression_value_29 == NULL) {
                                assert(HAS_ERROR_OCCURRED(tstate));

                                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                exception_lineno = 110;
                                type_description_2 = "o";
                                goto tuple_build_exception_43;
                            }
                            Py_INCREF(tmp_expression_value_29);
                        } else {
                            goto tuple_build_exception_43;
                        }
                    }

                    tmp_expression_value_28 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_29, mod_consts[216]);
                    Py_DECREF(tmp_expression_value_29);
                    if (tmp_expression_value_28 == NULL) {
                        assert(HAS_ERROR_OCCURRED(tstate));

                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                        exception_lineno = 110;
                        type_description_2 = "o";
                        goto tuple_build_exception_43;
                    }
                    tmp_tuple_element_45 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_28, mod_consts[239]);
                    Py_DECREF(tmp_expression_value_28);
                    if (tmp_tuple_element_45 == NULL) {
                        assert(HAS_ERROR_OCCURRED(tstate));

                        FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                        exception_lineno = 110;
                        type_description_2 = "o";
                        goto tuple_build_exception_43;
                    }
                    PyTuple_SET_ITEM(tmp_list_element_14, 1, tmp_tuple_element_45);
                }
                goto tuple_build_noexception_43;
                // Exception handling pass through code for tuple_build:
                tuple_build_exception_43:;
                Py_DECREF(tmp_list_element_14);
                goto dict_build_exception_1;
                // Finished with no exception for tuple_build:
                tuple_build_noexception_43:;
                tmp_dict_value_1 = MAKE_LIST_EMPTY(2);
                {
                    PyObject *tmp_tuple_element_46;
                    PyList_SET_ITEM(tmp_dict_value_1, 0, tmp_list_element_14);
                    tmp_tuple_element_46 = mod_consts[258];
                    tmp_list_element_14 = MAKE_TUPLE_EMPTY(2);
                    {
                        PyObject *tmp_expression_value_30;
                        PyObject *tmp_expression_value_31;
                        PyTuple_SET_ITEM0(tmp_list_element_14, 0, tmp_tuple_element_46);
                        tmp_expression_value_31 = PyObject_GetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[158]);

                        if (tmp_expression_value_31 == NULL) {
                            if (CHECK_AND_CLEAR_KEY_ERROR_OCCURRED(tstate)) {
                                tmp_expression_value_31 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[158]);

                                if (unlikely(tmp_expression_value_31 == NULL)) {
                                    tmp_expression_value_31 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[158]);
                                }

                                if (tmp_expression_value_31 == NULL) {
                                    assert(HAS_ERROR_OCCURRED(tstate));

                                    FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                                    exception_lineno = 112;
                                    type_description_2 = "o";
                                    goto tuple_build_exception_44;
                                }
                                Py_INCREF(tmp_expression_value_31);
                            } else {
                                goto tuple_build_exception_44;
                            }
                        }

                        tmp_expression_value_30 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_31, mod_consts[216]);
                        Py_DECREF(tmp_expression_value_31);
                        if (tmp_expression_value_30 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 112;
                            type_description_2 = "o";
                            goto tuple_build_exception_44;
                        }
                        tmp_tuple_element_46 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_30, mod_consts[239]);
                        Py_DECREF(tmp_expression_value_30);
                        if (tmp_tuple_element_46 == NULL) {
                            assert(HAS_ERROR_OCCURRED(tstate));

                            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                            exception_lineno = 112;
                            type_description_2 = "o";
                            goto tuple_build_exception_44;
                        }
                        PyTuple_SET_ITEM(tmp_list_element_14, 1, tmp_tuple_element_46);
                    }
                    goto tuple_build_noexception_44;
                    // Exception handling pass through code for tuple_build:
                    tuple_build_exception_44:;
                    Py_DECREF(tmp_list_element_14);
                    goto list_build_exception_10;
                    // Finished with no exception for tuple_build:
                    tuple_build_noexception_44:;
                    PyList_SET_ITEM(tmp_dict_value_1, 1, tmp_list_element_14);
                }
                goto list_build_noexception_10;
                // Exception handling pass through code for list_build:
                list_build_exception_10:;
                Py_DECREF(tmp_dict_value_1);
                goto dict_build_exception_1;
                // Finished with no exception for list_build:
                list_build_noexception_10:;
                tmp_res = PyDict_SetItem(tmp_dictset_value, tmp_dict_key_1, tmp_dict_value_1);
                Py_DECREF(tmp_dict_value_1);
                assert(!(tmp_res != 0));
            }
            goto dict_build_noexception_1;
            // Exception handling pass through code for dict_build:
            dict_build_exception_1:;
            Py_DECREF(tmp_dictset_value);
            goto frame_exception_exit_2;
            // Finished with no exception for dict_build:
            dict_build_noexception_1:;
            tmp_res = PyObject_SetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[259], tmp_dictset_value);
            Py_DECREF(tmp_dictset_value);
            if (tmp_res != 0) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 25;
                type_description_2 = "o";
                goto frame_exception_exit_2;
            }
        }


        // Put the previous frame back on top.
        popFrameStack(tstate);

        goto frame_no_exception_1;
        frame_exception_exit_2:


        if (exception_tb == NULL) {
            exception_tb = MAKE_TRACEBACK(frame_ead9b724b65ce3c43b718984fb92cd7f_2, exception_lineno);
        } else if (exception_tb->tb_frame != &frame_ead9b724b65ce3c43b718984fb92cd7f_2->m_frame) {
            exception_tb = ADD_TRACEBACK(exception_tb, frame_ead9b724b65ce3c43b718984fb92cd7f_2, exception_lineno);
        }

        // Attaches locals to frame if any.
        Nuitka_Frame_AttachLocals(
            frame_ead9b724b65ce3c43b718984fb92cd7f_2,
            type_description_2,
            outline_0_var___class__
        );



        assertFrameObject(frame_ead9b724b65ce3c43b718984fb92cd7f_2);

        // Put the previous frame back on top.
        popFrameStack(tstate);

        // Return the error.
        goto nested_frame_exit_1;
        frame_no_exception_1:;
        goto skip_nested_handling_1;
        nested_frame_exit_1:;

        goto try_except_handler_7;
        skip_nested_handling_1:;
        {
            nuitka_bool tmp_condition_result_4;
            PyObject *tmp_cmp_expr_left_1;
            PyObject *tmp_cmp_expr_right_1;
            CHECK_OBJECT(tmp_class_creation_1__bases);
            tmp_cmp_expr_left_1 = tmp_class_creation_1__bases;
            CHECK_OBJECT(tmp_class_creation_1__bases_orig);
            tmp_cmp_expr_right_1 = tmp_class_creation_1__bases_orig;
            tmp_condition_result_4 = RICH_COMPARE_NE_NBOOL_OBJECT_TUPLE(tmp_cmp_expr_left_1, tmp_cmp_expr_right_1);
            if (tmp_condition_result_4 == NUITKA_BOOL_EXCEPTION) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 18;

                goto try_except_handler_7;
            }
            if (tmp_condition_result_4 == NUITKA_BOOL_TRUE) {
                goto branch_yes_3;
            } else {
                goto branch_no_3;
            }
        }
        branch_yes_3:;
        CHECK_OBJECT(tmp_class_creation_1__bases_orig);
        tmp_dictset_value = tmp_class_creation_1__bases_orig;
        tmp_res = PyObject_SetItem(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18, mod_consts[260], tmp_dictset_value);
        if (tmp_res != 0) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 18;

            goto try_except_handler_7;
        }
        branch_no_3:;
        {
            PyObject *tmp_assign_source_38;
            PyObject *tmp_called_value_18;
            PyObject *tmp_args_value_2;
            PyObject *tmp_tuple_element_47;
            PyObject *tmp_kwargs_value_2;
            CHECK_OBJECT(tmp_class_creation_1__metaclass);
            tmp_called_value_18 = tmp_class_creation_1__metaclass;
            tmp_tuple_element_47 = mod_consts[165];
            tmp_args_value_2 = MAKE_TUPLE_EMPTY(3);
            PyTuple_SET_ITEM0(tmp_args_value_2, 0, tmp_tuple_element_47);
            CHECK_OBJECT(tmp_class_creation_1__bases);
            tmp_tuple_element_47 = tmp_class_creation_1__bases;
            PyTuple_SET_ITEM0(tmp_args_value_2, 1, tmp_tuple_element_47);
            tmp_tuple_element_47 = locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18;
            PyTuple_SET_ITEM0(tmp_args_value_2, 2, tmp_tuple_element_47);
            CHECK_OBJECT(tmp_class_creation_1__class_decl_dict);
            tmp_kwargs_value_2 = tmp_class_creation_1__class_decl_dict;
            frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 18;
            tmp_assign_source_38 = CALL_FUNCTION(tstate, tmp_called_value_18, tmp_args_value_2, tmp_kwargs_value_2);
            Py_DECREF(tmp_args_value_2);
            if (tmp_assign_source_38 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 18;

                goto try_except_handler_7;
            }
            assert(outline_0_var___class__ == NULL);
            outline_0_var___class__ = tmp_assign_source_38;
        }
        CHECK_OBJECT(outline_0_var___class__);
        tmp_assign_source_37 = outline_0_var___class__;
        Py_INCREF(tmp_assign_source_37);
        goto try_return_handler_7;
        NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
        return NULL;
        // Return handler code:
        try_return_handler_7:;
        Py_DECREF(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18);
        locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18 = NULL;
        goto try_return_handler_6;
        // Exception handler code:
        try_except_handler_7:;
        exception_keeper_type_5 = exception_type;
        exception_keeper_value_5 = exception_value;
        exception_keeper_tb_5 = exception_tb;
        exception_keeper_lineno_5 = exception_lineno;
        exception_type = NULL;
        exception_value = NULL;
        exception_tb = NULL;
        exception_lineno = 0;

        Py_DECREF(locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18);
        locals_core$panic$$$class__1_HelixSyntaxHighlightingLexer_18 = NULL;
        // Re-raise.
        exception_type = exception_keeper_type_5;
        exception_value = exception_keeper_value_5;
        exception_tb = exception_keeper_tb_5;
        exception_lineno = exception_keeper_lineno_5;

        goto try_except_handler_6;
        // End of try:
        NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
        return NULL;
        // Return handler code:
        try_return_handler_6:;
        CHECK_OBJECT(outline_0_var___class__);
        Py_DECREF(outline_0_var___class__);
        outline_0_var___class__ = NULL;
        goto outline_result_1;
        // Exception handler code:
        try_except_handler_6:;
        exception_keeper_type_6 = exception_type;
        exception_keeper_value_6 = exception_value;
        exception_keeper_tb_6 = exception_tb;
        exception_keeper_lineno_6 = exception_lineno;
        exception_type = NULL;
        exception_value = NULL;
        exception_tb = NULL;
        exception_lineno = 0;

        // Re-raise.
        exception_type = exception_keeper_type_6;
        exception_value = exception_keeper_value_6;
        exception_tb = exception_keeper_tb_6;
        exception_lineno = exception_keeper_lineno_6;

        goto outline_exception_1;
        // End of try:
        NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
        return NULL;
        outline_exception_1:;
        exception_lineno = 18;
        goto try_except_handler_5;
        outline_result_1:;
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[165], tmp_assign_source_37);
    }
    goto try_end_5;
    // Exception handler code:
    try_except_handler_5:;
    exception_keeper_type_7 = exception_type;
    exception_keeper_value_7 = exception_value;
    exception_keeper_tb_7 = exception_tb;
    exception_keeper_lineno_7 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    Py_XDECREF(tmp_class_creation_1__bases_orig);
    tmp_class_creation_1__bases_orig = NULL;
    Py_XDECREF(tmp_class_creation_1__bases);
    tmp_class_creation_1__bases = NULL;
    Py_XDECREF(tmp_class_creation_1__class_decl_dict);
    tmp_class_creation_1__class_decl_dict = NULL;
    Py_XDECREF(tmp_class_creation_1__metaclass);
    tmp_class_creation_1__metaclass = NULL;
    Py_XDECREF(tmp_class_creation_1__prepared);
    tmp_class_creation_1__prepared = NULL;
    // Re-raise.
    exception_type = exception_keeper_type_7;
    exception_value = exception_keeper_value_7;
    exception_tb = exception_keeper_tb_7;
    exception_lineno = exception_keeper_lineno_7;

    goto frame_exception_exit_1;
    // End of try:
    try_end_5:;
    CHECK_OBJECT(tmp_class_creation_1__bases_orig);
    Py_DECREF(tmp_class_creation_1__bases_orig);
    tmp_class_creation_1__bases_orig = NULL;
    CHECK_OBJECT(tmp_class_creation_1__bases);
    Py_DECREF(tmp_class_creation_1__bases);
    tmp_class_creation_1__bases = NULL;
    CHECK_OBJECT(tmp_class_creation_1__class_decl_dict);
    Py_DECREF(tmp_class_creation_1__class_decl_dict);
    tmp_class_creation_1__class_decl_dict = NULL;
    CHECK_OBJECT(tmp_class_creation_1__metaclass);
    Py_DECREF(tmp_class_creation_1__metaclass);
    tmp_class_creation_1__metaclass = NULL;
    CHECK_OBJECT(tmp_class_creation_1__prepared);
    Py_DECREF(tmp_class_creation_1__prepared);
    tmp_class_creation_1__prepared = NULL;
    {
        PyObject *tmp_assign_source_39;
        PyObject *tmp_called_value_19;
        tmp_called_value_19 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[165]);

        if (unlikely(tmp_called_value_19 == NULL)) {
            tmp_called_value_19 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[165]);
        }

        if (tmp_called_value_19 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 116;

            goto frame_exception_exit_1;
        }
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 116;
        tmp_assign_source_39 = CALL_FUNCTION_NO_ARGS(tstate, tmp_called_value_19);
        if (tmp_assign_source_39 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 116;

            goto frame_exception_exit_1;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[1], tmp_assign_source_39);
    }
    {
        PyObject *tmp_assign_source_40;
        nuitka_bool tmp_condition_result_5;
        PyObject *tmp_called_instance_1;
        PyObject *tmp_call_result_1;
        int tmp_truth_name_2;
        PyObject *tmp_called_value_20;
        PyObject *tmp_called_value_21;
        tmp_called_instance_1 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[136]);

        if (unlikely(tmp_called_instance_1 == NULL)) {
            tmp_called_instance_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[136]);
        }

        assert(!(tmp_called_instance_1 == NULL));
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 119;
        tmp_call_result_1 = CALL_METHOD_NO_ARGS(tstate, tmp_called_instance_1, mod_consts[17]);
        if (tmp_call_result_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 119;

            goto frame_exception_exit_1;
        }
        tmp_truth_name_2 = CHECK_IF_TRUE(tmp_call_result_1);
        if (tmp_truth_name_2 == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_call_result_1);

            exception_lineno = 119;

            goto frame_exception_exit_1;
        }
        tmp_condition_result_5 = tmp_truth_name_2 == 0 ? NUITKA_BOOL_FALSE : NUITKA_BOOL_TRUE;
        Py_DECREF(tmp_call_result_1);
        if (tmp_condition_result_5 == NUITKA_BOOL_TRUE) {
            goto condexpr_true_2;
        } else {
            goto condexpr_false_2;
        }
        condexpr_true_2:;
        tmp_called_value_20 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[147]);

        if (unlikely(tmp_called_value_20 == NULL)) {
            tmp_called_value_20 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[147]);
        }

        if (tmp_called_value_20 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 118;

            goto frame_exception_exit_1;
        }
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 118;
        tmp_assign_source_40 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_called_value_20, &PyTuple_GET_ITEM(mod_consts[261], 0), mod_consts[262]);
        if (tmp_assign_source_40 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 118;

            goto frame_exception_exit_1;
        }
        goto condexpr_end_2;
        condexpr_false_2:;
        tmp_called_value_21 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[146]);

        if (unlikely(tmp_called_value_21 == NULL)) {
            tmp_called_value_21 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[146]);
        }

        if (tmp_called_value_21 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 120;

            goto frame_exception_exit_1;
        }
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 120;
        tmp_assign_source_40 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_called_value_21, &PyTuple_GET_ITEM(mod_consts[261], 0), mod_consts[262]);
        if (tmp_assign_source_40 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 120;

            goto frame_exception_exit_1;
        }
        condexpr_end_2:;
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[2], tmp_assign_source_40);
    }
    {
        PyObject *tmp_assign_source_41;
        PyObject *tmp_annotations_1;
        tmp_annotations_1 = DICT_COPY(mod_consts[263]);


        tmp_assign_source_41 = MAKE_FUNCTION_core$panic$$$function__1_highlight_code(tmp_annotations_1);

        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[264], tmp_assign_source_41);
    }
    // Tried code:
    {
        PyObject *tmp_assign_source_42;
        PyObject *tmp_expression_value_32;
        PyObject *tmp_called_instance_2;
        tmp_called_instance_2 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[135]);

        if (unlikely(tmp_called_instance_2 == NULL)) {
            tmp_called_instance_2 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[135]);
        }

        assert(!(tmp_called_instance_2 == NULL));
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 127;
        tmp_expression_value_32 = CALL_METHOD_NO_ARGS(tstate, tmp_called_instance_2, mod_consts[265]);
        if (tmp_expression_value_32 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 127;

            goto try_except_handler_8;
        }
        tmp_assign_source_42 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_32, mod_consts[266]);
        Py_DECREF(tmp_expression_value_32);
        if (tmp_assign_source_42 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 127;

            goto try_except_handler_8;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50], tmp_assign_source_42);
    }
    {
        PyObject *tmp_ass_subvalue_1;
        PyObject *tmp_ass_subscribed_1;
        PyObject *tmp_ass_subscript_1;
        tmp_ass_subvalue_1 = (PyObject *)&PyLong_Type;
        tmp_ass_subscribed_1 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[134]);

        if (unlikely(tmp_ass_subscribed_1 == NULL)) {
            tmp_ass_subscribed_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[134]);
        }

        if (tmp_ass_subscribed_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 127;

            goto try_except_handler_8;
        }
        tmp_ass_subscript_1 = mod_consts[50];
        tmp_result = SET_SUBSCRIPT(tstate, tmp_ass_subscribed_1, tmp_ass_subscript_1, tmp_ass_subvalue_1);
        if (tmp_result == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 127;

            goto try_except_handler_8;
        }
    }
    goto try_end_6;
    // Exception handler code:
    try_except_handler_8:;
    exception_keeper_type_8 = exception_type;
    exception_keeper_value_8 = exception_value;
    exception_keeper_tb_8 = exception_tb;
    exception_keeper_lineno_8 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    // Preserve existing published exception id 1.
    exception_preserved_1 = GET_CURRENT_EXCEPTION(tstate);

    if (exception_keeper_tb_8 == NULL) {
        exception_keeper_tb_8 = MAKE_TRACEBACK(frame_a2676065e0c895da5b2c9b4d6277da45, exception_keeper_lineno_8);
    } else if (exception_keeper_lineno_8 != 0) {
        exception_keeper_tb_8 = ADD_TRACEBACK(exception_keeper_tb_8, frame_a2676065e0c895da5b2c9b4d6277da45, exception_keeper_lineno_8);
    }

    PUBLISH_CURRENT_EXCEPTION(tstate, &exception_keeper_type_8, &exception_keeper_value_8, &exception_keeper_tb_8);
    // Tried code:
    {
        bool tmp_condition_result_6;
        PyObject *tmp_cmp_expr_left_2;
        PyObject *tmp_cmp_expr_right_2;
        tmp_cmp_expr_left_2 = EXC_TYPE(PyThreadState_GET());
        tmp_cmp_expr_right_2 = PyExc_OSError;
        tmp_res = EXCEPTION_MATCH_BOOL(tstate, tmp_cmp_expr_left_2, tmp_cmp_expr_right_2);
        assert(!(tmp_res == -1));
        tmp_condition_result_6 = (tmp_res != 0) ? true : false;
        if (tmp_condition_result_6 != false) {
            goto branch_yes_4;
        } else {
            goto branch_no_4;
        }
    }
    branch_yes_4:;
    {
        PyObject *tmp_assign_source_43;
        tmp_assign_source_43 = mod_consts[267];
        UPDATE_STRING_DICT0(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[50], tmp_assign_source_43);
    }
    goto branch_end_4;
    branch_no_4:;
    tmp_result = RERAISE_EXCEPTION(&exception_type, &exception_value, &exception_tb);
    if (unlikely(tmp_result == false)) {
        exception_lineno = 126;
    }

    if (exception_tb && exception_tb->tb_frame == &frame_a2676065e0c895da5b2c9b4d6277da45->m_frame) frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = exception_tb->tb_lineno;

    goto try_except_handler_9;
    branch_end_4:;
    goto try_end_7;
    // Exception handler code:
    try_except_handler_9:;
    exception_keeper_type_9 = exception_type;
    exception_keeper_value_9 = exception_value;
    exception_keeper_tb_9 = exception_tb;
    exception_keeper_lineno_9 = exception_lineno;
    exception_type = NULL;
    exception_value = NULL;
    exception_tb = NULL;
    exception_lineno = 0;

    // Restore previous exception id 1.
    SET_CURRENT_EXCEPTION(tstate, &exception_preserved_1);

    // Re-raise.
    exception_type = exception_keeper_type_9;
    exception_value = exception_keeper_value_9;
    exception_tb = exception_keeper_tb_9;
    exception_lineno = exception_keeper_lineno_9;

    goto frame_exception_exit_1;
    // End of try:
    try_end_7:;
    // Restore previous exception id 1.
    SET_CURRENT_EXCEPTION(tstate, &exception_preserved_1);

    goto try_end_6;
    NUITKA_CANNOT_GET_HERE("exception handler codes exits in all cases");
    return NULL;
    // End of try:
    try_end_6:;
    {
        PyObject *tmp_assign_source_44;
        PyObject *tmp_import_name_from_19;
        PyObject *tmp_name_value_9;
        PyObject *tmp_globals_arg_value_8;
        PyObject *tmp_locals_arg_value_8;
        PyObject *tmp_fromlist_value_8;
        PyObject *tmp_level_value_8;
        tmp_name_value_9 = mod_consts[268];
        tmp_globals_arg_value_8 = (PyObject *)moduledict_core$panic;
        tmp_locals_arg_value_8 = Py_None;
        tmp_fromlist_value_8 = mod_consts[269];
        tmp_level_value_8 = mod_consts[15];
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 130;
        tmp_import_name_from_19 = IMPORT_MODULE5(tstate, tmp_name_value_9, tmp_globals_arg_value_8, tmp_locals_arg_value_8, tmp_fromlist_value_8, tmp_level_value_8);
        if (tmp_import_name_from_19 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 130;

            goto frame_exception_exit_1;
        }
        if (PyModule_Check(tmp_import_name_from_19)) {
            tmp_assign_source_44 = IMPORT_NAME_OR_MODULE(
                tstate,
                tmp_import_name_from_19,
                (PyObject *)moduledict_core$panic,
                mod_consts[270],
                mod_consts[15]
            );
        } else {
            tmp_assign_source_44 = IMPORT_NAME_FROM_MODULE(tstate, tmp_import_name_from_19, mod_consts[270]);
        }

        Py_DECREF(tmp_import_name_from_19);
        if (tmp_assign_source_44 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 130;

            goto frame_exception_exit_1;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[270], tmp_assign_source_44);
    }
    {
        PyObject *tmp_assign_source_45;
        PyObject *tmp_called_value_22;
        tmp_called_value_22 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[270]);

        if (unlikely(tmp_called_value_22 == NULL)) {
            tmp_called_value_22 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[270]);
        }

        assert(!(tmp_called_value_22 == NULL));
        frame_a2676065e0c895da5b2c9b4d6277da45->m_frame.f_lineno = 132;
        tmp_assign_source_45 = CALL_FUNCTION_NO_ARGS(tstate, tmp_called_value_22);
        if (tmp_assign_source_45 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 132;

            goto frame_exception_exit_1;
        }
        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[3], tmp_assign_source_45);
    }
    {
        PyObject *tmp_assign_source_46;
        PyObject *tmp_kw_defaults_1;
        PyObject *tmp_annotations_2;
        PyObject *tmp_dict_key_2;
        PyObject *tmp_dict_value_2;
        PyObject *tmp_expression_value_33;
        PyObject *tmp_subscript_value_2;
        tmp_kw_defaults_1 = DICT_COPY(mod_consts[271]);
        tmp_dict_key_2 = mod_consts[272];
        tmp_expression_value_33 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[141]);

        if (unlikely(tmp_expression_value_33 == NULL)) {
            tmp_expression_value_33 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[141]);
        }

        if (tmp_expression_value_33 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_kw_defaults_1);

            exception_lineno = 134;

            goto frame_exception_exit_1;
        }
        tmp_subscript_value_2 = PyExc_Exception;
        tmp_dict_value_2 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_33, tmp_subscript_value_2);
        if (tmp_dict_value_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);
            Py_DECREF(tmp_kw_defaults_1);

            exception_lineno = 134;

            goto frame_exception_exit_1;
        }
        tmp_annotations_2 = _PyDict_NewPresized( 5 );
        {
            PyObject *tmp_expression_value_34;
            PyObject *tmp_subscript_value_3;
            tmp_res = PyDict_SetItem(tmp_annotations_2, tmp_dict_key_2, tmp_dict_value_2);
            Py_DECREF(tmp_dict_value_2);
            assert(!(tmp_res != 0));
            tmp_dict_key_2 = mod_consts[84];
            tmp_dict_value_2 = (PyObject *)&PyUnicode_Type;
            tmp_res = PyDict_SetItem(tmp_annotations_2, tmp_dict_key_2, tmp_dict_value_2);
            assert(!(tmp_res != 0));
            tmp_dict_key_2 = mod_consts[109];
            tmp_dict_value_2 = (PyObject *)&PyLong_Type;
            tmp_res = PyDict_SetItem(tmp_annotations_2, tmp_dict_key_2, tmp_dict_value_2);
            assert(!(tmp_res != 0));
            tmp_dict_key_2 = mod_consts[95];
            tmp_expression_value_34 = (PyObject *)&PyTuple_Type;
            tmp_subscript_value_3 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[137]);

            if (unlikely(tmp_subscript_value_3 == NULL)) {
                tmp_subscript_value_3 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[137]);
            }

            if (tmp_subscript_value_3 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 134;

                goto dict_build_exception_2;
            }
            tmp_dict_value_2 = LOOKUP_SUBSCRIPT(tstate, tmp_expression_value_34, tmp_subscript_value_3);
            if (tmp_dict_value_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 134;

                goto dict_build_exception_2;
            }
            tmp_res = PyDict_SetItem(tmp_annotations_2, tmp_dict_key_2, tmp_dict_value_2);
            Py_DECREF(tmp_dict_value_2);
            assert(!(tmp_res != 0));
            tmp_dict_key_2 = mod_consts[273];
            tmp_dict_value_2 = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[138]);

            if (unlikely(tmp_dict_value_2 == NULL)) {
                tmp_dict_value_2 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[138]);
            }

            if (tmp_dict_value_2 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


                exception_lineno = 134;

                goto dict_build_exception_2;
            }
            tmp_res = PyDict_SetItem(tmp_annotations_2, tmp_dict_key_2, tmp_dict_value_2);
            assert(!(tmp_res != 0));
        }
        goto dict_build_noexception_2;
        // Exception handling pass through code for dict_build:
        dict_build_exception_2:;
        Py_DECREF(tmp_kw_defaults_1);
        Py_DECREF(tmp_annotations_2);
        goto frame_exception_exit_1;
        // Finished with no exception for dict_build:
        dict_build_noexception_2:;


        tmp_assign_source_46 = MAKE_FUNCTION_core$panic$$$function__2_panic(tmp_kw_defaults_1, tmp_annotations_2);

        UPDATE_STRING_DICT1(moduledict_core$panic, (Nuitka_StringObject *)mod_consts[274], tmp_assign_source_46);
    }


    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto frame_no_exception_2;
    frame_exception_exit_1:


    if (exception_tb == NULL) {
        exception_tb = MAKE_TRACEBACK(frame_a2676065e0c895da5b2c9b4d6277da45, exception_lineno);
    } else if (exception_tb->tb_frame != &frame_a2676065e0c895da5b2c9b4d6277da45->m_frame) {
        exception_tb = ADD_TRACEBACK(exception_tb, frame_a2676065e0c895da5b2c9b4d6277da45, exception_lineno);
    }



    assertFrameObject(frame_a2676065e0c895da5b2c9b4d6277da45);

    // Put the previous frame back on top.
    popFrameStack(tstate);

    // Return the error.
    goto module_exception_exit;
    frame_no_exception_2:;

    // Report to PGO about leaving the module without error.
    PGO_onModuleExit("core$panic", false);

    Py_INCREF(module_core$panic);
    return module_core$panic;
    module_exception_exit:

#if defined(_NUITKA_MODULE) && 0
    {
        PyObject *module_name = GET_STRING_DICT_VALUE(moduledict_core$panic, (Nuitka_StringObject *)const_str_plain___name__);

        if (module_name != NULL) {
            Nuitka_DelModule(tstate, module_name);
        }
    }
#endif
    PGO_onModuleExit("core$panic", false);

    RESTORE_ERROR_OCCURRED(tstate, exception_type, exception_value, exception_tb);
    return NULL;
}
