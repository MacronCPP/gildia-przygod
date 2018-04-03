package gbhelper.EventConditionTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class EventConditionItem extends EventConditionType {
	int itemID, amount;
	public EventConditionItem(String name, int itemID, int amount) {
		super(name, 1);
		this.itemID = itemID;
		this.amount = amount;
	}

	@Override
	public Data construct(String[] values) {
		return new EventConditionItem(values[0], Integer.parseInt(values[1]), Integer.parseInt(values[2]));
	}

	@Override
	public String getBytes() {
		return itemID + ", " + amount + ", 0";
	}
		
	@Override
	public String[] getValues() {
		String ret[] =  {"Name", "ItemID", "Amount"};
		return ret;
	}
		
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{ItemID: "+itemID+", Amount: " + amount + "}");
		return allValuesProperty;
	}

}
