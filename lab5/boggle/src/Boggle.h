// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <set>
#include "../lib/StanfordCPPLib/grid.h"
#include "../lib/StanfordCPPLib/random.h"
#include "../lib/StanfordCPPLib/lexicon.h"

// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
	Boggle();   //constructor
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    string shuffledCubes = ""; //needs to be public to be accessed by boggleplay, is a representation for output


	void boardOverwrite(string customGame);
    Grid<char> getBoard();
    set<string> getUsedWords();
	set<string> getCompUsedWords();
	void shuffleCubes(); //randomization of cubes
    bool hasBeenUsed(string word);
	void clearUsedWords();
    bool isLongEnough(string word);
    bool existsInLex(string prefix);
    void playerBacktrack(string word);
    bool findWord(string &word);
    void findWords();
	int calcScore(string who);

private:
    //bool found;
	Grid<char> board;
    set<string> usedWords; //contains all legit words the player has found
    set<string> compUsedWords; //words for CPU player after player player has played

    bool playerRecursion(string prefix, unsigned int index, int row_pos, int col_pos, string &word, bool &found);
    void computerRecursion(string prefix, int row_pos, int col_pos);

    //would like to initialize a lexicon here to be global in Boggle.cpp
	Lexicon lex = Lexicon("EnglishWords.dat");
    set<string> wordsFoundOnBoard;
};

#endif
