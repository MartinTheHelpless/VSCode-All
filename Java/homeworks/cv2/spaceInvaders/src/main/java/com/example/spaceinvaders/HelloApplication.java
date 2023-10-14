package com.example.spaceinvaders;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;


public class HelloApplication extends Application {

    int tileMatrix[][];

    final int PLAYER_HEIGHT = 50;
    final int PLAYER_WIDTH = 50;
    final int BASE_HP = 50;
    final int X_WALK_SPEED = 2;
    private final Pane root = new Pane();
    private Pane createContent() {

        root.setPrefSize(800, 600);

        // root.getChildren().add(player);

        AnimationTimer timer = new AnimationTimer() {
            @Override
            public void handle(long now) {
                update();
            }
        };


        timer.start();

        return root;
    }

    private void update() {

    }

    @Override
    public void start(Stage stage) throws Exception {

        Scene scene = new Scene(createContent());

        scene.setOnKeyPressed(e -> {

            Thread t1;
            t1 = new Thread(new Runnable() {
                @Override
                public void run() {
                    switch (e.getCode()) {
                        case A:
                            player.moveLeft();
                            break;
                        case D:
                            player.moveRight();
                            break;
                        case SPACE:
                            player.jump();

                    }
                }
            });
            t1.start();
        });

        scene.setOnKeyReleased(e -> {

            Thread t2;
            t2 = new Thread(new Runnable() {
                @Override
                public void run() {
                    switch (e.getCode()) {
                        case A:
                            player.stopLMove();
                            break;
                        case D:
                            player.stopRMove();
                            break;
                    }
                }
            });
            t2.start();
        });


        stage.setScene(scene);
        stage.show();

    }

    private static class testEnemy extends Rectangle {
        int hp;
        final int maxHp = 75;
        final String type;

        testEnemy(String type, int w, int h, int hp, Color color) {
            super(w, h, color);
            this.type = type;
            this.hp = hp;
        }
    }

    public static void main(String[] args) {
        launch();
    }


}