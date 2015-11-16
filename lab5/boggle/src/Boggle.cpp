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
    Lexicon lex("EnglishWords.dat"); //initialization here a super bad thing? Could not do in .h file
    if (lex.contains(prefix)){
        wordsFoundOnBoard.insert(prefix); //will overwrite duplicate if any, used by both recursive searches but perhaps not needed for player
    }
    return true;
    //return (lex.containsPrefix(prefix));
}

/*
 * For every member in board, if member is the start of the word we're looking for, perform recursion to see if it exists
 */
bool Boggle::findWord(string &word){

    string prefix = "";

    //uppercase all characters
    for (unsigned int letter = 0; letter < word.length(); letter++){
        word[letter] = toupper(word[letter]);
    }

    bool found = false;
    for (int row = 0; row < 4; row++){ //first iteration, check if word start is in board
        for (int col = 0; col < 4; col++){
            if ((board[row][col] == word[0]) && (not (found))){
                prefix.push_back(word[0]);
                //found = playerRecursion(prefix, 2, row, col, word, found);
                for (int i = row - 1; i < row + 2; i++){ //second iteration, check for all neighbours of first word
                    for (int j = col - 1; j < col + 2; j++){
                        //if (board.inBounds(i,j)) cout << board[i][j];
                        //debug
                        if (board.inBounds(i, j) && (board[i][j] == (word[1]))){ //if correct neighbour found, recursive loop the rest
                            prefix.push_back(word[1]);
                            found = playerRecursion(prefix, 2, i, j, word, found);
                            prefix.pop_back();
                            cout << "Prefix is right now: " << prefix << endl;
                        }
                    }
                }
            }
        }
    }
    return found;
}

// && (not (found))
//fycliomgorilhjhu //problem from letter 2 to 3. Problem words: Coil, Foil, Roil, Moil
//FYCL
//IOMG
//ORIL
//HJHU

//leartdpalaiejegr  //solved
//LEAR
//TDPA
//LAIE
//JEGR

/*
 * Recursive search for the player. Will not look up every word on the table, will only look for the word the player gives as an argument
 */
bool Boggle::playerRecursion(string prefix, unsigned int index, int row_pos, int col_pos, string &word, bool &found){
    for (int i = row_pos - 1; i < row_pos + 2; i++){
        for (int j = col_pos - 1; j < col_pos + 2; j++){
			//debug code
            cout << "playerRecursion i: " << i << ", j:" << j << endl << "letter: " << word[index] << endl;
            if ((board.inBounds(i, j)) && (board[i][j] == word[index]) && (not ((i == row_pos) && (j == col_pos))) && (not (found))){ //found a neighbour that has the next letter we are looking for
                prefix.push_back(board[i][j]); //"concatenate" the letter to the prefix string
                if (existsInLex(prefix)){ //check if prefix is legit so that the player can't cheat
                    index++;
                    cout << "Index is: " << index << endl;
                    if (index == word.length()){
                        cout << "Returning true here!" << endl;
                        found = true;
                        return found; //got the word. Return to previous level, where the loop finishes and then the found-bool blocks further looping.
                    }
                    return playerRecursion(prefix, index, i, j, word, found);
                }
            }
        }
    }
    return found;
}

/*
 * Computer version of find word
 */
void Boggle::findWords(){
    string prefix = "";
    for (int row = 0; row < 4; row++){ //first iteration, check if word start is in board
        for (int col = 0; col < 4; col++){
            char c = board[row][col];
            prefix.push_back(c);
            for (int i = row - 1; i < row + 2; i++){ //second iteration, check for all neighbours of first word
                for (int j = col - 1; j < col + 2; j++){
                    if (board.inBounds(i, j)){ //for every neighbour found, recursive loop the rest
                        prefix.push_back(c);
                        computerRecursion(prefix, i, j);
                        prefix.pop_back();
                    }
                }
            }
            prefix.pop_back();
        }
    }
}

void Boggle::computerRecursion(string prefix, int row_pos, int col_pos){
    for (int i = row_pos - 1; i < row_pos + 2; i++){
        for (int j = col_pos - 1; j < col_pos + 2; j++){
            if ((board.inBounds(i, j)) && ((i != row_pos) || (j != col_pos))){ //found a valid neighbour
                prefix.push_back(board[i][j]); //"concatenate" the letter to the prefix string
                if (!(usedWords.find(prefix) != usedWords.end()) && existsInLex(prefix) && isLongEnough(prefix)){ //check if prefix is legit so that the computer can't cheat
                    compUsedWords.insert(prefix); //if the player hasn't used the word already, add it to the PC scoreboard
                }
                if (existsInLex(prefix)){
                    return computerRecursion(prefix, i, j);
                }
                prefix.pop_back();
            }
        }
    }
}
