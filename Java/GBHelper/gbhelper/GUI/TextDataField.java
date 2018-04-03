package gbhelper.GUI;

import javafx.scene.Node;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;

public class TextDataField extends DataField {
	public TextDataField(String name) {
		super(name);
		field = new TextField();
	}

	TextField field;

	@Override
	String getValue() {
		return field.getText();
	}

	@Override
	Node getNode() {
		return field;
	}
}
