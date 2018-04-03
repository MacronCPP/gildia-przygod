package gbhelper.ItemTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Potion extends ItemType {

	int value;
	public Potion(String name, int maxQuantity, int value) {
		super(name, 7, maxQuantity);
		this.value = value;
	}

	@Override
	public int getByte() {
		// TODO Auto-generated method stub
		return value;
	}

	@Override
	public String[] getValues() {
		String ret[] =  {"Name", "Max quantity", "HP value"};
		return ret;
	}
	
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{Quantity: "+maxQuantity+", HP value: " + value + "}");
		return allValuesProperty;
	}
	
	@Override
	public Data construct(String[] values) {
		return new Potion(values[0], Integer.parseInt(values[1]), Integer.parseInt(values[2]));
	}

}
