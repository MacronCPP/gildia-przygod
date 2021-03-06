package gbhelper.EventTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class EventGetItem extends EventType {
	int itemID, amount;
	public EventGetItem(String name, int itemID, int amount) {
		super(name, 2);
		this.itemID = itemID;
		this.amount = amount;
	}

	@Override
	public Data construct(String[] values) {
		return new EventGetItem(values[0], Integer.parseInt(values[1]), Integer.parseInt(values[2]));
	}

	@Override
	public String getBytes() {
		return itemID + ", " + amount + ", 0, 0";
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
