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

print(something(3123))