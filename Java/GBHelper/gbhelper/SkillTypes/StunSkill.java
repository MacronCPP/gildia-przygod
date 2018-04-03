package gbhelper.SkillTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class StunSkill extends SkillType {
	int length, checkStatReduction;
	String statisticToCheck;
	public StunSkill(String target, String name, String description, int checkStatReduction, int length, String statisticToCheck) {
		super(target, name, description, 0, 0);
		this.length = length;
		this.checkStatReduction = checkStatReduction;
		this.statisticToCheck = statisticToCheck;
	}

	@Override
	public String getByte() {
		return getCombinedID() + ", " + length + ", 0, 0, " + super.getBaseBytes();
	}

	@Override
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{Stun length: "+ length + "}");
		return allValuesProperty;
	}

	@Override
	public String[] getValues() {
		String ret[] =  {"Target", "Name", "Description", "Check stat reduction", "Stun length", "Statistic to check"};
		return ret;
	}

	@Override
	public Data construct(String[] values) {
		return new StunSkill(values[0], values[1], values[2], Integer.parseInt(values[3]), Integer.parseInt(values[4]), values[5]);
	}

}
