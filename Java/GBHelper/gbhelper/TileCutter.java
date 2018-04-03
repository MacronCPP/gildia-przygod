package gbhelper;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

import javafx.embed.swing.SwingFXUtils;
import javafx.scene.image.Image;

public class TileCutter {
	BufferedImage tileset;
	
	TileCutter(String filename) {
		try {
			tileset = ImageIO.read(new File(filename));
		} catch (IOException e) {
			System.exit(-1);
		}
	}
	
	Image getTile(int ID) {
		return SwingFXUtils.toFXImage(tileset.getSubimage((ID%16)*8, (ID/16)*8, 8, 8), null);
	}
}
