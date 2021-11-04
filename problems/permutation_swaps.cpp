#include <iostream>
#include <vector>
#include <set>
using namespace std;

void depthFirstSearch(int, vector<vector<int>> &, vector<bool> &, vector<int> &);

int main() {
    /**
     * In order to find out if one can be converted into the other,
     * we create a Graph from the swappable indices, to find out 
     * connected components in it. If the all the elements in the 
     * connected components are present in both the lists, in the same
     * range, then it is convertable
     */ 
    cout << "\nThis program finds out if one list can be converted to other via series of swaps.\n" << endl;
    
    int n;
    cout << "Enter size of lists to consider: ";
    cin >> n;

    vector<int> arrOne(n), arrTwo(n);
    cout << "\nEnter space seperated elements of the first list," << endl;
    for (auto &x : arrOne) cin >> x;
    cout << "\nEnter space seperated elements of the second list," << endl;
    for (auto &x : arrTwo) cin >> x;

    int q;
    cout << "\nEnter number of pairs of swappable indices: ";
    cin >> q;

    vector<vector<int>> graph(n);
    cout << "Enter space seperated line delimited pairs of swappable indices," << endl;
    for (int i = 0; i < q; i += 1) {
        int id1, id2;
        cin >> id1 >> id2;
        graph[id1 - 1].push_back(id2 - 1);
        graph[id2 - 1].push_back(id1 - 1);
    }

    // We will store components here
    vector<vector<int>> components;
    // Visited will track all the componets yet to visit
    vector<bool> visited(n, false);
    // We will use depth first search to find all connected components
    for (int i = 0; i < n; i += 1) {
        // Already a part of a component
        if (visited[i]) continue;

        // To store the components temporarily
        vector<int> component;
        depthFirstSearch(i, graph, visited, component);

        components.push_back(component);
    }

    // We need to check if the same elements are present in both, hence set
    set<int> first, second;
    bool flag = false;

    for (auto &component : components) {
        for (auto &index : component) {
            // Insert the corresponding elements in these indices
            first.insert(arrOne[index]);
            second.insert(arrTwo[index]);
        }

        if (first != second) {
            // Since they are not equal, the two list cannot be interconverted
            flag = true;
            break;
        }

        // We need to reset the sets for next turn
        first.clear();
        second.clear();
    }

    if (flag) cout << "\nThe first list cannot be converted to the second by any number of swaps." << endl;
    else cout << "\nThe first list can be converted to the second." << endl;

    cout << endl;

    return 0;
}

void depthFirstSearch(int curr, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &component) {
    // Marking this node as visited and pushing this into current component
    visited[curr] = true;
    component.push_back(curr);

    for (auto &neighbour : graph[curr]) {
        // We have already visited this node
        if (visited[neighbour]) continue;
        depthFirstSearch(neighbour, graph, visited, component);
    }
}