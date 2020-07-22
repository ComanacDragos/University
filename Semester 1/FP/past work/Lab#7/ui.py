from service import *

def menu ():
    menu = '''
1. Add flight
2. Change duration of flight
3. Change destionation city of all flights with a given destination city
4. List flights with given departure city
5. Exit  
    '''
    print(menu)

def print_list (flights):
    count = 0
    for i in flights:
        count += 1
        print(str(count) + ". " + str(get_code(i)) + " " + str(get_duration(i) )+  " " + str(get_departureCity(i)) + " " + str(get_destinationCity(i)))

def ui_add (flights):
    print("")
    code = input("Give code: ").strip("")
    duration = input("Give duration: ").strip("")
    departureCity = input("Give departure city: ").strip("")
    destinationCity = input("Give destination city: ").strip("")
    print("")

    flight = create_flight(code, duration, departureCity, destinationCity)

    try:
        add_flight(flights, flight)
    
    except ValueError:
        print("Invalid data")

def ui_change_duration (flights):
    print("")
    code = input("Give code: ").strip(" ")
    duration = input ("Give new duration: ").strip(" ")
    print("")
    try:
        change_duration(flights, code, duration)
    except:
        print("Duration must be a number")

def ui_change_dest (flights):
    print("")
    initDest = input("Give initial destination city: ").strip(" ")
    newDest = input("Give new destination city: ").strip(" ")
    print("")
    try:
        change_dest(flights, initDest, newDest)
    except ValueError:
        print("Invalid destination")

def ui_list (flights):
    city = input("Give departure city: ").strip(" ")
    print_list(list_flights(flights, city))

def start():
    flights = init_flights()
    commands = {
        "1" : ui_add,
        "2" : ui_change_duration,
        "3" : ui_change_dest,
        "4" : ui_list,
        "6" : print_list
        
    }
    while True:
        menu()
        choice = input ("Give choice: ").strip("")
        if choice in commands:
            commands[choice](flights)
        elif choice == "5":
            return
        else:
            print("Invalid command")

start()
