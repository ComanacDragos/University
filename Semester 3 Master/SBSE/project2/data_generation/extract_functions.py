import os.path
import re
import sys

from utils import open_json, to_json
from pathlib import Path


def remove_first_indent(method_lines):
    signature = method_lines[0]

    count = 0
    for char in signature:
        if char == ' ':
            count += 1
        else:
            break

    return [x[count:] for x in method_lines]


def extract_name(signature):
    start = signature.find('(')
    return signature[:start].split()[-1]


def extract_java_methods(file_path):
    with open(file_path) as file:
        java_code = file.readlines()

    methods = {}
    method = []
    bracket_count = 0

    for line in java_code:
        if " class " in line:
            continue
        if not bracket_count and re.match(r'^(public|private|protected|static|final|synchronized|abstract).*{$',
                                          line.strip()):
            method = [line]
            bracket_count = 1
        elif bracket_count:
            method.append(line)
            for char in line:
                if char == "{":
                    bracket_count += 1
                elif char == "}":
                    bracket_count -= 1
                    if bracket_count == 0:
                        methods[extract_name(method[0])] = ''.join(remove_first_indent(method))
                        break

    return methods


def extract_python_methods(file_path):
    with open(file_path) as file:
        python_code = file.readlines()

    methods = {}
    method = []

    for line in python_code:
        if 'def' in line:
            if len(method):
                methods[extract_name(method[0])] = ''.join(remove_first_indent(method))
            method = [line]
        else:
            if len(method):
                method.append(line)
    if len(method):
        methods[extract_name(method[0])] = ''.join(remove_first_indent(method))
    return methods


def write_methods(file, methods, output):
    methods_dir = output / file.split(".")[0]
    if not os.path.exists(methods_dir):
        os.makedirs(methods_dir)

    name_to_path = {}
    for name, body in methods.items():
        method_path = methods_dir / f"{name}.txt"
        try:
            with open(method_path, 'w') as writer:
                writer.write(body)
                name_to_path[name] = Path(file.split(".")[0]) / f"{name}.txt"
        except OSError:
            continue
    return name_to_path


if __name__ == "__main__":
    # try:
    #     input_file = "data/processed/thealgorithms/java/audiofilters/IIRFilter.java"
    #     methods = extract_java_methods(input_file)
    #     for method in methods:
    #         print("=" * 100)
    #         print(method)
    # except FileNotFoundError:
    #     print("File not found.")
    # print("@"*100)
    # try:
    #     input_file = "data/processed/thealgorithms/python/audiofilters/IIRFilter.py"
    #     methods = extract_python_methods(input_file)
    #     for method_name, body in methods.items():
    #         print("=" * 100)
    #         print(method_name)
    #         print(body)
    # except FileNotFoundError:
    #     print("File not found.")

    mapping = open_json(sys.argv[1])
    method_input = Path(sys.argv[2])
    method_output = Path(sys.argv[3])
    mapping_output = sys.argv[4]

    method_mapping = {}

    for java_file, python_file in mapping.items():
        print(java_file)
        java_methods = extract_java_methods(method_input / java_file)
        name_to_java_paths = write_methods(java_file, java_methods, method_output)
        java_names = set(name_to_java_paths.keys())

        if python_file:
            print(python_file)
            python_methods = extract_python_methods(method_input / python_file)
            name_to_python_paths = write_methods(python_file, python_methods, method_output)
            python_names = set(name_to_python_paths.keys())

            for name in java_names.intersection(python_names):
                method_mapping[str(name_to_java_paths[name])] = str(name_to_python_paths[name])

            java_file_class_name = Path(java_file).stem
            if '__init__' in name_to_python_paths and java_file_class_name in name_to_java_paths:
                method_mapping[str(name_to_java_paths[java_file_class_name])] = str(name_to_python_paths['__init__'])
        else:
            for path in name_to_java_paths.values():
                method_mapping[str(path)] = ''

    to_json(method_mapping, mapping_output)

