package gbhelper.EventTypes;

import gbhelper.DatabaseManager.Data;
import gbhelper.EventConditionTypes.EventConditionItem;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class EventChangeMap extends EventType {
	int x, y, bank;
	String map;
	public EventChangeMap(String name, String map, int x, int y, int bank) {
		super(name, 4);
		this.x = x;
		this.y = y;
		this.bank = bank;
		this.map = map;
	}

	@Override
	public Data construct(String[] values) {
		return new EventChangeMap(values[0], values[1], Integer.parseInt(values[2]), Integer.parseInt(values[3]), Integer.parseInt(values[4]));
	}

	@Override
	public String getBytes() {
		return "0, 0/*POINTER" + map + "*/, " + (((bank&24)<<5) + x) + ", " + (((bank & 7)<<5)+y) + "";
	}
		
	@Override
	public String[] getValues() {
		String ret[] =  {"Name",  "Map", "X", "Y", "Bank"};
		return ret;
	}
		
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{X: "+ x +", Y: " + y + ", Map: " + map + ", Bank: " + bank + "}");
		return allValuesProperty;
	}
}
