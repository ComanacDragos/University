def create_number (real,imaginary):
    return [real,imaginary]

def empty ():
    '''
    Returns an empty list
    '''
    empty = []
    return empty

def get_first_element (numberList):
    return numberList[0]

def get_real(number):
    return number[0]

def get_imaginary(number):
    return number[1]

def set_real(number,value):
    number[0] = value

def set_imaginary(number,value):
    number[1] = value

def add_el (numberList,el):
    '''
    Adds an element to the list
        input parameters: 
            number list - the list in which we want to add the element
            el - the element which we want to add to the list
    '''
    numberList.append(el)
    

def menu ():
    '''
    Function prints the menu
    '''
    print("")
    print("1. Read number")
    print("2. Display the entire list of numbers")
    print("3. Display longest sequence of complex numbers with the same modulus")
    print("4. Display longest sequence of complex numbers where the real part is in the form of a mountain (first the values increase, then they decrease)")
    print("5. Exit")
    print("")

def init_list ():
    '''
    Function initializes the list of complex numbers
    '''
    numberList = empty()
    add_el(numberList,create_number(1,2))
    add_el(numberList,create_number(2,1))
    add_el(numberList,create_number(-1,2))
    add_el(numberList,create_number(2,0))
    add_el(numberList,create_number(0,1.4))
    add_el(numberList,create_number(0,0))
    add_el(numberList,create_number(0.3,0.4))
    add_el(numberList,create_number(-0.3,-0.4))
    add_el(numberList,create_number(0.4,0.3))
    add_el(numberList,create_number(0.3,-0.4))
    add_el(numberList,create_number(-0.3,0.4))
    add_el(numberList,create_number(1,2))
    add_el(numberList,create_number(1.1,-1))
    add_el(numberList,create_number(2,6))
    add_el(numberList,create_number(3.2,5))
    add_el(numberList,create_number(-3.4,6))
    add_el(numberList,create_number(-3.5,10))
    add_el(numberList,create_number(3.6,-1))
    return numberList

def read_number (numberList):
    '''
    Function reads a number and then it appends it to the list
    Input parameters 
        - numberList - the list of complex numbers
    '''
    real = float(input("Real part= "))
    imaginary = float(input("Imaginary part= "))
    if real == int(real):
        real = int(real)
    if imaginary == int(imaginary):
        imaginary = int(imaginary)
    number = create_number(real,imaginary)
    add_el(numberList,number)

def display (numberList):
    '''
    Function displays the list of complex numbers in a+bi form where a is the real part and b is the imaginary part
    Input parameters
        - numberList - the list of complex numbers
    '''
    count=0
    for i in numberList:
        count = count+1
        real = get_real(i)
        imaginary = get_imaginary(i)
        if real == 0:
            if imaginary == 1:
                print(str(count) + ". " + "i")
            elif imaginary == 0:
                print(str(count) + ". " + "0")
            elif imaginary == -1:
                print(str(count) + ". " + "-i")
            else:
                print(str(count) + ". " + str(imaginary) + 'i')
        elif imaginary == 0:
            print(str(count) + ". " + str(real))
        else:
            if float(imaginary) > 0:
                if imaginary == 1:
                    print(str(count) + ". " + str(real) + "+" + "i")
                else:
                    print(str(count) + ". " + str(real) + "+" + str(imaginary) +"i")
            else:
                if imaginary == -1:
                    print(str(count) + ". " + str(real) + "-i")
                else:
                    print(str(count) + ". " + str(real) + str(imaginary) + "i")

def modulus (real,imaginary):
    '''
    Returns the modulus (squared) of a complex number
    Input parameters:
        - real - real part of the complex number
        - imaginary - iamginary part of the complex number
    '''
    return real**2+imaginary**2

def same_modulus (numberList):
    '''
    Displays the longest sequence of complex numbers with the same modulus in a list 
    Input parameters:
         - numberList - list of complex numbers
    '''
    maxSeq = empty()
    currentSeq = empty()
    first = get_first_element(numberList)
    currentMod = modulus(get_real(first),get_imaginary(first))
    for i in numberList:
        real = get_real(i)
        imaginary=get_imaginary(i)
        if currentMod == modulus(real,imaginary):
            add_el(currentSeq,i)
        else:
            currentMod=modulus(real,imaginary)
            if len(currentSeq) > len(maxSeq):
                maxSeq = empty()
                maxSeq = currentSeq
            currentSeq = empty()
            add_el(currentSeq,i)
    if len(currentSeq) > len(maxSeq):
                maxSeq = empty()
                maxSeq = currentSeq
    return maxSeq

def mountain_form (numberList):
    '''
    Function displays longest sequence of complex numbers where the real part is in the form of a mountain (first the values increase, then they decrease)
    Input parameters:
         - numberList - list of complex numbers
    Output parameters:
        - maxSeq - the longest sequence with the required property
    '''
    maxSeq = empty()
    currentSeq = empty()
    ok = 1
    antVal = get_real(get_first_element(numberList))
    for i in numberList:
        real = get_real(i)
        if ok == 1:
            if real >= antVal:
                add_el(currentSeq,i)
            else:
                ok = 0
                add_el(currentSeq,i)
        else:
            if real <= antVal:
                add_el(currentSeq,i)
            else:
                ok = 1
                if len(currentSeq) > len(maxSeq):
                    maxSeq = empty()
                    maxSeq = currentSeq
                currentSeq = empty()
                add_el(currentSeq,i)
        antVal = real
    if len(currentSeq) > len(maxSeq):
        maxSeq = empty()
        maxSeq = currentSeq
    return maxSeq
                                    
        
def start():
    numberList = init_list()
    while True:
        menu()
        choice = input(">")
        if choice == "3":
            display(same_modulus(numberList))
        elif choice == "2":
            display(numberList)
        elif choice == "1":
            read_number(numberList)
        elif choice == "4":
            display(mountain_form(numberList))
        elif choice == "5":
            return
        else:
            print("Invalid command")
            


start()