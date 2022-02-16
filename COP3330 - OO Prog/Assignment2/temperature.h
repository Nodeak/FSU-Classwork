/*		Kaedon Hamm
		COP 3330 Section 7
		Assignment 2
		
		Header file for Temperature class that provides prototype for functions
		as well as declares private variables that the class has access to.
*/	

class Temperature
{
	
	public:
		Temperature(double deg = 0, char tscale = 'C');
		void Input();
		void Show() const;
		bool Set(double deg, char s);
		double GetDegrees() const;
		char GetScale() const;
		bool SetFormat(char f);
		bool Convert(char sc);
		int Compare (const Temperature& d);
		
	
	private:
		double degrees;
		char scale;
		char format;
		bool degCheck(double deg, char tscale) const;
		void setDefaults();
};