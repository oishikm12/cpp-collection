#include <iostream>
#include <list>
#include <unordered_map>
#include <set>
using namespace std;

// Custom Node for edges or destinations of graph
class Trip {
    public: 
        string destination;
        int busCost;
        int flightCost;

        Trip(string dest, int bus, int flight) : destination(dest), busCost(bus), flightCost(flight) {};
};

unordered_map<string, int> dijkstraShortestPath(unordered_map<string, list<Trip>> &, string);
int getMinimalCost(unordered_map<string, list<Trip>> &, string, string);

int main() {
    // In order to find out the minimal cost between two points via a
    // combination of at most one flight and multiple bus trips, we 
    // simply need to use dijkstra's algorithm, one from destination and
    // one from source. Then simply traverse over each node and its
    // neighbours, find out the cost of flight between them, and get
    // the cost of bus between the source / destination & neighbours
    cout << "\nThis program finds out minimal cost from source to destination given bus trip costs and permission to use at most 1 flight trip.\n" << endl;
    int routes;
    cout << "Enter the number of routes to consider: ";
    cin >> routes;

    unordered_map<string, list<Trip>> graph;

    for (int i = 0; i < routes; i += 1) {
        cout << "Enter space seperated source and destinations," << endl;
        string src, dest;
        cin >> src >> dest;
        cout << "Enter space seperated cost for bus & flight between " << src << " and " << dest << "," << endl;
        int bus, flight;
        cin >> bus >> flight;
        graph[src].push_back({dest, bus, flight});
        graph[dest].push_back({src, bus, flight});
    }

    string source, destination;
    cout << "\nEnter the source to depart from: ";
    cin >> source;
    cout << "\nEnter the destination to reach: ";
    cin >> destination;

    int cost = getMinimalCost(graph, source, destination);

    cout << "\nIt will cost at least " << cost << " to reach from " << source << " to " << destination << "." << endl;

    cout << endl;

    return 0;
}

unordered_map<string, int> dijkstraShortestPath(unordered_map<string, list<Trip>> &graph, string start) {
    // We use this to maintain cost of travelling for every node from start
    unordered_map<string, int> cost;

    for (auto &[node, neighbours] : graph) {
        cost[node] = INT_MAX;
    }

    // Since a set is sorted, we can always find out the 
    // node at the minimal distance from the front
    set<pair<int, string>> path;

    cost[start] = 0;
    path.insert(make_pair(0, start));

    // We continue till all have been visited
    while (!path.empty()) {
        // This is the node that is least distance away from start
        auto [currCost, currNode] = *(path.begin());
        // Since we have already processed this distance, we no longer need it
        path.erase(path.begin());

        // Iterate over children over current's neighbours
        for (auto &nextStop : graph[currNode]) {
            // We first check if the cost to travel from current 
            // node to the neighbour addded to the cost of travelling
            // from start to current node, is less than the cost
            // of travelling from start to this node
            if (currCost + nextStop.busCost < cost[nextStop.destination]) {
                // If we do find such a record, we remove it and
                // insert the lesser cost route to the set
                auto existing = path.find(make_pair(cost[nextStop.destination], nextStop.destination));
                if (existing != path.end()) path.erase(existing);

                cost[nextStop.destination] = currCost + nextStop.busCost;
                path.insert(make_pair(cost[nextStop.destination], nextStop.destination));
            }
        }
    }

    return cost;
}

int getMinimalCost(unordered_map<string, list<Trip>> &graph, string source, string destination) {
    // First we generate two distance maps, one from the source, and one from destination
    unordered_map<string, int> sourceCost = dijkstraShortestPath(graph, source);
    unordered_map<string, int> destinationCost = dijkstraShortestPath(graph, destination);

    // The cost with only buses can be derived via simple dijkistra
    int costWithBus = sourceCost[destination];
    
    int costWithPlanesAndBuses = INT_MAX;

    for (auto &[node, neighbours] : graph) {
        // For every neighbour there are three costs involved
        // 1. The cost from source to current node via bus
        // 2. The cost from current node to neighbour via flight
        // 3. The cost from the neighbour to destination via bus
        for (auto &dest : neighbours) {
            int inFlightCost = sourceCost[node] + dest.flightCost + destinationCost[dest.destination];
            costWithPlanesAndBuses = min(costWithPlanesAndBuses, inFlightCost);
        }
    }

    return min(costWithBus, costWithPlanesAndBuses);
}