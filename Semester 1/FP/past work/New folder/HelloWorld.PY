def create_number (real,imaginary):
    return [real,imaginary]

def get_real(number):
    return number[0]

def get_imaginary(number):
    return number[1]

def set_real(number,value):
    number[0] = value

def set_imaginary(number,value):
    number[1] = value

def menu ():
    print("1. Read number")
    print("4. Exit")

def init_list ():
    numberList = []
    numberList.append([1,2])
    numberList.append([0.5,3])
    return numberList



def start():
    numberList = init_list
    while True:
        menu()
        choice = input(">")
        if choice == "4":
            return 


start()
        
