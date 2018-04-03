package gbhelper.SkillTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class NormalDamageSkill extends SkillType {
	public NormalDamageSkill(String target, String name, String descrpition, int bank) {
		super(target, name, descrpition, bank, 1);
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
		return new NormalDamageSkill(values[0], values[1], values[2], Integer.parseInt(values[3]));
	}

}
