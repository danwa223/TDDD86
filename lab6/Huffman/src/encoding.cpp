#include "encoding.h"
#include <queue>

map<int, int> buildFrequencyTable(istream& input) {
	cout << "asdf";

	map<int, int> freqTable;
	map<int, int>::iterator it;

	int inChar;

	// Keep reading characters from input untill we reach end of file (-1)
	while(inChar != -1) {
		inChar = input.get();

		// Insert new characters into freqTable, otherwise increment frequency counter
		if((it = freqTable.find(inChar)) != freqTable.end()) {
			it->second++;
		} else {
			freqTable.insert(make_pair(inChar, 1));
		}
	}

	// End Of File, currently always adding this
	freqTable.insert(make_pair(PSEUDO_EOF, 1));

    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {

	map<int, int>::iterator it;
	priority_queue<HuffmanNode> prioQueue;

	for (it = freqTable.begin(); it != freqTable.end(); ++it) {
		prioQueue.push(HuffmanNode(it->first, it->second));
	}

	// build tree

    return nullptr;
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    map<int, string> encodingMap;
    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
