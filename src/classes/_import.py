if __name__ == '__main__':
    from keyword_abstraction import KeywordAbstraction
    from namespace_abstraction import NamespaceAbstraction as Namespace

from typing import override
from threading import Thread
from time import time

"""
All types of valid input lines:
  include "add" from "test.c";
  include "add" as "c_add" from "test.c" ;
  include { "add", "sub" } from "test.c" using namespace;
  include { "add" as "c_add" , "sub" as "c_sub" } from "test.c";
  include { "somepy" } from "test.py";
  include { "arange" } from "numpy";
  include { "arange" as "np_arange" } from "numpy" using namespace;
  // can go for any number of arguments
  
  so this transpiles like so, any c or c++ file:
  # example: include "add" from "test.c";
  # output: class test:\n    add = __import_c__("test.c", "add")
  
  # example: include "add" as "c_add" from "test.c" ;
  # output: c_add = __import_c__("test.c", "add")

  # example: include { "add", "sub" } from "test.c" using namespace;
  # output: add = __import_c__("test.c", "add")\nsub = __import_c__("test.c", "sub")
"""
class Import[T](KeywordAbstraction):
    __lines:     list[str] = []
    __namespace: Namespace = None
    __blocked:   bool      = False
    
    def timeout(self) -> None:
        start = time()
        self.__blocked = True
        a = Thread(target=self.__process)
        a.start()
        while time() - start < 10:
            pass
        else:
            a.join()
        self.__blocked = False
    
    
    @override
    def __init__(self, line: list[str], namespace: Namespace):
        super().__init__(line, namespace)
        self.__blocked = True
        self.__lines = line
        self.__namespace = namespace
        self.timeout()
        
    @override
    def __process(self) -> None:
        pass
    
    @override
    def __str__(self) -> str:
        pass
    
    @override
    def error(self) -> str:
        pass
    
    def wait(self) -> None:
        while self.__blocked:
            pass
    
    def __repr__(self) -> str:
        return f"Import({self.line}, {self.namespace})"


test_data = [['<\\t:0>', 'include', '"add"', 'from', '"test.c"'], ['<\\t:0>', 'fn', 'factorial', '(', 'n', ':', 'int', ')', '->', 'int', ':'], ['<\\t:1>', 'if', '(', 'n', '>', '1', ')', ':'], ['<\\t:2>', 'return', 'n', '*', 'factorial', '(', 'n', '-', '1', ')'], ['<\\t:1>', 'else', ':'], ['<\\t:2>', 'return', '1'], ['<\\t:2>', 'a', ':', 'map', '=', '{', '{', '1', ':', '2', '}', ':', '3', '}'], ['<\\t:1>', 'for', '(', 'var', 'i', ';', 't', '>=', '0', ';', 'i', '<', '10', ';', 'i', '++', ')', ':'], ['<\\t:2>', 'print', '(', 'i', ')'], ['<\\t:1>', 'return', 'switch', '(', 'n', ')', '{', '0', '->', '1', ',', '_', '->', 'n', '*', 'factorial', '(', 'n', '-', '1', ')', '}'], ['<\\t:0>', 'fn', 'main', '(', ')', ':'], ['<\\t:1>', 'n', ':', 'int', '?'], ['<\\t:1>', 'n', '=', 'input', '(', '"Enter a positive integer: "', ')', '.', 'to_int', '(', ')'], ['<\\t:1>', 'print', '(', '"Factorial of "', '+', 'n', '+', '" = "', '+', 'factorial', '(', 'n', ')', ')'], ['<\\t:0>', 'interface', 'Legs', ':'], ['<\\t:1>', 'fn', 'walk', '(', ')', '->', 'string', '<\\r1>'], ['<\\t:0>', 'interface', 'Ears', ':'], ['<\\t:1>', 'fn', 'listen', '(', ')', '->', 'string', '<\\r1>'], ['<\\t:0>', 'interface', 'Animal', 'impl', 'Legs', ',', 'Ears', ':'], ['<\\t:1>', 'fn', 'speak', '(', ')', '->', 'string', '<\\r1>'], ['<\\t:1>', 'fn', 'eat', '(', ')', '->', 'string', '<\\r1>'], ['<\\t:1>', 'fn', 'sleep', '(', ')', '->', 'int', '<\\r1>'], ['<\\t:0>', 'class', 'Dog', '::', 'Animal', ':'], ['<\\t:1>', 'fn', 'speak', '(', ')', '->', 'string', ':'], ['<\\t:2>', 'return', '"Woof!"'], ['<\\t:1>', '#', '[', 'override', ']', 'fn', 'eat', '(', ')', '->', 'string', ':'], ['<\\t:2>', 'return', '"The dog is eating."'], ['<\\t:1>', 'fn', 'sleep', '(', ')', '->', 'int', ':'], ['<\\t:2>', 'return', '8'], ['<\\t:0>', 'class', 'GoldenRetriever', '::', 'Dog', ':'], ['<\\t:1>', 'fn', 'speak', '(', ')', '->', 'string', ':'], ['<\\t:2>', 'return', '"Bark!"'], ['<\\t:2>', 'for', '(', 'var', 'i', ';', 'int', '=', '0', ';', 'i', '<', '10', ';', 'i', '++', ')', ':'], ['<\\t:3>', 'print', '(', 'i', ')'], ['<\\t:1>', '...']]