package com.example.cv04;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;


public class Game extends Application {

    final int PLAYER_HEIGHT = 50;
    final int PLAYER_WIDTH = 50;
    final int BASE_HP = 50;
    final int X_WALK_SPEED = 2;
    private final Pane root = new Pane();

    private final Player player = new Player("Fanda", PLAYER_HEIGHT, PLAYER_WIDTH, BASE_HP, Color.GREENYELLOW);

    private Pane createContent() {

        root.setPrefSize(800, 600);

        root.getChildren().add(player);

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

    private class Player extends Rectangle {
        int hp;
        final int maxHp = 400;
        final String name;
        boolean jump;
        int yVelocity;
        boolean lMove = false;
        boolean rMove = false;

        Player(String name, int height, int width, int hp, Color color) {
            super(width, height, color);
            this.name = name;
            this.hp = hp;
            this.jump = false;
            this.setTranslateX(200);
            this.setTranslateY(200);
        }

        void moveLeft() {
            this.rMove = false;
            this.lMove = true;
            Thread l;
            l = new Thread(new Runnable() {
                @Override
                public void run() {
                    while (lMove) {
                        setTranslateX(getTranslateX() - X_WALK_SPEED);
                        try {
                            Thread.sleep(10);
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }
                }
            });
            l.start();
        }

        void moveRight() {
            this.lMove = false;
            this.rMove = true;
            Thread r;
            r = new Thread(new Runnable() {
                @Override
                public void run() {
                    while (rMove) {
                        setTranslateX(getTranslateX() + X_WALK_SPEED);
                        try {
                            Thread.sleep(10);
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }
                }
            });
            r.start();
        }

        void stopRMove() {
            this.rMove = false;
        }

        void stopLMove() {
            this.lMove = false;
        }

        void jump() {
            if (!jump) {
                Thread j;
                j = new Thread(new Runnable() {
                    @Override
                    public void run() {
                        jump = true;
                        yVelocity = 18;
                        for (int i = 1; i <= 37; i++) {
                            setTranslateY(getTranslateY() - yVelocity);
                            yVelocity -= 1;
                            try {
                                Thread.sleep(13);
                            } catch (InterruptedException e) {
                                throw new RuntimeException(e);
                            }
                        }
                        yVelocity = 0;
                        jump = false;
                    }
                });
                j.start();
            }
        }

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