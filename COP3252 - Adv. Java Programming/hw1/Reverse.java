// Reverse class

import java.util.Scanner;       // Used for console inputs

public class Reverse {
    public static void main(String[] args){
		Scanner input = new Scanner(System.in);

		while(true){
			System.out.print("Please enter a long integer (0 to quit): ");
			long original = input.nextLong();
		
			if(original == 0){
				break;
			}
			
			// Reverse string using StringBuilder (Java5)
			String og_string = Long.toString(original);
			String rev_string = new StringBuilder(og_string).reverse().toString();

			long reverse = Long.parseLong(rev_string);

			System.out.println(reverse);
		}
		input.close();
    }
}
