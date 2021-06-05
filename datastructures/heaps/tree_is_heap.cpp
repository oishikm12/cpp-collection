#include <iostream>
#include <queue>
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
bool isMaxHeap(Node*);

int main() {
    /**
     * Checking wether a tree is a maxheap or not, involves, checking
     * that all children of a node are less than it or not and that the
     * tree itself is complete. This can be done with breadth first 
     * traversal of the tree ensuring every node has 2 children or it
     * does not, no node after it has children
     */ 
    cout << "\nThis program checks wether a binary tree is a heap or not.\n" << endl;

    cout << "Enter space seperated elements of the tree," << endl;
    Node *root = buildTree();

    bool isHeap = isMaxHeap(root);

    if (isHeap) cout << "\nThe given tree is a max heap." << endl;
    else cout << "\nThe given tree is not a heap." << endl;

    cout << endl;

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

bool isMaxHeap(Node *tree) {
    Node *temp = tree;

    // By using a queue to store node, we can implement BFS
    queue<Node*> store;
    store.push(temp);
    
    bool isLeaf = false;

    while (!store.empty()) {
        temp = store.front();
        store.pop();
        
        // For every node we check if the data in its child is 
        // greater, and if so heap property is not true
        if (temp->left) {
            if (isLeaf || temp->left->data >= temp->data) return false;
            store.push(temp->left);
        } else {
            isLeaf = true;
        }
        
        // If the node does not have a child, then we assume
        // its a leaf node, and as such no other node after it
        // should have a child either
        if (temp->right) {
            if (isLeaf || temp->right->data >= temp->data) return false;
            store.push(temp->right);
        } else {
            isLeaf = true;
        }
    }
    
    return true;
}