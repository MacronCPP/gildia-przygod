package gbhelper.SkillTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public abstract class SkillType implements Data {
	int ID;
	int bank;
	String name, description, target;
	SkillType(String target, String name, String description, int bank, int ID) {
		this.name = name;
		this.description = description;
		this.bank = bank;
		this.target = target;
		this.ID = ID;
	}
	
	public static String skillTargets[] = {"Enemy", "All enemies", "Ally", "All allies", "Self"};
	transient StringProperty IDProperty;
	public int getID() {
		return ID;
	}
	
	public int getCombinedID() {
		int ret = ID;
		for(int i = 0; i < skillTargets.length; i++) {
			if(skillTargets[i].equals(target)) {
				ret |= (i << 5);
				return ret;
			}
		}
		return ret;
	}
	
	public StringProperty getIDProperty() {
		if(IDProperty == null) 
			IDProperty = new SimpleStringProperty(Integer.toString(ID));
		return IDProperty;
	}
	
	abstract public String getByte();
	
	public String getBaseBytes() {
		return "0, 0/*pointer" + name + "NameDescription" + "*/, " + bank;
	}
	
	public String getNameAndDesriptionString() {
		return "const char " + name + "NameDescription[] = \"" + name.toUpperCase() + "|" + description.toUpperCase() + "|\";";
	}
	
	transient StringProperty nameProperty, descriptionProperty;
	transient StringProperty allValuesProperty, targetProperty;
	
	public StringProperty getTarget() {
		if(targetProperty == null) 
			targetProperty = new SimpleStringProperty(target);
		return targetProperty;
	}
	
	public StringProperty getName() {
		if(nameProperty == null) 
			nameProperty = new SimpleStringProperty(name);
		return nameProperty;
	}

	public StringProperty getDescription() {
		if(descriptionProperty == null) 
			descriptionProperty = new SimpleStringProperty(description);
		return descriptionProperty;
	}
	public abstract StringProperty getAllValues();
	
	public abstract String[] getValues(); 
	
	@Override
	public abstract Data construct(String[] values);

}
