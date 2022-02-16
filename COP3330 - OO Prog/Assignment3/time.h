/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 3
 *		
 *		Header file for Time class that provides prototype for member functions
 *		as well as overloaded operators.
*/

#include <iostream>

using namespace std;

class Time
{
		// 	Overloaded operators
		friend ostream& operator<<(ostream&, const Time&);
		friend istream& operator>>(istream&, Time&);
		friend Time operator+(const Time&, const Time&);
		friend Time operator-(const Time&, const Time&);
		friend Time operator*(const Time&, int);
		friend bool operator<(const Time&, const Time&);
		friend bool operator<=(const Time&, const Time&);
		friend bool operator>(const Time&, const Time&);
		friend bool operator>=(const Time&, const Time&);
		friend bool operator==(const Time&, const Time&);
		friend bool operator!=(const Time&, const Time&);
		
	
	public:
		// Constructors
		Time();
		Time(int tsec);
		Time(int tdays, int thour, int tmin, int tsec);
		
		// Member Functions
		void convertSec();
		void convertNorm();
		
		bool setTime(int tdays, int thour, int tmin, int tsec);
		
		// More Overloaded Operators
		Time& operator++();		//prefix inc
		Time operator++(int);	//postfix inc
		Time& operator--();		//prefix dec
		Time operator--(int);	//postfix dec
		
	private:
		// Pricate Variables
		int sec;
		int min;
		int hour;
		int days;
		
		
		
};