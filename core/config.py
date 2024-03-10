import os
import toml
from argparse import Namespace
from core.panic import panic

CACHE: dict[str, Namespace] = {}
CONFIG_PATH = ".helix/config.toml"


def save_config(config: Namespace):
    """Save the config to the config file

    Args:
        config (Namespace): The config to save
    """
    with open(CONFIG_PATH, "w") as file:
        toml.dump(dict(config), file)


def load_config(path: str = CONFIG_PATH) -> Namespace:
    if path in CACHE:
        return CACHE[path]

    if path != CONFIG_PATH:
        (
            panic(
                FileNotFoundError(
                    f"Could not find config file at {path}"
                ),
                no_lines=True,
                file=path,
            )
            if not os.path.exists(path)
            else None
        )

    with open(path, "r") as file:
        data = Namespace(**toml.load(file))
        CACHE[path] = data
        return data


def set_config_path(path: str) -> None:
    global CONFIG_PATH
    CONFIG_PATH = path
