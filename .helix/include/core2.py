# make a metaclass called HelixMeta that will be used to create all the primitive types
# when a fucntion in a subclass is called, the meta class should check if the types are the same as the subclass or as defiend in the altranitive_types var in the subclass and if they are not, then it should raise a TypeError

import os
import sys
import threading
import time

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
)

from concurrent.futures import (
    Future,
    ThreadPoolExecutor,
    ProcessPoolExecutor
)

from multimethod import subtype