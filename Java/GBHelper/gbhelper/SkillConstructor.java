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
import gbhelper.ItemTypes.ItemType;
import gbhelper.SkillTypes.FunctionDamageSkill;
import gbhelper.SkillTypes.MoraleBoostSkill;
import gbhelper.SkillTypes.NormalDamageSkill;
import gbhelper.SkillTypes.SkillType;
import gbhelper.SkillTypes.SkillTypeFactory;
import gbhelper.SkillTypes.StatBoostSkill;
import gbhelper.SkillTypes.StatChangingSkill;
import gbhelper.SkillTypes.StatReductionSkill;
import gbhelper.SkillTypes.StunSkill;
import javafx.scene.Scene;
import javafx.scene.control.TableView;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public class SkillConstructor {
	DatabaseManager<SkillType> manager;
	TableView<SkillType> tableView;
	GridPane mainPane, buttonPane, tablePane;
	void loadTable() {
		String itemTableName[] = DialogProvider.askForData("Skill set", "Name of skill set", "Filename");
		if(itemTableName.length == 0)
			return;
		try {
			ObjectInputStream stream = new ObjectInputStream(Files.newInputStream(Paths.get(itemTableName[0] +".gbitem")));
			manager.load((DatabaseManager<SkillType>)stream.readObject());
			stream.close();
		} catch (Exception e) {
		} 
	}

	void saveTable() {
		String ret[] = DialogProvider.askForData("Save skills", null, "Filename");
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
		System.out.print("const char skills[] = {");
		for(int j = 0; j < manager.getList().size(); j++) {
			SkillType type = (SkillType)manager.getList().get(j);
			System.out.println();
			System.out.print("\t");
			System.out.print(type.getByte());
			if(j != manager.getList().size() - 1)
				System.out.print(",");
		}
		System.out.print("};");
		for(int j = 0; j < manager.getList().size(); j++) {
			SkillType type = (SkillType)manager.getList().get(j);
			System.out.println();
			System.out.print(type.getNameAndDesriptionString());
		}
		
	}
	
	
	public void makeButtons(GridPane pane) {
		OnSector.buildAddButton("Save skills", pane).setOnMouseClicked((ev) -> {saveTable();});
		OnSector.buildAddButton("Load skills", pane).setOnMouseClicked((ev) -> {loadTable();});
		OnSector.buildAddButton("Export skills", pane).setOnMouseClicked((ev) -> {exportTable();});
		OnSector.centerEveryNode(pane);
	}
	
	void run(Stage primaryStage) {
		mainPane = new GridPane();
		buttonPane = new GridPane();
		
		Scene scene = new Scene(mainPane, 800, 640);
		
		manager = new DatabaseManager<SkillType>();
		manager.init(mainPane, 600, 600,
				new ColumnDescription("Skill name", new SkillTypeFactory.NameFactory()),
				new ColumnDescription("Skill description", new SkillTypeFactory.NameFactory()),
				new ColumnDescription("Skill values", new SkillTypeFactory.AllValuesFactory()),
				new ColumnDescription("Target", new SkillTypeFactory.TargetFactory()),
				new ColumnDescription("Type", new SkillTypeFactory.TypeFactory()));
		manager.addTypes(manager.new TypeRepresentation("Stun skill", new StunSkill(null, null, null, 0, 0, null)),
				manager.new TypeRepresentation("Normal attack", new NormalDamageSkill(null, null, null, 0)),
				manager.new TypeRepresentation("Function skill", new FunctionDamageSkill(null, null, null, 0, null, 0)),
				manager.new TypeRepresentation("Morale boost", new MoraleBoostSkill(null, null, null, 0)),
				manager.new TypeRepresentation("Stat boost", new StatBoostSkill(null, null, null, 0, 0, 0, null, null, 0, null, 0)),
				manager.new TypeRepresentation("Stat reduce", new StatReductionSkill(null, null, null, 0, 0, 0, null, null, 0, null, 0))
				);
	
		manager.addPreferredFields(
				new ChoiceBoxField("Target", SkillType.skillTargets),
				new ChoiceBoxField("Statistic #1", StatChangingSkill.statistics),
				new ChoiceBoxField("Statistic #2", StatChangingSkill.statistics),
				new ChoiceBoxField("Statistic #3", StatChangingSkill.statistics),
				new ChoiceBoxField("Statistic to check", StatChangingSkill.statistics));
		manager.run();
		makeButtons(manager.getButtonPane());
		
		primaryStage.setTitle("GB Helper");
		primaryStage.setScene(scene);
		
	}
}
