#include <iostream>
#include <queue>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node() = default;
        Node(int d) : data(d), left(NULL), right(NULL) {}
        ~Node() {
            delete left;
            delete right;
            left = right = NULL;
        }
};

Node* buildTree();
int replaceSum(Node *);
void printTree(Node *);

int main() {
    /**
     * In order to find the sum of children of a node we can add the
     * current value of node to its child recursively. Starting the 
     * function from root will yield us the sum for each node
     */
    cout << "\nThis program replaces each node with sum of child in a tree\n" << endl;
    
    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    replaceSum(root);

    cout << "\nThe tree is : " << endl;
    printTree(root);

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

int replaceSum(Node *root) {
    // We have reached a leaf node
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return root->data; 

    int leftSum = replaceSum(root->left);
    int rightSum = replaceSum(root->right);

    int temp = root->data;
    // We store the sum of their children in current node, and return the sum
    root->data = leftSum + rightSum;
    return temp + root->data;
}

void printTree(Node *root) {
    // We use queue to print level wise
    queue<Node*> container;

    Node *temp = root;
    container.push(temp);
    // By inserting an extra NULL we can identify when a level changes
    container.push(NULL);

    while (!container.empty()) {
        temp = container.front();
        container.pop();

        if (temp == NULL) {
            cout << endl;
            // There are more levels below, so we use another seperator
            if (!container.empty()) container.push(NULL);
        } else {
            cout << temp->data << " ";
            // We check if it has children and accordingly print
            if (temp->left != NULL) container.push(temp->left);
            if (temp->right != NULL) container.push(temp->right);
        }
    }
}