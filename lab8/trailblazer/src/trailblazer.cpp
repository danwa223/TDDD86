#include "costs.h"
#include "trailblazer.h"
#include <queue>
#include "pqueue.h"

using namespace std;

bool depthFirstSearchRecursive(BasicGraph& graph, Vertex* start, Vertex* end, vector<Vertex*>& path);


bool depthFirstSearchRecursive(BasicGraph& graph, Vertex* currentNode, Vertex* end, vector<Vertex*>& path) {

	currentNode->visited = true;
	currentNode->setColor(GREEN);

	// if start and end is the same node they are the path
	if (currentNode == end) {
		path.push_back(currentNode);
		return true;
	}

	for (Vertex* neighbour : graph.getNeighbors(currentNode)) {
		if (!neighbour->visited) {

			// Check if the child find a path, if it does add it to the path
			if (depthFirstSearchRecursive(graph, neighbour, end, path)) {
				path.push_back(currentNode);
				return true;
			}
		}
	}

	currentNode->setColor(GRAY);
	return false;
}


// This algorithm will NOT find the shortest path
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {

	// Reset BasicGraph data and declare the path vector
	graph.resetData();
	vector<Vertex*> path;

	// Call the recursive help function
	depthFirstSearchRecursive(graph, start, end, path);

    return path;
}

vector<Node *> pathBuilderToStart(Vertex* start, Vertex* end){
    //iterate back to start
    vector<Vertex*> path;
    Vertex* cur = end; //initiate with the end
    while (cur != start){
        path.insert(path.begin(), cur);
        cur = cur->previous;
    }
    path.insert(path.begin(), start);
    return path;
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    queue<Vertex*> allPaths;
    allPaths.push(start);

    while (!allPaths.empty()){
        Vertex* position = allPaths.front(); //element next in line to be evaluated
        allPaths.pop();
        position->visited = true;
        position->setColor(GREEN);
        if (position == end){
            return pathBuilderToStart(start, position); //builds the entire path here
        }else{
            for (Node *next : graph.getNeighbors(position)){ //for all neighbours of current element, see lab doc
                if (!next->visited){
                    next->setColor(YELLOW);
                    next->previous = position;
                    allPaths.push(next);
                }
            }
        }
    }
    //if pathBuildBfs wasn't called we return an empty path
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
	graph.resetData();
    vector<Vertex*> path;
    for (Vertex* node : graph.getNodeSet()){ //initiate all nodes with an inf. cost
        node->cost = INFINITY;
    }
    PriorityQueue<Vertex*> pQueue;
    start->cost = 0;
    pQueue.enqueue(start, start->cost); //start of search

    while (!pQueue.isEmpty()){
        Vertex* v = pQueue.dequeue();
        v->visited = true;
        v->setColor(GREEN);
        if (v == end){
            return pathBuilderToStart(start, v); //same as the one bfs uses
        }else{
            for(Arc* edge : graph.getEdgeSet(v)){ //Go through each edge from the Vertex v, counting the cost for each newly visited vertex
                Vertex* next = edge->finish;
                if (!next->visited){
                    double cost = v->cost + edge->cost;
                    if (cost < next->cost){ //found a lesser cost, what dijkstra is all about
                        next->setColor(YELLOW);
                        next->cost = cost;
                        next->previous = v;
                        pQueue.enqueue(next, cost);
                        //pQueue.changePriority(next, cost); Only do this if next already is in the queue, but this should not ever occur?
                    }
                }
            }
        }
    }
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    //works the same way as dijkstra, the only change is that it uses a heuristic to calculate the vertex cost.
	graph.resetData();
    vector<Vertex*> path;
    for (Vertex* node : graph.getNodeSet()){ //initiate all nodes with an inf. cost
        node->cost = INFINITY;
    }
    PriorityQueue<Vertex*> pQueue;
    start->cost = 0;
    pQueue.enqueue(start, start->heuristic(end)); //start of search

    while (!pQueue.isEmpty()){
        Vertex* v = pQueue.dequeue();
        v->visited = true;
        v->setColor(GREEN);
        if (v == end){
            return pathBuilderToStart(start, v); //same as the one bfs uses
        }else{
            for(Arc* edge : graph.getEdgeSet(v)){ //Go through each edge from the Vertex v, counting the cost for each newly visited vertex
                Vertex* next = edge->finish;
                if (!next->visited){
                    double cost = v->cost + edge->cost;
                    if (cost < next->cost){ //found a lesser cost
                        next->setColor(YELLOW);
                        next->cost = cost;
                        next->previous = v;
                        pQueue.enqueue(next, cost + next->heuristic(end));
                        //pQueue.changePriority(next, cost + next->heuristic(end)); Only do this if next already is in the queue, but this should not ever occur?
                    }
                }
            }
        }
    }
    return path;
}
