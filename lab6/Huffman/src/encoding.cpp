#include "encoding.h"
#include "bitstream.h"
#include <queue>

void traverseTree(map<int, string> &encodingMap, HuffmanNode *currentNode, string path); //should be in .h file but we only turn in this one!

map<int, int> buildFrequencyTable(istream& input) {

	map<int, int> freqTable;
	map<int, int>::iterator it;

	int inChar;

	// Keep reading characters from input untill we reach End Of File (-1)
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

	priority_queue<HuffmanNode> prioQueue;
    HuffmanNode *Node;

	// Use the frequency table to build a priority queue of tree nodes
    //map<int,int>::iterator and map<int, int>::const_iterator
    //TODO: Ask about this, why auto?
    for (auto it = freqTable.begin(); it != freqTable.end(); ++it) {
        Node = new HuffmanNode(it->first, it->second);
        HuffmanNode insertNode = *Node;
        prioQueue.push(insertNode);
    }

    HuffmanNode *parentNode; //parent that will be built
    HuffmanNode leftNode; //first in prioQueue
    HuffmanNode rightNode; //second in prioQueue
    HuffmanNode *pointer; //temp

	while(!(prioQueue.size() == 1)) {
		leftNode = prioQueue.top();
		prioQueue.pop();
        rightNode = prioQueue.top();
		prioQueue.pop();

		// Create a new node
		// Count is the combined frequency of the two nodes, firstNode is the left and secondNode the right child
        parentNode = new HuffmanNode(NOT_A_CHAR, (leftNode.count + rightNode.count), nullptr, nullptr); //building of parent
        pointer = new HuffmanNode(leftNode.character, leftNode.count, leftNode.zero, leftNode.one);
        parentNode->zero = pointer;
        pointer = new HuffmanNode(rightNode.character, rightNode.count, rightNode.zero, rightNode.one);
        parentNode->one = pointer;

        HuffmanNode insertNode = *parentNode;
        prioQueue.push(insertNode);
	}

    return parentNode; //root after all insertions and re-linkings have been done
}

/*
 * Builds our encoding map, duh. Uses recursion to traverse the entire tree.
 */
map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {

    map<int, string> encodingMap;
    string path = "";
    traverseTree(encodingMap, encodingTree, path);
    return encodingMap;
}

/*
 * Used to find all characters in a given tree, recursive calls to next node until the entire tree has been traversed
 */
void traverseTree(map<int, string> &encodingMap, HuffmanNode *currentNode, string path){

    if (currentNode == nullptr) return; //trivia: root has no number 0 or 1
    if (currentNode->isLeaf()){
        encodingMap.insert(make_pair(currentNode->character, path)); //put the char with the path needed to get there
        return;
    }else{
        traverseTree(encodingMap, currentNode->zero, path + "0"); //go left
        traverseTree(encodingMap, currentNode->one, path + "1"); //go right
    }
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {

	int bit = 0;
	bool found = false;
	string character = "";

	// Keep going until End Of File (-1)
	while(!(bit == -1)) {
		bit = input.readBit();

		// Keep going until we find a character
		while(!found) {

			// Check if character is in tree
			if(character) {
				found = true;
			} else {
				character.append(bit);
			}
		}
		found = false;

		// Write to output stream
		output.put(bit);
	}
}

/*
 * Used to find all characters in a given tree, recursive calls to next node until the entire tree has been traversed
 */
void traverseTree(map<int, string> &encodingMap, HuffmanNode *currentNode, string path){

	if (currentNode == nullptr) return; //trivia: root has no number 0 or 1
	if (currentNode->isLeaf()){

		return;
	}else{
		traverseTree(encodingMap, currentNode->zero, path + "0"); //go left
		traverseTree(encodingMap, currentNode->one, path + "1"); //go right
	}
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
