package gbhelper.ItemTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Armor extends ItemType {
	int value;
	public Armor(String name, int maxQuantity, int value) {
		super(name, 2, maxQuantity);
		this.value = value;
	}
	@Override
	public int getByte() {
		return value;
	}
	
	@Override
	public String[] getValues() {
		String ret[] =  {"Name", "Max quantity", "Armor value"};
		return ret;
	}
	
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{Quantity: "+maxQuantity+", Value: " + value + "}");
		return allValuesProperty;
	}
	@Override
	public Data construct(String[] values) {
		return new Armor(values[0], Integer.parseInt(values[1]), Integer.parseInt(values[2]));
	}
}
