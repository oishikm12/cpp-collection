#include <iostream>
using namespace std;

class Equation {
    public:
        int x, y;
        int gcd;

        // Initializes the value as needed
        Equation(int = 0, int = 0, int = 0);
};

Equation :: Equation(int val1, int val2, int hcf) {
    x = val1;
    y = val2;
    gcd = hcf;
}

Equation extendedEuclid(int, int);

int main() {
    /**
     * Extended Euclidean algorithm functions by simply finding GCD
     * recursively all the while maintaining coefficients of equations
     * a & b required to attain that GCD. At every step y becomes the
     * MMI of a % b & x becomes MMI of b % a
     */ 
    cout << "\nThis program implements Extended Euclidean Algorithm.\n" << endl;
    int a, b;
    cout << "Enter the first value whose coefficients to find: ";
    cin >> a;
    cout << "Enter the first value whose coefficients to find: ";
    cin >> b;

    Equation solvedEq = extendedEuclid(a, b);

    cout << "\nThe equation generated: " << a << "x + " << b << "y = GCD(" << a << ", " << b << ")." << endl;
    cout << "The solution computed: " << a << "(" << solvedEq.x << ") + " << b << "(" << solvedEq.y << ") = " << solvedEq.gcd << "." << endl;
    cout << "Value of x is " << solvedEq.x << ", and that of y is " << solvedEq.y << "." << endl;

    cout << endl;

    return 0;
}

Equation extendedEuclid(int a, int b) {
    // Base Case, GCD is stored in a, so equation becomes
    // 1*(gcd) + 0*b = gcd
    if (b == 0) return Equation(1, 0, a);

    // We recurse to find GCD via euclid's method
    Equation nextEqu = extendedEuclid(b, a % b);

    // GCD formulae from base case can be rearranged to
    // ax + by = gcd(a, b) = gcd(b, a % b)
    // Also, a % b = a - b * (a / b)
    // So, (b)x1 + (a % b)y1 = gcd(b, a % b)
    //  => (b)x1 + (a)y1 - (b * [a / b])y1 = gcd(b, a % b) = ax + by
    //  => b(x1 - [a / b] * y1) + a(y1) = ax + by
    // Thus, for previous step x becomes y of next,
    // x becomes x1 - [a / b] * y1 of next step
    int newX = nextEqu.y;
    int newY = nextEqu.x - (a / b) * nextEqu.y;

    return Equation(newX, newY, nextEqu.gcd);
}