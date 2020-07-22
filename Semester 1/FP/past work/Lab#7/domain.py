def empty ():
    return []


def create_flight (code, duration, departureCity, destinationCity):
    l = empty()
    l.append(code)
    l.append(duration)
    l.append(departureCity)
    l.append(destinationCity)
    return l

def get_code (flight):
    return flight[0]

def get_duration (flight):
    return flight[1]

def get_departureCity (flight):
    return flight[2]

def get_destinationCity(flight):
    return flight[3]

def set_duration (flight, value):
    flight[1] =value

def set_destinationCity  (flight, value):
    flight[3] = value

def init_flights ():
    flights = empty()
    flights.append(create_flight("B01", "50", "Cluj-Napoca", "London"))
    flights.append(create_flight("B02", "40", "Botosani", "London"))
    flights.append(create_flight("B03", "70", "Cluj-Napoca", "Iasi"))
    flights.append(create_flight("B04", "30", "Botosani", "London"))
    flights.append(create_flight("B05", "25", "Cluj-Napoca", "Paris"))
    return flights