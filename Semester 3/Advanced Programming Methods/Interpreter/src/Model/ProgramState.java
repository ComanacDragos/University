package Model;

import Model.ADTs.*;
import Model.Statements.IStatement;
import Model.Values.IValue;

import java.io.BufferedReader;
import java.util.Map;
import java.util.stream.Collectors;

public class ProgramState {
    MyIStack<IStatement> executionStack;
    MyIDictionary<String, IValue> symbolsTable;
    MyIList<IValue> out;
    IStatement originalProgram;
    MyIDictionary<String, BufferedReader> fileTable;
    MyHeap heap;

    public ProgramState(MyIStack<IStatement> executionStack, MyIDictionary<String, IValue> symbolsTable, MyIList<IValue> out, MyIDictionary<String, BufferedReader> fileTable, MyHeap heap, IStatement originalProgram){
        this.executionStack = executionStack;
        this.symbolsTable = symbolsTable;
        this.out = out;
        this.originalProgram = originalProgram;
        this.fileTable = fileTable;
        this.heap = heap;
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

    public MyIDictionary<String, BufferedReader> getFileTable() {
        return fileTable;
    }

    public void setFileTable(MyIDictionary<String, BufferedReader> fileTable) {
        this.fileTable = fileTable;
    }

    public MyHeap getHeap() {
        return heap;
    }

    public void setHeap(MyHeap heap) {
        this.heap = heap;
    }

    public ProgramState deepCopy(){
        MyIStack<IStatement> newExecutionStack = new MyStack<>();
        MyIDictionary<String, IValue> newSymbolsTable = new MyDictionary<>();
        MyIList<IValue> newOut = new MyList<>();
        MyIDictionary<String, BufferedReader> newFileTable = new MyDictionary<>();
        MyHeap heap = new MyHeap();

        this.executionStack.stream().map(
                IStatement::deepCopy
        ).forEach(newExecutionStack::push);

        this.symbolsTable.stream().collect(
                Collectors.toMap(Map.Entry::getKey, e -> e.getValue().deepCopy())
        ).entrySet().stream().forEach(
                e -> newSymbolsTable.put(e.getKey(), e.getValue())
        );

        this.out.stream().map(
                IValue::deepCopy
        ).forEach(newOut::add);

        this.fileTable.stream().forEach(
                e -> newFileTable.put(e.getKey(), e.getValue())
        );

        this.heap.stream().forEach(
                e -> heap.put(e.getValue().deepCopy())
        );

        return new ProgramState(newExecutionStack, newSymbolsTable, newOut, newFileTable, heap, this.originalProgram.deepCopy());
    }

    @Override
    public String toString() {
        return "Execution stack\n" +this.executionStack.toString() +
                "Symbols table\n" + this.symbolsTable.toString() +
                "Out\n" + this.out.toString() +
                "File table\n" + this.fileTable.stream().map(Map.Entry::getKey).collect(Collectors.joining("\n")) +
                "Heap\n" + this.heap.toString()
                +"\n\n";
    }
}


