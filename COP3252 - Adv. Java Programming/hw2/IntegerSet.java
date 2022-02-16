/**
 * class IntegerSet.java
 * Author: Kaedon Hamm
 * 
 * For COP3252, Java Programming
 */


public class IntegerSet
 {
    private boolean[] Set;

    public IntegerSet(){
        Set = new boolean[101];
        for(boolean num : Set)
            num = false;
    }

    // Combines two sets to hold numbers existing in either set
    public IntegerSet union(IntegerSet iSet){
        IntegerSet temp = new IntegerSet();
        for(int i = 0; i < 101; i++){
            if(iSet.Set[i] == true || this.Set[i] == true)
                temp.Set[i] = true;
        }
        return temp;
    }

    // Combines two sets to only hold numbers existing in both sets
    public IntegerSet intersection(IntegerSet iSet){
        IntegerSet temp = new IntegerSet();
        for(int i = 0; i < 101; i++){
            if(iSet.Set[i] == false || this.Set[i] == false)
                temp.Set[i] = false;
            else
                temp.Set[i] = true;
        }
        return temp;
    }

    // Inserts number into set
    public IntegerSet insertElement(int data){
        this.Set[data] = true;
        return this;
    }

    // Deletes number from set
    public IntegerSet deleteElement(int data){
        this.Set[data] = false;
        return this;
    }

    // Compares two sets
    public boolean isEqualTo(IntegerSet iSet){
        for(int i = 0; i < 101; i++){
            if(this.Set[i] != iSet.Set[i])
                return false;
        }
        return true;
    }

    // Prints set to screen. ex) 5 25 40 (--- for an empty set)
    public String toString(){
        String message = "";
        for(int i = 0; i < 101; i++){
            if(this.Set[i] == true)
            message += i + " ";
        }

        if(message == "")
            return "---";

        return message;
    }
}