#include <iostream>
#include <stack>
using namespace std;

bool checkBalance(string &);

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
    else cout << "\nThe equation is not syntactically valid." << endl;

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