import importlib
from domain import *

'''
specification
tests 
exceptions
simple feature driven development
undoo
modular programming


menu driven circles program
    - add a circle (radius > 0, in the (+,+) first quadrant)
    - delete circles with radius < r
    - show circles
    - undo?
    - exit
'''

'''
here everything that writes/reads to the user
NB!
only module where input/print/call functions that do that


ui -> functions
ui -> domain
functions -> domain

'''



def add_circle_ui ():
    x = int(input("x="))
    y = int(input("y="))
    r = int(input("r="))
    add_circle(circles,x,y,r)


def show_circles_ui ():
    pass

def show_circles_ui(circles):
    for c in circles:
        print("("+ str(get_x(c))+","+str(get_y(c))+", r="+str(get_r(c)))

def print_menu ():
    print("")
    print("1. Add a circle")
    print("3. Show circles")
    print("0.Exit")
    print("")

def start ():
    circle = test_init()
    # command design pattern
    commands = {
        '1' : add_circle_ui,
        '3' : show_circles_ui
    }
    while True:
        print_menu()
        cmd = input("command: ")
        if cmd == '0':
            return
        if cmd in commands.keys():
            commands[cmd](circle)
        else:
            print("Bad command or file name")
    pass

start()