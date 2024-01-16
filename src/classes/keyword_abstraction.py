from abc import ABC, abstractmethod
from namespace_abstraction import NamespaceAbstraction as Namespace

class KeywordAbstraction(ABC):
    @abstractmethod
    def __init__[T: (list[str], Namespace)](self, line: T, namespace: T):
        pass
    
    @abstractmethod
    def __process(self) -> list[str]:
        pass
    
    @abstractmethod
    def __str__(self) -> str:
        pass
    
    @abstractmethod
    def error(self) -> str:
        pass