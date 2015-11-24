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
	cout << "Entering buildEncodingTree(freqTable);";

	//map<int, int>::iterator it;
	priority_queue<HuffmanNode> prioQueue;

	// Use the frequency table to build a priority queue of tree nodes
	//map<int,int>::iterator and map<int, int>::const_iterator TODO: Ask about this
	for (auto it = freqTable.begin(); it != freqTable.end(); ++it) {
		HuffmanNode *tempNode = new HuffmanNode(it->first, it->second);
		prioQueue.push(*tempNode);
	}

	HuffmanNode firstNode;
	HuffmanNode secondNode;

	// Keep combining nodes until the priority queue only contain a root of a tree
	while(!(prioQueue.size() == 1)) {

		// getting the two first nodes from the Priority Queue
		firstNode = prioQueue.top();
		prioQueue.pop();
		secondNode = prioQueue.top();
		prioQueue.pop();

		cout << "Whileing...";
		// Create a new node
		// Count is the combined frequency of the two nodes, firstNode is the left and secondNode the right child
		HuffmanNode *parentNode = new HuffmanNode(NOT_A_CHAR, (firstNode.count + secondNode.count), &firstNode, &secondNode);

		prioQueue.push(*parentNode);
	}

	// The priority queue should contain only a tree by now
	HuffmanNode *treeRoot = new HuffmanNode();
	*treeRoot = prioQueue.top();
	return treeRoot;
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
