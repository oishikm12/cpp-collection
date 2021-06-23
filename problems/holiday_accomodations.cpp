#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

int getMaxShuffleDist(unordered_map<int, list<pair<int, int>>> &);
int dfsNodeCost(int, unordered_map<int, bool> &, unordered_map<int, int> &, unordered_map<int, list<pair<int, int>>> &, int &);

int main() {
    /**
     * In order to find out the maximum distance travelled after shuffling
     * we simply need to apply pigeonHole principle to deduce that for every
     * edge the number of crossing shiffles occuring across that edge is 
     * equal to 2 * min(nodes before it, nodes after it)
     */
    cout << "\nThis program finds out the best way to shuffle nodes such that each person travels the maximum distance via the shortest route.\n" << endl; 
    int edges;
    cout << "Enter number of edges to consider: ";
    cin >> edges;

    unordered_map<int, list<pair<int, int>>> graph;

    cout << "Enter space seperated nodes to connect and the distance between them, line delimited for every edge," << endl;
    for (int i = 0; i < edges; i += 1) {
        int u, v, cost;
        cin >> u >> v >> cost;
        graph[u].push_back(make_pair(v, cost));
        graph[v].push_back(make_pair(u, cost));
    }

    int totalDist = getMaxShuffleDist(graph);

    cout << "\n" << totalDist << " is the maximum distance that all the people will have travelled post shuffling." << endl;

    cout << endl;

    return 0;
}

int getMaxShuffleDist(unordered_map<int, list<pair<int, int>>> &graph) {
    // We store this for every node, how many come before it
    // and how many after this node
    unordered_map<int, int> nodeCnt;
    // Here we track visited nodes
    unordered_map<int, bool> visited;

    int distance = 0;
    dfsNodeCost(0, visited, nodeCnt, graph, distance);

    return distance;
}

int dfsNodeCost(int node, unordered_map<int, bool> &visited, unordered_map<int, int> &nodeCnt, unordered_map<int, list<pair<int, int>>> &graph, int &ans) {
    // The current node's count itself is considered as 1
    nodeCnt[node] = 1;
    // We have also visited this node now
    visited[node] = true;

    for (auto &[neighbour, distance] : graph[node]) {
        if (visited[neighbour]) continue;

        // For every neighbour excepting its parent, we simply add
        // whatever count it acquires recursivelly, i.e DFS
        nodeCnt[node] += dfsNodeCost(neighbour, visited, nodeCnt, graph, ans);

        // The resultant sum is calculated using the previous formulae itself
        // It works because of the principle that if for an edge there are two
        // nodes before it and five after, the net shuffle across it can only be
        // 2 values leaving, and 2 new values entering, hence min(before, after) * 2 * distance
        ans += min(nodeCnt[neighbour], (int)visited.size() - nodeCnt[neighbour]) * distance * 2;
    }

    return nodeCnt[node];
}