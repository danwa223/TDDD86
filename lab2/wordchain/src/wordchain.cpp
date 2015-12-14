#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <set>

using namespace std;

const string alphabet  = "abcdefghijklmnopqrstuvwxyz";

void welcomeMsg();
void processFile(vector<string> &wordList);
void wordChain(string &firstWord, string &lastWord, queue<stack<string> > &allPaths, stack<string> &currentPath, vector<string> &wordList);
bool searchWord(string &currentWord, vector<string> &wordList);
bool used(string &currentWord, set<string> &usedWords);
int comparator(string &currentWord, string &listItem);
void printShortestPath(stack<string> &currentPath, string &firstWord, string &lastWord);

int main(){
  welcomeMsg();
  string firstWord;
  string lastWord;
  cin >> firstWord;
  cin >> lastWord;
  queue<stack<string> > allPaths; //empty queue of stacks
  stack<string> currentPath;
  vector<string> wordList;
  processFile(wordList);
  currentPath.push(firstWord);
  allPaths.push(currentPath);
  wordChain(firstWord, lastWord, allPaths, currentPath, wordList);
  return 0;
}

void welcomeMsg(){
  //captain obvious
  cout << "Welcome to TDDD86 Word Chain." << endl;
  cout << "If you give me two English words, I will transform the" << endl;
  cout << "first into the second by changing one letter at a time." << endl;
  cout << endl;
  cout << "Please type two words: ";
}

void processFile(vector<string> &wordList){
  //reads file, saves every word in the wordList vector
  ifstream fileInput;
  string line;
  fileInput.open("../res/dictionary.txt");
  while (getline(fileInput, line)){
  wordList.push_back(line);
  }
  fileInput.close();
}

void wordChain(string &firstWord, string &lastWord, queue<stack<string> > &allPaths, stack<string> &currentPath, vector<string> &wordList){
  //actual brain of the code, does all logic
  int wordLength = firstWord.length();
  int TTL = 0;
  set<string> usedWords;
  usedWords.insert(firstWord);
  while (!allPaths.empty()){
    currentPath = allPaths.front(); //current working path
    allPaths.pop(); //deque current working path
    TTL++;
    if (currentPath.top() == lastWord){
      //shortest path has been found, print it
      printShortestPath(currentPath, firstWord, lastWord);
      cout << "Have a nice day." << endl;
      cout << "TTL: " << TTL << endl;
      break;
    }
    else{
      for (int i = 0; i < wordLength; ++i){
	//new copy of currentWord so that every letter can be tested separately
	string currentWord = currentPath.top();
	for (int j = 0; j < 26; ++j){
	  currentWord[i] = alphabet[j];
	  if (searchWord(currentWord, wordList)){ //maybe switch with below?
	    if (not (used(currentWord, usedWords))){ 
	      //word exists in dictionary and has not been used already
	      stack<string> backup = currentPath; //copy of current chain stack
	      usedWords.insert(currentWord);
	      backup.push(currentWord); //put neighbour word at the top of the copy stack
	      allPaths.push(backup); //add copy stack to the end of the queue
  	    }
    	  }
 	}
      }
    }
  }
}

bool used(string &currentWord, set<string> &usedWords){
  return usedWords.find(currentWord) != usedWords.end(); //log2 find speed
}

bool searchWord(string &currentWord, vector<string> &wordList){ //binary search
  /*dictionary has 267750 lines (words), is sorted.
    worst case search = log(2, 267750) = 18.03 -> 19 iterations
    this is inspired by the binary search from seminar shown 14/9,
    I had written my own before but this one is better.*/
  int lo = 0;
  int hi = wordList.size() - 1;
  while (lo <= hi){
    int mid = lo + (hi - lo) / 2;
    string listItem = wordList[mid]; //pivot element
    if (comparator(currentWord, listItem) == 0){
      return true;
    }
    if (comparator(currentWord, listItem) < 0){
      hi = mid - 1; //searched elem is earlier in the dict
    }
    else{
      lo = mid + 1; //searched elem is later in the dict
    }
  }
  return false;
}

int comparator(string &currentWord, string &listItem){
  return currentWord.compare(listItem); //returns an int
}

void printShortestPath(stack<string> &currentPath, string &firstWord, string &lastWord){
  //prints the stack, which happens to be the shortest path.
  cout << "Chain from " << lastWord << " back to " << firstWord << ":" << endl;
  while (!currentPath.empty()){
    cout << currentPath.top() << ' ';
    currentPath.pop();
  }
  cout << endl;
}
