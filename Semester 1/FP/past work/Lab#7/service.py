from domain import *
def add_flight (flights, flight):
    '''
    Function adds a flight to the list of flights
    Input:
        flights - the list of flights
        flight - the flight to be added
    Exception:
        - duration is less than 20 min
        - code, departure or destination city has less than 3 characters
    If an exception is raised the flight will not be added
    '''
    if len(get_code(flight)) < 3 or len(get_departureCity(flight)) < 3 or len(get_destinationCity(flight)) < 3:
        raise ValueError
    
    try:
        duration = int(get_duration(flight))
        if duration < 20:
            raise ValueError
    except:
        raise ValueError

    flights.append(flight)

def test_add ():
    '''
    Tests the add feature
    '''
    l = empty()
    flight1 = create_flight("123", "40", "asdasf", "asfas")
    add_flight(l, flight1)
    assert l[0] == create_flight("123", "40", "asdasf", "asfas")

    try: 
        flight2 = create_flight("2", "40", "asdasf", "asfas")
        add_flight(l,flight2)
        assert False
    except ValueError:
        assert True
    
    try: 
        flight2 = create_flight("123", "40", "sf", "asfas")
        add_flight(l,flight2)
        assert False
    except ValueError:
        assert True

    try: 
        flight2 = create_flight("123", "40", "asfasdas", "as")
        add_flight(l,flight2)
        assert False
    except ValueError:
        assert True

    try: 
        flight2 = create_flight("123", "10", "asfasdas", "asasfads")
        add_flight(l,flight2)
        assert False
    except ValueError:
        assert True

test_add()


def change_duration (flights, code, duration):
    try:
        dur = int(duration)
    except:
        raise ValueError
    for i in flights:
        if code == get_code(i):
            set_duration(i, duration)


def change_dest (flights, initDest, newDest):
    if len(newDest) < 3:
        raise ValueError

    for i in flights:
        if initDest == get_destinationCity(i):
            set_destinationCity(i, newDest)

def list_flights (flights, city):
    l = empty()
    for i in flights:
        if city == get_departureCity(i):
            set_duration(i, int(get_duration(i)))
            l.append(i)
    l = sorted (l, key = get_duration)
    return l