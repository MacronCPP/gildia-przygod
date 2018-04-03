package gbhelper.TileTypes;

import java.util.Random;

import gbhelper.Map;
import gbhelper.Tile;
import javafx.scene.image.Image;

public class RandomizedTile extends TileType {
	RandomTilePropability tiles[];
	public RandomizedTile(String name, RandomTilePropability... prop) {
		super(name);
		tiles = prop;
	}
	
	public RandomTilePropability getProp(Tile tile) {
		return RandomTilePropability.getRandom(new Random(tile.hashCode()), tiles);
	}
	
	@Override
	public int getID(Map map, Tile tile) {
		return getProp(tile).ID;
	}

	@Override
	public boolean isCollidable() {
		return false;
	}

	@Override
	public Image getImage(Map map, Tile on) {
		if(map == null)
			return tiles[0].image;
		return getProp(on).image;
	}

}
