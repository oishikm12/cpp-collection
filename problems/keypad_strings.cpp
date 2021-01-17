#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> keypad = {"", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"};

void findKeypadStrings(string&, string&, int, int);

int main() {
    /**
     * We use recursion to explore each possible combination of a given string
     * based on it's number
     */ 
    cout << "\nThis program finds out possiblities based on number.\n" << endl;
    string input, output;
    cout << "Enter search number : ";
    cin >> input;
    output.resize(input.length());

    cout << "\nThe possible strings are," << endl;
    findKeypadStrings(input, output, 0, 0);

    cout << endl;

    return 0;
}

void findKeypadStrings(string &inp, string &op, int i, int j) {
    // Once we reach the end, we simply print the string
    if (i == inp.length()) {
        cout << op << endl;
        return;
    }

    // We extract a digit
    int digit = inp[i] - '0';
    if (digit == 0 || digit == 1) findKeypadStrings(inp, op, i + 1, j);

    // For each possible letter it can represent, we make a recursive call
    for (int k = 0; k != keypad[digit].length(); k += 1) {
        op[j] = keypad[digit][k];
        findKeypadStrings(inp, op, i + 1, j + 1);
    }
}