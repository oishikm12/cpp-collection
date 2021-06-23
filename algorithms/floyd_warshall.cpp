#include <iostream>
#include <vector>
using namespace std;

int main() {
    /**
     * We initialize the solution matrix same as the input graph matrix 
     * as a first step. Then we update the solution matrix by considering 
     * all vertices as an intermediate vertex. The idea is to one by one 
     * pick all vertices and updates all shortest paths which include the 
     * picked vertex as an intermediate vertex in the shortest path.
     */
    cout << "\nThis program finds out shortest path from each node to other in a weighted graph.\n" << endl; 
    int edges, vertices;
    cout << "Enter number of edges to consider: ";
    cin >> edges;
    cout << "Enter number of vertices to consider: ";
    cin >> vertices;

    vector<vector<int>> graph(vertices, vector<int>(vertices, INT_MAX));
    cout << "Enter space seperated, line delimited edges & their weights," << endl;
    for (int i = 0; i < edges; i += 1) {
        int u, v, wt;
        cin >> u >> v >> wt;
        graph[u][v] = wt;
        graph[v][u] = wt;
    }

    vector<vector<int>> distances = floydWarshallDist(graph, vertices);
    cout << "\nThe distance from each nodes to the others are," << endl;
    printGraph(distances, vertices);

    cout << endl;

    return 0;
}

vector<vector<int>> floydWarshallDist(vector<vector<int>> &graph, int vertices) {
    // Add all vertices one by one to the set of intermediate vertices.
    // 1. Before start of an iteration, we have shortest distances between all
    //    pairs of vertices such that the shortest distances consider only the
    //    vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
    // 2. After the end of an iteration, vertex no. k is added to the set of
    //    intermediate vertices and the set becomes {0, 1, 2, ...k}
    // NOTE: Minimal distance is same as that in initial graph
    vector<vector<int>> distances = graph;

    for (int k = 0; k < vertices; k += 1) {
        // Pick all vertices as source one by one
        for (int i = 0; i < vertices; i += 1) {
            // Pick all vertices as destination for the above picked source
            for (int j = 0; j < vertices; j += 1) {
                // If vertex k is on the shortest path from i to j, then 
                // update the value of distances[i][j]
                bool isShortest = distances[i][j] > (distances[i][k] + distances[k][j]);
                bool isValid = distances[k][j] != INT_MAX && distances[i][k] != INT_MAX;

                if (isValid && isShortest) distances[i][j] = distances[i][k] + distances[k][j];
            }
        }
    }

    return distances;
}

void printGraph(vector<vector<int>> &graph, int vertices) {
    cout << "\n   ";
    for (int i = 0; i < vertices; i += 1) cout << i << " ";
    cout << "\n   ";
    for (int i = 0; i < vertices; i += 1) cout << "_ ";
    cout << endl;
    for (int i = 0; i < vertices; i += 1) {
        cout << i << "| ";
        for (int j = 0; j < vertices; j += 1) cout << graph[i][j] << " ";
        cout << endl;
    }
}