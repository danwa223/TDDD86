#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
//#include <string>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
//#include "lexicon.h"

//using namespace std;

//void printBoard(Board &board);
//bool checkWord(string word);

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {

	Lexicon lex("EnglishWords.dat");

    if (yesOrNo("Do you want to generate a random board? ")) {
		cout << "Every day I'm shuffelin'..." << endl;
		boggle.shuffleCubes();
    }
	cout << endl << "It's your turn!" << endl;

	// the players turn
	while(true) {
		printBoard(boggle.getBoard());

		printPlayerWords(/*some shitty array*/);
		printPlayerWords();

		string word;

        cout << "Type a word (or press Enter to end your turn): ";
		getline(cin, word);

		if (checkWord(lex, word)) {
            cout << "You found a new word! '" << word << "'" << endl;
			boggle.usedWords.insert(word);
            }
		else {
			cout << "That's not a word! Try again" << endl;
		}

		// the players turn is over
		if (cin.get() == '\n') break;
    }



}

/*
 * Prints the game board one time
 */
void printBoard(Grid<char> board) {

    // TODO: make sure this work for grid
    for (int h = 0; h < 4; ++h) {
        for (int w = 0; w < 4; ++w) {
			cout << board[h][w];
        }
        cout << endl;
    }
	cout << endl;
}

/*
 * Print out the words the player have already found
 */
void printPlayerWords(){
	cout << "Your words (" << "some int" << "): {";
	for (int i = 0; i < 10; ++i){ //TODO: Later change this to actually take an array and print real words
		cout << "\"" << " array[i]" << "\", ";
	}
	cout << "}" << endl;
}

/*
 * Return true if the string entered is a valid word according to the lexicon
 */
bool checkWord(Lexicon lex, string word) {
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
