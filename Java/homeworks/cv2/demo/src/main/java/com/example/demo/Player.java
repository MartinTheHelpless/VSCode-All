package com.example.demo;

public class Player {
    int pts;
    double posX;
    double posY;

    int height;

    int width;

    Player(int width, int height, double x, double y) {
        this.pts = 0;
        this.posX += x;
        this.posY += y;
        this.height = height;
        this.width = width;
    }

}
