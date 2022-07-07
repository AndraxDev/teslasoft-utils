import json
settings = open("settings.json", "r")
raw_data = settings.read().replace("\\", "\\\\")
dcparams = json.loads(raw_data)

def get_param(value):
    return dcparams[value]

def load_settings():
    return dcparams
