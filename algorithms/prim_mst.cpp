#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<int> primMST(vector<vector<int>> &);
int getMinWeightVertex(vector<int> &, vector<bool> &, int);

int main() {
    /**
     * The idea is to maintain two sets of vertices. The first set 
     * contains the vertices already included in the MST, the other 
     * set contains the vertices not yet included. At every step, it
     * considers all the edges that connect the two sets, and picks
     * the minimum weight edge from these edges. After picking the edge,
     * it moves the other endpoint of the edge to the set containing MST
     */ 
    cout << "\nThis program uses Prim's Algorithm to find out minimum spanning tree.\n" << endl;
    int vertices, edges;
    cout << "Enter the number of vertices to consider: ";
    cin >> vertices;
    cout << "Enter the number of edges to consider: ";
    cin >> edges;

    vector<vector<int>> graph(vertices, vector<int>(vertices, 0));
    
    cout << "Enter space seperated nodes in a edge and their weights, delimited by newline," << endl;
    for (int i = 0; i < edges; i += 1) {
        int u, v, wt;
        cin >> u >> v >> wt;
        graph[u][v] = wt;
        graph[v][u] = wt;
    }

    vector<int> mst = primMST(graph);

    int sum = 0;
    cout << "\nThe resulting MST is," << endl;
    for (int i = 1; i < vertices; i += 1) {
        cout << mst[i] << " -> " << i << " => " << graph[i][mst[i]] << endl;
        sum += graph[i][mst[i]];
    }
    cout << "\nThe cost incurred is: " << sum << "." << endl;

    cout << endl;

    return 0;
}

vector<int> primMST(vector<vector<int>> &graph) {
    int vertices = graph.size();

    // Vector to store constructed MST 
    vector<int> parent(vertices);
    // Represents current weight / cost to reach this vertex
    vector<int> weight(vertices);
    // To represent set of vertices included in MST 
    vector<bool> visited(vertices); 
  
    // We inintialize all the weights as Max, and also set all to false
    for (int i = 0; i < vertices; i += 1) { 
        weight[i] = INT_MAX;
        visited[i] = false; 
    }
  
    // We always include the first vertex in MST, and then
    // Make it 0 so that this vertex is picked as first vertex. 
    weight[0] = 0; 
    // First node becomes the root of MST
    parent[0] = -1; 
  
    // The MST will have all vertices 
    for (int count = 1; count < vertices; count += 1) { 
        // Pick the minimum weight vertex from the 
        // set of vertices not yet included in MST 
        int u = getMinWeightVertex(weight, visited, vertices); 
  
        // Add the picked vertex to the MST Set 
        visited[u] = true; 
  
        // Update weight value and parent index of 
        // the adjacent vertices of the picked vertex. 
        // Consider only those vertices which are not 
        // yet included in MST 
        for (int v = 0; v < vertices; v += 1) { 
            // graph[u][v] is non zero only for adjacent vertices of `u`
            if (!graph[u][v]) continue;
            // visited[v] is false for vertices not yet included in MST 
            // Update the weight only if graph[u][v] is smaller than weight[v] 
            if (visited[v] == false && graph[u][v] < weight[v]) {
                parent[v] = u;
                weight[v] = graph[u][v]; 
            }
        }
    } 
  
    return parent;
}

int getMinWeightVertex(vector<int> &weight, vector<bool> &visited, int vertices)  { 
    // Initialize minimum value 
    int minimum = INT_MAX; 
    int minIndex; 
  
    // We then simply find the minimum unvisited weight
    for (int v = 0; v < vertices; v += 1) { 
        if (visited[v] == false && weight[v] < minimum) {
            minimum = weight[v];
            minIndex = v; 
        }
    }
  
    return minIndex; 
} 