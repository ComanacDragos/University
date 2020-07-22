def empty ():
    return []

def create_animal (code, name, type, species):
    l = empty()
    l.append(code)
    l.append(name)
    l.append(type)
    l.append(species)
    return l

def get_code (animal):
    return animal[0]

def get_name (animal):
    return animal[1]

def get_type (animal):
    return animal[2]

def get_species (animal):
    return animal[3]

def set_type (animal, value):
    animal[2] = value

def set_species (animal, value):
    animal[3] = value