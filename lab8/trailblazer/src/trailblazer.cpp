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

vector<Node *> pathBuildBfs(Vertex* start, Vertex* end){
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
            return pathBuildBfs(start, position); //builds the entire path here
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
