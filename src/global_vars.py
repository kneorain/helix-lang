from types import MappingProxyType as map

CACHE = {}

DOUBLE_CHARACTER: list[str] = [
    r"==",
    r"!=",
    r"->",
    r"\:\:",
    r"<-",
    r"<=",
    r">=",
    r"&&",
    r"\|\|",
    r"\+\+",
    r"--",
    r"\+\=",
    r"\-\=",
    r"\*\=",
    r"\/\=",
    r"\&\=",
    r"\|\=",
    r"\^\=",
    r"\%\=",
    r"\*\*",
    r"\.\.\.",
]

KEYWORDS: map[str, map[str, str | bool]] = map({
    # IF YOU MODIFY THE KEYWORDS !DO NOT CHANGE THE INTERNAL NAMES!
    "if"            : map({"internal_name": "IF"       ,  "body_required": True  ,  "keyword_type" : "control_flow"}),
    "else"          : map({"internal_name": "ELSE"     ,  "body_required": True  ,  "keyword_type" : "control_flow"}),
    "while"         : map({"internal_name": "WHILE"    ,  "body_required": True  ,  "keyword_type" : "loop"}),
    "for"           : map({"internal_name": "FOR"      ,  "body_required": True  ,  "keyword_type" : "loop"}),
    "continue"      : map({"internal_name": "CONTINUE" ,  "body_required": False ,  "keyword_type" : "loop"}),
    "stop"          : map({"internal_name": "BREAK"    ,  "body_required": False ,  "keyword_type" : "loop"}),
 
    "case"          : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "switch_match"}),
    "default"       : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "switch_match"}),
    "switch"        : map({"internal_name": ""         ,  "body_required": False ,  "keyword_type" : "switch_match"}),
    "match"         : map({"internal_name": ""         ,  "body_required": False ,  "keyword_type" : "switch_match"}),
 
    "fn"            : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "function"}),
    "async"         : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "function"}),
    "return"        : map({"internal_name": ""         ,  "body_required": False ,  "keyword_type" : "function"}),
 
    "class"         : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "class"}),
    "struct"        : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "struct"}),
    "interface"     : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "interface"}),
    "enum"          : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "enum"}),
    "union"         : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "class"}),
    "try"           : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "error_handling"}),
    "catch"         : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "error_handling"}),
    "finally"       : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "error_handling"}),
    "throw"         : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "error_handling"}),
    "thread"        : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "callable"}),
    "lambda"        : map({"internal_name": ""         ,  "body_required": True  ,  "keyword_type" : "callable"}),
    "break"         : map({"internal_name": ""         ,  "body_required": False ,  "keyword_type" : "core"}),
    "yield"         : map({"internal_name": ""         ,  "body_required": False ,  "keyword_type" : "core"}),
    "await"         : map({"internal_name": ""         ,  "body_required": False ,  "keyword_type" : "core"}),
    
    "delegate"      : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "private"       : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "protected"     : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "final"         : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "implements"    : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "abstract"      : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "let"           : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "const"         : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "var"           : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "final"         : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "public"        : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "private"       : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "protected"     : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "include"       : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "import"        : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "using"         : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "from"          : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "async"         : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "await"         : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "yield"         : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    "yield\\s+from" : map({"internal_name":""          ,  "body_required":False  ,  "keyword_type" : ""}),
    # -------------------------------------- #
})

BODY_REQUIRED_KEYWORDS: map[str, str] = map({
    keyword : KEYWORDS[keyword]["keyword_type"]
    for keyword in KEYWORDS.keys()
    if keyword[1]
}) # type: ignore


PUNCTUATION = r".,:?()[]{}<>+-*/=|&^%$#~"
COMMENT = "~~"
BLOCK_COMMENT = "~*~"