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
	for (int i = currentSize - 1; i >= 0; --i){
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

	//remove the tile from its current place and add it to the end of the list
	removeTile(index);
	addTile(tile);
}

void TileList::lower(int x, int y){

	//get the tile
	int index = indexOfTopTile(x,y);

	//there was no tile
	if (index == -1) return;

	Tile tile = tileArray[index];

	//remove the tile but increment currentSize since we want to keep the size of the array
	removeTile(index);
	currentSize++;

	//shift the array and put tile in the first spot
	for (int i = currentSize - 2; i >= 0; --i){
		tileArray[i + 1] = tileArray[i];
	}

	//add the tile to the start of the array
	tileArray[0] = tile;
}

void TileList::remove(int x, int y){

	//get the tile
	int index = indexOfTopTile(x,y);

	//there was no tile
	if (index == -1) return;

	removeTile(index);
}

void TileList::removeAll(int x, int y){

	//keep calling remove until there's no more tiles at the coordinates
	while(indexOfTopTile(x,y) != -1){
		remove(x,y);
	}
}

void TileList::removeTile(int index){

	//if index == currentSize we just decrement currentSize as that remove the last element in practice
	if (!(index == currentSize -1)){
		for (int i = index; i < currentSize; ++i){
			tileArray[i] = tileArray[i + 1];
		}
	}
	currentSize--;
}
