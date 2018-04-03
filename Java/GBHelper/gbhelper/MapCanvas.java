package gbhelper;

import javafx.scene.canvas.Canvas;
import javafx.scene.input.MouseEvent;

public class MapCanvas {
	Map map;
	Canvas canvas;
	boolean clicked;
	MapCanvas(Map map, int sizeX, int sizeY) {
		this.map = map;
		canvas = new Canvas(sizeX, sizeY);
		canvas.addEventHandler(MouseEvent.ANY, (MouseEvent ev) -> {
			if(ev.isPrimaryButtonDown()) {
				map.set((int)(ev.getX()/sizeX*map.sizeX), (int)(ev.getY()/sizeY*map.sizeY)); 
				draw();
				}});
	}
	
	Canvas getCanvas() {
		return canvas;
	}
	
	void draw() {
		for(int i = 0; i < map.sizeX; i++) {
			for(int j = 0; j < map.sizeY; j++) {
				canvas.getGraphicsContext2D().drawImage(map.tiles[i][j].getImage(map), i*canvas.getWidth()/map.sizeX,
						j*canvas.getHeight()/map.sizeY, 
						(i+1)*canvas.getWidth()/map.sizeX-i*canvas.getWidth()/map.sizeX, 
						(i+1)*canvas.getHeight()/map.sizeY-i*canvas.getHeight()/map.sizeY);
			}
		}
	}
}
