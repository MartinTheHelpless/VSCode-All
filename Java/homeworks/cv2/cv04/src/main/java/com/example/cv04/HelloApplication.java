package com.example.cv04;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {

    private final Pane root = new Pane();

    private Pane createContent(){

        root.setPrefSize(800, 600);

        return root;

    }

    @Override
    public void start(Stage stage) throws IOException {

        Scene scene = new Scene(createContent());


        stage.setScene(scene);
        stage.show();
    }

    private static class Player extends Rectangle {
        int score;
        int height;
        int width;
        Color color;
        final String name;
        Rectangle scoreDisplay;

        Player(String name, int height, int width, int x, int y, Color color){

            this.name = name;
            this.score = 0;
            this.height = height;
            this.width = width;
            setTranslateX(x);
            setTranslateY(y);

        }



    };












    public static void main(String[] args) {
        launch();
    }

}