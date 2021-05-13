#include <iostream>
#include <queue>
#include <stack>
#include <vector>

/**
 * Binary Tree consists of at most two nodes connected to the root
 * Each node then contains its data as well as two or no links to its children
 * A node with no child is a leaf while a node with no parents is root
 */

#ifndef BINARY_TREE_CLASS_H
#define BINARY_TREE_CLASS_H

namespace binarytree {

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
    }

    template <typename T>
    void BinaryTree<T> :: create() {
        ROOT = buildTree();
    }

    template <typename T>
    Node<T>* BinaryTree<T> :: buildTree() {
        // First take the data from user
        T data;
        std::cin >> data;

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
    }

    template <typename T>
    void BinaryTree<T> :: inorder() {
        inorderTraversal(ROOT);
    }

    template <typename T>
    void BinaryTree<T> :: postorder() {
        postorderTraversal(ROOT);
    }

    template <typename T>
    void BinaryTree<T> :: preorderTraversal(Node<T> *curr) {
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
    void BinaryTree<T> :: inorderTraversal(Node<T> *curr) {
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
    void BinaryTree<T> :: postorderTraversal(Node<T> *curr) {
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
    void BinaryTree<T> :: preorderIterative() {
        if (ROOT == NULL) return;

        // Iterative preorder requires the use of stack to store
        // what we have already traversed and go back to it
        std::stack<Node<T>*> container;
        Node<T> *temp = ROOT;
        container.push(temp);

        // This is used to store the output
        std::vector<T> list;

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
        for (int i = 0; i < list.size(); i += 1) std::cout << list[i] << (i == list.size() - 1 ? "" : " ");
    }

    template <typename T>
    void BinaryTree<T> :: inorderIterative() {
        if (ROOT == NULL) return;

        // Iterative inorder requires the use of stack to store
        // what we have already traversed and go back to it
        std::stack<Node<T>*> container;
        Node<T> *temp = ROOT;

        // This is used to store the output
        std::vector<T> list;

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
        for (int i = 0; i < list.size(); i += 1) std::cout << list[i] << (i == list.size() - 1 ? "" : " ");
    }

    template <typename T>
    void BinaryTree<T> :: postorderIterative() {
        if (ROOT == NULL) return;

        // Iterative postorder requires the use of stack to store
        // what we have already traversed and go back to it
        std::stack<Node<T>*> container;
        Node<T> *temp = ROOT;
        container.push(temp);

        // This is used to store the output
        std::vector<T> list;

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
        for (int i = list.size() - 1; i >= 0; i -= 1) std::cout << list[i] << (i == 0 ? "" : " ");
    }

    template <typename T>
    void BinaryTree<T> :: bfs() {
        // In order to traverse level wise we use a queue to store 
        // current levels nodes. Since queue is FIFO, this ensures 
        // nodes of a certain level are printed before next level
        std::queue<Node<T>*> container;

        Node<T> *temp = ROOT;
        container.push(temp);

        while (!container.empty()) {
            // By checking its size we know exactly how many nodes in this level
            int n = container.size();

            while (n--) {
                temp = container.front();
                container.pop();
                std::cout << temp->data << " ";

                // We check if it has children and accordingly print
                if (temp->left != NULL) container.push(temp->left);
                if (temp->right != NULL) container.push(temp->right);
            }

            std::cout << std::endl;
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
        return 1 + std::max(height(curr->left), height(curr->right));
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
        if (level > getHeight()) std::cout << "Level not found." << std::endl;
        else traverseLevels(ROOT, level);
    }

    template <typename T>
    void BinaryTree<T> :: traverseLevels(Node<T> *curr, int level) {
        if (curr == NULL) return;

        // Eventually level will recurse to 1 at desired level
        if (level == 1) std::cout << curr->data << " ";

        // After traversing current level we move onto their children
        traverseLevels(curr->left, level - 1);
        traverseLevels(curr->right, level - 1);
    }
}

#endif /* BINARY_TREE_CLASS_H */