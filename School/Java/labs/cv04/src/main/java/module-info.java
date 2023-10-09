module com.example.cv04 {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires org.kordamp.bootstrapfx.core;
    requires com.almasb.fxgl.all;
    requires jdk.jfr;

    opens com.example.cv04 to javafx.fxml;
    exports com.example.cv04;
}