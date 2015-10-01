#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour(){}

Tour::Tour(Point a, Point b, Point c, Point d){
    cout << "A node has been created" << endl;
	//creating a circular linked list (I hope)
    firstNode = new Node(a, new Node(b, new Node(c, new Node(d, firstNode))));
    /*Node *nodeB = new Node(b, nullptr);
    Node *nodeC = new Node(c, nullptr);
    Node *nodeD = new Node(d, firstNode);*/
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
        Node *current = firstNode;
        while (current->next != nullptr){
            current = current->next;
        }
        current->next = new Node(point, nullptr); //syntax for point? seems correct but unsure
	}
}

void Tour::clear() { //clears from the front to the back (if there is such a thing in a circular linked list...)
    while (firstNode != nullptr) {
        Node* temp = firstNode;
        firstNode = firstNode->next;
        delete temp;
    }
}

void Tour::show(){

    Point point = node->point; //TODO: Fix this, node is not declared here currently in this git push
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
