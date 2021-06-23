#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

void dfsHelper(int, unordered_map<int, list<int>> &, unordered_map<int, bool> &, list<int> &);
list<int> topologicalSort(unordered_map<int, list<int>> &);
list<int> topoSortKahn(unordered_map<int, list<int>> &);

int main() {
    /**
     * In topological sort, we print the elements of a directed acyclic
     * graph in such a manner such that every element can only share an
     * edge with those elements coming after it
     */ 
    cout << "\nThis program performs topological sort via DFS & BFS(Kahn) on a graph.\n" << endl;
    int edges;
    cout << "Enter number of edges to consider: ";
    cin >> edges;

    unordered_map<int, list<int>> graph;
    cout << "Enter space seperated vertices to connect, line delimited for every edge," << endl;
    for (int i = 0; i < edges; i += 1) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    list<int> dfsTopo = topologicalSort(graph);
    list<int> bfsTopo = topoSortKahn(graph);

    cout << "\nThe elements in topological ordering (DFS) are," << endl;
    for (auto &nodes : dfsTopo) cout << nodes << " ";
    cout << "\nThe elements in topological ordering (BFS) are," << endl;
    for (auto &nodes : bfsTopo) cout << nodes << " ";

    cout << endl;

    return 0;
}

list<int> topologicalSort(unordered_map<int, list<int>> &graph) {
    // We maintain the topological ordering in a list
    list<int> order;
    // This marks already visited node as true
    unordered_map<int, bool> visited;

    // For every yet unvisited node, we recursively call the DFS function
    for (auto &[node, neighbours] : graph) {
        if (!visited[node]) dfsHelper(node, graph, visited, order);
    }

    return order;
}

void dfsHelper(int node, unordered_map<int, list<int>> &graph, unordered_map<int, bool> &visited, list<int> &order) {
    // Set the current node as visited
    visited[node] = true;

    // We then call the same function recursively for its unvisited neighbours
    for (auto neighbour : graph[node]) {
        if (!visited[neighbour]) dfsHelper(neighbour, graph, visited, order);
    }

    // At this point all the children for this node have already been
    // visited, so we add the current in front of them in the list
    order.push_front(node);
}

list<int> topoSortKahn(unordered_map<int, list<int>> &graph) {
    // This allows us to perform BFS
    queue<int> store;

    // Visited keeps tracks of already visited nodes, and inDegree
    // counts the number of edges pointed towards current node
    unordered_map<int, bool> visited;
    unordered_map<int, int> inDegree;

    // We traverse all nodes to count their inDegrees
    for (auto &[node, neighbours] : graph) {
        // If there are no records of current node, we insert 0 for it
        if (inDegree.count(node) == 0) inDegree[node] = 0;
        // We simply traverse through all children of current node
        // and increase their inDegree by 1
        for (auto &neighbour : neighbours) inDegree[neighbour] += 1;
    }

    // We start traversing from the nodes with an indegree of 0
    // since these do not have dependencies
    for (auto &[node, degree] : inDegree) {
        if (degree == 0) store.push(node);
    }

    list<int> result;

    while (!store.empty()) {
        // We pop the frontmost element, and reduce the inDegree
        // of all those nodes conneted to it by 1
        result.push_back(store.front());
        store.pop();

        for (auto &neighbour : graph[result.back()]) {
            inDegree[neighbour] -= 1;
            // If this node has 0 indegree, then we place this in the
            // topological order, since it has no dependencies
            if (inDegree[neighbour] == 0) store.push(neighbour);
        }
    }

    return result;
}