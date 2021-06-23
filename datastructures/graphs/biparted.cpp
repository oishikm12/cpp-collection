#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
using namespace std;

bool checkBiColoring(unordered_map<int, list<int>> &, int);

int main() {
    /**
     * In order to check if a graph is biparted or not, we perform
     * a BFS traversal on it wherein we expect the nodes on a certain
     * level to have different color when compared to next level. This
     * way, nodes without a direct connection will have same colors
     */ 
    cout << "\nThis program finds out if a graph is biparted or not.\n" << endl;
    int edges;
    cout << "Enter the number of edges to consider: ";
    cin >> edges;

    unordered_map<int, list<int>> graph;
    int start = INT_MAX;
    cout << "Enter space seperated vertices to connect, line delimited for every edge," << endl;
    for (int i = 0; i < edges; i += 1) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);

        if (start == INT_MAX) start = u;
    }

    bool isBiParted = checkBiColoring(graph, start);

    if (isBiParted) cout << "\nThe graph is a biparted graph." << endl;
    else cout << "\nThe graph is not biparted." << endl;

    cout << endl;

    return 0;
}

bool checkBiColoring(unordered_map<int, list<int>> &graph, int start) {
    // We use this to mark colors of each node
    unordered_map<int, int> colors;

    for (auto &[node, neighbours] : graph) {
        // We traverse over all nodes and its neighbours 
        // setting the colors parameter to -1, i.e. unvisited
        colors[node] = -1;
        for (auto &neighbour : neighbours) colors[neighbour] = -1;
    }

    queue<int> store;
    // We push the starting node into the queue, and
    // mark it with a color
    store.push(start);
    colors[start] = 0;

    while (!store.empty()) {
        int front = store.front();
        store.pop();

        // We traverse over all neighbours of the current node
        // and while pushing them into queue, give them alternate
        // colors as our current one, placing them in the other group
        for (auto &neighbour : graph[front]) {
            if (colors[neighbour] == -1) {
                colors[neighbour] = 1 - colors[front];
                store.push(neighbour);
            } else if (colors[neighbour] == colors[front]) {
                // If we come across a node that was previously colored,
                // however that color matches with its immidiate neighbour
                // then the graph is not biparted
                return false;
            }
        }
    }

    return true;
}