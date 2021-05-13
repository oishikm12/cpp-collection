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
void mirrorify(Node *, Node *);
void printTree(Node *);

int main() {
    /**
     * In order to mirror a tree, we will simply take in nodes
     * of a tree and then recursively call mirro function while
     * passing left to right and right to left
     */
    cout << "\nThis program creates a mirrored clone of a tree\n" << endl;
    
    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    Node *mirr = new Node();
    mirrorify(root, mirr);

    cout << "\nThe original tree is : " << endl;
    printTree(root);

    cout << "\nThe mirrored tree is : " << endl;
    printTree(mirr);

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

void mirrorify(Node *root, Node *mirr) {
    // Copy the current node's data
    mirr->data = root->data;

    if (root->right) {
        // If we have a left node, we copy it into right node
        mirr->left = new Node();
        mirrorify(root->right, mirr->left);
    }

    if (root->left) {
        // If we have a right node, we copy it into left node
        mirr->right = new Node();
        mirrorify(root->left, mirr->right);
    }
}

void printTree(Node *root) {
    // We use queue to print level wise
    queue<Node*> container;

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