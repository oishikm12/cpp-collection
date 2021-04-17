#include "head_bt.h"
#include <iostream>

using namespace binarytree;
using namespace std;

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

    cout << "\nPreorder traversal of this tree :" << endl;
    btree.preorder();
    cout << endl;

    cout << "\nInorder traversal of this tree :" << endl;
    btree.inorder();
    cout << endl;

    cout << "\nPostorder traversal of this tree :" << endl;
    btree.postorder();
    cout << endl;

    cout << "\nBreadth First traversal of this tree :" << endl;
    btree.bfs();

    int level;
    cout << "\nEnter level whose elements to display : ";
    cin >> level;
    btree.printKthLevel(level);
    cout << endl;

    cout << endl;

    return 0;
}