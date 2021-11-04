#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Edge {
	// Auxillary structure to hold all data about Edges
	public:
		int src, dest, cost, id;
		Edge(int s = 0, int d = 0, int c = 0, int i = 0) : src(s), dest(d), cost(c), id(i) {};
};

int findParent(int, unordered_map<int, int> &);
void tarjanDFS(int, int, int &, vector<int> &, vector<int> &, unordered_map<int, list<pair<int, int>>> &, vector<int> &);

int main() {
	/**
	 * In order to find out the recurrence count of edges in MST of a graph
	 * we simply need to identify Bridge Edges that connect two strongly 
	 * connected components. This can be done via Tarjan's algorithm, and will
	 * represent nodes that will appear in all MSTs, otherwise edges with same cost
	 * that do not form a cycle will appear in some, others will never appear 
	 */
	cout << "\nThis program finds out the recurrence count of edges in any possible MST of a graph.\n" << endl;
	int edges, vertices;
	cout << "Enter the number of edges to consider: ";
	cin >> edges;
	cout << "Enter the number of vertices to consider: ";
	cin >> vertices;

	vector<Edge> edgeList(edges);
	cout << "Enter space seperated, line delimited source, destination & cost of an edge," << endl;
	for (int i = 0; i < edges; i += 1) {
		edgeList[i].id = i;
		cin >> edgeList[i].src >> edgeList[i].dest >> edgeList[i].cost;
	}

	sort(edgeList.begin(), edgeList.end(), [](auto &a, auto &b) {
		// We sort the edges on basis of increasing cost, so that we
		// always choose the edge with least cost
		return a.cost < b.cost;
	});

	// To store the results
	vector<int> result(edges);

	// Stores discovery times of visited vertices, with value as order
    vector<int> disc(vertices, -1);
    // Earliest visited vertex (the vertex with minimum discovery time) 
    // that can be reached from subtree rooted with current vertex
    vector<int> low(vertices, -1);

	// We will use this to keep track of topmost nodes to use in Union Find
	unordered_map<int, int> parents;
	for (auto &x : edgeList) {
		parents[x.src] = x.src;
		parents[x.dest] = x.dest;
	}

	// The main graph substructure
	unordered_map<int, list<pair<int, int>>> graph;

	// Iterating over all edges
	int i = 0;
	while (i < edges) {
		// We do not need to consider the edges with same weight, since they 
		// represent alternatives, and are likely to be present in some MSTs
		int j = i;
		while (j + 1 < edges && edgeList[i].cost == edgeList[j + 1].cost) j += 1;
	
		for (int k = i; k <= j; k += 1) {
			// This is to find out, out of all edges with same cost, which
			// edges will actually be selected in any MST
			Edge currEdge = edgeList[k];

			int parentOfSrc = findParent(currEdge.src, parents);
			int parentOfDest = findParent(currEdge.dest, parents);
		
			if (parentOfSrc == parentOfDest) {
				// This edge will connect already visited Nodes
				// hence we will never include this in any MST
				result[currEdge.id] = 3;
			} else {
				// This node will likely be included in one or more MST
				result[currEdge.id] = 2;
				// By setting these as 0, these become undiscovered, since we 
				// need to find out wether a bridge edge exists between these two components
				disc[parentOfSrc] = 0;
				disc[parentOfDest] = 0;
			}

			// We will reset any already stored possible branch edges
			graph[parentOfSrc].clear();
			graph[parentOfDest].clear();
		}

		for (int k = i; k <= j; k += 1) {
			// This is to recreate the connections between branch edges
			Edge currEdge = edgeList[k];

			int parentOfSrc = findParent(currEdge.src, parents);
			int parentOfDest = findParent(currEdge.dest, parents);
		
			if (parentOfSrc != parentOfDest) {
				graph[parentOfSrc].push_back({parentOfDest, currEdge.id});
				graph[parentOfDest].push_back({parentOfSrc, currEdge.id});
			}
		}

		// Count of vertex discovery, initially 0 before DFS
		int time = 0;

		for (int k = i; k <= j; k += 1) {
			// By performing Tarjan's DFS, we can find out if it is indeed branch edge
			Edge currEdge = edgeList[k];

			int parentOfSrc = findParent(currEdge.src, parents);
			int parentOfDest = findParent(currEdge.dest, parents);
		
			if (!disc[parentOfSrc]) tarjanDFS(parentOfSrc, -1, time, disc, low, graph, result);
		}

		for (int k = i; k <= j; k += 1) {
			// Finally we will join the two parents, since we have now found
			// out if there was a bridge existing between them
			Edge currEdge = edgeList[k];

			int parentOfSrc = findParent(currEdge.src, parents);
			int parentOfDest = findParent(currEdge.dest, parents);

			// Union Algorithm
			parents[parentOfDest] = parentOfSrc;
		}

		// All edges till jth index had same cost as ith index, hence we set it to next
		i = j + 1;
	}

	cout << "\nThe status of each edge in possible MST creation is," << endl;
	for (auto &x : edgeList) {
		string res = result[x.id] == 1 ? "Is present in every MST" : result[x.id] == 2 ? "Is present in at least one MST" : "Is present in no MST";
		cout << x.src << " -> " << x.dest << " : " << res << endl;
	}

	cout << endl;

	return 0;
} 

int findParent(int curr, unordered_map<int, int> &parents) {
    // We need to find the topmost node, this node is part of,
    // int the process we apply path compression such that
    // subsequent operations are faster
    if (parents[curr] != curr) parents[curr] = findParent(parents[curr], parents);
    return parents[curr];
}

void tarjanDFS(int curr, int currIndex, int &time, vector<int> &disc, vector<int> &low, unordered_map<int, list<pair<int, int>>> &graph, vector<int> &result) {
    // Initializing discovery & low value for this node
    time += 1;
    disc[curr] = time;
    low[curr] = time;
	
	// We then traverse over the neighbours of this node
    for (auto &[neighbour, id] : graph[curr]) {
		// This forms a loop
		if (id == currIndex) continue;

        if (disc[neighbour] == 0) {
            // This vertex has not been visited yet, so we recurse in DFS
            tarjanDFS(neighbour, id, time, disc, low, graph, result);
            // Checking if the subtree rooted with 'neighbour' has a
            // connection to one of the ancestors of 'curr', i.e. neigbour
            // will have a lower `low` only if its a part of SCC
            low[curr] = min(low[curr], low[neighbour]);
			// If the low value of neighbour node, is greater than discovery of curr,
			// then this is indeed a bridge edge connecting two components
			// had it not been so, low[neighbour] wouldve been the same as discovery of curr
			if (low[neighbour] > disc[curr]) result[id] = 1;
        } else {
            // Update low value of 'u' only of 'v' is still in stack
            // (i.e. it's a back edge to root, not cross edge to sibling).
            low[curr] = min(low[curr], disc[neighbour]);
        }
    }
}
