// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"

TileList::TileList(){

	currentSize = 0;
	allocSize = 10;

	Tile *tileArray = new Tile[allocSize];
}

TileList::~TileList(){

	delete[] tileArray;
}

void TileList::addTile(Tile tile){

	//if true we've reached the max size and need to allocate more space
	if (currentSize == allocSize){
		allocate();
	}

	//increment current size after adding element since arrays are 0-indexed
	tileArray[currentSize] = tile;
	currentSize++;
}

void TileList::allocate(){

	int tempAllocSize = allocSize*2;
	Tile *tempTileArray = new Tile[tempAllocSize];

	//copy the old array into the temporary array
	for (int i = 0; i < currentSize; ++i){
		tempTileArray[i] = tileArray[i];
	}

	//free memory of old array and copy the temporary array into a new one
	//delete[] tileArray;  //TODO: FIX THIS
	tileArray = tempTileArray;
	allocSize = tempAllocSize;
}

void TileList::drawAll(QGraphicsScene* scene){

	for (int i = 0; i < currentSize; ++i){
        tileArray[i].draw(scene); //was Tile[i].draw before???, seems more logical that you want to draw a tile from the tileArray.
        //also gave compiling errors before
	}
}

int TileList::indexOfTopTile(int x, int y){

	//iterate backwards over the tileList and return the first tile matching the given coordinates
	for (int i = currentSize; i >= 0; --i){
		if (tileArray[i].contains(x,y)) return i;
	}

	//no matching tile found
	return -1;
}

void TileList::raise(int x, int y){

	//get the tile
	int index = indexOfTopTile(x,y);

	//there was no tile
	if (index == -1) return;

	Tile tile = tileArray[index];

	for (int i = index; i < currentSize; i++){
		tileArray[i] = tileArray[i + 1];
	}

	removeTile(index);
	addTile(tile);
}

void TileList::lower(int x, int y){

	//get the tile
	int index = indexOfTopTile(x,y);

	//there was no tile
	if (index == -1) return;
}

void TileList::remove(int x, int y){

	 // TODO: write this member
}

void TileList::removeAll(int x, int y){

    // TODO: write this member
}

void TileList::removeTile(int index) {

	for (int i = index; i < currentSize; i++){
		tileArray[i] = tileArray[i + 1];
	}

	currentSize--;
}
