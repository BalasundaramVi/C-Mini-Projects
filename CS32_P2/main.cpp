//
//  main.cpp
//  Project 2
//
//  Created by Vignesh Balasundaram on 7/8/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

int readDictionary(istream &dictfile, string dict[]);
int recursivePermute(string word, const string dict[], int size, string results[]);
void recurPrint(const string results[], int size);
void StringtoChar(string word, string dict, char cword[], char cdict[]);
bool checkWordHelper(char word[], char dict[], int size);
bool checkWord(string word, string dict, int size);

//////////////////////////////////////////////////////////////////////////////////////////
// MAIN ROUTINE
int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    
    dictfile.open("/Users/VigneshB/Desktop/words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
    
    nwords = readDictionary(dictfile, dict);
    
    cout << "Please enter a string for an anagram: ";
    cin >> word;
    
    int numMatches = recursivePermute(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        recurPrint(results, numMatches);
}

/////////////////////////////////////////////////////////////////////////////////////////
// readDictionary
// gets the dictionary file and fills the array of strings

int readDictionary(istream &dictfile, string dict[])
{
    getline(dictfile, dict[0]);
    if (!dictfile)                                  //final case of recursion
    {
        return 0;
    }
    return readDictionary(dictfile, dict+1) + 1;    //calls recursive function and adds 1
}


/////////////////////////////////////////////////////////////////////////////////////////
// recursivePermute
// if a word in the dictionary is the same length as the test word, this function calls
// a check to see if the two words are a match. if the words match, the word is stored
// in results[].
int recursivePermute(string word, const string dict[], int size, string results[])
{
    if (word[0] == '\0')                            //failsafe
    {
        return 0;
    }
    if (size==0)                                    //failsafe
        return 0;
    
    unsigned long int wlength = word.size();
    
    if (dict[0].size() == wlength)                  //checks if dictionary word is same length as test word
    {
        if (checkWord(word, dict[0], wlength))      //calls checkWord function
        {
            results[0] = dict[0];                   //stores the word from dictionary into results
            return recursivePermute(word, dict+1, size-1, results+1) + 1;   //calls recursive function but adds 1
        }
        else
            return recursivePermute(word, dict+1, size-1, results);         //calls recursive function
    }
    else
        return recursivePermute(word, dict+1, size-1, results);             //calls recursive function
    
    return 0;                                                               //function should probably never reach here
}

/////////////////////////////////////////////////////////////////////////////////////////
// checkWord
// this function basically calls creates to arrays of characters, and then calls the two
// functions StringtoChar and checkWordHelper
bool checkWord(string word, string dict, int size)
{
    char a[size], b[size];
    StringtoChar(word, dict, a, b);                 //calls StringtoChar, which converts string to array of characters
    
    if (checkWordHelper(a, b, size))                //checks if the word is actually an anagram of the original word
        return true;
    else
        return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
// StringtoChar
// this function just takes two strings (word, and dictionary word (dict)) and converts
// them into arrays of characters
void StringtoChar(string word, string dict, char cword[], char cdict[])
{
    if (word[0] == '\0')                            //failsafe
    {
        return;
    }
    
    cword[0] = tolower(word[0]);                    //converts all letters to lower case
    cdict[0] = tolower(dict[0]);                    //converts all letters to lower case
    
    
    StringtoChar(word.substr(1,word.size()-1), dict.substr(1,dict.size()-1), cword+1, cdict+1);
    // recursive function until all characters are finished

    unsigned long int size = word.size();           //sorts both arrays into alphabetical order
    sort(cword, cword+size);
    sort(cdict, cdict+size);
}
/////////////////////////////////////////////////////////////////////////////////////////
// checkWordHelper
// since the array has been sorted alphabetically, this function just goes character by
// character and makes sure every character matches to prove that the word is an anagram
bool checkWordHelper(char word[], char dict[], int size)
{
    if (size==0)                                    //failsafe
        return true;
    if (word[0] == '\0' && dict[0] == '\0')         //failsafe
        return true;
    if ((word[0] != '\0' && dict[0] == '\0')
        || (word[0] == '\0' && dict[0] != '\0'))    //failsafe
        return false;
    
    if (word[0]==dict[0])
    {
        if (checkWordHelper(word+1, dict+1, size-1))    //recursive checks every character
        {
        return true;
        }
    }
    
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
// recurPrint
// prints the results
void recurPrint(const string results[], int size)
{
    if (size==0)                                //failsafe
        return;
    if (results[0] == "")                       //failsafe
        return;
    
    cout << results[0] << endl;                 //outputs word
    recurPrint(results+1, size-1);              //recursively goes through entire array
}


