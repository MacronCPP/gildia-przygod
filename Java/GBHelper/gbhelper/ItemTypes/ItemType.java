package gbhelper.ItemTypes;

import java.io.Serializable;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public abstract class ItemType implements Serializable, Data {
	int maxQuantity, ID;
	String name;
	ItemType(String name, int ID, int maxQuantity) {
		this.ID = ID;
		this.maxQuantity = maxQuantity;
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
	
	abstract public int getByte();
	
	public int getMaxQuantity() {
		return maxQuantity;
	}
	
	transient StringProperty nameProperty;
	transient StringProperty allValuesProperty;
	
	public StringProperty getName() {
		if(nameProperty == null) 
			nameProperty = new SimpleStringProperty(name);
		return nameProperty;
	}
	
	public abstract StringProperty getAllValues();
	
	public abstract String[] getValues();
}
