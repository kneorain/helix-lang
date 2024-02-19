from multimethod import multimethod as __internal__multi_method


n = 0
_ = "_"
class default_value_dict(dict):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.default = self["_"]

    def __getitem__(self, key):
        # Check if the key is a tuple and iterate over the items in the dictionary
        if isinstance(key, tuple):
            for dict_key in self.keys():
                if isinstance(dict_key, tuple) and len(dict_key) == len(key):
                    # Check if all elements match or are wildcards
                    if all(k == dk or dk == "?" or dk == "any" for k, dk in zip(key, dict_key)):
                        return super().__getitem__(dict_key)
            return self.default
        try:
            return super().__getitem__(key)
        except KeyError:
            return self.default
        
    def __setitem__(self, key, value):
        super().__setitem__(key, value)
        
"""return match(n) {
    1 -> "one",
    2 -> "two",
    3 -> "three",
    _ -> "fuck all"
};"""

def something(n) -> str:
    return default_value_dict({
        1: "one",
        2: "two",
        3: "three",
        _: "fuck all"
    })[n]

#print(something(3123))

# for (var i = 0; i < len(arr); i+=1)
# for i in C_For(i = 0,  __c_o_n_d_i_t_i_o_n__='i < len(arr)', __i_n_c_r_e_m_e_n_t__='i+=1'):
#   body

# for (var i, j = 0; i < len(arr); i+=1)
# for i, j in C_For(i = 0, j = 0, __c_o_n_d_i_t_i_o_n__='i < len(arr)', __i_n_c_r_e_m_e_n_t__='i+=1'):
#   body

class C_For:
    def __init__(self, **kwargs):
        # Initialize loop variables
        self.loop_vars = kwargs
        # Extract condition and increment expressions
        self.condition = 'True'
        self.increment = ''
        # Evaluate initial conditions
        [exec(f"{var} = {value}") for var, value in self.loop_vars.items()]

    def __iter__(self):
        return self

    def __next__(self):
        if not self.loop_condition_met:
            raise StopIteration
        current_values = tuple(self.loop_vars.values())
        exec(self.increment, None, self.loop_vars)
        self.loop_condition_met = eval(self.condition, None, self.loop_vars)
        return current_values if len(current_values) > 1 else current_values[0]
    
    def set_con(self, condition):
        self.condition = condition
        self.loop_condition_met = eval(self.condition, None, self.loop_vars)
        return self
    
    def set_inc(self, increment):
        self.increment = increment.replace('++', '+= 1').replace('--', '-= 1').replace('+*', '*= 1').replace('-*', '*= -1').replace('/-', '/ -1').replace('/*', '*= 1')
        return self

arr = [1, 2, 3]
for i, j in C_For(i = int(0), j = int(0)).set_con('i < len(arr)').set_inc('i ++ ; j ++'):
    print(i, j)

@__internal__multi_method
def some_function(arr: list[str]) -> list:
    arr : list[int] = [ 1 , 2 , 3 ]
    for i in arr:
        print ( i )
    del i

    for i in C_For(i = int(0)).set_con('i < 10').set_inc('i ++ '):
        print ( i )
    del i

    return arr

print(some_function([ "1" , "2" , "3" ]))