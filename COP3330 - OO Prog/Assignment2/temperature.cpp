/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 2
 *		
 *		File sets temperature's degrees and scale, asks for keyboard input, 
 *		prints out the temperature in different formats, converts temperatures,
 *		compares temperatures, as well as makes sure given temperatures are valid.
*/

#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include "temperature.h"

using namespace std;

Temperature::Temperature(double deg, char tscale){						// Contructors
																		// Creates a temperature with a degrees and a scale
	scale = tscale = toupper(tscale);									// Makes sure it is a valid temperature
		
	if (deg < 0 && tscale == 'K'){
		setDefaults();
	}
	else if (tscale != 'C' && tscale != 'F' && tscale != 'K'){
		setDefaults();
	}
	else{
		if (degCheck(deg, tscale) == true){
			degrees = deg;
			scale = tscale;
		}
		else if (degCheck(deg, tscale) == false){
			setDefaults();
		}
	}
	format = 'D';		
	
}

void Temperature::Input(){												// Provides user with a way to input their own template
																		// Makes sure it is a valid temperature
	cout << "Please enter a temperature: ";
	cin >> degrees >> scale;
	scale = toupper(scale);
	bool torf = degCheck(degrees, scale);
	
	if (torf == false){
		while(torf == false){
			cout << "Invalid input. Please try again: ";
			cin >> degrees >> scale;
			scale = toupper(scale);
			torf = degCheck(degrees, scale);
		}
	}
}

void Temperature::Show() const{											// Prints out temperature with specified format
																		// and sets a default precision/format
	int oldprecision = cout.precision();
	
	if (format == 'D'){
		cout.precision(oldprecision);
		cout << degrees << " " << scale;
	}
	else if (format == 'P'){
		cout.precision(1);
		cout << fixed << degrees <<  " " << setprecision(oldprecision) << scale << endl;
	}
	else if (format == 'L'){
		cout.precision(oldprecision);
		if (scale == 'C')
			cout << degrees << " " << "Celsius" << oldprecision << endl;
		else if (scale == 'K')
			cout << degrees << " " << "Kelvin" << endl;
		else if (scale == 'F')
			cout << degrees << " " << "Fahrenheit" << endl;
	}
}

bool Temperature::Set(double deg, char s){								// Changes a temperature to the one sent in
																		// while also making sure it is valid to do so
	if (degCheck(deg, s) == true)
	{
		degrees = deg;
		scale = toupper(s);
	}
	else
		return false;
}

double Temperature::GetDegrees() const{
	return degrees;
}

char Temperature::GetScale() const{
	return scale;
}

bool Temperature::SetFormat(char f){									// Changes the format used in Show() function based upon the given parameter

	f = toupper(f);
	
	if (f == 'D'){
		format = 'D';
		return true;
		
	}
	else if (f == 'P'){
		format = 'P';
		return true;
		
	}
	else if (f == 'L'){
		format = 'L';
		return true;
	}
	else
		return false;
	
	
}

bool Temperature::Convert(char sc){										// Converts current degrees to a different scale depending on parameter sent in
	
	sc = toupper(sc);
	
	if (sc == 'C'){
		if (scale == 'F'){
			degrees = (degrees - 32) * (5/9);
			scale = 'C';
			SetFormat('D');
			return true;
		}
		else if (scale == 'K'){
			degrees = degrees - 273.15;
			scale = 'C';
			SetFormat('D');
			return true;
		}
		else
			return false;
	}
	else if (sc == 'F'){
		if (scale == 'C'){
			degrees = (degrees * (9/5)) + 32;
			scale = 'F';
			SetFormat('D');
			return true;
		}
		if (scale == 'K'){
			degrees = ((degrees - 273.15) * (9.0/5.0)) + 32;
			scale == 'F';
			SetFormat('D');
			return true;
		}
		else
			return false;
	}
	else if (sc == 'K'){
		if (scale == 'C'){
			degrees = (degrees + 273.15);
			scale = 'K';
			SetFormat('D');
			return true;
		}
		else if (scale == 'F'){
			degrees = (degrees - 32) * (5/9) + 273.15;
			scale = 'K';
			SetFormat('D');
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

int Temperature::Compare (const Temperature& d){						// Compares two different temperatures by deciding on a base scale, saving the temp
	double temp = degrees;												// in a temp variable, and then changing the current degrees/scale to the one passed through 
	char tscale = scale;												// then changing the current temperature back to its original values
	bool torf;
	
	if (d.scale == scale){
		if (degrees > d.degrees)
			return 1;
		else if (degrees == d.degrees)
			return 0;
		else if (degrees < d.degrees)
			return -1;
	}
	else if (d.scale == 'K' && scale != 'K'){
		torf = Convert('C');
		if (degrees > d.degrees)
			return 1;
		else if (degrees == d.degrees)
			return 0;
		else if (degrees < d.degrees)
			return -1;
	}
	else if (d.scale == 'F' && scale != 'F'){
		torf = Convert('F');
		if (degrees > d.degrees)
			return 1;
		else if (degrees == d.degrees)
			return 0;
		else if (degrees < d.degrees)
			return -1;
	}
	else if (d.scale == 'C' && scale != 'C'){
		torf = Convert('C');
		if (degrees > d.degrees)
			return 1;
		else if (degrees == d.degrees)
			return 0;
		else if (degrees < d.degrees)
			return -1;
	}
	else
		return 2;
	degrees = temp;
	//d.degrees = temp2;
	scale = tscale;
	//d.scale = tscale2;
}

bool Temperature::degCheck(double deg, char tscale) const{					// Checks to see if the degrees/scale sent in through the parameters are valid to be used
	
	tscale = toupper(tscale);
	
	if (tscale == 'C'){
		if (deg + 273.15 < 0){
			return false;
		}
		else
			return true;
	}
	else if (tscale == 'F'){
		if ((deg - 32) * (5.0/9.0) + 273.15 < 0){
			return false;
		}
		else
			return true;
	}
	else if (tscale == 'K'){
		if (deg >= 0)
			return true;
	}
	else
		return false;
}

void Temperature::setDefaults(){
	degrees = 0;
	scale = 'C';
}
