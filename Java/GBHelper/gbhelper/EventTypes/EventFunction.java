package gbhelper.EventTypes;

import gbhelper.DatabaseManager.Data;
import gbhelper.EventConditionTypes.EventConditionItem;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class EventFunction extends EventType {
	String function;
	public EventFunction(String name, String function) {
		super(name, 31);
		this.function = function;
	}

	@Override
	public Data construct(String[] values) {
		return new EventFunction(values[0], values[1]);
	}

	@Override
	public String getBytes() {
		return "0, 0/*POINTER" + function + "*/, ";
	}
		
	@Override
	public String[] getValues() {
		String ret[] =  {"Name", "Function"};
		return ret;
	}
		
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{Function: "+ function + "}");
		return allValuesProperty;
	}
}
