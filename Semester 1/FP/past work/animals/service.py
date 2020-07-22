from domain import *


def add_animal (animals, animal):
    '''
    '''
    code = get_code(animal)
    for i in animals:
        if get_code(i) == code:
            raise ValueError

    if len(get_code(animal)) == 0 or len(get_name(animal)) == 0 or len(get_species(animal)) == 0 or len(get_type(animal)) == 0: 
        raise TypeError

    animals.append(animal)

def init_animals ():
    l = empty()
    add_animal(l, create_animal("1", "Bob3","carnivore", "Lion" ))
    add_animal(l, create_animal("2", "Bob6","herbivore", "Crocodile" ))
    add_animal(l, create_animal("3", "Bob2","carnivore", "Lion" ))
    add_animal(l, create_animal("4", "Bob4","carnivore", "Bird" ))
    return l

def change_type (animals, code, type):
    '''
    '''
    for i in animals:
        if get_code(i) == code:
            set_type(i, type)
            return
    raise ValueError

def change_species (animals, species, type):
    '''
    '''
    if len(species) == 0 or len(type) == 0:
        raise ValueError
    ok = 0
    for i in animals:
        if get_species(i) == species:
            change_type(animals, get_code(i), type)
            ok = 1
    if ok == 0:
        raise TypeError



def list_animals_sorted (animals, type):
    '''
    '''
    l = empty()
    for i in animals:
        if get_type(i) == type:
            l.append(i)
    l = sorted(l, key = get_name)
    l = sorted(l, key = get_code)
    return l