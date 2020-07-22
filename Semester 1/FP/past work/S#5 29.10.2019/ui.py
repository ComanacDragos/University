from service import Service

class UI:

    #can ui do it s job without service
    # no => it does not make sense to create a ui without having Service
    def __init__(self, service):
        self._Service = Service


    def addStar (self):
        # read star location, mass , magnitude
        # check if it valid
        # call service.addstar(newStar)
        newStar = None
        self._service.addstar(newStar)
        pass

    def sortStars (self):
        pass

    def start (self):
        print('Welcome to star catalogue!')
        # print menu, read user choice, etc.
        # call addStar and sortStar methods
s = Service()

ui = UI(s)

ui.start()