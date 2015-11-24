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
		if (inChar == -1) break;

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

/*
 * Puts every (int)character in the map as an encoded path.
 */
void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    int c; //actually is char
    string encodedPath;
    while (true){
        //compare c to map, replace c with the string representation
        c = input.get();
        if (encodingMap.find(c) != encodingMap.end()){ //might be redundant
            encodedPath += encodingMap.at(c);
        }
        if ((c == 256) || (c == -1)){ //EOF, ascii being dumb
            break;
        }
    }
    //cout << encodedPath << endl; debug
    for (unsigned int i = 0; i < encodedPath.size(); i++){
        output.writeBit(encodedPath[i] == '1');
    }
}

/*
 * Decodes data given bit input (so if you are using the terminal, give it 0s and 1s you dipshit)
 */
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {


    int bit;
    HuffmanNode *currentNode = encodingTree;

    while(true) {
        bit = input.readBit();
        if ((bit == -1) || (bit == 256)){
            break; //reached EOF
        } else if (bit == 0){
            currentNode = currentNode->zero; //go left
        } else if (bit == 1){ //bit == 1
            currentNode = currentNode->one; //go right
        }
        if (currentNode->isLeaf()){
            output.put(currentNode->character); //output the char since we are in a leaf
            currentNode = encodingTree; //reset to root
        }
    }
}

void compress(istream& input, obitstream& output) {

    map<int, int> freqTable = buildFrequencyTable(input);
    HuffmanNode *encodingTree = buildEncodingTree(freqTable);
    map<int, string> encodingMap = buildEncodingMap(encodingTree);

    string header = "{";
    for(map<int,int>::const_iterator it = freqTable.begin(); it != freqTable.end(); ++it){
        header.append(to_string(it->first)+":"+to_string(it->second)+", ");
    }
    header = header.substr(0,header.size()-2); //remove last ",' '"
    header.append("}");
    //cout << header << endl; debug

    //save the entire header in the output for decompression later
    for(unsigned int i = 0;i<header.size(); i++){
        output<<header[i];
    }

    // Rewind input for encodeData()
    input.clear();
    input.seekg(0, ios::beg);

    encodeData(input, encodingMap, output);
}
map<int, int> decompressFreqTable(ibitstream &input){

    map<int, int> freqTable;
    int key, value;
    string stringChar;

    // remove first {
    int byte = input.get();

    while(byte != (int)'}'){ //keep looping until end of header

        // reset values
        key = 0;
        value = 0;
        byte = input.get();

        // remove space
        if(byte == (int)' ') byte = input.get();

        // get ascii representation
        while(byte != (int)':'){
            //stringChar = (char)byte; //string rep of char rep that originates from ascii rep DEBUG
            //value += stoi(stringChar); //add value of string
            value += byte;
            byte = input.get();
        }
        // skips the ":"
        byte = input.get();

        // get key (amount of occurance)
        while(byte != (int)',' && byte!=(int)'}'){
            //stringChar = (char)byte; //string rep of char rep that originates from count DEBUG
            //key += stoi(stringChar); //add value of string
            key += byte;
            byte = input.get();
        }
        // insert in freqTable
        freqTable.insert(make_pair(value, key));
    }
    return freqTable;
}

void decompress(ibitstream& input, ostream& output) {
    map<int, int> freqTable = decompressFreqTable(input);
    HuffmanNode *encodingTree = buildEncodingTree(freqTable);
    decodeData(input, encodingTree, output);
}

void freeTree(HuffmanNode *node) {

	// Debug code
	//cout << endl << "Printing tree:" << endl;
	//printSideways(node);

	HuffmanNode *currentNode = node;

	// Return if there is no tree
	if (currentNode == nullptr) return;

	// If we're a leaf, delete ourselves
	if (currentNode->isLeaf()) {
		delete currentNode;
		return;
	}  else {

		// Visit the left node, once we return cut the pointer
		freeTree(currentNode->zero);
		currentNode->zero = nullptr;

		// Visit the right node, once we return cut the pointer
		freeTree(currentNode->one);
		currentNode->one = nullptr;
	}
}
