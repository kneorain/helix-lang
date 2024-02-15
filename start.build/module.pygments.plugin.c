/* Generated code for Python module 'pygments$plugin'
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

/* The "module_pygments$plugin" is a Python object pointer of module type.
 *
 * Note: For full compatibility with CPython, every module variable access
 * needs to go through it except for cases where the module cannot possibly
 * have changed in the mean time.
 */

PyObject *module_pygments$plugin;
PyDictObject *moduledict_pygments$plugin;

/* The declarations of module constants used, if any. */
static PyObject *mod_consts[145];
#ifndef __NUITKA_NO_ASSERT__
static Py_hash_t mod_consts_hash[145];
#endif

static PyObject *module_filename_obj = NULL;

/* Indicator if this modules private constants were created yet. */
static bool constants_created = false;

/* Function to create module private constants. */
static void createModuleConstants(PyThreadState *tstate) {
    if (constants_created == false) {
        loadConstantsBlob(tstate, &mod_consts[0], UNTRANSLATE("pygments.plugin"));
        constants_created = true;

#ifndef __NUITKA_NO_ASSERT__
        for (int i = 0; i < 145; i++) {
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
void checkModuleConstants_pygments$plugin(PyThreadState *tstate) {
    // The module may not have been used at all, then ignore this.
    if (constants_created == false) return;

    for (int i = 0; i < 145; i++) {
        assert(mod_consts_hash[i] == DEEP_HASH(tstate, mod_consts[i]));
        CHECK_OBJECT_DEEP(mod_consts[i]);
    }
}
#endif

// The module code objects.
static PyCodeObject *codeobj_ebe3fc16cc6109fce68be05c0d37c541;
static PyCodeObject *codeobj_07017567a5a33bc26d066f927c932cd3;
static PyCodeObject *codeobj_ceb92494f6c172c57d7ef78414cc60e8;
static PyCodeObject *codeobj_69dc823866a694451fa9ac511ed82c60;
static PyCodeObject *codeobj_2033227d0779c41662ecff4076cc2ed9;
static PyCodeObject *codeobj_be4da8bfd064e70c4899ee31e77c316c;

static void createModuleCodeObjects(void) {
    module_filename_obj = MAKE_RELATIVE_PATH(mod_consts[140]); CHECK_OBJECT(module_filename_obj);
    codeobj_ebe3fc16cc6109fce68be05c0d37c541 = MAKE_CODE_OBJECT(module_filename_obj, 1, 0, mod_consts[141], mod_consts[141], NULL, NULL, 0, 0, 0);
    codeobj_07017567a5a33bc26d066f927c932cd3 = MAKE_CODE_OBJECT(module_filename_obj, 86, CO_GENERATOR | CO_OPTIMIZED | CO_NEWLOCALS, mod_consts[128], mod_consts[128], mod_consts[142], NULL, 0, 0, 0);
    codeobj_ceb92494f6c172c57d7ef78414cc60e8 = MAKE_CODE_OBJECT(module_filename_obj, 76, CO_GENERATOR | CO_OPTIMIZED | CO_NEWLOCALS, mod_consts[124], mod_consts[124], mod_consts[142], NULL, 0, 0, 0);
    codeobj_69dc823866a694451fa9ac511ed82c60 = MAKE_CODE_OBJECT(module_filename_obj, 71, CO_GENERATOR | CO_OPTIMIZED | CO_NEWLOCALS, mod_consts[121], mod_consts[121], mod_consts[142], NULL, 0, 0, 0);
    codeobj_2033227d0779c41662ecff4076cc2ed9 = MAKE_CODE_OBJECT(module_filename_obj, 81, CO_GENERATOR | CO_OPTIMIZED | CO_NEWLOCALS, mod_consts[126], mod_consts[126], mod_consts[142], NULL, 0, 0, 0);
    codeobj_be4da8bfd064e70c4899ee31e77c316c = MAKE_CODE_OBJECT(module_filename_obj, 47, CO_OPTIMIZED | CO_NEWLOCALS, mod_consts[118], mod_consts[118], mod_consts[143], NULL, 1, 0, 0);
}

// The module function declarations.
static PyObject *MAKE_GENERATOR_pygments$plugin$$$function__2_find_plugin_lexers$$$genobj__1_find_plugin_lexers();


static PyObject *MAKE_GENERATOR_pygments$plugin$$$function__3_find_plugin_formatters$$$genobj__1_find_plugin_formatters();


static PyObject *MAKE_GENERATOR_pygments$plugin$$$function__4_find_plugin_styles$$$genobj__1_find_plugin_styles();


static PyObject *MAKE_GENERATOR_pygments$plugin$$$function__5_find_plugin_filters$$$genobj__1_find_plugin_filters();


static PyObject *MAKE_FUNCTION_pygments$plugin$$$function__1_iter_entry_points();


static PyObject *MAKE_FUNCTION_pygments$plugin$$$function__2_find_plugin_lexers();


static PyObject *MAKE_FUNCTION_pygments$plugin$$$function__3_find_plugin_formatters();


static PyObject *MAKE_FUNCTION_pygments$plugin$$$function__4_find_plugin_styles();


static PyObject *MAKE_FUNCTION_pygments$plugin$$$function__5_find_plugin_filters();


// The module function definitions.
static PyObject *impl_pygments$plugin$$$function__1_iter_entry_points(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *par_group_name = python_pars[0];
    PyObject *var_entry_points = NULL;
    PyObject *var_groups = NULL;
    PyObject *tmp_selectable_groups_class;
    PyObject *tmp_entry_points_class;
    PyObject *tmp_entry_point_class;
    int tmp_res;
    struct Nuitka_FrameObject *frame_be4da8bfd064e70c4899ee31e77c316c;
    NUITKA_MAY_BE_UNUSED char const *type_description_1 = NULL;
    PyObject *exception_type = NULL;
    PyObject *exception_value = NULL;
    PyTracebackObject *exception_tb = NULL;
    NUITKA_MAY_BE_UNUSED int exception_lineno = 0;
    PyObject *tmp_return_value = NULL;
    static struct Nuitka_FrameObject *cache_frame_be4da8bfd064e70c4899ee31e77c316c = NULL;
    PyObject *exception_keeper_type_1;
    PyObject *exception_keeper_value_1;
    PyTracebackObject *exception_keeper_tb_1;
    NUITKA_MAY_BE_UNUSED int exception_keeper_lineno_1;

    // Actual function body.
    {
        PyObject *tmp_assign_source_1;
        {
            PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
            tmp_assign_source_1 = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[0]);
        }
        assert(!(tmp_assign_source_1 == NULL));
        assert(var_entry_points == NULL);
        var_entry_points = tmp_assign_source_1;
    }
    {
        PyObject *tmp_assign_source_2;
        PyObject *tmp_selectable_group_dict_1;
        PyObject *tmp_dict_key_1;
        PyObject *tmp_dict_value_1;
        PyObject *tmp_selectable_group_dict_2;
        PyObject *tmp_tuple_element_1;
        {
            PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
            tmp_selectable_groups_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[1]);
        }
        assert(!(tmp_selectable_groups_class == NULL));
        tmp_dict_key_1 = mod_consts[2];
        {
            PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
            tmp_entry_points_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[3]);
        }
        assert(!(tmp_entry_points_class == NULL));
        {
            PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
            tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
        }
        assert(!(tmp_entry_point_class == NULL));
        {
            PyObject *kw_values[3] = {mod_consts[5], mod_consts[6], mod_consts[2]};

            tmp_tuple_element_1 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
        }

        Py_DECREF(tmp_entry_point_class);
        assert(!(tmp_tuple_element_1 == NULL));
        tmp_selectable_group_dict_2 = MAKE_TUPLE_EMPTY(4);
        PyTuple_SET_ITEM(tmp_selectable_group_dict_2, 0, tmp_tuple_element_1);
        {
            PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
            tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
        }
        assert(!(tmp_entry_point_class == NULL));
        {
            PyObject *kw_values[3] = {mod_consts[8], mod_consts[6], mod_consts[2]};

            tmp_tuple_element_1 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
        }

        Py_DECREF(tmp_entry_point_class);
        assert(!(tmp_tuple_element_1 == NULL));
        PyTuple_SET_ITEM(tmp_selectable_group_dict_2, 1, tmp_tuple_element_1);
        {
            PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
            tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
        }
        assert(!(tmp_entry_point_class == NULL));
        {
            PyObject *kw_values[3] = {mod_consts[9], mod_consts[6], mod_consts[2]};

            tmp_tuple_element_1 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
        }

        Py_DECREF(tmp_entry_point_class);
        assert(!(tmp_tuple_element_1 == NULL));
        PyTuple_SET_ITEM(tmp_selectable_group_dict_2, 2, tmp_tuple_element_1);
        {
            PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
            tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
        }
        assert(!(tmp_entry_point_class == NULL));
        {
            PyObject *kw_values[3] = {mod_consts[10], mod_consts[11], mod_consts[2]};

            tmp_tuple_element_1 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
        }

        Py_DECREF(tmp_entry_point_class);
        assert(!(tmp_tuple_element_1 == NULL));
        PyTuple_SET_ITEM(tmp_selectable_group_dict_2, 3, tmp_tuple_element_1);
        tmp_dict_value_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_entry_points_class, tmp_selectable_group_dict_2);
        Py_DECREF(tmp_entry_points_class);
        Py_DECREF(tmp_selectable_group_dict_2);
        assert(!(tmp_dict_value_1 == NULL));
        tmp_selectable_group_dict_1 = _PyDict_NewPresized( 5 );
        {
            PyObject *tmp_selectable_group_dict_3;
            PyObject *tmp_tuple_element_2;
            PyObject *tmp_selectable_group_dict_4;
            PyObject *tmp_tuple_element_3;
            PyObject *tmp_selectable_group_dict_5;
            PyObject *tmp_tuple_element_4;
            PyObject *tmp_selectable_group_dict_6;
            PyObject *tmp_tuple_element_5;
            tmp_res = PyDict_SetItem(tmp_selectable_group_dict_1, tmp_dict_key_1, tmp_dict_value_1);
            Py_DECREF(tmp_dict_value_1);
            assert(!(tmp_res != 0));
            tmp_dict_key_1 = mod_consts[12];
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_points_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[3]);
            }
            assert(!(tmp_entry_points_class == NULL));
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[13], mod_consts[14], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            tmp_selectable_group_dict_3 = MAKE_TUPLE_EMPTY(25);
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 0, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[15], mod_consts[16], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 1, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[17], mod_consts[18], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 2, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[19], mod_consts[20], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 3, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[21], mod_consts[22], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 4, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[23], mod_consts[24], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 5, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[25], mod_consts[26], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 6, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[27], mod_consts[28], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 7, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[29], mod_consts[30], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 8, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[31], mod_consts[32], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 9, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[33], mod_consts[34], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 10, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[35], mod_consts[36], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 11, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[37], mod_consts[38], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 12, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[39], mod_consts[40], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 13, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[41], mod_consts[42], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 14, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[43], mod_consts[44], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 15, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[45], mod_consts[46], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 16, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[47], mod_consts[48], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 17, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[49], mod_consts[50], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 18, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[51], mod_consts[52], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 19, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[53], mod_consts[54], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 20, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[55], mod_consts[56], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 21, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[57], mod_consts[58], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 22, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[59], mod_consts[60], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 23, tmp_tuple_element_2);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[61], mod_consts[62], mod_consts[12]};

                tmp_tuple_element_2 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_2 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_3, 24, tmp_tuple_element_2);
            tmp_dict_value_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_entry_points_class, tmp_selectable_group_dict_3);
            Py_DECREF(tmp_entry_points_class);
            Py_DECREF(tmp_selectable_group_dict_3);
            assert(!(tmp_dict_value_1 == NULL));
            tmp_res = PyDict_SetItem(tmp_selectable_group_dict_1, tmp_dict_key_1, tmp_dict_value_1);
            Py_DECREF(tmp_dict_value_1);
            assert(!(tmp_res != 0));
            tmp_dict_key_1 = mod_consts[63];
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_points_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[3]);
            }
            assert(!(tmp_entry_points_class == NULL));
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[64], mod_consts[65], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            tmp_selectable_group_dict_4 = MAKE_TUPLE_EMPTY(19);
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 0, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[66], mod_consts[67], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 1, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[68], mod_consts[67], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 2, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[0], mod_consts[69], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 3, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[70], mod_consts[71], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 4, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[72], mod_consts[73], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 5, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[74], mod_consts[75], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 6, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[76], mod_consts[77], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 7, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[78], mod_consts[79], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 8, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[80], mod_consts[71], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 9, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[81], mod_consts[82], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 10, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[83], mod_consts[84], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 11, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[85], mod_consts[77], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 12, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[86], mod_consts[87], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 13, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[88], mod_consts[87], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 14, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[89], mod_consts[90], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 15, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[91], mod_consts[77], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 16, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[92], mod_consts[93], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 17, tmp_tuple_element_3);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[94], mod_consts[75], mod_consts[63]};

                tmp_tuple_element_3 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_3 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_4, 18, tmp_tuple_element_3);
            tmp_dict_value_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_entry_points_class, tmp_selectable_group_dict_4);
            Py_DECREF(tmp_entry_points_class);
            Py_DECREF(tmp_selectable_group_dict_4);
            assert(!(tmp_dict_value_1 == NULL));
            tmp_res = PyDict_SetItem(tmp_selectable_group_dict_1, tmp_dict_key_1, tmp_dict_value_1);
            Py_DECREF(tmp_dict_value_1);
            assert(!(tmp_res != 0));
            tmp_dict_key_1 = mod_consts[95];
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_points_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[3]);
            }
            assert(!(tmp_entry_points_class == NULL));
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[96], mod_consts[97], mod_consts[95]};

                tmp_tuple_element_4 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_4 == NULL));
            tmp_selectable_group_dict_5 = MAKE_TUPLE_EMPTY(8);
            PyTuple_SET_ITEM(tmp_selectable_group_dict_5, 0, tmp_tuple_element_4);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[98], mod_consts[99], mod_consts[95]};

                tmp_tuple_element_4 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_4 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_5, 1, tmp_tuple_element_4);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[100], mod_consts[101], mod_consts[95]};

                tmp_tuple_element_4 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_4 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_5, 2, tmp_tuple_element_4);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[102], mod_consts[99], mod_consts[95]};

                tmp_tuple_element_4 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_4 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_5, 3, tmp_tuple_element_4);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[103], mod_consts[104], mod_consts[95]};

                tmp_tuple_element_4 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_4 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_5, 4, tmp_tuple_element_4);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[105], mod_consts[99], mod_consts[95]};

                tmp_tuple_element_4 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_4 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_5, 5, tmp_tuple_element_4);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[106], mod_consts[107], mod_consts[95]};

                tmp_tuple_element_4 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_4 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_5, 6, tmp_tuple_element_4);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[108], mod_consts[109], mod_consts[95]};

                tmp_tuple_element_4 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_4 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_5, 7, tmp_tuple_element_4);
            tmp_dict_value_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_entry_points_class, tmp_selectable_group_dict_5);
            Py_DECREF(tmp_entry_points_class);
            Py_DECREF(tmp_selectable_group_dict_5);
            assert(!(tmp_dict_value_1 == NULL));
            tmp_res = PyDict_SetItem(tmp_selectable_group_dict_1, tmp_dict_key_1, tmp_dict_value_1);
            Py_DECREF(tmp_dict_value_1);
            assert(!(tmp_res != 0));
            tmp_dict_key_1 = mod_consts[110];
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_points_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[3]);
            }
            assert(!(tmp_entry_points_class == NULL));
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[111], mod_consts[112], mod_consts[110]};

                tmp_tuple_element_5 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_5 == NULL));
            tmp_selectable_group_dict_6 = MAKE_TUPLE_EMPTY(2);
            PyTuple_SET_ITEM(tmp_selectable_group_dict_6, 0, tmp_tuple_element_5);
            {
                PyObject *hard_module = IMPORT_HARD_IMPORTLIB__METADATA();
                tmp_entry_point_class = LOOKUP_ATTRIBUTE(tstate, hard_module, mod_consts[4]);
            }
            assert(!(tmp_entry_point_class == NULL));
            {
                PyObject *kw_values[3] = {mod_consts[113], mod_consts[114], mod_consts[110]};

                tmp_tuple_element_5 = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_entry_point_class, kw_values, mod_consts[7]);
            }

            Py_DECREF(tmp_entry_point_class);
            assert(!(tmp_tuple_element_5 == NULL));
            PyTuple_SET_ITEM(tmp_selectable_group_dict_6, 1, tmp_tuple_element_5);
            tmp_dict_value_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_entry_points_class, tmp_selectable_group_dict_6);
            Py_DECREF(tmp_entry_points_class);
            Py_DECREF(tmp_selectable_group_dict_6);
            assert(!(tmp_dict_value_1 == NULL));
            tmp_res = PyDict_SetItem(tmp_selectable_group_dict_1, tmp_dict_key_1, tmp_dict_value_1);
            Py_DECREF(tmp_dict_value_1);
            assert(!(tmp_res != 0));
        }
        tmp_assign_source_2 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_selectable_groups_class, tmp_selectable_group_dict_1);
        Py_DECREF(tmp_selectable_groups_class);
        Py_DECREF(tmp_selectable_group_dict_1);
        assert(!(tmp_assign_source_2 == NULL));
        assert(var_groups == NULL);
        var_groups = tmp_assign_source_2;
    }
    // Tried code:
    if (isFrameUnusable(cache_frame_be4da8bfd064e70c4899ee31e77c316c)) {
        Py_XDECREF(cache_frame_be4da8bfd064e70c4899ee31e77c316c);

#if _DEBUG_REFCOUNTS
        if (cache_frame_be4da8bfd064e70c4899ee31e77c316c == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_frame_be4da8bfd064e70c4899ee31e77c316c = MAKE_FUNCTION_FRAME(tstate, codeobj_be4da8bfd064e70c4899ee31e77c316c, module_pygments$plugin, sizeof(void *)+sizeof(void *)+sizeof(void *)+sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_frame_be4da8bfd064e70c4899ee31e77c316c->m_type_description == NULL);
    frame_be4da8bfd064e70c4899ee31e77c316c = cache_frame_be4da8bfd064e70c4899ee31e77c316c;

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackCompiledFrame(tstate, frame_be4da8bfd064e70c4899ee31e77c316c);
    assert(Py_REFCNT(frame_be4da8bfd064e70c4899ee31e77c316c) == 2);

    // Framed code:
    {
        bool tmp_condition_result_1;
        PyObject *tmp_expression_value_1;
        CHECK_OBJECT(var_groups);
        tmp_expression_value_1 = var_groups;
        tmp_res = HAS_ATTR_BOOL2(tstate, tmp_expression_value_1, mod_consts[115]);
        if (tmp_res == -1) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 61;
            type_description_1 = "ooNo";
            goto frame_exception_exit_1;
        }
        tmp_condition_result_1 = (tmp_res != 0) ? true : false;
        if (tmp_condition_result_1 != false) {
            goto branch_yes_1;
        } else {
            goto branch_no_1;
        }
    }
    branch_yes_1:;
    {
        PyObject *tmp_called_value_1;
        PyObject *tmp_expression_value_2;
        PyObject *tmp_kw_call_value_0_1;
        CHECK_OBJECT(var_groups);
        tmp_expression_value_2 = var_groups;
        tmp_called_value_1 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_2, mod_consts[115]);
        if (tmp_called_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 64;
            type_description_1 = "ooNo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(par_group_name);
        tmp_kw_call_value_0_1 = par_group_name;
        frame_be4da8bfd064e70c4899ee31e77c316c->m_frame.f_lineno = 64;
        {
            PyObject *kw_values[1] = {tmp_kw_call_value_0_1};

            tmp_return_value = CALL_FUNCTION_WITH_NO_ARGS_KWSPLIT(tstate, tmp_called_value_1, kw_values, mod_consts[116]);
        }

        Py_DECREF(tmp_called_value_1);
        if (tmp_return_value == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 64;
            type_description_1 = "ooNo";
            goto frame_exception_exit_1;
        }
        goto frame_return_exit_1;
    }
    goto branch_end_1;
    branch_no_1:;
    {
        PyObject *tmp_called_value_2;
        PyObject *tmp_expression_value_3;
        PyObject *tmp_args_element_value_1;
        PyObject *tmp_args_element_value_2;
        CHECK_OBJECT(var_groups);
        tmp_expression_value_3 = var_groups;
        tmp_called_value_2 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_3, mod_consts[117]);
        if (tmp_called_value_2 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 68;
            type_description_1 = "ooNo";
            goto frame_exception_exit_1;
        }
        CHECK_OBJECT(par_group_name);
        tmp_args_element_value_1 = par_group_name;
        tmp_args_element_value_2 = MAKE_LIST_EMPTY(0);
        frame_be4da8bfd064e70c4899ee31e77c316c->m_frame.f_lineno = 68;
        {
            PyObject *call_args[] = {tmp_args_element_value_1, tmp_args_element_value_2};
            tmp_return_value = CALL_FUNCTION_WITH_ARGS2(tstate, tmp_called_value_2, call_args);
        }

        Py_DECREF(tmp_called_value_2);
        Py_DECREF(tmp_args_element_value_2);
        if (tmp_return_value == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 68;
            type_description_1 = "ooNo";
            goto frame_exception_exit_1;
        }
        goto frame_return_exit_1;
    }
    branch_end_1:;


    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto frame_no_exception_1;
    frame_return_exit_1:

    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto try_return_handler_1;
    frame_exception_exit_1:


    if (exception_tb == NULL) {
        exception_tb = MAKE_TRACEBACK(frame_be4da8bfd064e70c4899ee31e77c316c, exception_lineno);
    } else if (exception_tb->tb_frame != &frame_be4da8bfd064e70c4899ee31e77c316c->m_frame) {
        exception_tb = ADD_TRACEBACK(exception_tb, frame_be4da8bfd064e70c4899ee31e77c316c, exception_lineno);
    }

    // Attaches locals to frame if any.
    Nuitka_Frame_AttachLocals(
        frame_be4da8bfd064e70c4899ee31e77c316c,
        type_description_1,
        par_group_name,
        var_entry_points,
        NULL,
        var_groups
    );


    // Release cached frame if used for exception.
    if (frame_be4da8bfd064e70c4899ee31e77c316c == cache_frame_be4da8bfd064e70c4899ee31e77c316c) {
#if _DEBUG_REFCOUNTS
        count_active_frame_cache_instances -= 1;
        count_released_frame_cache_instances += 1;
#endif
        Py_DECREF(cache_frame_be4da8bfd064e70c4899ee31e77c316c);
        cache_frame_be4da8bfd064e70c4899ee31e77c316c = NULL;
    }

    assertFrameObject(frame_be4da8bfd064e70c4899ee31e77c316c);

    // Put the previous frame back on top.
    popFrameStack(tstate);

    // Return the error.
    goto try_except_handler_1;
    frame_no_exception_1:;
    NUITKA_CANNOT_GET_HERE("tried codes exits in all cases");
    return NULL;
    // Return handler code:
    try_return_handler_1:;
    CHECK_OBJECT(var_entry_points);
    Py_DECREF(var_entry_points);
    var_entry_points = NULL;
    Py_XDECREF(var_groups);
    var_groups = NULL;
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

    CHECK_OBJECT(var_entry_points);
    Py_DECREF(var_entry_points);
    var_entry_points = NULL;
    Py_XDECREF(var_groups);
    var_groups = NULL;
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
    CHECK_OBJECT(par_group_name);
    Py_DECREF(par_group_name);
    assert(exception_type);
    RESTORE_ERROR_OCCURRED(tstate, exception_type, exception_value, exception_tb);

    return NULL;

function_return_exit:
   // Function cleanup code if any.
    CHECK_OBJECT(par_group_name);
    Py_DECREF(par_group_name);

   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}


static PyObject *impl_pygments$plugin$$$function__2_find_plugin_lexers(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *tmp_return_value = NULL;

    // Actual function body.


    tmp_return_value = MAKE_GENERATOR_pygments$plugin$$$function__2_find_plugin_lexers$$$genobj__1_find_plugin_lexers();

    goto function_return_exit;

    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;


function_return_exit:
   // Function cleanup code if any.


   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}



#if 1
struct pygments$plugin$$$function__2_find_plugin_lexers$$$genobj__1_find_plugin_lexers_locals {
    PyObject *var_entrypoint;
    PyObject *tmp_for_loop_1__for_iterator;
    PyObject *tmp_for_loop_1__iter_value;
    char const *type_description_1;
    PyObject *exception_type;
    PyObject *exception_value;
    PyTracebackObject *exception_tb;
    int exception_lineno;
    char yield_tmps[1024];
    PyObject *exception_keeper_type_1;
    PyObject *exception_keeper_value_1;
    PyTracebackObject *exception_keeper_tb_1;
    int exception_keeper_lineno_1;
    PyObject *exception_keeper_type_2;
    PyObject *exception_keeper_value_2;
    PyTracebackObject *exception_keeper_tb_2;
    int exception_keeper_lineno_2;
};
#endif

static PyObject *pygments$plugin$$$function__2_find_plugin_lexers$$$genobj__1_find_plugin_lexers_context(PyThreadState *tstate, struct Nuitka_GeneratorObject *generator, PyObject *yield_return_value) {
    CHECK_OBJECT(generator);
    assert(Nuitka_Generator_Check((PyObject *)generator));
    CHECK_OBJECT_X(yield_return_value);

#if 1
    // Heap access.
    struct pygments$plugin$$$function__2_find_plugin_lexers$$$genobj__1_find_plugin_lexers_locals *generator_heap = (struct pygments$plugin$$$function__2_find_plugin_lexers$$$genobj__1_find_plugin_lexers_locals *)generator->m_heap_storage;
#endif

    // Dispatch to yield based on return label index:
    switch(generator->m_yield_return_index) {
    case 1: goto yield_return_1;
    }

    // Local variable initialization
    NUITKA_MAY_BE_UNUSED nuitka_void tmp_unused;
    static struct Nuitka_FrameObject *cache_m_frame = NULL;
    generator_heap->var_entrypoint = NULL;
    generator_heap->tmp_for_loop_1__for_iterator = NULL;
    generator_heap->tmp_for_loop_1__iter_value = NULL;
    generator_heap->type_description_1 = NULL;
    generator_heap->exception_type = NULL;
    generator_heap->exception_value = NULL;
    generator_heap->exception_tb = NULL;
    generator_heap->exception_lineno = 0;

    // Actual generator function body.
    // Tried code:
    if (isFrameUnusable(cache_m_frame)) {
        Py_XDECREF(cache_m_frame);

#if _DEBUG_REFCOUNTS
        if (cache_m_frame == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_m_frame = MAKE_FUNCTION_FRAME(tstate, codeobj_69dc823866a694451fa9ac511ed82c60, module_pygments$plugin, sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_m_frame->m_type_description == NULL);
    generator->m_frame = cache_m_frame;
    // Mark the frame object as in use, ref count 1 will be up for reuse.
    Py_INCREF(generator->m_frame);
    assert(Py_REFCNT(generator->m_frame) == 2); // Frame stack

    Nuitka_SetFrameGenerator(generator->m_frame, (PyObject *)generator);

    assert(generator->m_frame->m_frame.f_back == NULL);

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackGeneratorCompiledFrame(tstate, generator->m_frame);
    assert(Py_REFCNT(generator->m_frame) == 2);

    // Store currently existing exception as the one to publish again when we
    // yield or yield from.
    STORE_GENERATOR_EXCEPTION(tstate, generator);

    // Framed code:
    {
        PyObject *tmp_assign_source_1;
        PyObject *tmp_iter_arg_1;
        PyObject *tmp_called_value_1;
        PyObject *tmp_args_element_value_1;
        tmp_called_value_1 = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[118]);

        if (unlikely(tmp_called_value_1 == NULL)) {
            tmp_called_value_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[118]);
        }

        if (tmp_called_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 72;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_args_element_value_1 = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[119]);

        if (unlikely(tmp_args_element_value_1 == NULL)) {
            tmp_args_element_value_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[119]);
        }

        if (tmp_args_element_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 72;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        generator->m_frame->m_frame.f_lineno = 72;
        tmp_iter_arg_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_1, tmp_args_element_value_1);
        if (tmp_iter_arg_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 72;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_1 = MAKE_ITERATOR(tstate, tmp_iter_arg_1);
        Py_DECREF(tmp_iter_arg_1);
        if (tmp_assign_source_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 72;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        assert(generator_heap->tmp_for_loop_1__for_iterator == NULL);
        generator_heap->tmp_for_loop_1__for_iterator = tmp_assign_source_1;
    }
    // Tried code:
    loop_start_1:;
    {
        PyObject *tmp_next_source_1;
        PyObject *tmp_assign_source_2;
        CHECK_OBJECT(generator_heap->tmp_for_loop_1__for_iterator);
        tmp_next_source_1 = generator_heap->tmp_for_loop_1__for_iterator;
        tmp_assign_source_2 = ITERATOR_NEXT(tmp_next_source_1);
        if (tmp_assign_source_2 == NULL) {
            if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                goto loop_end_1;
            } else {

                FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);
                generator_heap->type_description_1 = "o";
                generator_heap->exception_lineno = 72;
                goto try_except_handler_2;
            }
        }

        {
            PyObject *old = generator_heap->tmp_for_loop_1__iter_value;
            generator_heap->tmp_for_loop_1__iter_value = tmp_assign_source_2;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_3;
        CHECK_OBJECT(generator_heap->tmp_for_loop_1__iter_value);
        tmp_assign_source_3 = generator_heap->tmp_for_loop_1__iter_value;
        {
            PyObject *old = generator_heap->var_entrypoint;
            generator_heap->var_entrypoint = tmp_assign_source_3;
            Py_INCREF(generator_heap->var_entrypoint);
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_expression_value_1;
        PyObject *tmp_called_instance_1;
        NUITKA_MAY_BE_UNUSED PyObject *tmp_yield_result_1;
        CHECK_OBJECT(generator_heap->var_entrypoint);
        tmp_called_instance_1 = generator_heap->var_entrypoint;
        generator->m_frame->m_frame.f_lineno = 73;
        tmp_expression_value_1 = CALL_METHOD_NO_ARGS(tstate, tmp_called_instance_1, mod_consts[120]);
        if (tmp_expression_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 73;
            generator_heap->type_description_1 = "o";
            goto try_except_handler_2;
        }
        Nuitka_PreserveHeap(generator_heap->yield_tmps, &tmp_called_instance_1, sizeof(PyObject *), NULL);
        generator->m_yield_return_index = 1;
        return tmp_expression_value_1;
        yield_return_1:
        Nuitka_RestoreHeap(generator_heap->yield_tmps, &tmp_called_instance_1, sizeof(PyObject *), NULL);
        if (yield_return_value == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 73;
            generator_heap->type_description_1 = "o";
            goto try_except_handler_2;
        }
        tmp_yield_result_1 = yield_return_value;
        Py_DECREF(tmp_yield_result_1);
    }
    if (CONSIDER_THREADING(tstate) == false) {
        assert(HAS_ERROR_OCCURRED(tstate));

        FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


        generator_heap->exception_lineno = 72;
        generator_heap->type_description_1 = "o";
        goto try_except_handler_2;
    }
    goto loop_start_1;
    loop_end_1:;
    goto try_end_1;
    // Exception handler code:
    try_except_handler_2:;
    generator_heap->exception_keeper_type_1 = generator_heap->exception_type;
    generator_heap->exception_keeper_value_1 = generator_heap->exception_value;
    generator_heap->exception_keeper_tb_1 = generator_heap->exception_tb;
    generator_heap->exception_keeper_lineno_1 = generator_heap->exception_lineno;
    generator_heap->exception_type = NULL;
    generator_heap->exception_value = NULL;
    generator_heap->exception_tb = NULL;
    generator_heap->exception_lineno = 0;

    Py_XDECREF(generator_heap->tmp_for_loop_1__iter_value);
    generator_heap->tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(generator_heap->tmp_for_loop_1__for_iterator);
    Py_DECREF(generator_heap->tmp_for_loop_1__for_iterator);
    generator_heap->tmp_for_loop_1__for_iterator = NULL;
    // Re-raise.
    generator_heap->exception_type = generator_heap->exception_keeper_type_1;
    generator_heap->exception_value = generator_heap->exception_keeper_value_1;
    generator_heap->exception_tb = generator_heap->exception_keeper_tb_1;
    generator_heap->exception_lineno = generator_heap->exception_keeper_lineno_1;

    goto frame_exception_exit_1;
    // End of try:
    try_end_1:;

    // Release exception attached to the frame
    DROP_GENERATOR_EXCEPTION(generator);



    goto frame_no_exception_1;
    frame_exception_exit_1:;

    // If it's not an exit exception, consider and create a traceback for it.
    if (!EXCEPTION_MATCH_GENERATOR(tstate, generator_heap->exception_type)) {
        if (generator_heap->exception_tb == NULL) {
            generator_heap->exception_tb = MAKE_TRACEBACK(generator->m_frame, generator_heap->exception_lineno);
        } else if (generator_heap->exception_tb->tb_frame != &generator->m_frame->m_frame) {
            generator_heap->exception_tb = ADD_TRACEBACK(generator_heap->exception_tb, generator->m_frame, generator_heap->exception_lineno);
        }

        Nuitka_Frame_AttachLocals(
            generator->m_frame,
            generator_heap->type_description_1,
            generator_heap->var_entrypoint
        );


        // Release cached frame if used for exception.
        if (generator->m_frame == cache_m_frame) {
#if _DEBUG_REFCOUNTS
            count_active_frame_cache_instances -= 1;
            count_released_frame_cache_instances += 1;
#endif

            Py_DECREF(cache_m_frame);
            cache_m_frame = NULL;
        }

        assertFrameObject(generator->m_frame);
    }

#if PYTHON_VERSION >= 0x300
#if PYTHON_VERSION < 0x3b0
    Py_CLEAR(EXC_TYPE_F(generator));
#endif
    Py_CLEAR(EXC_VALUE_F(generator));
#if PYTHON_VERSION < 0x3b0
    Py_CLEAR(EXC_TRACEBACK_F(generator));
#endif
#endif

    // Return the error.
    goto try_except_handler_1;

    frame_no_exception_1:;
    goto try_end_2;
    // Exception handler code:
    try_except_handler_1:;
    generator_heap->exception_keeper_type_2 = generator_heap->exception_type;
    generator_heap->exception_keeper_value_2 = generator_heap->exception_value;
    generator_heap->exception_keeper_tb_2 = generator_heap->exception_tb;
    generator_heap->exception_keeper_lineno_2 = generator_heap->exception_lineno;
    generator_heap->exception_type = NULL;
    generator_heap->exception_value = NULL;
    generator_heap->exception_tb = NULL;
    generator_heap->exception_lineno = 0;

    Py_XDECREF(generator_heap->var_entrypoint);
    generator_heap->var_entrypoint = NULL;
    // Re-raise.
    generator_heap->exception_type = generator_heap->exception_keeper_type_2;
    generator_heap->exception_value = generator_heap->exception_keeper_value_2;
    generator_heap->exception_tb = generator_heap->exception_keeper_tb_2;
    generator_heap->exception_lineno = generator_heap->exception_keeper_lineno_2;

    goto function_exception_exit;
    // End of try:
    try_end_2:;
    Py_XDECREF(generator_heap->tmp_for_loop_1__iter_value);
    generator_heap->tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(generator_heap->tmp_for_loop_1__for_iterator);
    Py_DECREF(generator_heap->tmp_for_loop_1__for_iterator);
    generator_heap->tmp_for_loop_1__for_iterator = NULL;
    Py_XDECREF(generator_heap->var_entrypoint);
    generator_heap->var_entrypoint = NULL;


    return NULL;

    function_exception_exit:

    assert(generator_heap->exception_type);
    RESTORE_ERROR_OCCURRED(tstate, generator_heap->exception_type, generator_heap->exception_value, generator_heap->exception_tb);

    return NULL;

}

static PyObject *MAKE_GENERATOR_pygments$plugin$$$function__2_find_plugin_lexers$$$genobj__1_find_plugin_lexers() {
    return Nuitka_Generator_New(
        pygments$plugin$$$function__2_find_plugin_lexers$$$genobj__1_find_plugin_lexers_context,
        module_pygments$plugin,
        mod_consts[121],
#if PYTHON_VERSION >= 0x350
        NULL,
#endif
        codeobj_69dc823866a694451fa9ac511ed82c60,
        NULL,
        0,
#if 1
        sizeof(struct pygments$plugin$$$function__2_find_plugin_lexers$$$genobj__1_find_plugin_lexers_locals)
#else
        0
#endif
    );
}


static PyObject *impl_pygments$plugin$$$function__3_find_plugin_formatters(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *tmp_return_value = NULL;

    // Actual function body.


    tmp_return_value = MAKE_GENERATOR_pygments$plugin$$$function__3_find_plugin_formatters$$$genobj__1_find_plugin_formatters();

    goto function_return_exit;

    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;


function_return_exit:
   // Function cleanup code if any.


   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}



#if 1
struct pygments$plugin$$$function__3_find_plugin_formatters$$$genobj__1_find_plugin_formatters_locals {
    PyObject *var_entrypoint;
    PyObject *tmp_for_loop_1__for_iterator;
    PyObject *tmp_for_loop_1__iter_value;
    char const *type_description_1;
    PyObject *exception_type;
    PyObject *exception_value;
    PyTracebackObject *exception_tb;
    int exception_lineno;
    char yield_tmps[1024];
    PyObject *exception_keeper_type_1;
    PyObject *exception_keeper_value_1;
    PyTracebackObject *exception_keeper_tb_1;
    int exception_keeper_lineno_1;
    PyObject *exception_keeper_type_2;
    PyObject *exception_keeper_value_2;
    PyTracebackObject *exception_keeper_tb_2;
    int exception_keeper_lineno_2;
};
#endif

static PyObject *pygments$plugin$$$function__3_find_plugin_formatters$$$genobj__1_find_plugin_formatters_context(PyThreadState *tstate, struct Nuitka_GeneratorObject *generator, PyObject *yield_return_value) {
    CHECK_OBJECT(generator);
    assert(Nuitka_Generator_Check((PyObject *)generator));
    CHECK_OBJECT_X(yield_return_value);

#if 1
    // Heap access.
    struct pygments$plugin$$$function__3_find_plugin_formatters$$$genobj__1_find_plugin_formatters_locals *generator_heap = (struct pygments$plugin$$$function__3_find_plugin_formatters$$$genobj__1_find_plugin_formatters_locals *)generator->m_heap_storage;
#endif

    // Dispatch to yield based on return label index:
    switch(generator->m_yield_return_index) {
    case 1: goto yield_return_1;
    }

    // Local variable initialization
    NUITKA_MAY_BE_UNUSED nuitka_void tmp_unused;
    static struct Nuitka_FrameObject *cache_m_frame = NULL;
    generator_heap->var_entrypoint = NULL;
    generator_heap->tmp_for_loop_1__for_iterator = NULL;
    generator_heap->tmp_for_loop_1__iter_value = NULL;
    generator_heap->type_description_1 = NULL;
    generator_heap->exception_type = NULL;
    generator_heap->exception_value = NULL;
    generator_heap->exception_tb = NULL;
    generator_heap->exception_lineno = 0;

    // Actual generator function body.
    // Tried code:
    if (isFrameUnusable(cache_m_frame)) {
        Py_XDECREF(cache_m_frame);

#if _DEBUG_REFCOUNTS
        if (cache_m_frame == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_m_frame = MAKE_FUNCTION_FRAME(tstate, codeobj_ceb92494f6c172c57d7ef78414cc60e8, module_pygments$plugin, sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_m_frame->m_type_description == NULL);
    generator->m_frame = cache_m_frame;
    // Mark the frame object as in use, ref count 1 will be up for reuse.
    Py_INCREF(generator->m_frame);
    assert(Py_REFCNT(generator->m_frame) == 2); // Frame stack

    Nuitka_SetFrameGenerator(generator->m_frame, (PyObject *)generator);

    assert(generator->m_frame->m_frame.f_back == NULL);

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackGeneratorCompiledFrame(tstate, generator->m_frame);
    assert(Py_REFCNT(generator->m_frame) == 2);

    // Store currently existing exception as the one to publish again when we
    // yield or yield from.
    STORE_GENERATOR_EXCEPTION(tstate, generator);

    // Framed code:
    {
        PyObject *tmp_assign_source_1;
        PyObject *tmp_iter_arg_1;
        PyObject *tmp_called_value_1;
        PyObject *tmp_args_element_value_1;
        tmp_called_value_1 = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[118]);

        if (unlikely(tmp_called_value_1 == NULL)) {
            tmp_called_value_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[118]);
        }

        if (tmp_called_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 77;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_args_element_value_1 = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[122]);

        if (unlikely(tmp_args_element_value_1 == NULL)) {
            tmp_args_element_value_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[122]);
        }

        if (tmp_args_element_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 77;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        generator->m_frame->m_frame.f_lineno = 77;
        tmp_iter_arg_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_1, tmp_args_element_value_1);
        if (tmp_iter_arg_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 77;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_1 = MAKE_ITERATOR(tstate, tmp_iter_arg_1);
        Py_DECREF(tmp_iter_arg_1);
        if (tmp_assign_source_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 77;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        assert(generator_heap->tmp_for_loop_1__for_iterator == NULL);
        generator_heap->tmp_for_loop_1__for_iterator = tmp_assign_source_1;
    }
    // Tried code:
    loop_start_1:;
    {
        PyObject *tmp_next_source_1;
        PyObject *tmp_assign_source_2;
        CHECK_OBJECT(generator_heap->tmp_for_loop_1__for_iterator);
        tmp_next_source_1 = generator_heap->tmp_for_loop_1__for_iterator;
        tmp_assign_source_2 = ITERATOR_NEXT(tmp_next_source_1);
        if (tmp_assign_source_2 == NULL) {
            if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                goto loop_end_1;
            } else {

                FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);
                generator_heap->type_description_1 = "o";
                generator_heap->exception_lineno = 77;
                goto try_except_handler_2;
            }
        }

        {
            PyObject *old = generator_heap->tmp_for_loop_1__iter_value;
            generator_heap->tmp_for_loop_1__iter_value = tmp_assign_source_2;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_3;
        CHECK_OBJECT(generator_heap->tmp_for_loop_1__iter_value);
        tmp_assign_source_3 = generator_heap->tmp_for_loop_1__iter_value;
        {
            PyObject *old = generator_heap->var_entrypoint;
            generator_heap->var_entrypoint = tmp_assign_source_3;
            Py_INCREF(generator_heap->var_entrypoint);
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_expression_value_1;
        PyObject *tmp_tuple_element_1;
        PyObject *tmp_expression_value_2;
        NUITKA_MAY_BE_UNUSED PyObject *tmp_yield_result_1;
        CHECK_OBJECT(generator_heap->var_entrypoint);
        tmp_expression_value_2 = generator_heap->var_entrypoint;
        tmp_tuple_element_1 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_2, mod_consts[123]);
        if (tmp_tuple_element_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 78;
            generator_heap->type_description_1 = "o";
            goto try_except_handler_2;
        }
        tmp_expression_value_1 = MAKE_TUPLE_EMPTY(2);
        {
            PyObject *tmp_called_instance_1;
            PyTuple_SET_ITEM(tmp_expression_value_1, 0, tmp_tuple_element_1);
            CHECK_OBJECT(generator_heap->var_entrypoint);
            tmp_called_instance_1 = generator_heap->var_entrypoint;
            generator->m_frame->m_frame.f_lineno = 78;
            tmp_tuple_element_1 = CALL_METHOD_NO_ARGS(tstate, tmp_called_instance_1, mod_consts[120]);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


                generator_heap->exception_lineno = 78;
                generator_heap->type_description_1 = "o";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_expression_value_1, 1, tmp_tuple_element_1);
        }
        goto tuple_build_noexception_1;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_1:;
        Py_DECREF(tmp_expression_value_1);
        goto try_except_handler_2;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_1:;
        Nuitka_PreserveHeap(generator_heap->yield_tmps, &tmp_tuple_element_1, sizeof(PyObject *), &tmp_expression_value_2, sizeof(PyObject *), NULL);
        generator->m_yield_return_index = 1;
        return tmp_expression_value_1;
        yield_return_1:
        Nuitka_RestoreHeap(generator_heap->yield_tmps, &tmp_tuple_element_1, sizeof(PyObject *), &tmp_expression_value_2, sizeof(PyObject *), NULL);
        if (yield_return_value == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 78;
            generator_heap->type_description_1 = "o";
            goto try_except_handler_2;
        }
        tmp_yield_result_1 = yield_return_value;
        Py_DECREF(tmp_yield_result_1);
    }
    if (CONSIDER_THREADING(tstate) == false) {
        assert(HAS_ERROR_OCCURRED(tstate));

        FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


        generator_heap->exception_lineno = 77;
        generator_heap->type_description_1 = "o";
        goto try_except_handler_2;
    }
    goto loop_start_1;
    loop_end_1:;
    goto try_end_1;
    // Exception handler code:
    try_except_handler_2:;
    generator_heap->exception_keeper_type_1 = generator_heap->exception_type;
    generator_heap->exception_keeper_value_1 = generator_heap->exception_value;
    generator_heap->exception_keeper_tb_1 = generator_heap->exception_tb;
    generator_heap->exception_keeper_lineno_1 = generator_heap->exception_lineno;
    generator_heap->exception_type = NULL;
    generator_heap->exception_value = NULL;
    generator_heap->exception_tb = NULL;
    generator_heap->exception_lineno = 0;

    Py_XDECREF(generator_heap->tmp_for_loop_1__iter_value);
    generator_heap->tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(generator_heap->tmp_for_loop_1__for_iterator);
    Py_DECREF(generator_heap->tmp_for_loop_1__for_iterator);
    generator_heap->tmp_for_loop_1__for_iterator = NULL;
    // Re-raise.
    generator_heap->exception_type = generator_heap->exception_keeper_type_1;
    generator_heap->exception_value = generator_heap->exception_keeper_value_1;
    generator_heap->exception_tb = generator_heap->exception_keeper_tb_1;
    generator_heap->exception_lineno = generator_heap->exception_keeper_lineno_1;

    goto frame_exception_exit_1;
    // End of try:
    try_end_1:;

    // Release exception attached to the frame
    DROP_GENERATOR_EXCEPTION(generator);



    goto frame_no_exception_1;
    frame_exception_exit_1:;

    // If it's not an exit exception, consider and create a traceback for it.
    if (!EXCEPTION_MATCH_GENERATOR(tstate, generator_heap->exception_type)) {
        if (generator_heap->exception_tb == NULL) {
            generator_heap->exception_tb = MAKE_TRACEBACK(generator->m_frame, generator_heap->exception_lineno);
        } else if (generator_heap->exception_tb->tb_frame != &generator->m_frame->m_frame) {
            generator_heap->exception_tb = ADD_TRACEBACK(generator_heap->exception_tb, generator->m_frame, generator_heap->exception_lineno);
        }

        Nuitka_Frame_AttachLocals(
            generator->m_frame,
            generator_heap->type_description_1,
            generator_heap->var_entrypoint
        );


        // Release cached frame if used for exception.
        if (generator->m_frame == cache_m_frame) {
#if _DEBUG_REFCOUNTS
            count_active_frame_cache_instances -= 1;
            count_released_frame_cache_instances += 1;
#endif

            Py_DECREF(cache_m_frame);
            cache_m_frame = NULL;
        }

        assertFrameObject(generator->m_frame);
    }

#if PYTHON_VERSION >= 0x300
#if PYTHON_VERSION < 0x3b0
    Py_CLEAR(EXC_TYPE_F(generator));
#endif
    Py_CLEAR(EXC_VALUE_F(generator));
#if PYTHON_VERSION < 0x3b0
    Py_CLEAR(EXC_TRACEBACK_F(generator));
#endif
#endif

    // Return the error.
    goto try_except_handler_1;

    frame_no_exception_1:;
    goto try_end_2;
    // Exception handler code:
    try_except_handler_1:;
    generator_heap->exception_keeper_type_2 = generator_heap->exception_type;
    generator_heap->exception_keeper_value_2 = generator_heap->exception_value;
    generator_heap->exception_keeper_tb_2 = generator_heap->exception_tb;
    generator_heap->exception_keeper_lineno_2 = generator_heap->exception_lineno;
    generator_heap->exception_type = NULL;
    generator_heap->exception_value = NULL;
    generator_heap->exception_tb = NULL;
    generator_heap->exception_lineno = 0;

    Py_XDECREF(generator_heap->var_entrypoint);
    generator_heap->var_entrypoint = NULL;
    // Re-raise.
    generator_heap->exception_type = generator_heap->exception_keeper_type_2;
    generator_heap->exception_value = generator_heap->exception_keeper_value_2;
    generator_heap->exception_tb = generator_heap->exception_keeper_tb_2;
    generator_heap->exception_lineno = generator_heap->exception_keeper_lineno_2;

    goto function_exception_exit;
    // End of try:
    try_end_2:;
    Py_XDECREF(generator_heap->tmp_for_loop_1__iter_value);
    generator_heap->tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(generator_heap->tmp_for_loop_1__for_iterator);
    Py_DECREF(generator_heap->tmp_for_loop_1__for_iterator);
    generator_heap->tmp_for_loop_1__for_iterator = NULL;
    Py_XDECREF(generator_heap->var_entrypoint);
    generator_heap->var_entrypoint = NULL;


    return NULL;

    function_exception_exit:

    assert(generator_heap->exception_type);
    RESTORE_ERROR_OCCURRED(tstate, generator_heap->exception_type, generator_heap->exception_value, generator_heap->exception_tb);

    return NULL;

}

static PyObject *MAKE_GENERATOR_pygments$plugin$$$function__3_find_plugin_formatters$$$genobj__1_find_plugin_formatters() {
    return Nuitka_Generator_New(
        pygments$plugin$$$function__3_find_plugin_formatters$$$genobj__1_find_plugin_formatters_context,
        module_pygments$plugin,
        mod_consts[124],
#if PYTHON_VERSION >= 0x350
        NULL,
#endif
        codeobj_ceb92494f6c172c57d7ef78414cc60e8,
        NULL,
        0,
#if 1
        sizeof(struct pygments$plugin$$$function__3_find_plugin_formatters$$$genobj__1_find_plugin_formatters_locals)
#else
        0
#endif
    );
}


static PyObject *impl_pygments$plugin$$$function__4_find_plugin_styles(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *tmp_return_value = NULL;

    // Actual function body.


    tmp_return_value = MAKE_GENERATOR_pygments$plugin$$$function__4_find_plugin_styles$$$genobj__1_find_plugin_styles();

    goto function_return_exit;

    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;


function_return_exit:
   // Function cleanup code if any.


   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}



#if 1
struct pygments$plugin$$$function__4_find_plugin_styles$$$genobj__1_find_plugin_styles_locals {
    PyObject *var_entrypoint;
    PyObject *tmp_for_loop_1__for_iterator;
    PyObject *tmp_for_loop_1__iter_value;
    char const *type_description_1;
    PyObject *exception_type;
    PyObject *exception_value;
    PyTracebackObject *exception_tb;
    int exception_lineno;
    char yield_tmps[1024];
    PyObject *exception_keeper_type_1;
    PyObject *exception_keeper_value_1;
    PyTracebackObject *exception_keeper_tb_1;
    int exception_keeper_lineno_1;
    PyObject *exception_keeper_type_2;
    PyObject *exception_keeper_value_2;
    PyTracebackObject *exception_keeper_tb_2;
    int exception_keeper_lineno_2;
};
#endif

static PyObject *pygments$plugin$$$function__4_find_plugin_styles$$$genobj__1_find_plugin_styles_context(PyThreadState *tstate, struct Nuitka_GeneratorObject *generator, PyObject *yield_return_value) {
    CHECK_OBJECT(generator);
    assert(Nuitka_Generator_Check((PyObject *)generator));
    CHECK_OBJECT_X(yield_return_value);

#if 1
    // Heap access.
    struct pygments$plugin$$$function__4_find_plugin_styles$$$genobj__1_find_plugin_styles_locals *generator_heap = (struct pygments$plugin$$$function__4_find_plugin_styles$$$genobj__1_find_plugin_styles_locals *)generator->m_heap_storage;
#endif

    // Dispatch to yield based on return label index:
    switch(generator->m_yield_return_index) {
    case 1: goto yield_return_1;
    }

    // Local variable initialization
    NUITKA_MAY_BE_UNUSED nuitka_void tmp_unused;
    static struct Nuitka_FrameObject *cache_m_frame = NULL;
    generator_heap->var_entrypoint = NULL;
    generator_heap->tmp_for_loop_1__for_iterator = NULL;
    generator_heap->tmp_for_loop_1__iter_value = NULL;
    generator_heap->type_description_1 = NULL;
    generator_heap->exception_type = NULL;
    generator_heap->exception_value = NULL;
    generator_heap->exception_tb = NULL;
    generator_heap->exception_lineno = 0;

    // Actual generator function body.
    // Tried code:
    if (isFrameUnusable(cache_m_frame)) {
        Py_XDECREF(cache_m_frame);

#if _DEBUG_REFCOUNTS
        if (cache_m_frame == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_m_frame = MAKE_FUNCTION_FRAME(tstate, codeobj_2033227d0779c41662ecff4076cc2ed9, module_pygments$plugin, sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_m_frame->m_type_description == NULL);
    generator->m_frame = cache_m_frame;
    // Mark the frame object as in use, ref count 1 will be up for reuse.
    Py_INCREF(generator->m_frame);
    assert(Py_REFCNT(generator->m_frame) == 2); // Frame stack

    Nuitka_SetFrameGenerator(generator->m_frame, (PyObject *)generator);

    assert(generator->m_frame->m_frame.f_back == NULL);

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackGeneratorCompiledFrame(tstate, generator->m_frame);
    assert(Py_REFCNT(generator->m_frame) == 2);

    // Store currently existing exception as the one to publish again when we
    // yield or yield from.
    STORE_GENERATOR_EXCEPTION(tstate, generator);

    // Framed code:
    {
        PyObject *tmp_assign_source_1;
        PyObject *tmp_iter_arg_1;
        PyObject *tmp_called_value_1;
        PyObject *tmp_args_element_value_1;
        tmp_called_value_1 = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[118]);

        if (unlikely(tmp_called_value_1 == NULL)) {
            tmp_called_value_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[118]);
        }

        if (tmp_called_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 82;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_args_element_value_1 = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[125]);

        if (unlikely(tmp_args_element_value_1 == NULL)) {
            tmp_args_element_value_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[125]);
        }

        if (tmp_args_element_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 82;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        generator->m_frame->m_frame.f_lineno = 82;
        tmp_iter_arg_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_1, tmp_args_element_value_1);
        if (tmp_iter_arg_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 82;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_1 = MAKE_ITERATOR(tstate, tmp_iter_arg_1);
        Py_DECREF(tmp_iter_arg_1);
        if (tmp_assign_source_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 82;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        assert(generator_heap->tmp_for_loop_1__for_iterator == NULL);
        generator_heap->tmp_for_loop_1__for_iterator = tmp_assign_source_1;
    }
    // Tried code:
    loop_start_1:;
    {
        PyObject *tmp_next_source_1;
        PyObject *tmp_assign_source_2;
        CHECK_OBJECT(generator_heap->tmp_for_loop_1__for_iterator);
        tmp_next_source_1 = generator_heap->tmp_for_loop_1__for_iterator;
        tmp_assign_source_2 = ITERATOR_NEXT(tmp_next_source_1);
        if (tmp_assign_source_2 == NULL) {
            if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                goto loop_end_1;
            } else {

                FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);
                generator_heap->type_description_1 = "o";
                generator_heap->exception_lineno = 82;
                goto try_except_handler_2;
            }
        }

        {
            PyObject *old = generator_heap->tmp_for_loop_1__iter_value;
            generator_heap->tmp_for_loop_1__iter_value = tmp_assign_source_2;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_3;
        CHECK_OBJECT(generator_heap->tmp_for_loop_1__iter_value);
        tmp_assign_source_3 = generator_heap->tmp_for_loop_1__iter_value;
        {
            PyObject *old = generator_heap->var_entrypoint;
            generator_heap->var_entrypoint = tmp_assign_source_3;
            Py_INCREF(generator_heap->var_entrypoint);
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_expression_value_1;
        PyObject *tmp_tuple_element_1;
        PyObject *tmp_expression_value_2;
        NUITKA_MAY_BE_UNUSED PyObject *tmp_yield_result_1;
        CHECK_OBJECT(generator_heap->var_entrypoint);
        tmp_expression_value_2 = generator_heap->var_entrypoint;
        tmp_tuple_element_1 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_2, mod_consts[123]);
        if (tmp_tuple_element_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 83;
            generator_heap->type_description_1 = "o";
            goto try_except_handler_2;
        }
        tmp_expression_value_1 = MAKE_TUPLE_EMPTY(2);
        {
            PyObject *tmp_called_instance_1;
            PyTuple_SET_ITEM(tmp_expression_value_1, 0, tmp_tuple_element_1);
            CHECK_OBJECT(generator_heap->var_entrypoint);
            tmp_called_instance_1 = generator_heap->var_entrypoint;
            generator->m_frame->m_frame.f_lineno = 83;
            tmp_tuple_element_1 = CALL_METHOD_NO_ARGS(tstate, tmp_called_instance_1, mod_consts[120]);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


                generator_heap->exception_lineno = 83;
                generator_heap->type_description_1 = "o";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_expression_value_1, 1, tmp_tuple_element_1);
        }
        goto tuple_build_noexception_1;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_1:;
        Py_DECREF(tmp_expression_value_1);
        goto try_except_handler_2;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_1:;
        Nuitka_PreserveHeap(generator_heap->yield_tmps, &tmp_tuple_element_1, sizeof(PyObject *), &tmp_expression_value_2, sizeof(PyObject *), NULL);
        generator->m_yield_return_index = 1;
        return tmp_expression_value_1;
        yield_return_1:
        Nuitka_RestoreHeap(generator_heap->yield_tmps, &tmp_tuple_element_1, sizeof(PyObject *), &tmp_expression_value_2, sizeof(PyObject *), NULL);
        if (yield_return_value == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 83;
            generator_heap->type_description_1 = "o";
            goto try_except_handler_2;
        }
        tmp_yield_result_1 = yield_return_value;
        Py_DECREF(tmp_yield_result_1);
    }
    if (CONSIDER_THREADING(tstate) == false) {
        assert(HAS_ERROR_OCCURRED(tstate));

        FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


        generator_heap->exception_lineno = 82;
        generator_heap->type_description_1 = "o";
        goto try_except_handler_2;
    }
    goto loop_start_1;
    loop_end_1:;
    goto try_end_1;
    // Exception handler code:
    try_except_handler_2:;
    generator_heap->exception_keeper_type_1 = generator_heap->exception_type;
    generator_heap->exception_keeper_value_1 = generator_heap->exception_value;
    generator_heap->exception_keeper_tb_1 = generator_heap->exception_tb;
    generator_heap->exception_keeper_lineno_1 = generator_heap->exception_lineno;
    generator_heap->exception_type = NULL;
    generator_heap->exception_value = NULL;
    generator_heap->exception_tb = NULL;
    generator_heap->exception_lineno = 0;

    Py_XDECREF(generator_heap->tmp_for_loop_1__iter_value);
    generator_heap->tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(generator_heap->tmp_for_loop_1__for_iterator);
    Py_DECREF(generator_heap->tmp_for_loop_1__for_iterator);
    generator_heap->tmp_for_loop_1__for_iterator = NULL;
    // Re-raise.
    generator_heap->exception_type = generator_heap->exception_keeper_type_1;
    generator_heap->exception_value = generator_heap->exception_keeper_value_1;
    generator_heap->exception_tb = generator_heap->exception_keeper_tb_1;
    generator_heap->exception_lineno = generator_heap->exception_keeper_lineno_1;

    goto frame_exception_exit_1;
    // End of try:
    try_end_1:;

    // Release exception attached to the frame
    DROP_GENERATOR_EXCEPTION(generator);



    goto frame_no_exception_1;
    frame_exception_exit_1:;

    // If it's not an exit exception, consider and create a traceback for it.
    if (!EXCEPTION_MATCH_GENERATOR(tstate, generator_heap->exception_type)) {
        if (generator_heap->exception_tb == NULL) {
            generator_heap->exception_tb = MAKE_TRACEBACK(generator->m_frame, generator_heap->exception_lineno);
        } else if (generator_heap->exception_tb->tb_frame != &generator->m_frame->m_frame) {
            generator_heap->exception_tb = ADD_TRACEBACK(generator_heap->exception_tb, generator->m_frame, generator_heap->exception_lineno);
        }

        Nuitka_Frame_AttachLocals(
            generator->m_frame,
            generator_heap->type_description_1,
            generator_heap->var_entrypoint
        );


        // Release cached frame if used for exception.
        if (generator->m_frame == cache_m_frame) {
#if _DEBUG_REFCOUNTS
            count_active_frame_cache_instances -= 1;
            count_released_frame_cache_instances += 1;
#endif

            Py_DECREF(cache_m_frame);
            cache_m_frame = NULL;
        }

        assertFrameObject(generator->m_frame);
    }

#if PYTHON_VERSION >= 0x300
#if PYTHON_VERSION < 0x3b0
    Py_CLEAR(EXC_TYPE_F(generator));
#endif
    Py_CLEAR(EXC_VALUE_F(generator));
#if PYTHON_VERSION < 0x3b0
    Py_CLEAR(EXC_TRACEBACK_F(generator));
#endif
#endif

    // Return the error.
    goto try_except_handler_1;

    frame_no_exception_1:;
    goto try_end_2;
    // Exception handler code:
    try_except_handler_1:;
    generator_heap->exception_keeper_type_2 = generator_heap->exception_type;
    generator_heap->exception_keeper_value_2 = generator_heap->exception_value;
    generator_heap->exception_keeper_tb_2 = generator_heap->exception_tb;
    generator_heap->exception_keeper_lineno_2 = generator_heap->exception_lineno;
    generator_heap->exception_type = NULL;
    generator_heap->exception_value = NULL;
    generator_heap->exception_tb = NULL;
    generator_heap->exception_lineno = 0;

    Py_XDECREF(generator_heap->var_entrypoint);
    generator_heap->var_entrypoint = NULL;
    // Re-raise.
    generator_heap->exception_type = generator_heap->exception_keeper_type_2;
    generator_heap->exception_value = generator_heap->exception_keeper_value_2;
    generator_heap->exception_tb = generator_heap->exception_keeper_tb_2;
    generator_heap->exception_lineno = generator_heap->exception_keeper_lineno_2;

    goto function_exception_exit;
    // End of try:
    try_end_2:;
    Py_XDECREF(generator_heap->tmp_for_loop_1__iter_value);
    generator_heap->tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(generator_heap->tmp_for_loop_1__for_iterator);
    Py_DECREF(generator_heap->tmp_for_loop_1__for_iterator);
    generator_heap->tmp_for_loop_1__for_iterator = NULL;
    Py_XDECREF(generator_heap->var_entrypoint);
    generator_heap->var_entrypoint = NULL;


    return NULL;

    function_exception_exit:

    assert(generator_heap->exception_type);
    RESTORE_ERROR_OCCURRED(tstate, generator_heap->exception_type, generator_heap->exception_value, generator_heap->exception_tb);

    return NULL;

}

static PyObject *MAKE_GENERATOR_pygments$plugin$$$function__4_find_plugin_styles$$$genobj__1_find_plugin_styles() {
    return Nuitka_Generator_New(
        pygments$plugin$$$function__4_find_plugin_styles$$$genobj__1_find_plugin_styles_context,
        module_pygments$plugin,
        mod_consts[126],
#if PYTHON_VERSION >= 0x350
        NULL,
#endif
        codeobj_2033227d0779c41662ecff4076cc2ed9,
        NULL,
        0,
#if 1
        sizeof(struct pygments$plugin$$$function__4_find_plugin_styles$$$genobj__1_find_plugin_styles_locals)
#else
        0
#endif
    );
}


static PyObject *impl_pygments$plugin$$$function__5_find_plugin_filters(PyThreadState *tstate, struct Nuitka_FunctionObject const *self, PyObject **python_pars) {
    // Preserve error status for checks
#ifndef __NUITKA_NO_ASSERT__
    NUITKA_MAY_BE_UNUSED bool had_error = HAS_ERROR_OCCURRED(tstate);
#endif

    // Local variable declarations.
    PyObject *tmp_return_value = NULL;

    // Actual function body.


    tmp_return_value = MAKE_GENERATOR_pygments$plugin$$$function__5_find_plugin_filters$$$genobj__1_find_plugin_filters();

    goto function_return_exit;

    NUITKA_CANNOT_GET_HERE("Return statement must have exited already.");
    return NULL;


function_return_exit:
   // Function cleanup code if any.


   // Actual function exit with return value, making sure we did not make
   // the error status worse despite non-NULL return.
   CHECK_OBJECT(tmp_return_value);
   assert(had_error || !HAS_ERROR_OCCURRED(tstate));
   return tmp_return_value;
}



#if 1
struct pygments$plugin$$$function__5_find_plugin_filters$$$genobj__1_find_plugin_filters_locals {
    PyObject *var_entrypoint;
    PyObject *tmp_for_loop_1__for_iterator;
    PyObject *tmp_for_loop_1__iter_value;
    char const *type_description_1;
    PyObject *exception_type;
    PyObject *exception_value;
    PyTracebackObject *exception_tb;
    int exception_lineno;
    char yield_tmps[1024];
    PyObject *exception_keeper_type_1;
    PyObject *exception_keeper_value_1;
    PyTracebackObject *exception_keeper_tb_1;
    int exception_keeper_lineno_1;
    PyObject *exception_keeper_type_2;
    PyObject *exception_keeper_value_2;
    PyTracebackObject *exception_keeper_tb_2;
    int exception_keeper_lineno_2;
};
#endif

static PyObject *pygments$plugin$$$function__5_find_plugin_filters$$$genobj__1_find_plugin_filters_context(PyThreadState *tstate, struct Nuitka_GeneratorObject *generator, PyObject *yield_return_value) {
    CHECK_OBJECT(generator);
    assert(Nuitka_Generator_Check((PyObject *)generator));
    CHECK_OBJECT_X(yield_return_value);

#if 1
    // Heap access.
    struct pygments$plugin$$$function__5_find_plugin_filters$$$genobj__1_find_plugin_filters_locals *generator_heap = (struct pygments$plugin$$$function__5_find_plugin_filters$$$genobj__1_find_plugin_filters_locals *)generator->m_heap_storage;
#endif

    // Dispatch to yield based on return label index:
    switch(generator->m_yield_return_index) {
    case 1: goto yield_return_1;
    }

    // Local variable initialization
    NUITKA_MAY_BE_UNUSED nuitka_void tmp_unused;
    static struct Nuitka_FrameObject *cache_m_frame = NULL;
    generator_heap->var_entrypoint = NULL;
    generator_heap->tmp_for_loop_1__for_iterator = NULL;
    generator_heap->tmp_for_loop_1__iter_value = NULL;
    generator_heap->type_description_1 = NULL;
    generator_heap->exception_type = NULL;
    generator_heap->exception_value = NULL;
    generator_heap->exception_tb = NULL;
    generator_heap->exception_lineno = 0;

    // Actual generator function body.
    // Tried code:
    if (isFrameUnusable(cache_m_frame)) {
        Py_XDECREF(cache_m_frame);

#if _DEBUG_REFCOUNTS
        if (cache_m_frame == NULL) {
            count_active_frame_cache_instances += 1;
        } else {
            count_released_frame_cache_instances += 1;
        }
        count_allocated_frame_cache_instances += 1;
#endif
        cache_m_frame = MAKE_FUNCTION_FRAME(tstate, codeobj_07017567a5a33bc26d066f927c932cd3, module_pygments$plugin, sizeof(void *));
#if _DEBUG_REFCOUNTS
    } else {
        count_hit_frame_cache_instances += 1;
#endif
    }

    assert(cache_m_frame->m_type_description == NULL);
    generator->m_frame = cache_m_frame;
    // Mark the frame object as in use, ref count 1 will be up for reuse.
    Py_INCREF(generator->m_frame);
    assert(Py_REFCNT(generator->m_frame) == 2); // Frame stack

    Nuitka_SetFrameGenerator(generator->m_frame, (PyObject *)generator);

    assert(generator->m_frame->m_frame.f_back == NULL);

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackGeneratorCompiledFrame(tstate, generator->m_frame);
    assert(Py_REFCNT(generator->m_frame) == 2);

    // Store currently existing exception as the one to publish again when we
    // yield or yield from.
    STORE_GENERATOR_EXCEPTION(tstate, generator);

    // Framed code:
    {
        PyObject *tmp_assign_source_1;
        PyObject *tmp_iter_arg_1;
        PyObject *tmp_called_value_1;
        PyObject *tmp_args_element_value_1;
        tmp_called_value_1 = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[118]);

        if (unlikely(tmp_called_value_1 == NULL)) {
            tmp_called_value_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[118]);
        }

        if (tmp_called_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 87;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_args_element_value_1 = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[127]);

        if (unlikely(tmp_args_element_value_1 == NULL)) {
            tmp_args_element_value_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[127]);
        }

        if (tmp_args_element_value_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 87;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        generator->m_frame->m_frame.f_lineno = 87;
        tmp_iter_arg_1 = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, tmp_called_value_1, tmp_args_element_value_1);
        if (tmp_iter_arg_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 87;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        tmp_assign_source_1 = MAKE_ITERATOR(tstate, tmp_iter_arg_1);
        Py_DECREF(tmp_iter_arg_1);
        if (tmp_assign_source_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 87;
            generator_heap->type_description_1 = "o";
            goto frame_exception_exit_1;
        }
        assert(generator_heap->tmp_for_loop_1__for_iterator == NULL);
        generator_heap->tmp_for_loop_1__for_iterator = tmp_assign_source_1;
    }
    // Tried code:
    loop_start_1:;
    {
        PyObject *tmp_next_source_1;
        PyObject *tmp_assign_source_2;
        CHECK_OBJECT(generator_heap->tmp_for_loop_1__for_iterator);
        tmp_next_source_1 = generator_heap->tmp_for_loop_1__for_iterator;
        tmp_assign_source_2 = ITERATOR_NEXT(tmp_next_source_1);
        if (tmp_assign_source_2 == NULL) {
            if (CHECK_AND_CLEAR_STOP_ITERATION_OCCURRED(tstate)) {

                goto loop_end_1;
            } else {

                FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);
                generator_heap->type_description_1 = "o";
                generator_heap->exception_lineno = 87;
                goto try_except_handler_2;
            }
        }

        {
            PyObject *old = generator_heap->tmp_for_loop_1__iter_value;
            generator_heap->tmp_for_loop_1__iter_value = tmp_assign_source_2;
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_assign_source_3;
        CHECK_OBJECT(generator_heap->tmp_for_loop_1__iter_value);
        tmp_assign_source_3 = generator_heap->tmp_for_loop_1__iter_value;
        {
            PyObject *old = generator_heap->var_entrypoint;
            generator_heap->var_entrypoint = tmp_assign_source_3;
            Py_INCREF(generator_heap->var_entrypoint);
            Py_XDECREF(old);
        }

    }
    {
        PyObject *tmp_expression_value_1;
        PyObject *tmp_tuple_element_1;
        PyObject *tmp_expression_value_2;
        NUITKA_MAY_BE_UNUSED PyObject *tmp_yield_result_1;
        CHECK_OBJECT(generator_heap->var_entrypoint);
        tmp_expression_value_2 = generator_heap->var_entrypoint;
        tmp_tuple_element_1 = LOOKUP_ATTRIBUTE(tstate, tmp_expression_value_2, mod_consts[123]);
        if (tmp_tuple_element_1 == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 88;
            generator_heap->type_description_1 = "o";
            goto try_except_handler_2;
        }
        tmp_expression_value_1 = MAKE_TUPLE_EMPTY(2);
        {
            PyObject *tmp_called_instance_1;
            PyTuple_SET_ITEM(tmp_expression_value_1, 0, tmp_tuple_element_1);
            CHECK_OBJECT(generator_heap->var_entrypoint);
            tmp_called_instance_1 = generator_heap->var_entrypoint;
            generator->m_frame->m_frame.f_lineno = 88;
            tmp_tuple_element_1 = CALL_METHOD_NO_ARGS(tstate, tmp_called_instance_1, mod_consts[120]);
            if (tmp_tuple_element_1 == NULL) {
                assert(HAS_ERROR_OCCURRED(tstate));

                FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


                generator_heap->exception_lineno = 88;
                generator_heap->type_description_1 = "o";
                goto tuple_build_exception_1;
            }
            PyTuple_SET_ITEM(tmp_expression_value_1, 1, tmp_tuple_element_1);
        }
        goto tuple_build_noexception_1;
        // Exception handling pass through code for tuple_build:
        tuple_build_exception_1:;
        Py_DECREF(tmp_expression_value_1);
        goto try_except_handler_2;
        // Finished with no exception for tuple_build:
        tuple_build_noexception_1:;
        Nuitka_PreserveHeap(generator_heap->yield_tmps, &tmp_tuple_element_1, sizeof(PyObject *), &tmp_expression_value_2, sizeof(PyObject *), NULL);
        generator->m_yield_return_index = 1;
        return tmp_expression_value_1;
        yield_return_1:
        Nuitka_RestoreHeap(generator_heap->yield_tmps, &tmp_tuple_element_1, sizeof(PyObject *), &tmp_expression_value_2, sizeof(PyObject *), NULL);
        if (yield_return_value == NULL) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


            generator_heap->exception_lineno = 88;
            generator_heap->type_description_1 = "o";
            goto try_except_handler_2;
        }
        tmp_yield_result_1 = yield_return_value;
        Py_DECREF(tmp_yield_result_1);
    }
    if (CONSIDER_THREADING(tstate) == false) {
        assert(HAS_ERROR_OCCURRED(tstate));

        FETCH_ERROR_OCCURRED(tstate, &generator_heap->exception_type, &generator_heap->exception_value, &generator_heap->exception_tb);


        generator_heap->exception_lineno = 87;
        generator_heap->type_description_1 = "o";
        goto try_except_handler_2;
    }
    goto loop_start_1;
    loop_end_1:;
    goto try_end_1;
    // Exception handler code:
    try_except_handler_2:;
    generator_heap->exception_keeper_type_1 = generator_heap->exception_type;
    generator_heap->exception_keeper_value_1 = generator_heap->exception_value;
    generator_heap->exception_keeper_tb_1 = generator_heap->exception_tb;
    generator_heap->exception_keeper_lineno_1 = generator_heap->exception_lineno;
    generator_heap->exception_type = NULL;
    generator_heap->exception_value = NULL;
    generator_heap->exception_tb = NULL;
    generator_heap->exception_lineno = 0;

    Py_XDECREF(generator_heap->tmp_for_loop_1__iter_value);
    generator_heap->tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(generator_heap->tmp_for_loop_1__for_iterator);
    Py_DECREF(generator_heap->tmp_for_loop_1__for_iterator);
    generator_heap->tmp_for_loop_1__for_iterator = NULL;
    // Re-raise.
    generator_heap->exception_type = generator_heap->exception_keeper_type_1;
    generator_heap->exception_value = generator_heap->exception_keeper_value_1;
    generator_heap->exception_tb = generator_heap->exception_keeper_tb_1;
    generator_heap->exception_lineno = generator_heap->exception_keeper_lineno_1;

    goto frame_exception_exit_1;
    // End of try:
    try_end_1:;

    // Release exception attached to the frame
    DROP_GENERATOR_EXCEPTION(generator);



    goto frame_no_exception_1;
    frame_exception_exit_1:;

    // If it's not an exit exception, consider and create a traceback for it.
    if (!EXCEPTION_MATCH_GENERATOR(tstate, generator_heap->exception_type)) {
        if (generator_heap->exception_tb == NULL) {
            generator_heap->exception_tb = MAKE_TRACEBACK(generator->m_frame, generator_heap->exception_lineno);
        } else if (generator_heap->exception_tb->tb_frame != &generator->m_frame->m_frame) {
            generator_heap->exception_tb = ADD_TRACEBACK(generator_heap->exception_tb, generator->m_frame, generator_heap->exception_lineno);
        }

        Nuitka_Frame_AttachLocals(
            generator->m_frame,
            generator_heap->type_description_1,
            generator_heap->var_entrypoint
        );


        // Release cached frame if used for exception.
        if (generator->m_frame == cache_m_frame) {
#if _DEBUG_REFCOUNTS
            count_active_frame_cache_instances -= 1;
            count_released_frame_cache_instances += 1;
#endif

            Py_DECREF(cache_m_frame);
            cache_m_frame = NULL;
        }

        assertFrameObject(generator->m_frame);
    }

#if PYTHON_VERSION >= 0x300
#if PYTHON_VERSION < 0x3b0
    Py_CLEAR(EXC_TYPE_F(generator));
#endif
    Py_CLEAR(EXC_VALUE_F(generator));
#if PYTHON_VERSION < 0x3b0
    Py_CLEAR(EXC_TRACEBACK_F(generator));
#endif
#endif

    // Return the error.
    goto try_except_handler_1;

    frame_no_exception_1:;
    goto try_end_2;
    // Exception handler code:
    try_except_handler_1:;
    generator_heap->exception_keeper_type_2 = generator_heap->exception_type;
    generator_heap->exception_keeper_value_2 = generator_heap->exception_value;
    generator_heap->exception_keeper_tb_2 = generator_heap->exception_tb;
    generator_heap->exception_keeper_lineno_2 = generator_heap->exception_lineno;
    generator_heap->exception_type = NULL;
    generator_heap->exception_value = NULL;
    generator_heap->exception_tb = NULL;
    generator_heap->exception_lineno = 0;

    Py_XDECREF(generator_heap->var_entrypoint);
    generator_heap->var_entrypoint = NULL;
    // Re-raise.
    generator_heap->exception_type = generator_heap->exception_keeper_type_2;
    generator_heap->exception_value = generator_heap->exception_keeper_value_2;
    generator_heap->exception_tb = generator_heap->exception_keeper_tb_2;
    generator_heap->exception_lineno = generator_heap->exception_keeper_lineno_2;

    goto function_exception_exit;
    // End of try:
    try_end_2:;
    Py_XDECREF(generator_heap->tmp_for_loop_1__iter_value);
    generator_heap->tmp_for_loop_1__iter_value = NULL;
    CHECK_OBJECT(generator_heap->tmp_for_loop_1__for_iterator);
    Py_DECREF(generator_heap->tmp_for_loop_1__for_iterator);
    generator_heap->tmp_for_loop_1__for_iterator = NULL;
    Py_XDECREF(generator_heap->var_entrypoint);
    generator_heap->var_entrypoint = NULL;


    return NULL;

    function_exception_exit:

    assert(generator_heap->exception_type);
    RESTORE_ERROR_OCCURRED(tstate, generator_heap->exception_type, generator_heap->exception_value, generator_heap->exception_tb);

    return NULL;

}

static PyObject *MAKE_GENERATOR_pygments$plugin$$$function__5_find_plugin_filters$$$genobj__1_find_plugin_filters() {
    return Nuitka_Generator_New(
        pygments$plugin$$$function__5_find_plugin_filters$$$genobj__1_find_plugin_filters_context,
        module_pygments$plugin,
        mod_consts[128],
#if PYTHON_VERSION >= 0x350
        NULL,
#endif
        codeobj_07017567a5a33bc26d066f927c932cd3,
        NULL,
        0,
#if 1
        sizeof(struct pygments$plugin$$$function__5_find_plugin_filters$$$genobj__1_find_plugin_filters_locals)
#else
        0
#endif
    );
}



static PyObject *MAKE_FUNCTION_pygments$plugin$$$function__1_iter_entry_points() {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_pygments$plugin$$$function__1_iter_entry_points,
        mod_consts[118],
#if PYTHON_VERSION >= 0x300
        NULL,
#endif
        codeobj_be4da8bfd064e70c4899ee31e77c316c,
        NULL,
#if PYTHON_VERSION >= 0x300
        NULL,
        NULL,
#endif
        module_pygments$plugin,
        NULL,
        NULL,
        0
    );


    return (PyObject *)result;
}



static PyObject *MAKE_FUNCTION_pygments$plugin$$$function__2_find_plugin_lexers() {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_pygments$plugin$$$function__2_find_plugin_lexers,
        mod_consts[121],
#if PYTHON_VERSION >= 0x300
        NULL,
#endif
        codeobj_69dc823866a694451fa9ac511ed82c60,
        NULL,
#if PYTHON_VERSION >= 0x300
        NULL,
        NULL,
#endif
        module_pygments$plugin,
        NULL,
        NULL,
        0
    );


    return (PyObject *)result;
}



static PyObject *MAKE_FUNCTION_pygments$plugin$$$function__3_find_plugin_formatters() {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_pygments$plugin$$$function__3_find_plugin_formatters,
        mod_consts[124],
#if PYTHON_VERSION >= 0x300
        NULL,
#endif
        codeobj_ceb92494f6c172c57d7ef78414cc60e8,
        NULL,
#if PYTHON_VERSION >= 0x300
        NULL,
        NULL,
#endif
        module_pygments$plugin,
        NULL,
        NULL,
        0
    );


    return (PyObject *)result;
}



static PyObject *MAKE_FUNCTION_pygments$plugin$$$function__4_find_plugin_styles() {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_pygments$plugin$$$function__4_find_plugin_styles,
        mod_consts[126],
#if PYTHON_VERSION >= 0x300
        NULL,
#endif
        codeobj_2033227d0779c41662ecff4076cc2ed9,
        NULL,
#if PYTHON_VERSION >= 0x300
        NULL,
        NULL,
#endif
        module_pygments$plugin,
        NULL,
        NULL,
        0
    );


    return (PyObject *)result;
}



static PyObject *MAKE_FUNCTION_pygments$plugin$$$function__5_find_plugin_filters() {
    struct Nuitka_FunctionObject *result = Nuitka_Function_New(
        impl_pygments$plugin$$$function__5_find_plugin_filters,
        mod_consts[128],
#if PYTHON_VERSION >= 0x300
        NULL,
#endif
        codeobj_07017567a5a33bc26d066f927c932cd3,
        NULL,
#if PYTHON_VERSION >= 0x300
        NULL,
        NULL,
#endif
        module_pygments$plugin,
        NULL,
        NULL,
        0
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

static function_impl_code const function_table_pygments$plugin[] = {
    impl_pygments$plugin$$$function__1_iter_entry_points,
    impl_pygments$plugin$$$function__2_find_plugin_lexers,
    impl_pygments$plugin$$$function__3_find_plugin_formatters,
    impl_pygments$plugin$$$function__4_find_plugin_styles,
    impl_pygments$plugin$$$function__5_find_plugin_filters,
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

    int offset = Nuitka_Function_GetFunctionCodeIndex(function, function_table_pygments$plugin);

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
        module_pygments$plugin,
        function_qualname,
        function_index,
        code_object_desc,
        constant_return_value,
        defaults,
        kw_defaults,
        doc,
        closure,
        function_table_pygments$plugin,
        sizeof(function_table_pygments$plugin) / sizeof(function_impl_code)
    );
}

static PyMethodDef _method_def_create_compiled_function = {
    "create_compiled_function",
    (PyCFunction)_create_compiled_function,
    METH_VARARGS, NULL
};


#endif

// Internal entry point for module code.
PyObject *modulecode_pygments$plugin(PyThreadState *tstate, PyObject *module, struct Nuitka_MetaPathBasedLoaderEntry const *loader_entry) {
    // Report entry to PGO.
    PGO_onModuleEntered("pygments$plugin");

    // Store the module for future use.
    module_pygments$plugin = module;

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
        PRINT_STRING("pygments$plugin: Calling setupMetaPathBasedLoader().\n");
#endif
        setupMetaPathBasedLoader(tstate);

#if PYTHON_VERSION >= 0x300
        patchInspectModule(tstate);
#endif

#endif

        /* The constants only used by this module are created now. */
        NUITKA_PRINT_TRACE("pygments$plugin: Calling createModuleConstants().\n");
        createModuleConstants(tstate);

        createModuleCodeObjects();

        init_done = true;
    }

#if defined(_NUITKA_MODULE) && 0
    PyObject *pre_load = IMPORT_EMBEDDED_MODULE(tstate, "pygments.plugin" "-preLoad");
    if (pre_load == NULL) {
        return NULL;
    }
#endif

    // PRINT_STRING("in initpygments$plugin\n");

    moduledict_pygments$plugin = MODULE_DICT(module_pygments$plugin);

#ifdef _NUITKA_PLUGIN_DILL_ENABLED
    {
        char const *module_name_c;
        if (loader_entry != NULL) {
            module_name_c = loader_entry->name;
        } else {
            PyObject *module_name = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)const_str_plain___name__);
            module_name_c = Nuitka_String_AsString(module_name);
        }

        registerDillPluginTables(tstate, module_name_c, &_method_def_reduce_compiled_function, &_method_def_create_compiled_function);
    }
#endif

    // Set "__compiled__" to what version information we have.
    UPDATE_STRING_DICT0(
        moduledict_pygments$plugin,
        (Nuitka_StringObject *)const_str_plain___compiled__,
        Nuitka_dunder_compiled_value
    );

    // Update "__package__" value to what it ought to be.
    {
#if 0
        UPDATE_STRING_DICT0(
            moduledict_pygments$plugin,
            (Nuitka_StringObject *)const_str_plain___package__,
            mod_consts[144]
        );
#elif 0
        PyObject *module_name = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)const_str_plain___name__);

        UPDATE_STRING_DICT0(
            moduledict_pygments$plugin,
            (Nuitka_StringObject *)const_str_plain___package__,
            module_name
        );
#else

#if PYTHON_VERSION < 0x300
        PyObject *module_name = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)const_str_plain___name__);
        char const *module_name_cstr = PyString_AS_STRING(module_name);

        char const *last_dot = strrchr(module_name_cstr, '.');

        if (last_dot != NULL) {
            UPDATE_STRING_DICT1(
                moduledict_pygments$plugin,
                (Nuitka_StringObject *)const_str_plain___package__,
                PyString_FromStringAndSize(module_name_cstr, last_dot - module_name_cstr)
            );
        }
#else
        PyObject *module_name = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)const_str_plain___name__);
        Py_ssize_t dot_index = PyUnicode_Find(module_name, const_str_dot, 0, PyUnicode_GetLength(module_name), -1);

        if (dot_index != -1) {
            UPDATE_STRING_DICT1(
                moduledict_pygments$plugin,
                (Nuitka_StringObject *)const_str_plain___package__,
                PyUnicode_Substring(module_name, 0, dot_index)
            );
        }
#endif
#endif
    }

    CHECK_OBJECT(module_pygments$plugin);

    // For deep importing of a module we need to have "__builtins__", so we set
    // it ourselves in the same way than CPython does. Note: This must be done
    // before the frame object is allocated, or else it may fail.

    if (GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)const_str_plain___builtins__) == NULL) {
        PyObject *value = (PyObject *)builtin_module;

        // Check if main module, not a dict then but the module itself.
#if defined(_NUITKA_MODULE) || !0
        value = PyModule_GetDict(value);
#endif

        UPDATE_STRING_DICT0(moduledict_pygments$plugin, (Nuitka_StringObject *)const_str_plain___builtins__, value);
    }

    UPDATE_STRING_DICT0(moduledict_pygments$plugin, (Nuitka_StringObject *)const_str_plain___loader__, (PyObject *)&Nuitka_Loader_Type);

#if PYTHON_VERSION >= 0x340
// Set the "__spec__" value

#if 0
    // Main modules just get "None" as spec.
    UPDATE_STRING_DICT0(moduledict_pygments$plugin, (Nuitka_StringObject *)const_str_plain___spec__, Py_None);
#else
    // Other modules get a "ModuleSpec" from the standard mechanism.
    {
        PyObject *bootstrap_module = getImportLibBootstrapModule();
        CHECK_OBJECT(bootstrap_module);

        PyObject *_spec_from_module = PyObject_GetAttrString(bootstrap_module, "_spec_from_module");
        CHECK_OBJECT(_spec_from_module);

        PyObject *spec_value = CALL_FUNCTION_WITH_SINGLE_ARG(tstate, _spec_from_module, module_pygments$plugin);
        Py_DECREF(_spec_from_module);

        // We can assume this to never fail, or else we are in trouble anyway.
        // CHECK_OBJECT(spec_value);

        if (spec_value == NULL) {
            PyErr_PrintEx(0);
            abort();
        }

// Mark the execution in the "__spec__" value.
        SET_ATTRIBUTE(tstate, spec_value, const_str_plain__initializing, Py_True);

        UPDATE_STRING_DICT1(moduledict_pygments$plugin, (Nuitka_StringObject *)const_str_plain___spec__, spec_value);
    }
#endif
#endif

    // Temp variables if any
    struct Nuitka_FrameObject *frame_ebe3fc16cc6109fce68be05c0d37c541;
    NUITKA_MAY_BE_UNUSED char const *type_description_1 = NULL;
    bool tmp_result;
    PyObject *exception_type = NULL;
    PyObject *exception_value = NULL;
    PyTracebackObject *exception_tb = NULL;
    NUITKA_MAY_BE_UNUSED int exception_lineno = 0;

    // Module code.
    {
        PyObject *tmp_assign_source_1;
        tmp_assign_source_1 = mod_consts[129];
        UPDATE_STRING_DICT0(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[130], tmp_assign_source_1);
    }
    {
        PyObject *tmp_assign_source_2;
        tmp_assign_source_2 = module_filename_obj;
        UPDATE_STRING_DICT0(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[131], tmp_assign_source_2);
    }
    frame_ebe3fc16cc6109fce68be05c0d37c541 = MAKE_MODULE_FRAME(codeobj_ebe3fc16cc6109fce68be05c0d37c541, module_pygments$plugin);

    // Push the new frame as the currently active one, and we should be exclusively
    // owning it.
    pushFrameStackCompiledFrame(tstate, frame_ebe3fc16cc6109fce68be05c0d37c541);
    assert(Py_REFCNT(frame_ebe3fc16cc6109fce68be05c0d37c541) == 2);

    // Framed code:
    {
        PyObject *tmp_assattr_value_1;
        PyObject *tmp_assattr_target_1;
        tmp_assattr_value_1 = module_filename_obj;
        tmp_assattr_target_1 = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[132]);

        if (unlikely(tmp_assattr_target_1 == NULL)) {
            tmp_assattr_target_1 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[132]);
        }

        assert(!(tmp_assattr_target_1 == NULL));
        tmp_result = SET_ATTRIBUTE(tstate, tmp_assattr_target_1, mod_consts[133], tmp_assattr_value_1);
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
        tmp_assattr_target_2 = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[132]);

        if (unlikely(tmp_assattr_target_2 == NULL)) {
            tmp_assattr_target_2 = GET_MODULE_VARIABLE_VALUE_FALLBACK(tstate, mod_consts[132]);
        }

        assert(!(tmp_assattr_target_2 == NULL));
        tmp_result = SET_ATTRIBUTE(tstate, tmp_assattr_target_2, mod_consts[134], tmp_assattr_value_2);
        if (tmp_result == false) {
            assert(HAS_ERROR_OCCURRED(tstate));

            FETCH_ERROR_OCCURRED(tstate, &exception_type, &exception_value, &exception_tb);


            exception_lineno = 1;

            goto frame_exception_exit_1;
        }
    }


    // Put the previous frame back on top.
    popFrameStack(tstate);

    goto frame_no_exception_1;
    frame_exception_exit_1:


    if (exception_tb == NULL) {
        exception_tb = MAKE_TRACEBACK(frame_ebe3fc16cc6109fce68be05c0d37c541, exception_lineno);
    } else if (exception_tb->tb_frame != &frame_ebe3fc16cc6109fce68be05c0d37c541->m_frame) {
        exception_tb = ADD_TRACEBACK(exception_tb, frame_ebe3fc16cc6109fce68be05c0d37c541, exception_lineno);
    }



    assertFrameObject(frame_ebe3fc16cc6109fce68be05c0d37c541);

    // Put the previous frame back on top.
    popFrameStack(tstate);

    // Return the error.
    goto module_exception_exit;
    frame_no_exception_1:;
    {
        PyObject *tmp_assign_source_3;
        tmp_assign_source_3 = Py_None;
        UPDATE_STRING_DICT0(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[135], tmp_assign_source_3);
    }
    {
        PyObject *tmp_assign_source_4;
        tmp_assign_source_4 = mod_consts[136];
        UPDATE_STRING_DICT0(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[119], tmp_assign_source_4);
    }
    {
        PyObject *tmp_assign_source_5;
        tmp_assign_source_5 = mod_consts[137];
        UPDATE_STRING_DICT0(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[122], tmp_assign_source_5);
    }
    {
        PyObject *tmp_assign_source_6;
        tmp_assign_source_6 = mod_consts[138];
        UPDATE_STRING_DICT0(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[125], tmp_assign_source_6);
    }
    {
        PyObject *tmp_assign_source_7;
        tmp_assign_source_7 = mod_consts[139];
        UPDATE_STRING_DICT0(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[127], tmp_assign_source_7);
    }
    {
        PyObject *tmp_assign_source_8;


        tmp_assign_source_8 = MAKE_FUNCTION_pygments$plugin$$$function__1_iter_entry_points();

        UPDATE_STRING_DICT1(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[118], tmp_assign_source_8);
    }
    {
        PyObject *tmp_assign_source_9;


        tmp_assign_source_9 = MAKE_FUNCTION_pygments$plugin$$$function__2_find_plugin_lexers();

        UPDATE_STRING_DICT1(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[121], tmp_assign_source_9);
    }
    {
        PyObject *tmp_assign_source_10;


        tmp_assign_source_10 = MAKE_FUNCTION_pygments$plugin$$$function__3_find_plugin_formatters();

        UPDATE_STRING_DICT1(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[124], tmp_assign_source_10);
    }
    {
        PyObject *tmp_assign_source_11;


        tmp_assign_source_11 = MAKE_FUNCTION_pygments$plugin$$$function__4_find_plugin_styles();

        UPDATE_STRING_DICT1(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[126], tmp_assign_source_11);
    }
    {
        PyObject *tmp_assign_source_12;


        tmp_assign_source_12 = MAKE_FUNCTION_pygments$plugin$$$function__5_find_plugin_filters();

        UPDATE_STRING_DICT1(moduledict_pygments$plugin, (Nuitka_StringObject *)mod_consts[128], tmp_assign_source_12);
    }

    // Report to PGO about leaving the module without error.
    PGO_onModuleExit("pygments$plugin", false);

    Py_INCREF(module_pygments$plugin);
    return module_pygments$plugin;
    module_exception_exit:

#if defined(_NUITKA_MODULE) && 0
    {
        PyObject *module_name = GET_STRING_DICT_VALUE(moduledict_pygments$plugin, (Nuitka_StringObject *)const_str_plain___name__);

        if (module_name != NULL) {
            Nuitka_DelModule(tstate, module_name);
        }
    }
#endif
    PGO_onModuleExit("pygments$plugin", false);

    RESTORE_ERROR_OCCURRED(tstate, exception_type, exception_value, exception_tb);
    return NULL;
}
