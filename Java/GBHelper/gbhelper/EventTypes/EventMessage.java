package gbhelper.EventTypes;

import gbhelper.DatabaseManager.Data;
import gbhelper.EventConditionTypes.EventConditionItem;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class EventMessage extends EventType {
	String message;
	int bank;
	boolean windowIn, windowOut, dontChangeBank;
	public EventMessage(String name, String message, int bank, boolean windowIn, boolean windowOut, boolean dontChangeBank) {
		super(name, 0);
		this.message = message;
		this.bank = bank;
		this.windowIn = windowIn;
		this.windowOut = windowOut;
		this.dontChangeBank = dontChangeBank;
	}

	@Override
	public Data construct(String[] values) {
		return new EventMessage(values[0], values[2], Integer.parseInt(values[1]), Boolean.parseBoolean(values[3]), Boolean.parseBoolean(values[4]), Boolean.parseBoolean(values[5]));
	}
	
	@Override
	public String getAdditionalString() {
		return "const char " + name + "MessageString[] = \"" + message + ";";
	}

	@Override
	public String getBytes() {
		String ret =  "0, 0/*pointer"+name+"MessageString"+"*/, " + bank + ", ";
		boolean wasFlag = false;
		if(windowIn) {
			wasFlag = true;
			ret += "FLAG_WINDOW_IN";
		}
		if(windowOut) {
			if(wasFlag)
				ret += " | ";
			ret += "FLAG_WINDOW_OUT";
			wasFlag = true;
		}
		if(dontChangeBank) {
			if(wasFlag) 
				ret += " | ";
			ret += "FLAG_DONT_CHANGE_BANK";
			wasFlag = true;
		}
		return ret;
	}
		
	@Override
	public String[] getValues() {
		String ret[] =  {"Name", "Bank", "Message", "Window in", "Window out", "Don't change bank"};
		return ret;
	}
		
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{Bank: " + bank + ", Message: "+ message+", Flags: {"+
		((windowIn)?("WindowIn "):("")) + ((windowOut)?("WindowOut"):("")) + ((dontChangeBank)?("DontChangeBank"):("")) + "}}");
		return allValuesProperty;
	}
}
