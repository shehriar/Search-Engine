/*
Made by Shehriar Burney
Date: 10/02/2022
Description: The program will read a text to find the URL and tags associated with it. It will then work as a search engine
where user can input a string and the program will give the URLs associated with it.

Creative function was made using the stopwords.txt file and part of it will be found in the creative.h header file.
Please view those to understand the Creative function easier.
*/

#include <iostream>
#include "search.h"
using namespace std;

int main() {
    //milestone 1 tests:
    /*
        string str = cleanToken("!hello!");
        cout<<str<<endl;
        str = cleanToken("@I'm!");
        cout<<str<<endl;
        str = cleanToken("1233445677!^^%^$!##@");
        cout<<str<<endl;
    */

    //milestone 2 tests:
    /*
        set<string> result;
        result = gatherTokens("No !luke, I'm your father");
        for(auto& i:result){
            cout<<i<<endl;
        }

    *//*/////////////////

        set<string> result;
        result = gatherTokens("A!re!! you $$ready, kids? 1234 )(Aye), aye, Captain! I can't hear you! Aye, ][aye, Captain! //Oh!");
        for(auto& i:result){
            cout<<i<<endl;
        }

    */
    
    //milestone 3 tests
    /*
        map<string, set<string>> index;
        int val = buildIndex("tiny.txt", index);
        map<string, set<string>>::iterator itr;
        for(itr = index.begin(); itr!=index.end(); itr++){
            string url = itr->first;
            cout<<url<<endl;
            for(auto&i:itr->second){
                cout<<i<<" ";
            }
            cout<<endl;
        }
        cout<<"Num values: "<<val<<endl;

    *//*/////////////////

        map<string, set<string>> index;
        int val = buildIndex("cplusplus.txt", index);
        map<string, set<string>>::iterator itr;
        for(itr = index.begin(); itr!=index.end(); itr++){
            string url = itr->first;
            cout<<url<<endl;
            for(auto&i:itr->second){
                cout<<i<<" ";
            }
            cout<<endl;
        }
        cout<<"Num values: "<<val<<endl;
    */
   //milestone 4 tests
   /*
        map<string, set<string>> index;
        buildIndex("cplusplus.txt", index);
        map<string, set<string>>::iterator itr;
        set<string> result;
        result = findQueryMatches(index, "vector");
        for(auto& i:result){
            cout<<i<<endl;
        }
        cout<<endl;

    *//*/////////////////

        result.clear();
        result = findQueryMatches(index, "vector +container");
        for(auto& i:result){
            cout<<i<<endl;
        }
        cout<<endl;

    *//*/////////////////

        result.clear();
        result = findQueryMatches(index, "vector +container -pointer");
        for(auto& i:result){
            cout<<i<<endl;
        }
        cout<<endl;
    */

   //milestone 5 test
   /*
        searchEngine("cplusplus.txt");
        
    *//*/////////////////

        searchEngine("tiny.txt")
   */

    //creative milestone test
    /*
        creativeSearchEngine("cplusplus.txt");
    */
    // TODO:  Write this function.
    searchEngine("uiccs-news.txt");
}



