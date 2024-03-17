from src.core.imports import (
    Future,
    ProcessPoolExecutor as ProcessPool,
    ThreadPoolExecutor  as ThreadPool,
    Literal,
    Optional,
    TypeAlias,
    Annotated,
    Callable,
    Iterable,
    NoReturn,
    Mapping,
    Generic,
    TypeVar,
    Union,
    Self,
    Any,
    cpu_count,
    CO_NESTED,
    Lock,
    sys,
)

# ------------------------------ Type Variables ------------------------------ #
T = TypeVar("T")
# ----------------------------- Version Checking ----------------------------- #
if sys.version_info < (3, 10):
    raise NotImplementedError(f"Python version must be 3.10 or greater to use this module, current version is {sys.version_info}")

# ------------------------------ Types ----------------------------------- #
PoolType:       TypeAlias = Annotated[Optional[Union[ThreadPool, ProcessPool]], "The pool to be used for the workers"]
LockType:       TypeAlias = Annotated[Lock,               "The lock to be used for the pool to avoid parallelism issues"]
WorkerType:     TypeAlias = Annotated[int,                "The amount of workers to create"]
FutureType:     TypeAlias = Annotated[Future,             "Future of the appended function"]
FuturesType:    TypeAlias = Annotated[list[Future],       "The futures to be executed (They are cleared after the execute method is called)"]
ResultsType:    TypeAlias = Annotated[list[T],            "The results of the futures after they have been executed (They are cleared when the execute method is called)"]
TimeoutType:    TypeAlias = Annotated[float,              "The time out for a worker to complete after the pool or future(s) is executed"]
ShutdownType:   TypeAlias = Annotated[bool,               "If the pool has been shutdown or not"]
PoolNameType:   TypeAlias = Annotated[str,                "The type of pool to create ('thread' or 'process')"]
FunctionType:   TypeAlias = Annotated[Callable[..., T],   "The function to be executed in the pool, adds to execution queue, (Queue is cleared after execute method is called)"]
InitializeType: TypeAlias = Annotated[Callable[..., None],"The initializer to be used for all the workers when the pool is created"]

# # ------------------------------ Types ----------------------------------- #
# type PoolType       = Annotated[Union[ThreadPool, ProcessPool], "The pool to be used for the workers"] # syntax: ignore
# type LockType       = Annotated[Lock,             "The lock to be used for the pool to avoid parallelism issues"] # syntax: ignore
# type WorkerType     = Annotated[int,              "The amount of workers to create"] # syntax: ignore
# type FutureType     = Annotated[Future,           "Future of the appended function"] # syntax: ignore
# type FuturesType    = Annotated[Iterable[Future],    "The futures to be executed (They are cleared after the execute method is called)"] # syntax: ignore
# type ResultsType    = Annotated[Iterable[T],      "The results of the futures after they have been executed (They are cleared when the execute method is called)"] # syntax: ignore
# type TimeoutType    = Annotated[float,            "The time out for a worker to complete after the pool or future(s) is executed"] # syntax: ignore
# type ShutdownType   = Annotated[bool,             "If the pool has been shutdown or not"] # syntax: ignore
# type PoolNameType   = Annotated[str,              "The type of pool to create ('thread' or 'process')"] # syntax: ignore
# type FunctionType   = Annotated[Callable[..., T], "The function to be executed in the pool, adds to execution queue, (Queue is cleared after execute method is called)"] # syntax: ignore
# type InitializeType = Annotated[Callable,         "The initializer to be used for all the workers when the pool is created"] # syntax: ignore


# ------------------------------- Functions ---------------------------------- #
def start_all_threads(x: Any = None) -> NoReturn: # type: ignore
    pass

__process_worker_function: Callable[..., T] = None # type: ignore

def set_process_worker_function(func: Callable[..., T]) -> None:
    global __process_worker_function
    __process_worker_function = func
    
def run_process_worker_function(*args: T) -> T:
    return __process_worker_function(*args) # type: ignore

def function_origin_is_outside(func):
    def check1(func):
        try: return func.__name__ == '<lambda>'
        except AttributeError: return False
    def check2(func):
        try: return func.__closure__ is not None
        except AttributeError: return False
    def check3(func):
        try: return func.__code__.co_flags & CO_NESTED
        except AttributeError: return False
    def check4(func):
        try: return '<locals>' in func.__qualname__
        except AttributeError: return False
        
    return (
           check1(func)
        or check2(func)
        or check3(func)
        or check4(func)
    )


# --------------------------------- Class ------------------------------------ #
class WorkerPool(Generic[T]):
    # ---------------------------- Variables --------------------------------- #
    __workers:     WorkerType
    __pool:        PoolType
    __futures:     FuturesType
    __lock:        LockType
    __results:     ResultsType
    __pool_type:   PoolNameType
    __shutdown:    ShutdownType
    __time_out:    TimeoutType
    __initializer: InitializeType

    # ---------------------------- Constructor ------------------------------- #
    def __init__(
            self,
            workers:     int      = cpu_count(),
            pool_type:   Annotated[Union[bool, str], "If True or 'thread', the pool will be an IO pool, if False or 'process', the pool will be a CPU pool"] = "thread",
            time_out:    float    = 60.0,
            initializer: Callable[..., None] = start_all_threads,
    ) -> None:
        self.__initializer = initializer
        self.__futures     = []
        self.__time_out    = time_out
        self.__workers     = workers
        self.__lock         = Lock()
        self.__shutdown    = False
        self.__pool        = None
        self.__results     = () # type: ignore
        self.__pool_type   = ((
            "thread" if pool_type else "process"
        ) if isinstance(pool_type, bool) else (
            pool_type.lower() if pool_type.lower() in ("thread", "process") else "thread"
        ))

        self.__structure_pool()

    # ---------------------------- Initializers ------------------------------ #
    def __structure_pool(
        self,
        by: Annotated[int, "The amount of workers to add or remove from the pool (< 0 to remove, > 0 to add)"] = 0,
        non_main_origin: Annotated[bool, "If the function is not from the main module or is a lambda"] = False,
        non_main_origin_function: Annotated[Callable, "The function to add to a workers namespace"] = None # type: ignore
    ) -> None:
        if by != 0:
            self.__workers += by
        if not non_main_origin or self.__pool_type == "thread":
            self.__pool = (
                ThreadPool(self.__workers, initializer=self.__initializer)
                if self.__pool_type == "thread"
                else ProcessPool(self.__workers, initializer=self.__initializer)
            )
        else:
            self.__pool = (
                ProcessPool(self.__workers, initializer=set_process_worker_function, initargs=(non_main_origin_function,))
            )

    # ---------------------------- Magic Methods ----------------------------- #
    def __enter__(self) -> Self:
        return self

    def __exit__(
        self,
        exc_type:  T,
        exc_value: int,
        traceback: Exception
    ) -> Literal[False]:
        if not self.__shutdown:
            self.close()
        return False
    
    def __del__(self) -> None:
        if not self.__shutdown:
            self.close()
        del (
            self.__pool,
            self.__futures,
            self.__lock
        )


    # ------------------------------ Modifiers ------------------------------- #
    def add_worker(
        self,
        workers: WorkerType = 1,
    ) -> None:
        with self.__lock:
            self.__structure_pool(workers)

    def remove_worker(
        self,
        workers: WorkerType = 1,
    ) -> None:
        with self.__lock:
            self.__structure_pool(-workers)

    # ------------------------------ Appenders ------------------------------- #
    def add_to_futures(self, *parm: FuturesType) -> None:
        self.__futures += [parm[0]] if len(parm) == 1 else parm # type: ignore
    
    def clear_futures(self) -> None:
        self.__futures.clear()
        
    def iter_futures(self) -> Iterable[FutureType]:
        return iter(self.__futures)
    
    def append_future(
        self,
        future: FutureType
    ) -> None:
        with self.__lock:
            if not isinstance(future, Future):
                raise TypeError("Future must be of type Future")
            self.add_to_futures(future) # type: ignore

    def append_futures(
        self,
        *futures: FuturesType
    ) -> None:
        with self.__lock:
            if not all(isinstance(future, Future) for future in futures):
                raise TypeError("All items in futures must be of type Future")
            self.add_to_futures(*futures)

    def append(
        self,
        func:     Annotated[Callable[..., T], "The function to be executed in the pool, adds to execution queue, (Queue is cleared after execute method is called)"],
        *args:    Annotated[Iterable[T] | T,      "The arguments to be passed to the function"],
        **kwargs: Annotated[Mapping[str, T] | T,  "The keyword arguments to be passed to the function"]
    ) -> FutureType:
        if not function_origin_is_outside(func) or self.__pool_type == "thread":
            with self.__lock:
                self.add_to_futures(self.__pool.submit(func, *args, **kwargs)) # type: ignore
                return self.__futures[-1]
        else:
            raise NotImplementedError("Cannot run non-root scoped (includes: lambda, closures, or any function in a local scope) functions in a process pool (Use a thread pool instead)")
            with self.__lock:
                self.__structure_pool(non_main_origin=True, non_main_origin_function=func)
                self.__futures.put(self.__pool.submit(run_process_worker_function, *args, **kwargs))
                self.__structure_pool()

    def append_with_post(
        self,
        func:      FunctionType,
        post_func: Annotated[Callable,        "The function to be executed after the future is completed, cannot take any arguments or return any"],
        *args:     Annotated[Iterable[T],     "The arguments to be passed to the function"],
        **kwargs:  Annotated[Mapping[str, T], "The keyword arguments to be passed to the function"]
    ) -> None:
        if not function_origin_is_outside(func) or self.__pool_type == "thread":
            with self.__lock:
                self.add_to_futures(self.__pool.submit(func, *args, **kwargs)) # type: ignore
                self.__futures[-1].add_done_callback(post_func)
        else:
            raise NotImplementedError("Cannot run non-root scoped (includes: lambda, closures, or any function in a local scope) functions in a process pool (Use a thread pool instead)")
            with self.__lock:
                self.__structure_pool(non_main_origin=True, non_main_origin_function=func)
                self.__futures.put(self.__pool.submit(run_process_worker_function, *args, **kwargs))
                self.__futures.queue[-1].add_done_callback(post_func)
                self.__structure_pool()
            
    def map_append(
        self,
        func:       FunctionType,
        *iterables: Annotated[Iterable[T], "The iterables to be passed to the function, must be the same length as the amount of arguments the function takes"]
    ) -> None:
        if not function_origin_is_outside(func) or self.__pool_type == "thread":
            with self.__lock:
                [
                    self.add_to_futures(self.__pool.submit(func, *args)) # type: ignore
                    for args in zip(*iterables)
                ]
        else:
            raise NotImplementedError("Cannot run non-root scoped (includes: lambda, closures, or any function in a local scope) functions in a process pool (Use a thread pool instead)")
            with self.__lock:
                self.__structure_pool(non_main_origin=True, non_main_origin_function=func)
                [
                    self.__futures.put(self.__pool.submit(run_process_worker_function, *args))
                    for args in zip(*iterables)
                ]
                self.__structure_pool()

    def map_append_with_post(
        self,
        func:       FunctionType,
        post_func:  Annotated[Callable, "The function to be executed after the future is completed, cannot take any arguments or return any"],
        *iterables: Annotated[Iterable[T], "The iterables to be passed to the function, must be the same length as the amount of arguments the function takes"]
    ) -> None:
        if not function_origin_is_outside(func) or self.__pool_type == "thread":
            with self.__lock:
                [
                    self.add_to_futures(self.__pool.submit(func, *args)) # type: ignore
                    for args in zip(*iterables)
                ]
                [
                    future.add_done_callback(post_func)
                    for future in self.iter_futures()[-len(iterables):] # type: ignore
                ]
        else:
            raise NotImplementedError("Cannot run non-root scoped (includes: lambda, closures, or any function in a local scope) functions in a process pool (Use a thread pool instead)")
            with self.__lock:
                self.__structure_pool(non_main_origin=True, non_main_origin_function=func)
                [
                    self.__futures.put(self.__pool.submit(run_process_worker_function, *args))
                    for args in zip(*iterables)
                ]
                [
                    future.add_done_callback(post_func)
                    for future in self.iter_futures()[-len(iterables):]
                ]
                self.__structure_pool()

    # ------------------------------ Returners ------------------------------- #
    def map(
        self,
        func:       FunctionType,
        *iterables: Annotated[Iterable[T], "The iterables to be passed to the function, must be the same length as the amount of arguments the function takes"],
        chunksize:  Annotated[int,         "The amount of items to be passed to the function at once"] = 1
    ) -> ResultsType:
        if not function_origin_is_outside(func) or self.__pool_type == "thread":
            with self.__lock:
                if isinstance(self.__pool, ThreadPool):
                    return [
                        x
                        for x in self.__pool.map(func, *iterables, timeout=self.__time_out, chunksize=chunksize)
                    ]
                elif isinstance(self.__pool, ProcessPool):
                    return [
                        x
                        for x in self.__pool.map(func, *iterables, timeout=self.__time_out, chunksize=chunksize)
                    ]
                else:
                    raise NotImplementedError("Cannot run non-root scoped (includes: lambda, closures, or any function in a local scope) functions in a process pool (Use a thread pool instead)")
        else:
            raise NotImplementedError("Cannot run non-root scoped (includes: lambda, closures, or any function in a local scope) functions in a process pool (Use a thread pool instead)")
            with self.__lock:
                self.__structure_pool(non_main_origin=True, non_main_origin_function=func)
                results = [
                    x
                    for x in self.__pool.map(run_process_worker_function, *iterables, timeout=self.__time_out)
                ]
                self.__structure_pool()
                return results

    def execute(
        self,
        *futures: Annotated[Union[Future, Iterable[Future]], "If no arguments are passed, the futures that were appended will be executed, if an iterable of futures is passed, they will be executed, if a single future is passed, it will be executed"]
    ) -> ResultsType:
        if not futures:
            self.__results = [
                future.result(timeout=self.__time_out)
                for future in self.iter_futures()
            ]
            self.clear_futures()
            return self.__results

        if not all(isinstance(future, Future) for future in futures):
            raise TypeError("All items in futures must be of type Future")

        if isinstance(futures[0], Iterable):
            return [
                future.result(timeout=self.__time_out)
                for future in futures[0]
            ]

        if len(futures) == 1 and isinstance(futures[0], Future):
            return futures[0].result(timeout=self.__time_out)


        return [
            future.result(timeout=self.__time_out) # type: ignore
            for future in futures
        ]

    # ---------------------------- Create Future ----------------------------- #
    def create_future(
        self,
        func:     FunctionType,
        *args:    Annotated[Iterable[T], "The arguments to be passed to the function"],
        **kwargs: Annotated[Mapping[str, T], "The keyword arguments to be passed to the function"]
    ) -> FutureType:
        if function_origin_is_outside(func) and self.__pool_type != "thread":
            raise NotImplementedError("Cannot run non-root scoped (includes: lambda, closures, or any function in a local scope) functions in a process pool (Use a thread pool instead)")
        
        return self.__pool.submit(func, *args, **kwargs) # type: ignore

    # ------------------------------- Shutdown ------------------------------- #
    def close(
        self,
        wait: Annotated[bool, "If the pool should wait for all the futures to complete before shutting down"] = True
    ) -> None:
        with self.__lock:
            if self.__pool:
                if wait: self.__pool.shutdown(wait=True)
                if not wait: self.__pool.shutdown(wait=False, cancel_futures=True)
        self.__shutdown = True
        self.clear_futures()

    # ------------------------------- Getters -------------------------------- #
    @property
    def workers(self)   -> WorkerType:   return self.__workers
    @property
    def pool_type(self) -> PoolNameType: return self.__pool_type
    @property
    def futures(self)   -> FuturesType:  return self.__futures
    @property
    def results(self)   -> ResultsType:  return self.__results
    @property
    def is_alive(self)  -> ShutdownType: return not self.__shutdown
    @property
    def pool(self)      -> PoolType:     return self.__pool

    # ------------------------------- Setters -------------------------------- #
    @workers.setter
    def workers(
        self,
        value: WorkerType
    ) -> None:
        with self.__lock:
            self.__workers = value
            self.__structure_pool()

    @futures.setter
    def futures(
        self,
        value: FuturesType
    ) -> None:
        with self.__lock:
            if not isinstance(value, list):
                raise TypeError("Futures must be a list")
            if not all(isinstance(x, Future) for x in value):
                raise TypeError("All items in futures must be of type Future")
            self.clear_futures()
            [
                self.add_to_futures(future) # type: ignore
                for future in value
            ]

    @pool_type.setter
    def pool_type(
        self,
        value: PoolNameType
    ) -> None:
        with self.__lock:
            if value.lower() not in ("thread", "process"):
                raise ValueError("Pool type must be 'thread' or 'process'")
            self.__pool_type = value.lower()
            self.__structure_pool()

    @results.setter
    def results(
        self,
        value: ResultsType
    ) -> None: raise AttributeError("Cannot set results, attribute is read-only")

    @is_alive.setter
    def is_alive(
        self,
        value: ShutdownType
    ) -> None: raise AttributeError("Cannot set is_alive, attribute is read-only")

    @pool.setter
    def pool(
        self,
        value: PoolType
    ) -> None: raise AttributeError("Cannot set pool, attribute is read-only")

if __name__ == "__main__":
    raise NotImplementedError("This module cannot be run as a script, to test it, run the ThreadPool_test.py file")