from menu_based_ui import *
from command_based_ui import *

def start ():
    while True:
        choice = '''
1. Command based user interface
2. Menu-based user interface
3. Exit
        '''
        print(choice)
        choice = input(">")
        if choice == "1":
            command_based()
        elif choice == "2":
            menu_based()
        elif choice == "3":
            return 
        else:
            print("\nInvalid command\n")
start() 