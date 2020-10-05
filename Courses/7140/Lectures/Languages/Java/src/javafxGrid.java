
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Line;

class DotGrid extends Pane {
    private Canvas canvas = new Canvas();
 
    public DotGrid() {
        //        getChildren().add(canvas);
        canvas.setWidth(300);
        canvas.setHeight(200);
    }

    void drawRectangles(GraphicsContext gc, int w, int h) {
        for (int x = 0; x < w;  x += 25) {
            for (int y = 0; y < h; y += 25) {
                gc.fillRect(x, y, 10, 15);
            }
        }
    }

    void drawGrid(int w, int h) {
        for (int x = 0; x < w;  x += 25) {
            Line line = new Line(x, 0, x, h);
            line.setStroke(Color.RED);
            getChildren().add(line);
        }
        for (int y = 0; y < h; y += 25) {
            Line line = new Line(0, y, w, y);
            line.setStroke(Color.GREEN);
            getChildren().add(line);
        }
    }
    
    @Override
    protected void layoutChildren() {
        GraphicsContext gc = canvas.getGraphicsContext2D();
        int w = (int) canvas.getWidth(), h = (int) canvas.getHeight();
        gc.clearRect(0, 0, w, h);
        gc.setFill(Color.BLUE);
        drawRectangles(gc, w, h);
        drawGrid(w, h);
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
