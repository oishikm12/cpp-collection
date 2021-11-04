#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <stack>
using namespace std;

void tarjanDFS(int, vector<int> &, vector<int> &, vector<bool> &, stack<int> &, unordered_map<int, list<int>> &, vector<vector<int>> &);

int main() {
    /**
     * Tarjan Algorithm is based on following facts: 
     * 1. DFS search produces a DFS tree/forest 
     * 2. SCC form subtrees of the DFS tree. 
     * 3. If we can find the head of such subtrees, we find a SCC
     * 4. There is no back edge from one SCC to another
     * At any given point if discovery[node] == low[node] then we found a head
     */ 
    cout << "\nThis problem finds out Strongly Connected Components via Tarjan's Algorithm.\n" << endl;
    int edges, vertices;
    cout << "Enter number of edges to consider: ";
    cin >> edges;
    cout << "Enter number of vertices to consider: ";
    cin >> vertices;

    unordered_map<int, list<int>> graph;
    cout << "Enter space seperated line delimited edges to connect in this graph," << endl;
    for (int i = 0; i < edges; i += 1) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    // Stores discovery times of visited vertices, with value as order
    vector<int> discovery(vertices, -1);
    // Earliest visited vertex (the vertex with minimum discovery time) 
    // that can be reached from subtree rooted with current vertex
    vector<int> lowestReachableAncestor(vertices, -1);
    // Tells us if the current vertex is currently in stack
    vector<bool> stackMember(vertices, false);
    // To store all the connected ancestors (could be part of SCC)
    stack<int> store;

    cout << "\nThe strongly connected componenets are," << endl;
    for (int i = 0; i < vertices; i += 1) {
        if (discovery[i] != -1) continue;

        vector<vector<int>> result;
        tarjanDFS(i, discovery, lowestReachableAncestor, stackMember, store, graph, result);
        for (auto &x : result) {
            for (auto &y : x) cout << y << ' ';
            cout << endl;
        }
    }

    cout << endl;

    return 0;
}

void tarjanDFS(int curr, vector<int> &disc, vector<int> &low, vector<bool> &stackMember, stack<int> &store, unordered_map<int, list<int>> &graph, vector<vector<int>> &result) {
    // A static variable is used as an indicator of time of discovery
    static int time = 0;

    // Initializing discovery & low value for this node
    time += 1;
    disc[curr] = time;
    low[curr] = time;

    // Adding current vertex to stack
    store.push(curr);
    stackMember[curr] = true;

    for (auto &neighbour : graph[curr]) {
        // We traverse all vertices adjacent to current node
        if (disc[neighbour] == -1) {
            // This vertex has not been visited yet, so we recurse in DFS
            tarjanDFS(neighbour, disc, low, stackMember, store, graph, result);
            // Checking if the subtree rooted with 'neighbour' has a
            // connection to one of the ancestors of 'curr', i.e. neigbour
            // will have a lower `low` only if its a part of SCC
            low[curr] = min(low[curr], low[neighbour]);
        } else {
            // Update low value of 'u' only of 'v' is still in stack
            // (i.e. it's a back edge to root, not cross edge to sibling).
            if (stackMember[neighbour]) low[curr] = min(low[curr], disc[neighbour]);
        }
    }

    // If the Earliest Visited time & discovery time matches for 
    // this vertex, then this is a head node of subtree & SCC is found
    if (low[curr] == disc[curr]) {
        vector<int> temp;

        // All the nodes visited in subtree are present in stack
        while (store.top() != curr) {
            temp.push_back(store.top());
            stackMember[store.top()] = false;
            store.pop();
        }

        // We also include the head of the subtree in the SCC
        temp.push_back(store.top());
        stackMember[store.top()] = false;
        store.pop();

        // Finally we add this to the result
        result.push_back(temp);
    }
}