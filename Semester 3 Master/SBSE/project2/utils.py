import json


def to_json(obj, file):
    json_obj = json.dumps(obj, indent=4)
    with open(file, "w") as f:
        f.write(json_obj)


def open_json(file):
    with open(file) as f:
        return json.load(f)
