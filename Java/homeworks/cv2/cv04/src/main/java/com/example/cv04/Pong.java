package com.example.cv04;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class Pong extends Application {

    final double WINDOW_WIDTH = 900;
    final double WINDOW_HEIGHT = 500;
    final double PADDLE_HEIGHT = 100;
    final int PADDLE_WIDTH = 15;
    final int SCORE_FONT = 45;
    final double BALL_SIZE = 15;
    int ball_speed = 0;
    int gameMode = 0;
    boolean play = false;

    private final Pane root = new Pane();

    Player p1;

    Player p2;

    Text startText = new Text(WINDOW_WIDTH / 2 - 219, WINDOW_HEIGHT / 2 - 50, "Press ENTER to play");
    Text colorHint = new Text(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 2 + 70, "Tab and Backspace to change paddle colors");

    private final Ball ball = new Ball((int) BALL_SIZE, Color.WHITE);

    private Pane createGame() {


        root.setPrefSize(WINDOW_WIDTH, WINDOW_HEIGHT);

        Player p1 = new Player(root, "Player One", PADDLE_HEIGHT, PADDLE_WIDTH, PADDLE_WIDTH, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2, Color.WHITE, SCORE_FONT, 1);

        Player p2 = new Player(root, "Player Two", PADDLE_HEIGHT, PADDLE_WIDTH, WINDOW_WIDTH - 2 * PADDLE_WIDTH, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2, Color.WHITE, SCORE_FONT, 2);


        root.getChildren().add(p1);

        root.getChildren().add(p2);

        startText.setFill(Color.WHITE);
        colorHint.setFill(Color.WHITE);

        startText.setFont(new Font("Roboto Mono", 50));
        colorHint.setFont(new Font("Roboto Mono", 30));

        root.getChildren().add(startText);
        root.getChildren().add(colorHint);

        root.getChildren().add(ball);

        if (gameMode == 1 ){
            AnimationTimer timer = new AnimationTimer() {
                @Override
                public void handle(long now) {
                    try {
                        Thread.sleep(10);
                        update();
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
            };
            timer.start();
        }



        return root;
    }

    private Pane createMenu() {

        root.setPrefSize(WINDOW_WIDTH, WINDOW_HEIGHT);

        Player p1 = new Player(root, "Player One", PADDLE_HEIGHT, PADDLE_WIDTH, PADDLE_WIDTH, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2, Color.WHITE, SCORE_FONT, 1);

        Player p2 = new Player(root, "Player Two", PADDLE_HEIGHT, PADDLE_WIDTH, WINDOW_WIDTH - 2 * PADDLE_WIDTH, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2, Color.WHITE, SCORE_FONT, 2);


        root.getChildren().add(new Text(WINDOW_WIDTH / 4 * 1, WINDOW_HEIGHT / 4, "Play Game"));

        AnimationTimer timer = new AnimationTimer() {
            @Override
            public void handle(long now) {
                try {
                    Thread.sleep(10);
                    update();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        };

        timer.start();

        return root;
    }

    private void update() throws InterruptedException {

        ball.setTranslateX(ball.getTranslateX() + (ball.hMove ? ball_speed : -ball_speed));
        ball.setTranslateY(ball.getTranslateY() + (ball.vMove ? ball_speed : -ball_speed));

        if (ball.getTranslateX() <= 0) {
            ball.switchXdir();
            p1.drawscorePlusOne();
            ball.setTranslateX(WINDOW_WIDTH / 2 - BALL_SIZE / 2);
            ball.setTranslateY(WINDOW_HEIGHT / 2 - BALL_SIZE / 2);
            ball_speed = 0;
            startText.setFill(Color.WHITE);
            colorHint.setFill(Color.WHITE);
            p1.scoreTab.setFill(Color.WHITE);
            p2.scoreTab.setFill(Color.WHITE);
        } else if (ball.getTranslateX() + BALL_SIZE >= WINDOW_WIDTH) {
            ball.switchXdir();
            p2.drawscorePlusOne();
            ball.setTranslateX(WINDOW_WIDTH / 2 - BALL_SIZE / 2);
            ball.setTranslateY(WINDOW_HEIGHT / 2 - BALL_SIZE / 2);
            ball_speed = 0;
            startText.setFill(Color.WHITE);
            colorHint.setFill(Color.WHITE);
            p1.scoreTab.setFill(Color.WHITE);
            p2.scoreTab.setFill(Color.WHITE);
        }

        if (ball.getTranslateY() <= 0)
            ball.switchYdir();
        else if (ball.getTranslateY() + BALL_SIZE >= WINDOW_HEIGHT)
            ball.switchYdir();

        if (p1.getBoundsInParent().intersects(ball.getBoundsInParent()) && ball.getTranslateX() >= p1.getTranslateX() + PADDLE_WIDTH - 2 * ball_speed)
            ball.switchXdir();
        else if (p2.getBoundsInParent().intersects(ball.getBoundsInParent()) && ball.getTranslateX() + BALL_SIZE <= p2.getTranslateX() + PADDLE_WIDTH - 2 * ball_speed)
            ball.switchXdir();

    }

    private void changePaddleColor(Player player) {

        player.setColorIndex((player.getColorIndex() + 1) > 8 ? 0 : (int) (player.getColorIndex() + 1));

        switch ((int) player.colorIndex) {
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
            case 6:
                player.setColor(Color.BURLYWOOD);
                break;
            case 7:
                player.setColor(Color.CORNSILK);
                break;
            case 8:
                player.setColor(Color.DARKRED);
                break;
        }
    }

    @Override
    public void start(Stage stage) {

        stage.setResizable(false);

        stage.setTitle("Pong!");

        Scene scene = new Scene(createMenu());

        switch (gameMode) {

            case 0:
                break;

            case 1:
                scene.setFill(Color.BLACK);

                scene.setOnKeyPressed(e -> {

                    Thread keys2;
                    keys2 = new Thread(() -> {
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
                            case ENTER:
                                ball_speed = 5;
                                play = true;
                                startText.setFill(Color.BLACK);
                                colorHint.setFill(Color.BLACK);
                                p1.scoreTab.setFill(Color.BLACK);
                                p2.scoreTab.setFill(Color.BLACK);
                                break;
                        }
                    });
                    keys2.start();
                });

                scene.setOnKeyReleased(e -> {

                    Thread keys1;
                    keys1 = new Thread(() -> {
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
                    });
                    keys1.start();
                });
                break;
        }

        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}