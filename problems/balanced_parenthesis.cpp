#include <iostream>
#include <stack>
using namespace std;

bool checkBalance(string &);
int lenOfValidSubstring(string &);

int main() {
    /**
     * In order to find out if the equation is balanced, we use a stack to
     * keep track of opening and closing parenthesis, for each opening one
     * there should be a closing one, any exception means the equation is wrong
     */ 
    cout << "\nThis program checks if parenthesis are balanced in a equation.\n" << endl;
    string equ;
    cout << "Enter the equation to check : ";
    cin >> equ;

    bool isBalanced = checkBalance(equ);

    if (isBalanced) cout << "\nThe equation is syntactically valid." << endl;
    else {
        int mxVal = lenOfValidSubstring(equ);
        cout << "\nThe equation is not syntactically valid. The length of largest valid substring in it is " << mxVal << "." << endl;
    }

    cout << endl;

    return 0;
}

bool checkBalance(string &equ) {
    // We create our stack of characters
    stack<char> elems;

    for (int i = 0; i < equ.length(); i += 1) {
        // Iterating over each element we push every ( we find
        if (equ[i] == '(') elems.push('(');
        else if (equ[i] == ')') {
            // If we find a ), we check if the top of stack has a open
            // bracket corresponding to it, if not then we return false
            if (elems.empty() || elems.top() != '(') return false;
            elems.pop();
        }
    }

    // If control reaches here then equal no. of closing & opening bracs exist
    return elems.empty();
}

int lenOfValidSubstring(string &equ) {
    // Counter variable
    int cnt = 0;
        
    // Create a stack and push -1 as initial index to it.
    stack<int> idx;
    idx.push(-1);
    
    for (int i = 0; i < equ.size(); i += 1) {
        // If the bracket is an opening one, we simply insert it
        if (equ[i] == '(') idx.push(i);
        if (equ[i] == ')') {
            // Otherwise, we first remove the previous, assuming
            // it to be an opening bracket
            if (!idx.empty()) idx.pop();
            
            if (!idx.empty()) {
                // Then we compare to check if the distance between the
                // last opening and current is greater than previously recorded
                cnt = max(cnt, i - idx.top());
            } else {
                // If the stack is empty it signifies, that no previously
                // valid substring was found
                idx.push(i);
            }
        }
    }
    
    return cnt;
}