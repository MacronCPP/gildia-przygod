package gbhelper.DatabaseManager;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import gbhelper.GUI.ColumnDescription;
import gbhelper.GUI.DataField;
import gbhelper.GUI.DialogProvider;
import gbhelper.GUI.OnSector;
import gbhelper.GUI.TableProvider;
import gbhelper.GUI.TextDataField;
import javafx.scene.control.TableView;
import javafx.scene.layout.GridPane;

public class DatabaseManager<T extends Data> implements Serializable{
	private static final long serialVersionUID = 1L;
	transient TableView<Data> table;
	transient List<TypeRepresentation> dataTypes;
	List<Data> list;
	transient List<DataField> preferredFields;
	transient GridPane mainPane, buttonPane;
	
	public class TypeRepresentation {
		String name;
		T dummy;
		
		public TypeRepresentation(String name, T dummy) {
			this.name = name;
			this.dummy = dummy;
		}
	}
	
	public List<Data> getList() {
		return list;
	}
	
	public void load(DatabaseManager<T> data) {
		list = data.list;
		updateTable();
	}
	
	public GridPane getButtonPane() {
		return buttonPane;
	}
	
	public void updateTable() {
		if(table == null) 
			return;
		table.getItems().removeAll(list);
		table.setItems(TableProvider.makeTableList(list));
	}
	
	public void assignButtons() {
		buttonPane = new GridPane();
		for(TypeRepresentation representation : dataTypes) {
			OnSector.buildAddButton("Add " + representation.name, buttonPane).setOnMouseClicked((ev) -> {
				DataField packedFields[] = new DataField[representation.dummy.getValues().length];
				try {
					String names[] = representation.dummy.getValues();
					for(int i = 0; i < names.length; i++) {
						boolean found = false;
						for(DataField field : preferredFields) {
							if(field.getName().equals(names[i])) {
								packedFields[i] = field;
								found = true;
								break;
							}
						}
						if(!found) {
							packedFields[i] = new TextDataField(names[i]);
						}
					}
					String values[] = DialogProvider.askForData("Add new " + representation.name, null, packedFields);
					if(values == null || values.length == 0)
						return;
					list.add(representation.dummy.construct(values));
					updateTable();
				}
				catch(Exception ex) {
					DialogProvider.errorAlert("Couldn't add type", "Wrong data format!");
					ex.printStackTrace();
				}
			});
		}
		OnSector.centerEveryNode(buttonPane);
		mainPane.add(buttonPane, 1, 0);
	}
	
	public void init(GridPane pane, int width, int height, ColumnDescription<Data>... descriptions) {
		this.mainPane = pane;
		table = TableProvider.makeTable(descriptions);
		table.setMinSize(width, height);
	}
	public DatabaseManager() {
		dataTypes = new ArrayList<>();
		list = new ArrayList<>();
		preferredFields = new ArrayList<>();
	}
	
	public void addType(String name, T type) {
		dataTypes.add(new TypeRepresentation(name, type));
	}
	
	public void addPreferredField(DataField field) {
		preferredFields.add(field);
	}
	
	public void addPreferredFields(DataField...fields) {
		for(DataField field : fields) 
			preferredFields.add(field);
	}
	
	public void addTypes(TypeRepresentation...representations) {
		for(TypeRepresentation representation : representations)
			dataTypes.add(representation);
	}
	
	public void run() {
		assignButtons();
		mainPane.add(table, 0, 0);
	}
}
