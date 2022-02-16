// Pi class
// Will approximate Pi to the number of iterations done using the following formula
// 4 * ((-1)^n / 2n+1)

import java.util.Scanner;       // Used for console inputs
import java.lang.Math;

public class Pi {

    public static void main(String[] args){
        Scanner input = new Scanner(System.in);

        System.out.println("Exercise 5.20: 'Approximating PI'");
        System.out.println("Compute to how many terms of the series? ");
        int series = input.nextInt();
        FULL_SERIES(series);
        input.close();
    }

    public static void FULL_SERIES(int series){
        System.out.println("terms\tPi approximation");

        for(int i = 1; i <= series; i++){
            System.out.printf("%d\t%f%n", i, PI_APPROX(i));
        }
    }

    public static double PI_APPROX(int num){
        double approx = 0.0;
        int sign = 1;        // Chooses +/-

        for(int i = 0; i < num; i++){
            if(sign == 1){
                approx = approx + (4.0 / (double)(2*i + 1));
                sign = 0;
            }
            else{
                approx = approx - (4.0 / (double)(2*i + 1));
                sign = 1;
            }
        }
        return approx;
    }
}