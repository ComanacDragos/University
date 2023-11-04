import os.path
import sys

from utils import open_json
import re
from pathlib import Path

mapping = open_json(sys.argv[1])
original_dir = Path(sys.argv[2])
processed_dir = Path(sys.argv[3])

print("original_dir", original_dir)
print("processed_dir", processed_dir)

java_patterns = [
    "^package",
    "^import",
    "^/\*\*",
    "^\*",
    "^//",
    "^/\*"
]

python_patterns = [
    "^#",
    '^"""',
    "^import"
]


def process_file(file_path, patterns):
    with open(original_dir / file_path, errors='ignore') as f:
        new_lines = []
        for line in f.readlines():
            stripped_line = line.strip()
            if len(stripped_line) > 0:
                ok = True
                for pattern in patterns:
                    if re.search(pattern, stripped_line) is not None:
                        ok = False
                        break
                if ok:
                    new_lines.append(line)

        if len(new_lines) > 0:
            file_dir = processed_dir / os.path.dirname(file_path)
            if not os.path.exists(file_dir):
                os.makedirs(file_dir)
            with open(processed_dir / file_path, 'w') as writer:
                writer.write("".join(new_lines))


for java_file, python_file in mapping.items():
    print(java_file)
    process_file(java_file, java_patterns)
    if python_file:
        print(python_file)
        process_file(python_file, python_patterns)

