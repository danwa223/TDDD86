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
 * Custom constructor for testing purposes, takes a custom string and uses the 16 first characters to create a board
 */
Boggle::Boggle(string customGame){
    board.resize(4, 4); //init the board, discard garbage values
    int index = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            char c = customGame[index];
            putchar(toupper(c)); //capitalizes current char
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
 * During play, checks if a given set<string> word fits the length criteria
 */
bool Boggle::isLongEnough(string word){
    return (word.length() > 3); //returns true for words length 4 or greater
}

/*
 * During play, checks if a word exists in the given lexicon of words
 */
bool Boggle::existsInLex(string word){
    //TODO: Implement lexicon
}
