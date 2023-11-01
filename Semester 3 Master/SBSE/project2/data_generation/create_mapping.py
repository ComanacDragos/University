from pathlib import Path
import os
import sys
from utils import to_json

root = Path(sys.argv[1])
output = sys.argv[2]

print("Root", root)
print("Output", output)


java_files = []
java_to_python = {}

for code_dir in [x for x in os.listdir(root) if x != 'csvs']:
    print(code_dir)
    w = os.walk(str(root / code_dir / 'java'))
    for (dirpath, dirnames, filenames) in w:
        for filename in filenames:
            java_files.append(str(Path(dirpath[len(str(root))+1:]) / filename))


for java_file in java_files:
    python_file = java_file.replace('java', 'python', 1).replace('java', 'py', -1)
    if os.path.exists(root / python_file):
        java_to_python[java_file] = python_file
    else:
        java_to_python[java_file] = ""

python_files = [x for x in java_to_python.values() if x != '']
print(java_files[0])
print(python_files[0])
print("Java: ", len(java_to_python.keys()), "Python: ", len(python_files))

to_json(java_to_python, output)




