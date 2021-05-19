#include <iostream>
#include <vector>
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
bool check(Node *);

int main() {
    /**
     * In order to check wether all leafs are at the same
     * level, we will simply use BFS to maintain the fact
     * wether all the nodes at current level have a child or not
     */
    cout << "\nThis program tells us if all the leaves of a tree are at the same level or not.\n" << endl; 

    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    bool isLeafy = check(root);

    if (isLeafy) cout << "\nThis tree has all the leaves at the same level." << endl;
    else cout << "\nThis tree has leaves at different levels." << endl;

    cout << endl;
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

bool check(Node *root) {
    if (!root || (!root->left && !root->right)) return false;
    
    // We use simple breathfirst traversal
    queue<Node *> q;
    Node* temp = root;
    q.push(root);
    
    bool sameLevel = true;
    
    while (!q.empty()) {
        int level = q.size();

        for(int i=0;i<level;i++){
            Node* curr = q.front();
            q.pop();    
            
            if(!curr->left && !curr->right){
                // If we do not the nodes at same level than
                // samelevel will be set to true only so that 
                // means no 2 nodes are having leaf node at same level.
                if(sameLevel && i != 0) return false;
                sameLevel = false;
            } else if(!sameLevel) {
                // If the leafnode is already received for 
                // the situation we are handling this
                return false;
            }
            
            if(curr->left) q.push(curr->left);
            if(curr->right) q.push(curr->right);
        }
    }

    return true;
}