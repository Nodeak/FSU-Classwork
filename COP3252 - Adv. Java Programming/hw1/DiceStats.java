// DiceStats class
// Reads in amount of dice and number of rolls and creates sim of all those rolls
// Some comments might seem unnecessary but are used as notes/reference for myself later.

import java.util.Scanner;       // Used for console inputs
import java.lang.Math;

public class DiceStats {
    public static int dice;
    public static int rolls;

    // Required for random number range
    public static int max = 6;
    public static int min = 1;
    public static int range = max - min + 1;
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);

        System.out.print("How many dice will constitute one roll? ");                   // Record number of dice
        dice = input.nextInt();

        System.out.print("How many rolls? ");                                           // Record number of rolls
        rolls = input.nextInt();

        dicestats();
    }

    public static void dicestats(){
        System.out.println("\nSum\t# of times\tPercentages\n");
        
        int[] results = new int[dice*6 + 1];                                            // Initialize and fill results array
        for(int i = 0; i <= dice*6; i++){
            results[i] = 0;
        }

        for(int i = 0; i < rolls; i++){                                                 // Calculate all rolls
            int num = 0;
            for(int j = 0; j < dice; j++){
                num += (int)(Math.random() * range) + min;                  // Adding the results of each die together
            }
            results[num]++;
        }

        for(int i = 0; i <= dice*6; i++){       
            if(i >= dice){
                double ratio = ((double)results[i] / (double)rolls) * 100;              // Calculate ratio to %

                System.out.printf("%d\t%d\t\t%.2f", i, results[i], ratio);
                System.out.print("%\n");
            }
        }
    }
}