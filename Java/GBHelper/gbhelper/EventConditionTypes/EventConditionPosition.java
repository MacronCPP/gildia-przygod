package gbhelper.EventConditionTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class EventConditionPosition extends EventConditionType {
	int x, y;
	public EventConditionPosition(String name, int x, int y) {
		super(name, 0);
		this.x = x;
		this.y = y;
	}

	@Override
	public Data construct(String[] values) {
		return new EventConditionPosition(values[0], Integer.parseInt(values[1]), Integer.parseInt(values[2]));
	}

	@Override
	public String getBytes() {
		return x + ", " + y + ", 0";
	}
		
	@Override
	public String[] getValues() {
		String ret[] =  {"Name", "X", "Y"};
		return ret;
	}
		
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{X: "+x+", Y: " + y + "}");
		return allValuesProperty;
	}

}
