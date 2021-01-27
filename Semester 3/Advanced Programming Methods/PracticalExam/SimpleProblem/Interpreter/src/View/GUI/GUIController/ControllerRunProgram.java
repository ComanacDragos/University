package View.GUI.GUIController;

import Controller.Controller;
import Exceptions.MyException;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Values.IValue;
import Observer.MyObserver;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.util.Pair;

import java.util.*;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class ControllerRunProgram extends MyObserver {
    @FXML
    Button runOneStepButton;
    @FXML
    Button runAnotherProgramButton;
    @FXML
    Button openNewWindowButton;
    @FXML
    TableColumn<Pair<Integer, IValue>, Integer> heapAddressColumn;
    @FXML
    TableColumn<Pair<Integer, IValue>, IValue> heapValueColumn;
    @FXML
    TableColumn<Pair<String, IValue>, String> symbolsTableNameColumn;
    @FXML
    TableColumn<Pair<String, IValue>, IValue> symbolsTableValueColumn;
    @FXML
    Label numberOfProgramStatesLabel;
    @FXML
    TableView<Pair<Integer, IValue>> heapTableView;
    @FXML
    ListView<Integer> programIdsListView;
    @FXML
    ListView<IStatement> executionStackListView;
    @FXML
    ListView<String> outListView;
    @FXML
    ListView<String> fileTableListView;
    @FXML
    TableView<Pair<String, IValue>> symbolsTableView;

    Stage parentStage;
    Scene selectProgramsScene;

    Controller controller;

    @FXML
    void initialize(){
        this.programIdsListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);

        this.heapAddressColumn.setCellValueFactory(new PropertyValueFactory<>("key"));
        this.heapValueColumn.setCellValueFactory(new PropertyValueFactory<>("value"));

        this.symbolsTableNameColumn.setCellValueFactory(new PropertyValueFactory<>("key"));
        this.symbolsTableValueColumn.setCellValueFactory(new PropertyValueFactory<>("value"));

        this.heapTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        this.symbolsTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
    }

    public void setParentStage(Stage parentStage) {
        this.parentStage = parentStage;
    }

    public void setSelectProgramsScene(Scene selectProgramsScene) {
        this.selectProgramsScene = selectProgramsScene;
    }

    public void setController(Controller controller) {
        this.controller = controller;
        this.controller.emptyLogFile();
        this.controller.setExecutorService(Executors.newFixedThreadPool(2));
    }

    public void update(){
        try {
            this.setNumberOfProgramStatesLabel();
            this.setProgramIdsListView();

            if(!this.controller.getPrograms().isEmpty()) {
                this.setExecutionStackListView();
                this.setSymbolsTableView();
                this.setHeapTableView();
                this.setFileTableListView();
                this.setOutListView();
            }
        }
        catch (MyException exception){
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle(exception.getMessage());
            alert.showAndWait();
        }
    }

    void setNumberOfProgramStatesLabel(){
        this.numberOfProgramStatesLabel.setText("Number of program states: " + this.controller.getPrograms().size());
    }

    void setProgramIdsListView(){
        ObservableList<Integer> programIds = FXCollections.observableArrayList();

        programIds.addAll(
          this.controller
          .getPrograms()
          .stream()
          .map(ProgramState::getProgramId)
          .collect(Collectors.toList())
        );

        this.programIdsListView.setItems(programIds);
    }

    void setExecutionStackListView(){
        ProgramState program = this.getSelectedProgram();

        ObservableList<IStatement> statements = FXCollections.observableArrayList();

        statements.addAll(
                program.getExecutionStack()
                .stream()
                .collect(Collectors.toList())
        );

        this.executionStackListView.setItems(statements);
    }

    void setSymbolsTableView(){
        ProgramState program = this.getSelectedProgram();

        ObservableList<Pair<String, IValue>> variables = FXCollections.observableArrayList();

        variables.addAll(
                program.getSymbolsTable().stream()
                    .map(e -> new Pair<>(e.getKey(), e.getValue()))
                    .collect(Collectors.toList())
        );

        this.symbolsTableView.setItems(variables);
    }

    void setHeapTableView(){
        ProgramState program = this.getSelectedProgram();

        ObservableList<Pair<Integer, IValue>> memory = FXCollections.observableArrayList();

         memory.addAll(
                program.getHeap().stream()
                        .map(e -> new Pair<>(e.getKey(), e.getValue()))
                        .collect(Collectors.toList())
        );

        this.heapTableView.setItems(memory);
    }

    void setFileTableListView(){
       ProgramState program = this.getSelectedProgram();

        ObservableList<String> files = FXCollections.observableArrayList();

        files.addAll(
                program.getFileTable().stream()
                .map(Map.Entry::getKey)
                .collect(Collectors.toList())
        );

        this.fileTableListView.setItems(files);
    }

    void setOutListView(){
        ProgramState program = this.getSelectedProgram();

        ObservableList<String> out = FXCollections.observableArrayList();

        out.addAll(
                program.getOut().stream()
                        .map(IValue::toString)
                        .collect(Collectors.toList())
        );

        this.outListView.setItems(out);
    }

    ProgramState getSelectedProgram() throws MyException{
        Integer id = this.programIdsListView.getSelectionModel().getSelectedItem();

        if(!Objects.nonNull(id)){
            this.programIdsListView.getSelectionModel().selectIndices(0);
            id = this.programIdsListView.getItems().get(0);

        }
        Optional<ProgramState> program = this.controller.getProgram(id);
        if(program.isEmpty())
            throw new MyException("Program is done");
        return program.get();
    }

    public void handleRunAnotherProgram() {
        this.closeProgram();
        this.parentStage.setScene(this.selectProgramsScene);
    }

    public void handleRunOneStep() {
        List<ProgramState> programs = this.controller.removeCompletedPrograms(this.controller.getPrograms());

        if(programs.isEmpty()){
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setContentText("Program is done");
            alert.showAndWait();
            return;
        }
        this.controller.runGarbageCollector();

        try{
            this.controller.oneStepForAllPrograms(programs);
        }
        catch (MyException exception){
            this.closeProgram();
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setContentText(exception.getMessage());
            alert.showAndWait();
            return;
        }
        //this.update();
        programs = this.controller.removeCompletedPrograms(programs);

        if(programs.isEmpty()){
            this.closeProgram();
        }
    }

    void closeProgram(){
        this.controller.getExecutorService().shutdownNow();
        this.controller.setRepositoryPrograms(new LinkedList<>());
        this.programIdsListView.getItems().clear();
        this.setNumberOfProgramStatesLabel();
    }

    public void handleSelectProgram() {
        this.update();
    }

    public void handleOpenNewWindow() {
        if(this.controller.getPrograms().isEmpty()){
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setContentText("Program is done");
            alert.showAndWait();
            return;
        }
        try{
            Parent root;
            FXMLLoader runProgramLoader = new FXMLLoader();
            runProgramLoader.setLocation(getClass().getResource("../FXML/RunProgram.fxml"));
            root = runProgramLoader.load();

            ControllerRunProgram newController = runProgramLoader.getController();

            Stage newStage = new Stage();
            Scene scene = new Scene(root, 1024, 720);

            newController.setParentStage(newStage);
            newController.setController(this.controller);

            GridPane gridPane = (GridPane) root;

            gridPane.getChildren().stream()
            .filter(node ->
                    Objects.nonNull(node.getId())
                    && (node.getId().equals("runAnotherProgramButton")
                    || node.getId().equals("openNewWindowButton")))
            .collect(Collectors.toList())
            .forEach(gridPane.getChildren()::remove);

            this.controller.addObserver(newController);
            this.controller.notyfiObservers();

            newStage.setScene(scene);
            newStage.show();
        }
        catch (Exception exc){
            exc.printStackTrace();
            System.exit(1);
        }
    }
}
