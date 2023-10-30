
#pragma once

#include <iostream>
#include <set>
#include <map>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <sstream>

//#include "creative.h"  //un-comment this and last two functions when testing creative function

using namespace std;
/*
Creative function was made using the stopwords.txt file and part of it will be found in the creative.h header file.
Please view those to understand the Creative function easier.
*/

//function takes in a string and removes all punctuation at the start and end of the string. It returns the clean string
string cleanToken(string s) {
    string word = s;
    string result = "";
    bool alpha = false;
    //loops and removes the first letter until the first letter is not a punctuation
    while(ispunct(word[0])){ 
        word.erase(word.begin());
    }
    int size = word.size();
    for(int i = size-1; i>=0; i--){
        // loops and removes the last letter until the last letter is not a punctuation
        if(ispunct(word[i])){ 
            word.erase(word.begin()+i);
        }
        else{
            break;
        }
    }
    // checks if there is a letter in the string
    for(auto&i:word){ 
        if(isalpha(i)){
            alpha = true;
        }
    }

    for(auto &ch:word){
        result+=tolower(ch);
    }

    if(!alpha){
        return "";
    }
    return result;  // TODO:  update this.
}

//function takes in a line of string and cleans each word of the string and adds it to a set, which it will return.
set<string> gatherTokens(string text) {
    set<string> tokens;
    stringstream str(text);
    set<string> setstr;
    string word;
    while(str>>word){
        tokens.insert(cleanToken(word));
    }
    tokens.erase(""); //removes any empty item in set.
    return tokens;
}

//Builds the map Index and returns the number of URLs in the text file
int buildIndex(string filename, map<string, set<string>>& index) {
    fstream file;
    file.open(filename,ios::in);
    string line, url;
    set<string> tempCleanSet;
    set<string> cleanSet;
    int numURls = 0;
    if(file.is_open()){ // opens the file
        while(getline(file, line)){ // first line is always URL
            url = line;
            getline(file, line); // second line is always tags associated with URL
            tempCleanSet = gatherTokens(line);
            for(auto &it:tempCleanSet){
                index[it].insert(url);
            }
            tempCleanSet.clear();
            numURls++;
        }
    }
    else{
        return 0;
    }
    
    // TODO:  Write this function.*/
    return numURls;
}

//Finds the query user inputted when there is a '+' sign.
void findqueryAND(map<string, set<string>>&index, string targetword, set<string> &result){
    set<string> tempAndSet, andSet;
    map<string, set<string>>::iterator it;
    for(it = index.begin(); it!=index.end(); it++){
        set<string> url = it->second;
        string words = it->first;
        if(it->first == targetword){
            for(auto&i:it->second){
                tempAndSet.insert(i); //adds all URLs associated with the targetword to tempAndSet
            }
        }
    }
    //finds the intersection between result set and tempAndSet, then assigning this new set to andSet.
    set_intersection(result.begin(), result.end(), tempAndSet.begin(), tempAndSet.end(), inserter(andSet, andSet.begin()));
    result = andSet;
}

//Finds the query user inputted when there is a '-' sign.
void findqueryNOT(map<string, set<string>>&index, string targetword, set<string> &result){
    set<string> tempNotSet, notSet;
    map<string, set<string>>::iterator it;
    for(it = index.begin(); it!=index.end(); it++){
        set<string> url = it->second;
        string words = it->first;
        if(it->first == targetword){
            for(auto&i:it->second){
                tempNotSet.insert(i);
            }
        }
    }
    set_difference(result.begin(), result.end(), tempNotSet.begin(), tempNotSet.end(), inserter(notSet, notSet.begin()));
    result = notSet;
}

//Finds the query user inputted when there is a space infront of word.
void findQueryOR(map<string, set<string>>&index, string targetword, set<string> &result){
    map<string, set<string>>::iterator it;
    for(it = index.begin(); it!=index.end(); it++){
        set<string> url = it->second;
        string words = it->first;
        if(it->first == targetword){
            for(auto&i:it->second){
                result.insert(i);
            }
        }
    }
}

//Checks the sign of the word and calls the function depending on the sign to search for the URLs. Returns all the URLs it found matches for.
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    stringstream str(sentence);
    string word = "";
    while(str>>word){
        if(word[0] == '+'){
            word.erase(word.begin());
            findqueryAND(index, word, result);
        }
        else if(word[0] == '-'){
            word.erase(word.begin());
            findqueryNOT(index, word, result);
        }
        else {
            findQueryOR(index, word, result);
        }
        word = "";  
    }
    return result;
}

//Main function of the program, it runs the whole code and prints all information.
void searchEngine(string filename) {
    cout<<"Stand by while building index..."<<endl;
    map<string, set<string>> index;
    int numKeys = buildIndex(filename, index);
    set<string> URLset;
    map<string, set<string>>::iterator it;

    cout<<"Indexed "<<numKeys<<" pages containing "<<index.size()<<" unique terms"<<endl;
    cout<<"Enter query sentence (press enter to quit): ";
    string sentence;
    getline(cin, sentence);
    if(sentence == ""){
        cout<<"Thank you for searching!";
        exit(0);
    }
    while(sentence!="\n"){
        set<string> result;
        result = findQueryMatches(index, sentence);
        cout<<"Found "<<result.size()<<" matching pages"<<endl;
        for(auto& i:result){
            cout<<i<<endl;
        }
        cout<<"Enter query sentence (press enter to quit): ";
        getline(cin, sentence);
        if(sentence == ""){
            cout<<"Thank you for searching!";
            exit(0);
        }
    }
}

//Uncomment these functions when testing creative function
/*
//Builds map which does not have stop words in and returns the number of URLs.
int buildCreativeIndex(string filename, map<string, set<string>>& index){
    fstream file;
    file.open(filename,ios::in);
    set<string> allStopWords = getStopWords();
    string line, url;
    set<string> tempCleanSet;
    set<string> temp2CleanSet;
    set<string> cleanSet;
    int numURls = 0;
    if(file.is_open())
    {
        while(getline(file, line)){
            url = line;
            getline(file, line);
            tempCleanSet = gatherTokens(line);
            set<string>urlSet;
            for(auto &it:tempCleanSet){
                if(!allStopWords.count(it)){ //checks if the word is not in the allStopWords set
                    index[it].insert(url);
                }
            }
            tempCleanSet.clear();
            numURls++;
        }
    }
    else
    {
        return 0;
    }
    
    // TODO:  Write this function.
    return numURls;
}

//Runs the creative function
void creativeSearchEngine(string filename){
    cout<<"Stand by while building index..."<<endl;
    map<string, set<string>> index;
    int numKeys = buildCreativeIndex(filename, index);
    set<string> numValues;
    map<string, set<string>>::iterator it;
    for(it = index.begin(); it!=index.end(); it++){
        for(auto&i:it->second){
            numValues.insert(i);
        }
    }
    cout<<"Indexed "<<numKeys<<" pages containing "<<index.size()<<" unique terms"<<endl;
    cout<<"Enter query sentence (press enter to quit): ";
    string sentence;
    cin.ignore();
    getline(cin, sentence, '\n');
    if(sentence == ""){
        cout<<"Thank you for searching!";
        exit(0);
    }
    while(sentence!="\n"){
        set<string> result;
        result = findQueryMatches(index, sentence);
        cout<<"Found "<<result.size()<<" matching pages"<<endl;
        for(auto& i:result){
            cout<<i<<endl;
        }
        cout<<"Enter query sentence (press enter to quit): ";
        getline(cin, sentence, '\n');
        if(sentence == ""){
            cout<<"Thank you for searching!";
            exit(0);
        }
    }
}
*/