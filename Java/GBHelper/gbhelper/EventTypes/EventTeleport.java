package gbhelper.EventTypes;

import gbhelper.DatabaseManager.Data;
import gbhelper.EventConditionTypes.EventConditionItem;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class EventTeleport extends EventType {
	int x, y;
	public EventTeleport(String name, int x, int y) {
		super(name, 6);
		this.x = x;
		this.y = y;
	}

	@Override
	public Data construct(String[] values) {
		return new EventTeleport(values[0], Integer.parseInt(values[1]), Integer.parseInt(values[2]));
	}

	@Override
	public String getBytes() {
		char ret[] = {(char)x, (char)y};
		return x + ", " + y + ", 0, 0";
	}
		
	@Override
	public String[] getValues() {
		String ret[] =  {"Name", "X", "Y"};
		return ret;
	}
		
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{X: "+ x +", Y: " + y + "}");
		return allValuesProperty;
	}
}
