# ----------------------------- Built-in Imports ----------------------------- #

# single imports - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #

import os
import re
import sys
import json
import enum
import mmap
import signal
import ctypes
import shutil
import hashlib
import functools
import threading
import subprocess
import py_compile
import dataclasses

from multiprocessing import cpu_count
from inspect         import CO_NESTED
from dataclasses     import dataclass
from datetime        import datetime
from sys             import exit
from io              import TextIOWrapper

# multi imports  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #

from pickle import (
    dump,
    load
)
from functools import (
    wraps,
    lru_cache
)
from threading import (
    Thread,
    Event,
    Lock,
)
from concurrent.futures import (
    Future,
    ThreadPoolExecutor,
    ProcessPoolExecutor
)
from typing import (
    Any,
    Optional,
    Union,
    Tuple,
    Mapping,
    Type,
    TypeVar,
    Generic,
    Callable,
    Iterable,
    Iterator,
    Sequence,
    Protocol,
    NoReturn,
    Literal,
    TypeAlias,
    Annotated,
    Self,
)
from types import (
    MappingProxyType as map,
    UnionType,
    FunctionType,
    MethodType,
    FrameType,
    ModuleType,
)
from time import (
    time,
    sleep,
    perf_counter,
    perf_counter_ns,
    process_time,
)

# ----------------------------- External Imports ----------------------------- #

# single imports - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #

import toml
from multimethod import subtype

# multi imports  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #

from argparse import (
    Namespace,
    ArgumentParser
)

# ----------------------------- Internal Imports ----------------------------- #

# src - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  #

from src.config                 import CONFIG
from src.cache_store            import (
    cache,
    file_cache
)
from src.panic                  import panic
from src.better_print           import color_print

# variables  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #

INDENT_CHAR = CONFIG.Formatter.indent_size * " "
re          = __import__(CONFIG.Transpiler.regex_module)

# src.token  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #

from src.token.normalize_tokens import normalize_tokens
from src.token.remove_comments  import remove_comment
from src.token.tokenize_file    import Tokenizer
from src.token.tokenize_line    import tokenize_line

# src.classes  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #

from src.classes.Token import (
    Processed_Line,
    Token_List,
    Token,
)
from   src.classes.Scope          import Scope
from   src.classes.Transpiler     import Transpiler
from   src.classes.WorkerPool     import WorkerPool
import src.core.framework         as     framework

from   src.classes.Hashing        import Hashing
from   src.classes.ArgParser      import ArgParser
from   src.classes.Timer          import Timer
from   src.classes.HelixLanguage  import HelixLanguage

# src.functions  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #

from src.functions._for         import _for
from src.functions._let         import _let
from src.functions._class       import _class
from src.functions._unless      import _unless
from src.functions._include     import _include
from src.functions._functions   import _function
from src.functions._unmarked    import _unmarked
from src.functions.inject_core  import inject_core

# ------------------------------ End of Imports ------------------------------ #

