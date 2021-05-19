#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node() = default;
        Node(int d) : data(d), left(NULL), right(NULL) {}
        ~Node() { delete left, delete right, left = right = NULL; }
};

Node* buildTree();
vector<int> diagonalTraversal(Node *);

int main() {
    /**
     * In order to find out the diagonal traversal of the
     * tree we will use a vector of map in order to figure out which
     * node are present at what horizontal distance from root
     */ 
    cout << "\nThis program prints a binary tree in diagonal manner.\n" << endl;

    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    vector<int> diag = diagonalTraversal(root);

    cout << "\nDiagonal traversal of the tree is :" << endl;
    for (auto &x: diag) cout << x << " ";

    cout << endl << endl;
    delete root;

    return 0;
}

Node* buildTree() {
    int data;
    cin >> data;

    // -1 means an end Node aka leaf
    if (data == -1) return NULL;

    // Recursively build tree
    Node *curr = new Node(data);
    curr->left = buildTree();
    curr->right = buildTree();

    return curr;
}

vector<int> diagonalTraversal(Node *root) {
    // If we place each node according their distance
    // we will need a map of distance to vector
    vector<int> store;
    map<int, vector<int>> dist;

    Node *curr = root;
    queue<pair<Node*, int>> q;
    q.push(make_pair(curr, 0));

    while(!q.empty()) {
        int n = q.size();

        for (int i = 0; i < n; i += 1) {
            curr = q.front().first;
            int currDist = q.front().second;
            q.pop();

            dist[currDist].push_back(curr->data);

            // The difference being right nodes will always inherit the same
            // distance as their parents since they are at the same level
            // diagonally while left node will reduce by 1
            if (curr->left) q.push(make_pair(curr->left, currDist + 1));
            if (curr->right) q.push(make_pair(curr->right, currDist));
        }
    }

    for (auto &x : dist) {
        for (auto &y : x.second) store.push_back(y);
    }
    return store;
}
