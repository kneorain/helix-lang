n = 0
_ = "_"
class default_value_dict(dict):
    # same as a dict but if there a key of _ then if a key is not found it will return the value of _
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.default = self[_]
        
    def __getitem__(self, key):
        try:
            return super().__getitem__(key)
        except KeyError:
            return self.default
        
    def __setitem__(self, key, value):
        super().__setitem__(key, value)
        

