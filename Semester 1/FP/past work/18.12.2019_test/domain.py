class Address:
    def __init__(self, Id, Name, X, Y):
        self.id = Id
        self.name = Name
        self.x = X
        self.y = Y

    def __str__(self):
        return "For address with id: " + str(self.id) + " we have: " + str(self.name) + ", (" + str(self.x) + ", " +str(self.y) + ")"

class Driver:
    def __init__(self, Name, X, Y):
        self.name = Name
        self.x = X
        self.y = Y

    def __str__(self):
        return "For " + str(self.name) + " the position is: (" + str(self.x) + ", " + str(self.y) + ")"


class driver_distance:
    def __init__(self, driver, distance):
        self.driver = driver
        self.distance = distance

    def __str__(self):
        return str(self.driver) + " and the disntace is: " + str(self.distance)

    def __lt__(self, other):
        return self.distance < other.distance