#include <iostream>
#include <queue>
#include <vector>
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
vector<int> leftView(Node *);
vector<int> rightView(Node *);
vector<int> topView(Node *);
vector<int> bottomView(Node *);

int main() {
    /**
     * To find out left view & right of a binary tree, we will simply 
     * level order traverse a tree and then print the first element
     * of each level. For top & bottom view, we will maintain max 
     * distance so far & pair node with distance and then accordingly
     * select which node to print
     */
    cout << "\nThis program finds out the directional views of a tree.\n" << endl;
    
    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    vector<int> left = leftView(root);
    vector<int> right = rightView(root);
    vector<int> top = topView(root);
    vector<int> down = bottomView(root);

    cout << "\nThe left view of the tree is :" << endl;
    for (auto &x: left) cout << x << " ";
    cout << "\nThe right view of the tree is :" << endl;
    for (auto &x: right) cout << x << " ";
    cout << "\nThe top view of the tree is :" << endl;
    for (auto &x: top) cout << x << " ";
    cout << "\nThe bottom view of the tree is :" << endl;
    for (auto &x: down) cout << x << " ";

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

vector<int> leftView(Node *root) {
    vector<int> list;
    queue<Node*> q;
   
    if (!root) return list;
   
    Node *curr = root;
    q.push(curr);
   
    while(!q.empty()) {
        // Instead of printing every node in queue
        // We only traverse the current level
        // i.e. number of elements currently in queue
        int n = q.size();
        
        for (int i = 0; i < n; i += 1) {
            curr = q.front();
            q.pop();
            
            // The first node of every level represents the leftmost view
            if (i == 0) list.push_back(curr->data);
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
   
    return list;
}

vector<int> rightView(Node *root) {
    vector<int> list;
    queue<Node*> q;
   
    if (!root) return list;
   
    Node *curr = root;
    q.push(curr);
   
    while(!q.empty()) {
        // Instead of printing every node in queue
        // We only traverse the current level
        // i.e. number of elements currently in queue
        int n = q.size();
        
        for (int i = 0; i < n; i += 1) {
            curr = q.front();
            q.pop();
            
            // The last node of every level represents the rightmost view
            if (i == n - 1) list.push_back(curr->data);
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
   
    return list;
}

vector<int> topView(Node *root) {
    vector<int> store;
    map<int, int> data;

    // In order to decide what the current distance of
    // a node is we pair up each node with what its
    // horizontal distance is from the root (0)
    Node *curr = root;
    queue<pair<Node *, int>> q;
    q.push(make_pair(curr, 0));

    while (!q.empty()) {
        curr = q.front().first;
        int currDist = q.front().second;
        q.pop();
        
        // For this specific distance this stores only
        // the first value of the distance, this ensures
        // only those from top are visible
        if (!data[currDist]) data[currDist] = curr->data;
        
        // Nodes to the left will have a distance 1 less than current
        // to the right will have 1 greater than current
        if (curr->left) q.push(make_pair(curr->left, currDist - 1));
        if (curr->right) q.push(make_pair(curr->right, currDist + 1));
    }

    for (auto &x : data) store.push_back(x.second);
    return store;
}

vector<int> bottomView(Node *root) {
    vector<int> store;
    map<int, int> data;

    // In order to decide what is visible from bottom
    // we maintain a pair of distance from root and the 
    // node itself. Each distance can have one possible node
    Node *curr = root;
    queue<pair<Node*, int>> q;
    q.push(make_pair(curr, 0));

    while (!q.empty()) {
        curr = q.front().first;
        int currDist = q.front().second;
        q.pop();
        
        // For this specific distance this stores the
        // latest value of node, this might get overwritten
        // by another node. This ensures bottom view
        data[currDist] = curr->data;
        
        // Nodes to the left will have a distance 1 less than current
        // to the right will have 1 greater than current
        if (curr->left) q.push(make_pair(curr->left, currDist - 1));
        if (curr->right) q.push(make_pair(curr->right, currDist + 1));
    }

    for (auto &x : data) store.push_back(x.second);
    return store;
}