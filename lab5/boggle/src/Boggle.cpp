//TODO: Add const where appropriate

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
}

/*
 * During play, checks if a given set<string> word fits the length criteria
 */
bool Boggle::isLongEnough(string word){
    return (word.length() > 3); //returns true for words length 4 or greater
}

/*
 * During play, checks if a prefix exists in the given lexicon of words, and if the prefix is a word, add it to the found words
 */
bool Boggle::existsInLex(string prefix){
    Lexicon lex("EnglishWords.dat"); //initialization here a super bad thing?
    if (lex.contains(prefix)){
        wordsFoundOnBoard.insert(prefix); //will overwrite duplicate if any
    }
    return (lex.containsPrefix(prefix));
}

/*
 * For every member in board, if member is the start of the word we're looking for, perform recursion to see if it exists
 */
bool Boggle::findWord(string &word){
    string prefix = "";
    bool found = false;
    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col++){
            if (word[0] == board[row][col]){
				prefix.push_back(word[0]);
                found = playerRecursion(prefix, 1, row, col, word);
            }
        }
    }
    return found;
}

/*
 * Main recursion body, to be commented more toroughly
 */
bool Boggle::playerRecursion(string prefix, unsigned int index, int row_pos, int col_pos, string &word){
    for (int i = row_pos - 1; i < row_pos + 2; i++){
		for (int j = col_pos - 1; j < col_pos + 2; j++){
			//debug code
			//cout << "playerRecursion i: " << i << ", j:" << j << endl << "letter: " << word[index] << endl;
            if ((board.inBounds(i, j)) && (board[i][j] == word[index])){
                prefix.push_back(board[i][j]);
                if (existsInLex(prefix)){
                    index++;
					if (index == word.length()) return true;
                    return playerRecursion(prefix, index, i, j, word);
                }
                prefix.pop_back();
            }
        }
    }
    return false;
}

/*string Boggle::recursion(string prefix, int row_pos, int col_pos){
    for (int i = row_pos - 1; i < row_pos + 2; i++){
        for (int j = col_pos - 1; i < col_pos + 2; j++){
            if (board.inBounds(i, j)){
                prefix.append(board[i][j]);
                if (existsInLex(prefix)){
                    recursion(prefix, row, col);
                }
                prefix.pop_back();
            }
        }
    }
}*/
