from ui_functions import *

def print_menu ():
    menu = '''
1. Add an expense to the list
2. Remove expenses
3. Replace the amount of an expense
4. List expenses
5. Write the total amount for the expenses having a given expense type
6. Write the maximum amount per each expense type for a given apartment id
7. Write a sorted list of the expenses after a given criteria
8. Keep only expenses having a certain criteria
9. Undo the last operation
10. Exit menu-based user interface
'''
    print(menu)

def menu_ui_add (expenses, history):
    '''
    The menu_ui function that adds an expense to the list of expenses
    Input parameters:
        expenses - the list of expenses
        histoyry - history of all lists of expenses
    '''
    params = empty()

    print("")
    apId = input("Give apartment id: ")
    expType = input("Give expense type: ")
    amount = input("Give amount: ")
    print("")

    params.append(apId)
    params.append(expType)
    params.append(amount)

    if valid_history("add", params) == 0:
        add_to_history(history, expenses)

    add_expense(expenses,params)

def menu_ui_remove (expenses, history):
    '''
    The menu_ui funnction that removes an expense, or multiple from the list of expenses
    Input parameters:
        expenses - the list of expenses
        history - the history of all lists of expenses
    '''

    choice = '''
1. Remove all expenses for a given apartment
2. Remove all expenses from a given apartment to another given apartment
3. Remove all expenses with a given expense type
    '''

    print(choice)
    choice = input(">")
    params = empty()

    if choice == "1":
        apId = input("Give apartment id: ")
        params.append(apId)

    elif choice == "2":
        first = input("Give first apartment id: ")
        last = input("Give last apartment id: ")
        params.append(first)
        params.append("to")
        params.append(last)

    elif choice == "3":
        expType = input("Give expense type: ")
        params.append(expType)

    else:
        print("\nInvalid command\n")
        return
    
    if valid_history("remove", params) == 0:
        add_to_history(history, expenses)

    remove_expense(expenses, params)

def menu_ui_replace (expenses, history):
    '''
    The menu_ui function that replaces the amoun of an expense with a new value
    Input parametes:
        expenses - the list of expenses
        history - history of all lists of expenses
    '''

    print("")
    apId = input("Give apartment id: ")
    expType = input("Give expense type: ")
    newAmount = input("Give new amount: ")
    print("")
    
    params = empty()
    params.append(apId)
    params.append(expType)
    params.append("with")
    params.append(newAmount)

    if valid_history("replace", params) == 0:
        add_to_history(history, expenses)
    replace_amount(expenses, params)

def menu_ui_list (expenses):
    '''
    The menu_ui function that lists a required list of expenses
    Input parameters:
        expenses - the list of expenses
    '''

    params = empty()
    choice = '''
1. Write the entire list of expenses
2. Write all expenses for a given apartment
3. Write all apartments having total amounts < | = | > than/to a given amount
    '''
    print(choice)
    choice = input('>')

    if choice == "2":
        apId = input("Give apartment id: ")
        params.append(apId)
    elif choice == "3":
        comp = input("Give comparrison operator: ")
        amount = input("Give amount: ")
        params.append(comp)
        params.append(amount)
    elif choice == "1":
        pass
    else:
        print("\nInvalid command\n")
        return
    list_expenses(expenses, params)

def menu_ui_sum (expenses):
    '''
    The menu_ui function that prints the total expenses having a given type
    Input parameters:
        expenses - the list of expenses
    '''

    params = empty()
    print("")
    expType = input("Give expense type: ")
    print("")
    params = [expType]
    sum(expenses,params)

def menu_ui_max (expenses):
    '''
    The menu_ui function that writes the maxim amount per each expense type for a given apartment id
    Input parameters:
        expenses - the list of expenses
    '''

    params = empty()
    print("")
    apId = input("Give apartment id: ")
    print("")
    params = [apId]
    max(expenses, params)

def menu_ui_sort (expenses):
    '''
    The menu_ui function that writes a sorted list of the expenses after a given criteria
    Input parameters:
        expenses - the list of expenses
    '''

    params = empty()
    choice = '''
1. Sort apartment
2. Sort type
    '''
    print(choice)
    choice = input(">")
    if choice == "1":
        params = ["apartment"]
    elif choice == "2":
        params = ["type"]
    else:
        print("\nInvalid command\n")
        return
    sort(expenses, params)

def menu_ui_filter (expenses, history):
    '''
    The menu_ui function that keeps expenses having a certain criteria
    Input parameters:
        expenses - the list of expenses
        history - history of all lists of expenses
    '''

    params = empty()
    choice = '''
1. Keep only expenses of a given type
2. Keep only expenses having an amount smaller than a given value
    '''
    print(choice)
    choice = input(">")
    if choice == "1":
        expType = input ("Give expense type: ")
        params.append(expType)
    elif choice == "2":
        amount = input("Give the amount: ")
        params.append(amount)
    else:
        print("\nInvalid command\n")
        return 
    
    if valid_history("filter", params) == 0:
        add_to_history(history, expenses)
    filter(expenses, params)

def menu_based():
    expenses = init_expenses()
    history = []
    commands = {
        "1" : menu_ui_add,
        "2" : menu_ui_remove,
        "3" : menu_ui_replace,
        "4" : menu_ui_list,
        "5" : menu_ui_sum,
        "6" : menu_ui_max,
        "7" : menu_ui_sort,
        "8" : menu_ui_filter
        }
    
    while True:
        print_menu()
        cmd = input(">")
        if cmd in ["1","2","3","8"]:
                commands[cmd](expenses, history)
        elif cmd in ["4","5","6","7"]:
            commands[cmd](expenses)
        elif cmd == "9":
            undo_ui(history, expenses, [])
        elif cmd == "10":
            return 
        else:
            print("\nInvalid command\n")