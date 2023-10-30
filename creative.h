//Creative function removes all stop words from the index. It does this by looking through the stopwords.txt file which contains all stop words in English.
//It then creates a set of all stop words, after which it checks if the tag for the URL is in that set.
//If it is then it will not add it to the index. If the word is not in the set then it will add to the index.
//"stopfile.txt" is necessary for this creative function to work.

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

//Adds all stop words in the txt file into a set.
set<string> getStopWords() {
  set<string> allStopWords;
  ifstream file("stopwords.txt");
  string line;
  while(getline(file, line)){
    stringstream str(line);
    string word;
    while(str>>word){
      if(isalpha(word[0])){ //checks if the string is a number or a word
        allStopWords.insert(word); //adds all words to set.
      }
    }
  }
  return allStopWords;
}