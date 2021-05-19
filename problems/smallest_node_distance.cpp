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
Node* lowestCommonAncestor(Node *, int, int);
int getDist(Node *, int);
int findDist(Node *, int, int);

int main() {
    /**
     * In order to find the distance between two nodes,
     * we will first find the lowest common ancestor
     * between these nodes, and then simply calculate
     * the distance b/w LCA & Node1 + LCA & Node 2
     */
    cout << "\nThis program finds out the least between two nodes in the given tree.\n" << endl; 

    Node *root;
    cout << "Enter elements as requested," << endl;
    root = buildTree();

    int first, second;
    cout << "\nEnter the first node to consider: ";
    cin >> first;
    cout << "\nEnter the second node to consider: ";
    cin >> second;

    int distance = findDist(root, first, second);

    cout << "\nThe least distance between " << first << " and " << second << " is " << distance << "units." << endl;

    cout << endl;
    delete root;

    return 0;
}

Node *buildTree() {
    Node *root = new Node();

    // We ask the user for value of root first
    int data;
    cout << "Enter the value of root: ";
    cin >> root->data;

    // We use BFS traversal to take input
    // -1 represents NULL node
    queue<Node *> q;
    q.push(root);

    while (!q.empty()) {
        int n = q.size();

        // We will iterate for every node in queue
        // and ask if user wants to create left & right child
        for (int i = 0; i < n; i += 1) {
            Node *curr = q.front();
            q.pop();
            int data;

            cout << "Enter the value of left child of " << curr->data << ": ";
            cin >> data;

            if (data != -1) {
                curr->left = new Node(data);
                // We add to queue to create their children
                q.push(curr->left);
            }

            cout << "Enter the value of right child of " << curr->data << ": ";
            cin >> data;

            if (data != -1) {
                curr->right = new Node(data);
                // We add to queue to create their childrens
                q.push(curr->right);
            }
        }
    }

    return root;
}

Node* lowestCommonAncestor(Node *root, int first, int second) {
    // Base condition, when we heat NULL, or find 
    // one of the elements we have to find LCA of
    if (!root || root->data == first || root->data == second) return root;

    // Recursively search for the elements
    // down the tree (postorder)
    Node *left = lowestCommonAncestor(root->left, first, second);
    Node *right = lowestCommonAncestor(root->right, first, second);

    // If we were able to find one of the values, 
    // we return that. This will also handle the 
    // case when we recieve NULL, i.e. this subtree 
    // has none of the desired value
    if (!left) return right;
    if (!right) return left;

    // If at any point we have both left & right,
    // this signifies this is the node where both
    // subtrees meet, and is the lowest common ancestor
    return root;
}

int getDist(Node *root, int val) {
    // This is base for reaching NULL
    if (!root) return -1;
    
    // We found the element, will calculate from here
    if (root->data == val) return 0;
    
    // Recursively call left & right to get dist (post)
    int leftDist = getDist(root->left, val);
    int rightDist = getDist(root->right, val);
    
    // Increment distance since we are moving up levels
    if (leftDist != -1) return leftDist + 1;
    if (rightDist != -1) return rightDist + 1;
    
    // This node is not the correct node
    return -1;
}
 
int findDist(Node *root, int a, int b) {
    // Get their LCA
    Node *ancestor = lowestCommonAncestor(root, a, b);

    // Calculate distance b/w LCA & node1, LCA & node2
    int distance = getDist(ancestor, a) + getDist(ancestor, b);
    
    return distance;
}