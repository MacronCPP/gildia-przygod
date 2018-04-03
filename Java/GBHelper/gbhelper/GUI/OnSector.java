package gbhelper.GUI;

import javafx.geometry.HPos;
import javafx.geometry.VPos;
import javafx.scene.canvas.Canvas;
import javafx.scene.control.Button;
import javafx.scene.effect.DropShadow;
import javafx.scene.image.Image;
import javafx.scene.image.PixelReader;
import javafx.scene.image.WritableImage;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;
import javafx.scene.text.Text;

public class OnSector {
	public static Button buildAddButton(String description, GridPane sector) {
		Button button = new Button(description);
		sector.addRow(sector.getChildren().size(), button);
		button.setMaxWidth(Double.MAX_VALUE);
		button.setMinWidth(180);
		DropShadow shadow = new DropShadow();
		
		button.addEventHandler(MouseEvent.MOUSE_ENTERED, (MouseEvent e) -> button.setEffect(shadow));
		button.addEventHandler(MouseEvent.MOUSE_EXITED, (MouseEvent e) -> button.setEffect(null));
		
		return button;
	}
	
	public static Button buildAddButton(Image image, GridPane sector) {
		Button button = new Button();
		sector.addRow(sector.getChildren().size(), button);
		button.setMaxSize(64, 64);
		button.setMinSize(64, 64);
		PixelReader reader = image.getPixelReader();
		WritableImage thumbnail = new WritableImage(64, 64);
		for(int i = 0; i < 64; i++) {
			for(int j = 0; j < 64; j++) {
				thumbnail.getPixelWriter().setPixels(i, j, 1, 1, reader, i/8, j/8);
			}
		}

		button.setBackground(new Background(new BackgroundImage(thumbnail, BackgroundRepeat.NO_REPEAT, BackgroundRepeat.NO_REPEAT, null, null)));
		DropShadow shadow = new DropShadow();
		
		button.addEventHandler(MouseEvent.MOUSE_ENTERED, (MouseEvent e) -> button.setEffect(shadow));
		button.addEventHandler(MouseEvent.MOUSE_EXITED, (MouseEvent e) -> button.setEffect(null));
		
		return button;
	}
	
	
	public static void addDummyText(GridPane sector) {
		Text dummyText = new Text();
		sector.addRow(sector.getChildren().size(), dummyText);
	}
	
	public static void centerEveryNode(Pane sector) {
		for(javafx.scene.Node n : sector.getChildren()) {
			GridPane.setHgrow(n, Priority.SOMETIMES);
			GridPane.setVgrow(n, Priority.SOMETIMES);
			GridPane.setHalignment(n, HPos.CENTER);
			GridPane.setValignment(n, VPos.CENTER);
		}
	}
	
}
