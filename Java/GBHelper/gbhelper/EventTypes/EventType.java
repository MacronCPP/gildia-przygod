package gbhelper.EventTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public abstract class EventType implements Data {
	int ID;
	String name;
	EventType(String name, int ID) {
		this.ID = ID;
		this.name = name;
	}
	
	transient StringProperty IDProperty;
	public int getID() {
		return ID;
	}
	
	public StringProperty getIDProperty() {
		if(IDProperty == null) 
			IDProperty = new SimpleStringProperty(Integer.toString(ID));
		return IDProperty;
	}
	
	transient StringProperty IndexProperty;
	public StringProperty getIndexProperty(int index) {
		IndexProperty = new SimpleStringProperty(Integer.toString(index));
		return IndexProperty;
	}
	
	abstract public String getBytes();
	
	transient StringProperty nameProperty;
	transient StringProperty allValuesProperty;
	
	public StringProperty getName() {
		if(nameProperty == null) 
			nameProperty = new SimpleStringProperty(name);
		return nameProperty;
	}
	
	public abstract StringProperty getAllValues();
	
	public abstract String[] getValues();

	public String getAdditionalString() {
		return null;
	}
}
