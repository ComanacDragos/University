# add <student id>, <name>, <grade>
# delete student <student id>
# list
# exit
# help
# command_word param1,param2
def get_id (student):
    return student[0]

def get_name (student):
    return student[1]

def get_grade (student):
    return student[2]


def create_student (sid,name,grade):  #non ui
    '''
    Create a student
    params:
        sid - id
        name - string of len>=3
        grade - int between 1 and 10
    output:
        succes - return the student
        errpr - return none
    '''
    if len(name) < 3:
        return None
    grade = int(grade)
    if grade < 1 or grade > 10:
        return None
    return [sid,name,grade]

def find_student (studentList,sid): 
    '''
    Find student having the given id
    params:
    output:
        student having given id
        None, student with given id not in list
    '''
    for s in studentList:
        if get_id(s) == sid:
            #this is the student you are looking for
            return s
    return None


def add_student (studentList, student):
    '''
    Add student to list
    params:
        studentList - the list of students
        student - the student
    output:
        0 - succes
        1 - Duplicate student id
    '''
    if find_student(studentList, get_id(student)) != None:
        return 1 
    studentList.append(student)
    return 0

def readCommand ():  #ui
    '''
    read and parse the user's commnad
    '''
    #cmd = input("command: ")
    #cmd = 'add 123,     Popescu Elena, 9'
    #cmd = 'exit'
    #1. separate the command word from the list of parameters
    #2. identify parameters
    #3. return tuple (command, list of params)
    cmd = input("command= ")
    idx=cmd.find(" ")
    if idx == -1:
        return (cmd, [])
    command = cmd[:idx]
    params = cmd[idx:]
    params = params.split(",")
    for i in range(len(params)):
        params[i] = params[i].strip()
    return (command,params)

def add_student_ui (studentList, params): #ui
    if len(params) != 3:
        print("Bad student parameters")
        return
    s = create_student(params[0],params[1],params[2])
    if s == None:
        print("invalid student data")
        return
    if add_student(studentList,s) == 1:
        print("Duplicate student id!")

def start(): #ui
    studentList=[]
    while True:
        print(studentList)
        # read user command
        cmdtuple = readCommand()
        cmd = cmdtuple[0]
        params = cmdtuple[1]
        if cmd == 'add':
            add_student_ui(studentList, params)
        elif cmd == 'exit':
            return
        else:
            print("bad command")
        

start()
# 1. function signature
# 2. specification
# 3. we can wrtite test

# what do test functions do?
# 1. take no parameters -> we want them to have no context
# 2. Have no user input/output
# 3. If the code is correct, do nothing visible
# 4. if the code has an error -> show that there is an error
    
def test_add_student ():
    slist = []
    s1 = create_student(1,"Marie",10)
    assert add_student(slist,s1)  == 0
    assert len(slist) == 1
    assert get_id(slist[0]) == 1

    assert add_student(slist,s1) == 1
    assert len(slist) == 1
    # assert <expression>
        

x = test_add_student
x() # () - function call operator
