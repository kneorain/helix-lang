
def hello_from_python() -> None:
    print("hello from python")


def test_args(a: int, b: int) -> int:
    print("a: ", a)
    return a

def test_kwargs(a: int, b: int, c: int = 3) -> int:
    print("------- kwargs -------")
    print("a: ", a)
    print("c: ", c)
    print("----------------------")
    return a + b + c

