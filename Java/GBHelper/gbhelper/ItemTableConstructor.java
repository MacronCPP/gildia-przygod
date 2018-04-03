package gbhelper;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;

import gbhelper.DatabaseManager.DatabaseManager;
import gbhelper.GUI.ChoiceBoxField;
import gbhelper.GUI.ColumnDescription;
import gbhelper.GUI.DialogProvider;
import gbhelper.GUI.OnSector;
import gbhelper.ItemTypes.Ammo;
import gbhelper.ItemTypes.Armor;
import gbhelper.ItemTypes.ItemType;
import gbhelper.ItemTypes.ItemTypeFactory;
import gbhelper.ItemTypes.Potion;
import gbhelper.ItemTypes.QuestItem;
import gbhelper.ItemTypes.StatBoostType;
import gbhelper.ItemTypes.Weapon;
import javafx.scene.Scene;
import javafx.scene.control.TableView;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public class ItemTableConstructor {
	DatabaseManager<ItemType> manager;
	TableView<ItemType> tableView;
	GridPane mainPane, buttonPane, tablePane;
	void loadTable() {
		String itemTableName[] = DialogProvider.askForData("ItemTable", "Name of itemtable", "Filename");
		if(itemTableName.length == 0)
			return;
		try {
			ObjectInputStream stream = new ObjectInputStream(Files.newInputStream(Paths.get(itemTableName[0] +".gbitem")));
			manager.load((DatabaseManager<ItemType>)stream.readObject());
			stream.close();
		} catch (Exception e) {
		} 
	}

	void saveTable() {
		String ret[] = DialogProvider.askForData("Save table", null, "Filename");
		if(ret.length == 0) return;
		try {
			ObjectOutputStream stream = new ObjectOutputStream(Files.newOutputStream(Paths.get(ret[0]+".gbitem")));
			stream.writeObject(manager);
			stream.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	void exportTable() {
		System.out.print("const char items[] = {");
		for(int j = 0; j < manager.getList().size(); j++) {
			ItemType type = (ItemType)manager.getList().get(j);
			System.out.println();
			System.out.print("\t");
			System.out.print(((type.getID() << 5) | (type.getMaxQuantity()))+ ", " + type.getByte() + ", ");
			for(int k = 0; k < 14; k++)  {
				if(k < type.getName().getValue().length())
					System.out.print("'" + Character.toUpperCase(type.getName().getValue().charAt(k)) + "'");
				else
					System.out.print("0");
				
				if(k != 13)
					System.out.print(", ");
			}
			if(j != manager.getList().size()-1)
				System.out.print(",");
		}
		System.out.print("};");
	}
	
	
	public void makeButtons(GridPane pane) {
		OnSector.buildAddButton("Save table", pane).setOnMouseClicked((ev) -> {saveTable();});
		OnSector.buildAddButton("Load table", pane).setOnMouseClicked((ev) -> {loadTable();});
		OnSector.buildAddButton("Export table", pane).setOnMouseClicked((ev) -> {exportTable();});
		OnSector.centerEveryNode(pane);
	}
	
	void run(Stage primaryStage) {
		mainPane = new GridPane();
		buttonPane = new GridPane();
		
		Scene scene = new Scene(mainPane, 800, 640);
		
		manager = new DatabaseManager<ItemType>();
		manager.init(mainPane, 600, 600,
				new ColumnDescription("Index", new ItemTypeFactory.IndexFactory(manager.getList())),
				new ColumnDescription("Item name", new ItemTypeFactory.NameFactory()),
				new ColumnDescription("Item values", new ItemTypeFactory.AllValuesFactory()),
				new ColumnDescription("Type", new ItemTypeFactory.TypeFactory()));
		manager.addTypes(manager.new TypeRepresentation("Ammo", new Ammo(null, 0, 0)),
				manager.new TypeRepresentation("Armor", new Armor(null, 0, 0)),
				manager.new TypeRepresentation("Potion", new Potion(null, 0, 0)),
				manager.new TypeRepresentation("Quest Item", new QuestItem(null, 0)),
				manager.new TypeRepresentation("StatBoost", new StatBoostType(null, 0, null, 0)),
				manager.new TypeRepresentation("Weapon", new Weapon(null, 0, "", 0, 0, 0))
				);
	
		manager.addPreferredField(new ChoiceBoxField("Type", "Melee", "Ranged", "Melee with heal"));
		
		manager.run();
		makeButtons(manager.getButtonPane());
		
		primaryStage.setTitle("GB Helper");
		primaryStage.setScene(scene);
		
	}
}
