from typing import Annotated, Any, Iterable, Self
from weakref import ref


def compare_with_type(__value: object, __type: type) -> bool:
    if __type in __primitive__:
        return type(__value) in __primitive__[__type]
    return type(__value) is __type


class object(object):
    __additional_types__: list[type] = []
    __value__: object = None
    
    def __check_type(self, __value: object) -> bool:
        if type(__value) in self.__additional_types__:
            return True
        if type(__value) is type(self.__value__):
            return True
        return False

char = Annotated[str, "char"]


class string(object):
    __value__: Any = None # type: ignore

    def __check_type(self, __value: Any) -> bool:
        if compare_with_type(__value, str):
            return True
        if type(__value) is type(self.__value__):
            return True
        return False

    def __add__(self, other: Any) -> str:
        if self.__check_type(other):
            return self.__value__ + other
        try:
            return self.__value__ + str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' + '{type(other).__name__}'")
        
    def __radd__(self, other: Any) -> str:
        if self.__check_type(other):
            return other + self.__value__
        try:
            return str(other) + self.__value__
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(other).__name__}'+d '{type(self).__name__}'")
    
    def __iadd__(self, other: Any) -> str:
        if self.__check_type(other):
            self.__value__ += other
            return self.__value__
        try:
            self.__value__ += str(other)
            return self.__value__
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' + '{type(other).__name__}'")
        
    def __mul__(self, other: int) -> str:
        if compare_with_type(other, int):
            return self.__value__ * other
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' * '{type(other).__name__}'")
    
    def __rmul__(self, other: int) -> str:
        if compare_with_type(other, int):
            return other * self.__value__
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(other).__name__}' * '{type(self).__name__}'")
    
    def __imul__(self, other: int) -> str:
        if compare_with_type(other, int):
            self.__value__ *= other
            return self.__value__
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' * '{type(other).__name__}'")
    
    def __getitem__(self, index: int) -> str:
        if compare_with_type(index, int):
            return self.__value__[index]
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}'[{type(index).__name__}]")
    
    def __setitem__(self, index: int, value: Any) -> str:
        _: list[char] = list(self.__value__)
        
        if compare_with_type(index, int) and compare_with_type(value, str):
            _[index] = value
            self.__value__ = "".join(_)
            
            del _
            return self.__value__
        
        del _
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}'[{type(index).__name__}]")
    
    def __delitem__(self, index: int) -> str:
        _: list[char] = list(self.__value__)
        
        if compare_with_type(index, int):
            del _[index]
            self.__value__ = "".join(_)
            
            del _
            return self.__value__
        
        del _
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}'[{type(index).__name__}]")
    
    def __iter__(self) -> Iterable[str]:
        return iter(list(self.__value__))
    
    def __contains__(self, value: Any) -> bool:
        if not compare_with_type(value, str):
            raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' in '{type(value).__name__}'")
        
        return value in self.__value__
     
    def __len__(self) -> int:
        return len(self.__value__)
    
    def __eq__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ == other
        try:
            return self.__value__ == str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' == '{type(other).__name__}'")
        
    def __ne__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ != other
        try:
            return self.__value__ != str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' != '{type(other).__name__}'")
        
    def __lt__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ < other
        try:
            return self.__value__ < str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' < '{type(other).__name__}'")
        
    def __gt__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ > other
        try:
            return self.__value__ > str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' > '{type(other).__name__}'")
        
    def __le__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ <= other
        try:
            return self.__value__ <= str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' <= '{type(other).__name__}'")
        
    def __ge__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ >= other
        try:
            return self.__value__ >= str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' >= '{type(other).__name__}'")
        
    def __bool__(self) -> bool:
        return bool(self.__value__)
    
    def __str__(self) -> str:
        return str(self.__value__)
    
    def __repr__(self) -> str:
        return f"<String({self.__value__})>"
    
    def __cast__(self, __type: type) -> Any:
        if compare_with_type(self.__value__, __type): return self.__value__
        try: return __type(self.__value__)
        except: raise TypeError(f"<String(02.E4)>: cannot cast type '{type(self).__name__}' to '{__type.__name__}'")
        
    def __init__(self, value: Any) -> None:
        if not compare_with_type(value, str):
            # try to cast value to string
            try: value = str(value)
            except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(value).__name__}'")

        self.__value__ = value
        del value
        
    def __copy__(self) -> Self:
        return type(self)(self.__value__)
    
    def __deepcopy__(self) -> Self:
        return type(self)(self.__value__)
    
    def __hash__(self) -> int:
        return hash(self.__value__)
    
    def __format__(self, format_spec: Any) -> str:
        return self.__value__.__format__(format_spec)
    
    def __new__(cls, value: Any) -> Self:
        # try to cast value to string
        try: value = str(value)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(value).__name__}'")
        
        # create new instance
        self = super().__new__(cls)
        self.__init__(value)
        
        del value

        return self
    
    def __del__(self) -> None:
        del self.__value__
    
    def __call__(self, value: Any) -> Self:
        return type(self)(value)
    
    def __set__(self, value: Any) -> None:
        if not compare_with_type(value, str):
            # try to cast value to string
            raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(value).__name__}', cannot auto cast to '{type(self).__name__}'")
        
        self.__value__ = value

class i8(object):
    __value__: Any = None # type: ignore
    __max__: int = 127
    __min__: int = -128

    def __check_range__(self, other: int | None = None) -> int:
        if other:
            if other > self.__max__ or other < self.__min__:
                raise ValueError(f"<Hex(02.E3)>: value '{other}' is out of range")
            
        if self.__value__ > self.__max__ or self.__value__ < self.__min__:
            raise ValueError(f"<Hex(02.E3)>: value '{self.__value__}' is out of range")

        if other: return other
        return self.__value__
        
    def __check_type(self, __value: Any) -> bool:
        if compare_with_type(__value, int):
            return True
        if type(__value) is type(self.__value__):
            return True
        return False

    def __add__(self, other: Any) -> int:
        if self.__check_type(other):
            return self.__check_range__(self.__value__ + other)
        try:
            return self.__check_range__(self.__value__ + int(other))
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' + '{type(other).__name__}'")
        
    def __radd__(self, other: Any) -> int:
        if self.__check_type(other):
            return self.__check_range__(other + self.__value__)
        try:
            return self.__check_range__(int(other) + self.__value__)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(other).__name__}' + '{type(self).__name__}'")
    
    def __iadd__(self, other: Any) -> int:
        if self.__check_type(other):
            self.__value__ += other
            return self.__check_range__()
        try:
            self.__value__ += int(other)
            return self.__check_range__()
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' + '{type(other).__name__}'")
        
    def __mul__(self, other: int) -> int:
        if compare_with_type(other, int):
            return self.__check_range__(self.__value__ * other)
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' * '{type(other).__name__}'")
    
    def __rmul__(self, other: int) -> int:
        if compare_with_type(other, int):
            return self.__check_range__(other * self.__value__)
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(other).__name__}' * '{type(self).__name__}'")
    
    def __imul__(self, other: int) -> int:
        if compare_with_type(other, int):
            self.__value__ *= other
            return self.__check_range__()
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' * '{type(other).__name__}'")
    
    def __getitem__(self, index: int) -> int:
        raise AttributeError(f"<Hex(04.E2)>: cannot get item from '{type(self).__name__}'")
    
    def __setitem__(self, index: int, value: Any) -> int:
        raise AttributeError(f"<Hex(04.E2)>: cannot set item to '{type(self).__name__}'")

    def __delitem__(self, index: int) -> int:
        raise AttributeError(f"<Hex(04.E2)>: cannot delete item from '{type(self).__name__}'")
    
    def __iter__(self) -> Iterable[int]:
        raise AttributeError(f"<Hex(04.E2)>: cannot iterate '{type(self).__name__}'")
    
    def __contains__(self, value: Any) -> bool:
        raise AttributeError(f"<Hex(04.E2)>: cannot check if '{type(self).__name__}' contains '{type(value).__name__}'")
    
    def __len__(self) -> int:
        raise AttributeError(f"<Hex(04.E2)>: cannot get length of '{type(self).__name__}'")
    
    def __eq__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ == other
        try:
            return self.__value__ == int(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' == '{type(other).__name__}'")
        
    def __ne__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ != other
        try:
            return self.__value__ != int(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' != '{type(other).__name__}'")
        
    def __lt__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ < other
        try:
            return self.__value__ < int(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' < '{type(other).__name__}'")
        
    def __gt__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ > other
        try:
            return self.__value__ > int(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' > '{type(other).__name__}'")
        
    def __le__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ <= other
        try:
            return self.__value__ <= int(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' <= '{type(other).__name__}'")
        
    def __ge__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ >= other
        try:
            return self.__value__ >= int(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' >= '{type(other).__name__}'")
        
    def __bool__(self) -> bool:
        return bool(self.__value__)
    
    def __str__(self) -> str:
        return str(self.__value__)
    
    def __repr__(self) -> str:
        return f"i8({self.__value__})"
    
    def __cast__(self, __type: type) -> Any:
        if compare_with_type(self.__value__, __type): return self.__value__
        try: return __type(self.__value__)
        except: raise TypeError(f"<i8(02.E4)>: cannot cast type '{type(self).__name__}' to '{__type.__name__}'")
    
    def __init__(self, value: Any) -> None:
        if not compare_with_type(value, int):
            # try to cast value to int
            try: value = int(value)
            except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(value).__name__}'")

        self.__value__ = value
        self.__check_range__()
        del value
        
    def __copy__(self) -> Self:
        return type(self)(self.__value__)
    
    def __deepcopy__(self) -> Self:
        return type(self)(self.__value__)
    
    def __hash__(self) -> int:
        return hash(self.__value__)
    
    def __format__(self, format_spec: Any) -> str:
        return self.__value__.__format__(format_spec)
    
    def __new__(cls, value: Any) -> Self:
        # try to cast value to int
        try: value = int(value)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(value).__name__}'")
        
        # create new instance
        self = super().__new__(cls)
        self.__init__(value)
        
        del value

        return self
    
    def __del__(self) -> None:
        del self.__value__
        
    def __call__(self, value: Any) -> Self:
        raise AttributeError(f"<Hex(04.E2)>: cannot call '{type(self).__name__}'")

    def __set__(self, value: Any) -> None:
        if not compare_with_type(value, int):
            # try to cast value to int
            raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(value).__name__}', cannot auto cast to '{type(self).__name__}'")
        
        self.__value__ = value
        self.__check_range__()
    
__primitive__: dict[type, tuple[type, ...]] = {
    int: (int, float),
    str: (str, bytes, string),
}
    
a = string("Hello, World!")
a.__set__(i8(127)) # <- a = 777

# a: string = "Hello, World!"

print(a)
    