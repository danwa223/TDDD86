// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"

TileList::TileList(){
	cout << "Tile list is being created";

	currentSize = 0;
	allocSize = 10;

	Tile *tileArray = new Tile[allocSize];
}

TileList::~TileList(){
	cout << "Tile list is being destroyed";

	delete[] tileArray;
}

void TileList::addTile(Tile tile){

	Tile[currentSize] = tile;
	currentSize++;   //increment size after adding element since arrays are 0-indexed
}

void TileList::drawAll(QGraphicsScene* scene){
	for (int i = 0; i < currentSize; ++i){
		Tile[i].draw(scene);
	}
}

int TileList::indexOfTopTile(int x, int y){
	//randomstringlol =Tile[currentSize].toString();
}

void TileList::raise(int x, int y){
    // TODO: write this member
}

void TileList::lower(int x, int y){
    // TODO: write this member
}

void TileList::remove(int x, int y){
    // TODO: write this member
}

void TileList::removeAll(int x, int y){
    // TODO: write this member
}
