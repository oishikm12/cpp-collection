#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Node {
    public:
        int data;
        Node *next, *arb;

        Node(int val = 0, Node *lfwd = NULL, Node *larb = NULL) : data(val), next(lfwd), arb(larb) {};
        ~Node() { delete arb, delete next; }
};

int main() {
    /**
     * In order to clone a linked list with arbitary pointer
     * we will maintain a map that will store the current 
     * addresses with old adresses, this will allow us to join
     * random nodes
     */ 
    cout << "\nThis program clones a singly linked list with arbitary pointers.\n" << endl;
    cout << "Enter size of the List: ";
    int n;
    cin >> n;

    cout << endl << "Enter space seperated elements of the list" << endl;
    vector<int> elems(n);
    for (int i = 0; i < n; i += 1) cin >> elems[i];

    cout << "Enter number of pairs in the list: ";
    int k;
    cin >> k;
    cout << "Enter space seperated line delimited pairs of arbitary links" << endl;
    vector<pair<int, int>> links(k);
    for (int i = 0; i < k; i += 1) cin >> links[i].first >> links[i].second;

    Node *head = NULL;
    head = build(head, elems, links);
    cout << "\nThe list is: " << endl;
    print(head);

    Node *newHead = copyList(head);
    cout << "\nThe copied list is," << endl;
    print(newHead);

    return 0;
}

Node* build(Node *head, vector<int> &elems, vector<pair<int, int>> &links) {
    int n = elems.size();
    int m = links.size();

    // We will store all the node in a vector to create arb links
    vector<Node*> ptrs;

    head = new Node(elems[0]);
    Node *temp = head;
    ptrs.push_back(temp);

    for (int i = 1; i < n; i += 1) {
        // Iterating the elements and pushing them onto vector
        temp->next = new Node(elems[i]);
        temp = temp->next;
        ptrs.push_back(temp);
    }

    for (int i = 0; i < m; i += 1) {
        // Simply connect their arbitary pointers
        pair<int, int> link = links[i];
        ptrs[link.first - 1]->arb = ptrs[link.second - 1];
    }

    return head;
}

void print(Node *head) {
    while (head != NULL) {
        cout << head->data;
        // Print data if connected to arbitary
        if (head->arb) cout << "(" << head->arb->data << ")";
        // Printing connector b/w nodes
        if (head->next != NULL) cout << " > ";
        head = head->next;
    }
    cout << endl;
}


Node *copyList(Node *head) {
    // Creating the new node
    Node *newHead = new Node(head->data);
    Node *tHead = head;
    Node *tnHead = newHead;
    
    // This will allow us to map old pointers to new pointers
    unordered_map<Node*, Node*> link;
    link[tHead] = tnHead;
    
    while (tHead->next) {
        // Copying and placing pointers in map
        tnHead->next = new Node(tHead->next->data);
        link[tHead->next] = tnHead->next;
        tHead = tHead->next;
        tnHead = tnHead->next;
    }
    
    tnHead = newHead;
    tHead = head;
    
    while (tHead) {
        // Fixing arbitary pointers
        tnHead->arb = link[tHead->arb];
        tHead = tHead->next;
        tnHead = tnHead->next;
    }
    
    return newHead;
}
