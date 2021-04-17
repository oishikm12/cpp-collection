#include "head_bst.h"
#include <iostream>

using namespace bstree;
using namespace std;

int main() {
    /**
     * We generate an instance of binary search tree class and perform operations
     */ 
    cout << "\nThis program generates a sample binary search tree object.\n" << endl;
    
    BinarySearchTree<int> bstree;

    cout << "\nEnter space delimited elements of the tree, -1 indicating end of input" << endl;
    bstree.create();

    cout << "\nHeight of this tree is : " << bstree.getHeight() << endl;
    cout << "\nNode count of this tree is : " << bstree.getCount() << endl;

    bool loop = true;
    int choice, elem;

    while(loop) {
        cout << "\nPlease enter your choice:\n1. Print Preorder Traversal\n2. Print Inorder Traversal\n3. Print Postorder Traversal\n4. Print Breadth First Traversal\n5. Search for an element\n6. Delete an element\n7. Exit" << endl;
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "\nPreorder traversal of this tree :" << endl;
                bstree.preorder();
                break;
            case 2:
                cout << "\nInorder traversal of this tree :" << endl;
                bstree.inorder();
                break;
            case 3:
                cout << "\nPostorder traversal of this tree :" << endl;
                bstree.postorder();
                break;
            case 4:
                cout << "\nBreadth First traversal of this tree :" << endl;
                bstree.bfs();
                break;
            case 5:
                cout << "\nEnter the element to search for: ";
                cin >> elem;
                if (bstree.search(elem)) cout << "\nElement is present in the tree" << endl;
                else cout << "\nElement is not present in the tree" << endl;
                break;
            case 6:
                cout << "\nEnter the element to delete: ";
                cin >> elem;
                if (bstree.remove(elem)) cout << "\nThe element has been deleted" << endl;
                else cout << "\nElement is not present in the tree" << endl;
                break;
            default:
                cout << "\nGoodbye" << endl;
                loop = false;
                break;
        }
    }

    cout << endl;

    return 0;
}