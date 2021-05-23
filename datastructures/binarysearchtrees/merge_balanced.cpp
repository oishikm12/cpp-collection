#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node(int val = 0, Node *lc = NULL, Node *rc = NULL) : data(val), left(lc), right(rc) {}
        ~Node() { delete left, delete right, left = right = NULL; }
};

Node* buildBST();
Node* insertInBST(Node*, int);
void levelPrint(Node *);
void inorderStore(Node *, vector<Node *> &);
Node* mergeBalanced(Node *, Node *);
Node* buildBalanced(vector<Node *> &, int, int);

int main() {
    /**
     * In order to merge two balanced trees, we simply
     * find out their respective inorder traversals, and
     * then combine the two sorted arrays, we then combine
     * the two balanced into a single from this array
     */ 
    cout << "\nThis program combines two balanced binary search trees into one.\n" << endl;

    cout << "Enter space seperate elements of the first tree," << endl;
    Node *root1 = buildBST();
    cout << "\nThe first tree looks like," << endl;
    levelPrint(root1);
    cout << endl;

    cout << "Enter space seperate elements of the awxons tree," << endl;
    Node *root2 = buildBST();
    cout << "\nThe seccond tree looks like," << endl;
    levelPrint(root2);
    cout << endl;

    cout << "\nThe tree after combining looks like," << endl;
    Node *root3 = mergeBalanced(root1, root2);
    levelPrint(root3);
    
    cout << endl;
    delete root3;

    return 0;
}

Node* buildBST() {
    // Value of the root node
    int data;
    cin >> data;

    Node *curr = NULL;

    while (data != -1) {
        // We will continue to take user input
        // till user enters -1
        curr = insertInBST(curr, data);
        cin >> data;
    }

    return curr;
}

Node* insertInBST(Node *curr, int data) {
    // If we reach null this becomes desired node
    // to place the value in
    if (!curr) return new Node(data);

    // If data is smaller, it goes into left child
    // else it goes into right child
    if (data <= curr->data) curr->left = insertInBST(curr->left, data);
    else curr->right = insertInBST(curr->right, data);

    return curr;
}

void levelPrint(Node *root) {
    // In order to traverse level wise we use a queue to store 
    // current levels nodes. Since queue is FIFO, this ensures 
    // nodes of a certain level are printed before next level
    queue<Node *> container;

    Node *temp = root;
    container.push(temp);

    while (!container.empty()) {
        // By checking its size we know exactly how many nodes in this level
        int n = container.size();

        while (n--) {
            temp = container.front();
            container.pop();
            cout << temp->data << " ";

            // We check if it has children and accordingly print
            if (temp->left != NULL) container.push(temp->left);
            if (temp->right != NULL) container.push(temp->right);
        }

        cout << endl;
    }
}

void inorderStore(Node *root, vector<Node *> &nodes) {
    // Base case
    if (root==NULL) return;
  
    // Store nodes in Inorder (which is sorted order for BST)
    inorderStore(root->left, nodes);
    nodes.push_back(root);
    inorderStore(root->right, nodes);
}

vector<Node *> mergeSortedArr(vector<Node *> &nodes1, vector<Node *> &nodes2) {
    int n = nodes1.size();
    int m = nodes2.size();

    vector<Node *> res;

    int i = 0, j = 0;

    // Merge function simply pushes the smaller of the 
    // two into the resultant vector and returns it
    while (i < n && j < m) {
        if (nodes1[i]->data < nodes2[j]->data) res.push_back(nodes1[i++]);
        else res.push_back(nodes2[j++]);
    }

    while (i < n) res.push_back(nodes1[i++]);
    while (j < m) res.push_back(nodes2[j++]);

    return res;
}

Node* mergeBalanced(Node *root1, Node *root2) {
    // We store the values in sorted inorder manner
    vector<Node *> nodes1, nodes2;
    inorderStore(root1, nodes1);
    inorderStore(root2, nodes2);

    // This stores the combines sorted nodes
    vector<Node *> sortedNodes = mergeSortedArr(nodes1, nodes2);

    // We call the recursive function to build the tree
    return buildBalanced(sortedNodes, 0, sortedNodes.size() - 1);
}

Node* buildBalanced(vector<Node *> &nodes, int left, int right) {
    // We have hit leaf
    if (left > right) return NULL;

    // Since the nodes are sorted, middle is the
    // middle most value, i.e suitable for root
    int mid = (right - left) / 2 + left;
    Node *root = nodes[mid];

    // We then reconstruct every node to its left
    // and to its right in the same manner
    root->left = buildBalanced(nodes, left, mid - 1);
    root->right = buildBalanced(nodes, mid + 1, right);

    return root;
}