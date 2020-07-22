def create_expense (apartmentId,expenseType,amount):
    dict = {
        "apartmentId" : apartmentId,
        "expenseType" : expenseType,
        "amount" : amount
    }
    return dict

def test_create_expense ():
    e = create_expense(1,"water",40)
    assert get_apartmentId(e) != 1
    assert get_expenseType(e) != "water"
    assert get_amount(e) != 40
test_create_expense


def get_apartmentId (apartment):
    return apartment["apartmentId"]

def get_expenseType (apartment):
    return apartment["expenseType"]

def get_amount (apartment):
    return apartment["amount"]

def set_apartmentId (apartment, newId):
    apartment["apartmentId"] = newId

def set_expenseType (apartment,newExpenseType):
    apartment["expenseType"] = newExpenseType

def set_amount (apartment,newAmount):
    apartment["amount"] = newAmount

def empty ():
    return []

def append_to_array (array,value):
    array.append(value)

def remove_el (array,value):
    array.remove(value)

def expenses_types():
    return  ["water", "heating", "electricity", "gas", "other"]

def print_simple_array (array):
    count = 1
    for i in array:
        print (str(count) + ". " + str(i))
        count = count+1

def error_messages (error):
    '''
    Function prints error messages for a given error number
    '''
    errorList = {
        "1" : "Wrong apartment id",
        "2" : "Wrong expense type",
        "3" : "Wrong amount",
        "4" : "<to> is missing",
        "5" : "<with> is missing",
        "6" : "The left operand is bigger than the right operand",
        "7" : "There is no apartment with given id",
        "8" : "There is no apartment with given expense",
        "9" : "Wrong number of operands",
        "10": "One of < | = | > is missing ",
        "11": "This kind of expense already exists for this apartment"
    }
    print(errorList[str(error)])

# LIST feature

def valid_list (params):
    '''
    Checks if the list command has a valid format
    Input :
        params: command values
    Output:
        0 - valid data
        1 - wrong apartment id
        3 - wrong amount
        9 - wrong number of operands
        10 - < | = | > is missing
    '''
    if len(params) == 1:
        try:
            id = int(params[0])
        except:
            return 1
        else:
            if id <= 0:
                return 1
    elif len(params) == 2:
        if params[0] not in ["<", "=", ">"]:
            return 10
        try:
            amount = int (params[1])
        except:
            return 3
        else:
            if amount <= 0 :
                return 3
    else:
        if len(params) > 2:
            return 9    
    return 0

def test_valid_list ():
    assert valid_list ([15]) == 0
    assert valid_list (["<", 10]) == 0
    assert valid_list (["15"]) == 0
    assert valid_list ([-15]) == 1
    assert valid_list (["-15"]) == 1
    assert valid_list ([">", -10]) == 3
    assert valid_list (["="]) == 1
    assert valid_list (["=",1,2,3]) == 9
    assert valid_list (["asd"]) == 1
    assert valid_list([]) == 0
    assert valid_list(["1231","1231323"]) == 10
test_valid_list()

def sum_expenses (expenses, apId):
    sum = 0
    for i in expenses:
        if get_apartmentId(i) == apId:
            sum = sum + get_amount(i)
    return sum

def test_sum_expenses ():
    exp = []
    append_to_array(exp,create_expense(1,"gas",2))    
    append_to_array(exp,create_expense(1,"other",2))
    append_to_array(exp,create_expense(1,"electricity",2))
    append_to_array(exp,create_expense(1,"water",2))
    assert sum_expenses(exp,1) == 8 

def display_expenses (expenses):
    count = 1
    print("")
    for i in expenses:
        apId = get_apartmentId(i)
        expenseType = get_expenseType(i)
        amount = get_amount(i)
        print(str(count) + ". " + "In apartment " + str(apId) + " for the expense type " + expenseType + " the amount is " + str(amount))
        count = count+1
    print("")


def list_expenses (expenses, params):
    if valid_list(params) != 0 :
        error_messages(valid_list(params))
    elif len(expenses) == 0:
        print("There are no expenses in any apartment")
    else:

        ok = 0
        if len(params) == 0:
            display_expenses(expenses)
        elif len(params) == 1:
            id = params[0]
            for i in expenses:
                if int(get_apartmentId(i)) == int(id):
                    print ("For " + str(get_expenseType(i)) + " the amount is " + str(get_amount(i)))
                    ok = 1
            if ok == 0:
                error_messages(7)
            else:
                print ("")

        elif len(params) == 2:
            amount = int(params[1])
            apList = empty()
            if params[0] == "<":
                for i in expenses:
                    id = int(get_apartmentId(i))
                    if sum_expenses(expenses, id) < amount:
                        append_to_array(apList,id)
                        ok = 1
                if ok == 1:
                    print ("The apartments with total expenses less than " + str(amount) + " are:")

            if params[0] == "=":
                for i in expenses:
                    id = get_apartmentId(i)
                    if sum_expenses(expenses, id) == amount:
                        append_to_array(apList,id)
                        ok = 1
                if ok == 1:
                    print ("The apartments with total expenses equal to " + str(amount) + " are:")

            if params[0] == ">":
                for i in expenses:
                    id = get_apartmentId(i)
                    if sum_expenses(expenses, id) > amount:
                        append_to_array(apList,id)
                        ok = 1
                if ok == 1:
                     print ("The apartments with total expenses more than " + str(amount) + " are:")
            if ok == 0:
                print("There are no such apartments")
            else:
                print("")
                apList = list (dict.fromkeys(apList))
                apList.sort()
                print_simple_array(apList)
                print("")
                


def read_command ():
    '''
    Function reads a command and splits it into the command keyword and the values of the command
    Output:
        command - command keyword
        params - the values of the command
    '''
    cmd = input("Give command: ")
    idx = cmd.find(" ")
    if idx == -1:
        return (cmd,[])
    command = cmd[:idx]
    params = cmd[idx+1:]
    params = params.split(" ")
    for i in range(len(params)):
        params[i] = params[i].strip()
    return [command,params]


# ADD expense feature

def valid_expense (expenses, params):
    '''
    Checks if an expense has a valid format
    input params:
        params - the expense
    output :
        0 - valid data
        1 - wrong apartment id
        2 - wrong expense type
        3 - wrong amount
        9 - wrong number of operands
        11 - this kind of expense already exists
    '''
    if len(params) != 3 :
        return 9
    try:
        apartmentId = int(params[0])
    except:
        return 1
    else:
        if apartmentId <= 0:
            return 1
    try:
        expenseType = params[1]
    except:
            return 2
    else:
        if expenseType not in expenses_types():
            return 2
        for i in expenses:
            if apartmentId == get_apartmentId(i) and expenseType ==  get_expenseType(i):
                return 11
    try:
        amount = int(params[2])
    except:
        return 3
    else:
        if amount <= 0:
            return 3
    return 0

def test_valid_expense ():
    '''
    Tests if the valid_expense function gives correct outputs
    '''    
    exp = empty ()
    assert valid_expense(exp,[1,"water", 3]) == 0
    assert valid_expense(exp,[-1, "water", 3]) == 1
    assert valid_expense(exp,[1,"awt",3]) == 2
    assert valid_expense (exp,[1, "heating", "asf"]) == 3
    assert valid_expense (exp,[]) == 9
    assert valid_expense (exp,[1, "heating"]) == 9
    assert valid_expense (exp,[1, "heating", -4]) == 3
    assert valid_expense (exp,[1, "heatg", 3]) == 2
    assert valid_expense (exp,[1, "heatg", 3, 4]) == 9
test_valid_expense()

def add_expense (expenses, params):
    '''
    Adds an expense to the expense list
    Input parameters :
        - expenses - the list of expenses
        - params - values of the expense
    '''
    valid = valid_expense(expenses, params)
    if valid != 0:
        error_messages(valid)
    else:
        expense = create_expense(int(params[0]), params[1], int(params[2]))
        append_to_array(expenses, expense)     


# REMOVE expenses feature

def valid_removal (params):
    '''
    Checks if an removal command has a valid format
    input params:
        params - the values of the removal command
    output :
        0 - valid data
        natural number - invalid data
    '''
    if len(params) == 1:
        if params[0] in expenses_types():
            return 0
        try:
            ap = int(params[0])
        except: 
            return 1
        else:
            if ap <= 0:
                return 1
    elif len(params) == 3:
        try:
            first = int(params[0])
            last = int(params[2])
        except:
            return 1
        else:
            if first <= 0 or last <= 0:
                return 1
            if first > last:
                return 6
            if params [1] !="to":
                return 4
    else:
        return 9
    return 0

def remove_expense (expenses, params):
    '''
    Removes a expense or multiple expenses from the list of expenses
    Input parameters:
        expenses - list of expenses
        params - values that need to be removed
    '''
    ok = 0
    valid = valid_removal(params)
    if valid != 0:
        error_messages(valid)
    else:

        if params[0] in expenses_types():
            expenseType = params[0]
            i = 0
            n = len(expenses)
            while i < n:
                if expenseType == get_expenseType(expenses[i]):
                    remove_el(expenses,expenses[i])
                    n = n-1
                    ok = 1
                else:
                    i = i+1
                
        else:
            first = int(params[0])
            if len(params) == 3:
                last = int(params[2])
            else:
                last = first
            i = 0
            n = len(expenses)
            while i < n:
                id = get_apartmentId(expenses[i])
                if id >= first and id <= last:
                    remove_el(expenses,expenses[i])
                    n = n-1
                    ok = 1
                else:
                    i = i+1
        if ok == 0:
            print("The requested expenses do not exist")
            
def test_valid_removal ():
    assert valid_removal([10]) == 0
    assert valid_removal([1,"to",10]) == 0
    assert valid_removal([1,"too",10]) == 4
    assert valid_removal(["gaas"]) == 1
    assert valid_removal([-1,"to",3]) == 1
    assert valid_removal([1,2]) == 9
    assert valid_removal([]) == 9
    assert valid_removal([3,"to","ASD"]) == 1
    assert valid_removal([3,"to",-3]) == 1
    assert valid_removal(["asd","to",3]) == 1
    assert valid_removal([4,"to",3]) == 6
    assert valid_removal(["asd",3,"asd"]) == 1
    assert valid_removal(["gaas"]) == 1
    assert valid_removal(["gas"]) == 0
    assert valid_removal(["gas",2]) == 9
test_valid_removal()



# REPLACE feature

def valid_replace (params):
    '''
    Checks if an replace command has valid parameters 
    Input - params - the list of parameters
    Output :
        1 - valid data 
        natural number - invalid data
    '''
    if len(params) != 4:
        return 9
    try:
        apId = int (params[0])
    except:
        return 1
    else: 
        if apId <= 0:
            return 1
    if params[1] not in expenses_types():
        return 2
    try:
        newAmount = int(params[3])
    except:
        return 3
    else:
        if newAmount <= 0:
            return 3
    if params [2] != "with":
        return 5
    return 0

def replace_amount (expenses, params):
    '''
    Replaces the amount of an expense for a given apartment
    Input :
        params - the values of the command
    '''
    valid = valid_replace(params)
    if valid != 0:
        error_messages(valid)
    else:
        ok = 0
        for i in expenses:
            id = get_apartmentId(i)
            expType = get_expenseType(i)
            if int(params[0]) == int(id) and params[1] == expType:
                set_amount(i, params[3])
                ok = 1
        if ok == 0:
            print ("The requested expense does not exist")

def test_valid_replace ():
    assert valid_replace(["12","gas","with","20"]) == 0
    assert valid_replace(["12","gas","with","20","32"]) == 9
    assert valid_replace(["12","ga","with","200"]) == 2
    assert valid_replace(["12","gas","o","200"]) == 5
    assert valid_replace(["12","gas","with","-200"]) == 3
    assert valid_replace(["-12","gas","with","200"]) == 1
    assert valid_replace(["12","gas","with","fgh"]) == 3
    assert valid_replace(["hjk","gas","with","200"]) == 1
    assert valid_replace(["12","gas","with"]) == 9
test_valid_replace()

# SUM feature

def valid_sum (params):
    '''
    Checks if the sum command has valid parameters
    Input:
        params - the operands of the command
    Output:
        0 - valid data
        natural number - invalid data
    '''
    if len(params) != 1:
        return 9
    if params[0] not in expenses_types():
        return 2
    return 0

def sum (expenses,params):
    '''
    Function writes the total amount for the expenses having a given type
    Input:
        expenses - the list of expenses
        params - the operands of the command
    '''
    valid = valid_sum(params)
    if valid != 0:
        error_messages(valid)
    else:
        expenseType = params[0]
        s = 0
        for i in expenses:
            if expenseType == get_expenseType(i):
                s = s+get_amount(i)
        if s == 0:
            print("There are no apartments with given expense")
        else:
            print(s)

def test_valid_sum ():
    assert valid_sum(["gas"]) == 0
    assert valid_sum([1]) == 2
    assert valid_sum(["1"]) == 2
    assert valid_sum([]) == 9
    assert valid_sum([""]) == 2
    assert valid_sum([1,2]) == 9
test_valid_sum()



def init_expenses ():
    '''
    Initializes a list of expenses
    '''
    expenses = empty()
    add_expense(expenses,[100,"water",40])
    add_expense(expenses,[101,"electricity",60])
    add_expense(expenses,[102,"other",20])
    add_expense(expenses,[100,"heating",45])
    add_expense(expenses,[101,"gas",100])
    return expenses

def give_help (params):
    '''
    Function provides details about the commands
    '''
    if len(params) != 0:
        error_messages(9)
        return
    print ("")
    print ("For adding an expense insert the following command:")
    print("     add <apartment> <type> <amount>")
    print("")
    print("For removing one or multiple expenses insert the following commands:")
    print("     remove <apartment>")
    print("     remove <start apartment> to <end apartment>")
    print("     remove <type>")
    print("")
    print("For replacing the amount of an expense with another amount insert the following command:")
    print("     replace <apartment> <type> with <amount>")
    print("")
    print("For listing expenses insert the following commands:")
    print("     list")
    print("     list <apartment>")
    print("     list [ < | = | > ] <amount>")
    print("")
    print("For exiting the program insert the following command:")
    print("     exit")
    print("Where:")
    print("     <apartment> is the apartment id")
    print("     <type> is the expense type")
    print("     <amount> is the cost of the expense")
    print("")

def start ():
    expenses = init_expenses()
    print("")
    print("Insert <help> for information about the commands ")
    print("")
    commands = {
        "add" : add_expense,
        "remove" : remove_expense,
        "replace" : replace_amount,
        "list" : list_expenses,
        "sum" : sum
        }
    while True:
        cmdList = read_command()
        cmd = cmdList[0]
        params = cmdList[1]
        if cmd in commands:
            commands[cmd](expenses,params)
        elif cmd == "help":
            give_help(params)
        elif cmd == "exit":
            return
        else:
            print("Invalid command")
            
        
start()

