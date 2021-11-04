#include <iostream>
#include <list>
#include <unordered_map>
#include <set>
using namespace std;

unordered_map<int, int> dijkstraShortestPath(unordered_map<int, list<pair<int, int>>> &, int);

int main() {
    /**
     * In order to find the shortest distance from starting node, to all
     * other nodes, we use a set to store pair of node & cost to reach it
     * At each iteration we remove the node smallest distance away, and then
     * compare the cost to reach its neighbours via that node with whatever
     * the cost to reach them previously was
     */ 
    cout << "\nThis program finds out shortest path between two points in a weighted graph.\n" << endl;
    int edges;
    cout << "Enter the number of edges to consider: ";
    cin >> edges;

    unordered_map<int, list<pair<int, int>>> graph;
    cout << "Enter space seperated vertices & their cost to connect, line delimited for every edge," << endl;
    for (int i = 0; i < edges; i += 1) {
        int u, v, cost;
        cin >> u >> v >> cost;
        graph[u].push_back(make_pair(v, cost));
        graph[v].push_back(make_pair(u, cost));
    }

    int start;
    cout << "Enter the node from which to start: ";
    cin >> start;

    unordered_map<int, int> distance = dijkstraShortestPath(graph, start);

    cout << "\nThe minimum cost to travel to all nodes is," << endl;
    for (auto &[node, cost] : distance) {
        cout << start << " -> " << node << " = " << cost << endl;
    }

    cout << endl;

    return 0;
}

unordered_map<int, int> dijkstraShortestPath(unordered_map<int, list<pair<int, int>>> &graph, int start) {
    // We use this to maintain distance of every node to start
    unordered_map<int, int> distance;

    for (auto &[node, neighbours] : graph) {
        distance[node] = INT_MAX;
    }

    // Since a set is sorted, we can always find out the 
    // node at the minimal distance from the front
    set<pair<int, int>> path;

    distance[start] = 0;
    path.insert(make_pair(0, start));

    // We continue till all have been visited
    while (!path.empty()) {
        // This is the node that is least distance away from start
        auto [currDist, currNode] = *(path.begin());
        // Since we have already processed this distance, we no longer need it
        path.erase(path.begin());

        // Iterate over children over current's neighbours
        for (auto &[neighbour, costToTravel] : graph[currNode]) {
            // We first check if the cost to travel from current 
            // node to the neighbour addded to the cost of travelling
            // from start to current node, is less than the cost
            // of travelling from start to this node
            if (currDist + costToTravel >= distance[neighbour]) continue;
            
            // If we do find such a record, we remove it and
            // insert the lesser cost route to the set
            auto existing = path.find(make_pair(distance[neighbour], neighbour));
            if (existing != path.end()) path.erase(existing);

            distance[neighbour] = currDist + costToTravel;
            path.insert(make_pair(distance[neighbour], neighbour));
        }
    }

    return distance;
}