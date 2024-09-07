import os
import sys
from concurrent.futures import ProcessPoolExecutor
from time import perf_counter_ns as time

IGNORED_DIRECTORIES = ('.git', '.vscode', '__pycache__', 'venv', 'libs', 'build', 'assets', '.xmake', '.github', '.vs', '.cache')
IGNORED_EXTENSIONS  = ('.zip', '.exe', '.dll', '.so', '.a', '.o', '.lib', '.obj', '.bin', '.pyc', '.pyd', '.pyo', '.pyi', '.pyw', '.war')

def process_file(file_path):
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
            file_extension = file_path.split('.')[-1]
            return file_extension, len(lines)
    except (OSError):
        print(f"Skipping {file_path} due to permission error or OS error.")
        return None

def count_lines(directory):
    print("-" * 75 + "\n")
    print(f"Counting lines in {directory} and its subdirectories...")
    print("\n" + "-" * 75 + "\n")

    lines_by_extension = dict()
    
    files = []

    for root, _, filenames in os.walk(directory):
        
        if any(ignored_dir in root for ignored_dir in IGNORED_DIRECTORIES):
            continue

        for filename in filenames: # Ignored files (also files with no extension)
            if any(ignored_ext in filename for ignored_ext in IGNORED_EXTENSIONS):
                continue

            if '.' not in filename:
                continue

            print(f"Processing {filename}")
            files.append(os.path.join(root, filename))
    
    for file in files:
        result = process_file(file)
        if result is not None:
            file_extension, lines = result
            lines_by_extension[file_extension] = lines_by_extension.get(file_extension, 0) + lines

    return sum(lines_by_extension.values()), dict(sorted(lines_by_extension.items(), key=lambda item: item[1], reverse=True))

def main():
    global IGNORED_DIRECTORIES
    
    if len(sys.argv) != 2:
        directory_path = os.getcwd()
    else:
        directory_path = sys.argv[1]
    
    if len(sys.argv) > 2:
        IGNORED_DIRECTORIES += tuple(sys.argv[2:])
    
    result = count_lines(directory_path)

    print("\n" + "-" * 75 + "\n")
    print(f"\u001b[32mTotal lines: {result[0]}\u001b[0m in {directory_path}")
    print("\n" + "-" * 75 + "\n")
    
    [print(f"*.{ext} lines: {lines}") for ext, lines in result[1].items()]
    print("\n" + "-" * 75)

if __name__ == "__main__":
    start = time()
    main()
    end = time()
    print(f"Time taken: {((end - start) / 1_000_000):,.2f} ms")