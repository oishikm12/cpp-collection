#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isCyclic(int node, vector<vector<int>> &, vector<bool> &, int);
bool isTree(vector<vector<int>> &, int);

int main() {
    /**
     * In order to check if a graph is a tree or not, all we
     * have to do is either BFS or DFS the graph. 
     */ 
    cout << "\nThis program checks if a graph is indeed a tree or not.\n" << endl;
    int vertices;
    cout << "Enter the number of vertices this graph has: ";
    cin >> vertices;

    vector<vector<int>> graph(vertices);
    

}

bool isCyclic(int node, vector<vector<int>> &graph, vector<bool> &visited, int parent) {
    // Mark the current node as visited
    visited[node] = true;
  
    // Recur for all the vertices adjacent to this vertex (DFS)
    for (auto &i : graph[node]) {
        // If an adjacent is not visited, then recur for that adjacent
        if (!visited[i]) {
           if (isCyclic(i, graph, visited, node)) return true;
        }
  
        // If an adjacent is visited and not parent of current
        // vertex, then there is a cycle.
        else if (i != parent) return true;
    }
    
    // This is not cyclic, since no node points to parent
    return false;
}
  

bool isTree(vector<vector<int>> &graph, int vertices) {
    // Returns true if the graph is a tree, else false.
    // Mark all the vertices as not visited
    vector<bool> visited(vertices, false);
  
    // The call to isCyclic serves multiple purposes.
    // It returns true if graph reachable from vertex 0 
    // is cyclcic. It also marks all vertices reachable from 0.
    if (isCyclic(0, graph, visited, -1)) return false;
  
    // If we find a vertex which is not reachable from 0 
    // (not marked by isCyclic(), then we return false
    for (int u = 0; u < vertices; u += 1) {
        if (!visited[u]) return false;
    }
  
    return true;
}