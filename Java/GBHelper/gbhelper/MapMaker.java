package gbhelper;

import java.io.IOException;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

import gbhelper.GUI.DialogProvider;
import gbhelper.GUI.OnSector;
import gbhelper.TileTypes.BlandTileType;
import gbhelper.TileTypes.MatchingTile;
import gbhelper.TileTypes.MatchingTilePosition;
import gbhelper.TileTypes.RandomTilePropability;
import gbhelper.TileTypes.RandomizedTile;
import gbhelper.TileTypes.TileType;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public class MapMaker extends Application {
	GridPane mainPane, buttonPane, canvasPane;
	Map map;
	MapCanvas canvas;
	TileCutter cutter;
	int selectedSizeX;
	int selectedSizeY;
	public static List<TileType> types;
	
	public void makeButtons(GridPane pane) {
		for(TileType type : types) {
			OnSector.buildAddButton(type.getImage(null, null), pane).setOnMouseClicked((ev) -> {Map.selectedTile = type;});
		}
		OnSector.buildAddButton("Save map", pane).setOnMouseClicked((ev) -> {saveMap();});
		OnSector.buildAddButton("Load map", pane).setOnMouseClicked((ev) -> {loadMap();});
		OnSector.buildAddButton("Export map", pane).setOnMouseClicked((ev) -> {exportMap();});
		OnSector.centerEveryNode(pane);
	}
	
	int[] combine(Tile tiles[][], int x, int y) {
		int ret[] = new int[3];
		for(int i = 1; i < 4; i++) {
			ret[i-1] = tiles[x+i][y].getID(map) - 112;
		}
		ret[0] += ((tiles[x][y].getID(map) - 112) & 0b110000) << 2;
		ret[1] += ((tiles[x][y].getID(map) - 112) & 0b001100) << 4;
		ret[2] += ((tiles[x][y].getID(map) - 112) & 0b000011) << 6;
		
		assert ret[0] < 256;
		assert ret[1] < 256;
		assert ret[2] < 256;
		
		assert (ret[0] & 63) + 112 == tiles[x+1][y].getID(map);
		assert (ret[1] & 63) + 112 == tiles[x+2][y].getID(map);
		assert (ret[2] & 63) + 112 == tiles[x+3][y].getID(map);
		assert (((ret[0] & 192) >> 2) | ((ret[1] & 192) >> 4) | ((ret[2] & 192) >> 6)) + 112 == tiles[x][y].getID(map);
		return ret;
	}
	void exportMap() {
		System.out.print("const char map[] = {");
		for(int j = 0; j < map.sizeY; j++) {
			for(int i = 0; i < map.sizeX/4; i++) {
				int combined[] = combine(map.tiles, i*4, j);
				for(int k = 0; k < 3; k++) {
					System.out.print(combined[k]);
					if(j != map.sizeY - 1 || i != map.sizeX/4 - 1 || k != 2)
						System.out.print(", ");
					else System.out.print("};");
				}
			}
			System.out.println();
			if(j != map.sizeY-1)
				System.out.print("\t");
		}
	}
	
	void saveMap() {
		String ret[] = DialogProvider.askForData("Save map", null, "Filename");
		if(ret.length == 0) return;
		try {
			ObjectOutputStream stream = new ObjectOutputStream(Files.newOutputStream(Paths.get(ret[0]+".gbmap")));
			stream.writeObject(map);
			stream.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	void loadMap() {
		String ret[] = DialogProvider.askForData("Load map", null, "Filename");
		if(ret.length == 0) return;
		try {
			ObjectInputStream stream = new ObjectInputStream(Files.newInputStream(Paths.get(ret[0] +".gbmap")));
			Map map = ((Map)stream.readObject());
			stream.close();
			this.map = map;
		} catch (Exception e) {
			this.map = new Map(selectedSizeX, selectedSizeY, types.get(0));
			
		} 
		if(canvas != null)
			canvasPane.getChildren().remove(canvas.canvas);
		canvas = new MapCanvas(map, 640, 640);
		canvasPane.add(canvas.canvas, 0, 0);
		Map.selectedTile = types.get(0);
	}
	
	public void initOverworldMap() {
		cutter = new TileCutter("tileset/tileset_overworld.png");
		types = new ArrayList<>();
		types.add(new RandomizedTile("Grass", 
				new RandomTilePropability(7*16, 1, cutter.getTile(7*16)),
				new RandomTilePropability(7*16+1, 0.10, cutter.getTile(7*16+1)),
				new RandomTilePropability(7*16+2, 0.05, cutter.getTile(7*16+2)),
				new RandomTilePropability(7*16+3, 0.02, cutter.getTile(7*16+3))));
		
		types.add(new BlandTileType("Something", cutter.getTile(7*16+4), 7*16+4, false));
		types.add(new BlandTileType("Stone", cutter.getTile(8*16), 8*16, true));
		
		types.add(new MatchingTile("Wall", true,
				new MatchingTilePosition(8*16+2, cutter.getTile(8*16+2), MatchingTile.TOP),
				new MatchingTilePosition(8*16+2, cutter.getTile(8*16+2), MatchingTile.BOTTOM),
				new MatchingTilePosition(8*16+2, cutter.getTile(8*16+2), MatchingTile.TOPBOTTOM),
				new MatchingTilePosition(8*16+1, cutter.getTile(8*16+1), MatchingTile.NONE),
				new MatchingTilePosition(8*16+6, cutter.getTile(8*16+6), MatchingTile.LEFT),
				new MatchingTilePosition(8*16+5, cutter.getTile(8*16+5), MatchingTile.RIGHT),
				new MatchingTilePosition(8*16+1, cutter.getTile(8*16+1), MatchingTile.RIGHTLEFT),
				new MatchingTilePosition(8*16+4, cutter.getTile(8*16+4), MatchingTile.TOPLEFT),
				new MatchingTilePosition(8*16+3, cutter.getTile(8*16+3), MatchingTile.TOPRIGHT),
				new MatchingTilePosition(8*16+5, cutter.getTile(8*16+5), MatchingTile.BOTTOMRIGHT),
				new MatchingTilePosition(8*16+6, cutter.getTile(8*16+6), MatchingTile.BOTTOMLEFT)));
		selectedSizeX = selectedSizeY = 32;
	}
	
	public void initArenaMap() {
		cutter = new TileCutter("tileset/tileset_arena.png");
		types = new ArrayList<>();
		types.add(new RandomizedTile("Grass", 
				new RandomTilePropability(7*16, 1, cutter.getTile(7*16)),
				new RandomTilePropability(8*16, 0.10, cutter.getTile(8*16)),
				new RandomTilePropability(9*16, 0.05, cutter.getTile(9*16)),
				new RandomTilePropability(10*16, 0.05, cutter.getTile(10*16)),
				new RandomTilePropability(10*16+1, 0.05, cutter.getTile(10*16+1)),
				new RandomTilePropability(10*16+2, 0.05, cutter.getTile(10*16+2))));
		
		types.add(new MatchingTile("Track", false,
				new MatchingTilePosition(7*16+1, cutter.getTile(7*16+1), MatchingTile.BOTTOMRIGHT),
				new MatchingTilePosition(7*16+2, cutter.getTile(7*16+2), MatchingTile.BOTTOMLEFT),
				new MatchingTilePosition(8*16+1, cutter.getTile(8*16+1), MatchingTile.TOPRIGHT),
				new MatchingTilePosition(8*16+2, cutter.getTile(8*16+2), MatchingTile.TOPLEFT),
				new MatchingTilePosition(7*16+3, cutter.getTile(7*16+3), MatchingTile.BOTTOM),
				new MatchingTilePosition(8*16+3, cutter.getTile(8*16+3), MatchingTile.TOPBOTTOM),
				new MatchingTilePosition(9*16+3, cutter.getTile(9*16+3), MatchingTile.ALL),
				new MatchingTilePosition(10*16+3, cutter.getTile(10*16+3), MatchingTile.TOP),
				new MatchingTilePosition(9*16+4, cutter.getTile(9*16+4), MatchingTile.LEFT),
				new MatchingTilePosition(9*16+2, cutter.getTile(9*16+2), MatchingTile.RIGHTLEFT),
				new MatchingTilePosition(9*16+1, cutter.getTile(9*16+1), MatchingTile.RIGHT)));
		
		types.add(new RandomizedTile("AudienceTop",
				new RandomTilePropability(7*16+12, 1, cutter.getTile(7*16+12)),
			    new RandomTilePropability(7*16+13, 1, cutter.getTile(7*16+13)),
			    new RandomTilePropability(7*16+14, 1, cutter.getTile(7*16+14))));
		
		types.add(new RandomizedTile("AudienceMid", 
				new RandomTilePropability(8*16+12, 1, cutter.getTile(8*16+12)),
				new RandomTilePropability(8*16+13, 1, cutter.getTile(8*16+13)),
				new RandomTilePropability(8*16+14, 1, cutter.getTile(8*16+14)),
				new RandomTilePropability(9*16+12, 1, cutter.getTile(9*16+12)),
				new RandomTilePropability(9*16+13, 1, cutter.getTile(9*16+13)),
				new RandomTilePropability(9*16+14, 1, cutter.getTile(9*16+14)),
				new RandomTilePropability(10*16+12, 1, cutter.getTile(10*16+12)),
				new RandomTilePropability(10*16+13, 1, cutter.getTile(10*16+13)),
				new RandomTilePropability(10*16+14, 1, cutter.getTile(10*16+14))));
			
		types.add(new MatchingTile("GateClosed", true, 
				new MatchingTilePosition(7*16+6, cutter.getTile(7*16+6), MatchingTile.BOTTOMRIGHT),
				new MatchingTilePosition(7*16+7, cutter.getTile(7*16+7), MatchingTile.BOTTOMLEFT),
				new MatchingTilePosition(8*16+6, cutter.getTile(8*16+6), MatchingTile.TOPRIGHT),
				new MatchingTilePosition(8*16+7, cutter.getTile(8*16+7), MatchingTile.TOPLEFT)));
			
		types.add(new MatchingTile("GateOpened", true, 
				new MatchingTilePosition(9*16+9, cutter.getTile(9*16+9), MatchingTile.BOTTOMRIGHT),
				new MatchingTilePosition(9*16+10, cutter.getTile(9*16+10), MatchingTile.BOTTOMLEFT),
				new MatchingTilePosition(10*16+9, cutter.getTile(10*16+9), MatchingTile.TOPRIGHT),
				new MatchingTilePosition(10*16+10, cutter.getTile(10*16+10), MatchingTile.TOPLEFT)));
		
		types.add(new MatchingTile("Wall", true,
				new MatchingTilePosition(9*16+11, cutter.getTile(9*16+11), MatchingTile.BOTTOM),
				new MatchingTilePosition(10*16+11, cutter.getTile(10*16+11), MatchingTile.TOP)));
		
		types.add(new MatchingTile("FlagWall", true,
				new MatchingTilePosition(9*16+15, cutter.getTile(9*16+15), MatchingTile.BOTTOM),
				new MatchingTilePosition(10*16+15, cutter.getTile(10*16+15), MatchingTile.TOP)));
		
		types.add(new MatchingTile("WallLeftSide", true,
				new MatchingTilePosition(7*16+5, cutter.getTile(7*16+5), MatchingTile.BOTTOM),
				new MatchingTilePosition(8*16+5, cutter.getTile(8*16+5), MatchingTile.TOP)));
		
		types.add(new MatchingTile("WallLeftSideL", true,				
				new MatchingTilePosition(9*16+5, cutter.getTile(9*16+5), MatchingTile.ALL)));
		
		types.add(new MatchingTile("WallRightSide", true,
				new MatchingTilePosition(7*16+8, cutter.getTile(7*16+8), MatchingTile.BOTTOM),
				new MatchingTilePosition(8*16+8, cutter.getTile(8*16+8), MatchingTile.TOP)));
		
		types.add(new MatchingTile("WallRightSideL", true,				
				new MatchingTilePosition(9*16+8, cutter.getTile(9*16+8), MatchingTile.ALL)));
			
		selectedSizeX = selectedSizeY = 32;
	}
	
	
	public void initFightWoodenMap() {
		
		cutter = new TileCutter("tileset/tileset_fight_wooden.png");
		types = new ArrayList<>();
		types.add(new BlandTileType("Floor", cutter.getTile(7*16), 7*16, false));
		types.add(new BlandTileType("Wall", cutter.getTile(7*16+1), 7*16+1, false));
		types.add(new BlandTileType("Torch", cutter.getTile(7*16+6), 7*16+6, false));
		types.add(new MatchingTile("Window", true,
				new MatchingTilePosition(7*16+2, cutter.getTile(7*16+2), MatchingTile.BOTTOMRIGHT),
				new MatchingTilePosition(7*16+3, cutter.getTile(7*16+3), MatchingTile.BOTTOMLEFT),
				new MatchingTilePosition(7*16+4, cutter.getTile(7*16+4), MatchingTile.TOPRIGHT),
				new MatchingTilePosition(7*16+5, cutter.getTile(7*16+5), MatchingTile.TOPLEFT),
				new MatchingTilePosition(7*16+2, cutter.getTile(7*16+2), MatchingTile.NONE)));
		
		selectedSizeX = 20;
		System.out.println("lel?");
		selectedSizeY = 18;
	}
	
	public void initFightArenaMap() {
		cutter = new TileCutter("tileset/tileset_fight_arena.png");
		types = new ArrayList<>();
		types.add(new RandomizedTile("Grass", 
				new RandomTilePropability(7*16, 1, cutter.getTile(7*16)),
				new RandomTilePropability(8*16, 0.10, cutter.getTile(8*16)),
				new RandomTilePropability(7*16+1, 0.05, cutter.getTile(7*16+1)),
				new RandomTilePropability(8*16+1, 0.05, cutter.getTile(8*16+1)),
				new RandomTilePropability(7*16+2, 0.05, cutter.getTile(7*16+2)),
				new RandomTilePropability(8*16+2, 0.05, cutter.getTile(8*16+2)),
				new RandomTilePropability(7*16+3, 0.05, cutter.getTile(7*16+3)),
				new RandomTilePropability(8*16+3, 0.05, cutter.getTile(8*16+3))));
				
		types.add(new RandomizedTile("AudienceTop",
				new RandomTilePropability(7*16+13, 1, cutter.getTile(7*16+13)),
			    new RandomTilePropability(7*16+14, 1, cutter.getTile(7*16+14)),
			    new RandomTilePropability(7*16+15, 1, cutter.getTile(7*16+15))));
		
		types.add(new RandomizedTile("AudienceMid", 
				new RandomTilePropability(8*16+13, 1, cutter.getTile(8*16+13)),
				new RandomTilePropability(8*16+14, 1, cutter.getTile(8*16+14)),
				new RandomTilePropability(8*16+15, 1, cutter.getTile(8*16+15)),
				new RandomTilePropability(7*16+5, 1, cutter.getTile(7*16+5)),
				new RandomTilePropability(7*16+6, 1, cutter.getTile(7*16+6)),
				new RandomTilePropability(7*16+7, 1, cutter.getTile(7*16+7)),
				new RandomTilePropability(8*16+5, 1, cutter.getTile(8*16+5)),
				new RandomTilePropability(8*16+6, 1, cutter.getTile(8*16+6)),
				new RandomTilePropability(8*16+7, 1, cutter.getTile(8*16+7))));
			
		types.add(new MatchingTile("GateClosed", true, 
				new MatchingTilePosition(7*16+9, cutter.getTile(7*16+9), MatchingTile.BOTTOMRIGHT),
				new MatchingTilePosition(7*16+10, cutter.getTile(7*16+10), MatchingTile.BOTTOMLEFT),
				new MatchingTilePosition(8*16+9, cutter.getTile(8*16+9), MatchingTile.TOPRIGHT),
				new MatchingTilePosition(8*16+10, cutter.getTile(8*16+10), MatchingTile.TOPLEFT)));
			
		types.add(new MatchingTile("GateOpened", true, 
				new MatchingTilePosition(7*16+11, cutter.getTile(7*16+11), MatchingTile.BOTTOMRIGHT),
				new MatchingTilePosition(7*16+12, cutter.getTile(7*16+12), MatchingTile.BOTTOMLEFT),
				new MatchingTilePosition(8*16+11, cutter.getTile(8*16+11), MatchingTile.TOPRIGHT),
				new MatchingTilePosition(8*16+12, cutter.getTile(8*16+12), MatchingTile.TOPLEFT)));
			
		types.add(new MatchingTile("Wall", true,
				new MatchingTilePosition(7*16+4, cutter.getTile(7*16+4), MatchingTile.BOTTOM),
				new MatchingTilePosition(8*16+4, cutter.getTile(8*16+4), MatchingTile.TOP)));
		
		types.add(new MatchingTile("FlagWall", true,
				new MatchingTilePosition(7*16+8, cutter.getTile(7*16+8), MatchingTile.BOTTOM),
				new MatchingTilePosition(8*16+8, cutter.getTile(8*16+8), MatchingTile.TOP)));
		selectedSizeX = 20;
		selectedSizeY = 18;
	}
	
	@Override
	public void start(Stage primaryStage) throws Exception {
		String option = DialogProvider.showOptions("Helper app", "Select application", "MapMaker", "ItemTableConstructor", "EventConstructor", "SkillConstructor");
		if(option == null)
			System.exit(10);
		if(option.equals("ItemTableConstructor")) {
			new ItemTableConstructor().run(primaryStage);
		} else if(option.equals("EventConstructor")) {
			new EventConstructor().run(primaryStage);
		} else if(option.equals("SkillConstructor")) {
			new SkillConstructor().run(primaryStage);
		} else{
		mainPane = new GridPane();
		buttonPane = new GridPane();
		canvasPane = new GridPane();
		
		Scene scene = new Scene(mainPane, 800, 640);
		
		option = DialogProvider.showOptions("Map package", "Select map package", "Arena", "Wooden - Fight", "Arena - Fight");
		if(option == null)
			System.exit(10);
		if(option.equals("Arena"))
			initArenaMap();
		if(option.equals("Wooden - Fight"))
			initFightWoodenMap();
		if(option.equals("Arena - Fight"))
			initFightArenaMap();
		
		makeButtons(buttonPane);
		mainPane.add(canvasPane, 0, 0);
		loadMap();
		if(map == null) System.exit(-1);
		mainPane.add(buttonPane, 1, 0);
		primaryStage.setTitle("GB Helper");
		primaryStage.setScene(scene);
		
		}
		primaryStage.show();
		primaryStage.setOnHiding(event -> {System.exit(0);});
	}

}
