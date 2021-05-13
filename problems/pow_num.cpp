#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1e9 + 7;

int modMul(long long a, long long b) { return (a % MOD * b % MOD) % MOD; }

int superPower(long long, long long);

int main() {
    /**
     * In order to find out power of a number we
     * use Euclid's algorithm however we simply add modular
     * functions to prevent integer overflow
     */ 
    cout << "\nThis program calculates power of number under integer limits (modulo 10^9 + 7).\n" << endl;
    int num, pwr;
    cout << "Enter the number whose power to find: ";
    cin >> num;
    cout << "Enter the exponent value: ";
    cin >> pwr;

    int res = superPower(num, pwr);

    cout << "\nThe value of " << num << "^" << pwr << " is " << res << "." << endl;

    cout << endl;

    return 0;
}

int superPower(long long num, long long expo) {
    int res = 1;

    while (expo > 0) {
        // Each time our exponent is odd we multiply it with result
        if (expo & 1) res = modMul(res, num); 
        num = modMul(num, num);
        // Dividing the exponent by 2 results in log n time
        expo = expo >> 1;
    }

    return res;
}