package com.example.cv04;

import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class Ball extends Rectangle {
    int size;
    Color color;
    boolean hMove;
    boolean vMove;
    final int WINDOW_WIDTH = 900;
    final int WINDOW_HEIGHT = 500;

    Ball(int size, Color color) {
        super(size, size, color);
        this.hMove = false;
        this.vMove = false;
        this.size = size;
        this.color = color;
        setTranslateX(WINDOW_WIDTH / 2 - size / 2);
        setTranslateY(WINDOW_HEIGHT / 2 - size / 2);
    }
    void setColor(Color color) {
        this.color = color;
        this.setFill(color);
    }

    boolean getHMove(){
        return  this.hMove;
    }

    boolean getVMove(){
        return  this.vMove;
    }

    void switchXdir(){
        this.hMove = !this.hMove;
    }

    void switchYdir(){
        this.vMove = !this.vMove;
    }

}