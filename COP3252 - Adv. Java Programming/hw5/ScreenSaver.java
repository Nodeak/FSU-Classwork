/**
 * Kaedon Hamm
 * COP3253 - HW5 - Due: 3/10/2021
 * Goal: Understand the Graphics2D and Java2D libraries
 * Assignment: Create a Screensaver on the JPanel
 *              - 50 Ovals, random sizes, colors, and stroke thickness
 *              - Must stay in frame
 *              - Use javax.swing.Timer to refresh every 1 second
 */

import java.awt.Graphics;
import java.awt.Color;
import java.awt.BasicStroke;
import java.awt.event.*;

import javax.swing.JPanel;
import javax.swing.JFrame;
import java.util.Random;
import java.awt.Graphics2D;
import javax.swing.Timer;

public class ScreenSaver extends JPanel{

    public void paintComponent(Graphics g){
        this.setBackground(Color.WHITE);
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;

        for(int i = 0; i < 50; i++){

            Random rand = new Random();
            int x,y,w,h;

            // Randomly generate an Oval until is stays in frame
            do{
                // Location of Oval
                x = rand.nextInt(getWidth());
                y = rand.nextInt(getHeight());
                
                // Size of Oval
                h = rand.nextInt(getWidth());
                w = rand.nextInt(getHeight());
            }while((x + w > getWidth()) || (y + h > getHeight()));

            // Sets the color for the next drawn Object
            g2.setColor(new Color(rand.nextInt(255), rand.nextInt(255), rand.nextInt(255)));
            g2.setStroke(new BasicStroke(rand.nextInt(9) + 1));
            g2.drawOval(x, y, w, h);
        }
    }

    public static void main(String args[]){
        JFrame frame = new JFrame("ScreenSaver");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        ScreenSaver bubbles = new ScreenSaver();
        frame.add(bubbles);

        frame.setSize(800, 600);
        frame.setVisible(true);

        // Generate Timer to generate an action every 1000ms (1s)
        Timer timer = new Timer(1000, new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                // Refresh the panel
                bubbles.revalidate();
                bubbles.repaint();
            } 
        });
        timer.start();      // Begin Timer, should have stop but that happens at close
    }
}