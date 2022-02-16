import java.util.Scanner;
import java.io.*;

public class WebToPigLatin{
    String sfile;
    FileOutputStream ofile = null;
    FileInputStream ifile = null;

    public WebToPigLatin(String ifile_name, String ofile_name){
        try{
            ifile = new FileInputStream(new File(ifile_name));

            // Opens output file and checks if already exists. If so, turn user away
            File file_check = new File(ofile_name);
            if(file_check.exists()){
                System.out.println("Output file already exists. Please choose another name.");
                System.exit(0);
            }
            else
                ofile = new FileOutputStream(new File(ofile_name));
        }
        catch(FileNotFoundException ex)
        {
            System.out.println("File not found: " + ifile_name);
        }
    }

    // Taken from example code online
    public void copy_files(){
        /*try{
            // Continuously read a byte from fis and write it to fos
            int r;
            while ((r = ifile.read()) != -1)
            {
                ofile.write((byte)r);
            }
        }
        catch(IOException ex){
            System.out.println("Copy Files: " + ex);
        }*/

        Scanner s = new Scanner(ifile);//.useDelimiter("\\A");
            //this.sfile = s.hasNext() ? s.next() : "";
            while(s.hasNext()){
                ofile.write((byte)s.next());
            }

    }

    public void translate(){

    }

    
    public static void main(String args[]){
        if(args.length != 2){
            System.out.println("Usage: java WebToPigLatin inputFile outputFile\nMust have two command-line parameters");
            System.exit(0);
        }
        WebToPigLatin ham = new WebToPigLatin(args[0], args[1]);



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