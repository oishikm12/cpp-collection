#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

int precedence(char);
bool isOperand(char); 
void swapBrackets(string &);

string prefixToInfix(string);
string prefixToPostfix(string); 
string infixToPrefix(string);
string infixToPostfix(string);
string postfixToPrefix(string);
string postfixToInfix(string);

int main() {
    /**
     * Conversion between multiple types of polish notations and infix
     * notations can be done via stack and queue
     */ 
    cout << "\nThis program converts between Infix, Prefix & Potfix notations of equations\n" << endl;

    bool flag = true;
    string inp, res;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Prefix to Infix." << endl;
        cout << "2. Prefix to Postfix." << endl;
        cout << "3. Infix to Prefix." << endl;
        cout << "4. Infix to Postfix." << endl;
        cout << "5. Postfix to Prefix." << endl;
        cout << "6. Postfix to Infix." << endl;
        cout << "7. Exit." << endl; 
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter Prefix Literal: ";
                cin >> inp;
                res = prefixToInfix(inp);
                cout << "\nInfix Literal is: " << res << endl;
                break; 
            case 2:
                cout << "\nEnter Prefix Literal: ";
                cin >> inp;
                res = prefixToPostfix(inp);
                cout << "\nPostfix Literal is: " << res << endl;
                break; 
            case 3:
                cout << "\nEnter Infix Literal: ";
                cin >> inp;
                res = infixToPrefix(inp);
                cout << "\nPrefix Literal is: " << res << endl;
                break; 
            case 4:
                cout << "\nEnter Infix Literal: ";
                cin >> inp;
                res = infixToPostfix(inp);
                cout << "\nPostfix Literal is: " << res << endl;
                break; 
            case 5:
                cout << "\nEnter Postfix Literal: ";
                cin >> inp;
                res = postfixToPrefix(inp);
                cout << "\nPrefix Literal is: " << res << endl;
                break; 
            case 6:
                cout << "\nEnter Postfix Literal: ";
                cin >> inp;
                res = postfixToInfix(inp);
                cout << "\nInfix Literal is: " << res << endl;
                break; 
            case 7:
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

int precedence(char x) {
    // Operator Precedence when changing notation type
    if (x == '^') return 3;
    if (x == '/' || x == '*') return 2;
    if (x == '-' || x == '+') return 1;
    return 0;
}

bool isOperand(char x) {
    // Checks if a character is non operator type
    if (x >= 'a' && x <= 'z') return true;
    if (x >= 'A' && x <= 'Z') return true;
    if (x >= '0' && x <= '9') return true;
    return false;
}

void swapBrackets(string &s) {
    // Swaps the brakets, useful when reversing the strings
    for (auto &c : s) {
        if (c == ')') c = '(';
        else if (c == '(') c = ')';
    }
}

string prefixToInfix(string s) {
    // In order to convert from prefix to infix notation, we
    // traverse from reverse direction, popping two elements
    // whenever we encounter an operator, combining them and 
    // reinserting them into stack
    stack<string> store;

    for (int i = s.size() - 1; i >= 0; i += 1) {
        // When we encounter an operand we simply push it
        if (isOperand(s[i])) store.push(string(1, s[i]));
        else {
            string op1 = store.top();
            store.pop();
            string op2 = store.top();
            store.pop();

            // We combine the current operation and reinsert into stack
            string operation = "(" + op1 + string(1, s[i]) + op2 + ")";
            store.push(operation);
        }
    }

    return store.top();
}

string prefixToPostfix(string s) {
    // In order to convert from prefix to postfix, we traverse
    // in reverse diretion, whenever we encounter an operator,
    // we concatenate the two topmost operands first then add
    // the operaor to the end
    stack<string> store;

    for (int i = s.size() - 1; i >= 0; i -= 1) {
        // Operands are simply pushed into stack
        if (isOperand(s[i])) store.push(string(1, s[i]));
        else {
            string op1 = store.top();
            store.pop();
            string op2 = store.top();
            store.pop();

            // We combine the current operation and reinsert into stack
            string operation = op1 + op2 + string(1, s[i]);
            store.push(operation);
        }
    }

    return store.top();
}

string infixToPrefix(string s) {
    // Reversing the expression, so that we get reversed postfix
    reverse(s.begin(), s.end());
    // Fixing the brackets after reversal
    swapBrackets(s);
    // Adding brackets so that no stray operators remain in stack
    s = "(" + s + ")";

    // We will store the entire result in a single string
    string result;
    // We will maintain this to keep track of our characters
    stack<char> store;

    // In order for us to get prefix, we reverse the infix expression
    // and find out its modified postfix, then we simply reverse it
    // again to get our prefix
    for (auto &c : s) {
        // If the character is an operand we simply push it to stack
        if (isOperand(c)) result.push_back(c);
        // We ignore the opening bracket till we find an equivalent closing one
        else if (c == '(') store.push('(');
        else if (c == ')') {
            while (!store.empty() && store.top() != '(') {
                // We remove every operator we encountered till the 
                // opening bracket, since these have precedence order
                result.push_back(store.top());
                store.pop();
            }

            // Removing the opening braket
            store.pop();
        } else {
            // When the operator is ^ its precedence changes in prefix
            if (c == '^') {
                while (!store.empty() && precedence(c) <= precedence(store.top())) {
                    // Whenever the precedence of current operator is less than
                    // or equal to the precedence of incomping operator, we simply
                    // pop elements from operator stack till the above condition is false
                    result.push_back(store.top());
                    store.pop();
                }
                // We now push the current operator
                store.push(c);
            } else {
                while (!store.empty() && precedence(c) < precedence(store.top())) {
                    // Whenever the precedence of current operator is less than
                    // the precedence of incomping operator, we simply pop elements 
                    // from operator stack till the above condition is false
                    result.push_back(store.top());
                    store.pop();
                }
                // We now push the current operator
                store.push(c);
            }
        }
    }

    // The result is currently in partial postfix form, we reverse it
    reverse(result.begin(), result.end());

    return result;
}

string infixToPostfix(string s) {
    // Adding brackets so that no stray operators remain in stack
    s = "(" + s + ")";
    // We will store the entire result in a single string
    string result;
    // We will maintain this to keep track of our characters
    stack<char> store;

    for (auto &c : s) {
        // If the character is an operand we simply push it to stack
        if (isOperand(c)) result.push_back(c);
        // We ignore the opening bracket till we find an equivalent closing one
        else if (c == '(') store.push('(');
        else if (c == ')') {
            while (!store.empty() && store.top() != '(') {
                // We remove every operator we encountered till the 
                // opening bracket, since these have precedence order
                result.push_back(store.top());
                store.pop();
            }

            // Removing the opening braket
            store.pop();
        } else {
            // This represents a case when we find an operator
            while (!store.empty() && precedence(c) <= precedence(store.top())) {
                // Whenever the precedence of current operator is less than
                // or equal to the precedence of incomping operator, we simply
                // pop elements from operator stack till the above condition is false
                result.push_back(store.top());
                store.pop();
            }
            // We now push the current operator
            store.push(c);
        }
    }

    return result;
}

string postfixToPrefix(string s) {
    // In order to convert from postfix to postfix, we traverse
    // in forward diretion, whenever we encounter an operator,
    // we concatenate the operator with the 2nd operand and
    // then the first operand, then we reinsert it to stack
    stack<string> store;

    for (int i = 0; i < s.size(); i += 1) {
        // Operands are simply pushed into stack
        if (isOperand(s[i])) store.push(string(1, s[i]));
        else {
            string op1 = store.top();
            store.pop();
            string op2 = store.top();
            store.pop();

            // We combine the current operation and reinsert into stack
            string operation = string(1, s[i]) + op2 + op1;
            store.push(operation);
        }
    }

    return store.top();
}

string postfixToInfix(string s) {
    // In order to convert postfix to infix, we use a forward
    // iteration, whenever we encounter an operator, we pop the
    // top two operands and combine them with the second operand
    // first, and reinsert them into stack
    stack<string> store;

    for (int i = 0; i < s.size(); i += 1) {
        // Operands are simply pushed into stack
        if (isOperand(s[i])) store.push(string(1, s[i]));
        else {
            string op1 = store.top();
            store.pop();
            string op2 = store.top();
            store.pop();

            // We combine the current operation and reinsert into stack
            string operation = "(" + op2 + string(1, s[i]) + op1 + ")";
            store.push(operation);
        }
    }

    return store.top();
}