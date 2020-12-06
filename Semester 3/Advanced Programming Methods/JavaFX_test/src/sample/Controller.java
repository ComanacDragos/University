package sample;

import javafx.scene.control.Button;
import javafx.scene.control.Label;

public class Controller {
    public Button myButton;
    public Label myLabel;

    public void handleButton() {
        this.myLabel.setText("");
    }
}
