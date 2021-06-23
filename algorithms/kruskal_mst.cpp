#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<vector<int>> kruskalMST(vector<vector<int>> &graph);

int main() {
    /**
     * Kruskal's algorithm is implemented with the idea of sorting all
     * the edges in a graph based on their weights, and then simply 
     * connecting those nodes in ascending, which do not form a circle
     */ 
    cout << "\nThis program uses Kruskal's Algorithm to find out minimum spanning tree.\n" << endl;
    int edges;
    cout << "Enter the number of edges to consider: ";
    cin >> edges;

    vector<vector<int>> graph(edges, vector<int>(3));
    
    cout << "Enter space seperated nodes in a edge and their weights, delimited by newline," << endl;
    for (int i = 0; i < edges; i += 1) cin >> graph[i][0] >> graph[i][1] >> graph[i][2];

    vector<vector<int>> mst = kruskalMST(graph);

    int sum = 0;
    cout << "\nThe resulting MST is," << endl;
    for (auto &edge : mst) {
        cout << edge[0] << " -> " << edge[1] << " => " << edge[2] << endl;
        sum += edge[2];
    }
    cout << "\nThe cost incurred is: " << sum << "." << endl;

    cout << endl;

    return 0;
}

vector<vector<int>> kruskalMST(vector<vector<int>> &graph) {
    // In order to find out minimal cost nodes we need to sort
    // the edges on the basis of ascending travelling cost
    sort(graph.begin(), graph.end(), [](vector<int> &a, vector<int> &b) {
        return a[2] < b[2];
    });

    // Next we need to maintain visitation status of each node
    // in order to prevent formation of a cycle
    unordered_map<int, bool> visited;
    for (auto &edge : graph) {
        visited[edge[0]] = false;
        visited[edge[1]] = false;
    }

    // We need a vector of vector to store valid connections
    vector<vector<int>> result;

    for (auto &edge : graph) {
        // Since both the nodes have already been traversed, connecting
        // them will create a loop, hence we ignore
        if (visited[edge[0]] && visited[edge[1]]) continue;

        result.push_back(edge);
        visited[edge[0]] = true;
        visited[edge[1]] = true;
    }

    return result;
}