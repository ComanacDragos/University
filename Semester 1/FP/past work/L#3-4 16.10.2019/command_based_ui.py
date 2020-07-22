from ui_functions import *

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

def give_help (params):
    '''
    Function provides details about the commands
    '''
    if len(params) != 0:
        error_messages(9)
        return
    help = """
For adding an expense insert the following command:
        add <apartment> <type> <amount>

For removing one or multiple expenses insert the following commands:
        remove <apartment>
        remove <start apartment> to <end apartment>
        remove <type>

For replacing the amount of an expense with another amount insert the following command:
        replace <apartment> <type> with <amount>

For listing expenses insert the following commands:
        list
        list <apartment>
        list [ < | = | > ] <amount>

    For adding an expense insert the following command:
        add <apartment> <type> <amount>

For removing one or multiple expenses insert the following commands:
        remove <apartment>
        remove <start apartment> to <end apartment>
        remove <type>

For replacing the amount of an expense with another amount insert the following command: 
        replace <apartment> <type> with <amount>

For listing expenses insert the following commands:
        list
        list <apartment>
        list [ < | = | > ] <amount>

For the sum of the amount of all expenses of a given type insert the following command
        sum <type>

For the maximum amount per each expense type for a given apartment insert the following command:
        max <apartment>

For exiting the command-based user interface insert the following command:
        exit        

Where:
        <apartment> is the apartment id
        <type> is the expense type
        <amount> is the cost of the expense
"""
    print(help)


def command_based ():
    expenses = init_expenses()
    history = []
    print("\nInsert <help> for information about the commands \n")

    commands = {
        "add" : add_expense,
        "remove" : remove_expense,
        "replace" : replace_amount,
        "list" : list_expenses,
        "sum" : sum,
        "max" : max,
        "sort": sort,
        "filter": filter
        }

    while True:
        cmdList = read_command()
        cmd = cmdList[0]
        params = cmdList[1]
        if cmd in ["remove", "replace", "filter"] and valid_history(cmd, params) == 0 and len(expenses) != 0 :
            add_to_history(history,expenses)
        elif cmd == "add" and valid_history(cmd, params) == 0:
            add_to_history(history, expenses)
        if cmd in commands:
            commands[cmd](expenses,params)  
        elif cmd == "help":
            give_help(params)
        elif cmd == "undo":
            undo_ui(history, expenses, params)
        elif cmd == "exit":
            return
        else:
            print("\nInvalid command\n")
