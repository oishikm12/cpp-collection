#include <iostream>
#include <vector>
using namespace std;

/**
 * An AVL tree is essentially the same as a binary search
 * tree, however, after every insertion, the tree is rotated 
 * to ensure that the balanced property of tree is maintained
 */ 

class Trunk {
    // Helper class for Pretty Printing
    public:
        Trunk *prev;
        string str;

        Trunk(Trunk *p, string s) : prev(p), str(s) {};
};

template <typename T>
class AVLTree;

template<typename T>
class Node {
    private:
        T data;
        int height;
        Node<T> *left, *right;

    public:
        // Used to assign value to a node
        Node(T);

        // Deallocate space for Node
        ~Node();

        // Will allow tree to access Nodes
        friend class AVLTree<T>;
};

template <typename T>
class AVLTree {
    private:
        Node<T> *ROOT;

    public:
        // Allocates for AVL Tree
        AVLTree();

        // Deallocates AVL Tree
        ~AVLTree();

        // Creates a new instance of AVL Tree
        void create(vector<T>);

        // Inserts an element into the Tree
        Node<T>* insert(Node<T> *, T);

        // Removes elements from Tree
        void destroy(vector<T>);

        // Deletes a node
        Node<T>* delNode(Node<T> *, T);

        // Retrieves the minimal node, reachable from current
        Node<T>* getMinNode(Node<T> *);

        // Finds out the height of a node
        int getHeight(Node<T> *);

        // Gets height of whole tree
        int height();

        // Finds out the balance factor of a node
        int getBalance(Node<T> *);

        // Balances a tree
        Node<T>* balance(Node<T> *);

        // Rotates a tree to its left
        Node<T>* leftRotate(Node<T> *);

        // Rotates a tree to its right
        Node<T>* rightRotate(Node<T> *);

        // Finds an element, wrapper for search
        bool find(T);

        // Searches for an element
        bool search(Node<T> *, T);

        // Wrapper around pretty printing caller
        void print();

        // Prints the tree in a beautiful manner
        void prettyPrintTree(Node<T> *, Trunk *, bool);
};

template <typename T>
Node<T> :: Node(T val) {
    data = val;
    // Every node is initially a leaf
    height = 1;
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
AVLTree<T> :: AVLTree() {
    ROOT = NULL;
}

template <typename T>
AVLTree<T> :: ~AVLTree() {
    delete ROOT;
    ROOT = NULL;
}

template <typename T>
void AVLTree<T> :: create(vector<T> elems) {
    // We simply iterate over all elements and insert them
    for (auto &x : elems) ROOT = insert(ROOT, x);
}

template <typename T>
Node<T>* AVLTree<T> :: insert(Node<T> *curr, T val) {
    // This is a leaf, hence normal insertion
    if (!curr) return new Node<T>(val);

    // Basic BST property is followed, where smaller
    // goes left & bigger to the right, duplicates are not allowed
    if (val < curr->data) curr->left = insert(curr->left, val);
    else if (val > curr->data) curr->right = insert(curr->right, val);
    else return curr;

    // After insertion, we update the height of ancestor nodes
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));

    // We check if this node is still balanced
    return balance(curr);
}

template <typename T>
void AVLTree<T> :: destroy(vector<T> elems) {
    // We simply iterate over all elements and delete them
    for (auto &x : elems) ROOT = delNode(ROOT, x);
}

template <typename T> 
Node<T>* AVLTree<T> :: delNode(Node<T> *curr, T val) {
    // Recursive case when we reach leaf
    if (curr == NULL) return curr;
 
    // If the key to be deleted is smaller than the curr's key,
    // then it lies in left subtree
    if (val < curr->data) curr->left = delNode(curr->left, val);
    // If the key to be deleted is greater than the curr's key,
    // then it lies in right subtree
    else if (val > curr->data) curr->right = delNode(curr->right, val);
    // If key is same as curr's key, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if(!curr->left || !curr->right) {
            Node<T> *temp = curr->left ? curr->left : curr->right;
 
            // One child case, hence removing link
            if (temp != NULL) curr->left = curr->right = NULL;

            // We then delete the current node, and point it to temp
            // For one child, it becomes the new curr, for no child, NULL
            delete curr;
            curr = temp;
        } else {
            // For nodes with 2 children, we get smallest in right subtree
            // i.e. inorder successor of current node
            Node<T>* temp = getMinNode(curr->right);
 
            // We then copy the inorder successors data to current node
            curr->data = temp->data;
            // And then delete the inorder successor instead
            curr->right = delNode(curr->right, temp->data);
        }
    }

    // If there is no element remaining
    if (!curr) return curr;

    // We then update the heights of current node
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));

    // We check if this node is still balanced
    return balance(curr);
}

template <typename T> 
Node<T>* AVLTree<T> :: getMinNode(Node<T> *curr) {
    Node<T> *temp = curr;
    // Loop down to find the leftmost leaf
    while (temp->left) temp = temp->left;
 
    return temp;
}

template <typename T>
int AVLTree<T> :: getHeight(Node<T> *curr) {
    // Simply access height property if present
    if (!curr) return 0;
    return curr->height;
}

template <typename T>
int AVLTree<T> :: height() {
    return getHeight(ROOT);
}

template <typename T>
int AVLTree<T> :: getBalance(Node<T> *curr) {
    // A positive balance represents longer left subtree
    // a longer right subtree for the alternative
    if (!curr) return 0;
    return getHeight(curr->left) - getHeight(curr->right);
}

template <typename T>
Node<T>* AVLTree<T> :: balance(Node<T> *curr) {
    // We check the balance factor to check if it is
    // unbalanced and in need of rotation
    int balance = getBalance(curr);

    // Case 1: Left Subtree has extra nodes & 
    //         new value is smaller than left node
    if (balance > 1 && getBalance(curr->left) >= 0) {
        // We rotate the curr subtree to its right
        return rightRotate(curr);
    }

    // Case 2: Left Subtree has extra nodes &
    //         new value is larger than left node
    if (balance > 1 && getBalance(curr->left) < 0) {
        // We first rotate the left subtree to its left,
        // then rotate curr subtree to its right
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }

    // Case 3: Right Subtree has extra nodes & 
    //         new value is larger than right node
    if (balance < -1 && getBalance(curr->right) <= 0) {
        // We rotate the curr subtree to its left
        return leftRotate(curr);
    }

    // Case 4: Right Subtree has extra nodes & 
    //         new value is smaller than right node
    if (balance < -1 && getBalance(curr->right) > 0) {
        // We first rotate the right subtree to its right,
        // then rotate curr subtree to its left
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }

    // Otherwise the node is balanced
    return curr;
}

template <typename T>
Node<T>* AVLTree<T> :: leftRotate(Node<T> *curr) {
    Node<T> *rightSubtree = curr->right;
    Node<T> *leftOfRight = rightSubtree->left;
 
    // Left rotation is performed by making the right subtree the 
    // new root, where current root is attached to its left, and the
    // left of the right subtree is attached to current roots right
    rightSubtree->left = curr;
    curr->right = leftOfRight;
 
    // Updating the resultant heights
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    rightSubtree->height = 1 + max(getHeight(rightSubtree->left), getHeight(rightSubtree->right));
 
    // Return new root
    return rightSubtree;
}

template <typename T>
Node<T>* AVLTree<T> :: rightRotate(Node<T> *curr) {
    Node<T> *leftSubtree = curr->left;
    Node<T> *rightOfLeft = leftSubtree->right;
 
    // Right rotation is performed by making the left subtree the 
    // new root, where current root is attached to its right, and the
    // right of the left subtree is attached to current roots left
    leftSubtree->right = curr;
    curr->left = rightOfLeft;
 
    // Updating the resultant heights
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    leftSubtree->height = 1 + max(getHeight(leftSubtree->left), getHeight(leftSubtree->right));
 
    // Return new root
    return leftSubtree;
}

template <typename T>
bool AVLTree<T> :: find(T key) {
    return search(ROOT, key);
}

template <typename T>
bool AVLTree<T> :: search(Node<T> *curr, T key) {
    if (!curr) return false;

    if (curr->data > key) return search(curr->left, key);
    else if (curr->data < key) return search(curr->right, key);
    else return true;
}

template <typename T>
void AVLTree<T> :: print() {
    // Calling the main function passing pointer to previous & direction
    prettyPrintTree(ROOT, NULL, false);
}

template <typename T>
void AVLTree<T> :: prettyPrintTree(Node<T> *root, Trunk *prev, bool isTop) {
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
     * We generate an instance of Adelson-Velskii and Landis tree class and perform operations
     */ 
    cout << "\nThis program generates a sample AVL tree object.\n" << endl;
    
    AVLTree<int> avltree;

    bool flag = true;
    int elem;

    while(flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Insert an element" << endl;
        cout << "2. Delete an element" << endl;
        cout << "3. Get height of tree" << endl;
        cout << "4. Search for an element" << endl;
        cout << "5. Pretty Print a Tree" << endl;
        cout << "6. Exit" << endl;
        int choice;
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "\nEnter the element to insert :" << endl;
                cin >> elem;
                avltree.create({elem});
                break;
            case 2:
                cout << "\nEnter the element to delete :" << endl;
                cin >> elem;
                avltree.destroy({elem});
                break;
            case 3:
                cout << "\nCurrent height of this tree is :" << avltree.height() << endl;
                break;
            case 4:
                cout << "\nEnter the element to search for :" << endl;
                cin >> elem;
                if (avltree.find(elem)) cout << "\n" << elem << " exists in the tree" << endl;
                else cout << "\n" << elem << " does not exist in the tree" << endl;
                break;
            case 5:
                cout << "\nHorizontal representation of the tree is :" << endl;
                avltree.print();
                break;
            case 6:
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