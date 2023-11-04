package com.example.spaceinvaders;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.paint.ImagePattern;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

import java.util.Random;


public class HelloApplication extends Application {

    Random rand = new Random();
    final int GRASS = 0;
    final ImagePattern GRASS_IMAGE = new ImagePattern(new Image("grass.jpg"));
    final int DIRT = 1;
    final ImagePattern DIRT_IMAGE = new ImagePattern(new Image("dirt.jpg"));
    final int STONE = 2;
    final ImagePattern STONE_IMAGE = new ImagePattern(new Image("stone.jpg"));
    final int BLUE_ORE = 3;
    final ImagePattern BLUE_ORE_IMAGE = new ImagePattern(new Image("blueOre.jpg"));
    final int DARK_ORE = 4;
    final ImagePattern DARK_ORE_IMAGE = new ImagePattern(new Image("darkOre.jpg"));
    static final int TILE_SIZE = 40;
    final int X_WALK_SPEED = 5;
    final int WINDOW_WIDTH = 800;
    final int WINDOW_HEIGHT = 600;
    final int MATRIX_WIDTH = 21;
    final int MATRIX_HEIGHT = 7;

    Tile[][] tileMatrix = new Tile[MATRIX_WIDTH][MATRIX_HEIGHT];

    private final Pane root = new Pane();

    private Pane createContent() {

        root.setPrefSize(WINDOW_WIDTH, WINDOW_HEIGHT);

        Player p1 = new Player("Fanda", WINDOW_WIDTH/2-TILE_SIZE/2, WINDOW_HEIGHT / 2 + (WINDOW_HEIGHT / 2) % 40 - 80, Color.MEDIUMPURPLE);

        root.getChildren().add(p1);

        for (int i = 0; i < MATRIX_WIDTH; i++) {
            for (int j = 0; j < MATRIX_HEIGHT; j++) {
                int xTilePos = TILE_SIZE * i;
                int yTilePos = WINDOW_HEIGHT / 2 + (WINDOW_HEIGHT / 2) % 40 + 40 * j;
                if (j == 0) {
                    tileMatrix[i][j] = new Tile(GRASS, xTilePos, yTilePos);
                    root.getChildren().add(tileMatrix[i][j]);
                } else if (j == 2 && rand.nextInt(2) == 0) {
                    tileMatrix[i][j] = new Tile(STONE, xTilePos, yTilePos);
                    root.getChildren().add(tileMatrix[i][j]);
                } else if (j < 3) {
                    tileMatrix[i][j] = new Tile(DIRT, xTilePos, yTilePos);
                    root.getChildren().add(tileMatrix[i][j]);
                } else if (rand.nextInt(50) > 45) {
                    tileMatrix[i][j] = new Tile(BLUE_ORE, xTilePos, yTilePos);
                    root.getChildren().add(tileMatrix[i][j]);
                } else if (rand.nextInt(50) > 45) {
                    tileMatrix[i][j] = new Tile(DARK_ORE, xTilePos, yTilePos);
                    root.getChildren().add(tileMatrix[i][j]);
                } else {
                    tileMatrix[i][j] = new Tile(STONE, xTilePos, yTilePos);
                    root.getChildren().add(tileMatrix[i][j]);
                }
            }
        }

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
    public void start(Stage stage) {

        Scene scene = new Scene(createContent());

        stage.setResizable(false);

        scene.addEventFilter(MouseEvent.MOUSE_PRESSED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                double mX = mouseEvent.getX();
                double mY = mouseEvent.getY();
                double tmp = WINDOW_HEIGHT / 2;
                double tmp2 = WINDOW_WIDTH / 2;
                if (tmp2 + TILE_SIZE / 2 - TILE_SIZE * 3 < mX && tmp2 + TILE_SIZE / 2 + TILE_SIZE * 3 > mX && tmp + TILE_SIZE - 4 * TILE_SIZE < mY && tmp + TILE_SIZE * 4 > mY) {
                    for (int i = 0; i < MATRIX_WIDTH; i++)
                        for (Tile tile : tileMatrix[i]) {
                            {
                                if (mX < tile.getTranslateX() + TILE_SIZE && mX > tile.getTranslateX() && mY < tile.getTranslateY() + TILE_SIZE && mY > tile.getTranslateY()) {
                                    root.getChildren().remove(tile);
                                    break;
                                }
                            }
                        }
                }
            }
        });

        scene.setOnKeyPressed(e -> {

            Thread t1;
            t1 = new Thread(() -> {
                switch (e.getCode()) {
                    case A:
                        moveTiles(-X_WALK_SPEED);
                        break;
                    case D:
                        moveTiles(X_WALK_SPEED);
                        break;
                }
            });
            t1.start();
        });

        stage.setScene(scene);
        stage.show();

    }

    private class Tile extends Rectangle {
        int type;
        int damage;

        Tile(int type, double x, double y) {
            super(TILE_SIZE, TILE_SIZE,getImageByColorType(type));
            this.type = type;
            this.damage = this.type * 700;
            this.setStroke(Color.BLACK);
            this.setStrokeWidth(1);
            this.setTranslateX(x);
            this.setTranslateY(y);
        }

    }

    private class Player extends Rectangle {
        int hp;
        final String name;
        Player(String name, int x, int y, Color color){
            super(TILE_SIZE, 2*TILE_SIZE, color);
            setTranslateX(x);
            setTranslateY(y);
            this.name = name;
        }
    }

    ImagePattern getImageByColorType(int type) {
        return switch (type) {
            case GRASS -> GRASS_IMAGE;
            case STONE -> STONE_IMAGE;
            case DARK_ORE -> DARK_ORE_IMAGE;
            case BLUE_ORE -> BLUE_ORE_IMAGE;
            default -> DIRT_IMAGE;
        };
    }

    void moveTiles(int pixels) {
        for (int i = 0; i < MATRIX_WIDTH; i++)
            for (Tile tile : tileMatrix[i]) {
                tile.setTranslateX(tile.getTranslateX() + pixels + TILE_SIZE < 0 ? WINDOW_WIDTH + pixels : (tile.getTranslateX() + pixels > WINDOW_WIDTH ? -TILE_SIZE + pixels : tile.getTranslateX() + pixels));
            }
    }

    public static void main(String[] args) {
        launch();
    }


}