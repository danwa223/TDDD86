#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <fstream> //fileInput
#include <sstream> //istringstream string >> int

using namespace std;

const string alphabet  = "abcdefghijklmnopqrstuvwxyz";

void processFile(vector<string> &wordList);
void getPreferences(int &wordLength, int &guesses, bool &displayWords);
void hangMan(vector<string> &wordList, int &wordLength, int &guesses, bool &displayWords);
void createGameList(vector<string> &wordList, int &wordLength, map<string, int> &wordFamilies);
void printGameStatus(map<string, int> &wordFamilies, int &wordLength, set<char> &alreadyGuessed, int &printedToken);
bool gameFinished(int &printedToken, int &wordLength);
bool used(char &currentChar, set<char> &alreadyGuessed);
bool checkIfInAlphabet(char &currentChar, const string &alphabet);
void createWordFamilies(char &currentChar, map<string, int> &wordFamilies, int &wordLength);
void getLargestFamily(map<string, int> &wordFamilies);

int main(){
  vector<string> wordList;
  set<string> startSet;
  int wordLength;
  int guesses;
  bool displayWords;
  char continuePlaying = 'y';
  processFile(wordList);
  cout << "Welcome to Hangman." << endl;
  while (continuePlaying == 'y'){
    //config first
    getPreferences(wordLength, guesses, displayWords);
    //Gameloop starts here
    hangMan(wordList, wordLength, guesses, displayWords);
    cout << endl;
    cout << "Continue playing (y/n)? ";
    cin >> continuePlaying;
  }
  return 0;
}

void processFile(vector<string> &wordList){
  //reads the dictionary into the wordList vector
  ifstream fileInput;
  string line;
  fileInput.open("../res/dictionary.txt");
  while (getline(fileInput, line)){
  wordList.push_back(line);
  }
  fileInput.close();
}

void getPreferences(int &wordLength, int &guesses, bool &displayWords){
  //handles all the inputs and configs
  char remainingWordsBool;
  cout << "Enter a valid number for your wordlength (1-29): ";
  cin >> wordLength;
  while ((wordLength < 1) or (wordLength > 29)){ //gotta change this later
    cout << "Enter a valid number for your wordlength (1-29): ";
    cin >> wordLength;
  }
  cout << "Enter how many guesses you want (1-26): ";
  cin >> guesses;
  guesses += 1;
  while (guesses < 1){ //could also restrict to <27 but not really needed...
    cout << "Enter how many guesses you want  (1-26): ";
    cin >> guesses;
    guesses += 1;
  }
  cout << "Do you want to see the remaining words in the wordlist (y/n)? ";
  cin >> remainingWordsBool;
  if (remainingWordsBool == 'y'){
    displayWords = true;
  }
  else{
    displayWords = false;
  }
}

void hangMan(vector<string> &wordList, int &wordLength, int &guesses, bool &displayWords){
  set<char> alreadyGuessed;
  map<string, int> wordFamilies;
  string inputChar;
  int printedToken = 0;
  int printedTokenOld;
  createGameList(wordList, wordLength, wordFamilies);
  //have to create a new start list every time we play new.
  while (true){
    //play the game
    if (displayWords){
      cout << "There are " << wordFamilies.size() << " possible words left." << endl;
    }
    printedTokenOld = printedToken; //keeps track of how many tokens we printed prev. iteration
    printGameStatus(wordFamilies, wordLength, alreadyGuessed, printedToken);
    if (printedToken == printedTokenOld){
      guesses--;
    }
    if (gameFinished(printedToken, wordLength)){ //game won
      cout << "Congratulations, you won!" << endl;
      break;
    }
    else if (guesses == 0){ //game over
      cout << "Sorry, no more guesses left. Better luck next time!" << endl;
      map<string, int>::iterator firstPair = wordFamilies.begin();
      cout << "The word I thought of was " << firstPair->first << " all the time!" << endl;
      break;
    }
    cout << "You have "<< guesses << " guesses left." << endl;
    cout << "Next guess: ";
    cin >> inputChar; //actually is string
    char currentChar = inputChar[0];
    while ((inputChar.length() != 1) or (!checkIfInAlphabet(currentChar, alphabet)) or (used(currentChar, alreadyGuessed))){ 
      //make sure user enters a single, valid, unused char (fuck you)
      if (!checkIfInAlphabet(currentChar, alphabet)){
	cout << "Do you seriously think " << currentChar << " is in the alphabet? ";
	cin >> inputChar;
      }
      else if (inputChar.length() != 1){
	cout << "A CHAR is only ONE letter, idiot: ";
	cin >> inputChar;
      }
      else{
	cout << "You already guessed " << currentChar << ". Guess something else: ";
	cin >> inputChar;
      }
      currentChar = inputChar[0];
    }
    //if we got this far then we got a valid input
    alreadyGuessed.insert(currentChar);
    createWordFamilies(currentChar, wordFamilies, wordLength);
    getLargestFamily(wordFamilies);
  }
}

void createGameList(vector<string> &wordList, int &wordLength, map<string, int> &wordFamilies){
  int listSize = wordList.size();
  //have to loop one single time over the entire wordlist, O(n)
  for (int i = 0; i < listSize; ++i){
    if (wordList[i].length() == wordLength){
      wordFamilies.insert(make_pair(wordList[i], 1)); //1 arbitrary number
    }
    //the idea behind the mapping is to tie a string to a family number
    //game starts with all words being mapped to the same family
  }
}

void printGameStatus(map<string, int> &wordFamilies, int &wordLength, set<char> &alreadyGuessed, int &printedToken){
  //compares current input char and checks it via the set, prints if exists
  map<string, int>::iterator firstPair = wordFamilies.begin();
  printedToken = 0;
  for (int i = 0; i < wordLength; ++i){
    string currentWord = firstPair->first;
    //we can take any arbitrary word that is remaining in our largest wordfamily
    if (used(currentWord[i], alreadyGuessed)){
      cout << currentWord[i];
      printedToken++;
    }
    else{
      cout << '-';
    }
  }
  cout << endl;
}

bool gameFinished(int &printedToken, int &wordLength){
  //if we printed a complete word then the game is over
  return (printedToken == wordLength);
}

bool used(char &currentChar, set<char> &alreadyGuessed){
  return alreadyGuessed.find(currentChar) != alreadyGuessed.end();
  //log(2, x) find speed
}

bool checkIfInAlphabet(char &currentChar, const string &alphabet){
  //will complain and return false for shit like åäö123
  int size = alphabet.size();
  for (int i = 0; i < size; ++i){
    if (currentChar == alphabet[i]){
      return true;
    }
  }
  return false;
}

void createWordFamilies(char &currentChar, map<string, int> &wordFamilies, int &wordLength){
  //does the entire legwork, maps new families depending on char input
  map<string, int>::iterator it;
  map<string, int> newFamilies;
  for(it = wordFamilies.begin(); it != wordFamilies.end(); ++it){
    //look up all mapped keys
    string newMappingStr;
    string currentWord = it->first;
    int newMapping;
    for (int i = 0; i < wordLength; ++i){
      if (currentWord[i] == currentChar){
	//user input char exists in the word we're looking up, create new data
	newMappingStr = newMappingStr + to_string(i+1);
	/*example: currentChar == 'e' and currentWord == "else" would yield
	  newMappingStr = "14"*/
      }
    }
    if (newMappingStr.empty()){
      //if no match of input char was found then store it in "no match" family
      newMappingStr = "0";
    }
    istringstream(newMappingStr) >> newMapping; //stores the string as an int
    newFamilies.insert(make_pair(currentWord, newMapping));
  }
  wordFamilies.clear();
  wordFamilies = newFamilies;
}

void getLargestFamily(map<string, int> &wordFamilies){
  //deletes all members of families that don't belong to the largest
  map<string, int>::iterator it, it2; //acts as my count(key)
  map<string, int> tempMap;
  set<int> testedMapVals;
  int largestMapVal = 0; //will be overwritten at first compare
  int largestFamily;
  for (it = wordFamilies.begin(); it != wordFamilies.end(); ++it){
    int currentSizeMapVal = 0;
    int tempMapVal = it->second; //can be 0,1,2... etc
    if (not (testedMapVals.find(tempMapVal) != testedMapVals.end())){
      //check if we tested the value already
      for (it2 = it; it2 != wordFamilies.end(); ++it2){
	//new value has been found, check all remaining map values for similar
	//should use O(n-k) time, where k is how far we progressed in the map
	if (it2->second == tempMapVal){
	  currentSizeMapVal++;
	}
      }
      if (currentSizeMapVal > largestMapVal){
	//creates a new largest family if found
	largestMapVal = currentSizeMapVal;
	largestFamily = tempMapVal;
      }
    }
    testedMapVals.insert(tempMapVal); //value has been tested
  }
  for (it = wordFamilies.begin(); it != wordFamilies.end(); ++it){
    if (it->second == largestFamily){
      tempMap.insert(make_pair(it->first, it->second));
      //was originally erasing depending on key, accidentally erased too much
      //better to just copy, clear old, then overwrite
    }
  }
  wordFamilies.clear();
  wordFamilies = tempMap;
}

//TODO: Logic is done. Game is done. Works perfectly (?).
//some small things that could improve code and functionality
//usage of multimap and count perhaps ?
