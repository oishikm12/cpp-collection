#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
using namespace std;

bool isCyclicBFS(unordered_map<int, list<int>> &, int);
bool dfsCyclicHelper(int, int, unordered_map<int, list<int>> &, unordered_map<int, bool> &);
bool isCyclicDFS(unordered_map<int, list<int>> &);

int main() {
    /**
     * In order to check if a graph is cyclic or not we simply have
     * to perform a BFS on the nodes, if the graph is directed, and 
     * DFS if the graph is undirected
     */ 
    cout << "\nThis program finds out if a graph is cyclic or not.\n" << endl;
    int edges;
    bool directed;
    cout << "Enter the number of edges to consider: ";
    cin >> edges;
    cout << "Enter 1 if the graph is directed: ";
    cin >> directed;

    unordered_map<int, list<int>> graph;
    int start = INT_MAX;
    cout << "Enter space seperated vertices to connect, line delimited for every edge," << endl;
    for (int i = 0; i < edges; i += 1) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        if (!directed) graph[v].push_back(u);
        else if (start == INT_MAX) start = u;
    }

    bool isCyclic;
    if (directed) isCyclic = isCyclicBFS(graph, start);
    else isCyclic = isCyclicDFS(graph);

    if (isCyclic) cout << "\nThe graph contains a cycle." << endl;
    else cout << "\nThe graph does not contain a cycle." << endl;

    cout << endl;

    return 0;
}

bool isCyclicBFS(unordered_map<int, list<int>> &graph, int start) {
    // While visited maps if a node has been already visited,
    // parent tracks the parent of a certain node
    unordered_map<int, bool> visited;
    unordered_map<int, int> parent;

    queue<int> store;

    // We insert the starting pointing of the graph into
    // the queue, since we start checking from the point
    store.push(start);
    visited[start] = true;
    parent[start] = start;

    while (!store.empty()) {
        // For every node we simply pop them from the queue,
        // and then compare if any of its neighbours have been
        // already visited, and they are not the parent of current
        int front = store.front();
        store.pop();

        for (auto &neighbour : graph[front]) {
            if (visited[neighbour] && parent[neighbour] != front) return true;
            else {
                store.push(neighbour);
                parent[neighbour] = front;
                visited[neighbour] = true;
            }
        }
    }

    return false;
}

bool dfsCyclicHelper(int node, int parent, unordered_map<int, list<int>> &graph, unordered_map<int, bool> &visited) {
    // Mark the current node as visited
    visited[node] = true;
  
    // Recur for all the vertices adjacent to this vertex (DFS)
    for (auto &i : graph[node]) {
        // If an adjacent is not visited, then recur for that adjacent
        if (!visited[i]) {
           if (dfsCyclicHelper(i, node, graph, visited)) return true;
        }
        // If an adjacent is visited and not parent of current
        // vertex, then there is a cycle.
        else if (i != parent) return true;
    }
    
    // This is not cyclic, since no node points to parent
    return false;
}

bool isCyclicDFS(unordered_map<int, list<int>> &graph) {
    // Returns true if the graph is a tree, else false.
    // Mark all the vertices as not visited
    unordered_map<int, bool> visited;
  
    // We simply traverse and check if any node in the graph
    // returns true for being cyclic
    for (auto &[node, neighbours] : graph) {
        if (!visited[node]) {
            if (dfsCyclicHelper(node, -1,  graph, visited)) return false;
        }
    }
  
    return true;
}