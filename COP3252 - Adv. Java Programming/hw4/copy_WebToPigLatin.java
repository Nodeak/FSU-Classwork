/**
 * Kaedon Hamm (kah16h)
 * Pig Latin Web Translator
 * Due Date: 3/1/2021
 * Advanced Java Programming
 */

import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.Formatter;
import java.io.*;

public class WebToPigLatin{
    String sfile;
    BufferedWriter ofile = null;
    BufferedReader ifile = null;

    public WebToPigLatin(String ifile_name, String ofile_name){
        try{
            ifile = new BufferedReader(new FileReader(ifile_name));

            // Opens output file and checks if already exists. If so, turn user away
            File file_check = new File(ofile_name);
            if(file_check.exists()){
                System.out.println("Output file already exists. Please choose another name.");
                System.exit(0);
            }
            else
                ofile = new BufferedWriter(new FileWriter(ofile_name));
        }
        catch(FileNotFoundException ex)
        {
            System.out.println("File not found: " + ifile_name);
        }
        catch(IOException ex){
            System.out.println(ex);
        }
    }

    public void parse(){
        int c_bits;
        StringBuilder temp = new StringBuilder();       // Holds temporary word until a ' ' is found    
        StringBuilder full_word = new StringBuilder();  // Temp transfers to this
        try{
            while((c_bits = ifile.read()) != -1){
                char c = (char)c_bits;
                String word = full_word.toString();

                // HTML Tag Check
                if(c == '<'){
                    temp.append(translate(word) + c);
                    int t_bits;
                    while((char)(t_bits = ifile.read()) != '>'){
                        temp.append((char)t_bits);
                        full_word.setLength(0);
                    }
                    temp.append((char)t_bits);
                }

                // Text &; Tag Check
                else if(c == '&'){
                    temp.append(c);
                    int t_bits;
                    while((char)(t_bits = ifile.read()) != ';'){
                        temp.append((char)t_bits);
                        full_word.setLength(0);
                    }
                    temp.append((char)t_bits);
                }

                // Ignore Numbers
                else if(Character.isDigit(c)){
                    temp.append(translate(word) + c);
                    full_word.setLength(0);
                }

                // Ignore Punctuation
                else if(isPunctuation(c)){
                    // Checking Abbreviations
                    if(word.length() == 1){
                        if(hasVowel(word))
                            temp.append(translate(word) + c);
                        else
                            temp.append(word + c);
                    }
                    else{
                        if(hasVowel(word))
                            temp.append(translate(word) + c);
                        else
                            temp.append(word + c);
                    }
                    full_word.setLength(0);
                }
                
                // Checks for single character in line or at end of line
                else if((c == ' ' || c == '\n') && word.length() == 1 && !hasVowel(word)){
                    if(c == ' ')
                        temp.append(word + ' ');
                    else
                        temp.append(word + '\n');
                    full_word.setLength(0);
                }
                else{

                    // Switch case for invisible characters
                    switch(c)
                    {
                        case '\n': temp.append(translate(word));
                                   temp.append("\n");
                                   full_word.setLength(0); break;
                        case '\t': temp.append("\t"); break;
                        case '\b': temp.append("\b"); break;
                        case '\r': temp.append(""); break;
                        case '\f': temp.append("\f"); break;
                        case '\'': temp.append("\'"); break;
                        case '\"': temp.append("\""); break;
                        case '\\': temp.append("\\"); break;
                        case ' ': temp.append(translate(word));
                                  temp.append(" ");
                                  full_word.setLength(0); break;
                        default: full_word.append(c);
                    }
                }
            }
            ofile.write(temp.toString());
        }
        catch(IOException ex){
            System.out.println(ex);
        }
    }
    
    // Checks all punctuation (besides ')
    public boolean isPunctuation(char c){
        if("~!@#$%^&*()_+-={}[]|\\\":;/.,?><".indexOf(c) != -1){
            return true;
        }
        return false;
    }

    // Checks if word has vowels
    public static boolean hasVowel(String word){
        if(word == null)
            return false;

        for(int i = 0; i < word.length(); i++){
            if("AEIOUYaeiouy".indexOf(word.charAt(i)) != -1)
                return true;
        }

        return false;
    }

    // Translates word into Pig Latin based on rules
    private String translate(String fw){
        StringBuilder sb = new StringBuilder(fw);
        if(fw == "")
            return "";
        else if(firstVowel(fw) == 0)        // Vowel is first letter
            return sb + "way";

        // Apply Rules

        // Flag for removal of capitalization before translation
        if(isCapital(fw)){
            char first_char = Character.toLowerCase(sb.charAt(0));
            sb.replace(0, 1, Character.toString(first_char));
        }

        int first_vowel = firstVowel(sb.toString());
        sb.append(sb.substring(0,first_vowel) + "ay");
        sb.delete(0, first_vowel);
        
        // Flag for capitalization after translation
        if(isCapital(fw)){
            char first_char = Character.toUpperCase(sb.charAt(0));
            sb.replace(0, 1, Character.toString(first_char));
        }

        return sb.toString();
    }

    // Checks to find the first vowel
    private int firstVowel(String word){

        // First letter is vowel, not Y
        if("AEIOUaeiou".indexOf(word.charAt(0)) != -1){
            return 0;
        }

        // If first vowel is Y, ignores and finds vowel (including Y)
        else if("Yy".indexOf(word.charAt(0)) != -1 && word.length() != 1){
            for(int i = 1; i < word.length(); i++){
                if("AEIOUYaeiouy".indexOf(word.charAt(i)) != -1)
                    return i;
            }
        }

        // First letter const. 
        for(int i = 0; i < word.length(); i++){
            if("AEIOUYaeiouy".indexOf(word.charAt(i)) != -1)
                return i;
        }
        return 0;
    }

    // Flag for Capitalization
    public static boolean isCapital(String word){
        if(Character.isUpperCase(word.charAt(0)))
            return true;
        return false;
    }
    
    public static void main(String args[]){
        if(args.length != 2){
            System.out.println("Usage: java WebToPigLatin inputFile outputFile\nMust have two command-line parameters");
            System.exit(0);
        }
        WebToPigLatin ham = new WebToPigLatin(args[0], args[1]);
        ham.parse();

        // Close files
        try{
            ham.ifile.close();
            ham.ofile.close();
        }
        catch(IOException ex){
            System.out.println("Closing files error: " + ex);
        }
    }
}