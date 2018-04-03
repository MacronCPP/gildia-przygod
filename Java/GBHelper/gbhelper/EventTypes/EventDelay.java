package gbhelper.EventTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class EventDelay extends EventType {
	int time;
	public EventDelay(String name, int time) {
		super(name, 7);
		this.time = time;
	}

	@Override
	public Data construct(String[] values) {
		return new EventDelay(values[0], Integer.parseInt(values[1]));
	}

	@Override
	public String getBytes() {
		return time/256 + ", " + time % 256 + ", 0, 0";
	}
		
	@Override
	public String[] getValues() {
		String ret[] =  {"Name", "Time"};
		return ret;
	}
		
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{Time(ms): "+time+"}");
		return allValuesProperty;
	}

}
