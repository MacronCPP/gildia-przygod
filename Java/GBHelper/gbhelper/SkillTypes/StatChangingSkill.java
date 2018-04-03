package gbhelper.SkillTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.StringProperty;

public abstract class StatChangingSkill extends SkillType {

	public StatChangingSkill(String target, String name, String description, int bank, int ID) {
		super(target, name, description, bank, ID);
	}

	public static String statistics[] = {"Strength", "Dexterity", "Perception", "Charisma", "Vitality", "Damage melee", "Damage ranged", "Morale boost"};
	
	protected int combine(String statistic, int amount) {
		int ret = 0;
		for(int i = 0; i < statistics.length; i++) {
			if(statistics[i].equals(statistic)) {
				ret = i;
				break;
			}
		}
		ret <<= 5;
		ret += amount/5;
		return ret;
	}
	
	protected int combineReq(String statistic, int length, int amountRed) {
		int ret = 0;
		for(int i = 0; i < statistics.length; i++) {
			if(statistics[i].equals(statistic)) {
				ret = i;
				break;
			}
		}
		ret += (amountRed/5) << 5;
		ret += length << 3;
		return ret;
	}
	
	@Override
	public String[] getValues() {
		String ret[] =  {"Target", "Name", "Description", "Bank", "Check stat reduction", "Length", "Statistic to check", "Statistic #1", "Amount #1", "Statistic #2", "Amount #2"};
		return ret;
	}
	
}
