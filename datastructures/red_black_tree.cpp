#include <iostream>
#include <vector>
using namespace std;

/**
 * A Red Black Tree uses sequence of two alternating colors
 * to ensure that the tree is always balanced. The main properties
 * 1. Roots & NULL leaves of Trees are always Black
 * 2. There are no two adjacent Red Nodes
 * 3. Sum of Black Nodes from ROOT to any NULL branch is always same
 * Unlike AVL trees, there are less rotations, hence less balanced,
 * hence is more likely used for insertion & deletion, not search
 */ 

class Trunk {
    // Helper class for Pretty Printing
    public:
        Trunk *prev;
        string str;

        Trunk(Trunk *p, string s) : prev(p), str(s) {};
};

// There are 2 possible node colors
enum Color { RED, BLACK };

template <typename T>
class RedBlackTree;

template<typename T>
class Node {
    private:
        T data;
        bool color;
        Node<T> *left, *right, *parent;

    public:
        // Used to assign value to a node
        Node(T);

        // Deallocate space for Node
        ~Node();

        // Will allow tree to access Nodes
        friend class RedBlackTree<T>;
};

template <typename T>
class RedBlackTree {
    private:
        Node<T> *ROOT;

    public:
        // Allocates for Red Black Tree
        RedBlackTree();

        // Deallocates Red Black Tree
        ~RedBlackTree();

        // Creates a new instance of Red Black Tree
        void create(vector<T>);

        // Inserts an element into the Tree
        void insert(T);

        // Fixes any RB Property mismatch in current node after insert
        void fixInsertViolation(Node<T> *);

        // Destroys elements from Tree
        void destroy(vector<T>);

        // Deletes an element from Tree
        void delNode(T);

        // Fixes any RB Property mismatch in current node after deletion
        void fixDeleteViolation(Node<T> *);

        // Rotates subtree left from current node
        void rotateLeft(Node<T> *);

        // Rotates subtree right from current node
        void rotateRight(Node<T> *);

        // Determines color of node
        bool getColor(Node<T> *);

        // Replaces a given node with another
        void redBlackTransplant(Node<T> *, Node<T> *);

        // Retrieves the minimal node, reachable from current
        Node<T>* getMinNode(Node<T> *);

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
    // Initial color for all nodes is RED
    color = RED;
    left = NULL;
    right = NULL;
    parent = NULL;
}

template <typename T>
Node<T> :: ~Node() {
    delete left;
    delete right;
    left = NULL;
    right = NULL;
}

template <typename T>
RedBlackTree<T> :: RedBlackTree() {
    ROOT = NULL;
}

template <typename T>
RedBlackTree<T> :: ~RedBlackTree() {
    delete ROOT;
    ROOT = NULL;
}

template <typename T>
void RedBlackTree<T> :: create(vector<T> elems) {
    // We simply insert all elements in the array
    // and then fix any RB violations
    for (auto &x : elems) {
        insert(x);
    }
}

template <typename T>
void RedBlackTree<T> :: insert(T key) {
    // Allocating space for the new node
    Node<T> *curr = new Node<T>(key);

    Node<T> *parent = NULL;
    Node<T> *temp = ROOT;

    while (temp) {
        // This node keeps track of immidiate parent
        parent = temp;

        // Standard BST traversal
        if (key > temp->data) temp = temp->right;
        else if (key < temp->data) temp = temp->left;
        else {
            // Duplicates are not allowed
            delete curr;
            return;
        }
    }

    curr->parent = parent;

    // Connecting the node to the tree
    if (!parent) ROOT = curr;
    else if (key > parent->data) parent->right = curr;
    else parent->left = curr;

    if (!parent) {
        // This is a ROOT node, hence must be black
        curr->color = BLACK;
        return;
    }

    // First generation child, no balancing needed
    if (!parent->parent) return;

    fixInsertViolation(curr);
}

template <typename T>
void RedBlackTree<T> :: fixInsertViolation(Node<T> *curr) {
    Node<T> *parent = NULL;
    Node<T> *grandParent = NULL;

    while ((curr != ROOT) && (getColor(curr) != BLACK) && (getColor(curr->parent) == RED)) {
        parent = curr->parent;
        grandParent = curr->parent->parent;
 
        if (parent == grandParent->left) {
            // Case A: Parent of curr is left child of Grand-parent of curr
            Node<T> *uncle = grandParent->right;
 
            if (uncle && getColor(uncle) == RED) {
                // Case A.1: The uncle of curr is also red, hence only Recoloring required
                grandParent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                curr = grandParent;
            } else {
                // Case A.2: curr is right child of its parent, hence Left-rotation required
                if (curr == parent->right) {
                    rotateLeft(parent);
                    curr = parent;
                    parent = curr->parent;
                }
 
                // Case A.3: curr is left child of its parent, hence Right-rotation required
                rotateRight(grandParent);
                swap(parent->color, grandParent->color);
                curr = parent;
            }
        } else {
            // Case B: Parent of curr is right child of Grand-parent of curr
            Node<T> *uncle = grandParent->left;
 
            // Case B.1: The uncle of curr is also red, hence only Recoloring required
            if (uncle && getColor(uncle) == RED) {
                grandParent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                curr = grandParent;
            } else {
                // Case B.2: curr is left child of its parent, hence Right-rotation required
                if (curr == parent->left) {
                    rotateRight(parent);
                    curr = parent;
                    parent = curr->parent;
                }
 
                // Case B.3: curr is right child of its parent, hence Left-rotation required
                rotateLeft(grandParent);
                swap(parent->color, grandParent->color);
                curr = parent;
            }
        }
    }
 
    ROOT->color = BLACK;
}

template <typename T>
void RedBlackTree<T> :: destroy(vector<T> elems) {
    // We simply delete all elements in the array
    // and then fix any RB violations
    for (auto &x : elems) {
        delNode(x);
    }
}

template <typename T>
void RedBlackTree<T> :: delNode(T key) {
    Node<T> *target = NULL;

    // We will use this for traversal
    Node<T> *curr = ROOT;

    while (curr) {
        if (curr->data == key) {
            target = curr;
            break;
        }

        // Normal BST Traversal
        if (curr->data < key) curr = curr->left;
        else curr = curr->right;
    }

    // Node to delete is not found
    if (!target) return;

    // We backup the original color & create a copy of the node
    Node<T> *temp = target;
    bool originalColor = getColor(temp);

    if (!target->left) {
        // If the node has only right child
        curr = target->right;
        redBlackTransplant(target, target->right);
    } else if (!target->right) {
        // If the node has only left child
        curr = target->left;
        redBlackTransplant(target, target->left);
    } else {
        // The above conditions also work, should the node have no children
        // Otherwise if the node has both children, we simply replace with rightmost smallest
        temp = getMinNode(target->right);
        originalColor = getColor(temp);

        curr = temp->right;

        if (temp->parent == target) {
            // If the replacement node has a child, we simply reorganize it
            curr->parent = temp;
        } else {
            // Otherwise we transplant it with its right child
            redBlackTransplant(temp, temp->right);
            temp->right = target->right;
            temp->right->parent = temp;
        }

        // Finally we transplant the node to be deleted with its inorder successor
        redBlackTransplant(target, temp);

        temp->left = target->left;
        temp->left->parent = temp;
        temp->color = getColor(target);
    }

    target->left = target->right = NULL;
    delete target;

    if (originalColor == BLACK) fixDeleteViolation(curr);
}

template <typename T>
void RedBlackTree<T> :: fixDeleteViolation(Node<T> *curr) {
    Node<T> *parent = NULL;

    while ((curr != ROOT) && (getColor(curr) == BLACK)) {
        parent = curr->parent;

        if (curr == parent->left) {
            // If the deleted node is to the left, then sibling is to its right
            Node<T> *sibling = parent->right;

            if (getColor(sibling) == RED) {
                // If we have a RED sibling, we change its parent to RED,
                // sibling to BLACK, and then rotate left, to bring the BLACK
                // as a common parent to both
                sibling->color = BLACK;
                parent->color = RED;

                rotateLeft(parent);
                sibling = parent->right;
            }

            if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                // If both the children of sibling are BLACK, then we make
                // the sibling RED, and move the target to its parent
                sibling->color = RED;
                curr = curr->parent;
            } else {
                if (getColor(sibling->right) == BLACK) {
                    // If one of the children of siblings is BLACK,
                    // then we make the other too, and make the parent RED
                    sibling->left->color = BLACK;
                    sibling->color = RED;

                    // Then we rotate right, to bring the RED sibling to right subtree
                    // making this now BLACK node as the sibling
                    rotateRight(sibling);
                    sibling = parent->right;
                } 

                // Afterwards we change the color of sibling to same as that of
                // parent of target, which is also made BLACK, and so is the right child of sibling
                sibling->color = getColor(parent);
                parent->color = BLACK;
                sibling->right->color = BLACK;

                // Finally the subtree is rotated right to make the RED node the root of subtree
                rotateLeft(parent);
                curr = ROOT;
            }
        } else {
            // If the deleted node is to the right, then sibling is to its left
            Node<T> *sibling = parent->left;

            if (getColor(sibling) == RED) {
                // If we have a RED sibling, we change its parent to RED,
                // sibling to BLACK, and then rotate right, to bring the BLACK
                // as a common parent to both
                sibling->color = BLACK;
                parent->color = RED;

                rotateRight(parent);
                sibling = parent->left;
            }

            if (getColor(sibling->right) == BLACK && getColor(sibling->left) == BLACK) {
                // If both the children of sibling are BLACK, then we make
                // the sibling RED, and move the target to its parent
                sibling->color = RED;
                curr = curr->parent;
            } else {
                if (getColor(sibling->left) == BLACK) {
                    // If one of the children of siblings is BLACK,
                    // then we make the other too, and make the parent RED
                    sibling->right->color = BLACK;
                    sibling->color = RED;

                    // Then we rotate left, to bring the RED sibling to left subtree
                    // making this now BLACK node as the sibling
                    rotateLeft(sibling);
                    sibling = parent->left;
                } 

                // Afterwards we change the color of sibling to same as that of
                // parent of target, which is also made BLACK, and so is the left child of sibling
                sibling->color = parent->color;
                parent->color = BLACK;
                sibling->left->color = BLACK;

                // Finally the subtree is rotated left to make the RED node the root of subtree
                rotateRight(parent);
                curr = ROOT;
            }
        }
    }

    // ROOT is ultimately colored BLACK
    curr->color = BLACK;
}

template <typename T>
void RedBlackTree<T> :: rotateLeft(Node<T> *curr) {
    // When rotating to the right we move the current
    // root to the left of its right node
    Node<T> *rightChild = curr->right;
 
    // The current root's right stores the right node' left
    curr->right = rightChild->left;
 
    if (curr->right) curr->right->parent = curr;
 
    // Restoring parents for new node
    rightChild->parent = curr->parent;
 
    if (!curr->parent) ROOT = rightChild;
    else if (curr == curr->parent->left) curr->parent->left = rightChild;
    else curr->parent->right = rightChild;
 
    rightChild->left = curr;
    curr->parent = rightChild;
}

template <typename T>
void RedBlackTree<T> :: rotateRight(Node<T> *curr) {
    // When rotating to the left we move the current
    // root to the right of its left node
    Node<T> *leftChild = curr->left;
 
    // The current root's left stores the left node' right
    curr->left = leftChild->right;
 
    if (curr->left) curr->left->parent = curr;
 
    // Restoring parents for new node
    leftChild->parent = curr->parent;
 
    if (!curr->parent) ROOT = leftChild;
    else if (curr == curr->parent->left) curr->parent->left = leftChild;
    else curr->parent->right = leftChild;
 
    leftChild->right = curr;
    curr->parent = leftChild;
}

template <typename T> 
bool RedBlackTree<T> :: getColor(Node<T> *curr) {
    // Deals with null nodes being BLACK
    if (!curr) return BLACK;
    return curr->color;
}

template <typename T> 
void RedBlackTree<T> :: redBlackTransplant(Node<T> *source, Node<T> *target) {
    if (!source->parent) {
        // The source node was the root itself
        ROOT = target;
    } else if (source = source->parent->left) {
        // Left Child of its parent
        source->parent->left = target;
    } else {
        // Right Child of its parent
        source->parent->right = target;
    }

    // By assigning the same parent, we have successfully, swapped
    // a black node with a red node
    target->parent = source->parent;
}

template <typename T> 
Node<T>* RedBlackTree<T> :: getMinNode(Node<T> *curr) {
    Node<T> *temp = curr;
    // Loop down to find the leftmost leaf
    while (temp->left) temp = temp->left;
 
    return temp;
}

template <typename T>
bool RedBlackTree<T> :: find(T key) {
    return search(ROOT, key);
}

template <typename T>
bool RedBlackTree<T> :: search(Node<T> *curr, T key) {
    if (!curr) return false;

    if (curr->data > key) return search(curr->left, key);
    else if (curr->data < key) return search(curr->right, key);
    else return true;
}

template <typename T>
void RedBlackTree<T> :: print() {
    // Calling the main function passing pointer to previous & direction
    prettyPrintTree(ROOT, NULL, false);
}

template <typename T>
void RedBlackTree<T> :: prettyPrintTree(Node<T> *root, Trunk *prev, bool isTop) {
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
    cout << "(" << root->data << (getColor(root) == RED ? 'R' : 'B') << ")" << endl;
 
    if (prev) prev->str = prevStr;

    // End of current data, and move to right side
    trunk->str = "   |";
 
    prettyPrintTree(root->left, trunk, false);

    delete trunk;
}

int main() {
    /**
     * We generate an instance of Red Black tree class and perform operations
     */ 
    cout << "\nThis program generates a sample Red-Black tree object.\n" << endl;
    
    RedBlackTree<int> rbtree;

    bool flag = true;
    int elem;

    while(flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Insert an element" << endl;
        cout << "2. Delete an element" << endl;
        cout << "3. Search for an element" << endl;
        cout << "4. Pretty Print a Tree" << endl;
        cout << "5. Exit" << endl;
        int choice;
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "\nEnter the element to insert :" << endl;
                cin >> elem;
                rbtree.create({elem});
                break;
            case 2:
                cout << "\nEnter the element to delete :" << endl;
                cin >> elem;
                rbtree.destroy({elem});
                break;
            case 3:
                cout << "\nEnter the element to search for :" << endl;
                cin >> elem;
                if (rbtree.find(elem)) cout << "\n" << elem << " exists in the tree" << endl;
                else cout << "\n" << elem << " does not exist in the tree" << endl;
                break;
            case 4:
                cout << "\nHorizontal representation of the tree is :" << endl;
                rbtree.print();
                break;
            case 5:
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