#include <iostream>
#include <vector>
#include <deque>
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
vector<int> zigZagTraversal(Node *);

int main() {
    /**
     * In order to change direction based on level, we will
     * maintain wether the level is even or odd, and accordingly
     * change pop direction via deque
     */ 
    cout << "\nThis program prints a tree in level order in alternate zig-zag traversal.\n" << endl;

    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    vector<int> zigBfs = zigZagTraversal(root);

    cout << "\nZig-Zag traversal of the tree is :" << endl;
    for (auto &x: zigBfs) cout << x << " ";

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

vector<int> zigZagTraversal(Node *root) {
    vector<int> store;

    // We create an iteration node and insert
    // root into the deque first
    Node *curr = root;
    deque<Node*> dq;
    dq.push_back(curr);

    // For even levels we traverse L to R, so we 
    // use pop_back(), for odd levels we use pop_front()
    int lvl = 0;

    while (!dq.empty()) {
        int n = dq.size();

        for (int i = 0; i < n; i += 1) {
            if (lvl & 1) {
                curr = dq.front();
                dq.pop_front();
                
                // For odd levels since we are traversing from
                // R to L, we need to push elements at the back
                // such that the last element gets accessed by front
                if (curr->right) dq.push_back(curr->right);
                if (curr->left) dq.push_back(curr->left);
            } else {
                curr = dq.back();
                dq.pop_back();

                // For even levels since we are traversing from
                // L to R, we need to push them at the front, such
                // that the last element gets accessed via front
                if (curr->left) dq.push_front(curr->left);
                if (curr->right) dq.push_front(curr->right);
            }

            store.push_back(curr->data);
        }

        lvl += 1;
    }

    return store;
}
