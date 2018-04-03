package gbhelper.GUI;

import javafx.beans.value.ObservableValue;
import javafx.scene.control.TableColumn.CellDataFeatures;
import javafx.util.Callback;

// Ta klasa jest jedynie w celu przechowywania opisu kolumny i latwego dodawania nowych kolumn do tabel

public class ColumnDescription<T> {
	public String name;
	public Callback<CellDataFeatures<T, String>, ObservableValue<String>> factory;
	
	public ColumnDescription(String name, Callback<CellDataFeatures<T, String>, ObservableValue<String>> factory) {
		this.name = name;
		this.factory = factory;
	}
}
