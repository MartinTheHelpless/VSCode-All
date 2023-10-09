package com.example.demo;

import javafx.geometry.Point2D;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class Ball {


    double posY;

    double posX;
    int size;
    Rectangle ball;
    int dirX;
    int dirY;

    Ball(double posX, double posY, int size) {

        this.ball = new Rectangle(size, size);
        this.posX = posX;
        this.posY = posY;
        this.size = size;
    }

}
