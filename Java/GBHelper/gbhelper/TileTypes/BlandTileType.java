package gbhelper.TileTypes;

import gbhelper.Map;
import gbhelper.Tile;
import javafx.scene.image.Image;

public class BlandTileType  extends TileType {
	Image image;
	int ID;
	boolean collidable; 
	public BlandTileType(String name, Image image, int ID, boolean collidable) {
		super(name);
		this.image = image;
		this.ID = ID;
		this.collidable = collidable;
	}
	@Override
	public int getID(Map map, Tile on) {
		return ID;
	}
	@Override
	public boolean isCollidable() {
		return collidable;
	}
	@Override
	public Image getImage(Map map, Tile on) {
		return image;
	}
}
