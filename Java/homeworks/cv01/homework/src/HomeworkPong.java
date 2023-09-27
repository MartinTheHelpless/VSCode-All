import javax.swing.*;
import java.awt.*;

public class HomeworkPong {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(HomeworkPong::run);
    }

    private static void run() {
        JFrame frame = new JFrame("Pong");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(720, 512);
        frame.setResizable(false);

        JPanel rectanglesPanel = new JPanel() {
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);

                setBackground(Color.BLACK);

                g.setColor(Color.WHITE);

                int centerY = (getHeight() - 50) / 2;

                g.fillRect(0, 0, frame.getWidth(), (frame.getHeight() / 100) * 4);

                g.fillRect(0, (frame.getHeight() / 100)*98, frame.getWidth(), (frame.getHeight() / 100) * 5);

                // Tady u toho spodního rectanglu je menší problém z nějakého důvodu, kde se asi zaokrouhluje ten výpočet
                // a je tam asi 2px cca mezera od spodního kraje k tomu rectanglu. Kdybych dal 99% a ne 98% z výšky framu,
                // nebylo by to hezké, tak jsem tam dal 5% na výšku rectanglu, aby to nebylo vidět. Když tam dáte 4, tak to uvidíte.
                // Je to jen menší kosmetiská úprava a myslím si, že to ani není poznat. Jen jsem si chtěl odůvodnit těch 5%,
                // když na ostatních řádcích jsou 4 procenta výšky framu.

                g.fillRect((frame.getWidth() / 100) * 3, (frame.getHeight() / 2) - (frame.getWidth() / 100) * 5, (frame.getWidth() / 100) * 2, (frame.getWidth() / 100) * 10);

                g.fillRect((frame.getWidth() / 100) * 97, (frame.getHeight() / 2) - (frame.getWidth() / 100) * 5, (frame.getWidth() / 100) * 2, (frame.getWidth() / 100) * 10);

                for (int i = 0; i < 92 / 4; i++) {
                    if (i % 2 == 0) {
                        g.fillRect(frame.getWidth() / 2 - (frame.getHeight() / 100) * 2, (frame.getHeight() / 100) * 4 + i * (frame.getHeight() / 25), (frame.getHeight() / 100) * 3, (frame.getHeight() / 100) * 3);
                    }
                }

            }
        };

        Font labelFont = new Font("SansSerif", Font.BOLD, 60); // Example font settings

        JLabel scoreLeft = new JLabel("4");
        scoreLeft.setFont(labelFont);
        scoreLeft.setForeground(Color.WHITE);
        scoreLeft.setHorizontalAlignment(SwingConstants.CENTER);
        scoreLeft.setBounds((frame.getWidth()/100)*40, (frame.getWidth()/100)*5, (frame.getWidth()/100)*7, (frame.getWidth()/100)*7);

        JLabel scoreRight = new JLabel("0");
        scoreRight.setFont(labelFont);
        scoreRight.setForeground(Color.WHITE);
        scoreRight.setHorizontalAlignment(SwingConstants.CENTER);
        scoreRight.setBounds((frame.getWidth()/100)*55, (frame.getWidth()/100)*5, (frame.getWidth()/100)*7, (frame.getWidth()/100)*7);


        frame.add(scoreRight);
        frame.add(scoreLeft);

        frame.add(rectanglesPanel);

        frame.setVisible(true);
    }
}
