#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

using namespace std;

Tour::Tour(){}

Tour::Tour(Point a, Point b, Point c, Point d){

	//creating a circular linked list (I hope)
	firstNode = new Node(a,
				new Node(b,
				new Node(c,
				new Node(d, firstNode))));
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
        current->next = new Node(point, nullptr);
	}
}

void Tour::clear() { //clears from the front to the back (if there is such a thing in a circular linked list...)

	Node *current = firstNode;

	while (firstNode != nullptr) {
		current = current->next;
		delete current;
	}
}

void Tour::show(){ //prints the linked list to console

	Node *current = firstNode;

	cout << current->point.toString() << endl;
	current = current->next;

    while (current != nullptr && current != firstNode) {
        cout << current->point.toString() << endl;
        current = current->next;
    }
}

void Tour::draw(QGraphicsScene *scene){

    Node* current = firstNode;

    current->point.drawTo(current->next->point, scene);
    current = current->next;

    while (current != nullptr && current != firstNode) {
        current->point.drawTo(current->next->point, scene);
        current = current->next;
    }
}

int Tour::size(){

	Node *current = firstNode;

    if (firstNode == nullptr){
        return 0;
    }

    int pointCtr = 1;
    current = current->next;
    while(current != nullptr && current != firstNode){
		pointCtr++;
		current = current->next;
	}
    return pointCtr;
}

double Tour::distance(){

	Node *current = firstNode;
    double tourDistance = 0;

    tourDistance += current->point.distanceTo(current->next->point);
    current = current->next;

    while (current != nullptr && current != firstNode) {
        tourDistance += current->point.distanceTo(current->next->point);
        current = current->next;
    }
    return tourDistance;
}

void Tour::insertNearest(Point p){

    //if empty list, insert first
    if(firstNode == nullptr){
		firstNode = new Node(p);
		firstNode->next = firstNode;
	} else {

		Node *current = firstNode;
		Node *nearestNode = firstNode;

        //initiate the search with the first node in the list as the current closest point
        double nearestDistance = p.distanceTo(firstNode->point);

        current = current->next;
        if (nearestDistance > p.distanceTo(current->point)){
            nearestNode = current;
            nearestDistance = p.distanceTo(current->point);
        }

        //traverse the list and look after points closer to p than the previous nearest
        while (current != nullptr && current != firstNode){
			current = current->next;
			if (nearestDistance > p.distanceTo(current->point)){
				nearestNode = current;
				nearestDistance = p.distanceTo(current->point);
			}
		}
		insert(p, *nearestNode);
	}
}

void Tour::insertSmallest(Point p){

	//if empty list, insert first
	if(firstNode == nullptr){
		firstNode = new Node(p);
		firstNode->next = firstNode;
	} else {

		//Node *current, *nearestNode = firstNode;
		Node *current = firstNode;
		Node *nearestNode = firstNode;

		//pretend to insert p between firstNode and firstNode->next to get the potential increase in distance
		double smallestIncrease = (p.distanceTo(current->point) + p.distanceTo(current->next->point));

		current = current->next;

		//compare current smallest increase with the potential distance between current, p and current-next
		if (smallestIncrease > p.distanceTo(current->point) + p.distanceTo(current->next->point)){
			nearestNode = current;
			smallestIncrease = p.distanceTo(current->point) + p.distanceTo(current->next->point);
		}

		//traverse the list and look after points which does not increase the total tour length
		while (current != nullptr && current->next != firstNode){
            current = current->next;

			//compare current smallest increase with the potential distance between current, p and current-next
			if (smallestIncrease > p.distanceTo(current->point) + p.distanceTo(current->next->point)){
				nearestNode = current;
				smallestIncrease = p.distanceTo(current->point) + p.distanceTo(current->next->point);
			}
		}
		insert(p, *nearestNode);
    }
}

void Tour::insert(Point p, Node &node){

		//create a new node and insert it after node
		Node *temp = node.next;
		node.next = new Node(p);
		node.next->next = temp;
}
