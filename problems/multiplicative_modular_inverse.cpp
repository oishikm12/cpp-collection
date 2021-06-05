#include <iostream>
using namespace std;

class Equation {
    public:
        int x, y;
        int gcd;

        Equation(int v1 = 0, int v2 = 0, int hcf = 0) : x(v1), y(v2), gcd(hcf) {};
};

Equation extendedEuclid(int, int);
int MMInv(int, int);

int main() {
    /**
     * For product of two numbers to be represented as A * B % M = 1
     * where M is some co-prime divisor to A we can conclude,
     * (A * B) mod M = 1 => (A * B - 1) mod M = 0
     * Thus A * B - 1 = M * q, where q is some multiplier to M
     * [A(B) + M * (-q ~ Q) = 1]
     * This can be represented in the form of ax + by = c
     * where x becomes B & y becomes Q & GCD(A, M) is c = 1
     * If we are to consider GCD(A, M) to be 1, they are coprime
     * Thus by solving this diaphantine equation we can get 
     * value of B & Q, where B is multiplicative modular inverse of A
     */ 
    cout << "\nThis program finds out the modular multiplicative inverse of a number.\n" << endl;
    int num, mod;
    cout << "Enter the number whose inverse to find: ";
    cin >> num;
    cout << "Enter a number coprime to previous: ";
    cin >> mod;

    int inv = MMInv(num, mod);

    cout << "\nThe MMI of " << num << " is " << inv << " modulo " << mod << "." << endl;

    cout << endl;

    return 0;
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