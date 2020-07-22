class Route:
    def __init__(self, Id, Lenght):
        self.id = Id
        self.lenght = Lenght

    @property
    def id (self):
        return self.Id

    @id.setter
    def id (self, value):
        self.Id = value

    @property
    def lenght (self):
        return self.Lenght

    @lenght.setter
    def lenght (self, value):
        self.Lenght = value

    def __str__ (self):
        return "Route code: " + str(self.id) + "," + str(self.lenght)

class Bus:
    def __init__(self, Id, RouteCode, Model, TimesUsed):
        self.id = Id
        self.routeCode = RouteCode
        self.model = Model
        self.timesUsed = TimesUsed

    def __str__(self):
        return "For bus: " + str(self.id) + ", the route code is: " + str(self.routeCode) + ", the model is: " + str(self.model) + ", the number of times used is: " + str(self.timesUsed)


class a:
    def __init__(self, a1, a2):
        self.a1 = a1
        self.a2 = a2


obj = a(1,2)

print(obj.a1, obj.a2)
obj.a1 = 3
print(obj.a1, obj.a2)

