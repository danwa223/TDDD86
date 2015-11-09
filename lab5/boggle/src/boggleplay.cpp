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
		cout << "Every day I'm shufflin'..." << endl;
		boggle.shuffleCubes();
    }

	clearConsole();

	cout << endl << "It's your turn!" << endl;

	// Players turn
	while(true) {
		printBoard(boggle.getBoard());

		printPlayerWords(boggle.getUsedWords());
		printScore(/*playerScore*/);

		string word;

        cout << "Type a word (or press Enter to end your turn): ";
		getline(cin, word);

		if (checkWord(lex, word)) {
			if (boggle.hasBeenUsed(word)) {
				cout << "You've already guessed that word! Try again!";
			} else {
				cout << "You found a new word! '" << word << "'";
			}

		// The players turn is over
		} else if (cin.get() == '\n'){
			break;
		} else {
			cout << "That's not a word! Try again!";
		}

		// Let's go another round!
		if (cin.get() == '\n') clearConsole();
    }

	//TODO: Make this
	// Computers turn
	cout << "It's my turn!" << endl;
	// recursive call
	void printComputerWords(/*getComputerWords*/);
	printScore(/*playerScore*/);

	if (true/* computerScore > playerScore*/) {
		cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
	} else if (true/* computerScore < playerScore*/) {
		cout << "I lost? Impossible!" << endl;
	} else {
		cout << "wat";
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
void printPlayerWords(set<string> usedWords) {

	if (usedWords.size()){
		cout << "Your words (" << usedWords.size() << "): {";

		set<string>::iterator it;
		for(it = usedWords.begin(); it != usedWords.end(); ++it){
			cout << "\"" << *it << "\", ";
		}
		cout << "}" << endl;
	}
}

/*
 * Print out the words the CPU found
 * TODO: This currently use the players set, create a new for the computer
 */
void printComputerWords(set<string> usedWords) {
	cout << "My words (" << usedWords.size() << "): {";

	set<string>::iterator it;
	for(it = usedWords.begin(); it != usedWords.end(); ++it){
		cout << "\"" << *it << "\", ";
	}
	cout << "}" << endl;
}

void printScore() {

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
