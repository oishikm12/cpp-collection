#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<int, int> bellmanShortestPath(vector<vector<int>> &, int);

int main() {
    /**
     * In order to find the shortest distance from starting node, to all
     * other nodes, we simply relax all nodes, i.e. we calculate distance 
     * from current to all other nodes, at every step the minimal value is kept
     * In the end, we try to relax the nodes again, if further relaxation
     * is possible this denotes a negative cycle which keeps on decreasing
     */ 
    cout << "\nThis program finds out shortest path between two points in a weighted graph with negative edges or detect a negative cycle (only if directed).\n" << endl;
    int edges;
    cout << "Enter the number of edges to consider: ";
    cin >> edges;

    vector<vector<int>> graph;
    cout << "Enter space seperated vertices & their cost to connect, line delimited for every edge," << endl;
    for (int i = 0; i < edges; i += 1) {
        int u, v, cost;
        cin >> u >> v >> cost;
        graph.push_back({u, v, cost});
    }

    int start;
    cout << "Enter the node from which to start: ";
    cin >> start;

    unordered_map<int, int> distance = bellmanShortestPath(graph, start);

    if (distance.count(0) != 0 && distance[0] == INT_MAX) {
        cout << "\nThis graph contains a negative cycle." << endl;
    } else {
        cout << "\nThe minimum cost to travel to all nodes is," << endl;
        for (auto &[node, cost] : distance) {
            cout << start << " -> " << node << " = " << cost << endl;
        }
    }

    cout << endl;

    return 0;
}

unordered_map<int, int> bellmanShortestPath(vector<vector<int>> &graph, int start) {
    // We use this to maintain distance of every node to start
    unordered_map<int, int> distance;
    int n = graph.size();

    // We initialize the distance from start to all other nodes
    // as Infinite, except start itself which is 0
    for (auto &edge : graph) distance[edge[0]] = INT_MAX;

    distance[start] = 0;

    for (int i = 0; i < n - 1; i += 1) {
        // For a graph with x vertices, the minimal edges needed
        // to traverse all would be x - 1, hence we during each 
        // turn we calculate distance from that specific node
        for (auto &edge : graph) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            // We only consider nodes that have been visited, this
            // includes starting node initially
            if (distance[u] != INT_MAX && distance[u] + wt < distance[v]) {
                // If the cost to reach the neighbour from current node is less
                // than whatever it cost to reach it previously, then we replace it
                distance[v] = distance[u] + wt;
            }
        }
    }

    for (int i = 0; i < n - 1; i += 1) {
        for (auto &edge : graph) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            // If we find another shorter path after our initial
            // iteration, this represents a negative cycle, i.e. a closed
            // loop whose cost decreases more as we loop
            if (distance[u] != INT_MAX && distance[u] + wt < distance[v]) {
                distance[0] = INT_MAX;
                return distance;
            }
        }
    }

    return distance;
}