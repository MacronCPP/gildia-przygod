package gbhelper.SkillTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class MoraleBoostSkill extends SkillType {
	public MoraleBoostSkill(String target, String name, String descrpition, int bank) {
		super(target, name, descrpition, bank, 3);
	}

	@Override
	public String getByte() {
		return getCombinedID() + ", 0, 0, 0, " + super.getBaseBytes();
	}

	@Override
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{}");
		return allValuesProperty;
	}

	@Override
	public String[] getValues() {
		String ret[] =  {"Target", "Name", "Description", "Bank"};
		return ret;
	}

	@Override
	public Data construct(String[] values) {
		return new MoraleBoostSkill(values[0], values[1], values[2], Integer.parseInt(values[3]));
	}

}
