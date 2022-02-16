/**
 * Kaedon Hamm
 * COP3253 - HW5 - Due: 3/10/2021
 * Goal: Understand the Graphics2D and Java2D libraries
 * Assignment: Generate a Snowman
 *              - Must have specific body specifications, eyes, and arms
 *              - Must be colored randomly
 *              - Must fit in frame and maintain correct scaling during resize
 */

import java.awt.Graphics;
import java.awt.Color;
import javax.swing.JPanel;
import javax.swing.JFrame;
import java.util.Random;

public class Snowman extends JPanel{

    public void paintComponent(Graphics g){
        this.setBackground(Color.WHITE);
        super.paintComponent(g);
        Random rand = new Random();

        // Holders for often-used numbers. Makes code more legible
        int buffer = (int)((getHeight() * 0.25) / 2);
        double half_height = getHeight() / 2;
        double half_width = getWidth() / 2;

        // Bottom Circle - Circles generated from x,y rep. top-left corner of box
        int bot_hw = (int)(half_height - buffer);           // Height and Width on circles are same
        int bot_x = (int)(half_width - (bot_hw / 2));
        int bot_y = (int)(half_height);

        // Middle Circle
        int mid_hw = (int)((half_height - buffer) * (0.66666));
        int mid_x = (int)(half_width - (mid_hw / 2));
        int mid_y = (int)(half_height - mid_hw);

        // Top Circle
        int top_hw = (int)((half_height - buffer) * (0.3333));
        int top_x = (int)(half_width - (top_hw / 2));
        int top_y = (int)(buffer);


        // Draw Circles - Bottom, Middle, Top - Random colors
        g.setColor(new Color(rand.nextInt(255), rand.nextInt(255), rand.nextInt(255)));
        g.drawOval(bot_x, bot_y, bot_hw, bot_hw);
        g.setColor(new Color(rand.nextInt(255), rand.nextInt(255), rand.nextInt(255)));
        g.drawOval(mid_x, mid_y, mid_hw, mid_hw);
        g.setColor(new Color(rand.nextInt(255), rand.nextInt(255), rand.nextInt(255)));
        g.drawOval(top_x, top_y, top_hw, top_hw);
        g.setColor(new Color(0,0,0));

        // Calculate Eye Positions
        int eye_hw = (int)(top_hw * (0.1));
        int leye_x = (int)(half_width + eye_hw);
        int leye_y = (int)((buffer + (top_hw / 2) - eye_hw));
        int reye_x = (int)(half_width - eye_hw - eye_hw);
        int reye_y = (int)((buffer + (top_hw / 2) - eye_hw));
        
        // Draw Eyes
        g.fillOval(leye_x, leye_y, eye_hw, eye_hw);
        g.fillOval(reye_x, reye_y, eye_hw, eye_hw);

        // Calculate Arm Positions
        int mid_center_x = (int)(half_width);
        int mid_center_y = (int)(mid_y + (mid_hw / 2));
        
        int larm_start_x = (int)(mid_center_x + (Math.sin(Math.toRadians(45)) * (mid_hw / 2)));
        int larm_start_y = (int)(mid_center_y - (Math.cos(Math.toRadians(45)) * (mid_hw / 2)));
        int larm_stop_x = (int)(half_width + (half_width - bot_x));
        int larm_stop_y = (int)(top_y + (top_hw / 2));

        int rarm_start_x = (int)(mid_center_x - (Math.sin(Math.toRadians(45)) * (mid_hw / 2)));
        int rarm_start_y = (int)(mid_center_y - (Math.cos(Math.toRadians(45)) * (mid_hw / 2)));
        int rarm_stop_x = bot_x;

        // Draw Arms
        g.drawLine(larm_start_x, larm_start_y, larm_stop_x, larm_stop_y);
        g.drawLine(rarm_start_x, rarm_start_y, rarm_stop_x, larm_stop_y);



    }

    public static void main(String args[]){
        JFrame frame = new JFrame("Snowman");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        Snowman frosty = new Snowman();
        frame.add(frosty);

        frame.setSize(600, 400);
        frame.setVisible(true);
    }
}