
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.layout.Pane;
 
class DotGrid extends Pane {
    private Canvas canvas = new Canvas();
 
    public DotGrid() {
        getChildren().add(canvas);
        canvas.setWidth(300);
        canvas.setHeight(200);
    }

    @Override
    protected void layoutChildren() {
        GraphicsContext gc = canvas.getGraphicsContext2D();

        int w = (int) canvas.getWidth(), h = (int) canvas.getHeight();
        gc.clearRect(0, 0, w, h);
        gc.setFill(Color.BLUE);

        for (int x = 0; x < w;  x += 25) {
            for (int y = 0; y < h; y += 25) {
                gc.fillRect(x, y, 10, 15);
            }
        }
    }
}

public class javafxGrid extends Application {
    @Override
    public void start(Stage stage) throws Exception {
        stage.setScene(new Scene(new DotGrid(), Color.WHITE));
        stage.show();
    }
 
    public static void main(String[] args) {
        launch(args);
    }
}
