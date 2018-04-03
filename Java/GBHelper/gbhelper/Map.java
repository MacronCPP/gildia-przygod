package gbhelper;

import java.io.Serializable;

import gbhelper.TileTypes.TileType;

public class Map implements Serializable {
	public int sizeX, sizeY;
	Tile tiles[][];
	public static TileType selectedTile;
	Map(int sizeX, int sizeY, TileType tileType) {
		this.sizeX = sizeX;
		this.sizeY = sizeY;
		tiles = new Tile[sizeX][sizeY];
		for(int i = 0; i < sizeX; i++) {
			for(int j = 0; j < sizeY; j++) {
				tiles[i][j] = new Tile(i, j, tileType);
			}
		}
	}
	
	void set(int x, int y) {
		if(x < 0 || y < 0 || x >= sizeX || y >= sizeY)
			return;
		
		tiles[x][y] = new Tile(x, y, selectedTile);
	}
	
	public Tile get(int x, int y) {
		if(x < 0 || y < 0 || x >= sizeX || y >= sizeY)
			return new Tile(0, 0, null);
		
		return tiles[x][y];
	}
}

