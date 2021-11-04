#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findParent(vector<pair<int, int>> &, int);
void unionByRankCompression(vector<pair<int, int>> &, int, int);
vector<vector<int>> kruskalMST(vector<vector<int>> &, int);

int main() {
    /**
     * Kruskal's algorithm is implemented with the idea of sorting all
     * the edges in a graph based on their weights, and then simply 
     * connecting those nodes in ascending, which do not form a circle
     */ 
    cout << "\nThis program uses Kruskal's Algorithm to find out minimum spanning tree.\n" << endl;
    int vertices, edges;
    cout << "Enter the number of vertices to consider: ";
    cin >> vertices;
    cout << "Enter the number of edges to consider: ";
    cin >> edges;

    vector<vector<int>> graph(edges, vector<int>(3));
    
    cout << "Enter space seperated nodes in a edge and their weights, delimited by newline," << endl;
    for (int i = 0; i < edges; i += 1) cin >> graph[i][0] >> graph[i][1] >> graph[i][2];

    vector<vector<int>> mst = kruskalMST(graph, vertices);

    int sum = 0;
    cout << "\nThe resulting MST is," << endl;
    for (auto &edge : mst) {
        cout << edge[0] << " -> " << edge[1] << " => " << edge[2] << endl;
        sum += edge[2];
    }
    cout << "\nThe cost incurred is: " << sum << "." << endl;

    cout << endl;

    return 0;
}

vector<vector<int>> kruskalMST(vector<vector<int>> &graph, int vertices) {
    // In order to find out minimal cost nodes we need to sort
    // the edges on the basis of ascending travelling cost
    sort(graph.begin(), graph.end(), [](vector<int> &a, vector<int> &b) {
        return a[2] < b[2];
    });

    // Next we maintain parents array, for union finding later
    // We store the node which led to current, and the rank of the node
    // ~ depth of children to whom this node is parent
    // Presently all nodes have themselves as parents, rank as 0
    vector<pair<int, int>> parents(vertices, {0, 0});
    for (int i = 0; i < vertices; i += 1) parents[i].first = i;

    // We need a vector of vector to store valid connections
    vector<vector<int>> result;

    // Currently connected vertices
    int count = 0;
    // Counter to traverse edge list
    int i = 0;

    // Any tree formed in a graph of `x` vertices, can have at most `x - 1` edges
    // otherwise a cycle is formed, and it becomes a graph
    while (count < vertices - 1) {
        vector<int> edge = graph[i++];
        int parentOfFirst = findParent(parents, edge[0]);
        int parentOfSecond = findParent(parents, edge[1]);

        if (parentOfFirst != parentOfSecond) {
            // If their topmost parent do not match, connecting 
            // them does not create a cycle
            result.push_back(edge);
            count += 1;
            // Since these are now the connected, their topmost parent must also match
            unionByRankCompression(parents, parentOfFirst, parentOfSecond);
        }
    }

    return result;
}

int findParent(vector<pair<int, int>> &parents, int curr) {
    // Union Find algorithm allows us to find the union point
    // of two vertices based on their parents, i.e. it finds
    // out the topmost parent of any given vertex
    
    if (parents[curr].first != curr) {
        // Path compression is technique, that assigns parents based on topmost
        // parent while traversal reducing time for subsequent operations
        // In essence, if c -> b -> a, we reduce it to c -> a <- b
        parents[curr].first = findParent(parents, parents[curr].first);
    }

    return parents[curr].first;
}

void unionByRankCompression(vector<pair<int, int>> &parents, int x, int y) {
    // Attach smaller rank tree under root of high rank tree (Union by Rank)
    // Otherwise, if ranks are same, then make one as root and increment its rank by one
    if (parents[x].second < parents[y].second) {
        parents[x].first = y;
    } else if (parents[x].second > parents[y].second) {
        parents[y].first = x;
    } else {
        parents[y].first = x;
        parents[x].second += 1;
    }
}