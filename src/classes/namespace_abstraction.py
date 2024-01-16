from abc import ABC, abstractmethod
 
class NamespaceAbstraction(ABC):
    @abstractmethod
    def __init__(self, line: list[str], namespace: str):
        self.__line = line
        self.__namespace = namespace
    
    @abstractmethod
    def __str__(self) -> str:
        pass
    
    @abstractmethod
    def error(self) -> str:
        pass