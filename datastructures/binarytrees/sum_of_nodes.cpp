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
pair<int, bool> sumBalanced(Node *);
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

    bool isSumTree = sumBalanced(root).second;

    if (isSumTree) cout << "\nThe tree is already a sum of it's nodes, re-doing." << endl;

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

pair<int, bool> sumBalanced(Node *root) {
    if (!root) return make_pair(0, true);
    
    pair<int, bool> left = sumBalanced(root->left);
    pair<int, bool> right = sumBalanced(root->right);
    
    int sum = left.first + right.first;
    
    // Checking if this is a leaf node or if sum = left + right
    // We return the sum as first of pair, and wether 
    // this node was a sum tree, as second of pair
    if (sum == 0 || sum == root->data) {
        return make_pair(sum + root->data, left.second && right.second);
    }
    
    return make_pair(sum + root->data, false);
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