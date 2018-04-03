package gbhelper.EventTypes;

import gbhelper.DatabaseManager.Data;
import gbhelper.EventConditionTypes.EventConditionItem;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class EventChangeTile extends EventType {
	int x, y, tile;
	public EventChangeTile(String name, int x, int y, int tile) {
		super(name, 3);
		this.x = x;
		this.y = y;
		this.tile = tile;
	}

	@Override
	public Data construct(String[] values) {
		return new EventChangeTile(values[0], Integer.parseInt(values[1]), Integer.parseInt(values[2]), Integer.parseInt(values[3]));
	}

	@Override
	public String getBytes() {
		char ret[] = {(char)x, (char)y, (char)tile};
		return x + ", " + y + ", " + tile + ", 0";
	}
		
	@Override
	public String[] getValues() {
		String ret[] =  {"Name", "X", "Y", "Tile"};
		return ret;
	}
		
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{X: "+ x +", Y: " + y + ", Tile: " + tile + "}");
		return allValuesProperty;
	}
}
