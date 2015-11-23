#include "encoding.h"

map<int, int> buildFrequencyTable(istream& input) {

	map<int, int> freqTable;

	int inChar = 0;
	map<int, int>::iterator it;

	// keep getting input chars untill we reach end of file (-1)
	while((inChar != -1)) {
		inChar = input.get();

		/*// map.insert(key) will return an iterator pointing to key if key is in map
		 *if(freqTable.insert(inChar) != freqTable.end) {
		 *
		 *}
		 */

		it = freqTable.find(inChar);
		if(it != freqTable.end()) {
			it->second++;
		} else {
			freqTable.insert(inChar ,1);
		}
	}

    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    // TODO: implement this function
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

