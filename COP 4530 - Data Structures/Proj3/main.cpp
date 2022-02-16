/*  Kaedon Hamm
*   10.25.2018
*   COP 4530
*   Project 3 - Queue and BFS
*   This project calculates the shortest route between two cities based upon an unweighted graph. Prints out total price at the end.
*
*	NOTE: When choosing "y" to calculate another route, press enter twice.
*/


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Queue.h"

using namespace std;
using namespace cop4530;

// Cleaner-Code functions
void BFS(Queue<int>&, vector<int>&, vector<bool>&, int *prices, int);
void turnTrue(vector<bool>&, int);
void addPrevCity(vector<int>&, int, int);
void visitedToFalse(vector<bool>&);
int cityToNum(vector<string>&, string);
string numToCity(vector<string>&, int);
vector<string> tracebackRoute(vector<int>&, vector<string>&, int, int);
void falseVisited(vector<bool>&);
int calcPrice(vector<int>&, int *prices, int, int);


// Fill functions
void fillVisited(vector<bool>&, int);
void fillCities(ifstream&, vector<string>&, int);
void fillPrevCities(vector<int>&, int);

// Print fucntions
void printPrices(int *prices, int s);
void printCit(vector<int>&, vector<string>&);
template <typename T>
void printVec(vector<T>);
void printFinal(vector<string>&, int);


// Main Program
int main(){

	// ************* Initialzing Variables *************
	ifstream fromfile;
	
	Queue<int> q;					// will hold current possible cities to be checked out
	vector<string> cities;			// list of all cities from file
	vector<int> prevCity;			// records previous city in reference to the visited cities
	vector<bool> visited;			// visited cities will have T. Should start with all false.

	int cityHold, startLocation, endLocation, price;
	string startCity, endCity;
	char answer;		
	bool startGood = false; bool endGood = false;



	// ****************** Opening File *****************
	fromfile.open("proj3.input");	// opens file
	
	if(!fromfile){					// making sure file is there
		cout << "Unable to open file proj3.input" << endl;
		exit(0);
	}



	// ************* Filling important containers **************


	fromfile >> cityHold;								// reads in amount of cities/lines to read in
	const int numberOfCities = cityHold;
	fillCities(fromfile, cities, numberOfCities);
	fillVisited(visited, numberOfCities);
	fillPrevCities(prevCity, numberOfCities);
	int prices[numberOfCities][numberOfCities];			// creates matrix of cities

	for (int i = 0; i < numberOfCities; i++){			// fills matrix of ciites
		for(int j = 0; j < numberOfCities; j++){
			fromfile >> prices[i][j];
		}
	}


	do{
	cout << "List of Cities and their flights:";
	cout << "\n**********************************\n";

	for (int i = 0; i < numberOfCities; i++){
		cout << cities[i] << endl;
		for(int j = 0; j < numberOfCities; j++){
			if(prices[i][j] > 0)
			cout << "- " << cities[j] << " $" << prices[i][j] << endl;
		}
	}
    cout << endl;

	// ************** Start of User input/loop ******************
		do{
			cout << "Please choose a starting destination and ending destination from this list:" << endl;
			cout << "Starting Destination: ";
			getline(cin, startCity);
			cout << endl;
			cout << "Ending Destination: ";
			getline(cin, endCity);
			cout << endl;

			for(int i = 0; i < cities.size(); i++){
				if(startCity == cities[i])
					startGood = true;
				if(endCity == cities[i])
					endGood = true;
			}
		}while(startGood != true || endGood != true);


	startLocation = cityToNum(cities, startCity);
	endLocation = cityToNum(cities, endCity);

	q.push(startLocation);
	BFS(q, prevCity, visited, (int *)prices, endLocation);									// finds shortest path
	while(!q.empty())
		q.pop();

    // calculates price
    price = 0;
	int tempStart = startLocation, tempEnd = endLocation;

	while(tempEnd != tempStart){
        price += (prices[tempEnd][prevCity[tempEnd]]);
		tempEnd = prevCity[tempEnd];
	}



	vector<string> results = tracebackRoute(prevCity, cities, startLocation, endLocation);	// creates vector of results, backtracking through the prevCity vector
	reverse(results.begin(), results.end());
	printFinal(results, price);
    cout << endl;


	visited.clear(); fillVisited(visited, numberOfCities);
	prevCity.clear(); fillPrevCities(prevCity, numberOfCities);

	startGood = endGood = false;

	cout << "Would you like to find another path? (y/n): ";
	cin >> answer;
	cin.ignore(1000, '\n');
	cout << endl;



	}while(answer == 'y' || answer =='Y');


	fromfile.close();
	return 0;
}




// ******************************** Functions ****************************
// Cleaner-Code fucntions
//				Loc Queue		Previous Cities			T/F Visited?		Prices Matrix
void BFS(Queue<int>& q, vector<int>& prevCity, vector<bool>& visited, int *prices, int endLoc){
	int qLoc = q.front();
	int nextLoc = qLoc;
	int tempSize = visited.size();

	turnTrue(visited, qLoc);
	addPrevCity(prevCity, qLoc, qLoc);
	while (nextLoc != endLoc){
		for(int i = 0; i < tempSize; i++){
			if(prices[qLoc*tempSize+i] > 0){
				if (visited[i] == false){
					q.push(i);
					turnTrue(visited, i);
					addPrevCity(prevCity, i, qLoc);
				}
				if(i == endLoc){
					nextLoc = i;
					break;
				}
			}
		}
		q.pop();
		qLoc = q.front();
	}
}

// tells program that visited elements have been visited
void turnTrue(vector<bool>& visited, int loc){
	visited[loc] = true;
}

// hold elements of what city you came from
void addPrevCity(vector<int>& prevCity, int loc, int city){
	prevCity[loc] = city;
}

// resets visited array to false
void visitedToFalse(vector<bool>& q){
	for(int i = 0; i < q.size(); i++)
		q[i] = false;
}

// takes in a city and outputs its number equivalent (based on a sized vector)
int cityToNum(vector<string>& cities, string city){
	for(int i = 0; i < cities.size(); i++){
		if(cities[i] == city)
			return i;
	}
}

// takes in a number and outputs its city equivalent (based on a sized vector)
string numToCity(vector<string>& cities, int loc){
	return cities[loc];
}

// fills in calculated city 'hops'
vector<string> tracebackRoute(vector<int>& prevCity, vector<string>& cities, int startLoc, int endLoc){
	vector<string> x;
	while(endLoc != startLoc){
		x.push_back(numToCity(cities, endLoc));
		endLoc = prevCity[endLoc];
	}
	x.push_back(numToCity(cities, startLoc));
	return x;
}


void falseVisited(vector<bool>& visited){
	for(int i = 0; i < visited.size(); i++)
		visited[i] = false;
}


// *************** Fill Functions *****************
void fillVisited(vector<bool>& visited, int s){
	for(int i = 0; i < s; i++)
		visited.push_back(false);
}


void fillCities(ifstream& in, vector<string>& cities, int s){
	string throwout, temp;
	getline(in, throwout);
	for(int i = 0; i < s; i++){
		getline(in, temp);
		cities.push_back(temp);
	}
	cout << endl;
}

void fillPrevCities(vector<int>& prevCity, int s){
	for(int i = 0; i < s; i++)
		prevCity.push_back(5);
}



// *************** Print Functions *****************
template <typename T>
void printVec(vector<T> q){
	for(int i = 0; i < q.size()-1; i++)
		cout << q[i]  << ", ";
	cout << q[q.size()-1];
	cout << endl;
}

void printFinal(vector<string>& q, int price){
	for(int i = 0; i < q.size()-1; i++)
		cout << q[i]  << " -> ";
	cout << q[q.size()-1] << " $" << price;
	cout << endl;
}


void printCit(vector<int> x, vector<string> cities){
	for (int i = 0; i < x.size(); i++){
		cout << cities[x[i]] <<  " ";
	}
	cout << endl;
}

void printPrices(int *prices, int s){
	for(int i = 0; i < s; i++){
		for(int j = 0; j < s; j++){
			cout << prices[i*s+j] << " ";
		}
		cout << endl;
	}
}
