#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int swapsRequired(vector<int> &);

int main() {
    cout << "\nThis program checks the number of swaps to convert a binary tree to binary search tree.\n" << endl;
    int ht;
    cout << "Enter the height of the tree to consider: ";
    cin >> ht;

    // For a complete binary tree, nodes = 2 ^ height - 1
    int n = (1 << ht) - 1;
    vector<int> nodes(n);

    cout << "Enter space seperated nodes of the complete binary tree," << endl;
    for (int i = 0; i < n; i += 1) cin >> nodes[i];

    int swpsReq = swapsRequired(nodes);

    cout << "\nIn order to convert this binary tree to a binary search tree " << swpsReq << " swaps will be required." << endl;

    cout << endl;

    return 0;
}

int swapsRequired(vector<int> &nodes) {
    int n = nodes.size();
    vector<pair<int, int>> posMap(n);

    // This is to store the original position of each element
    for (int i = 0; i < n; i += 1) posMap[i] = make_pair(nodes[i], i);

    // The nodes are now in proper BST inorder format
    sort(posMap.begin(), posMap.end());
    int swps = 0;

    for (int i = 0; i < n; i += 1) {
        // This node is in its correct position
        if (i == posMap[i].second) continue;

        // Placing the element in their correct positions
        swap(posMap[i].first, posMap[posMap[i].second].first);
        swap(posMap[i].second, posMap[posMap[i].second].second);

        // Need to backtrack after swapping
        if (i != posMap[i].second) i -= 1;

        swps += 1;
    }

    return swps;
}