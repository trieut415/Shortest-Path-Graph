//Trieu Tran and Noah Hathout

#include "Graph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits>


//initial constructor, make an enpty tree
Graph::Graph() {
    numVertices = 0; 
    numEdges = 0;
    adj = nullptr;
}

//setter for numVertices
void Graph::initVertices(int V) {
    numVertices = V;
    adj = new vector<pair<int, int> >[V]; //vector to store adjacency list
}

//getter for numVertices
int Graph::getNumVertices() {
    return numVertices;
}

//setter for numEdges
void Graph::setNumEdges(int E) {
    numEdges = E;
}

//getter for numEdges
int Graph::getNumEdges() {
    return numEdges;
}

//add an Edge using a adjacency list with pairs
void Graph::addEdge(int v, int u, int weight) {
    if(u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
        adj[v].push_back(make_pair(u, weight)); 
        adj[u].push_back(make_pair(v, weight));
        numEdges++; 
    }
}

//print the graph through traversing each pair in the adjacency list
void Graph::print() {
    for(int v = 0; v < numVertices; v++) {
       cout << v << ": "; 
       for(const auto& pair : adj[v]) {
          cout << pair.first << " (" << pair.second << ") "; // print
       }
       cout << endl;
    }
}

//read in a file, set numVertices, and add to the adjacency list
void Graph::generateGraph(string fileName) {
    fstream f;
    f.open(fileName, ios::in);

    if(f.is_open()) {
        string line;
        int numV, numE,u,v,w;
        int lines = 0;
        while(getline(f, line)){
            istringstream iss(line);
            if(lines == 0) {
               iss >> numV >> numE;
               initVertices(numV);
               lines++;
            }else{
               iss >> u >> v >> w;
               addEdge(u, v, w); 
            }
        }
    }
    f.close();
}


void Graph::numShortestPaths(int source) {
   vector<int> countV(numVertices, 0);
   vector<int> distance(numVertices, numeric_limits<int>::max());
   priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq; //using a min heap priority queue similar to the one in last HW, 

   countV[source] = 1; 
   distance[source] = 0;

   pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int uVertex = pq.top().second;
        int runningDist = pq.top().first;
        pq.pop();

        if (runningDist > distance[uVertex]) {
            continue;
        }

        for (auto& pair : adj[uVertex]) {
            if (distance[pair.first] == distance[uVertex] + pair.second) {
               countV[pair.first] += countV[uVertex];
            } else if (distance[pair.first] > distance[uVertex] + pair.second) {
                distance[pair.first] = distance[uVertex] + pair.second;
                countV[pair.first] = countV[uVertex];
                pq.push(make_pair(distance[pair.first], pair.first)); //push new pair into the tree in the case that it is the appropriate pair for an MST
            }
        }
    }

//print a list of shortest paths in the distance vector and countV vector
   cout << "\nShortest paths from node " << source << ": \n"; 
   for (int v = 0; v < numVertices; v++) {
      if (v != source) {
         cout << "Distance to vertex " << v << " is " << distance[v];
         cout << " and there are " << countV[v] << " shortest paths\n";
        }
    }
}