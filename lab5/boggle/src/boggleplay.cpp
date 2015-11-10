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

		printWords(boggle.getUsedWords(), "Your ");
		cout << "Your score: " << boggle.calcScore("p") << endl;

		string word;

        cout << "Type a word (or press Enter to end your turn): ";
		getline(cin, word);

		if (word == "") {
			cout << endl;
			break;
        } else if (boggle.hasBeenUsed(word)){
            cout << "You've alredy guessed that word! Try again!";
        } else if ((checkWord(lex, word)) && (not (boggle.hasBeenUsed(word))) && boggle.findWord(word)) {
            cout << "You found a new word! '" << word << "'";
		} else {
			cout << "That's not a word! Try again!";
		}

		// Let's go another round!
		//if (cin.get() == '\n') clearConsole();
		cout << endl;
	}

	//TODO: Make this
	// Computers turn
	cout << "It's my turn!" << endl;
	// recursive algoritm in boggle.cpp
	//void printWords(boggle.getUsedWords(), "My"); //TODO: Change to computer
	cout << "My score: " << boggle.calcScore("c") << endl;

	if (true/* computerScore > playerScore*/) {
		cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
	} else if (true/* computerScore < playerScore*/) {
		cout << "I lost? Impossible!" << endl;
	} else {
		cout << "wat";
	}

	//clearing the list of used word in case we want to play another round
	boggle.clearUsedWords();
}

/*
 * Prints the game board one time
 */
void printBoard(Grid<char> board) {

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
void printWords(set<string> usedWords, string who) {

	//if (usedWords.size()){
		cout << who << " words (" << usedWords.size() << "): {";

		set<string>::iterator it;
		for(it = usedWords.begin(); it != usedWords.end(); ++it){
			cout << "\"" << *it << "\", ";
		}
		cout << "}" << endl;
	//}
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
