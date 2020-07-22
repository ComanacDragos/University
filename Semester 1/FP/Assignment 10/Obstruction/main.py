from Obstruction.consoleUI.UI import *

class Main:
    def __init__(self):
        self.UI = UI()
        self.UI.ui_start_console()
        while True:
            choice = input("Want to play again?(1/0): ").strip()
            if choice == "0":
                return
            elif choice == "1":
                self.UI = UI()
                self.UI.ui_start_console()
            else:
                print("Invalid command")
Main()
