// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <queue>
// TODO: include any other headers you need; remove this comment
using namespace std;

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
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
    vector<Vertex*> path;
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
