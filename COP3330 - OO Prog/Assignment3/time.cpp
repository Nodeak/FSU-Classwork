/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 3
 *		
 *		File sets Time based upon given input, converts time into just seconds and back to normal.
 *		Also overloads <<,>>,+,-,*,<,>,<=,>=,==,!=,++,and -- to be functional with the Time objects.
*/

#include <iostream>
#include "time.h"	

using namespace std;

// CONSTRUCTORS
Time::Time(){														// Defualt constructor
	setTime(0,0,0,0);
}

Time::Time(int tsec){												// Allows for one parameter to be passed in in the form of seconds
	setTime(0,0,0,tsec);
	convertNorm();
}
	
Time::Time(int tdays, int thour, int tmin, int tsec){				// Allows for specific parameter set to be passed in
	
	if (setTime(tdays, thour, tmin, tsec) == false)
		setTime(0,0,0,0);
	else{
		setTime(tdays, thour, tmin, tsec);
		convertNorm();
	}

}

// MEMBER FUNCTIONS
bool Time::setTime(int tdays, int thour, int tmin, int tsec){		// Function to set Time object's variables
	
	if (tsec < 0 || tmin < 0 || thour < 0 || tdays < 0)
		return false;
	else{
		sec = tsec;
		min = tmin;
		hour = thour;
		days = tdays;
		return true;
	}
}

void Time::convertNorm(){											// Converts Time to normal so that there are no numbers that exceed the appropriate limit
	
	while (sec >= 60){
		sec = sec - 60;
		min++;
	}
	while (min >= 60){
		min = min - 60;
		hour++;
	}
	while (hour >= 24){
		hour = hour - 24;
		days++;
	}
	
	if (days == 0 && hour == 0 && min == 0 && sec < 0)
		sec = 0;
}

void Time::convertSec(){											// Converts Time to seconds to make it easier for +, -, *, ++, -- and comparison operators
	
	hour = hour + (days * 24);
	days = 0;
	min = min + (hour * 60);
	hour = 0;
	sec = sec + (min * 60);
	min = 0;
	
}

// OVERLOADED OPERATORS make given operators compatible with Time objects
ostream& operator<<(ostream& os, const Time& t){
	
	os << t.days << "~";
	
	// adding 0 to HOURS
	if (t.hour < 10)
		os << "0" << t.hour << ":";
	else
		os << t.hour << ":";
	
	// adding 0 to MINUTES
	if (t.min < 10)
		os << "0" << t.min << ":";
	else
		os << t.min << ":";
	
	//adding 0 to SECONDS
	if (t.sec < 10)
		os << "0" << t.sec << endl;
	else
		os << t.sec << endl;
	
	return os;
		
}

istream& operator>>(istream& is, Time& t){
	char symbol;
	is >> t.days >> symbol >> t.hour >> symbol >> t.min >> symbol >> t.sec;
	if (t.setTime(t.days,t.hour,t.min,t.sec) == false)
		t.setTime(0,0,0,0);
	else
		t.convertNorm();
	return is;
}

Time operator+(const Time& t1, const Time& t2){
	Time temp = t1;
	temp.convertSec();
	int s1 = temp.sec;
	
	temp = t2;
	temp.convertSec();
	int s2 = temp.sec;
	
	temp.sec = s1 + s2;
	
	temp.convertNorm();
	
	return temp;
	
}

Time operator-(const Time& t1, const Time& t2){
	Time temp = t1;
	temp.convertSec();
	int s1 = temp.sec;
	
	temp = t2;
	temp.convertSec();
	int s2 = temp.sec;
	
	temp.sec = s1 - s2;
	
	temp.convertNorm();
	
	return temp;
}

Time operator*(const Time& t1, int m){
	Time temp = t1;
	temp.convertSec();
	int s1 = temp.sec;
	
	temp.sec = s1 * m;
	
	temp.convertNorm();
	
	return temp;
}

bool operator<(const Time& t1, const Time& t2){
	Time temp1 = t1;
	Time temp2 = t2;
	temp1.convertSec();
	temp2.convertSec();
	int s1 = temp1.sec;
	int s2 = temp2.sec;
	if(s1 < s2)
		return true;
	else
		return false;
}

bool operator<=(const Time& t1, const Time& t2){
	Time temp1 = t1;
	Time temp2 = t2;
	temp1.convertSec();
	temp2.convertSec();
	int s1 = temp1.sec;
	int s2 = temp2.sec;
	if(s1 <= s2)
		return true;
	else
		return false;
}

bool operator>(const Time& t1, const Time& t2){
	Time temp1 = t1;
	Time temp2 = t2;
	temp1.convertSec();
	temp2.convertSec();
	int s1 = temp1.sec;
	int s2 = temp2.sec;
	if(s1 > s2)
		return true;
	else
		return false;
}

bool operator>=(const Time& t1, const Time& t2){
	Time temp1 = t1;
	Time temp2 = t2;
	temp1.convertSec();
	temp2.convertSec();
	int s1 = temp1.sec;
	int s2 = temp2.sec;
	if(s1 >= s2)
		return true;
	else
		return false;
}


	Time temp1 = t1;
	Time temp2 = t2;
	temp1.convertSec();
	temp2.convertSec();
	int s1 = temp1.sec;
	int s2 = temp2.sec;
	if(s1 == s2)
		return true;
	else
		return false;
}

bool operator!=(const Time& t1, const Time& t2){
	Time temp1 = t1;
	Time temp2 = t2;
	temp1.convertSec();
	temp2.convertSec();
	int s1 = temp1.sec;
	int s2 = temp2.sec;
	if(s1 != s2)
		return true;
	else
		return false;
}

Time& Time::operator++(){
	convertSec();
	sec = sec + 1;
	convertNorm();
	return *this;
} 	

Time Time::operator++(int){
	Time temp = * this;
	convertSec();
	sec = sec + 1;
	convertNorm();
	return temp;
}
 	
Time& Time::operator--(){
	convertSec();
	sec = sec - 1;
	convertNorm();
	return *this;
}

Time Time::operator--(int){
	Time temp = * this;
	convertSec();
	sec = sec - 1;
	convertNorm();
	return temp;
}
