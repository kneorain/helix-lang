import src.core.base as base
from src.core.imports import (
    os,
    datetime,
    Optional,
    Any
)

def inject_core(
    _cls_ref: Any,
    code: Optional[str] = None,
    is_main: bool = True,
    __version__: str = "NOT SET",
    __file__: str = "NOT SET",
) -> str:
    def get_all_importable_modules(
        path: str,
    ) -> list[str]:
        import inspect
        import importlib.util

        # Load the module specified by the path
        module_spec = (
            importlib.util.spec_from_file_location(
                "module.name", path
            )
        )
        if module_spec and module_spec.loader:
            module = importlib.util.module_from_spec(
                module_spec
            )
            module_spec.loader.exec_module(module)

            # Inspect the module and list all classes, functions, and variables
            importable_items = []
            for name, obj in inspect.getmembers(module):
                if (
                    inspect.isfunction(obj)
                    or inspect.isclass(obj)
                    or (not name.startswith("_"))
                ):
                    if not name.startswith("_H_"):
                        importable_items.append(name)
            return importable_items
        else:
            return (
                []
            )  # or raise an exception if the module can't be loaded
    back_slash = "\\"
    inject_code = f"""# trunk-ignore-all(black)
# trunk-ignore-all(isort)
# --------------------------------------------------------------------------------
#                                 GENERATED FILE
# --------------------------------------------------------------------------------
# Filename: {os.path.basename(_cls_ref.__file__)}
# Generation Date: {datetime.now().strftime("%Y-%m-%d %H:%M:%S")}
# Generator: Helix Transpiler
# --------------------------------------------------------------------------------
# WARNING: This file is AUTO-GENERATED by the Helix Transpiler. Any modifications
# made directly to this file may be OVERWRITTEN during future compilations. To
# introduce changes, please modify the source files and recompile.
# --------------------------------------------------------------------------------
# Licensed under the Creative Commons Attribution 4.0 International License (CC BY 4.0)
# SPDX-License-Identifier: CC-BY-4.0
# License Details: https://creativecommons.org/licenses/by/4.0/
#
# By using this file, you agree to the Terms and Conditions of the License.
# --------------------------------------------------------------------------------
# Helix Version: {__version__}
# Repository: https://github.com/kneorain/helix
# Documentation: https://kneorain.github.io/helix/
# For further assistance, contact the development team or refer to project documentation.
# --------------------------------------------------------------------------------
from __future__ import annotations # type: ignore

from beartype.door import is_bearable as is_typeof, is_subhint as is_sub_typeof # type: ignore
from beartype import beartype, BeartypeConf # type: ignore
###### from include.plum.plum import dispatch as overload_with_type_check

import os               # type: ignore
import sys              # type: ignore
import types            # type: ignore

sys.path.append(os.path.dirname(os.path.realpath(\"{__file__.replace(back_slash, os.sep+os.sep)}\")) + os.sep + ".helix")            # type: ignore
sys.path.append(os.path.dirname(os.path.realpath(\"{__file__.replace(back_slash, os.sep+os.sep)}\")))            # type: ignore
sys.path.append(os.path.dirname(os.path.realpath(os.getcwd())))                                     # type: ignore
# trunk-ignore(ruff/F401)
from include.core import {', '.join(get_all_importable_modules(os.path.join(".helix", "include", "core.py")))} # type: ignore
# trunk-ignore(ruff/F401)
# trunk-ignore(ruff/F811)
from include.core import __import_c__, __import_cpp__, __import_py__, __import_rs__                 # type: ignore

import threading  # type: ignore
import functools  # type: ignore

__exit__ = sys.exit
_lock = threading.Lock()
__file__ = "{os.path.realpath(_cls_ref.__file__).replace(back_slash, os.sep+os.sep)}"
# trunk-ignore(ruff/F821)
def exception_handler(exception_type: type[BaseException] | threading.ExceptHookArgs, exception: Optional[Exception] = None, tb: Optional[types.TracebackType] = None, debug_hook: bool = False, thread_error: bool = False):
    import traceback
    import linecache
    import os

    from include.core import _H_tokenize_line__
    from beartype.roar import BeartypeException
    
    print()

    thread_name = None
    if thread_error and exception_type is not None:
        thread_name = exception_type.thread.name  # type: ignore
        exception = exception_type.exc_value      # type: ignore
        tb = exception_type.exc_traceback         # type: ignore
        exception_type = exception_type.exc_type  # type: ignore

    stack = traceback.extract_tb(tb)
    stack = traceback.StackSummary([frame for frame in stack if not frame.filename.startswith("<@beartype(")])
    exception = TypeError(str(exception).replace("type hint", "type")) if isinstance(exception, BeartypeException) else exception
    current_exception = exception
    relevant_frames = []

    early_replacements = dict((v, k) for k, v in {base.EARLY_REPLACEMENTS}.items())

    # First loop: filter out irrelevant frames
    index = 0
    for frame in stack:
        filename = frame.filename
        line_no = frame.lineno
        if "_hlx" in os.path.basename(filename):
            filename = __file__
            try:
                line_no = int(open(frame.filename + ".lines", "r").readlines()[line_no-1]) # type: ignore
            except IndexError:
                print("TODO: approximate corresponding line number in .hlx file")
                panic(
                    LookupError(f"Could not find the corresponding line number in the .hlx file for the line {{frame.lineno}} in the generated file {{frame.filename}}. Please report this issue."),
                    line_no=1, # type: ignore
                    replacements=early_replacements,
                    thread_name=thread_name,
                    no_lines=True,
                    lang="py"
                )
            except FileNotFoundError:
                panic(
                    FileNotFoundError(f"The file {{frame.filename}} was not found. Please ensure that the file exists and is accessible."
                                      "You should never see this error. If you do, something went really wrong."),

                    line_no=1, # type: ignore
                    replacements=early_replacements,
                    thread_name=thread_name,
                    no_lines=True,
                    lang="py"
                )
                
            if line_no == -1:
                continue

            if line_no == -1:
                continue
        
        if ";#\\"\\"\\"REMOVE-STACK\\"\\"\\"#" in linecache.getline(filename, line_no).strip():
            continue
        
        if (
            linecache.getline(filename, line_no-1).strip() == "def hx_internal_multi_method_decorator(*args, **kwargs):" # type: ignore
            and
            linecache.getline(filename, line_no-3).strip() == "def hx__multi_method(func: Callable) -> Callable:" # type: ignore
        ):
            continue
            
        relevant_frames.append((index, frame))
        index += 1

    if len(relevant_frames) > 1:
        _lock.acquire(blocking=True, timeout=1.2)
        for frame_info in relevant_frames:
            index, frame = frame_info
            filename = frame.filename
            line_no = frame.lineno

            if "_hlx" in os.path.basename(filename):
                filename = __file__
                line_no = int(open(frame.filename + ".lines", "r").readlines()[line_no-1]) # type: ignore

            # Attempt to find the marked part in the error message
            # see if the frame contains colno and end_colno
            marks = None
            if hasattr(frame, "colno") and hasattr(frame, "end_colno"): # type: ignore
                marks = list(_H_tokenize_line__(frame._line[frame.colno:frame.end_colno])) # type: ignore
            try:
                file_ext =  os.path.basename(filename).split('.')[1] # type: ignore
            except IndexError:
                file_ext = "py"
            if marks:
                panic(
                    current_exception,  # type: ignore
                    *marks,
                    file=filename,
                    line_no=line_no,  # type: ignore
                    multi_frame=True,
                    pos=0 if index == 0 else 1 if index < len(relevant_frames) - 1 else 2,
                    replacements=early_replacements,
                    follow_marked_order=True,
                    mark_start=frame.colno,
                    thread_name=thread_name,
                    lang=file_ext
                )
            else:
                panic(
                    current_exception,  # type: ignore
                    file=filename,
                    line_no=line_no,  # type: ignore
                    replacements=early_replacements,
                    multi_frame=True,
                    pos=0 if index == 0 else 1 if index < len(relevant_frames) - 1 else 2,
                    thread_name=thread_name,
                    lang=file_ext
                )
            current_exception = current_exception.__cause__ if current_exception.__cause__ else current_exception  # type: ignore
        else:
            _lock.release()
            exit(1)
    else:
        _lock.acquire(blocking=True, timeout=0.1)
        index, frame = relevant_frames[0]
        filename = frame.filename
        line_no = frame.lineno

        if "_hlx" in filename:
            filename = __file__
            line_no = int(open(frame.filename + ".lines", "r").readlines()[line_no-1]) # type: ignore

        # Attempt to find the marked part in the error message
        # see if the frame contains colno and end_colno
        marks = None
        if hasattr(frame, "colno") and hasattr(frame, "end_colno"):
            marks = list(_H_tokenize_line__(frame._line[frame.colno:frame.end_colno])) # type: ignore

        try:
            file_ext =  os.path.basename(filename).split('.')[1]
        except IndexError:
            file_ext = "py"
        if marks:
            panic(
                current_exception, # type: ignore
                *marks,
                file=filename,
                line_no=line_no, # type: ignore
                replacements=early_replacements,
                follow_marked_order=True,
                mark_start=frame.colno,
                thread_name=thread_name,
                lang=file_ext
            )
        else:
            panic(
                current_exception, # type: ignore
                file=filename,
                line_no=line_no, # type: ignore
                replacements=early_replacements,
                thread_name=thread_name,
                lang=file_ext
            )

        _lock.release()
        exit(1)

sys.excepthook = exception_handler  # type: ignore
threading.excepthook = functools.partial(exception_handler, thread_error=True)
sys.argv = ["{os.path.realpath(__file__).replace(back_slash, os.sep+os.sep)}", "{os.path.realpath(_cls_ref.__file__).replace(back_slash, os.sep+os.sep)}"] + list(sys.argv)[2:]
del os, threading, functools
overload_with_type_check = beartype(conf=BeartypeConf(is_color=False))   # type: ignore

\x92

if __name__ == "__main__":
    try:
        main() # type: ignore
    except (KeyError, TypeError):
        main(sys.argv)
"""
    if not is_main:
        return inject_code.split("\x92")[0] + (
            code if code else "\x92"
        )

    if code is not None:
        return inject_code.replace("\x92", code)
    else:
        return inject_code
