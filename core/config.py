import pickle, os
from argparse import Namespace

def save_config(config: Namespace):
    with open(f"cache{os.sep}shared.data", "wb") as config_file:
        pickle.dump(config, config_file)
        
def load_config() -> Namespace:
    with open(f"cache{os.sep}shared.data", "rb") as config_file:
        return pickle.load(config_file)

def delete_config():
    os.remove(f"cache{os.sep}shared.data")
