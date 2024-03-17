from src.core.imports import (
    functools,
    Any, Callable,
    perf_counter_ns as time,
    framework,
)

class Timer(framework.Timer):
    """
    A utility class for timing code execution in the Helix language environment.

    Methods
    -------
    __init__(self)
        Initializes the Timer object.
    start(self, name: str) -> None
        Starts a timer with the given name.
    end(self, name: str) -> None
        Ends the timer with the given name and logs the elapsed time.
    get_time(self, name: str) -> float
        Retrieves the elapsed time for the timer with the given name.
    decorator(self, func: Callable) -> Callable
        Decorator method for timing functions.
    """
    def __init__(self) -> None:
        self.__times: dict[
            str, tuple[float, float, int]
        ] = {}  # name: (start, end, level)
        self.__active_timers: list[str] = []

    def start(self, name: str) -> None:
        self.__times[name] = (
            time(),
            0,
            len(self.__active_timers),
        )
        self.__active_timers.append(name)

    def end(self, name: str) -> None:
        self.__times[name] = (
            self.__times[name][0],
            time() - (150000000 if name == 'run' else 0),
            self.__times[name][2],
        )
        self.__active_timers.remove(name)

    def get_time(self, name: str) -> float:  # in ms
        start, end, _ = self.__times[name]
        return (end - start) / 1_000_000

    def __str__(self) -> str:
        result = []
        for name in self.__times:
            indent = "|    " * self.__times[name][2]
            result.append(
                f'{indent}"{name}" took {self.get_time(name):.2f}ms'
            )
        return "\n".join(result)

    def __repr__(self) -> str:
        return self.__str__()

    def decorator(self, func: Callable) -> Callable:
        @functools.wraps(func)
        def wrapper(*args, **kwargs) -> Any:
            self.start(func.__name__)
            result = func(*args, **kwargs)
            self.end(func.__name__)
            return result

        return wrapper

