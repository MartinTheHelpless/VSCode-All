package com.example.cv04;

import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.Text;


public class Player extends Rectangle {

    final int WINDOW_WIDTH = 900;
    final int WINDOW_HEIGHT = 500;
    final int PADDLE_HEIGHT = 100;
    int score;
    double height;
    double colorIndex;
    double width;
    boolean moveU = false;
    boolean moveDwn = false;
    Color color;
    final String name;
    Text scoreTab;

    Player(Pane pane, String name, double height, double width, double x, double y, Color color, double scoreFSize, double playerNumber) {
        super(width, height, color);
        Font font = new Font("Roboto Mono", scoreFSize);
        scoreTab = new Text((playerNumber > 1 ? (double) WINDOW_WIDTH / 2 - 75 : (double) WINDOW_WIDTH / 2 + 45), 50, "0");
        scoreTab.setFont(font);
        scoreTab.setFill(Color.WHITE);
        scoreTab.setFill(Color.WHITE);
        colorIndex = 0;
        pane.getChildren().add(scoreTab);
        this.name = name;
        this.score = 0;
        this.height = height;
        this.width = width;

        setTranslateX(x);
        setTranslateY(y);
    }

    double getColorIndex() {
        return this.colorIndex;
    }

    void setColorIndex(int colorIndex) {
        this.colorIndex = colorIndex;
    }

    void setColor(Color color) {
        this.color = color;
        this.setFill(this.color);
    }

    void moveUp() {
        this.moveDwn = false;
        this.moveU = true;
        Thread t2;
        t2 = new Thread(new Runnable() {
            @Override
            public void run() {
                while (moveU) {
                    setTranslateY(getTranslateY() - 3);
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                    if (getTranslateY() <= 0) {
                        setTranslateY(5);
                        moveU = false;
                    }
                }
            }
        });
        t2.start();
    }

    void moveDown() {
        this.moveU = false;
        this.moveDwn = true;
        Thread t1;
        t1 = new Thread(new Runnable() {
            @Override
            public void run() {
                while (moveDwn) {
                    setTranslateY(getTranslateY() + 3);
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                    if (getTranslateY() + PADDLE_HEIGHT >= WINDOW_HEIGHT) {
                        setTranslateY(WINDOW_HEIGHT - PADDLE_HEIGHT);
                        moveDwn = false;
                    }
                }
            }
        });
        t1.start();
    }

    void drawscorePlusOne() {
        this.score += 1;
        this.scoreTab.setText(String.valueOf(score));
    }

}