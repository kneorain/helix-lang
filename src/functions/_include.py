from typing import Optional
from src.core.imports import (
    Processed_Line,
    Token_List,
    panic,
    os,
    INDENT_CHAR,
    re,
)

def is_in_string(token: str) -> bool:
    return re.search(r"\".*?\"", token) or re.search(r"\'[a-zA-Z0-9]\'", token)

def identify_import_type(combined_line: str, ast_list: Token_List) -> dict:
    regex_patterns = {
        'only_path_with_alias_explicit': r'include\s+(?P<type>(?:C|CPP|PY|RS|HX|c|cpp|py|rs|helix))\s*\(\s*\"(?P<path>.*?)\"\s*\)\s+as\s+(?P<alias>\w+)',
        'only_path_with_alias':          r'include\s+\"(?P<path>.*?)\"\s+as\s+(?P<alias>\w+)',
        'only_module_and_path_explicit': r'include\s+\"(?P<modules>.*?)\"\s+from\s+(?P<type>(?:C|CPP|PY|RS|HX|c|cpp|py|rs|helix))\s*\(\s*\"(?P<path>.*?)\"\s*\)',
        'only_module_and_path':          r'include\s+\"(?P<modules>.*?)\"\s+from\s+\"(?P<path>.*?)\"',
        'only_path_no_alias_explicit':   r'include\s+(?P<type>(?:C|CPP|PY|RS|HX|c|cpp|py|rs|helix))\s*\(\s*\"(?P<path>.*?)\"\s*\)',
        'only_path_no_alias':            r'include\s+\"(?P<path>.*?)\"',
        'path_with_modules_explicit':    r'include\s+\((?P<modules>.*?)\)\s+from\s+(?P<type>(?:C|CPP|PY|RS|HX|c|cpp|py|rs|helix))\s*\(\s*\"(?P<path>.*?)\"\s*\)',
        'path_with_modules':             r'include\s+\((?P<modules>.*?)\)\s+from\s+\"(?P<path>.*?)\"',
        'path_with_namespace_explicit':  r'include\s+(?P<namespace>namespace)\s+(?P<type>(?:C|CPP|PY|RS|HX|c|cpp|py|rs|helix))\s*\(\s*\"(?P<path>.*?)\"\s*\)',
        'path_with_namespace':           r'include\s+(?P<namespace>namespace)\s+\"(?P<path>.*?)\"',
    }

    for regex in regex_patterns.values():
        match = re.match(regex, combined_line)
        if match:
            match = match.groupdict()
            if not match.get('type', ""):
                match["type"] = os.path.splitext(match["path"])[1][1:].upper()
            if not match.get('modules', ""):
                match["modules"] = False
            else:
                match["modules"] = [module.strip()[1:-1] for module in match["modules"].split(",")] if ',' in match["modules"] else [match["modules"]]
            if not match.get('alias', ""):
                match["alias"] = False
            if match.get('namespace', ""):
                match["type"] = f"{match['type']}_NAMESPACE"
                del match["namespace"]

            if not match.get('path', ""):
                panic(SyntaxError(f"Invalid include statement: {combined_line}"), file=ast_list.file, line_no=ast_list.line[0].line_number)

            match["type"] = match["type"].upper()
            return match
    panic(SyntaxError(f"Invalid include statement: {combined_line}"), file=ast_list.file, line_no=ast_list.line[0].line_number)
    return {}

def _include(ast_list: Token_List, current_scope, parent_scope, root_scope) -> Processed_Line:
    combined_line: str = ' '.join([_.token for _ in ast_list.line])
    match = identify_import_type(combined_line, ast_list)

    type: str            = match["type"]
    path: str            = match["path"]
    alias: Optional[str]           = match["alias"]
    alias = alias.strip() if alias else None
    modules: list[str]   = match["modules"]

    import_statement = ""
    if type == "C":
        if not alias and not modules:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}{os.path.splitext(path)[0].strip()} = __import_c__(\"{path}\")\n", ast_list)
        elif alias and modules and len(modules) == 1:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}{alias} = __import_c__(\"{path}\").{modules[0]}\n", ast_list)
        elif alias and modules and len(modules) > 1:
            panic(SyntaxError(f"Invalid include statement: {combined_line} cannot have multiple modules and an alias"), file=ast_list.file, line_no=ast_list.line[0].line_number)
        elif alias and not modules:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}{alias} = __import_c__(\"{path}\")\n", ast_list)
        elif not alias and modules and len(modules) == 1:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}{os.path.splitext(path)[0].strip()} = __import_c__(\"{path}\").{modules[0]}\n", ast_list)
        elif not alias and modules and len(modules) > 1:
            import_statement = f"{INDENT_CHAR*ast_list.line[0].indent_level}{os.path.splitext(path)[0].strip()} = __import_c__(\"{path}\")\n"
            for module in modules:
                import_statement += f"{INDENT_CHAR*ast_list.line[0].indent_level}{module.strip()} = {os.path.splitext(path)[0].strip()}.{module}\n"
            import_statement += f"{INDENT_CHAR*ast_list.line[0].indent_level}del {os.path.splitext(path)[0].strip()}\n"
            return Processed_Line(import_statement, ast_list)
        else:
            panic(SyntaxError(f"Invalid include statement: {combined_line}"), file=ast_list.file, line_no=ast_list.line[0].line_number)
    elif type == "CPP":
        if not alias and not modules:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}{os.path.splitext(path)[0].strip()} = __import_c__(\"{path}\")\n", ast_list)
        elif alias and modules and len(modules) == 1:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}{alias} = __import_c__(\"{path}\").{modules[0]}\n", ast_list)
        elif alias and modules and len(modules) > 1:
            panic(SyntaxError(f"Invalid include statement: {combined_line} cannot have multiple modules and an alias"), file=ast_list.file, line_no=ast_list.line[0].line_number)
        elif alias and not modules:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}{alias} = __import_c__(\"{path}\")\n", ast_list)
        elif not alias and modules and len(modules) == 1:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}{os.path.splitext(path)[0].strip()} = __import_c__(\"{path}\").{modules[0]}\n", ast_list)
        elif not alias and modules and len(modules) > 1:
            import_statement = f"{INDENT_CHAR*ast_list.line[0].indent_level}{os.path.splitext(path)[0].strip()} = __import_c__(\"{path}\")\n"
            for module in modules:
                import_statement += f"{INDENT_CHAR*ast_list.line[0].indent_level}{module} = {os.path.splitext(path)[0].strip()}.{module}\n"
            import_statement += f"{INDENT_CHAR*ast_list.line[0].indent_level}del {os.path.splitext(path)[0].strip()}\n"
            return Processed_Line(import_statement, ast_list)
        else:
            panic(SyntaxError(f"Invalid include statement: {combined_line}"), file=ast_list.file, line_no=ast_list.line[0].line_number)

    elif type == "PY":
        if not alias and not modules:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}import {path}\n", ast_list)
        elif alias and not modules:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}import {path} as {alias}\n", ast_list)
        elif alias and modules and len(modules) == 1:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}from {path} import {modules[0]} as {alias}\n", ast_list)
        elif not alias and modules and len(modules) > 1:
            import_statement = f"{INDENT_CHAR*ast_list.line[0].indent_level}from {path} import {', '.join(modules)}\n"
            return Processed_Line(import_statement, ast_list)
        else:
            panic(SyntaxError(f"Invalid include statement: {combined_line}"), file=ast_list.file, line_no=ast_list.line[0].line_number)
    elif type == "RS":
        if not alias and not modules:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}{os.path.splitext(path)[0].strip()} = __rs_import__(\"{path}\")\n", ast_list)
        elif alias and not modules:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}{alias} = __rs_import__(\"{path}\")\n", ast_list)
        elif alias and modules and len(modules) == 1:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}{alias} = __rs_import__(\"{path}\").{modules[0]}\n", ast_list)
        elif alias and modules and len(modules) > 1:
            panic(SyntaxError(f"Invalid include statement: {combined_line} cannot have multiple modules and an alias"), file=ast_list.file, line_no=ast_list.line[0].line_number)
        elif not alias and modules and len(modules) == 1:
            return Processed_Line(f"{INDENT_CHAR*ast_list.line[0].indent_level}{os.path.splitext(path)[0].strip()} = __rs_import__(\"{path}\").{modules[0]}\n", ast_list)
        elif not alias and modules and len(modules) > 1:
            import_statement = f"{INDENT_CHAR*ast_list.line[0].indent_level}{os.path.splitext(path)[0].strip()} = __rs_import__(\"{path}\")\n"
            for module in modules:
                import_statement += f"{INDENT_CHAR*ast_list.line[0].indent_level}{module} = {os.path.splitext(path)[0].strip()}.{module}\n"
            import_statement += f"{INDENT_CHAR*ast_list.line[0].indent_level}del {os.path.splitext(path)[0].strip()}\n"
            return Processed_Line(import_statement, ast_list)
        else:
            panic(SyntaxError(f"Invalid include statement: {combined_line}"), file=ast_list.file, line_no=ast_list.line[0].line_number)
    elif type == "HX":
        panic(SyntaxError(f"importing namespace \"{path}\" is not supported"), file=ast_list.file, line_no=ast_list.line[0].line_number)

    return Processed_Line(import_statement, ast_list)


"""
include "test.c"
include "test.cpp"
include "test.rs"
include "test.hx"
include C ( "test.c" )
include CPP ( "test.cpp" )
include PY ( "numpy" )
include RS ( "test.rs" )
include HX ( "test.hx" )

include "test.c" as add
include "test.cpp" as add
include "test.rs" as add
include "test.hx" as add
include C ( "test.c" ) as add
include CPP ( "test.cpp" ) as add
include PY ( "numpy" ) as add
include RS ( "test.rs" ) as add
include HX ( "test.hx" ) as add

include "add" from "test.c"
include "add" from "test.cpp"
include "test" from PY("numpy")
include "test" from "test.rs"
include "test" from "test.hx"
include "add" from C("test.c")
include "add" from CPP("test.cpp")
include "test" from RS("test.rs")
include "test" from HX("test.hx")

include ( "add", "sub" ) from "test.c"
include ( "add", "sub" ) from "test.cpp"
include ( "test", "sub" ) from PY("numpy")
include ( "test", "sub" ) from "test.rs"
include ( "test", "sub" ) from "test.hx"
include ( "add", "sub" ) from C("test.c")
include ( "add", "sub" ) from CPP("test.cpp")
include ( "test", "sub" ) from RS("test.rs")
include ( "test", "sub" ) from HX("test.hx")

include namespace "test.hx"
include namespace HX("test.hx")

All of the following are valid include statements:
1. single module no alias and yes path:
    tokens from ast.line could be ["include", "\"add\"",  "from", "\"test.c\""] the following fields are: modules = ["add"], module_path = "test.c", module_alias = "", module_type = "C",
    tokens from ast.line could be ["include", "\"add\"",  "from", "C", "(", "\"test.c\"", ")"] the following fields are: modules = ["add"], module_path = "test.c", module_alias = "", module_type = "C",
    tokens from ast.line could be ["include", "\"add\"",  "from", "\"test.cpp\""] the following fields are: modules = ["add"], module_path = "test.cpp", module_alias = "", module_type = "CPP",
    tokens from ast.line could be ["include", "\"add\"",  "from", "CPP", "(", "\"test.c\"", ")"] the following fields are: modules = ["add"], module_path = "test.c", module_alias = "", module_type = "CPP",
    tokens from ast.line could be ["include", "\"test\"", "from", "PY", "(", "\"numpy\"", ")"] the following fields are: modules = ["test"], module_path = "numpy", module_alias = "", module_type = "PY",
    tokens from ast.line could be ["include", "\"test\"", "from", "\"test.rs\""] the following fields are: modules = ["test"], module_path = "test.rs", module_alias = "", module_type = "RS",
    tokens from ast.line could be ["include", "\"test\"", "from", "RS", "(", "\"test.rs\"", ")"] the following fields are: modules = ["test"], module_path = "test.rs", module_alias = "", module_type = "RS"

2. only a path and an alias (C, CPP, PY, RS):
    tokens from ast.line could be ["include", "\"test.c\"", "as", "add"] the following fields are: modules = [], module_path = "test.c", module_alias = "add", module_type = "C",
    tokens from ast.line could be ["include", "C", "(", "\"test.c\"", ")", "as", "add"] the following fields are: modules = [], module_path = "test.c", module_alias = "add", module_type = "C",
    tokens from ast.line could be ["include", "\"test.cpp\"", "as", "add"] the following fields are: modules = [], module_path = "test.cpp", module_alias = "add", module_type = "CPP",
    tokens from ast.line could be ["include", "CPP", "(", "\"test.c\"", ")", "as", "add"] the following fields are: modules = [], module_path = "test.c", module_alias = "add", module_type = "CPP",
    tokens from ast.line could be ["include", "PY", "(", "\"numpy\"", ")", "as", "add"] the following fields are: modules = [], module_path = "numpy", module_alias = "add", module_type = "PY",
    tokens from ast.line could be ["include", "\"test.rs\"", "as", "add"] the following fields are: modules = [], module_path = "test.rs", module_alias = "add", module_type = "RS",
    tokens from ast.line could be ["include", "RS", "(", "\"test.rs\"", ")", "as", "add"] the following fields are: modules = [], module_path = "test.rs", module_alias = "add", module_type = "RS"

3. only a path and no alias (C, CPP, PY, RS):
    tokens from ast.line could be ["include", "\"test.c\""] the following fields are: modules = [], module_path = "test.c", module_alias = "", module_type = "C",
    tokens from ast.line could be ["include", "C", "(", "\"test.c\"", ")"] the following fields are: modules = [], module_path = "test.c", module_alias = "", module_type = "C",
    tokens from ast.line could be ["include", "\"test.cpp\""] the following fields are: modules = [], module_path = "test.cpp", module_alias = "", module_type = "CPP",
    tokens from ast.line could be ["include", "CPP", "(", "\"test.c\"", ")"] the following fields are: modules = [], module_path = "test.c", module_alias = "", module_type = "CPP",
    tokens from ast.line could be ["include", "PY", "(", "\"numpy\"", ")"] the following fields are: modules = [], module_path = "numpy", module_alias = "", module_type = "PY",
    tokens from ast.line could be ["include", "\"test.rs\""] the following fields are: modules = [], module_path = "test.rs", module_alias = "", module_type = "RS",
    tokens from ast.line could be ["include", "RS", "(", "\"test.rs\"", ")"] the following fields are: modules = [], module_path = "test.rs", module_alias = "", module_type = "RS"
    tokens from ast.line could be ["include", "\"test.hx\""] the following fields are: modules = [], module_path = "test.hx", module_alias = "", module_type = "HX",

4. multiple modules no alias and yes path:
    tokens from ast.line could be ["include", "(", "\"add\"",  ",", "sub", ")", "from", "\"test.c\""] the following fields are: modules = ["add", "sub"], module_path = "test.c", module_alias = "", module_type = "C",
    tokens from ast.line could be ["include", "(", "\"add\"",  ",", "sub", ")", "from", "C", "(", "\"test.c\"", ")"] the following fields are: modules = ["add", "sub"], module_path = "test.c", module_alias = "", module_type = "C",
    tokens from ast.line could be ["include", "(", "\"add\"",  ",", "sub", ")", "from", "\"test.cpp\""] the following fields are: modules = ["add", "sub"], module_path = "test.cpp", module_alias = "", module_type = "CPP",
    tokens from ast.line could be ["include", "(", "\"add\"",  ",", "sub", ")", "from", "CPP", "(", "\"test.c\"", ")"] the following fields are: modules = ["add", "sub"], module_path = "test.c", module_alias = "", module_type = "CPP",
    tokens from ast.line could be ["include", "(", "\"test\"", ",", "sub", ")", "from", "PY", "(", "\"numpy\"", ")"] the following fields are: modules = ["test", "sub"], module_path = "numpy", module_alias = "", module_type = "PY",
    tokens from ast.line could be ["include", "(", "\"test\"", ",", "sub", ")", "from", "\"test.rs\""] the following fields are: modules = ["test", "sub"], module_path = "test.rs", module_alias = "", module_type = "RS",
    tokens from ast.line could be ["include", "(", "\"test\"", ",", "sub", ")", "from", "RS", "(", "\"test.rs\"", ")"] the following fields are: modules = ["test", "sub"], module_path = "test.rs", module_alias = "", module_type = "RS"

5. only a path and namespace:
    tokens from ast.line could be ["include", "namespace", "\"test.hx\""]
    tokens from ast.line could be ["include", "namespace", "HX(\"test.hx\")"]

Output for each:
1.
    C: {IDENT_CHAR*line.indent_level}test_c = __c_cpp_import__("test.c")\n{IDENT_CHAR*line.indent_level}add = test_c.add\n{IDENT_CHAR*line.indent_level}del test_c
    CPP: {IDENT_CHAR*line.indent_level}test_cpp = __c_cpp_import__("test.cpp")\n{IDENT_CHAR*line.indent_level}add = test_cpp.add\n{IDENT_CHAR*line.indent_level}del test_cpp
    PY: {IDENT_CHAR*line.indent_level}from numpy import test
    RS: {IDENT_CHAR*line.indent_level}test_rs = __rs_import__("test.rs")\n{IDENT_CHAR*line.indent_level}add = test_rs.add\n{IDENT_CHAR*line.indent_level}del test_rs

2.
    C: {IDENT_CHAR*line.indent_level}add = __c_cpp_import__("test.c")
    CPP: {IDENT_CHAR*line.indent_level}add = __c_cpp_import__("test.cpp")
    PY: {IDENT_CHAR*line.indent_level}import numpy as add
    RS: {IDENT_CHAR*line.indent_level}add = __rs_import__("test.rs")

3.
    C: {IDENT_CHAR*line.indent_level}test = __c_cpp_import__("test.c")
    CPP: {IDENT_CHAR*line.indent_level}test = __c_cpp_import__("test.cpp")
    PY: {IDENT_CHAR*line.indent_level}import numpy
    RS: {IDENT_CHAR*line.indent_level}test = __rs_import__("test.rs")

4.
    C: {IDENT_CHAR*line.indent_level}test_c = __c_cpp_import__("test.c")\n{IDENT_CHAR*line.indent_level}add = test_c.add\n{IDENT_CHAR*line.indent_level}sub = test_c.sub\n{IDENT_CHAR*line.indent_level}del test_c
    CPP: {IDENT_CHAR*line.indent_level}test_cpp = __c_cpp_import__("test.cpp")\n{IDENT_CHAR*line.indent_level}add = test_cpp.add\n{IDENT_CHAR*line.indent_level}sub = test_cpp.sub\n{IDENT_CHAR*line.indent_level}del test_cpp
    PY: {IDENT_CHAR*line.indent_level}from numpy import test, sub
    RS: {IDENT_CHAR*line.indent_level}test_rs = __rs_import__("test.rs")\n{IDENT_CHAR*line.indent_level}add = test_rs.add\n{IDENT_CHAR*line.indent_level}sub = test_rs.sub\n{IDENT_CHAR*line.indent_level}del test_rs

5.
    HX: print("importing namespace test.hx is not supported")
"""




"""
importing a C or C++ file:
runs command: gcc -shared -o /tmp/.helix/gcc/test.so test.c
becomes:
from ctypes import cdll
test_c = cdll.LoadLibrary("/Volumes/Container/OPSECQUIZ/libmylib.so")
add = test_c.add
"""