from service import *

def menu ():
    menu  = '''
1. Add animal
2. Change type of an animal
3. Change type of a species
4. Show all animals with a given type sorted by name
5. Exit
'''
    print(menu)

def list_animals (animals):
    count = 0 
    for i in animals:
        count += 1
        print(str(count) + ". " + "The code is " + get_code(i) + " , the name is " + get_name(i) + " the species is " + get_species(i) + " and the type is " + get_type(i))
        
def ui_add (animals):
    '''
    '''
    print("")
    code = input("Give code: ").strip(" ")
    name = input("Give name: ").strip(" ")
    species = input("Give species: ").strip(" ")
    typ = input("Give type: ").strip(" ")
    print("")
    try:
        animal = create_animal(code,name,typ,species)
        add_animal(animals, animal)
        print("The animal was added succesfully")
    except ValueError:
        print("There aleready exists an animal with the given code")
    except TypeError:
        print("One of the fields is void")

def ui_change_type (animals):
    '''
    '''
    print("")
    code = input("Give code: ").strip(" ")
    type = input("Give type: ").strip("")
    print("")
    try:
        change_type(animals, code, type)
        print("The type was succesfully changed")
    except ValueError:
        print("There is no animal with given code")

def ui_change_species (animals):
    '''
    '''
    print("")
    species = input("Give species: ").strip(" ")
    type = input("Give new type: ").strip(" ")
    print("")
    try:
        change_species(animals, species, type)
        print("The types were changed succesfully")
    except ValueError:
        print("One of the filds is void")
    except TypeError:
        print("There is no animal with given species")

def ui_list (animals):
    '''
    '''

    print("")
    type = input("Give type: ").strip(" ")
    l = list_animals_sorted(animals, type)
    if len(l) == 0:
        print("There are no animals with given type")
    else:
        list_animals(l)
   

def start ():
    animals = init_animals()
    commands = {
        "1" : ui_add,
        "2" : ui_change_type,
        "3" : ui_change_species,
        "4" : ui_list,
        "6" : list_animals
    }
    while True:
        menu()
        choice = input(">").strip(" ")
        if choice in commands:
            commands[choice](animals)
        elif choice == "5":
            return 
        else:
            print("\nInvalid command")

start()
