// class Fraction
// Author:  Kaedon Hamm (Based off of Bob Myer's Fraction Class)
//
// For COP3252, Java Programming

public class Fraction
{
    private int numerator = 0;		    // numerator (and keeps sign)
    private int denominator = 1;		// always stores positive value

    public Fraction(){

    }

    public Fraction(int n, int d){
        if (set(n,d)==false)
            set(0,1);
    }

    public boolean set(int n, int d){
        if (d > 0){
            numerator = n;
            denominator = d;
            return true;
        }
        else
            return false;
    }

    public String toString(){
        return (numerator + "/" + denominator);
    }

    public int getNumerator(){
        return numerator;
    }

    public int getDenominator(){
        return denominator;
    }

    public double decimal(){
        return (double)numerator / denominator;
    }

    public Fraction simplify(){
        // Default to 0/1 for 0/N
        if(this.numerator == 0)
            return new Fraction(this.numerator, 1);

        // Find GCF and divide numer & denom by it
        int gcf = 0;
        for(int i = 1; i < this.denominator; i++){
            if(this.denominator % i == 0 && this.numerator % i == 0){
                gcf = i;
            }
        }
        return new Fraction(this.numerator / gcf, this.denominator / gcf);
    }

    public Fraction add(Fraction f){
        int numer = (this.numerator * f.denominator) + (f.numerator * this.denominator);
        int denom = this.denominator * f.denominator;

        return new Fraction(numer, denom).simplify();
    }

    public Fraction subtract(Fraction f){
        int numer = (this.numerator * f.denominator) - (f.numerator * this.denominator);
        int denom = this.denominator * f.denominator;

        return new Fraction(numer, denom).simplify();
    }

    public Fraction multiply(Fraction f){
        int numer = this.numerator * f.numerator;
        int denom = this.denominator * f.denominator;

        return new Fraction(numer, denom).simplify();
    }

    public Fraction divide(Fraction f){
        int numer = this.numerator * f.denominator;
        int denom = this.denominator * f.numerator;

        if(denom < 0){                      // Switch negative sign back to numerator
            denom *= -1;
            numer *= -1;
        }

        return new Fraction(numer, denom).simplify();
    }
}