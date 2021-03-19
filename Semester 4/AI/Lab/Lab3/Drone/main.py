from Drone.UI.GUI import *

if __name__ == '__main__':
    # GUI()
    myService = Service()
    for i in range(200):
        myService.solver()
    print(myService.computeStats())
