#include <iostream>
#include <vector>
using namespace std;

int calculateCatalan(vector<int>&, int);

int main() {
    /**
     * Catalan numbers on nonnegative integers n are a set of numbers 
     * that arise in tree enumeration problems of the type, "In how many 
     * ways can a regular n-gon be divided into n-2 triangles if different 
     * orientations are counted separately?" (Euler's polygon division problem). 
     * The solution is the Catalan number. It exists in the form 2nCn / n - 1
     */ 
    cout << "\nThis program displays Catalan Numbers upto a particular range\n" << endl;

    int n;
    cout << "Enter range for calculation: ";
    cin >> n;

    vector<int> store(n + 1);
    calculateCatalan(store, n);

    cout << "\nThe numbers are:" << endl;
    for (int i = 0; i <= n; i += 1) cout << store[i] << " ";
    cout << endl;

    return 0;
}

int calculateCatalan(vector<int> &store, int n) {
    // By using a vector we are reducing time complexity via Dynamic Programming
    if (n == 0) store[n] = 1;

    // The base for catalan is C(i) * C(n - i)
    if (store[n] == 0) {
        int ans = 0;
        for (int i = 1; i <= n; i += 1) ans += calculateCatalan(store, i - 1) * calculateCatalan(store, n - i);
        store[n] = ans;
    }

    return store[n];
}