import src.core.core as core
from src.core.imports import (
    Processed_Line,
    Token_List,
    Token,
    map,
    Scope,
    _class,
    INDENT_CHAR,
    Optional,
    framework,
)

replace_function_name: map[str, str] = map(
    {
        "=="    : "__eq__",
        "!="    : "__ne__",
        "<"     : "__lt__",
        "<="    : "__le__",
        ">"     : "__gt__",
        ">="    : "__ge__",
        "+"     : "__add__",
        "-"     : "__sub__",
        "*"     : "__mul__",
        "/"     : "__truediv__",
        "//"    : "__floordiv__",
        "%"     : "__mod__",
        "**"    : "__pow__",
        "<<"    : "__lshift__",
        ">>"    : "__rshift__",
        "&"     : "__and__",
        "|"     : "__or__",
        "^"     : "__xor__",
        "~"     : "__invert__",
        "@"     : "__matmul__",
        "r+"    : "__radd__",
        "r-"    : "__rsub__",
        "r*"    : "__rmul__",
        "r/"    : "__rtruediv__",
        "r//"   : "__rfloordiv__",
        "r%"    : "__rmod__",
        "r**"   : "__rpow__",
        "r<<"   : "__rlshift__",
        "r>>"   : "__rrshift__",
        "r&"    : "__rand__",
        "r|"    : "__ror__",
        "r^"    : "__rxor__",
        "+="    : "__iadd__",
        "-="    : "__isub__",
        "*="    : "__imul__",
        "/="    : "__itruediv__",
        "//="   : "__ifloordiv__",
        "%="    : "__imod__",
        "**="   : "__ipow__",
        "<<="   : "__ilshift__",
        ">>="   : "__irshift__",
        "&="    : "__iand__",
        "|="    : "__ior__",
        "^="    : "__ixor__",
    }
)


class ExtractTypedParamsFromFunc(framework.Translate):
    allowed_untyped = ("self", "cls", "super")

    def __init__(
        self, ast_line: Token_List, root_scope: Scope
    ):
        self.line_copy: Token_List = ast_line.copy()
        self.generic: str = ""
        self.in_param: bool = False
        self.generic_count: int = 0
        self.in_generic: bool = False
        self.root_scope: Scope = root_scope
        self.ast_line: Token_List = ast_line
        self.return_type: Optional[str] = None
        self.line: list[Token] = ast_line.line[2:]
        self.variables: dict[str, dict[str, str]] = {}
        self.params: Optional[dict[str, dict[str, str]]] = (
            None
        )

    def parse(
        self,
    ) -> dict[
        str, Optional[str] | dict[str, dict[str, str]]
    ]:
        token: str = self.line[0].token

        if token == "(" and self.line[1].token == ")":
            return self.handle_no_parameters()
        elif token == "(":
            self.in_param = True
            self.line = self.line[1:]
        else:
            core.ERROR_CODES.SYNTAX_MISSING_EXCEPTED_TOKEN.format(
                token="("
            ).panic(
                ")",
                file=self.ast_line.file,
                line_no=self.ast_line.find_line_number(
                    self.root_scope.get_keyword("FUNCTION")
                ),
            )

        while self.in_param and self.line:
            token = self.line[0].token

            if token == ")":
                del token
                return self.handle_end_of_parameters()
            elif token == "<":
                self.handle_generic_start()
            elif token == ">":
                self.handle_generic_end()
            elif self.in_generic:
                self.handle_generic_content()
            elif token == ",":
                self.line = self.line[1:]
            else:
                self.handle_parameter()
        
        del token
        self.__del__()
        raise SyntaxError(
            f"<Hex(02.E3)>: Expected a closing parenthesis after the parameters"
        )

    def handle_end_of_parameters(
        self,
    ) -> dict[
        str, Optional[str | dict[str, dict[str, str]]]
    ]:
        if self.line[1].token == "->":
            # no parameters, just a return type
            if (
                self.line[2].token == ":"
                or self.line[2].token == "<\\r1>"
            ):
                core.ERROR_CODES.SYNTAX_MISSING_EXCEPTED_TOKEN.format(
                    token="->"
                ).panic(
                    "->",
                    file=self.ast_line.file,
                    line_no=self.ast_line.find_line_number(
                        self.root_scope.get_keyword(
                            "FUNCTION"
                        )
                    ),
                )
            return {
                "return_type": self.line[2].token,
                "params": self.variables,
            }
        else:
            # no parameters, no return type
            if (
                self.line[1].token != ":"
                and self.line[1].token != "<\\r1>"
            ):
                core.ERROR_CODES.SYNTAX_MISSING_EXCEPTED_TOKEN.format(
                    token="{}"
                ).panic(
                    "fn",
                    file=self.ast_line.file,
                    line_no=self.ast_line.find_line_number(
                        self.root_scope.get_keyword(
                            "FUNCTION"
                        )
                    ),
                )
            return {
                "return_type": None,
                "params": self.variables,
            }

    def handle_generic_start(self) -> None:
        self.generic_count += 1
        self.in_generic = True
        self.generic += "[" + " "
        self.line = self.line[1:]

    def handle_generic_end(self) -> None:
        self.generic_count -= 1
        self.in_generic = self.generic_count > 0
        self.generic += " " + "]"

        if not self.in_generic:
            self.variables[
                tuple(self.variables.keys())[-1]
            ]["type"] += self.generic
            self.generic = ""
            self.line = self.line[1:]

    def handle_generic_content(self) -> None:
        self.generic += self.line[0].token
        self.line = self.line[1:]

    def handle_parameter(self) -> None:
        token: str = self.line[0].token

        if self.line[1].token == ":":
            self.variables[token] = {
                "type": self.line[2].token
            }
            self.line = self.line[3:]
        else:
            if token == "=":
                core.ERROR_CODES.SYNTAX_UNSUPPORTED_SYNTAX.format(
                    syntax="="
                ).panic(
                    token,
                    file=self.ast_line.file,
                    line_no=self.ast_line.find_line_number(
                        self.root_scope.get_keyword(
                            "FUNCTION"
                        )
                    ),
                )
            if token in self.allowed_untyped:
                self.variables[token] = {"type": "Any"}
                self.line = self.line[1:]
            else:
                del token
                core.ERROR_CODES.TYPE_UNDECLARED.format(
                    identifier=tuple(self.variables.keys())[
                        -1
                    ]
                ).panic(
                    tuple(self.variables.keys())[-1],
                    file=self.ast_line.file,
                    line_no=self.ast_line.find_line_number(
                        self.root_scope.get_keyword(
                            "FUNCTION"
                        )
                    ),
                )

        del token
    
    def __del__(self) -> None:
        del self.line
        del self.in_param
        del self.variables
        del self.generic
        del self.in_generic
        del self.generic_count
        del self.root_scope
        del self.ast_line
    
    def handle_no_parameters(
        self,
    ) -> dict[
        str, Optional[str] | dict[str, dict[str, str]]
    ]:
        if self.line[2].token == "->":
            # no parameters, just a return type
            if (
                self.line[3].token == ":"
                or self.line[3].token == "<\\r1>"
            ):
                core.ERROR_CODES.SYNTAX_MISSING_EXCEPTED_TOKEN.format(
                    token="->"
                ).panic(
                    "->",
                    file=self.ast_line.file,
                    line_no=self.ast_line.line[
                        0
                    ].line_number,
                )
            return {
                "return_type": self.line[3].token,
                "params": {},
            }
        else:
            # no parameters, no return type
            if (
                self.line[2].token != ":"
                and self.line[2].token != "<\\r1>"
            ):
                core.ERROR_CODES.SYNTAX_MISSING_EXCEPTED_TOKEN.format(
                    token="{}"
                ).panic(
                    "fn",
                    file=self.ast_line.file,
                    line_no=self.ast_line.line[
                        0
                    ].line_number,
                )
            return {"return_type": None, "params": {}}


class Function(framework.Translate):
    def __init__(
        self,
        ast_list: Token_List,
        current_scope: Scope,
        parent_scope: Scope,
        root_scope: Scope,
    ):
        self.ast_list: Token_List = ast_list
        self.current_scope: Scope = current_scope
        self.parent_scope: Scope = parent_scope
        self.root_scope: Scope = root_scope
        self.decorators: list[str] = []
        self.modifiers: dict[str, bool] = {}
        self.not_allowed_classes: tuple[str, ...] = (
            parent_scope.get_keyword("CLASS"),
            parent_scope.get_keyword("INTERFACE"),
            parent_scope.get_keyword("STRUCT"),
            parent_scope.get_keyword("UNION"),
            parent_scope.get_keyword("ENUM"),
            parent_scope.get_keyword("ABSTRACT"),
            parent_scope.get_keyword("UNSAFE"),
        )

        self.variables: dict[
            str, str | dict[str, dict[str, str]] | None
        ] = {}
        
        self.name: str = ""
        self.output: str = ""
    
    def parse(self) -> Processed_Line:
        self._process_decorators()
        self._process_modifiers()

        if self.ast_list.line[
            0
        ].token != self.root_scope.get_keyword("FUNCTION"):
            self._handle_non_function()

        self.variables = ExtractTypedParamsFromFunc(
            self.ast_list, self.root_scope
        ).parse()
        self._process_name()
        self.add_to_output(
            f"def {self.name}("
            if self.name not in self.parent_scope.functions
            else f"def _("
        )

        self._process_params()
        self._process_return_type()
        self.add_to_output(
            self.__add_indent(self.output), 2
        )

        if any(
            [
                i == self.root_scope.get_keyword("ABSTRACT")
                for i in self.parent_scope.name
            ]
        ) or any(
            [
                i
                == self.root_scope.get_keyword("INTERFACE")
                for i in self.parent_scope.name
            ]
        ):
            self.decorators.append("@hx__abstract_method")

        self._process_modifiers_step_2()

        self.parent_scope.functions[self.name] = {
            "type": self.variables["return_type"],
            "params": self.variables["params"],
            self.root_scope.get_keyword(
                "STATIC"
            ): self.modifiers.get(
                self.root_scope.get_keyword("STATIC"), False
            ),
            self.root_scope.get_keyword(
                "ASYNC"
            ): self.modifiers.get(
                self.root_scope.get_keyword("ASYNC"), False
            ),
            self.root_scope.get_keyword(
                "PRIVATE"
            ): self.modifiers.get(
                self.root_scope.get_keyword("PRIVATE"),
                False,
            ),
            self.root_scope.get_keyword(
                "UNSAFE"
            ): self.modifiers.get(
                self.root_scope.get_keyword("UNSAFE"), False
            ),
            self.root_scope.get_keyword(
                "FINAL"
            ): self.modifiers.get(
                self.root_scope.get_keyword("FINAL"), False
            ),
        }

        if "unknown" in self.output:
            self.output = self.output

        (
            self.decorators.append(
                "@overload_with_type_check"
            )
            if (
                not self.modifiers.get(
                    self.root_scope.get_keyword("ASYNC"),
                    False,
                )
            )
            else (None)
        )

        decorators: str = ""
        if self.decorators:
            for _, decorator in enumerate(
                reversed(self.decorators)
            ):
                decorators += self.__add_indent(decorator)

        self.add_to_output(
            self.__add_indent(
                self.output.replace(
                    "unknown", "Any"
                ).strip()
            ),
            2,
        )
        self.add_to_output(decorators, 1)
        
        return self._return_output()

    def add_to_output(
        self, output: str, side: int = 0
    ) -> None:
        if side == 0:
            self.output += output
        elif side == 1:
            self.output = output + self.output
        else:
            self.output = output

    def _process_decorators(self) -> None:
        if self.ast_list.line[0].token == "#":
            for _ in range(self.ast_list.count("#")):
                decorator = self.ast_list.get_between(
                    "[", "]"
                )
                self.ast_list.line = self.ast_list.line[
                    len(decorator) + 3 :
                ]
                self.decorators.append(
                    "@"
                    + " ".join(
                        [__.token for __ in decorator]
                    )
                )
            del decorator
            del _
                

    def _process_modifiers(self) -> None:
        self.modifiers = {
            self.root_scope.get_keyword("ASYNC"): False,
            self.root_scope.get_keyword("PRIVATE"): False,
            self.root_scope.get_keyword("PROTECTED"): False,
            self.root_scope.get_keyword("FINAL"): False,
            self.root_scope.get_keyword("UNSAFE"): False,
            self.root_scope.get_keyword("STATIC"): False,
        } # TODO: add virtual/kernel
        index = 0

        if self.ast_list.line[
            0
        ].token != self.root_scope.get_keyword("FUNCTION"):
            line = self.ast_list.line.copy()
            while line:
                index += 1
                if line[0].token in self.modifiers.keys():
                    self.modifiers[line[0].token] = True
                    line = line[1:]
                else:
                    if line[
                        0
                    ].token != self.root_scope.get_keyword(
                        "FUNCTION"
                    ):
                        break
                    else:
                        break
            
            del line
            
            self.ast_list.line = self.ast_list.line[
                (index - 1) :
            ]

        del index
    def _process_name(self) -> None:
        self.name = self.ast_list.line[1].token

        if self.name in replace_function_name:
            if not any(
                [
                    i in self.not_allowed_classes
                    for i in self.parent_scope.name
                ]
            ):
                core.ERROR_CODES.OPERATOR_OVERLOADING_OUTSIDE_CLASS.panic(
                    self.name,
                    file=self.ast_list.file,
                    line_no=self.ast_list.find_line_number(
                        self.name
                    ),
                )
            self.name = replace_function_name[self.name]

    def _handle_non_function(self) -> Processed_Line:
        if (
            self.ast_list.line[0].token
            in self.not_allowed_classes
        ):
            return _class(
                self.ast_list.splice(len(self.modifiers)),
                self.current_scope,
                self.parent_scope,
                self.root_scope,
                self.modifiers,
            )

        core.ERROR_CODES.SYNTAX_MISSING_EXCEPTED_TOKEN.format(
            token=self.root_scope.get_keyword("FUNCTION")
        ).panic(
            self.ast_list[1].token,
            file=self.ast_list.file,
            line_no=self.ast_list[0].line_number,
        )

    def _process_params(self) -> None:
        if not self.variables["params"]:
            self.add_to_output(")")
        else:
            self._process_params_internal()
            self.add_to_output(self.output[:-2] + ")", 2)

    def _process_params_internal(self):
        if not self.variables["params"]:
            raise ValueError(
                "The variable type is not a dictionary"
            )
        if not isinstance(self.variables["params"], dict):
            raise ValueError(
                "The variable type is not a dictionary"
            )

        for k, v in self.variables["params"].items():
            if v["type"] == "void":
                core.ERROR_CODES.TYPE_INVALID_TYPE_IN_CONTEXT.format(
                    type="void"
                ).panic(
                    "void",
                    file=self.ast_list.file,
                    line_no=self.ast_list.find_line_number(
                        k
                    ),
                )
            self.add_to_output(
                f"{k}: {core.replace_primitive(v['type'], 0)}, "
            )
            self.current_scope.variables[k] = v["type"]
        
        del k, v

    def __add_indent(
        self, output: str, offset: int = 0
    ) -> str:
        return f"\n{INDENT_CHAR*(self.ast_list.indent_level+offset)}{output}"

    def _process_return_type(self) -> None:
        if (
            self.ast_list.line[-1].token == "<\\r1>"
            and self.ast_list.indent_level == 0
        ):
            core.ERROR_CODES.SYNTAX_INVALID_SYNTAX.format(
                location="noop function at the global scope is not allowed, "
                         "use {...} to create an empty block function",
            ).panic(
                "fn",
                file=self.ast_list.file,
                line_no=self.ast_list.find_line_number(
                    self.name
                ),
            )

        if self.variables["return_type"]:
            self.add_to_output(
                f" -> {self.variables['return_type']}:"
                if self.ast_list.line[-1].token != "<\\r1>"
                else f" -> {self.variables['return_type']}:"
                     f"{self.__add_indent('pass', 1)}"
            )
        else:
            self.add_to_output(
                ":"
                if self.ast_list.line[-1].token != "<\\r1>"
                else f":{self.__add_indent('pass', 1)}"
            )

    def _process_modifiers_step_2(self) -> None:
        if self.modifiers[
            self.root_scope.get_keyword("STATIC")
        ]:
            if not any(
                [
                    i in self.not_allowed_classes
                    for i in self.parent_scope.name
                ]
            ):
                core.ERROR_CODES.FUNCTION_INVALID_MODIFIERS.format(
                    modifiers="static",
                ).panic(
                    self.root_scope.get_keyword("STATIC"),
                    file=self.ast_list.file,
                    line_no=self.ast_list.line[
                        0
                    ].line_number,
                )

            self.decorators.append(f"@staticmethod")

        if self.modifiers[
            self.root_scope.get_keyword("ASYNC")
        ]:
            self.decorators.append(f"@hx__async")

        if self.modifiers[
            self.root_scope.get_keyword("PRIVATE")
        ]:
            # TODO: ADD A DECORATOR FOR PRIVATE TO MARK THE TYPE OF THE FUNCTION AS PRIVATE
            self.modifiers[
                self.root_scope.get_keyword("PRIVATE")
            ] = True

        if self.modifiers[
            self.root_scope.get_keyword("FINAL")
        ]:
            self.decorators.append(f"@final")

        if self.modifiers[
            self.root_scope.get_keyword("UNSAFE")
        ]:
            # TODO: ADD A DECORATOR FOR UNSAFE TO MARK THE TYPE OF THE FUNCTION AS UNSAFE
            self.modifiers[
                self.root_scope.get_keyword("UNSAFE")
            ] = True

        if (
            self.modifiers[
                self.root_scope.get_keyword("PRIVATE")
            ]
            and self.modifiers[
                self.root_scope.get_keyword("STATIC")
            ]
        ):
            core.ERROR_CODES.FUNCTION_INVALID_MODIFIERS.format(
                modifiers="private and static",
            ).panic(
                self.root_scope.get_keyword("PRIVATE"),
                self.root_scope.get_keyword("STATIC"),
                file=self.ast_list.file,
                line_no=self.ast_list.line[0].line_number,
            )

        if (
            self.modifiers[
                self.root_scope.get_keyword("ASYNC")
            ]
            and self.modifiers[
                self.root_scope.get_keyword("UNSAFE")
            ]
        ):
            core.ERROR_CODES.FUNCTION_INVALID_MODIFIERS.format(
                modifiers="async and unsafe",
            ).panic(
                self.root_scope.get_keyword("ASYNC"),
                self.root_scope.get_keyword("UNSAFE"),
                file=self.ast_list.file,
                line_no=self.ast_list.find_line_number(
                    self.root_scope.get_keyword("STATIC")
                ),
            )

    def _return_output(self) -> Processed_Line:
        del self.decorators
        del self.modifiers
        del self.not_allowed_classes
        del self.variables
        del self.name
        del self.current_scope
        del self.parent_scope
        del self.root_scope
        
        return Processed_Line(
            self.output,
            self.ast_list,
        )


def _function(
    ast_list: Token_List,
    current_scope: Scope,
    parent_scope: Scope,
    root_scope: Scope,
) -> Processed_Line:
    return Function(
        ast_list, current_scope, parent_scope, root_scope
    ).parse()
