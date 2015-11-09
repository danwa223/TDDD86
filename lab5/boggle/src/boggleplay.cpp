#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
//#include <string>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"

//using namespace std;

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle &boggle) {

    if (yesOrNo("Do you want to generate a random board? ")) {
        cout << "Every day I'm shuffelin'...";
        //shuffleCubes();
    }
    cout << "It's your turn!" << endl;

	printBoard(boggle.board);

    //printPlayerWords(some shitty array);

    string word;

    while(true) {
        cout << "Type a word (or press Enter to end your turn): ";
       getline(cin, word);

        if (checkWord(word)) {
            cout << "You found a new word! '" << word << "'" << endl;
            }

        cout << "That's not a word! Try again" << endl;
    }

}

/*
 * Prints the game board one time
 */
void printBoard(Board& board) {

    // TODO: make sure this work for grid
    for (int h = 0; h < 4; ++h) {
        for (int w = 0; w < 4; ++w) {
			cout << board[h][w];
        }
        cout << endl;
    }
}

/*
 * Return true if the string entered is a valid word according to the lexicon
 */
bool checkWord(string word) {
    return lex.contains(word);
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
