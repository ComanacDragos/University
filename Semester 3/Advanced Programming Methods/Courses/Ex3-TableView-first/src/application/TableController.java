package application;

import javafx.fxml.FXML;

import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;

import javafx.scene.control.TableView;

import javafx.scene.control.TableColumn;

public class TableController {
	@FXML
	private TableView<Person> tableView;
	@FXML
	private TableColumn<Person,String> firstName;
	@FXML
	private TableColumn<Person,String> lastName;
	@FXML
	private TableColumn<Person,String> emailAddress;
	@FXML
	private TextField firstNameField;
	@FXML
	private TextField lastNameField;
	@FXML
	private TextField emailField;

	// Event Listener on Button.onAction
	@FXML
	public void addPerson(ActionEvent event) {
		ObservableList<Person> data = tableView.getItems();
        data.add(new Person(firstNameField.getText(),
            lastNameField.getText(),
            emailField.getText()
        ));
                   
        firstNameField.setText("");
        lastNameField.setText("");
        emailField.setText("");
	}
	
	@FXML
	public void initialize() {
		firstName.setCellValueFactory(new PropertyValueFactory<Person,String>("firstName")); 
		lastName.setCellValueFactory(new PropertyValueFactory<Person,String>("lastName")); 
		emailAddress.setCellValueFactory(new PropertyValueFactory<Person,String>("email")); 
		tableView.setItems(getPersonList());
	}
	
	 private ObservableList<Person> getPersonList() {
		 
	      Person p1 = new Person("Michael","Brown","m@example.com");
	      
	 
	      ObservableList<Person> list = FXCollections.observableArrayList(p1);
	      return list;
	  }
}

