/*  Kaedon Hamm
*   12/6/2018
*   Spell Checker using HashTables
*   Duan COP4530
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "hashtable.h"

using namespace cop4530;
using namespace std;


// extra functions
string newWords(string, HashTable<string>&);
string assembleWord(char [], int);
char alphabet(int);
void menu();


// main program
int main(int argc, char **argv){
// used when there are four command line parameters
if(argc == 4){
    HashTable<string> dict;
    // load in dictionary for spellchecking
    dict.load(argv[1]);
    fstream infile; ofstream outfile;
    infile.open(argv[2]); outfile.open(argv[3]);

    string currWord, currLine, ucurrWord, lcurrWord, origWord;
    vector<string> sentence;

    // get each line of the file to be parsed through
    while(getline(infile, currLine)){
        istringstream iss(currLine);
        // goes through the current line word by word
        while(iss >> currWord){
            // erases all punctuation in file and puts words into a vector
            currWord.erase(remove_if(currWord.begin(), currWord.end(), ::ispunct), currWord.end());
            sentence.push_back(currWord);
        }
        // will go through the vector of words one by one, looking for any misspells and offering to correct them
        for(auto i : sentence){
            origWord = i;

            // set upper and lowercase versions of the word
            transform(i.begin(), i.end(), i.begin(), ::toupper);
            ucurrWord = i;
            transform(i.begin(), i.end(), i.begin(), ::tolower);
            lcurrWord = i;

            if(!dict.contains(lcurrWord)){

                // replace the word in the sentence with upper case and print it out
                currLine.replace(currLine.find(origWord), origWord.length(), ucurrWord);
                cout << currLine << endl;
                cout << "============================================" << endl;
                // let user decide whether they want to use a new word or not
                //string s = newWords(lcurrWord, dict);
                currLine.replace(currLine.find(ucurrWord), ucurrWord.length(), newWords(lcurrWord, dict));

            }
        }
        outfile << currLine << endl;
        sentence.clear();
    }
    return 0;
}

// runs when there is only one command line parameter sent in
else if(argc == 1){
    int cap;
    cout << "Enter preferred hash table capacity: ";
    cin >> cap;
    string s;
    HashTable<string> dict(cap);
    char menuChoice;
    do{
        menu();
        cin >> menuChoice;
        switch(menuChoice){

// loads in a file to the hashtable
            case 'l': 
                cout << "Enter dictionary to load from: ";
                cin >> s;
                if(dict.load(s.c_str()))
                    cout << "Dictionary loaded successfully." << endl;
                break;

// Adds a word to the hashtable
            case 'a': 
                cout << "Enter word: ";
                cin >> s;
                if (!dict.contains(s)){
                    dict.insert(s);
                    cout << "Word " << s << " added." << endl;
                }
                else              
                    cout << "*****: Word already exists . Could not add." << endl;
                break;

// removes a word from the hashtable
            case 'r':
                cout << "Enter word: ";
                cin >> s;
                if(!dict.contains(s))
                    cout << "*****: Word not found. Could not delete." << endl;
                else{
                    dict.remove(s);
                    cout << "Word " << s << " deleted." << endl;
                }
                break;

// clears the hashtable
            case 'c':
                dict.clear();
                break;

// finds a word in the hashtable
            case 'f':
                cout << "Enter word: ";
                cin >> s;
                if(dict.contains(s))
                    cout << "Word " << s << " was found." << endl;
                else
                    cout << "Word " << s << " not found." << endl;
                break;

// dumps the hashtable onto the screen
            case 'd':
                dict.dump();
                break;

// prints the size of the hashtable
            case 's':
                cout << "Size of hashtable: " << dict.hashSize() << endl;
                break;

// writes the hashtable to a file that the user inputs
            case 'w':
                cout << "Enter dictionary file name to write to: ";
                cin >> s;
                dict.write_to_file(s.c_str());
                break;

// exits the program
            case 'x':
                return 0;



        }
    }while(menuChoice != 'x');
    return 0;
}
}

/******************

Helper Functions

******************/

// Goes through each word and changes the character to try all possibilities. Cross-references with dictionary.
string newWords(string misspell, HashTable<string>& d){
    vector<string> newWords;
    string choice;
    char var [misspell.length()];

    int parse = 0;
    for(auto& c : misspell){
        var[parse] = c;
        parse++;
    }


    for(int i = 0; i < misspell.length(); i++){
        char original = var[i];
        for(int j = 1 ; j <= 26; j++){
            var[i] = alphabet(j);
            string temp = assembleWord(var, misspell.length());
            if(d.contains(temp)){
                newWords.push_back(temp);
            }
            if(newWords.size() == 10)
                break;
        }
        var[i] = original;
        if(newWords.size() == 10)
            break;
    }
    
    int x = 0;
    for(auto i : newWords){
        cout << "(" << x << ") " << i << endl;
        x++;
    }
    cout << "Type 'n' to keep the word." << endl << "============================================" << endl;
    cin >> choice;
    if(choice != "n"){
        string s = newWords[stoi(choice)];
        newWords.clear();
        return s;
    }
    newWords.clear();
    return misspell;
}

// Assembles the char array into a single string to be compared to the dictionary
string assembleWord(char words[], int length){
    string temp;

    for(int i = 0; i < length; i++){
        
        temp = temp + words[i];
    }
    return temp;
}


// Returns letter of alphabet that is requested by number
char alphabet(int x){
    switch(x){
        case 1: return 'a';
        case 2: return 'b';
        case 3: return 'c';
        case 4: return 'd';
        case 5: return 'e';
        case 6: return 'f';
        case 7: return 'g';
        case 8: return 'h';
        case 9: return 'i';
        case 10: return 'j';
        case 11: return 'k';
        case 12: return 'l';
        case 13: return 'm';
        case 14: return 'n';
        case 15: return 'o';
        case 16: return 'p';
        case 17: return 'q';
        case 18: return 'r';
        case 19: return 's';
        case 20: return 't';
        case 21: return 'u';
        case 22: return 'v';
        case 23: return 'w';
        case 24: return 'x';
        case 25: return 'y';
        case 26: return 'z';
    }
}


void menu()
{
	cout << "\n\n";
	cout << "l - Load Dictionary From File" << endl;
	cout << "a - Add Word" << endl;
	cout << "r - Remove Word" << endl;
	cout << "c - Clear HashTable" << endl;
	cout << "f - Find Word" << endl;
	cout << "d - Dump HashTable" << endl;
	cout << "s - HashTable Size" << endl;
	cout << "w - Write to File" << endl;
	cout << "x - Exit program" << endl;
	cout << "\nEnter choice : ";
}
