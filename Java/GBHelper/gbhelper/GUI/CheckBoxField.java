package gbhelper.GUI;

import javafx.scene.Node;
import javafx.scene.control.CheckBox;

public class CheckBoxField extends DataField {
	CheckBox box;
	public CheckBoxField(String name) {
		super(name);
		box = new CheckBox();
	}

	@Override
	String getValue() {
		return Boolean.toString(box.isSelected());
	}

	@Override
	Node getNode() {
		return box;
	}

}
