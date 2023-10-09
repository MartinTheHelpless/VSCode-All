package com.example.demo;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

public class HelloApplication extends Application {
    private static final int WIDTH = 874;
    private static final int HEIGHT = 512;
    private static final int PADDLE_WIDTH = 10;
    private static final int PADDLE_HEIGHT = 120;
    private static final int BALL_SIZE = 20;
    private static final int BALL_SPEED = 2;

    private double paddle1Y = HEIGHT / 2 - PADDLE_HEIGHT / 2;
    private double paddle2Y = HEIGHT / 2 - PADDLE_HEIGHT / 2;

    private boolean upPressed = false;
    private boolean downPressed = false;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Pong");
        Pane root = new Pane();
        Scene scene = new Scene(root, WIDTH, HEIGHT);

        Ball ball = new Ball(scene.getWidth() / 2, scene.getHeight() / 2, BALL_SIZE);

        Player players[] = {new Player(PADDLE_WIDTH, PADDLE_HEIGHT, .scene.getWidth()/2, scene.getHeight()/2), new Player(PADDLE_WIDTH, PADDLE_HEIGHT, scene.getWidth()/2, scene.getHeight()/2)};

        ball.dirX = BALL_SPEED;

        ball.dirY = BALL_SPEED;

        Canvas canvas = new Canvas(WIDTH, HEIGHT);
        root.getChildren().add(canvas);

        GraphicsContext gc = canvas.getGraphicsContext2D();

        scene.setOnKeyPressed(e -> {
            if (e.getCode() == KeyCode.W) upPressed = true;
            if (e.getCode() == KeyCode.S) downPressed = true;
        });

        scene.setOnKeyReleased(e -> {
            if (e.getCode() == KeyCode.W) upPressed = false;
            if (e.getCode() == KeyCode.S) downPressed = false;
        });

        new AnimationTimer() {
            @Override
            public void handle(long currentNanoTime) {
                gc.clearRect(0, 0, WIDTH, HEIGHT);

                if (upPressed && paddle1Y > 0) {
                    paddle1Y -= 5;
                }
                if (downPressed && paddle1Y < HEIGHT - players[0].height) {
                    paddle1Y += 5;
                }

                // Update ball position
                ball.posX += ball.dirX;
                ball.posY += ball.dirY;

                if (ball.posY <= 0 || ball.posY >= HEIGHT - ball.size) {
                    ball.dirY = -ball.dirY;
                }

                if (ball.posX <= players[0].width && ball.posY >= paddle1Y && ball.posY <= paddle1Y + players[0].height
                        || ball.posX >= WIDTH - players[0].width - ball.size && ball.posY >= paddle2Y && ball.posY <= paddle2Y + players[0].height) {
                    ball.dirX = -ball.dirX;
                }

                if (ball.posX < 0 || ball.posX > WIDTH) {
                    ball.posX = WIDTH / 2 - ball.size/ 2;
                    ball.posY = HEIGHT / 2 - ball.size / 2;
                    ball.dirX *= -1;
                    ball.dirY *= -1;
                }

                // Draw paddles
                gc.fillRect(0, paddle1Y, players[0].width, players[0].height);
                gc.fillRect(WIDTH - players[0].width, paddle2Y, players[0].width, players[0].height);

                // Draw ball
                gc.fillOval(ball.posX, ball.posY, ball.size, ball.size);
            }
        }.start();

        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
