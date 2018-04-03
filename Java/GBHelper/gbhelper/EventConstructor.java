package gbhelper;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

import gbhelper.DatabaseManager.Data;
import gbhelper.DatabaseManager.DatabaseManager;
import gbhelper.EventConditionTypes.EventConditionFactory;
import gbhelper.EventConditionTypes.EventConditionItem;
import gbhelper.EventConditionTypes.EventConditionPosition;
import gbhelper.EventConditionTypes.EventConditionType;
import gbhelper.EventTypes.EventChangeMap;
import gbhelper.EventTypes.EventChangeTile;
import gbhelper.EventTypes.EventDelay;
import gbhelper.EventTypes.EventFunction;
import gbhelper.EventTypes.EventGetItem;
import gbhelper.EventTypes.EventLoseItem;
import gbhelper.EventTypes.EventMessage;
import gbhelper.EventTypes.EventTeleport;
import gbhelper.EventTypes.EventType;
import gbhelper.EventTypes.EventTypeFactory;
import gbhelper.GUI.CheckBoxField;
import gbhelper.GUI.ColumnDescription;
import gbhelper.GUI.DialogProvider;
import gbhelper.GUI.OnSector;
import gbhelper.ItemTypes.ItemType;
import javafx.scene.Scene;
import javafx.scene.control.TableView;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public class EventConstructor {
	DatabaseManager<EventConditionType> conditionManager;
	DatabaseManager<EventType> outcomeManager;
	TableView<ItemType> tableView;
	GridPane mainPane, eventPane, conditionPane;
	static String conditions[] = {"EVENT_CONDITION_POSITION", "EVENT_CONDITION_ITEM", "EVENT_CONDITION_FUNCTION", "EVENT_CONDITION_FLAG", "EVENT_CONDITION_BIT_FLAG"};
	static String events[] = {"EVENT_MESSAGE", "EVENT_GET_ITEM", "EVENT_LOSE_ITEM", "EVENT_CHANGE_TILE", "EVENT_CHANGE_MAP", "EVENT_ENCOUNTER", "EVENT_TELEPORT", "EVENT_DELAY", 
			"EVENT_MOVE_CAMERA", "", "", "", "", "", "", "",
			"", "", "", "", "", "", "", "",
			"", "", "", "", "", "", "", "EVENT_FUNCTION"};
	void loadTable() {
		String itemTableName[] = DialogProvider.askForData("ItemTable", "Name of itemtable", "Filename");
		if(itemTableName.length == 0)
			return;
		try {
			ObjectInputStream stream = new ObjectInputStream(Files.newInputStream(Paths.get(itemTableName[0] +".gbevent")));
			conditionManager.load((DatabaseManager<EventConditionType>)stream.readObject());
			outcomeManager.load((DatabaseManager<EventType>)stream.readObject());
			stream.close();
		} catch (Exception e) {
		} 
	}

	void saveTable() {
		String ret[] = DialogProvider.askForData("Save table", null, "Filename");
		if(ret.length == 0) return;
		try {
			ObjectOutputStream stream = new ObjectOutputStream(Files.newOutputStream(Paths.get(ret[0]+".gbevent")));
			stream.writeObject(conditionManager);
			stream.writeObject(outcomeManager);
			stream.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	void exportTable() {
		List<Data> conditionTypes = conditionManager.getList();
		List<Data> eventTypes = outcomeManager.getList();
		System.out.println("const char events[] = {" + conditionTypes.size() + ", ");
		for(int i = 0; i < conditionTypes.size(); i++) {
			System.out.print(conditions[((EventConditionType)conditionTypes.get(i)).getID()] + ", " + ((EventConditionType)conditionTypes.get(i)).getBytes());
			if(i != conditionTypes.size()-1)
				System.out.println(",");
			else
				System.out.println();
		}
		System.out.println(eventTypes.size() + ", ");
		for(int i = 0; i < eventTypes.size(); i++) {
			System.out.print(events[((EventType)eventTypes.get(i)).getID()] + ", " + ((EventType)eventTypes.get(i)).getBytes());
			if(i != eventTypes.size()-1)
				System.out.println(",");
			else
				System.out.println();
		}
		System.out.println("};");
		for(Data type : eventTypes) 
			if(((EventType)type).getAdditionalString() != null)
				System.out.println(((EventType)type).getAdditionalString());
		
	}
	
	
	public void makeButtons(GridPane pane) {
		OnSector.buildAddButton("Save table", pane).setOnMouseClicked((ev) -> {saveTable();});
		OnSector.buildAddButton("Load table", pane).setOnMouseClicked((ev) -> {loadTable();});
		OnSector.buildAddButton("Export table", pane).setOnMouseClicked((ev) -> {exportTable();});
		OnSector.centerEveryNode(pane);
	}
	
	void run(Stage primaryStage) {
		mainPane = new GridPane();
		eventPane = new GridPane();
		conditionPane = new GridPane();
		
		Scene scene = new Scene(mainPane, 800, 640);
		
		conditionManager = new DatabaseManager<EventConditionType>();
		conditionManager.init(conditionPane, 600, 240,
				new ColumnDescription("Index", new EventConditionFactory.IndexFactory(conditionManager.getList())),
				new ColumnDescription("Condition name", new EventConditionFactory.NameFactory()),
				new ColumnDescription("Condition values", new EventConditionFactory.AllValuesFactory()),
				new ColumnDescription("Type", new EventConditionFactory.TypeFactory()));
		conditionManager.addTypes(conditionManager.new TypeRepresentation("Position Condition", new EventConditionPosition(null, 0, 0)),
				conditionManager.new TypeRepresentation("Item Condition", new EventConditionItem(null, 0, 0)));
	
		conditionManager.run();
		
		outcomeManager = new DatabaseManager<EventType>();
		outcomeManager.init(eventPane, 600, 400,
				new ColumnDescription("Index", new EventTypeFactory.IndexFactory(conditionManager.getList())),
				new ColumnDescription("Event name", new EventTypeFactory.NameFactory()),
				new ColumnDescription("Event values", new EventTypeFactory.AllValuesFactory()),
				new ColumnDescription("Type", new EventTypeFactory.TypeFactory()));
		outcomeManager.addTypes(outcomeManager.new TypeRepresentation("Message", new EventMessage(null, null, 0, false, false, false)),
				outcomeManager.new TypeRepresentation("Get item", new EventGetItem(null, 0, 0)),
				outcomeManager.new TypeRepresentation("Lose item", new EventLoseItem(null, 0, 0)),
				outcomeManager.new TypeRepresentation("Change map", new EventChangeMap(null, "", 0, 0, 0)),
				outcomeManager.new TypeRepresentation("Change tile", new EventChangeTile(null, 0, 0, 0)),
				outcomeManager.new TypeRepresentation("Teleport", new EventTeleport(null, 0, 0)),
				outcomeManager.new TypeRepresentation("Delay", new EventDelay(null, 0)),
				outcomeManager.new TypeRepresentation("Function", new EventFunction(null, null)));
		outcomeManager.addPreferredFields(new CheckBoxField("Window in"),
				new CheckBoxField("Window out"), 
				new CheckBoxField("Don't change bank"));
		
		outcomeManager.run();
		
		makeButtons(outcomeManager.getButtonPane());
		
		mainPane.add(conditionPane, 0, 0);
		mainPane.add(eventPane, 0, 1);
		
		primaryStage.setTitle("GB Helper");
		primaryStage.setScene(scene);
	}
		
}
