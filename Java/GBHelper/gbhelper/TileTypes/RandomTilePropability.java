package gbhelper.TileTypes;

import java.io.Serializable;
import java.util.Random;

import javafx.scene.image.Image;

public class RandomTilePropability implements Serializable  {
	public double wage;
	public Image image;
	public int ID;
	public RandomTilePropability(int ID, double wage, Image image) {
		this.wage = wage;
		this.image = image;
		this.ID = ID;
	}
	
	static double sum(RandomTilePropability tiles[]) {
		double ret = 0;
		for(int i = 0; i < tiles.length; i++)
			ret += tiles[i].wage;
		return ret;
	}
	
	static RandomTilePropability getRandom(Random generator, RandomTilePropability... tiles) {
		double rand = generator.nextDouble()*sum(tiles);
		double sumT = 0;
		for(int i = 0; i < tiles.length; i++) {
			if(rand < sumT + tiles[i].wage) return tiles[i];
			sumT += tiles[i].wage;
		}
		return tiles[tiles.length-1];
	}
}
