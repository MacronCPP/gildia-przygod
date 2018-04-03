package gbhelper.ItemTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Weapon extends ItemType {
	int dices;
	int sides;
	int add;
	String type;
	public Weapon(String name, int maxQuantity, String type, int dices, int sides, int add) {
		super(name, 3, maxQuantity);
		this.dices = dices;
		this.sides = sides;
		this.add = add;
		this.type = type;
	}

	@Override
	public int getID() {
		if(type.equals("Melee"))
			return super.getID();
		if(type.equals("Ranged"))
			return super.getID()+1;
		if(type.equals("Melee with heal"))
			return super.getID()+2;
		
		return super.getID();
	}
	
	@Override
	public int getByte() {
		return (dices << 6) | (sides << 2) | add;
	}
	
	@Override
	public String[] getValues() {
		String ret[] =  {"Name", "Max quantity", "Type", "Dices", "Sides", "Additional damage"};
		return ret;
	}
	
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{Quantity: "+maxQuantity+", Type: " + type + ", Dices: " + dices + "d" + sides + "+" + add + "}");
		return allValuesProperty;
	}
	
	@Override
	public Data construct(String[] values) {
		return new Weapon(values[0], Integer.parseInt(values[1]), values[2], Integer.parseInt(values[3]), Integer.parseInt(values[4]), Integer.parseInt(values[5]));
	}
}
