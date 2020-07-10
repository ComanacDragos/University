from UI import *
import sys, threading

class Main:
    def __init__(self):
        self.graph = DoubleDictGraph()
        self.controller = Controller(self.graph)
        self.UI = UI(self.controller)
        self.UI.start()

sys.setrecursionlimit(400000)
threading.stack_size(2**27)

def run():
    Main()
#threading.Thread(target=run).start()
run()