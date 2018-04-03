package gbhelper.GUI;

import javafx.collections.FXCollections;
import javafx.scene.Node;
import javafx.scene.control.ChoiceBox;

public class ChoiceBoxField extends DataField {
	public ChoiceBoxField(String name, String... options) {
		super(name);
		field = new ChoiceBox<String>(FXCollections.observableArrayList(options));
	}

	ChoiceBox<String> field;

	@Override
	String getValue() {
		return field.getSelectionModel().getSelectedItem();
	}

	@Override
	Node getNode() {
		return field;
	}
}
