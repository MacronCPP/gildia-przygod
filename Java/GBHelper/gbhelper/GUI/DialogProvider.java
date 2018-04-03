package gbhelper.GUI;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Dialog;
import javafx.scene.control.Label;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;

public class DialogProvider {
	public static String[] askForData(String title, String description, String... data) {
		Dialog<String[]> dialog = new Dialog<>();
		dialog.setTitle(title);
		dialog.setHeaderText(description);
		List<TextField> fields = new ArrayList<TextField>();
		
		GridPane sector = new GridPane();
		sector.setHgap(10);
		sector.setVgap(10);
		sector.setPadding(new Insets(20, 150, 10, 10));
		
		for(int i = 0; i < data.length; i++) {
			fields.add(new TextField());
			sector.add(new Label(data[i] + ":"), 0, i);
			sector.add(fields.get(i), 1, i);
		}
		
		ButtonType ok = new ButtonType("Ok");
		ButtonType cancel = new ButtonType("Cancel");
		
		dialog.getDialogPane().getButtonTypes().setAll(ok, cancel);

		dialog.getDialogPane().setContent(sector);
		
		dialog.setResultConverter(dialogButton -> {
		    if (dialogButton == ok) {
		        String[] ret = new String[fields.size()];
		        for(int i = 0; i < fields.size(); i++) {
		        	ret[i] = fields.get(i).getText();
		        }
		        return ret;
		    }
		    return new String[0];
		});

		Optional<String[]> result = dialog.showAndWait();	
		if(result.isPresent())
			return result.get();
		else 
			return null;
	}
	
	public static String[] askForData(String title, String description, DataField... data) {
		Dialog<String[]> dialog = new Dialog<>();
		dialog.setTitle(title);
		dialog.setHeaderText(description);
		List<Node> fields = new ArrayList<>();
		
		GridPane sector = new GridPane();
		sector.setHgap(10);
		sector.setVgap(10);
		sector.setPadding(new Insets(20, 150, 10, 10));
		
		for(int i = 0; i < data.length; i++) {
			fields.add(data[i].getNode());
			sector.add(new Label(data[i].getName() + ":"), 0, i);
			sector.add(fields.get(i), 1, i);
		}
		
		ButtonType ok = new ButtonType("Ok");
		ButtonType cancel = new ButtonType("Cancel");
		
		dialog.getDialogPane().getButtonTypes().setAll(ok, cancel);

		dialog.getDialogPane().setContent(sector);
		
		dialog.setResultConverter(dialogButton -> {
		    if (dialogButton == ok) {
		        String[] ret = new String[fields.size()];
		        for(int i = 0; i < fields.size(); i++) {
		        	ret[i] = data[i].getValue();
		        }
		        return ret;
		    }
		    return new String[0];
		});

		Optional<String[]> result = dialog.showAndWait();	
		if(result.isPresent())
			return result.get();
		else 
			return null;
	}
	
	public static String showOptions(String title, String description, String... data) {
		Dialog<String> dialog = new Dialog<>();
		dialog.setTitle(title);
		dialog.setHeaderText(description);
		List<ButtonType> buttons = new ArrayList<ButtonType>();
		
		for(int i = 0; i < data.length; i++) {
			buttons.add(new ButtonType(data[i]));
		}

		dialog.getDialogPane().getButtonTypes().setAll(buttons);
		
		dialog.setResultConverter(dialogButton -> {
		    for(ButtonType button : buttons) {
		    	if(button.equals(dialogButton)) {
		    		return button.getText();
		    	}
		    }
		    return "";
		});

		Optional<String> result = dialog.showAndWait();	
		if(result.isPresent())
			return result.get();
		else 
			return "";
	}
	
	public static <T> void showTable(String title, String description, TableView<T> table) {
		Dialog<String[]> dialog = new Dialog<>();
		dialog.setTitle(title);
		dialog.setHeaderText(description);
		
		GridPane sector = new GridPane();
		sector.setHgap(10);
		sector.setVgap(10);
		sector.add(table, 0, 0);
		
		ButtonType ok = new ButtonType("Ok");
		
		dialog.getDialogPane().getButtonTypes().setAll(ok);
		dialog.getDialogPane().setContent(sector);
		dialog.showAndWait();
	}
	
	public static <T> boolean showTableSeries(String title, String description, TableView<T> table) {
		Dialog<Boolean> dialog = new Dialog<>();
		dialog.setTitle(title);
		dialog.setHeaderText(description);
		
		GridPane sector = new GridPane();
		sector.setHgap(10);
		sector.setVgap(10);
		sector.add(table, 0, 0);
		
		ButtonType next = new ButtonType("Next");
		ButtonType cancel = new ButtonType("Cancel");
		
		dialog.getDialogPane().getButtonTypes().setAll(next, cancel);
		dialog.getDialogPane().setContent(sector);
		
		dialog.setResultConverter(dialogButton -> {
		    if (dialogButton == next) return true;
		    else return false;
		});
		
		Optional<Boolean> result = dialog.showAndWait();	
		if(result.isPresent())
			return result.get();
		else 
			return false;
	}
	
	public static void errorAlert(String title, String description) {
		Alert alert = new Alert(AlertType.ERROR);
		alert.setTitle(title);
		alert.setHeaderText(null);
		alert.setContentText(description);

		alert.showAndWait();
	}
	
	public static void infoAlert(String title, String description) {
		Alert alert = new Alert(AlertType.INFORMATION);
		alert.setTitle(title);
		alert.setHeaderText(null);
		alert.setContentText(description);

		alert.showAndWait();
	}
	
	public static boolean askForConfirmation(String title, String description) {
		Alert alert = new Alert(AlertType.CONFIRMATION);
		alert.setTitle(title);
		alert.setHeaderText(null);
		alert.setContentText(description);

		Optional<ButtonType> result = alert.showAndWait();
		boolean ret = false;
		if (result.get() == ButtonType.OK){
			ret = true;
		} else {
			ret = false;
		}
		
		return ret;
	}
}
