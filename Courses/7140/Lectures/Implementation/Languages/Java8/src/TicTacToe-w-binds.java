// TicTacToe.java, user-against-user, JavaFX GUI
// from http://www.cs.armstrong.edu/liang/intro10e/html/TicTacToe.html
// mods by pmateti@wright.edu

import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;
import javafx.scene.shape.Ellipse;

public class TicTacToe extends Application {

    private char whoseTurn = 'X'; // one of X or O
    private Cell[][] cell =  new Cell[3][3];
    private Label statusLabel = new Label("X's turn to play");
    private int nFullCells = 0;
    private boolean gameOver = false;

    @Override
    public void start(Stage primaryStage) {
        GridPane pane = new GridPane(); 
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                pane.add(cell[i][j] = new Cell(), j, i);

        BorderPane borderPane = new BorderPane();
        borderPane.setCenter(pane);
        borderPane.setBottom(statusLabel);
    
        Scene scene = new Scene(borderPane, 300, 300);
        primaryStage.setTitle("TicTacToe");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public boolean isFull() {
        return nFullCells >= 9; // > should never happen
    }
    
    public boolean hasWon(char token) {
        for (int i = 0; i < 3; i++)
            if (cell[i][0].getToken() == token &&
                cell[i][1].getToken() == token &&
                cell[i][2].getToken() == token)
                return true;
        for (int j = 0; j < 3; j++)
            if (cell[0][j].getToken() == token &&
                cell[1][j].getToken() == token &&
                cell[2][j].getToken() == token)
                return true;
        if (cell[0][0].getToken() == token &&
            cell[1][1].getToken() == token &&
            cell[2][2].getToken() == token)
            return true;
        if (cell[0][2].getToken() == token &&
            cell[1][1].getToken() == token &&
            cell[2][0].getToken() == token)
            return true;
        return false;
    }

    public class Cell extends Pane {

        private char token = ' ';   // one of blank, X, or O

        public Cell() {
            setStyle("-fx-border-color: black"); 
            setPrefSize(100, 100);
            setOnMouseClicked(e -> handleMouseClick());
        }

        public char getToken() {
            return token;
        }

        public void drawX() {
            double w = getWidth(), h = getHeight();
            Line line1 = new Line(10.0f, 10.0f, w - 10.0f, h - 10.0f);
            // line1.endXProperty(). bind(widthProperty(). subtract(10));
            // line1.endYProperty(). bind(heightProperty(). subtract(10));
            Line line2 = new Line(10.0f, h - 10.0f, w - 10.0f, 10.0f);
            // line2.startYProperty(). bind(heightProperty(). subtract(10));
            // line2.endXProperty(). bind(widthProperty(). subtract(10));
            getChildren().addAll(line1, line2); 
        }

        public void drawO() {
            double w = getWidth(), h = getHeight();
            Ellipse ellipse = new Ellipse(w/2, h/2, w/2 - 10.0f, h/2 - 10.0f);
            // ellipse. centerXProperty().bind(widthProperty().divide(2));
            // ellipse. centerYProperty(). bind(heightProperty(). divide(2));
            // ellipse. radiusXProperty(). bind(widthProperty(). divide(2). subtract(10));        
            // ellipse.radiusYProperty(). bind(heightProperty(). divide(2). subtract(10));   
            ellipse.setStroke(Color.BLACK);
            ellipse.setFill(Color.WHITE);
            getChildren().add(ellipse);
        }

        public void setToken(char c) {
            if (c == 'X')
                drawX();
            else 
                drawO();
            token = c;
            nFullCells ++;
        }

        private void handleMouseClick() {
            String s = "";
            if (token == ' ' && !gameOver) {
                setToken(whoseTurn);
                if (hasWon(whoseTurn)) {
                    gameOver = true;
                    s = whoseTurn + " won! The game is over";
                }
                else if (isFull()) {
                    gameOver = true;
                    s = "Draw! The game is over";
                }
                else {
                    whoseTurn = (whoseTurn == 'X') ? 'O' : 'X';
                    s = whoseTurn + "'s turn";
                }
                statusLabel.setText(s);
            }
        }
    }
  
    public static void main(String[] args) {
        launch(args);
    }
}
