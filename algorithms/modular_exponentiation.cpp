#include <iostream>
using namespace std;

const long long int MOD = 1e9 + 7;

int modExp(int, unsigned int);
int modMul(long long, long long);

int main() {
    /**
     * Modular Exponentiation works by converting the exponent into
     * its binary format, and thereby multiplying the number whenever
     * a set bit is found
     */ 
    cout << "\nThis program finds out power of number modulus to integer limits.\n" << endl;
    int base, pwr;
    cout << "Enter base number : ";
    cin >> base;
    cout << "Enter power to raise : ";
    cin >> pwr;

    cout << endl << base << " raised to " << pwr << " modulo " << MOD << " is : " << modExp(base, pwr) << endl;

    cout << endl;

    return 0;
}

int modMul(long long a, long long b) {
    // Simple modular mathematics to handle negative numbers
    // Long is typecasted automatically to int & vice-versa
    return (((a + MOD) % MOD) * ((b + MOD) % MOD)) % MOD;
}

int modExp(int base, unsigned int power) {
    // Initial value of result
    int result = 1;

    // The power of number can be transformed into its binary format
    // eg: 3 ^ 5 => 3 ^ (101)b 
    // This can be interpreted as 3 ^ (2^2 + 0^1 + 2^0) => 3 ^ 4 * 3 ^ (2 * 0) * 3 ^ 1
    // i.e. [(9 * 9) + 1] + [(3 * 3) * (0)] + [3 * (1)]
    while (power > 0) {
        if (power & 1) result = modMul(result, base);

        base = modMul(base, base);

        power = power >> 1;
    }

    return result;
}