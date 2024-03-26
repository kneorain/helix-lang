# Installation

### create a virtual environment
### install the requirements
### run helix.py with a test file

<<<<<<< HEAD
=======
- NOTE: Helix is written in Python 3.12 and does not support Python 2.x or any version of Python 3.x below 3.12. (Maybe it does, I haven't tested it.)
- Helix is functional (but quite unstable). All testing has only been done on Windows,
  it may or may not work on other operating systems.

>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
python helix.py syntax/test.hlx
deactivate # to exit the virtual environment when done
```
