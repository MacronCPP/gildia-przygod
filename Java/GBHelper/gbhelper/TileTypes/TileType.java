package gbhelper.TileTypes;

import java.io.Serializable;

import gbhelper.Map;
import gbhelper.Tile;
import javafx.scene.image.Image;

public abstract class TileType implements Serializable  {
	String name;
	TileType(String name) {
		this.name = name;
	}
	public String getName() {
		return name;
	}
	public abstract int getID(Map map, Tile on);
	public abstract boolean isCollidable();
	public abstract Image getImage(Map map, Tile on);
}
