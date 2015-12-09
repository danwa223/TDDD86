#include "costs.h"
#include "trailblazer.h"
#include "pqueue.h"

using namespace std;

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

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
	graph.resetData();
    vector<Vertex*> path;
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
	graph.resetData();
    vector<Vertex*> path;
    return path;
}
