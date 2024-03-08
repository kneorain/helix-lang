from helix import HelixProcess
helix_import = HelixProcess.__hook_import__("syntax/test.hlx")



a: list[int] = [1, 2, 3, 4, 5]
b: list[str] = ["a", "b", "c", "d", "e"]


print(helix_import.is_typeof(b, list[str]))