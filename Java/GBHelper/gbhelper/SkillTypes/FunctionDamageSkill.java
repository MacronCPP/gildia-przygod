package gbhelper.SkillTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class FunctionDamageSkill extends SkillType {
	String function;
	int bank, functionBank;
	public FunctionDamageSkill(String target, String name, String descrpition, int bank, String function, int functionBank) {
		super(target, name, descrpition, bank, 2);
		this.function = function;
		this.bank = bank;
		this.functionBank = functionBank;
	}

	@Override
	public String getByte() {
		return getCombinedID() + ", 0, 0/*pointer" + function + "*/" + ", 0," + super.getBaseBytes();
	}

	@Override
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{Function: " + function + ", Bank: " + functionBank + "}");
		return allValuesProperty;
	}

	@Override
	public String[] getValues() {
		String ret[] =  {"Target", "Name", "Descrpition", "Bank", "Function", "Function bank"};
		return ret;
	}

	@Override
	public Data construct(String[] values) {
		return new FunctionDamageSkill(values[0], values[1], values[2], Integer.parseInt(values[3]), values[4], Integer.parseInt(values[5]));
	}

}
