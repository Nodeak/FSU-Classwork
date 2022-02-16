/**
 * Kaedon Hamm
 * COP3253 - HW5 - Due: 3/24/2021
 * Goal: More practice with Swing and AWT
 * Assignment: Create a guessing game that gives feedback on guess as well as can 
 *              be played again or closed out.
 * Status: Completed.
 * 
 * Things to change/try: setContentPane(); --> frame.getContentPane().add(panel);
 */

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.event.*;

import javax.swing.*;

import java.util.Random;

public class Guess extends JFrame{

    private int targetNum;
    private int prevNum;
    private int resultNum = 0;

    public Guess(){
        super("Your Guess is My Command");

        // Starts Game
        JPanel gamePanel = createGamePanel();
        add(gamePanel);
    }

    // Generate Game Panel
    private JPanel createGamePanel(){

        // Generate new Random number
        Random rand = new Random();
        targetNum = rand.nextInt(1000);

        // Components
        JPanel panel = new JPanel();
        JLabel instructions = new JLabel("Pick a number 1-1000");
        JLabel hintLabel = new JLabel("Good Luck!");
        JTextField guessField = new JTextField(4);
        JButton guessButton = new JButton("Guess");
        JLabel prevGuess = new JLabel("Previous Guess: ");

        panel.setBackground(Color.WHITE);

        // Format components on panel
        guessField.setMaximumSize(guessField.getPreferredSize());
        instructions.setAlignmentX(CENTER_ALIGNMENT);
        hintLabel.setAlignmentX(CENTER_ALIGNMENT);
        guessField.setAlignmentX(CENTER_ALIGNMENT);
        guessButton.setAlignmentX(CENTER_ALIGNMENT);
        prevGuess.setAlignmentX(CENTER_ALIGNMENT);

        // Add components to panel
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.add(instructions);
        panel.add(hintLabel);
        panel.add(guessField);
        panel.add(guessButton);
        panel.add(prevGuess);

        // 'Guess' is pushed
        guessButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e){
                try{
                    int guessNum = Integer.parseInt(guessField.getText());
                    int guessDiff = targetNum - guessNum;
                    
                    // Gives user a hint of direction
                    if(guessDiff > 0)
                        hintLabel.setText("Too Low!");
                    else if(guessDiff < 0)
                        hintLabel.setText("Too High!");
                    else
                        hintLabel.setText("Spot On!");
                    

                    // Guess comparison changes background
                    if(guessNum == targetNum){                              // Target == Guess
                        setContentPane(createEndPanel());                   // changes to end screen
                        invalidate();
                        validate();
                    }
                    else if(prevNum != 0 && guessNum == prevNum){
                        panel.setBackground(Color.WHITE);
                    }
                    else if(targetNum < guessNum && prevNum != 0){
                        if(prevNum < guessNum){                              // Target < Prev < Guess -- Blue, getting Colder
                            panel.setBackground(new Color(78, 197, 237));
                        }
                        else{                                                // Target < Guess < Previous -- Red, getting warmer
                            panel.setBackground(new Color(168, 37, 37));
                        }
                    }
                    else if(guessNum < targetNum && prevNum != 0){
                        if(guessNum < prevNum){                              // Guess < Prev < Target -- Blue, getting Colder
                            panel.setBackground(new Color(78, 197, 237));
                        }
                        else{                                                // Prev < Guess < Target -- Red, getting warmer
                            panel.setBackground(new Color(168, 37, 37));
                        }
                    }
                    prevNum = guessNum;
                    prevGuess.setText("Previous guess: " + String.valueOf(prevNum));
                    guessField.setText("");
                }
                catch(Exception err){
                    System.out.println(err);
                }

            }
        });
        return panel;
    }

    // Generates the Winner Screen
    private JPanel createEndPanel(){

        // Components
        JPanel panel = new JPanel();
        JLabel winnerWinner = new JLabel("Winner winner,");
        JLabel chickeDinner = new JLabel("chicken dinner!");
        JTextField guessField = new JTextField(4);
        JButton playAgainButton = new JButton("Play Again");
        JButton closeButton = new JButton("Close");
        
        Box horiz = Box.createHorizontalBox();
        horiz.add(playAgainButton);
        horiz.add(closeButton);

        panel.setBackground(new Color(12, 179, 48));            // Green
        
        // Format components on panel
        guessField.setMaximumSize(guessField.getPreferredSize());
        guessField.setEditable(false);
        guessField.setText(String.valueOf(targetNum));
        winnerWinner.setAlignmentX(CENTER_ALIGNMENT);
        chickeDinner.setAlignmentX(CENTER_ALIGNMENT);
        guessField.setAlignmentX(CENTER_ALIGNMENT);
        horiz.setAlignmentX(CENTER_ALIGNMENT);

        // Add components to panel
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.add(winnerWinner);
        panel.add(chickeDinner);
        panel.add(guessField);
        panel.add(horiz);

        // Generates new version of GamePanel
        playAgainButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e){
                setContentPane(createGamePanel());
                invalidate();
                validate();
            }
        });

        closeButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e){
                System.exit(0);
            }
        });

        return panel;
    }

    public static void main(String[] args){
        Guess clue = new Guess();
        clue.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        clue.setSize(200, 150);
        clue.setVisible(true);
    }
}