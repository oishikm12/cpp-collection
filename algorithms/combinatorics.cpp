#include <iostream>
using namespace std;

int factorial(int);
int combine(int, int);
int permute(int, int);

int main() {
    /**
     * Combinatorics requires the use of factorials
     */ 
    cout << "\nThis program calculates combination & permutation of a number.\n" << endl;
    int n, r;
    cout << "Enter value of n : ";
    cin >> n;
    cout << "Enter value of r : ";
    cin >> r;

    cout << "Permutation of these numbers is, " << permute(n, r) << endl;
    cout << "Combination of these numbers is, " << combine(n, r) << endl;
    cout << endl;
    
    return 0;
}

int factorial(int val) {
    int res = 1;
    while (val > 0) {
        res *= val;
        val -= 1;
    }
    return res;
}

int combine(int n, int r) {
    // n!/r!(n-r)!
    return factorial(n) / (factorial(r) * factorial(n - r));
}

int permute(int n, int r) {
    // n!/(n-r)!
    return factorial(n) / factorial(n - r);
}