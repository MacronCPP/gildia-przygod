package gbhelper.EventTypes;

import java.util.List;

import gbhelper.DatabaseManager.Data;
import javafx.beans.value.ObservableValue;
import javafx.scene.control.TableColumn.CellDataFeatures;
import javafx.util.Callback;

public class EventTypeFactory {
	public static class NameFactory implements Callback<CellDataFeatures<EventType, String>, ObservableValue<String>> {
			@Override
			public ObservableValue<String> call(CellDataFeatures<EventType, String> param) {
				return param.getValue().getName();
			}
	}
	
	public static class TypeFactory implements Callback<CellDataFeatures<EventType, String>, ObservableValue<String>> {
		@Override
		public ObservableValue<String> call(CellDataFeatures<EventType, String> param) {
			return param.getValue().getIDProperty();
		}
	}
	
	public static class IndexFactory implements Callback<CellDataFeatures<EventType, String>, ObservableValue<String>> {
		List<Data> list;
		public IndexFactory(List<Data> list2) {
			this.list = list2;
		}
		@Override
		public ObservableValue<String> call(CellDataFeatures<EventType, String> param) {
			return param.getValue().getIndexProperty(list.indexOf(param.getValue()));
		}
	}
	
	public static class AllValuesFactory implements Callback<CellDataFeatures<EventType, String>, ObservableValue<String>> {
		@Override
		public ObservableValue<String> call(CellDataFeatures<EventType, String> param) {
			return param.getValue().getAllValues();
		}
}
}