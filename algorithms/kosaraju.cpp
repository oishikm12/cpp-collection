#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <stack>
using namespace std;

bool checkStrongConnection(unordered_map<int, list<int>> &);
void dfsTraversal(int, unordered_map<int, bool> &, unordered_map<int, list<int>> &);
unordered_map<int, list<int>> reversal(unordered_map<int, list<int>> &);
vector<vector<int>> strongComponents(unordered_map<int, list<int>> &);
void dfsIntoStack(int, unordered_map<int, list<int>> &, unordered_map<int, bool> &, stack<int> &);
void dfsFromStack(int , unordered_map<int, list<int>> &, unordered_map<int, bool> &, vector<int> &);

int main() {
    /**
     * This algorithm simply uses DFS to visit all the nodes from start
     * If we can visit all the nodes, then we reverse, i.e. transpose
     * and then try to revisit all the nodes via DFS from the same start
     * If successfull, the graph is considered to be strongly connected
     */ 
    cout << "\nThis program checks if a given graph is strongly connected via Kosaraju's Algorithm.\n" << endl;
    int edges;
    cout << "Enter the number of edges to consider: ";
    cin >> edges;

    unordered_map<int, list<int>> graph;
    
    cout << "Enter space seperated edges, delimited by lines," << endl;
    for (int i = 0; i < edges; i += 1) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    bool isSC = checkStrongConnection(graph);

    if (isSC) cout << "\nThe graph is strongly connected." << endl;
    else {
        cout << "\nThe graph is not strongly connected." << endl;

        vector<vector<int>> components = strongComponents(graph);

        if (components.size() == 0) cout << "\nThere are no strongly connected components either." << endl;
        else {
            cout << "\nThere are strongly connected components though," << endl;
            for (auto &x : components) {
                for (auto &y : x) cout << y << ' ';
                cout << endl;
            }
        }
    }

    cout << endl;

    return 0;
}

bool checkStrongConnection(unordered_map<int, list<int>> &graph) {
    // This keeps track of all the nodes present
    unordered_map<int, bool> visited;
    // We chose an arbitary node as our starting point
    // Since all nodes should be reachable if strongly connected
    // starting node should not matter
    auto start = graph.begin()->first;

    for (auto &[node, neighbours] : graph) {
        // We traverse over all nodes and its neighbours 
        // setting the visited parameter to false
        visited[node] = false;
        for (auto &neighbour : neighbours) visited[neighbour] = false;
    }

    dfsTraversal(start, visited, graph);

    for (auto &[node, vis] : visited) {
        // After dfs traversal, we check if any node remains unreachable,
        // if so, then the graph is not strongly connected
        if (!vis) return false;
        // If it was reachable, we reset the visited status to false
        vis = false;
    }

    unordered_map<int, list<int>> reversedGraph = reversal(graph);

    dfsTraversal(start, visited, reversedGraph);

    for (auto &[node, vis] : visited) {
        // If a node is not visited, after reversal of edges, the graph is
        // not strongly connected, since the path b/w two nodes is unidirectional
        if (!vis) return false;
    }

    return true;
}

void dfsTraversal(int node, unordered_map<int, bool> &visited, unordered_map<int, list<int>> &graph) {
    // We mark the current node as traversed and visited
    visited[node] = true;

    for (auto &neighbour : graph[node]) {
        // We then simply check if any of its neighbours hav'nt been visited
        // and if so we simply recurse to traverse that node
        if (visited[neighbour]) continue;
        dfsTraversal(neighbour, visited, graph);
    }
}

unordered_map<int, list<int>> reversal(unordered_map<int, list<int>> &graph) {
    unordered_map<int, list<int>> reversedGraph;

    for (auto &[node, neighbours] : graph) {
        for (auto &neighbour : neighbours) {
            // In order to reverse the graph, we simply push the node,
            // into the adjacency list of neighbours
            reversedGraph[neighbour].push_back(node);
        }
    }

    return reversedGraph;
}

vector<vector<int>> strongComponents(unordered_map<int, list<int>> &graph) {
    // We will store the order of node visits in this stack
    stack<int> container;
    // We will store all components here
    vector<vector<int>> result;

    // This keeps track of all the nodes present
    unordered_map<int, bool> visited;

    for (auto &[node, neighbours] : graph) {
        // We traverse over all nodes and its neighbours 
        // setting the visited parameter to false
        visited[node] = false;
        for (auto &neighbour : neighbours) visited[neighbour] = false;
    }

    // We now perform normal DFS on the graph to get all connected components
    for (auto &[node, vis] : visited) {
        if (!vis) dfsIntoStack(node, graph, visited, container);
    }

    unordered_map<int, list<int>> reversedGraph = reversal(graph);
    
    // For the next DFS, we reset the visited values
    for (auto &[_, vis] : visited) vis = false;

    // We then pop one element by element from the stack, and then
    // print all the strongly connected nodes to it
    while (!container.empty()) {
        int curr = container.top();
        container.pop();

        if (visited[curr]) continue;

        vector<int> component;
        dfsFromStack(curr, reversedGraph, visited, component);

        result.push_back(component);
    }

    return result;
}

void dfsIntoStack(int node, unordered_map<int, list<int>> &graph, unordered_map<int, bool> &visited, stack<int> &container) {
    // We mark the current node as traversed and visited
    visited[node] = true;

    for (auto &neighbour : graph[node]) {
        // We then simply check if any of its neighbours hav'nt been visited
        // and if so we simply recurse to traverse that node
        if (visited[neighbour]) continue;
        dfsIntoStack(neighbour, graph, visited, container);
    }

    // We then push the current node, after traversing all its neighbours into stack
    container.push(node);
}

void dfsFromStack(int node, unordered_map<int, list<int>> &graph, unordered_map<int, bool> &visited, vector<int> &component) {
    // We mark the current node as traversed and visited
    visited[node] = true;
    // We add this element to current strong component
    component.push_back(node);

    for (auto &neighbour : graph[node]) {
        // We then simply check if any of its neighbours hav'nt been visited
        // and if so we simply recurse to traverse that node
        if (visited[neighbour]) continue;
        dfsFromStack(neighbour, graph, visited, component);
    }
}