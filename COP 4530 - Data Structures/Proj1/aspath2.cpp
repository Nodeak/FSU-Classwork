/*
	Kaedon Hamm
	COP 4530
	9.20.2018
	
	This program reads BGP data, finds the ASPATHS, and presents all its naighbors.

*/


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <sstream>


using namespace std;

struct list{
	int aspath;
	set<int> neighbors;
};



void newAspath(vector<list>& listList, list& aspath);
void newNeighbor(list& currEntry, int newNeigh);
void bubblesort(vector<list>& vec);


int main(){

    list currList;
    string row;
    string fullText;
    vector<int> tempIntVec;
    vector<list> pathList;
    ifstream infile;
    ofstream outfile;
    ofstream tempfile;

    outfile.open("results.txt");
    if(!outfile){ 
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }

	infile.open("ribSMALL.txt");
	
	if(!infile){
		cout << "Unable to open file tenlines.txt" << endl;
		exit(0);
	}




	
    set<int> temp;
    while(!infile.eof()){ 

        for(int i = 0; i < 6; i++){
            infile.ignore(256, '|');		
        }

        getline (infile, row, '|');
        infile.ignore(256, '\n');

        for(int i = 0; i < row.size(); i++){
            string single = "";
            while(row[i] != ' ' && row[i] != '\n' && i < row.size()){
                single += row[i];
                i++;
            }
            temp.insert(stoi(single));
        }

        fullText += row + "\n";
    }

    

    tempIntVec.assign(temp.begin(), temp.end());

    for(int i = 0; i < tempIntVec.size(); i++){
        currList.aspath = tempIntVec[i];
        newAspath(pathList, currList);
    }
    

    string rNeighbor;
    string lNeighbor;
    string cPath;

    istringstream iss(fullText);
    while(iss >> rNeighbor){
        if(rNeighbor == "\n"){
            for(int i = 0; i < pathList.size(); i++){
                if(pathList[i].aspath == stoi(cPath)){
                    newNeighbor(pathList[i], stoi(lNeighbor));
                }
            }
        }
        else{
        cPath = rNeighbor;
        for(int i = 0; i < pathList.size(); i++){
            if(pathList[i].aspath == stoi(cPath)){
                iss >> rNeighbor;
                newNeighbor(pathList[i], stoi(rNeighbor));
                lNeighbor = cPath;
                cPath = rNeighbor;
                newNeighbor(pathList[i], stoi(lNeighbor));
            }
            
        }
        }
    }

    bubblesort(pathList);


    for(int i = 0; i < pathList.size(); i++){
        cout << pathList[i].aspath << " ";
        vector<int> veryTemp;
        veryTemp.assign(pathList[i].neighbors.begin(), pathList[i].neighbors.end());
        cout << veryTemp.size() << " ";
        for(int j = 0; j < veryTemp.size(); j++){
            cout << veryTemp[j] << "|";
        }
        cout << endl;
    }



	return 0;
}

void newAspath(vector<list>& listList, list& aspath){
	listList.push_back(aspath);
}

void newNeighbor(list& currEntry, int newNeigh){
	currEntry.neighbors.insert(newNeigh);
}

void bubblesort(vector<list>& vec){

    for(int i = 0; i < vec.size();i++)
		for(int j = i+1; j < vec.size(); j++)
		{
				if(vec[i].neighbors.size() < vec[j].neighbors.size())
					swap(vec[i],vec[j]);
                else if(vec[i].neighbors.size() == vec[j].neighbors.size()){
                    if(vec[i].aspath < vec[j].aspath)
                        swap(vec[i],vec[j]);
			}
		}
}