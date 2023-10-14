package com.example.cv04;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

import java.io.IOException;

public class Pong extends Application {

    public final int WINDOW_WIDTH = 900;
    public final int WINDOW_HEIGHT = 500;
    final int PADDLE_HEIGHT = 100;
    final int PADDLE_WIDTH = 15;
    final int SCORE_HEIGHT = 60;
    final int SCORE_WIDTH = 45;
    final int BALL_SIZE = 15;
    int paddleColor = 0;

    private final Pane root = new Pane();

    private final Player p1 = new Player(root, "Player One", PADDLE_HEIGHT, PADDLE_WIDTH, PADDLE_WIDTH, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2, Color.WHITE, SCORE_WIDTH, SCORE_HEIGHT, 1);

    private final Player p2 = new Player(root, "Player Two", PADDLE_HEIGHT, PADDLE_WIDTH, WINDOW_WIDTH - 2 * PADDLE_WIDTH, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2, Color.WHITE, SCORE_WIDTH, SCORE_HEIGHT, 2);

    private final Ball ball = new Ball(BALL_SIZE, Color.WHITE);

    private Pane createContent() {

        root.setPrefSize(WINDOW_WIDTH, WINDOW_HEIGHT);

        root.getChildren().add(p1);

        root.getChildren().add(p2);

        root.getChildren().add(ball);

        return root;
    }



    private void changePaddleColor(Player player) {

        player.setColorIndex(((player.getColorIndex() + 1) > 5 ? 0 : player.getColorIndex() + 1));

        switch (player.colorIndex) {
            case 0:
                player.setColor(Color.WHITE);
                break;
            case 1:
                player.setColor(Color.MEDIUMPURPLE);
                break;
            case 2:
                player.setColor(Color.INDIGO);
                break;
            case 3:
                player.setColor(Color.GREENYELLOW);
                break;
            case 4:
                player.setColor(Color.STEELBLUE);
                break;
            case 5:
                player.setColor(Color.ORANGE);
                break;
        }
    }

    @Override
    public void start(Stage stage) throws IOException {

        Scene scene = new Scene(createContent());

        scene.setFill(Color.BLACK);

        Thread main = Thread.currentThread();

        scene.setOnKeyPressed(e -> {

            Thread keys2;
            keys2 = new Thread(new Runnable() {
                @Override
                public void run() {
                    switch (e.getCode()) {
                        case W:
                            p1.moveUp();
                            break;
                        case S:
                            p1.moveDown();
                            break;
                        case UP:
                            p2.moveUp();
                            break;
                        case DOWN:
                            p2.moveDown();
                            break;
                        case TAB:
                            changePaddleColor(p1);
                            break;
                        case BACK_SPACE:
                            changePaddleColor(p2);
                            break;
                    }
                }
            });
            keys2.start();
        });

        scene.setOnKeyReleased(e -> {

            Thread keys1;
            keys1 = new Thread(new Runnable() {
                @Override
                public void run() {
                    switch (e.getCode()) {
                        case W:
                            p1.moveU = false;
                            break;
                        case S:
                            p1.moveDwn = false;
                            break;
                        case UP:
                            p2.moveU = false;
                            break;
                        case DOWN:
                            p2.moveDwn = false;
                            break;
                    }
                }
            });
            keys1.start();
        });

        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}