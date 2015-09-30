#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour(){}

Tour::Tour(Point a, Point b, Point c, Point){

	//creating a circular linked list (I hope)
	firstNode   = new Node(a, nodeB);
	Node *nodeB = new Node(b, nodeC);
	Node *nodeC = new Node(c, nodeD);
	Node *nodeD = new Node(d, nodeA);
}

Tour::~Tour(){

	clear();
}

void Tour::addPoint(Point point){

	//if list is empty, add as first node
	//otherwise, traverse list until last node is found then add node
	if (firstNode == nullptr){
		firstNode = new Node(point, nullptr);
	}
	else{

		while (!nullptr){

		}
	}

	Node node = new Node(point, nullptr);
}

void Tour::show(){

	Point point = node->point;
	std::cout << point.toString();

	node = node->next;
}

void Tour::draw(QGraphicsScene *scene){

    // TODO: write this member
}

int Tour::size(){

    // TODO: write this member
}

double Tour::distance(){

    // TODO: write this member
}

void Tour::insertNearest(Point p){

    // TODO: write this member
}

void Tour::insertSmallest(Point p){

    // TODO: write this member
}
