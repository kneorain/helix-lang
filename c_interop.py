from src.core.imports import (
    CONFIG,
    framework,
)

class C_Interop(framework.Interop):
    cache_dir: str
    input_file: str
    output_file: str
    #hash: Hashing

    
    def __init__(self, input_file: str, *attrs: str) -> None:
        pass
    
    def __getattr__(self, attr: str) -> Any:
        pass
    
    def __setattr__(self, attr: str, value: Any) -> None:
        raise AttributeError("Cannot set attribute")
    
    def __delattr__(self, attr: str) -> None:
        pass
    
    def __compile__(self) -> None:
        pass
    
    def get(self) -> tuple[ctypes.CDLL._FuncPtr, ...]:
        pass
    
    def __del__(self) -> None:
        pass