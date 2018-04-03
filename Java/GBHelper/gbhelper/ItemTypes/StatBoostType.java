package gbhelper.ItemTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class StatBoostType extends ItemType {
	Statistic stat;
	int amount;
	public StatBoostType(String name, int maxQuantity, Statistic stat, int amount) {
		super(name, 5, maxQuantity);
		this.amount = (amount/5)*5;
		this.stat = stat;
	}

	@Override
	public int getByte() {
		return ((stat.ordinal()) << 5) | amount;
	}
	
	@Override
	public String[] getValues() {
		String ret[] =  {"Name", "Max quantity", "Statistic", "Amount"};
		return ret;
	}
	
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{Quantity: "+maxQuantity+", Stat: " + stat + ", Boost: " + amount + "}");
		return allValuesProperty;
	}
	
	@Override
	public Data construct(String[] values) {
		return new StatBoostType(values[0], Integer.parseInt(values[1]), Statistic.values()[Integer.parseInt(values[2])], Integer.parseInt(values[3]));	
	}
}
