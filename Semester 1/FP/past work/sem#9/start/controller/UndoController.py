class UndoController:
    def __init__ (self):
        #history of program operations (the undoable ones)
        self._history = []
        #index of operation to undo/redo
        self._index = 0

        #are we during an undo/redo operation

        self._duringUndoRedo = False
    

    def recordOperation (self, operation):
        '''
        Record how to undo/redo a program operation
        '''
        # might not be enough=
        #how to clear the history list if a different operation is made after some undo's
        
        if self._duringUndoRedo == True:
            return


        if self._index < len(self._history):
            self._history = self._history[:self._index]
        

        self._history.append(operation)
        self._index += 1

    def undo (self):
        if self._index == 0:
            raise ValueError("No more undos!")

        self._duringUndoRedo = True

        self._index -= 1
        self._history[self._index].undo()

        self._duringUndoRedo = False

    def redo (self):
        if self._index == len(self._history):
            raise ValueError("No more redos!")
        
        self._duringUndoRedo = True

        self._history[self._index].redo()
        self._history[self._index] += 1

        self._duringUndoRedo = False
    
# remember which function to call and which parameters
# implementation of command design pattern
class FunctionCall:
    def __init__ (self, function, *parameters):
        self._function = function
        self._params = parameters

    # () -> function call operator
    def call (self):
        self._function(*self._params)




#undo/redo are the sides of the same coin

    class Operation:
        '''
        Encodes an operation that happened in the program
        '''
        def __init__ (self, undoFunction, redoFunction):
            self._undo = undoFunction
            self._redo = redoFunction
        
        def undo (self):
            self._undo.call()
    
        def redo (self):
            self._redo.call()

'''
Implement a cascadedOperation class which uses a list of operations
in undo() you take each operation and call undo ()on it
redo likewise
'''

