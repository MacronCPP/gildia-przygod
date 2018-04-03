package gbhelper.ItemTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Ammo extends ItemType {
	int additionalDamage;
	public Ammo(String name, int maxQuantity, int additionalDamage) {
		super(name, 6, maxQuantity);
		this.additionalDamage = additionalDamage;
	}

	@Override
	public int getByte() {
		return additionalDamage;
	}

	@Override
	public String[] getValues() {
		String ret[] =  {"Name", "Max quantity", "Additional damage"};
		return ret;
	}
	
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{Quantity: "+maxQuantity+", AddDMG: " + additionalDamage + "}");
		return allValuesProperty;
	}
	
	@Override
	public Data construct(String[] values) {
		return new Ammo(values[0], Integer.parseInt(values[1]), Integer.parseInt(values[2]));
	}
}
