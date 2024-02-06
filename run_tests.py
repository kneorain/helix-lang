# go thru all the files in the test directory and run them

import os
import subprocess
import sys

def run_tests():
    test_dir = os.path.join(os.getcwd(), "tests")
    for file in os.listdir(test_dir):
        if file.endswith(".py"):
            print(f"Running {file}")
            subprocess.run([sys.executable, os.path.join(test_dir, file)])
            
if __name__ == "__main__":
    run_tests()