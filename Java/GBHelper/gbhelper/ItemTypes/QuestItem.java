package gbhelper.ItemTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class QuestItem extends ItemType {
	
	public QuestItem(String name, int maxQuantity) {
		super(name, 2, maxQuantity);
	}

	@Override
	public int getByte() {
		return 0;
	}
	
	@Override
	public String[] getValues() {
		String ret[] =  {"Name", "Max quantity"};
		return ret;
	}
	
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{Quantity: "+maxQuantity+"}");
		return allValuesProperty;
	}
	
	@Override
	public Data construct(String[] values) {
		return new QuestItem(values[0], Integer.parseInt(values[1]));
	}
}
