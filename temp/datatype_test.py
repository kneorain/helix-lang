# python with strong typing

from typing import TypeVar, Generic, Type, Callable
from decimal import Decimal as double
from abc import ABC, abstractmethod
  

T = TypeVar("T")
char = TypeVar("char", str, int)

# int, float, double, char, string, bool
class unary(ABC):
    __value: int or "H_int"
    __is_immutable: bool
    
    @abstractmethod
    def __init__(self,
                 value: int or float or double or "H_int" or "H_float" or "H_double",
                 is_immutable: bool = False):
        self.__is_immutable = is_immutable
        if isinstance(value, int):
            self.__value = value
        elif isinstance(value, H_int) or isinstance(value, H_float) or isinstance(value, H_double):
            self.__value = value.value
        else:
            raise TypeError(f"Invalid type for int: {type(value)}")

    def do_checks(self,
                  value: int or float or double or "H_int" or "H_float" or "H_double",
                  is_binary: bool = False,
                  type: Type = None):
        if is_binary:
            if isinstance(value, type):
                return value
            elif isinstance(value, H_int) or isinstance(value, H_float) or isinstance(value, H_double):
                return value.value
            else:
                if isinstance(value, int) and isinstance(self.__value, float):
                    return value
                elif isinstance(self.__value, int) and isinstance(value, float):
                    return value
                if isinstance(value, float) and isinstance(self.__value, double):
                    return value
                elif isinstance(self.__value, float) and isinstance(value, double):
                    return value
                raise TypeError(f"Invalid type for int: {type(value)}")
        else:
            if self.__is_immutable:
                raise TypeError("Can not change immutable value")
            if isinstance(value, type):
                return value
            elif isinstance(value, H_int) or isinstance(value, H_float) or isinstance(value, H_double):
                return value.value
            else:
                if isinstance(value, int) and isinstance(self.__value, float):
                    return value
                elif isinstance(self.__value, int) and isinstance(value, float):
                    return value
                if isinstance(value, float) and isinstance(self.__value, double):
                    return value
                elif isinstance(self.__value, float) and isinstance(value, double):
                    return value
                raise TypeError(f"Invalid type for int: {type(value)}")
    
    @abstractmethod
    def __add__(self,
                value: int or float or double or "H_int" or "H_float" or "H_double",
                type: Type = None):
        value = self.do_checks(value, True, type)
        return self.__value + value
    @abstractmethod
    def __mul__(self,
                value: int or float or double or "H_int" or "H_float" or "H_double",
                type: Type = None):
        value = self.do_checks(value, True, type)
        return self.__value * value
    @abstractmethod
    def __truediv__(self,
                value: int or float or double or "H_int" or "H_float" or "H_double",
                type: Type = None):
        value = self.do_checks(value, True, type)
        return self.__value / value
    @abstractmethod
    def __mod__(self,
                value: int or float or double or "H_int" or "H_float" or "H_double",
                type: Type = None):
        value = self.do_checks(value, True, type)
        return self.__value % value
    @abstractmethod
    def __floordiv__(self,
                     value: int or float or double or "H_int" or "H_float" or "H_double",
                     type: Type = None):
        value = self.do_checks(value, True, type)
        return self.__value // value
    @abstractmethod
    def __pow__(self,
                value: int or float or double or "H_int" or "H_float" or "H_double",
                type: Type = None):
        value = self.do_checks(value, True, type)
        return self.__value ** value
    
    @abstractmethod
    def __neg__(self):
        return -self.__value
    
    @abstractmethod
    def __abs__(self):
        return abs(self.__value)
    
    @abstractmethod
    def __eq__(self,
               value: int or float or double or "H_int" or "H_float" or "H_double",
               type: Type = None):
        value = self.do_checks(value, True, type)
        return self.__value == value
    
    @abstractmethod
    def __ne__(self,
               value: int or float or double or "H_int" or "H_float" or "H_double",
               type: Type = None):
        value = self.do_checks(value, True, type)
        return self.__value != value
    
    @abstractmethod
    def __lt__(self,
               value: int or float or double or "H_int" or "H_float" or "H_double",
               type: Type = None):
        value = self.do_checks(value, True, type)
        return self.__value < value
    
    @abstractmethod
    def __le__(self,
               value: int or float or double or "H_int" or "H_float" or "H_double",
               type: Type = None):
        value = self.do_checks(value, True, type)
        return self.__value <= value
    
    @abstractmethod
    def __gt__(self,
               value: int or float or double or "H_int" or "H_float" or "H_double",
               type: Type = None):
        value = self.do_checks(value, True, type)
        return self.__value > value
    
    @abstractmethod
    def __ge__(self,
               value: int or float or double or "H_int" or "H_float" or "H_double",
               type: Type = None):
        value = self.do_checks(value, True, type)
        return self.__value >= value
    
    @abstractmethod
    def __str__(self):
        return str(self.__value)
    
    @abstractmethod
    def __repr__(self):
        return repr(self.__value)
    
    @abstractmethod
    def __hash__(self):
        return hash(self.__value)

    @property
    def value(self):
        return self.__value

    def set(self, value: int or float or double or "H_int" or "H_float" or "H_double", type: Type = None):
        self.__value = self.do_checks(value, False, type)
    
class H_float(unary):
    def __init__(self, value: float or "H_float", is_immutable: bool = False):
        if isinstance(value, float):
            value = value
        elif isinstance(value, H_float):
            value = value.value
        elif isinstance(value, int):
            value = float(value)
        elif isinstance(value, H_int):
            value = float(value.value)
        elif isinstance(value, double):
            value = float(value)
        elif isinstance(value, H_double):
            value = float(value.value)
        else:
            raise TypeError(f"Invalid type for int: {type(value)}")
        
        super().__init__(float(value), is_immutable)
    
    def __add__(self, value: float or "H_float") -> "H_float":
        return H_float(super().__add__(value, float))
    
    def __sub__(self, value: float or "H_float") -> "H_float":
        return H_float(super().__add__(value, float))
    
    def __mul__(self, value: float or "H_float") -> "H_float":
        return H_float(super().__mul__(value, float))
    
    def __truediv__(self, value: float or "H_float") -> "H_float":
        return H_float(super().__truediv__(value, float))
    
    def __mod__(self, value: float or "H_float") -> "H_float":
        return H_float(super().__mod__(value, float))
    
    def __floordiv__(self, value: float or "H_float") -> "H_float":
        return H_float(super().__floordiv__(value, float))
    
    def __pow__(self, value: float or "H_float") -> "H_float":
        return H_float(super().__pow__(value, float))
    
    def __neg__(self) -> "H_float":
        return H_float(super().__neg__())
    
    def __abs__(self) -> "H_float":
        return H_float(super().__abs__())
    
    def __eq__(self) -> bool:
        return super().__eq__(self, float)
    
    def __ne__(self) -> bool:
        return super().__ne__(self, float)
    
    def __lt__(self) -> bool:
        return super().__lt__(self, float)
    
    def __le__(self) -> bool:
        return super().__le__(self, float)
    
    def __gt__(self) -> bool:
        return super().__gt__(self, float)
    
    def __ge__(self) -> bool:
        return super().__ge__(self, float)
    
    def __str__(self) -> str:
        return str(super().__str__())
    
    def __repr__(self) -> str:
        return repr(super().__repr__())
    
    def __hash__(self) -> float:
        return hash(super().__hash__())
    
    def setter(self, value: float or "H_float"):
        super().set(value, float)
        
    @property
    def value(self):
        return super().value
    

class H_double(unary):
    def __init__(self, value: int or "H_int", is_immutable: bool = False):
        if isinstance(value, float):
            value = value
        elif isinstance(value, H_float):
            value = value.value
        elif isinstance(value, int):
            value = float(value)
        elif isinstance(value, H_int):
            value = float(value.value)
        elif isinstance(value, double):
            value = float(value)
        elif isinstance(value, H_double):
            value = float(value.value)
        else:
            raise TypeError(f"Invalid type for int: {type(value)}")
        super().__init__(double(value), is_immutable)

class H_int(unary):
    def __init__(self, value: int or "H_int", is_immutable: bool = False):
        if isinstance(value, float):
            value = int(value)
        elif isinstance(value, H_float):
            value = int(value.value)
        elif isinstance(value, int):
            value = value
        else:
            raise TypeError(f"Invalid type for int: {type(value)}")

        super().__init__(int(value), is_immutable)
    
    def __add__(self, value: int or "H_int") -> "H_int":
        return H_int(super().__add__(value, int))
    
    def __sub__(self, value: int or "H_int") -> "H_int":
        return H_int(super().__add__(value, int))
    
    def __mul__(self, value: int or "H_int") -> "H_int":
        return H_int(super().__mul__(value, int))
    
    def __truediv__(self, value: int or "H_int") -> "H_int":
        return H_int(super().__truediv__(value, int))
    
    def __mod__(self, value: int or "H_int") -> "H_int":
        return H_int(super().__mod__(value, int))
    
    def __floordiv__(self, value: int or "H_int") -> "H_int":
        return H_int(super().__floordiv__(value, int))
    
    def __pow__(self, value: int or "H_int") -> "H_int":
        return H_int(super().__pow__(value, int))
    
    def __neg__(self) -> "H_int":
        return H_int(super().__neg__())
    
    def __abs__(self) -> "H_int":
        return H_int(super().__abs__())
    
    def __eq__(self) -> bool:
        return super().__eq__(self, int)
    
    def __ne__(self) -> bool:
        return super().__ne__(self, int)
    
    def __lt__(self) -> bool:
        return super().__lt__(self, int)
    
    def __le__(self) -> bool:
        return super().__le__(self, int)
    
    def __gt__(self) -> bool:
        return super().__gt__(self, int)
    
    def __ge__(self) -> bool:
        return super().__ge__(self, int)
    
    def __str__(self) -> str:
        return str(super().__str__())
    
    def __repr__(self) -> str:
        return repr(super().__repr__())
    
    def __hash__(self) -> int:
        return hash(super().__hash__())
    
    def setter(self, value: int or "H_int"):
        super().set(value, int)
        
    @property
    def value(self):
        return super().value
    
    @value.setter
    def value(self, value: int or "H_int"):
        super().value = value
        
        
# a: int = 1
# transpile to this:
a = H_int(1)

# let a: int = 1
# transpile to this:
a = H_int(1, True)

# a = 2
# transpile to this:
#a.setter(2) # raises error if a is immutable

def check_types(*types):
    def decorator(func):
        def wrapper(*args, **kwargs):
            regular_types = []
            args_type = None
            kwargs_type = {}

            for i in range(len(types)):
                if isinstance(types[i], list):
                    args_type = types[i][0]
                elif isinstance(types[i], dict):
                    kwargs_type[tuple(types[i].keys())[0]] = types[i][tuple(types[i].keys())[0]]
                else:
                    regular_types.append(types[i])
            
            for i in range(len(regular_types)):
                if not isinstance(args[i], regular_types[i]):
                    raise TypeError(f"Invalid type for argument {i}: {type(args[i])}")
                
            if args_type is not None:
                for i in range(len(args) - len(regular_types)):
                    if not isinstance(args[i + len(regular_types)], args_type):
                        raise TypeError(f"Invalid type for argument {i + len(regular_types)}: {type(args[i + len(regular_types)])}")
                    
            if kwargs_type is not None:
                for key in kwargs_type.keys():
                    if not isinstance(kwargs[key], kwargs_type[key]):
                        raise TypeError(f"Invalid type for argument {key}: {type(kwargs[key])}")
                    
            return func(*args, **kwargs)
        return wrapper
    return decorator

@check_types(int, int)
def add(x: int, y: int):
    print(x, y)



@check_types(int, [str])
def sub(x: int, *y: str):
    print(x, y)

@check_types(int, {"y": str})
def mul(x: int, y: str = "hello"):
    print(x, y)

@check_types(int, [int], {"z": str})
def div(x: int, *y: int, z: str = "hello"):
    print(x, y, z)

print(add(1, 2)) # 3
print(sub(1, "2", "2", "2", "2")) # 3
print(mul(1, y="2")) # 3
print(div(1, 2, 3, 4, 5, z="he12llo")) # 3
