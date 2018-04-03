package gbhelper.TileTypes;

import java.util.ArrayList;
import java.util.List;

import gbhelper.Map;
import gbhelper.Tile;
import javafx.scene.image.Image;

public class MatchingTile extends TileType {
	List<MatchingTilePosition> maps;
	boolean collidable;
	public MatchingTile(String name, boolean collidable, MatchingTilePosition... tiles) {
		super(name);
		maps = new ArrayList<>();
		this.collidable = collidable;
		for(int i = 0; i < tiles.length; i++) {
			maps.add(tiles[i]);
		}
	}
	
	/*
	 * 0 - left
	 * 1 - right
	 * 2 - up
	 * 3 - down
	 */
	
	static public String NONE = "0000", TOP = "0010", LEFT = "1000", 
	RIGHT = "0100", BOTTOM = "0001", TOPLEFT = "1010",
	TOPRIGHT = "0110", BOTTOMLEFT = "1001", BOTTOMRIGHT = "0101",
	TOPBOTTOM = "0011", RIGHTLEFT="1100", ALL="1111";
	
	int getDiffrence(String pos, String secPos) {
		int diff = 0;
		for(int i = 0; i < pos.length(); i++) {
			if(pos.charAt(i) != secPos.charAt(i)) {
				if(pos.charAt(i) == '0') 
					diff += 1;
				else 
					diff += 5;
			}
		}
		return diff;
	}
	
	int getDiffrence(boolean[] table, String secPos) {
		int diff = 0;
		for(int i = 0; i < table.length; i++) {
			if(table[i] != (secPos.charAt(i) == '1')) {
				if(!table[i]) 
					diff += 1;
				else 
					diff += 5;
			}
		}
		return diff;
	}
	
	public MatchingTilePosition getProp(Map map, Tile tile) {
		boolean table[] = new boolean[4];
		table[0] = map.get(tile.x-1, tile.y).type == this;
		table[1] = map.get(tile.x+1, tile.y).type == this;
		table[2] = map.get(tile.x, tile.y-1).type == this;
		table[3] = map.get(tile.x, tile.y+1).type == this;
		
		int minDiff = getDiffrence(table, maps.get(0).pos);
		MatchingTilePosition lowest = maps.get(0);
		for(MatchingTilePosition pos : maps) {
			if(minDiff > getDiffrence(table, pos.pos)) {
				minDiff = getDiffrence(table, pos.pos);
				lowest = pos;
			}
		}
		return lowest;
	}
	
	@Override
	public int getID(Map map, Tile tile) {
		return getProp(map, tile).ID;
	}

	@Override
	public boolean isCollidable() {
		return collidable;
	}

	@Override
	public Image getImage(Map map, Tile on) {
		if(map == null)
			return maps.get(0).image;
		return getProp(map, on).image;
	}

	
}
