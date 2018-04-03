package gbhelper.GUI;

import javafx.scene.Node;

public abstract class DataField {
	String name;
	public DataField(String name) {
		this.name = name;
	}
	public String getName() {
		return name;
	}
	
	abstract String getValue();
	abstract Node getNode();
}
