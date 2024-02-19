# THIS TOOK ME 2 DAYS TO WRITE, I'M SO PROUD OF MYSELF
from classes.Token import Processed_Line, Token, Token_List
import classes.Transpiler as Transpiler
from core.cache_store import cache
from core.config import load_config
import globals
from classes.Scope import Scope

INDENT_CHAR = load_config().Formatter["indent_char"]
re = __import__(load_config().Transpiler["regex_module"])

from core.panic import panic

def _for(ast_list: Token_List, current_scope: Scope, parent_scope: Scope, root_scope: Scope, modifiers=None) -> str:
    output = ""

    if ";" in ast_list:
        # extract and process the 3 parts of the for loop
        init_statement      = ast_list.split(";")[0].splice(1)
        condition_statement = ast_list.split(";")[1]
        increment_statement = ast_list.split(";")[2]

        declarations: dict[str, dict[str, str]] = {}

        for_in_brackets = False
        if '(' == init_statement[0]:
            init_statement = init_statement.splice(1)
            for_in_brackets = True
        try:
            if ')' == increment_statement[-2] and for_in_brackets:
                increment_statement = increment_statement.splice(0, -2)
        except IndexError:
            panic(SyntaxError(f"Expected ')' at the end of the increment statement"), "{", file=ast_list.file, line_no=ast_list.find_line_number(increment_statement[-1]))

        if ':' not in init_statement and len(init_statement) > 1:
            panic(SyntaxError(f"Expected type declaration for variable in for loop"), init_statement.full_line(), file=ast_list.file, line_no=ast_list.find_line_number(init_statement[0]))

        @cache
        def process_init_statement(init_statement: Token_List) -> dict:
            processed_decls: dict[str, dict[str, str]] = {}
            stack:           list[str]                 = []

            current_var_name:    str  = ""
            current_var_type:    str  = ""
            current_var_value:   str  = ""
            current_var_unsafe:  bool = False
            current_var_discard: bool = True

            #TODO: add support for generics in loop declarations IF needed
            
            expecting_type:  bool = False
            expecting_value: bool = False
            excepting_name:  bool = False
            in_generic:      bool = False
            generic_count:   int  = 0

            @cache
            def extract_variables(index: int, token: Token) -> None:
                nonlocal current_var_name, in_generic, generic_count, current_var_type, current_var_value, current_var_unsafe, current_var_discard, expecting_type, expecting_value, excepting_name

                if token in [globals.find_keyword("LET"), globals.find_keyword("VAR"), globals.find_keyword("UNSAFE")]:
                    if expecting_value:
                        excepting_name = True
                        expecting_value = False
                        processed_decls[stack[-1]]["value"] = current_var_value.strip()[:-2]
                        current_var_value = ""

                    current_var_unsafe = token == globals.find_keyword("UNSAFE") or init_statement[index-1] == globals.find_keyword("UNSAFE")

                    current_var_discard = not (token == globals.find_keyword("LET"))
                    current_var_discard = not (token == globals.find_keyword("LET") or init_statement[index+1] == globals.find_keyword("LET"))

                    excepting_name = True
                    return

                if excepting_name:
                    if token == ",":
                        stack.append(current_var_name.strip())
                        processed_decls[current_var_name.strip()] = {
                            "type":    current_var_type.strip(),
                            "value":   current_var_value.strip(),
                            globals.find_keyword("UNSAFE"):  current_var_unsafe,
                            "discard": current_var_discard
                        }
                        current_var_name = ""
                        return
                    if token == ":": # var a : int
                        excepting_name = False
                        expecting_type = True
                        stack.append(current_var_name.strip())
                        processed_decls[current_var_name.strip()] = {
                            "type":    current_var_type.strip(),
                            "value":   current_var_value.strip(),
                            globals.find_keyword("UNSAFE"):  current_var_unsafe,
                            "discard": current_var_discard
                        }
                        current_var_name = ""
                        return
                    current_var_name += token.token + " "
                    return

                if expecting_type:
                    if in_generic:
                        if token == "<":
                            generic_count += 1
                        if token == ">":
                            generic_count -= 1
                            if generic_count == 0:
                                in_generic = False
                        return
                    
                    if token == "=":
                        expecting_value = True
                        expecting_type = False
                        for _name in stack:
                            processed_decls[_name] = {
                                "type":    processed_decls[_name]["type"] if processed_decls[_name]["type"] != '' else current_var_type.strip(),
                                "value":   processed_decls[_name]["value"] if processed_decls[_name]["value"] != '' else current_var_value.strip(),
                                globals.find_keyword("UNSAFE"):  processed_decls[_name][globals.find_keyword("UNSAFE")],
                                "discard": processed_decls[_name]["discard"]
                            } if processed_decls[_name]["type"] == "" and processed_decls[_name]["value"] == "" else processed_decls[_name]
                        current_var_type = ""
                        return
                    if token == ",":
                        excepting_name = True
                        expecting_type = False
                        processed_decls[stack[-1]] = {
                            "type":    current_var_type.strip(),
                            "value":   current_var_value.strip(),
                            globals.find_keyword("UNSAFE"):  current_var_unsafe,
                            "discard": current_var_discard
                        }
                        current_var_type = ""
                        return
                        
                    if token == "<":
                        in_generic = True
                        generic_count += 1
                        return

                    current_var_type += token.token + " "
                    return

                if expecting_value:
                    current_var_value += token.token + " "
                    return

            [extract_variables(index, token) for index, token in enumerate(init_statement)]

            if expecting_type:
                processed_decls[stack[-1]]["type"] = current_var_type.strip()
            if expecting_value:
                processed_decls[stack[-1]]["value"] = current_var_value.strip()

            def re_process_stack(_name: str, processed_decls: dict[str, dict[str, str]]) -> dict[str, dict[str, str]]:
                if processed_decls[_name]["value"] == "":
                    if processed_decls[_name]["type"].endswith("?"):
                        processed_decls[_name]["type"] = processed_decls[_name]["type"][:-1].strip()
                        processed_decls[_name]["value"] = f"{processed_decls[_name]["type"]}(None)"
                    elif processed_decls[_name]["type"] != "":
                        processed_decls[_name]["value"] = f"{processed_decls[_name]["type"]}()"
                    else:
                        # set the type to the type of the next non empty type
                        for __name in reversed(stack):
                            if processed_decls[__name]["type"] != "":
                                processed_decls[_name]["value"] = f"{processed_decls[__name]["type"]}()" if not processed_decls[__name]["type"].endswith("?") else f"{processed_decls[__name]["type"][:-1].strip()}(None)"
                                processed_decls[_name]["type"] = processed_decls[__name]["type"]
                                break
                else:
                    if processed_decls[_name]["type"].endswith("?"):
                        processed_decls[_name]["type"] = processed_decls[_name]["type"][:-1].strip()
                        processed_decls[_name]["value"] = f"{processed_decls[_name]["type"]}(None)" if processed_decls[_name]["value"] == "" else f"{processed_decls[_name]["type"]}({processed_decls[_name]['value']})"
                    elif processed_decls[_name]["type"] != "":
                        processed_decls[_name]["value"] = f"{processed_decls[_name]["type"]}({processed_decls[_name]['value']})"

            [re_process_stack(_name, processed_decls) for _name in stack]

            return processed_decls

        if len(init_statement) > 1 and init_statement[0].token in (globals.find_keyword("LET"), globals.find_keyword("VAR"), globals.find_keyword("UNSAFE")):
            declarations = process_init_statement(init_statement)
            # if any vars need to be discarded
            if any([declarations[_name]["discard"] for _name in declarations]):
                Transpiler.Transpiler.add_to_transpiled_queue.append((
                    f"{INDENT_CHAR*ast_list.indent_level}del {', '.join([f'{_name}' for _name in declarations if declarations[_name]['discard']])}\n",
                    current_scope
                ))
        elif len(init_statement) > 1:
            panic(SyntaxError(f"Expected 'let', 'var', or 'unsafe"), init_statement[0].token, file=ast_list.file, line_no=ast_list.find_line_number(init_statement[0]))

        # modifdify increment statement from 'i ++ , j ++' to 'i ++ ; j ++'
        # but it shouldn't jus replace the comma with a semicolon since there could be a comma in the increment statement itself (i.e. 'i += function_call(1, 2, 3) , j += 1') so it should only replace the comma with a semicolon if the comma is not inside a function call/brackets/square brackets/curly brackets
        @cache
        def replace_comma(increment_statement: str) -> str:
            # Stack to keep track of brackets
            bracket_stack: list[str] = []

            # List to hold the characters of the new increment statement
            new_statement: list[str] = []

            def process_brackets(char: str) -> str:
                nonlocal bracket_stack, new_statement
                # If the character is an opening bracket, push it onto the stack
                if char in "({[":
                    bracket_stack.append(char)

                # If the character is a closing bracket, pop from the stack
                elif char in ")}]":
                    if bracket_stack:
                        bracket_stack.pop()

                # If the character is a comma and we're not inside brackets, replace it
                elif char == ',' and not bracket_stack:
                    char = ';'

                # Add the character to the new statement
                new_statement.append(char)

            [process_brackets(char) for char in increment_statement]

            return ''.join(new_statement)[0:-1] if ''.join(new_statement).endswith(':') else ''.join(new_statement)

        increment_statement = replace_comma(increment_statement.full_line())
        output += "for " + ', '.join([f"{_name}" for _name in declarations]) + " in C_For(" + ', '.join([f"{_name} = {declarations[_name]['value']}" for _name in declarations]).strip() + ").set_con('" + condition_statement.full_line() + "').set_inc('" + increment_statement + "')" + ":"
        output = INDENT_CHAR*ast_list.indent_level + output
    else:
        # for (let i, var c in range(1, arr.len())) {
        # remove enclosing brackets
        ast_list = ast_list.splice(1, -1) # remove for
        if '(' == ast_list[0]:
            ast_list = ast_list.splice(1) # remove (
        if ')' == ast_list[-1]:
            ast_list = ast_list.splice(0, -1) # remove )

        init_statement      = ast_list.split("in")[0]
        condition_statement = ast_list.splice(len(init_statement) + 1)
        if ':' in init_statement:
            panic(SyntaxError(f"Unexpected ':' in declaration statement, can't specify type in a pythonic for loop."), ":", file=ast_list.file, line_no=ast_list.find_line_number(condition_statement[-1]))

        if '=' in init_statement:
            panic(SyntaxError(f"Unexpected '=' in declaration statement, can't specify value in a pythonic for loop."), "=", file=ast_list.file, line_no=ast_list.find_line_number(condition_statement[-1]))

        # all possiblites, no value allowed
        # let a, b
        # let a, let b
        # let a, var b
        # let a, unsafe b
        # let a, var b, unsafe c

        def process_init_statement(init_statement: Token_List) -> dict:
            processed_decls: dict[str, dict[str, str]] = {}
            stack:           list[str]                 = []

            current_var_name:    str  = ""
            current_var_unsafe:  bool = False
            current_var_discard: bool = True

            excepting_name:  bool = False

            @cache
            def extract_variables(index: int, token: Token) -> None:
                nonlocal current_var_name, current_var_unsafe, current_var_discard, excepting_name

                if token in [globals.find_keyword("LET"), globals.find_keyword("VAR"), globals.find_keyword("UNSAFE")]:
                    current_var_unsafe = token == globals.find_keyword("UNSAFE") or init_statement[index-1] == globals.find_keyword("UNSAFE")

                    current_var_discard = not (token == globals.find_keyword("LET"))
                    current_var_discard = not (token == globals.find_keyword("LET") or init_statement[index+1] == globals.find_keyword("LET"))

                    excepting_name = True
                    return

                if excepting_name:
                    if token == ",":
                        stack.append(current_var_name.strip())
                        processed_decls[current_var_name.strip()] = {
                            globals.find_keyword("UNSAFE"):  current_var_unsafe,
                            "discard": current_var_discard
                        }
                        current_var_name = ""
                        return

                    current_var_name += token.token + " "
                    return

            [extract_variables(index, token) for index, token in enumerate(init_statement)]

            if excepting_name:
                stack.append(current_var_name.strip())
                processed_decls[current_var_name.strip()] = {
                    globals.find_keyword("UNSAFE"):  current_var_unsafe,
                    "discard": current_var_discard
                }


            for _name in stack:
                processed_decls[_name] = {
                    globals.find_keyword("UNSAFE"):  processed_decls[_name][globals.find_keyword("UNSAFE")],
                    "discard": processed_decls[_name]["discard"]
                }

            return processed_decls

        try:
            declarations = process_init_statement(init_statement)
        except IndexError:
            panic(SyntaxError(f"Expected variable declaration in for loop"), "for", file=ast_list.file, line_no=ast_list.find_line_number(condition_statement[-1]))

        # if any vars need to be discarded
        if any([declarations[_name]["discard"] for _name in declarations]):
            Transpiler.Transpiler.add_to_transpiled_queue.append((
                f"{INDENT_CHAR*ast_list.indent_level}del {', '.join([f'{_name}' for _name in declarations if declarations[_name]['discard']])}\n",
                current_scope
            ))

        output += "for " + ', '.join([f"{_name}" for _name in declarations]) + " in " + condition_statement.full_line() + ":"
        output = INDENT_CHAR*ast_list.indent_level + output

    return Processed_Line(output, ast_list)