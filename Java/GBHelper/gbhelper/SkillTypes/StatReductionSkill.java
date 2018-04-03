package gbhelper.SkillTypes;

import gbhelper.DatabaseManager.Data;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class StatReductionSkill extends StatChangingSkill {
	String statisticFirst, statisticSecond;
	int amountFirst, amountSecond, length;
	String statisticToCheck;
	int checkStatReduction;
	public StatReductionSkill(String target, String name, String description, int bank, int checkStatReduction, int length, String statisticToCheck,
			String statisticFirst, int amountFirst, String statisticSecond, int amountSecond) {
		super(target, name, description, bank, 4);
		this.statisticFirst = statisticFirst;
		this.amountFirst = amountFirst/5*5;
		this.statisticSecond = statisticSecond;
		this.amountSecond = amountSecond/5*5;
		this.length = length;
		this.checkStatReduction = checkStatReduction;
		this.statisticToCheck = statisticToCheck;
	}
	
	@Override
	public String getByte() {
		return getCombinedID() + ", " + combineReq(statisticToCheck, length, checkStatReduction) + ", " + combine(statisticFirst, amountFirst) + ", " + combine(statisticSecond, amountSecond) + ", "
				+ super.getBaseBytes();
	}

	@Override
	public StringProperty getAllValues() {
		if(allValuesProperty == null) 
			allValuesProperty = new SimpleStringProperty("{CheckStatReduction: " + checkStatReduction + "Length: " + length + 
					", StatisticToCheck: " + statisticToCheck + 
					", Statistic #1: " + statisticFirst + "(" + amountFirst + "), " + 
					"Statistic #2: " + statisticSecond + "(" + amountSecond + "};");
		return allValuesProperty;
	}

	@Override
	public Data construct(String[] values) {
		return new StatReductionSkill(values[0], values[1], values[2], Integer.parseInt(values[3]),
				Integer.parseInt(values[4]), Integer.parseInt(values[5]), values[6],
				values[7], Integer.parseInt(values[8]),
				values[9], Integer.parseInt(values[10]));
	}

}
