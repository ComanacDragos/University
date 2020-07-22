'''
here you code everything about the domain

domain = =circles,q,z,expenses,transactions, contest results(=problem domain)
'''

# c = [0,0,1] unit circle not valid in out program
def f ():
    print("ok!")
def create_circle (x,y,r):
    '''
    creates a circle centered in (x,y) with radius r
    params:
        x,y,r - ints, where x,y,r > 0 and circle in (+,+)
    Returns the cirlce
    Raises ValueError if circle is invalid
    '''

    if r <= 0:
        raise ValueError("Radius < 0!")
    if x < r or y < r:
        raise ValueError("Circle not in 1st quadrant")
    return [x,y,r]

def get_x (c):
    return c[0]

def get_y (c):
    return c[1]

def get_r (c):
    return c[2]

#1. write the function specification 
#2. write a test function
#3. run test function => it must fail
#4. write the function code 
#5. run test function => it should pass (repeat 3-5 until you get it right)
#6. optimize

def test_init ():
    circles = []
    circles.append(create_circle(1,1,1))
    circles.append(create_circle(1,2,1))
    circles.append(create_circle(2,1,1))

def test_create_circle ():
    c = create_circle(1,1,1)
    assert get_x(c) == 1 and get_y(c) ==1 and get_r(c) == 1

    #radius < 0
    try:
        c = create_circle(1,1,-1)
        assert False
    except ValueError:
        assert True

    # not in first q
    try:
        c = create_circle(1,1,2)
        assert False
    except ValueError:
        assert True
test_create_circle()