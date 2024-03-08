import asyncio
import functools
import math
import os
import re
import time
from typing import IO, AsyncGenerator, Generator, Optional, Self
from types import MappingProxyType as mpt
from psutil import virtual_memory

CONVERSIONS_DICT = mpt({
    # SI Units (Decimal)
    "bit": 1 / 8,
    "byte": 1,
    "kilobyte": 1000,
    "megabyte": 1000 ** 2,
    "gigabyte": 1000 ** 3,
    "terabyte": 1000 ** 4,
    "petabyte": 1000 ** 5,
    "exabyte": 1000 ** 6,
    "zetabyte": 1000 ** 7,
    "yottabyte": 1000 ** 8,

    # Binary Units (IEC)
    "kibibyte": 1024,
    "mebibyte": 1024 ** 2,
    "gibibyte": 1024 ** 3,
    "tebibyte": 1024 ** 4,
    "pebibyte": 1024 ** 5,
    "exbibyte": 1024 ** 6,
    "zebibyte": 1024 ** 7,
    "yobibyte": 1024 ** 8,

    # Abbreviations
    "b": 1,
    "kb": 1000,
    "mb": 1000 ** 2,
    "gb": 1000 ** 3,
    "tb": 1000 ** 4,
    "pb": 1000 ** 5,
    "eb": 1000 ** 6,
    "zb": 1000 ** 7,
    "yb": 1000 ** 8,

    "kib": 1024,
    "mib": 1024 ** 2,
    "gib": 1024 ** 3,
    "tib": 1024 ** 4,
    "pib": 1024 ** 5,
    "eib": 1024 ** 6,
    "zib": 1024 ** 7,
    "yib": 1024 ** 8,
})
CONVERTER_CHECK = re.compile(r"^(\d+(\.\d+)?)\s*([a-zA-Z]+)$")

@functools.lru_cache(maxsize=None)
@functools.total_ordering
def sizeof_int(data: str) -> int:
    # Use the precompiled regex: CONVERTER_CHECK
    match = CONVERTER_CHECK.match(data)
    
    if not match:
        raise ValueError(f"Invalid data format: {data}, expected format is like '[number][space][unit]', e.g., '2 MB', '512KB', or '1.5 TB'")

    if match.groups()[2].lower() not in CONVERSIONS_DICT:
        raise ValueError(f"Invalid unit: {match.groups()[2].lower()}, expected one of {', '.join(CONVERSIONS_DICT.keys())}")

    return int(float(match.groups()[0]) * CONVERSIONS_DICT[match.groups()[2].lower()])

def sizeof_fmt(num, suffix="B"):
    for unit in ("", "Ki", "Mi", "Gi", "Ti", "Pi", "Ei", "Zi"):
        if abs(num) < 1024.0:
            return f"{num:3.1f}{unit}{suffix}"
        num /= 1024.0
    return f"{num:.1f}Yi{suffix}"

class FileStream:
    def __convert_in(self, data: bytes|str) -> bytes:
        return data.encode(self.__encoding) if isinstance(data, str) and not self.__use_bytes else bytes(data)

    def __convert_out(self, data: bytes) -> str:
        return data if self.__use_bytes else data.decode(self.__encoding)
        
    def is_empty(self) -> bool:
        return self.__size == 0
    
    def __init__(self, file: str, exclusive: bool = False, chunk_size: Optional[int] = None, start: int = 0, encoding: str = "utf-8", use_bytes: bool = False) -> None:
        if os.path.isdir(file):
            raise IsADirectoryError(f"{file} is a directory.")
        if exclusive and os.path.exists(file):
            raise FileExistsError(f"{file} already exists.")
        if not os.path.exists(file):
            open(file, "wb").close()
    
        _access: tuple[bool, bool] = os.access(file, os.R_OK), os.access(file, os.W_OK)
        if not _access[0] or not _access[1]: raise PermissionError(f"Both read and write, permissions denied for {file}.")
        elif not _access[0]: raise PermissionError(f"Read permission denied for {file}.")
        elif not _access[1]: raise PermissionError(f"Write permission denied for {file}.")
    
        self.__use_bytes = use_bytes
        self.__size = os.path.getsize(file)
        self.__encoding        = encoding
        
        def calculate_optimal_chunking_size(size: int) -> int:
            # Define the minimum and maximum chunk sizes min: 1 kib, max: 5 kib
            min_chunk_size = 1024
            max_chunk_size = 1024 * 100
            
            if size <= 0:
                return min_chunk_size
            
            log_chunk_size = min_chunk_size * math.log2(size / min_chunk_size + 1)
            
            optimal_chunk_size = int(max(min_chunk_size, min(log_chunk_size, max_chunk_size)))
            return optimal_chunk_size
        
        self.__chunk_size      = chunk_size if chunk_size else calculate_optimal_chunking_size(self.__size)
        self.__total_chunks    = self.__size // self.__chunk_size
        if self.__size > (1024 * 1024 * 1024) / 2: # 512 MB
            self.__file = open(file, "r+b", buffering=self.__chunk_size)
        else:
            self.__file: IO[bytes] = open(file, "r+b")
            
        self.__file.seek(start)
        self.__file.flush()
        
    def __enter__(self) -> Self:
        return self
    
    def __exit__(self, exc_type: Optional[type], exc_val: Optional[Exception], exc_tb: Optional[object]) -> Optional[bool]:
        self.__file.close()
        return exc_type is None

    
    async def __read_stream(self, start: int, end: int) -> AsyncGenerator[str, None]:
        self.__file.seek(start)
        
        _ = end
        
        # normalize both the start and end positions to the nearest chunk
        start = start - (start % self.__chunk_size)
        end   = min(end + (self.__chunk_size - (end % self.__chunk_size)) if end % self.__chunk_size else end, self.__size)
        
        while (current_chunk := self.__file.read(self.__chunk_size)):
            # if its the last chunk, trim the bytes
            yield (
                self.__convert_out(current_chunk[:_ - end])  # end - self.current_position()
                if self.current_position() >= end
                else
                    self.__convert_out(current_chunk)
            )
            if self.current_position() >= end:
                break
            
    def read_chunk(self, chunk: int) -> str:
        if chunk < 0 or chunk > self.__total_chunks:
            raise ValueError(f"Invalid chunk: {chunk}, expected a value between 0 and {self.__total_chunks}")
        
        previous_position = self.current_position()
        self.__file.seek(chunk * self.__chunk_size)
        data = self.__convert_out(self.__file.read(self.__chunk_size))
        self.__file.seek(previous_position)
        return data
    
    async def __read(self, start: Optional[int], end: Optional[int]) -> str:
        if self.__use_bytes:
            return b''.join([chunk async for chunk in self.__read_stream(start=start, end=end)])
        return ''.join([chunk async for chunk in self.__read_stream(start=start, end=end)])
        
    #@profile
    def read(self, start: Optional[int] = None, end: Optional[int] = None, ignore_errors: bool = False) -> str:
        if end and end > self.__size:
            raise ValueError(f"Invalid end: {end}, expected a value between 0 and {self.__size}")
        
        if start is None: start = 0
        if end   is None: end   = self.__size
        
        start = start if start >= 0 else self.__size + start
        end   = end   if end   >= 0 else self.__size + end
        
        # Validate start and end
        if start > end and not ignore_errors:
            raise ValueError(f"Invalid start: {start}, expected a value less than {end}")

        # if theres more data then system memory, use __read_generator
        if (end - start) * 4 > virtual_memory().available:
            return self.__convert_out(self.__file.read()[start:end])
        
        return (
            self.__convert_out(self.__file.read()[start:end])
            if self.__size < 10 * (1024 * 1024) # 10 MB
            else
                asyncio.run(self.__read(start, end))
        )

    def read_stream(self, start: Optional[int] = None, end: Optional[int] = None) -> Generator[str, None, None]:
        if end and end > self.__size:
            raise ValueError(f"Invalid end: {end}, expected a value between 0 and {self.__size}")
        
        if start is None: start = 0
        if end   is None: end   = self.__size
        
        start = start if start >= 0 else self.__size + start
        end   = end   if end   >= 0 else self.__size + end
        
        # Validate start and end
        if start > end:
            raise ValueError(f"Invalid start: {start}, expected a value less than {end}")

        # Convert the async generator to a list of items
        async def _read_stream(start: int, end: int) -> list[str|bytes]:
            return [chunk async for chunk in self.__read_stream(start=start, end=end)]
        
        for chunk in asyncio.run(_read_stream(start, end)):
            yield chunk
        del chunk

    
        
    def __del__(self):
        try:
            self.__file.close()
        except AttributeError:
            pass
    
    def __repr__(self) -> str:
        return f"SafeFile({self.file}, \"read-write-bytes\", {self.__chunk_size}, {self.__encoding})"
    
    def __str__(self) -> str:
        return f"SafeFile({self.file}, \"read-write-bytes\", {self.__chunk_size}, {self.__encoding})"
    
    def __iter__(self) -> Generator[str, None, None]:
        return self.read_stream()
    
    def __next__(self) -> str:
        return next(self.read_stream())
    
    def seek(self, position: int, whence: int = 0) -> None:
        self.__file.seek(position, whence)
        
    def current_position(self) -> int:
        return self.__file.tell()
    
    def flush(self) -> None:
        self.__file.flush()
    
    def __len__(self) -> str:
        # convert to a human readable format
        return sizeof_fmt(self.__size) if self.__size < 1024 else f"{self.__size / 1024} KB" if self.__size < 1024 ** 2 else f"{self.__size / (1024 ** 2)} MB" if self.__size < 1024 ** 3 else f"{self.__size / (1024 ** 3)} GB" if self.__size < 1024 ** 4 else f"{self.__size / (1024 ** 4)} TB" if self.__size < 1024 ** 5 else f"{self.__size / (1024 ** 5)} PB" if self.__size < 1024 ** 6 else f"{self.__size / (1024 ** 6)} EB" if self.__size < 1024 ** 7 else f"{self.__size / (1024 ** 7)} ZB" if self.__size < 1024 ** 8 else f"{self.__size / (1024 ** 8)} YB"
    
    
    
    @property
    def chunk_size(self) -> int:
        return self.__chunk_size
    
    @property
    def total_chunks(self) -> int:
        return self.__total_chunks
    
    @property
    def sizeof(self) -> int:
        return self.__size
        
path = os.path.join(os.path.expanduser("~"),  "test.txt")

start = 1024 * 1024 # 1 MB
end = 1024 * 1024 * 1024 * 5 # 5 GB
start_time = time.perf_counter_ns()
#with open(path, "wb") as file:
#    # write 1gb of data
#    file.write(b"0" * ((1024 * 1024 * 1024) * 5))
#print(f"\nFile Size: {os.path.getsize(path) / 1_000_000} MB")
#print(f"File created in: {(time.perf_counter_ns() - start_time) / 1_000_000} ms")

start_time = time.perf_counter_ns()
with FileStream(path, use_bytes=True) as file:
    print(sizeof_fmt(len(file.read(start, end))))
    print((file).__len__())
    
end_time = time.perf_counter_ns()
file_stream_time = (end_time - start_time) / 1_000_000 # in ms

print(f"File Stream Time: {file_stream_time:,.2f} ms\n")

start_time = time.perf_counter_ns()
with open(path, "rb") as file:
    print(sizeof_fmt(len(file.read()[start:end])))

end_time = time.perf_counter_ns()
file_time = (end_time - start_time) / 1_000_000 # in ms

print(f"Open Time: {file_time:,.2f} ms")
    
    
