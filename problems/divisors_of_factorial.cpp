#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void generateSieve(vector<bool> &);
int calcRepetations(int);
int calcDivisors(int);

int main() {
    /**
     * In order to find out how many divisors of a number, we first
     * need to represent the number itself as a power of primes
     * Once we have that, the number of divisors simply product of
     * the powers of those primes + 1. We simply repeat this for all
     * numbers in the factorial series
     */ 
    cout << "\nThis program finds out the total divisors in factorial of a number.\n" << endl;
    int num;
    cout << "Enter the number whose count of divisors of factorial to find: ";
    cin >> num;

    int divCount = calcDivisors(num);

    cout << "\nThere are " << divCount << " divisors for the factorial of " << num << "." << endl;

    cout << endl;

    return 0;
}

int calcDivisors(int num) {
    // We first need to find all primes that can occur, we know that no
    // prime greater than the nmber itself will divide the number
    vector<bool> primes(num + 1, true);
    generateSieve(primes); 

    // For every prime factor, we will be multiplying their powers
    // hence we start with 1 i.e, 1 * (a + 1) * (b + 1) * (c + 1)...
    // NOTE: The reason we add 1 to each power, as 0 is not included
    int res = 1;

    for (int i = 0; i <= num; i += 1) {
        // We only need to consider prime factors of a number
        // Since this is factorial, we know that all primes
        // are bound to be divisors of some number
        if (primes[i] == false) continue;

		res = res * (calcRepetations(i, num) + 1);
    }
    
    return res;
}

int calcRepetations(int prime, int num) {
    int val = 0;

    // For all the number in the factorial of num
    // i.e. 1 ... num, we know that 2 will appear as a divisor
    // for 2, 2 + 2, 2 + 2 + 2 and so on, the same will be true for
    // all primes, hence we need to simply find out how many times
    // this divisor will appear in the range 1 ... num => num / prime
    int curr = num / prime;
    
    // We know that when a prime appears in a sequence it's 
    // its powers are also bound to appear, so we add for them
    // For example, 2 -> 2, 4, 6, 8 ... etc => n / 2
    // 2^2 -> 4, 8, 16 ... etc => n / 2^2
    // 2^k => n / 2^k. 
    // Generatlizing this, (n / p^k) where p is a prime &  p^k <= n
    while (curr > 0) {
        val = val + curr;
        curr = curr / prime;
    }
    
    return val;
}

void generateSieve(vector<bool> &primes) {
    int n = primes.size() - 1;
    primes[0] = primes[1] = false;
    
    for (int i = 2; i <= sqrt(n); i += 1) {
        if (primes[i]) {
            for (int j = i * i; j <= n; j += i) primes[j] = false;
        }
    }
}
