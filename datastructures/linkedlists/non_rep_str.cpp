#include <iostream>
using namespace std;

class Node {
    public:
        char data;
        Node *next, *prev;

        Node(char val = ' ', Node *lfwd = NULL, Node *lbck = NULL) : data(val), next(lfwd), prev(lbck) {};
        ~Node() { delete prev, delete next; }
};

void appendNode(Node *&, Node *&, char x);
void removeNode(Node *&, Node *&, Node *);
string firstNonRep(string);

int main() {
    /**
     * In order to replace every character in the string with
     * non repeating characters, we will maintain a list of
     * non them in DLL, updating them every turn
     */ 
    cout << "\nThis program replaces every character with a non repeating character via DLL.\n" << endl;
    cout << "Enter the string to transform: ";
    string a;
    cin >> a;

    cout << "\nThe converted string is: ";
    string b = firstNonRep(a);
    cout << b << endl;

    return 0;
}

void appendNode(Node *&head, Node *&tail, char x) {
    // Appends node to a list with value
    Node *temp = new Node(x);
  
    if (head == NULL) {
        // If there exist no node, we make the head and tail same
        head = tail = temp;
        return;
    }

    // After appending the node to list, move the last node
    tail->next = temp;
    temp->prev = tail;
    tail = temp;
}

void removeNode(Node *&head, Node *&tail, Node *temp) {
    // There is no node to delete
    if (head == NULL) return;
  
    // Increment or decrement head / tail, if the node is at ends
    if (head == temp) head = head->next;
    if (tail == temp) tail = tail->prev;

    // Re-link the nodes to the front and back
    if (temp->next != NULL) temp->next->prev = temp->prev;
    if (temp->prev != NULL) temp->prev->next = temp->next;
  
    // Deletes the current node
    temp->next = NULL;
    temp->prev = NULL;
    delete temp;
}

string firstNonRep(string a) {
    string b;

    // DLL represents every character of the letter
    Node *inDLL[26];
    bool repeated[26];

    for (int i = 0; i < 26; i += 1) {
        // Default values in the, setting the DLL as NULL
        inDLL[i] = NULL;
        repeated[i] = false;
    }

    Node *head = NULL, *tail = NULL;

    for (auto &x : a) {
        if (!repeated[x]) {
            if (inDLL[x] == NULL) {
                // Add the node to the list, and add it to vector of nodes
                appendNode(head, tail, x);
                inDLL[x] = tail;
            } else {
                // Element has been repeated so remove it from list
                removeNode(head, tail, inDLL[x]);
                inDLL[x] = NULL;
                repeated[x] = true;
            }
        }
  
        // If there is no non-repeated element, add #
        if (head) b.push_back(head->data);
        else b.push_back('#');
    }

    return b;
}