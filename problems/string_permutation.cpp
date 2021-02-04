#include <iostream>
#include <vector>
using namespace std;

void permute(string&, int, int);

int main() {
    /**
     * In order to find all permutations of a string we select a character
     * and then recursively call the same function to select the next character
     */ 
    cout << "\nThis program finds out possible permutations of a string.\n" << endl;
    string val;
    cout << "Enter the string to find permutations of : ";
    cin >> val;

    permute(val, 0, val.size() - 1);

    cout << endl;

    return 0;
}

void permute(string &val, int start, int end) {
    // Base Case we simply print
    if (start == end) {
        cout << val << endl;
    } else {
        // We iterate over all possible strings starting with
        // letter at 0, and swap with letter at i
        for (int i = start; i <= end; i += 1) {
            swap(val[start], val[i]);
            // continue with next possiblity
            permute(val, start + 1, end);
            // backtrack
            swap(val[start], val[i]);
        }
    }
}