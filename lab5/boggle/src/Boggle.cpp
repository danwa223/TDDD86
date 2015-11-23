#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include "Boggle.h"
#include "shuffle.h"
#include "strlib.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = { // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

/*
 * Default constructor for a board given the cubes in CUBES.
 */
Boggle::Boggle(){
    board.resize(4, 4); //init the board, discard garbage values
    int currentDice = 0;
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            int diceSideUp = randomInteger(0, CUBE_SIDES - 1);
            board[i][j] = CUBES[currentDice][diceSideUp]; //converts a random member of every cube to a char on the board
            currentDice++;
        }
    }
}
/*
 * Overwrite the board, takes a custom string and uses the 16 first characters
 */
void Boggle::boardOverwrite(string customGame){
    int index = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            char c = customGame[index];
			c = toupper(c); //capitalizes current char
            board[i][j] = c; //puts char on the board
            index++;
        }
    }
}

/*
 * Getter for the console output in boggleplay.cpp
 */
Grid<char> Boggle::getBoard(){
    return board;
}

/*
 * Getter for the console output in boggleplay.cpp
 */
set<string> Boggle::getUsedWords(){
    return usedWords;
}

/*
 * Getter for the console output in boggleplay.cpp
 */
set<string> Boggle::getCompUsedWords(){
	return compUsedWords;
}

/*
 * Calls the randomization in shuffle.h using the Grid template (board is a grid)
 */
void Boggle::shuffleCubes(){
    shuffle(board);
}

/*
 * Calculate the score based on number and length of the words in a set
 */
int Boggle::calcScore(string who) {
	int score = 0;
	string str;

	set<string>::iterator it;
	if (who == "p") {    //Calculate the users score
		for(it = usedWords.begin(); it != usedWords.end(); ++it){
			str = *it;
			if (str.length() >= 4) {
				score += str.length() - 3;
			}
		}
	} else if (who == "c") {    //Calculate the computers score
		for(it = compUsedWords.begin(); it != compUsedWords.end(); ++it){
			str = *it;
			if (str.length() >= 4) {
				score += str.length() - 3;
			}
		}
	}
	return score;
}

/*
 * During play, checks if a given word has already been played
 */
bool Boggle::hasBeenUsed(string word){
    bool wordFound = usedWords.find(word) != usedWords.end(); //true if word has already been used
    if (not (wordFound)){
        usedWords.insert(word); //doing this here keeps the logic in Boggle.cpp and lets boggleplay.cpp not worry about it
	}
    return wordFound;
}

/*
 * Emptying the set of used words
 */
void Boggle::clearUsedWords() {
	usedWords.clear();
	compUsedWords.clear();
}

/*
 * During play, checks if a given set<string> word fits the length criteria
 * Not currently in use as we allow the player to enter shorter wordss
 */
bool Boggle::isLongEnough(string word){
    return (word.length() > 3); //returns true for words length 4 or greater
}

/*
 * During play, checks if a prefix exists in the given lexicon of words, and if the prefix is a word, add it to the found words
 */
bool Boggle::existsInLex(string prefix){
	return lex.containsPrefix(prefix);
}

/*
 * Helper for recursive function calls, resets the visited board.
 */
void Boggle::searchInit(){
    visited.resize(4,4);

    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            visited[i][j] = false;
        }
    }
}

/*
 * Help function to get the player recursion going
 */
bool Boggle::findWord(string &word){

    searchInit();
    string prefix = "";
	found = false;

    //uppercase all characters in a word
    for (unsigned int letter = 0; letter < word.length(); letter++) {
        word[letter] = toupper(word[letter]);
    }

    //iterate over the board, start recursion on unvisited positions in bounds that start with the correct letter
    for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			if (board[row][col] == word[0]) {
				playerRecursion(prefix, row, col, word);
				if (found) return true;
			}
        }
    }
    return false;
}

/*
 * Main recursion for confirming that the player entered a correct word
 */
void Boggle::playerRecursion(string prefix, int row, int col, string &word) {

    //if we're not inbounds or already visited the spot we're looking at in the current recursion loop simply return, prevents endless loop
    if ((!board.inBounds(row, col)) || (visited[row][col]) ) return;

    //update relevant variables
    keepLooking = true;
    visited[row][col] = true;
    prefix.push_back(board[row][col]);
	//cout << prefix << endl;            //debug

	//this will be called if the last letter of the prefix is actually found on the board
    if (prefix == word){
		found = true;      // bool found is declared in header and used for simplicity in boggleplay.cpp
        return;
    }

    //if we have looped to an incorrect prefix, stop looking deeper
    for (unsigned int i = 0; i < prefix.length(); i++){
        if(prefix[i] != word[i]){
			keepLooking = false;   // bool keepLooking is declared in header
        }
    }
    //if we are working with a prefix that doesn't exist, return
    if (!lex.containsPrefix(word)) return;

    // if the prefix exists but word is not completed, keep checking, make sure that we "unvisited" a certain spot or it will block us later
    if (keepLooking) {
        playerRecursion(prefix, row - 1, col, word); //N
        playerRecursion(prefix, row, col + 1, word); //E
        playerRecursion(prefix, row + 1, col, word); //S
        playerRecursion(prefix, row, col - 1, word); //W
        playerRecursion(prefix, row - 1, col + 1, word); //NE
        playerRecursion(prefix, row + 1, col + 1, word); //SE
        playerRecursion(prefix, row + 1, col - 1, word); //SW
        playerRecursion(prefix, row - 1, col - 1, word); //NW
        visited[row][col] = false;
    }else{
        visited[row][col] = false;
        return;
    }
}

/*
 * Help function to get the CPU recursion going
 */
void Boggle::findWords(){
    searchInit();
    string prefix = "";

    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col++){
            computerRecursion(prefix, row, col);
        }
    }
}

/*
 * Main recursion for finding all remaining words on the board
 */
void Boggle::computerRecursion(string prefix, int row, int col){

	// if we're not inbounds or already visited the spot we're looking at in the current recursion loop simply return, prevents endless loop
    if ((!board.inBounds(row, col)) || (visited[row][col]) ) return;

	// update relevant variables
    visited[row][col] = true;
    prefix.push_back(board[row][col]);

	// words of 3 chars or less don't give score, discard them
	// found words added to the list of words found by the CPU
	if (lex.contains(prefix) && prefix.size() > 3){
        addCompWord(prefix);
    }

    if (lex.containsPrefix(prefix)){
        computerRecursion(prefix, row - 1, col); //N
        computerRecursion(prefix, row, col + 1); //E
        computerRecursion(prefix, row + 1, col); //S
        computerRecursion(prefix, row, col - 1); //W
        computerRecursion(prefix, row - 1, col + 1); //NE
        computerRecursion(prefix, row + 1, col + 1); //SE
        computerRecursion(prefix, row + 1, col - 1); //SW
        computerRecursion(prefix, row - 1, col - 1); //NW
        visited[row][col] = false;
    }else{
        visited[row][col] = false;
        return;
    }
}

/*
 * Add only words not found by the player to the CPUs words
 */
void Boggle::addCompWord(string word){
	if(usedWords.find(word) == usedWords.end()) {
		compUsedWords.insert(word);
	}
}
