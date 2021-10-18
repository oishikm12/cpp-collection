#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

/**
 * Binary Tree consists of at most two nodes connected to the root
 * Each node then contains its data as well as two or no links to its children
 * A node with no child is a leaf while a node with no parents is root
 */

class Trunk {
    // Helper class for Pretty Printing
    public:
        Trunk *prev;
        string str;

        Trunk(Trunk *p, string s) : prev(p), str(s) {};
};

template <typename T>
class BinaryTree;

template<typename T>
class Node {
    private:
        T data;
        Node<T> *left, *right;

    public:
        // Used to assign value to a node
        Node(T);

        // Deallocate space for Node
        ~Node();

        // Will allow tree to access Nodes
        friend class BinaryTree<T>;
};

template<typename T>
class BinaryTree {
    private:
        Node<T> *ROOT;

    public:
        // Allocates for Binary Tree
        BinaryTree();

        // Deallocates Binary Tree
        ~BinaryTree();

        // Creates a new instance of Binary Tree
        void create();

        // Builds a tree recursively
        Node<T>* buildTree();

        // Caller function
        void preorder();

        // Caller function
        void inorder();

        // Caller function
        void postorder();

        // Traverses the tree in Preorder, ie. root prints first
        void preorderTraversal(Node<T>*);

        // Traverses the tree in Inorder, ie. root prints middle
        void inorderTraversal(Node<T>*);

        // Traverses the tree in Postorder, ie. root prints last
        void postorderTraversal(Node<T>*);

        // Traverses the tree in Preorder iteratively, ie. root prints first
        void preorderIterative();

        // Traverses the tree in Inorder iteratively, ie. root prints middle
        void inorderIterative();

        // Traverses the tree in Postorder iteratively, ie. root prints last
        void postorderIterative();

        // Performs a breadth first traversal, ie. level wise
        void bfs();

        // Returns height of tree
        int getHeight();

        // Finds out height of the tree
        int height(Node<T>*);

        // Prints values at certain level
        void printKthLevel(int);

        // BFS Traversal to a particular level
        void traverseLevels(Node<T>*, int);

        // Return Node count of tree
        int getCount();

        // Counts the number of nodes in tree
        int count(Node<T>*);

        // Wrapper around pretty printing caller
        void print();

        // Prints the tree in a beautiful manner
        void prettyPrintTree(Node<T> *, Trunk *, bool);
};

template <typename T>
Node<T> :: Node(T val) {
    data = val;
    left = NULL;
    right = NULL;
}

template <typename T>
Node<T> :: ~Node() {
    delete left;
    delete right;
    left = NULL;
    right = NULL;
}

template <typename T>
BinaryTree<T> :: BinaryTree() {
    ROOT = NULL;
}

template <typename T>
BinaryTree<T> :: ~BinaryTree() {
    delete ROOT;
    ROOT = NULL;
}

template <typename T>
void BinaryTree<T> :: create() {
    ROOT = buildTree();
}

template <typename T>
Node<T>* BinaryTree<T> :: buildTree() {
    // First take the data from user
    T data;
    cin >> data;

    // This is to ensure that a leaf stays as such
    if (data == -1) return NULL;

    // Recursively build left & right trees
    Node<T> *curr = new Node<T>(data);
    curr->left = buildTree();
    curr->right = buildTree();

    return curr;
}

template <typename T>
void BinaryTree<T> :: preorder() {
    preorderTraversal(ROOT);
    cout << endl;
}

template <typename T>
void BinaryTree<T> :: inorder() {
    inorderTraversal(ROOT);
    cout << endl;
}

template <typename T>
void BinaryTree<T> :: postorder() {
    postorderTraversal(ROOT);
    cout << endl;
}

template <typename T>
void BinaryTree<T> :: preorderTraversal(Node<T> *curr) {
    if (curr != NULL) {
        // Preorder we print the data in current node
        // Then we print from left node, recursively travel to its left
        // Then once no more left nodes remain the right nodes are printed
        cout << curr->data << " ";
        preorderTraversal(curr->left);
        preorderTraversal(curr->right);
    }
}

template <typename T>
void BinaryTree<T> :: inorderTraversal(Node<T> *curr) {
    if (curr != NULL) {
        // Inorder travels to left first ,this continues recursively
        // Once we reach the left most we print current data, move back up
        // Print the data of parent and then print right node's data
        inorderTraversal(curr->left);
        cout << curr->data << " ";
        inorderTraversal(curr->right);
    }
}

template <typename T>
void BinaryTree<T> :: postorderTraversal(Node<T> *curr) {
    if (curr != NULL) {
        // Post order travels to left most node first recursively
        // Once there it travels rightmost recursively
        // There it prints the data and travels up to parent and left
        postorderTraversal(curr->left);
        postorderTraversal(curr->right);
        cout << curr->data << " ";
    }
}

template <typename T>
void BinaryTree<T> :: preorderIterative() {
    if (ROOT == NULL) return;

    // Iterative preorder requires the use of stack to store
    // what we have already traversed and go back to it
    stack<Node<T>*> container;
    Node<T> *temp = ROOT;
    container.push(temp);

    // This is used to store the output
    vector<T> list;

    while(!container.empty()) {
        // Since preorder invloves printing the data first
        // we pop whatever is inside the stack and print its data
        temp = container.top();
        container.pop();
        list.push_back(temp->data);

        // We then move its left & right sub child to the stack
        // Since stack is LIFO, we push left last, so its the
        // first to come out in next iteration as per preorder
        if (temp->right) container.push(temp->right);
        if (temp->left) container.push(temp->left);
    }

    // Printing whatever is inside list
    for (int i = 0; i < list.size(); i += 1) cout << list[i] << (i == list.size() - 1 ? "" : " ");
    cout << endl;
}

template <typename T>
void BinaryTree<T> :: inorderIterative() {
    if (ROOT == NULL) return;

    // Iterative inorder requires the use of stack to store
    // what we have already traversed and go back to it
    stack<Node<T>*> container;
    Node<T> *temp = ROOT;

    // This is used to store the output
    vector<T> list;

    while(temp || !container.empty()) {
        // In case of inorder, we traverse to the leftmost of
        // every node before printing its value & moving right
        while (temp) {
            container.push(temp);
            temp = temp->left;
        }

        // This way we will always have the leftmost value
        temp = container.top();
        container.pop();
        list.push_back(temp->data);

        // After printing data of head we move to its right subtree
        temp = temp->right;
    }

    // Printing whatever is inside list
    for (int i = 0; i < list.size(); i += 1) cout << list[i] << (i == list.size() - 1 ? "" : " ");
    cout << endl;
}

template <typename T>
void BinaryTree<T> :: postorderIterative() {
    if (ROOT == NULL) return;

    // Iterative postorder requires the use of stack to store
    // what we have already traversed and go back to it
    stack<Node<T>*> container;
    Node<T> *temp = ROOT;
    container.push(temp);

    // This is used to store the output
    vector<T> list;

    while(!container.empty()) {
        // Postorder functions in exact reverse of preorder
        // Hence we store the current data in list first
        temp = container.top();
        container.pop();
        list.push_back(temp->data);

        // Since postorder is right first, we push right at the end
        if (temp->left) container.push(temp->left);
        if (temp->right) container.push(temp->right);
    }

    // Printing whatever is inside list in reverse order
    // because postorder reads rightmost first
    for (int i = list.size() - 1; i >= 0; i -= 1) cout << list[i] << (i == 0 ? "" : " ");
    cout << endl;
}

template <typename T>
void BinaryTree<T> :: bfs() {
    // In order to traverse level wise we use a queue to store 
    // current levels nodes. Since queue is FIFO, this ensures 
    // nodes of a certain level are printed before next level
    queue<Node<T>*> container;

    Node<T> *temp = ROOT;
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

template <typename T>
int BinaryTree<T> :: getHeight() {
    return height(ROOT);
}

template <typename T>
int BinaryTree<T> :: height(Node<T> *curr) {
    // Base case for end of recursion
    if (curr == NULL) return 0;
    // We add 1 for current level and recurse till we reach a leaf
    return 1 + max(height(curr->left), height(curr->right));
}

template <typename T>
int BinaryTree<T> :: getCount() {
    return count(ROOT);
}

template <typename T>
int BinaryTree<T> :: count(Node<T> *curr) {
    // Base case for end of recursion
    if (curr == NULL) return 0;
    // We add 1 for node and recurse for left & right child
    return 1 + count(curr->left) + count(curr->right);
}

template <typename T>
void BinaryTree<T> :: printKthLevel(int level) {
    if (level > getHeight()) cout << "Level not found.";
    else traverseLevels(ROOT, level);
    cout << endl;
}

template <typename T>
void BinaryTree<T> :: traverseLevels(Node<T> *curr, int level) {
    if (curr == NULL) return;

    // Eventually level will recurse to 1 at desired level
    if (level == 1) cout << curr->data << " ";

    // After traversing current level we move onto their children
    traverseLevels(curr->left, level - 1);
    traverseLevels(curr->right, level - 1);
}

template <typename T>
void BinaryTree<T> :: print() {
    // Calling the main function passing pointer to previous & direction
    prettyPrintTree(ROOT, NULL, false);
}

template <typename T>
void BinaryTree<T> :: prettyPrintTree(Node<T> *root, Trunk *prev, bool isTop) {
    // This node does not exist, no need to print
    if (root == NULL) return;
 
    // Spacing between previous nodes in this level
    string prevStr = "    ";
    Trunk *trunk = new Trunk(prev, prevStr);
 
    // Inorder Traversal of nodes, so that root comes in middle
    prettyPrintTree(root->right, trunk, true);
 
    if (!prev) {
        // Represents a node at this level
        trunk->str = "---";
    } else if (isTop) {
        // Right node is present to top in horizontal view
        trunk->str = ".---";
        prevStr = "   |";
    } else {
        // Left node is present in bottom in horizontal view
        trunk->str = "`---";
        prev->str = prevStr;
    }

    // We traverse every element in this level
    // and store the strings in a vector, to be
    // printed in reverse order
    Trunk *temp = trunk;
    vector<string> nd;

    while (temp != NULL) {
        nd.push_back(temp->str);
        temp = temp->prev;
    }

    for (int i = nd.size() - 1; i >= 0; i -= 1) cout << nd[i];
    cout << "(" << root->data << ")" << endl;
 
    if (prev) prev->str = prevStr;

    // End of current data, and move to right side
    trunk->str = "   |";
 
    prettyPrintTree(root->left, trunk, false);

    delete trunk;
}

int main() {
    /**
     * We generate an instance of binary tree class and perform operations
     */ 
    cout << "\nThis program generates a sample binary tree object.\n" << endl;
    
    BinaryTree<int> btree;

    cout << "\nEnter space delimited elements of the tree, -1 indicating no element" << endl;
    btree.create();

    cout << "\nHeight of this tree is : " << btree.getHeight() << endl;
    cout << "\nNode count of this tree is : " << btree.getCount() << endl;

    bool flag = true;
    int lvl;

    while(flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Print Preorder Traversal" << endl;
        cout << "2. Print Inorder Traversal" << endl;
        cout << "3. Print Postorder Traversal" << endl;
        cout << "4. Print Breadth First Traversal" << endl;
        cout << "5. Print Specific Level" << endl;
        cout << "6. Pretty Print Tree" << endl;
        cout << "7. Exit" << endl;
        int choice;
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "\nPreorder traversal of this tree :" << endl;
                btree.preorder();
                break;
            case 2:
                cout << "\nInorder traversal of this tree :" << endl;
                btree.inorder();
                break;
            case 3:
                cout << "\nPostorder traversal of this tree :" << endl;
                btree.postorder();
                break;
            case 4:
                cout << "\nBreadth First traversal of this tree :" << endl;
                btree.bfs();
                break;
            case 5:
                cout << "\nEnter level whose elements to print: ";
                cin >> lvl;
                btree.printKthLevel(lvl);
            case 6:
                cout << "\nHorizontal representation of the tree is :" << endl;
                btree.print();
                break;
            case 7:
                cout << "\nGoodbye !!!" << endl;
                flag = !flag;
                break;
            default:
                cout << "\nPlease try again" << endl;
                break;
        }
    }

    cout << endl;

    return 0;
}