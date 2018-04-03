package gbhelper.SkillTypes;

import java.util.List;

import gbhelper.DatabaseManager.Data;
import javafx.beans.value.ObservableValue;
import javafx.scene.control.TableColumn.CellDataFeatures;
import javafx.util.Callback;

public class SkillTypeFactory {
	public static class NameFactory implements Callback<CellDataFeatures<SkillType, String>, ObservableValue<String>> {
			@Override
			public ObservableValue<String> call(CellDataFeatures<SkillType, String> param) {
				return param.getValue().getName();
			}
	}
	
	public static class DescriptionFactory implements Callback<CellDataFeatures<SkillType, String>, ObservableValue<String>> {
		@Override
		public ObservableValue<String> call(CellDataFeatures<SkillType, String> param) {
			return param.getValue().getDescription();
		}
	}

	public static class TargetFactory implements Callback<CellDataFeatures<SkillType, String>, ObservableValue<String>> {
		@Override
		public ObservableValue<String> call(CellDataFeatures<SkillType, String> param) {
			return param.getValue().getTarget();
		}
	}
	
	public static class TypeFactory implements Callback<CellDataFeatures<SkillType, String>, ObservableValue<String>> {
		@Override
		public ObservableValue<String> call(CellDataFeatures<SkillType, String> param) {
			return param.getValue().getIDProperty();
		}
	}
	
	public static class AllValuesFactory implements Callback<CellDataFeatures<SkillType, String>, ObservableValue<String>> {
		@Override
		public ObservableValue<String> call(CellDataFeatures<SkillType, String> param) {
			return param.getValue().getAllValues();
		}
}
}