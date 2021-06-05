#include <iostream>
#include <numeric>
using namespace std;

class Equation {
    public:
        int x, y;
        int gcd;

        Equation(int v1 = 0, int v2 = 0, int hcf = 0) : x(v1), y(v2), gcd(hcf) {};
};

Equation extendedEuclid(int, int);
int MMInv(int, int);
int getPossConfigs(int, int ,int);

int main() {
    /**
     * In order to find all possible solutions to configs of a & b
     * which add up to a third value, we can use the equation aX + bY = d,
     * When, X = 0 => Y = d / b, this implies 0 <= Y <= d / b
     * Now, for aX = d - bY, we need to get [d - bY] divisible by a to get X,
     * => (d - bY) % a = 0 => So, we need to find Y' that would be the 
     * smallest value of Y such that d - bY' is divisible by a
     * => d - b(Y' + a), d - b(Y' + 2a) ... would be the next value of Y'
     */ 
    cout << "\nThis program finds out all possible permutations of two weights which sum up to a third value.\n" << endl;
    int w1, w2, target;
    cout << "Enter the first weight: ";
    cin >> w1;
    cout << "Enter the second weight: ";
    cin >> w2;
    cout << "Enter the target weight to reach: ";
    cin >> target;

    int count = getPossConfigs(w1, w2, target);

    cout << "\nThere are " << count << " possible ways to add permutations of " << w1 << " and " << w2 << " to get " << target << "." << endl;

    cout << endl;

    return 0;
}

int getPossConfigs(int a, int b, int d) {
    // We simply divide all numbers by their GCD to ensure
    // that values are in their simple form with no common factors
    int hcf = gcd(a, b);

    if (d % hcf != 0) {
        // If the GCD of coefficients is not divisible by `d`, then
        // there is no integer solution of x & y
        return 0;
    }

    if (d == 0) {
        // If the result is 0, there exists only 1 solution, 
        // i.e. not to select any weights, x = y = 0
        return 1;
    }

    a = a / hcf;
    b = b / hcf;
    d = d / hcf;

    // Getting smallest value of Y' for which  d - bY' is divisible by a
    // This can be found in O(log(max(a, b))) by using Multiplicative Modulo Inverse,
    // Previously, (d - bY) % a = 0 => (d % a) - (b % a) * (Y % a) = 0
    // If we were to aggregate this equation, Y % a can be written as Y`
    // This becomes Y` = (d / b) % a => This can represented by MMI as d * MMI(b, a)
    int yDash = ((d % a) * MMInv(b, a)) % a;
    int firstVal = d / b;
    
    // However the constraint here becomes 0 <= Y <= (d / b) => d >= Y` * b 
    // Otherwise no solution can exist since d is smaller
    if (d < yDash * b) return 0;
    
    // LHS of the constraint gives us 0 <= Y => 0 <= Y` + na, where
    // n is the last possible value for which Y` + na <= d / b is true
    // Thus, na <= (d / b) - Y` => n <= ((d / b) - Y') / a
    int num = (firstVal - yDash) / a;
    
    // n represnts the last value, so n + 1 represents all possible solutions
    return num + 1;
}

int MMInv(int num, int mod) {
    // A modular multiplicative inverse of an integer `a` is an 
    // integer `x` such that the product `a*x` is congruent to `1` 
    // with respect to the modulus `m`
    Equation ans = extendedEuclid(num, mod);
    return (ans.x % mod + mod) % mod;
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