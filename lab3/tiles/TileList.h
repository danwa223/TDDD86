// This is the .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"

class TileList {
public:
	TileList();   //constructor
	~TileList();  //destructor

	//public functions
	void addTile(Tile tile);                     //add a tile to the end of the tile array
	void drawAll(QGraphicsScene* scene) const;   //draw all tiles
	int indexOfTopTile(int x, int y) const;      //return value of the last (also last drawn) tile
	void lower(int x, int y);                    //move tile to the begining of the list
	void raise(int x, int y);                    //move tile to the end of the list
	void remove(int x, int y);                   //remove tile
	void removeAll(int x, int y);                //remove all tiles

private:
	//private functions
	void allocate();                   //allocate more memory for the dynamic array
	void removeTile(int index);        //remove a specific tile in an array

    int allocSize = 10, currentSize = 0;

    Tile *tileArray = new Tile[allocSize];

};

#endif // TILELIST_H
