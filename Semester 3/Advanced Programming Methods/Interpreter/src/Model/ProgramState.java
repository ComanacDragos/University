package Model;

import Exceptions.EmptyCollection;
import Exceptions.MyException;
import Model.ADTs.*;
import Model.Statements.IStatement;
import Model.Values.IValue;

import java.io.BufferedReader;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;

public class ProgramState {
    MyIStack<IStatement> executionStack;
    MyIDictionary<String, IValue> symbolsTable;
    MyIList<IValue> out;
    IStatement originalProgram;
    MyIDictionary<String, BufferedReader> fileTable;
    MyHeap heap;
    Integer programId;
    static AtomicInteger currentId = new AtomicInteger(0);

    public ProgramState(MyIStack<IStatement> executionStack, MyIDictionary<String, IValue> symbolsTable, MyIList<IValue> out, MyIDictionary<String, BufferedReader> fileTable, MyHeap heap, IStatement originalProgram){
        this.executionStack = executionStack;
        this.symbolsTable = symbolsTable;
        this.out = out;
        this.originalProgram = originalProgram;
        this.fileTable = fileTable;
        this.heap = heap;
        this.programId = ProgramState.currentId.incrementAndGet();
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

    public MyIStack<IStatement> executionStackDeepCopy(){
        MyIStack<IStatement> newExecutionStack = new MyStack<>();
        this.executionStack.stream().map(
                        IStatement::deepCopy
                ).forEach(newExecutionStack::push);
        return newExecutionStack;
    }

    public MyIDictionary<String, IValue> symbolsTableDeepCopy(){
        MyIDictionary<String, IValue> newSymbolsTable = new MyDictionary<>();
        this.symbolsTable.stream().collect(
                Collectors.toMap(Map.Entry::getKey, e -> e.getValue().deepCopy())
        ).entrySet().stream().forEach(
                e -> newSymbolsTable.put(e.getKey(), e.getValue())
        );
        return newSymbolsTable;
    }

    public MyIList<IValue> outDeepCopy(){
        MyIList<IValue> newOut = new MyList<>();

        this.out.stream().map(
                IValue::deepCopy
        ).forEach(newOut::add);
        return newOut;
    }

    public MyIDictionary<String, BufferedReader> fileTableDeepCopy(){
        MyIDictionary<String, BufferedReader> newFileTable = new MyDictionary<>();
        this.fileTable.stream().forEach(
                e -> newFileTable.put(e.getKey(), e.getValue())
        );
        return newFileTable;
    }

    public MyHeap heapDeepCopy(){
        MyHeap newHeap = new MyHeap();

        this.heap.stream().forEach(
                e -> newHeap.put(e.getKey(), e.getValue().deepCopy())
        );
        return newHeap;
    }

    public ProgramState deepCopy(){

        return new ProgramState(this.executionStackDeepCopy(),
                                this.symbolsTableDeepCopy(),
                                this.outDeepCopy(),
                                this.fileTableDeepCopy(),
                                this.heapDeepCopy(),
                                this.originalProgram.deepCopy());
    }

    public Boolean isNotCompleted(){
        return !this.executionStack.isEmpty();
    }

    public ProgramState executeOneStep() throws MyException {
        if(this.executionStack.isEmpty())
            throw new EmptyCollection("Empty execution stack");
        return this.executionStack.pop().execute(this);
    }

    @Override
    public String toString() {
        return  "Program: " + this.programId + '\n' +
                "Execution stack\n" +this.executionStack.toString() +
                "Symbols table\n" + this.symbolsTable.toString() +
                "Out\n" + this.out.toString() +
                "File table\n" + this.fileTable.stream().map(Map.Entry::getKey).collect(Collectors.joining("\n")) +
                "Heap\n" + this.heap.toString()
                +"\n\n";
    }
}


