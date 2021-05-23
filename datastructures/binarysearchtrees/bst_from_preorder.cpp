#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node(int val = 0, Node *lc = NULL, Node *rc = NULL) : data(val), left(lc), right(rc) {}
        ~Node() { delete left, delete right, left = right = NULL; }
};

Node* buildBST(vector<int> &);
Node* insertInBST(Node*, int);
void levelPrint(Node *);

int main() {
    /**
     * In order to find the lowest common ancestor in
     * a binary search tree we simply have to recurse till
     * we find a middle value between the two values
     */ 
    cout << "\nThis program constructs a BST from preorder traversal.\n" << endl;
    int n;
    cout << "Enter number of elements to consider: ";
    cin >> n;

    vector<int> preorder(n);
    cout << "Enter space seperated elements of the preorder traversal," << endl;
    for (int i = 0; i < n; i += 1) cin >> preorder[i];

    Node *root = buildBST(preorder);

    cout << "\nThe tree thus formed is," << endl;
    levelPrint(root);

    cout << endl;
    delete root;

    return 0;
}

Node* buildBST(vector<int> &data) {
    Node *curr = NULL;

    for (auto &x : data) {
        // We will continue to construct tree for all nodes
        curr = insertInBST(curr, x);
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