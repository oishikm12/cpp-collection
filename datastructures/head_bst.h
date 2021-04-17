#include <iostream>
#include <queue>

/**
 * Binary Search Tree consists of at most two nodes connected to the root
 * Each node is in itself a value such that all values smaler than itself
 * are present in its left subtree and all values greater are on its right
 * subtree. This condition recursively holds true for every node in BST
 */

#ifndef BINARY_SEARCH_TREE_CLASS_H
#define BINARY_SEARCH_TREE_CLASS_H

namespace bstree {

    template <typename T>
    class BinarySearchTree;

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
            friend class BinarySearchTree<T>;
    };

    template<typename T>
    class BinarySearchTree {
        private:
            Node<T> *ROOT;

        public:
            // Allocates for Binary Search Tree
            BinarySearchTree();

            // Deallocates Binary Search Tree
            ~BinarySearchTree();

            // Creates a new instance of Binary Search Tree
            void create();

            // Keeps asking user for input
            Node<T>* buildTree();

            // Inserts recursively in its correct position
            Node<T>* insertInBST(Node<T>*, T);

            // Removes a certain element if present in the tree
            bool remove(T);
            
            // Finds and recursively deletes an element
            Node<T>* deleteInBST(Node<T>*, T);

            // Preserves BST when deleteing element
            Node<T>* deleteAndRestoreTree(Node<T>*, T);

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

            // Traverses the tree in postorder, ie. root prints last
            void postorderTraversal(Node<T>*);

            // Performs a breadth first traversal, ie. level wise
            void bfs();

            // Returns height of tree
            int getHeight();

            // Finds out height of the tree
            int height(Node<T>*);

            // Return Node count of tree
            int getCount();

            // Counts the number of nodes in tree
            int count(Node<T>*);

            // Seacrhes for an element in tree
            bool search(T);

            // Finds an element recursively
            bool find(Node<T>*, T);
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
    BinarySearchTree<T> :: BinarySearchTree() {
        ROOT = NULL;
    }

    template <typename T>
    BinarySearchTree<T> :: ~BinarySearchTree() {
        delete ROOT;
    }

    template <typename T>
    void BinarySearchTree<T> :: create() {
        ROOT = buildTree();
    }

    template <typename T>
    Node<T>* BinarySearchTree<T> :: buildTree() {
        // First take the data from user
        T data;
        std::cin >> data;

        // We initialize a pointer to to store data in
        Node<T> *curr = NULL;

        // While user does not enter -1, we continue to push data into tree
        while (data != -1) {
            curr = insertInBST(curr, data);
            std::cin >> data;
        }

        return curr;
    }

    template <typename T>
    Node<T>* BinarySearchTree<T> :: insertInBST(Node<T> *curr, T data) {
        // Base case when we have reached desired position
        if (curr == NULL) return new Node<T>(data);

        // Recursive case to place data in desired position
        if (data <= curr->data) curr->left = insertInBST(curr->left, data);
        else curr->right = insertInBST(curr->right, data);

        return curr;
    }

    template <typename T>
    bool BinarySearchTree<T> :: remove(T data) {
        // Checks if an element is present or not in tree
        if (!find(ROOT, data)) return false;
        ROOT = deleteInBST(ROOT, data);
        return true;
    }

    template <typename T>
    Node<T>* BinarySearchTree<T> :: deleteInBST(Node<T> *curr, T data) {
        if (curr == NULL) return NULL;

        // Finds the exact position to delet from and recursively call it
        if (data < curr->data) {
            curr->left = deleteInBST(curr->left, data);
        } else if (data == curr->data) {
            curr = deleteAndRestoreTree(curr, data);
        } else {
            curr->right = deleteInBST(curr->right, data);
        }

        return curr;
    }

    template <typename T>
    Node<T>* BinarySearchTree<T> :: deleteAndRestoreTree(Node<T> *curr, T data) {
        // If the node has no child we simply delete it
        if (curr->right == NULL && curr->right == NULL) {
            delete curr;
            return NULL;
        }

        // If the node has only right child
        if (curr->right != NULL && curr->left == NULL) {
            // We store the data of right child and then delete current
            Node<T> *temp = curr->right;
            curr->right = NULL;
            delete curr;
            return temp;
        }

        // If the node has only left child
        if (curr->right == NULL && curr->left != NULL) {
            // We store the data of left child and then delete current
            Node<T> *temp = curr->left;
            curr->left = NULL;
            delete curr;
            return temp;
        }

        // If the node has both a left child and a right child then we
        // transfer the left children to first free empty left subchild
        // of the right child, that way BST order is preserved
        Node<T> *temp = curr->right;
        Node<T> *pos = curr->right;

        while (temp->left != NULL) temp = temp->left;

        temp->left = curr->left;
        curr->left = NULL;
        curr->right = NULL;
        delete curr;
        return pos;
    }

    template <typename T>
    void BinarySearchTree<T> :: preorder() {
        preorderTraversal(ROOT);
    }

    template <typename T>
    void BinarySearchTree<T> :: inorder() {
        inorderTraversal(ROOT);
    }

    template <typename T>
    void BinarySearchTree<T> :: postorder() {
        postorderTraversal(ROOT);
    }

    template <typename T>
    void BinarySearchTree<T> :: preorderTraversal(Node<T> *curr) {
        if (curr != NULL) {
            // Preorder we print the data in current node
            // Then we print from left node, recursively travel to its left
            // Then once no more left nodes remain the right nodes are printed
            std::cout << curr->data << " ";
            preorderTraversal(curr->left);
            preorderTraversal(curr->right);
        }
    }

    template <typename T>
    void BinarySearchTree<T> :: inorderTraversal(Node<T> *curr) {
        if (curr != NULL) {
            // Inorder travels to left first ,this continues recursively
            // Once we reach the left most we print current data, move back up
            // Print the data of parent and then print right node's data
            inorderTraversal(curr->left);
            std::cout << curr->data << " ";
            inorderTraversal(curr->right);
        }
    }

    template <typename T>
    void BinarySearchTree<T> :: postorderTraversal(Node<T> *curr) {
        if (curr != NULL) {
            // Post order travels to left most node first recursively
            // Once there it travels rightmost recursively
            // There it prints the data and travels up to parent and left
            postorderTraversal(curr->left);
            postorderTraversal(curr->right);
            std::cout << curr->data << " ";
        }
    }

    template <typename T>
    void BinarySearchTree<T> :: bfs() {
        // In order to traverse level wise we use a queue to store 
        // current levels nodes. Since queue is FIFO, this ensures 
        // nodes of a certain level are printed before next level
        std::queue<Node<T>*> container;

        Node<T> *temp = ROOT;
        container.push(temp);
        // By inserting an extra NULL we can identify when a level changes
        container.push(NULL);

        while (!container.empty()) {
            temp = container.front();
            container.pop();

            if (temp == NULL) {
                std::cout << std::endl;
                // There are more levels below, so we use another seperator
                if (!container.empty()) container.push(NULL);
            } else {
                std::cout << temp->data << " ";

                // We check if it has children and accordingly print
                if (temp->left != NULL) container.push(temp->left);
                if (temp->right != NULL) container.push(temp->right);
            }
        }
    }

    template <typename T>
    int BinarySearchTree<T> :: getHeight() {
        return height(ROOT);
    }

    template <typename T>
    int BinarySearchTree<T> :: height(Node<T> *curr) {
        // Base case for end of recursion
        if (curr == NULL) return 0;
        // We add 1 for current level and recurse till we reach a leaf
        return 1 + std::max(height(curr->left), height(curr->right));
    }

    template <typename T>
    int BinarySearchTree<T> :: getCount() {
        return count(ROOT);
    }

    template <typename T>
    int BinarySearchTree<T> :: count(Node<T> *curr) {
        // Base case for end of recursion
        if (curr == NULL) return 0;
        // We add 1 for node and recurse for left & right child
        return 1 + count(curr->left) + count(curr->right);
    }

    template <typename T>
    bool BinarySearchTree<T> :: search(T data) {
        return find(ROOT, data);
    }

    template <typename T>
    bool BinarySearchTree<T> :: find(Node<T> *curr, T data) {
        // If we have reached a leaf, the element is not there
        if (curr == NULL) return false;
        // Check if the current node data is the one we are searching for
        if (curr->data == data) return true;

        // If the current element is greater, the data could be present in
        // left subtree otherwise the data could be present in right subtree
        if (curr->data > data) return find(curr->left, data);
        else return find(curr->right, data);
    }
}

#endif /* BINARY_SEARCH_TREE_CLASS_H */