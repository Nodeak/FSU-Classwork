/**
 * Kaedon Hamm
 * COP3253 - HW5 - Due: 3/10/2021
 * Goal: Understand the Graphics2D and Java2D libraries
 * Assignment: Create a JPanel that generates 5 randomly sized and colored triangles
 *              that fit in the frame.
 */

import java.awt.Graphics;
import java.awt.Color;
import java.awt.geom.GeneralPath;
import javax.swing.JPanel;
import javax.swing.JFrame;
import java.util.Random;
import java.awt.Graphics2D;

public class Triangle extends JPanel{

    public void paintComponent( Graphics g){

        this.setBackground(Color.WHITE);
        super.paintComponent(g);            // Calls superclass's paintComponent
        Graphics2D g2 = (Graphics2D) g;

        // Creates 5 triangles using the `g` paintComponent
        for(int i = 0; i < 5; i++){

            Random rand = new Random();
            int h = this.getHeight();
            int w = this.getWidth();

            // Sets the color for the next drawn Object
            //g2.setColor(new Color(rand.nextInt(255), rand.nextInt(255), rand.nextInt(255)));
            Color b = new Color(0, 0, 255);
            g2.setColor(b);
            //g.drawArc(200,150,65,30,270,180);            
            // Set of x,y coordinates for GeneralPath to use
            int[] xpoints = new int[] {rand.nextInt(w), rand.nextInt(w), rand.nextInt(w)};
            int[] ypoints = new int[] {rand.nextInt(h), rand.nextInt(h), rand.nextInt(h)};
            GeneralPath path = new GeneralPath(GeneralPath.WIND_NON_ZERO, xpoints.length);

            // Draw triangle
            path.moveTo(xpoints[0], ypoints[0]);
            path.lineTo(xpoints[1], ypoints[1]);
            path.lineTo(xpoints[2], ypoints[2]);
            path.lineTo(xpoints[0], ypoints[0]);
            path.closePath();


            g.drawOval(200,300,50,100) / 2;
            // Color in Triangle
            //((Graphics2D)g).fill(path);
        }
    }

    public static void main(String args[]){

        JFrame frame = new JFrame("Triangle");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        Triangle phineas = new Triangle();
        frame.add(phineas);             // Adds Triangle JPanel to JFrame

        frame.setSize(500,500);         // Default window size
        frame.setVisible(true);
    }
}