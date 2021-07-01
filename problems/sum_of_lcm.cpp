#include <iostream>
#include <vector>
using namespace std;

void calculateTotient(vector<int> &, int);
int calculateSum(int);

int main() {
    /**
     * In order to find out the sum of lcm, we can simply convert the
     * LCM in the form of a * b / gcd(a, b). Upon further exploration
     * this can be reduced to sum of n^2 / gcd(i, n). However since 
     * GCD itself is likely to be repeated multiple times we can find
     * out its count via Euler's Totient Function since the number of
     * co-primes can be determines n / d
     */ 
    cout << "\nThis program finds out sum of LCM of numbers from [1, n] to [n, n].\n" << endl;
    int num;
    cout << "Enter the number whose sum of LCM to find: ";
    cin >> num;

    int result = calculateSum(num); 

    cout << "\nThe LCM sum of " << num << " is " << result << "." << endl;

    cout << endl;

    return 0; 
}

void calculateTotient(vector<int> &totient, int n) {
    // Initially we consider each number to have exactly that
    // many numbers coprime to it
    for (int i = 0; i <= n; i += 1) totient[i] = i;

    // phi(n) => phi(p1^a1)*phi(p2^a2)*phi(p3^a3)..
    // hence we simply iterate over primes, and
    for (int i = 2; i <= n; i += 1) {
        // If the number is equal to its positional value, it
        // represents that the number is a prime, and thus has
        // n - 1 numbers coprime to it
        if (totient[i] != i) continue;

        totient[i] -= 1;

        for (int j = 2 * i; j <= n; j += i) {
            //  multiply its multiples via (p - 1) / p
            // i.e. removinf count of those which are not coprime
            totient[j] = (totient[j] * (i - 1)) / i;
        }
    }
}

int calculateSum(int n) {
    vector<int> totient(n + 1), result(n + 1);
    calculateTotient(totient, n);

    // Calculating LCM of a number can be condensed into 
    // LCM (a, b) = a * b / gcd(a, b). Putting this into perspective
    // Sum [LCM(i, n)] = ∑ (i * n / gcd(i, n)). In other words,
    // this can be shortened to 2 * S - 2 * n = ∑ n^2 / gcd(i, n)
    // ∑LCM(i, n) = ((∑(d * ETF(d)) + 1) * n) / 2 , where d is the 
    // number of divisors for that specific number
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            // All these numbers are divisible by i, hence we add onto them
            // the value d * ETF(d)
            result[j] += (i * totient[i]);
        }
    }
    
    for (int i = 1; i <= n; i += 1) {
        result[i] = (result[i] + 1) * (i / 2);
    }

    return result[n];
}