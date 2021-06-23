#include <iostream>
#include <vector>
using namespace std;

int travellingSalesCost(vector<vector<int>> &, vector<vector<int>> &, int, int);

int main() {
    /**
     * In order to figure out the minimal cost hamiltonian cycle of TSP,
     * we simply use a bitmask to represent visited cities, accordingly at
     * each recursive iteration we find out the travelling cost from current
     * position to its unvisited neighbours, and select the minimal one
     */ 
    cout << "\nThis program finds out the minimal cost incurred by a travelling salesman to visit all cities.\n" << endl;
    int cities;
    cout << "Enter the number of cities to consider: "; 
    cin >> cities;

    vector<vector<int>> graph(cities, vector<int>(cities));
    cout << "Enter space seperated cost to travel from one city to all other cities, line delimited for all cities," << endl;
    for (int i = 0; i < cities; i += 1) for (int j = 0; j < cities; j += 1) cin >> graph[i][j];

    vector<vector<int>> store(cities, vector<int>((1 << cities), -1));

    int minCost = travellingSalesCost(graph, store, 0, 0);

    cout << "\nIt will cost us " << minCost << " to make a round trip from start to all other cities." << endl;

    cout << endl;

    return 0;
}

int travellingSalesCost(vector<vector<int>> &graph, vector<vector<int>> &store, int pos, int mask) {
    int n = graph.size();

    // If all cities have been visited, then the mask will contain
    // only 1s, hence we will simply return cost to reach from last to first
    if (mask == ((1 << n) - 1)) return graph[pos][0];

    // If we have previously calculated minimum down this tree
    if (store[pos][mask] != -1) return store[pos][mask];

    int minCost = INT_MAX;

    // We will try to visit the next unvisited city
    for (int city = 0; city < n; city += 1) {
        if ((mask & (1 << city)) == 0) {
            // If the result is 0, this signifies unvisited city
            // Hence we add the cost to reach this city, and to it, we
            // recurse for next suitable minimum cost destination
            int newCost = graph[pos][city] + travellingSalesCost(graph, store, city, mask | (1 << city));
            minCost = min(minCost, newCost);
        }
    }

    cout << minCost << endl;

    store[pos][mask] = minCost;

    return minCost;
}