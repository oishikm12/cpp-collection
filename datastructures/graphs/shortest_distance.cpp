#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
using namespace std;

void printShortestDistances(unordered_map<int, list<int>> &, int);

int main() {
    /**
     * In order to find out the shortest distance between nodes, the best
     * way is to perform breadth first search from the given node, therein
     * the current node is 1 distance away from whatever its parent was
     * from the starting node
     */ 
    cout << "\nThis program finds out the distance between starting node and other nodes.\n" << endl;
    int edges;
    cout << "Enter the number of edges to consider in the graph: ";
    cin >> edges;

    unordered_map<int, list<int>> graph;
    cout << "Enter space seperated vertices to connect, line delimited for every edge," << endl;
    for (int i = 0; i < edges; i += 1) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start;
    cout << "Enter the vertext from where to start calculating distance from: ";
    cin >> start;

    printShortestDistances(graph, start);

    cout << endl;

    return 0;
}

void printShortestDistances(unordered_map<int, list<int>> &graph, int start) {
    // Since we will be travelling breadth first, we need to store all neighbours
    queue<int> store;

    // We will use two maps, one to store the distance from one node to other
    // The other to map every node to its immidiate parent
    unordered_map<int, int> distance;
    unordered_map<int, int> parent;

    // We will set the distance of all nodes to maximum at first,
    // this will allow us to distinguish between unvisited nodes
    for (auto &[node, neighbours] : graph) distance[node] = INT_MAX;

    store.push(start);
    distance[start] = 0;

    // After inserting the first node, we will traverse over all
    // its neighbours and repeat the same
    while (!store.empty()) {
        int curr = store.front();
        store.pop();

        for (auto &neighbour : graph[curr]) {
            if (distance[neighbour] == INT_MAX) {
                // If the current node was not visited before, then 
                // the distance is simply 1 more than whatever its
                // immidiate parent is from the start
                store.push(neighbour);
                distance[neighbour] = distance[curr] + 1;
                parent[neighbour] = curr;
            }
        }
    }

    for (auto &[node, dist] : distance) {
        if (node == start) continue;

        int curr = node;
        while (curr != start) {
            // We simply print the link all the way back to the start
            // we do this by using the map of parents we created earlier
            cout << curr << " -> ";
            curr = parent[curr];
        }
        cout << start << " : " << dist << endl;
    }
}