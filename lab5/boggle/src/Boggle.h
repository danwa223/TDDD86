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

// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    Boggle();   //constructor
    Boggle(string customGame); //custom board constructor
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    string shuffledCubes = ""; //needs to be public to be accessed by boggleplay, is a representation for output

    // TODO: decide the public member functions and declare them
    //void throwDices(); //pick a random letter frome each dice
    void shuffleCubes(); //randomization of cubes
    bool hasBeenUsed(string word);
    bool isLongEnough(string word);
    bool hasBeenPlayed(string word);

private:
    // TODO: decide the private member variables/functions and declare them

    Grid<char> board;
    set<string> usedWords;
};

#endif
