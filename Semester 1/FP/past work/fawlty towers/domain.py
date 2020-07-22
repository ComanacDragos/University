from datetime import date

class Room:
    def __init__(self, Number, Type, State = 0):
        self.number = Number
        self.type = Type
        self.state = State

    @staticmethod
    def is_natural (n):
        try:
            n = float(n)
        except:
            raise ValueError("A string was given")
        else:
            if n != int(n) or n <= 0:
                raise ValueError("A natural number must be given")

    @property
    def state (self):
        return self.State

    @state.setter
    def state (self, value):
        self.State = value

    def set_state (self):
        self.state = 1

    def clear_state (self):
        self.state = 0

    @property
    def number (self):
        return self.Number

    @number.setter
    def number(self, value):
        self.is_natural(value)
        value = int(value)
        self.Number = value

    @property
    def type (self):
        return self.Type

    @type.setter
    def type (self, value):
        self.is_natural(value)
        value = int(value)
        if value not in [1,2,4]:
            raise ValueError("Type not 1,2,4")
        self.Type = value

    def __str__(self):
        return "Room number: " + str(self.number) + ", type: " + str(self.type) + ", state: " + str(self.state)

class Reservation:
    def __init__(self, ReservationNumber,RoomNumber, Name,  NrGuests, Arrival, Departure):
        self.Id = ReservationNumber
        self.name = Name
        self.roomNumber = RoomNumber
        self.guests = NrGuests
        self.arrival = Arrival
        self.departure = Departure

    @staticmethod
    def is_natural(n):
        try:
            n = float(n)
        except:
            raise ValueError("A string was given")
        else:
            if n != int(n) or n <= 0:
                raise ValueError("A natural number must be given")

    def __str__(self):
        return str(self.Id) + ', ' +str(self.roomNumber) + ', ' +  str(self.name) + ', '  + str(self.guests) + ', ' + str(self.arrival) + ', ' +str(self.departure)

