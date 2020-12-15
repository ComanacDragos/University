package View.GUI;

import View.GUI.GUIController.ControllerSelectProgram;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public class GUIView extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception{
        FXMLLoader selectProgramLoader = new FXMLLoader();
        selectProgramLoader.setLocation(getClass().getResource("FXML/SelectProgram.fxml"));
        GridPane root = selectProgramLoader.load();

        ControllerSelectProgram controller = selectProgramLoader.getController();

        controller.setParentStage(primaryStage);

        Scene scene = new Scene(root, 1024, 720);
        //scene.getStylesheets().add(getClass().getResource("CSS/main.css").toExternalForm());

        primaryStage.setTitle("Interpreter");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
