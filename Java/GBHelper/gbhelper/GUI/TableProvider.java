package gbhelper.GUI;
import java.util.ArrayList;
import java.util.List;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;

public class TableProvider {
	@SafeVarargs
	public static <T> TableView<T> makeTable(ColumnDescription<T>... descriptions) {
		TableView<T> table = new TableView<>();
		
		List<TableColumn<T, String>> columns = new ArrayList<TableColumn<T, String>>();
		
		for(ColumnDescription<T> description : descriptions) {
			TableColumn<T, String> column = new TableColumn<T, String>(description.name);
			column.setCellValueFactory(description.factory);
			columns.add(column);
		}
		
		table.getColumns().setAll(columns);
		return table;
	}
	
	public static <T> ObservableList<T> makeTableList(List<T> list){
		ObservableList<T> ret = FXCollections.observableArrayList();
		ret.addAll(list);
		return ret;
	}

	
}
