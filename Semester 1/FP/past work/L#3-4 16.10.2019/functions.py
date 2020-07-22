from domain import *
import copy
#LIST feature

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
        #for i in expenses:
            #if apartmentId == get_apartmentId(i) and expenseType ==  get_expenseType(i):
                #return 11
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

def test_valid_sum ():
    assert valid_sum(["gas"]) == 0
    assert valid_sum([1]) == 2
    assert valid_sum(["1"]) == 2
    assert valid_sum([]) == 9
    assert valid_sum([""]) == 2
    assert valid_sum([1,2]) == 9
test_valid_sum()

def sum_expenses_types (expenses, expenseType):
    sum = 0
    for i in expenses:
        if get_expenseType(i) == expenseType:
            sum = sum + int(get_amount(i))
    return sum

def test_sum_expenses_types ():
    expenses = empty()

    append_to_array(expenses,create_expense(100,"water",40))
    append_to_array(expenses,create_expense(101,"electricity",60))
    append_to_array(expenses,create_expense(102,"other",20))
    append_to_array(expenses,create_expense(100,"heating",45))
    append_to_array(expenses,create_expense(101,"gas",100))
    append_to_array(expenses,create_expense(100,"water",50))
    append_to_array(expenses,create_expense(101,"electricity",70))
    append_to_array(expenses,create_expense(102,"other",90))
    append_to_array(expenses,create_expense(100,"heating",90))
    append_to_array(expenses,create_expense(101,"gas",40))

    assert sum_expenses_types(expenses, "gas") == 140
    assert sum_expenses_types(expenses, "gas") != 130
test_sum_expenses_types()


#MAX feature

def max_amount (expenses, apId, expenseType):
    '''
    Returns the maximum amount of an expense type for a given apartment
    Input parameters:
        expenses - the list of expenses
        apId - the apartment for which we want to find the max amount
        expenseType - the expense for which we want to find the max amount
    Output parameters:
        max - the maximum amount for an expense in a given apartment
    '''

    max = 0
    for i in expenses:
        if int(get_apartmentId(i)) == int(apId) and get_expenseType(i) == expenseType:
            if max < int(get_amount(i)):
                max = int(get_amount(i))
    return max

def test_max_amount ():
    expenses = empty()

    append_to_array(expenses,create_expense(100,"water",40))
    append_to_array(expenses,create_expense(101,"electricity",60))
    append_to_array(expenses,create_expense(102,"other",20))
    append_to_array(expenses,create_expense(100,"heating",45))
    append_to_array(expenses,create_expense(101,"gas",100))
    append_to_array(expenses,create_expense(100,"water",50))
    append_to_array(expenses,create_expense(101,"electricity",70))
    append_to_array(expenses,create_expense(102,"other",90))
    append_to_array(expenses,create_expense(100,"heating",90))
    append_to_array(expenses,create_expense(101,"gas",40))
    assert max_amount(expenses, 100, "water") == 50
    assert max_amount(expenses, 101, "gas") == 100
    assert max_amount(expenses, 200, "gas") == 0

test_max_amount()

def valid_max (params):
    '''
    Checks if the max command is valid
    Input:
        params - the values of the command
    Output:
        0 if the command is valid
        1 if the apartment id is wrong
        9 if the number of operands is wrong
    '''
    if len(params) != 1:
        return 9
    try:
        apId = int(params[0])
    except:
        return 1
    else:
        if apId <= 0:
            return 1
    return 0

def test_valid_max ():
    assert valid_max([14]) == 0
    assert valid_max(["14"]) == 0
    assert valid_max(["ad"]) == 1
    assert valid_max([1,2]) == 9
test_valid_max()

def expense_types_for_ap (expenses,apId):
    expensesForAp = empty()
    for i in expenses:
        if int(apId) == int(get_apartmentId(i)) and get_expenseType(i) not in expensesForAp:
            append_to_array(expensesForAp,get_expenseType(i))
    return expensesForAp

def test_expense_types_for_ap ():
    expenses = empty()

    append_to_array(expenses,create_expense(100,"water",40))
    append_to_array(expenses,create_expense(101,"electricity",60))
    append_to_array(expenses,create_expense(102,"other",20))
    append_to_array(expenses,create_expense(100,"heating",45))
    append_to_array(expenses,create_expense(101,"gas",100))
    append_to_array(expenses,create_expense(100,"water",50))
    append_to_array(expenses,create_expense(101,"electricity",70))
    append_to_array(expenses,create_expense(102,"other",90))
    append_to_array(expenses,create_expense(100,"heating",90))
    append_to_array(expenses,create_expense(101,"gas",40))

    assert expense_types_for_ap(expenses, 100) == ["water", "heating"]
    assert expense_types_for_ap(expenses, 120) == []
    assert expense_types_for_ap(expenses, 100) != ["water", "heating", "other"]
    assert expense_types_for_ap(expenses, 100) != ["other", "heating", "other"]
test_expense_types_for_ap()

# SORT feature

def valid_sort (params):
    '''
    Checks if the sort command has the correct operand
    Input:
        params - the operand
    Output:
        0 if the operand is correct
        12 if the operand is incorrect

    '''
    if len(params) != 1:
        return 12
    if params[0] not in ["apartment","type"]:
        return 12
    return 0

def test_valid_sort():
    assert valid_sort(["type"]) == 0
    assert valid_sort(["apartment"]) == 0
    assert valid_sort(["asdasf"]) == 12
    assert valid_sort([]) == 12
    assert valid_sort(["type", 1]) == 12
test_valid_sort()

def sort_list (list1, list2):
    '''
    Sorts the lists based on the values in the second list
    Input parameters:
        list1 - list with expense types / apartment ids
        list2 - list with the amount for each expense type
    '''
    l = len(list2)
    for i in range(0,l-1):
        for j in range(i+1,l):
            if list2[i] > list2[j]: 
                aux = list2[i]
                list2[i] = list2[j]
                list2[j] = aux
                
                aux = list1[i]
                list1[i] = list1[j]
                list1[j] = aux
                
def sort_apartment (expenses):
    '''
    Function provides the list of apartments sorted by the total amount of expenses
    Input parameters :
        expenses - the list of expenses
    Output parameters:
        apList - the list of apartments sorted by the total amount
        amountList - the list of total amounnt for each apartment
    '''
    apList = empty()
    amountList = empty()
    for i in expenses:
        apId = int(get_apartmentId(i))
        if apId not in apList:
            append_to_array(apList,apId)
            append_to_array(amountList,int(sum_expenses(expenses,apId)))
    sort_list(apList,amountList)
    return [apList,amountList]

def test_sort_apartment ():
    expenses = empty()

    append_to_array(expenses,create_expense(100,"water",40))
    append_to_array(expenses,create_expense(101,"electricity",60))
    append_to_array(expenses,create_expense(102,"other",20))
    append_to_array(expenses,create_expense(100,"heating",45))
    append_to_array(expenses,create_expense(101,"gas",100))
    append_to_array(expenses,create_expense(100,"water",50))
    append_to_array(expenses,create_expense(101,"electricity",70))
    append_to_array(expenses,create_expense(102,"other",90))
    append_to_array(expenses,create_expense(100,"heating",90))
    append_to_array(expenses,create_expense(101,"gas",40))
    
    apList = sort_apartment(expenses)

    assert apList[0] == [102,100,101]
    assert apList[0] != [1,2,3,"asd"]
    assert apList[1] == [110,225,270]
    assert len(apList[1]) == len(apList[0])
test_sort_apartment()

def sort_types (expenses):
    '''
    Returns the list of expenses sorted by their totatl amount
    Input parameters:
        expenses - the list of expenses
    Output parameters:
        typeList - the list of expense types sorted by their total amount
        amountList - the list of the total amount per each expense
    '''
    typeList = expenses_types()
    amountList = empty()
    for i in expenses_types():
        append_to_array(amountList,sum_expenses_types(expenses,i))
    sort_list(typeList,amountList)
    return [typeList,amountList]

def test_sort_types ():
    expenses = empty()

    append_to_array(expenses,create_expense(100,"water",40))
    append_to_array(expenses,create_expense(101,"electricity",60))
    append_to_array(expenses,create_expense(102,"other",20))
    append_to_array(expenses,create_expense(100,"heating",45))
    append_to_array(expenses,create_expense(101,"gas",100))
    append_to_array(expenses,create_expense(100,"water",50))
    append_to_array(expenses,create_expense(101,"electricity",70))
    append_to_array(expenses,create_expense(102,"other",90))
    append_to_array(expenses,create_expense(100,"heating",90))
    append_to_array(expenses,create_expense(101,"gas",40))
    
    apList = sort_types(expenses)
    assert apList == [['water', 'other', 'electricity', 'heating', 'gas'], [90, 110, 130, 135, 140]]
    assert len(apList[1]) == len(apList[0])

test_sort_types()

#FILTER feature

def valid_filter (params):
    '''
    Checks if the filter command is correct
    Input parameters:
        params - the command values
    Output:
        0 - valid data
        2 - wrong type
        3 - wrong amount
        9 - wrong number of operands
    '''
    if len(params) != 1:
        return 9
    if params[0] in expenses_types():
        return 0
    else:
        try:
            amount = int(params[0])
        except:
            return 2
        else:
            if amount <= 0:
                return 3
    return 0

def test_valid_filter ():
    assert valid_filter(["gas"]) == 0
    assert valid_filter([300]) == 0
    assert valid_filter(["300"]) == 0
    assert valid_filter(["asda"]) == 2
    assert valid_filter(["-32"]) == 3
    assert valid_filter([]) == 9
    assert valid_filter([1,2,3]) == 9
test_valid_filter()

def filter_type (expenses, expenseType):
    '''
    Function keeps all expenses that have the required expense type
    Input parameters:
        expenses - the list of expenses
        expenseType - the required expense type
    '''
    i = 0
    l = len(expenses)
    while i < l:
        if get_expenseType(expenses[i]) != expenseType:
            expenses.remove(expenses[i])
            l = l-1
        else:
            i = i+1

def test_filter_type ():
    expenses = empty()
    append_to_array(expenses,create_expense(101,"electricity",60))
    append_to_array(expenses,create_expense(100,"water",50))
    append_to_array(expenses,create_expense(100,"water",50))
    append_to_array(expenses,create_expense(101,"electricity",70))
    append_to_array(expenses,create_expense(100,"water",50))
    append_to_array(expenses,create_expense(100,"water",50))

    filter_type(expenses, "electricity")
   
    assert len(expenses) == 2
    assert get_expenseType(expenses[1]) == "electricity"
test_filter_type()

def filter_amount (expenses, amount):
    '''
    Function keep all expenses that have an amount smaller than the required amount
    Input parameters:
        expenses - the list of expenses
        amount - the required amount
    '''
    i = 0
    l = len(expenses)
    while i < l:
        if int(get_amount(expenses[i])) >= int(amount):
            expenses.remove(expenses[i])
            l = l-1
        else:
            i = i+1

def test_filter_amount ():
    expenses = empty()
    append_to_array(expenses,create_expense(101,"water",60))
    append_to_array(expenses,create_expense(100,"water",350))
    append_to_array(expenses,create_expense(101,"electricity",350))

    filter_amount(expenses, 300)
    assert len(expenses) == 1
    assert get_expenseType(expenses[0]) == "water"
test_filter_amount()

#UNDO feature

def undo (history, expenses):
    '''
    Function replaces the current list of expenses with the last list 
    Input parameters:
        history - the list that retains the lists of expenses 
        expenses - the current list of expenses
    '''
    expenses.clear()
    aux = history[-1]
    for i in aux:
        append_to_array(expenses,i)
    history.remove(history[-1])

def test_undo ():
    x = [1,2,3]
    y = [[1,2,3],[4,5,6]]
    undo(y,x)
    assert x == [4,5,6]
    assert y == [[1,2,3]]
test_undo()

def add_to_history (history, expenses):
    '''
    Function adds to history the current list of expenses
    Input parameters:
        history - the history of all lists of expenses
        expenses - the current expenses
    '''
    if len (history) != 0:
        if expenses == [] and history[-1] == [] and expenses == history[-1]:
            return
    append_to_array(history, [])
    history[-1] = copy.deepcopy(expenses)

def test_add_to_history ():
    x = [1,2,3]
    y = [[3,4,5]]
    add_to_history(y,x)
    assert y == [[3,4,5],[1,2,3]]
    x[0] = 10
    assert y == [[3,4,5],[1,2,3]]
test_add_to_history()

def valid_history (cmd, params):
    '''
    Function checks if a command that changes the list of expenses is valid so that it can add the list of expenses to history
    Input parameters:
        cmd - one of the add, remove, replace or filter commands
        params - the parameters of the command
    Output parameters:
        0 - if data is valid
        1 - otherwise
    '''
    if cmd == "add" and valid_expense([], params) != 0:
        return 1
    elif cmd == "remove" and valid_removal(params) != 0:
        return 1
    elif cmd == "replace" and valid_replace(params) != 0:
        return 1
    elif cmd == "filter" and valid_filter(params) != 0:
        return 1
    return 0

def test_valid_history ():
    assert valid_history("add", [1,"gas",2]) == 0
    assert valid_history("add", [1,"gas","2"]) == 0
    assert valid_history("add", [1,"gas",-2]) == 1
    assert valid_history("filter", ["sfa"]) == 1
    assert valid_history("filter", ["gas"]) == 0
test_valid_history()