#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <stack>
using namespace std;

/**
 * A Graph is a non-linear data structure consisting of nodes and edges. 
 * The nodes are sometimes also referred to as vertices and the edges are 
 * lines or arcs that connect any two nodes in the graph. There can be two 
 * types of graph, one where the edges have values assigned to it, and others
 * where they do not have a value. Furthermore, edges can be unidirectional
 * or bidirectional, determining which nodes can be visited from one
 * Eg:   a --- b      a -> b, c        b -> a, c, d
 *       |  /  |      c -> a, b, d     d -> c, b
 *       c --- d      
 */ 

template <typename T>
class Graph {
    private:
        unordered_map<T, list<T>> data;

    public:
        // Adds an edge to this graph
        void addEdge(T, T, bool = true);

        // Prints all the edges in the graph
        void print();

        // Travels nodes in bfs fashion, i.e. visiting all neighbours
        void breadthFirstTraversal(T);

        // Travels nodes in dfs fashion, i.e. visiting the first neighbour
        // of current before other neighbours, this holds true recursively
        void depthFirstTraversal(T);

        // Checks if the given node is part of graph
        bool search(T);

        // Finds out how many disconnected components are present
        int countComponents();

        // Helper function performing recursive DFS
        void dfsHelper(int, unordered_map<int, bool> &);
};

template <typename T>
void Graph<T> :: addEdge(T start, T end, bool biDiretional) {
    data[start].push_back(end);
    // If the graph is bidirectional, then we connect end to start also
    if (biDiretional) data[end].push_back(start);
}

template <typename T>
void Graph<T> :: print() {
    for (auto &[node, adjacents] : data) {
        cout << node << " -> ";

        // This represents all the nodes connected to current
        // node, and is present in linked list
        auto itr = adjacents.begin();

        while (itr != adjacents.end()) {
            cout << (*itr);
            itr++;
            // This is to prevent printing of comma when at last
            if (itr != adjacents.end()) cout << ", ";
        }

        cout << endl;
    }
}

template <typename T>
void Graph<T> :: breadthFirstTraversal(T start) {
    // A queue allows us to store all adjacent nodes of a node
    queue<T> store;
    // This will allow us to mark already visited nodes
    unordered_map<T, bool> visited;

    // We first insert the starting node
    store.push(start);
    visited[start] = true;

    // We then traverse over contents of queue, i.e. adjacents of node
    while (!store.empty()) {
        T front = store.front();
        store.pop();

        cout << front;

        for (T &neighbour : data[front]) {
            // After printing the current node, we push all the
            // unvisited neighbours of the current node
            if (!visited[neighbour]) {
                store.push(neighbour);
                visited[neighbour] = true;
            }
        }

        if (!store.empty()) cout << ", ";
    }

    cout << endl;
}

template <typename T>
void Graph<T> :: depthFirstTraversal(T start) {
    // Stack allows us to visit the node that is inserted most recently
    // hence travelling to first neighbour before any other
    stack<T> store;
    // This will allow us to mark already visited nodes
    unordered_map<T, bool> visited;

    // We insert the starting node
    store.push(start);
    visited[start] = true;

    // We then traverse over contents of stack, i.e. adjacent of current
    while (!store.empty()) {
        T top = store.top();
        store.pop();

        cout << top;

        for (T &first : data[top]) {
            // After printing the current, we check if any of its neighbours
            // are not visited, and if so push them onto stack
            if (!visited[first]) {
                store.push(first);
                visited[first] = true;
            }
        }

        if (!store.empty()) cout << ", ";
    }

    cout << endl;
}

template <typename T>
bool Graph<T> :: search(T node) {
    return data.count(node) != 0;
}

template <typename T>
void Graph<T> :: dfsHelper(int node, unordered_map<int, bool> &visited) {
    // Marks the current node as visited
    visited[node] = true;

    for (auto &neighbour : data[node]) {
        // For every node that is not visited, recursively travels there
        if (!visited[neighbour]) dfsHelper(neighbour, visited);
    }
}

template <typename T>
int Graph<T> :: countComponents() {
    // Maintains which nodes are visited in graph
    unordered_map<int, bool> visited;
    // Count of individual componenets in graph
    int components = 0;

    for (auto &[node, neighbours] : data) {
        if (!visited[node]) {
            // Each time we encounter a non visited node, we add
            // to our components and perform DFS for all nodes 
            // connected to it, exploring the entire component
            components += 1;
            dfsHelper(node, visited);
        }
    }

    return components;
}

int main() {
    /**
     * We generate a sample instance of Graph & add nodes to it
     */ 
    cout << "\nThis program crates a sample Graph Instance.\n" << endl; 

    Graph<int> grid;

    bool flag = true;

    int val1, val2;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Insert an edge into graph" << endl;
        cout << "2. Print all nodes in graph" << endl;
        cout << "3. Perform BFS from a node" << endl;
        cout << "4. Perform DFS from a node" << endl;
        cout << "5. Exit" << endl;
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter space seperated two nodes to connect," << endl;
                cin >> val1 >> val2;
                grid.addEdge(val1, val2);
                cout << "\n" << val1 << " has been connected to " << val2 << "." << endl;
                break;
            case 2:
                cout << "\nAll nodes in the graph are:" << endl;
                grid.print();
                break;
            case 3:
                cout << "\nEnter the node to start BFS from: ";
                cin >> val1;
                if (grid.search(val1)) {
                    cout << "\nBreadth First Traversal from " << val1 << " is," << endl;
                    grid.breadthFirstTraversal(val1);
                } else {
                    cout << "\n" << val1 << " is not part of the graph." << endl;
                }
                break;
            case 4:
                cout << "\nEnter the node to start DFS from: ";
                cin >> val1;
                if (grid.search(val1)) {
                    cout << "\nDepth First Traversal from " << val1 << " is," << endl;
                    grid.depthFirstTraversal(val1);
                } else {
                    cout << "\n" << val1 << " is not part of the graph." << endl;
                }
                break;
            case 5:
                cout << "\nGoodbye !!!" << endl;
                flag = !flag;
                break;
            default:
                cout << "\nPlease try again" << endl;
                break;
        }
    }

    cout << endl;

    return 0;
}