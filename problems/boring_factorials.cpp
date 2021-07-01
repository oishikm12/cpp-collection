#include <iostream>
using namespace std;

typedef long long int ll;

ll modMul(ll, ll, ll);
ll modExp(ll, ll, ll);
ll modInv(ll, ll);

int main() {
    /**
     * In order to find modulo of a factorial of a number modulo prime
     * we will use Wilson's theorem where in (p - 1)! % p = -1
     * For a number n < p (n >= p ! will have 0 as modulo), we can say
     * (1 * 2 * ... * n * n + 1 * ... * p - 1 ) % p = -1
     * Thus, (1 * ... * n) % p = -1 * modInv(n + 1, p) * ... * mI(p - 1, p)
     */ 
    cout << "\nThis program uses Wilson's Theorem to find out modulo of a factorial to prime.\n" << endl;
    int num, prime;
    cout << "Enter the number whose factorial to find: ";
    cin >> num;
    cout << "Enter the prime with which to modulo the factorial: ";
    cin >> prime;

    int ans = 1;

    if (num >= prime) {
        // Since the number is greater than the prime, its factorial
        // will include the prme number itself as a factor
        ans = 0;
    } else {
        int temp = 1;
        // We suimply find ech of the modular inverse and multiply it
        for (int i = num + 1; i < prime; i += 1) temp = modMul(temp, modInv(i, prime), prime);
        // Since the end result is negative, we subtract it from the
        // divisor, i.e. the prime itself in this case
        ans = prime - temp;
    }

    cout << "\nThe factorial of " << num << " modulo " << prime << " is " << ans << "." << endl;

    cout << endl;

    return 0;
}

ll modMul(ll a, ll b, ll mod) {
    // Simple modular mathematics to handle negative numbers
    // Long is typecasted automatically to int & vice-versa
    return (((a + mod) % mod) * ((b + mod) % mod)) % mod;
}

ll modExp(ll base, ll power, ll mod) {
    // Initial value of result
    ll result = 1;

    // The power of number can be transformed llo its binary format
    // eg: 3 ^ 5 => 3 ^ (101)b 
    // This can be llerpreted as 3 ^ (2^2 + 0^1 + 2^0) => 3 ^ 4 * 3 ^ (2 * 0) * 3 ^ 1
    // i.e. [(9 * 9) + 1] + [(3 * 3) * (0)] + [3 * (1)]
    while (power > 0) {
        if (power & 1) result = modMul(result, base, mod);

        base = modMul(base, base, mod);

        power = power >> 1;
    }

    return result;
}

ll modInv(ll a, ll mod) { 
    // Multiplicative modular Inverse of a number can be converted
    // to power of a, p - 2, given we are finding its modulus
    // with a prime p, this is done via fermat's little theorem
    return modExp(a % mod, mod - 2, mod); 
}