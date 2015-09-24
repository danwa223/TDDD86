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
    Tile *tempTileArray = new Tile[allocSize*2];
}

TileList::~TileList(){
    //Labb 3 FAQ säger att destruktorn kallas på "automatiskt" ??? https://www.ida.liu.se/~TDDD86/info/lab3-faq.shtml
    cout << "Tile list is being destroyed" << endl;

	delete[] tileArray;
}

void TileList::addTile(Tile tile){

    if (currentSize == allocSize){ //reached array limit but still want to add more
        allocSize = allocSize*2;
        for (int i = 0; i < currentSize; ++i){
            //copy entire old array into temp, O(n)
            tempTileArray[i] = tileArray[i];
        }
        //increment size after adding element since arrays are 0-indexed
        tempTileArray[currentSize] = tile;
        currentSize++;
        //delete[] tileArray; //see comment in destructor, is this line needed?
        tileArray = tempTileArray; //ERROR HERE: invalid array assignment
        //could be an issue with deep copy, see slides from FÖ 8. See slides from FÖ7 on how to dynamically change array aswell
        //delete[] tempTileArray; //see comment in destructor, is this line needed?
    }
    else{
        tileArray[currentSize] = tile;
        currentSize++;
    }
}

void TileList::drawAll(QGraphicsScene* scene){
	for (int i = 0; i < currentSize; ++i){
        tileArray[i].draw(scene); //was Tile[i].draw before???, seems more logical that you want to draw a tile from the tileArray.
        //also gave compiling errors before
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
