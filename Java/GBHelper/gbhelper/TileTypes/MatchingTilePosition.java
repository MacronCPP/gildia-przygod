package gbhelper.TileTypes;

import javafx.scene.image.Image;

public class MatchingTilePosition {
	Image image;
	int ID;
	String pos;
	
	public MatchingTilePosition(int ID, Image image, String pos) {
		this.ID = ID;
		this.image = image;
		this.pos = pos;
	}
}
