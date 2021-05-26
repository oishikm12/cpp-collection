#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void depthFirstTraversal(vector<vector<int>>&, int, int);
void breadthFirstTraversal(vector<vector<int>>&, int);

int main() {
    /**
     * There are no direct STL representations to implement a tree
     * As such we use a 2D array to represent various indices as nodes
     * and when two nodes are connected we use a number ~ 1 to represent
     * a connected node. This is similar to matrix representation of graphs
     */
    cout << "\nThis program simulates a tree via STL\n" << endl;
    int n;
    cout << "Enter the number of nodes you would like to consider: ";
    cin >> n;
    
    vector<vector<int>> tree(n + 1);
    cout << "Enter space seperated pairs of n - 1 edges delimited by newline" << endl;
    for (int i = 0; i < n - 1; i += 1) {
        int first, second;
        cin >> first >> second;
        tree[first].push_back(second);
        tree[second].push_back(first);
    }

    cout << "\nDepth First traversal of this tree :" << endl;
    depthFirstTraversal(tree, 1, 1);
    cout << endl;

    cout << "\nBreadth First traversal of this tree :" << endl;
    breadthFirstTraversal(tree, 1);

    cout << endl;

    return 0;
}

void depthFirstTraversal(vector<vector<int>>& tree, int root, int parent) {
    // We print the element in current position first
    // This is essentially a preorder traversal of tree with n nodes
    cout << root << " ";

    for (auto &x : tree[root]) {
        // Since the tree represented is connected to its parent, we
        // continue in case of parent to prevent a loop
        if (x == parent) continue;
        // We recurse where x is the next node, and root becomes the parent
        depthFirstTraversal(tree, x, root);
    }
}

void breadthFirstTraversal(vector<vector<int>>& tree, int root) {
    // Queue is used to store sequence of elements to print
    queue<int> q;
    q.push(root);

    // So that we do not have revisit a parent, we maintain record
    vector<bool> visited(tree.size() * tree.size(), false);

    while (!q.empty()) {
        // We print the current element and mark it as visited
        int curr = q.front();
        q.pop();
        visited[curr] = true;
        cout << curr << " ";

        for (auto &x : tree[curr]) {
            // We then add to queue every child if not visited & the loop continues
            if (visited[x]) continue;
            q.push(x);
        }
    }
}