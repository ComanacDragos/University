package Model;

import Model.ADTs.MyIDictionary;
import Model.ADTs.MyIList;
import Model.ADTs.MyIStack;
import Model.Statements.IStatement;
import Model.Values.IValue;

import java.io.BufferedReader;

public class ProgramState {
    MyIStack<IStatement> executionStack;
    MyIDictionary<String, IValue> symbolsTable;
    MyIList<IValue> out;
    IStatement originalProgram;
    MyIDictionary<String, BufferedReader> fileTable;

    public ProgramState(MyIStack<IStatement> executionStack, MyIDictionary<String, IValue> symbolsTable, MyIList<IValue> out, IStatement originalProgram){
        this.executionStack = executionStack;
        this.symbolsTable = symbolsTable;
        this.out = out;
        this.originalProgram = originalProgram;
    }

    public IStatement getOriginalProgram() {
        return originalProgram;
    }

    public MyIDictionary<String, IValue> getSymbolsTable() {
        return symbolsTable;
    }

    public MyIList<IValue> getOut() {
        return out;
    }

    public MyIStack<IStatement> getExecutionStack() {
        return executionStack;
    }

    public void setExecutionStack(MyIStack<IStatement> executionStack) {
        this.executionStack = executionStack;
    }

    public void setOriginalProgram(IStatement originalProgram) {
        this.originalProgram = originalProgram;
    }

    public void setOut(MyIList<IValue> out) {
        this.out = out;
    }

    public void setSymbolsTable(MyIDictionary<String, IValue> symbolsTable) {
        this.symbolsTable = symbolsTable;
    }


    @Override
    public String toString() {
        return "Execution stack\n" +this.executionStack.toString() +
                "Symbols table\n" + this.symbolsTable.toString() +
                "Out\n" + this.out.toString();
                //"\n" + this.originalProgram.toString() +
    }
}


