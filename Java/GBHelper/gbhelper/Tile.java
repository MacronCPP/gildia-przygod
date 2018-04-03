package gbhelper;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

import gbhelper.TileTypes.TileType;
import javafx.scene.image.Image;

public class Tile implements Serializable {
	public int x, y;
	transient public TileType type;
	public Tile(int x, int y, TileType type) {
		this.x = x;
		this.y = y;
		this.type = type;
	}
	
	private void writeObject(ObjectOutputStream strumien) throws IOException { 
		strumien.defaultWriteObject();
		strumien.writeObject(type.getName());
	}

	private void readObject(ObjectInputStream strumien) throws ClassNotFoundException, IOException {
		strumien.defaultReadObject();
		String type = (String)strumien.readObject();
		for(TileType found : MapMaker.types) {
			if(found.getName().equals(type)) {
				this.type = found;
				return;
			}
		}
		this.type = null;
    }
	public int getID(Map map) {
		return type.getID(map, this);
	}
	
	public Image getImage(Map map) {
		return type.getImage(map, this);
	}
}
