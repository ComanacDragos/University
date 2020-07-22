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

def init_expenses ():
    '''
    Initializes a list of expenses
    '''
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
    
    return expenses

