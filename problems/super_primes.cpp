#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int countSuperPrime(int);

int main() {
    /**
     * In order to count the number of prime divisors a number
     * can have, we will generate a Sieve of Erastosthenes till
     * that number, this can be further simplified, by assuming
     * no number has 2 prime divisors, and then subtract 1 for
     * every multiple of a prime
     */ 
    cout << "\nThis program finds out how many numbers between a range from 1 has exactly 2 prime divisors.\n" << endl;
    int n;
    cout << "Enter the upper limit of range: ";
    cin >> n;

    int cnt = countSuperPrime(n);

    cout << "There are " << cnt << " super primes from 1 to " << n << "." << endl;

    cout << endl;

    return 0;
}

int countSuperPrime(int num) {
    // Initialize a sieve uptil the required number
    // Difference being we are assuming all of them have
    // no prime divisors
    vector<int> superPrime(num + 1, 2);

    // Any number will have prime divisors upto half
    // of what that number is, starting from 2
    for (int i = 2; i <= num / 2; i += 1) {
        if (superPrime[i] == 2) {
            // For every number that has no prime divisor
            // every multiple of it will have one prime
            // divisor more, i.e. current number itself
            for (int j = i; j <= num; j += i) superPrime[j]--;
        }
    }

    // We return the count of all numbers with at least 2 prime divisors
    return count(superPrime.begin(), superPrime.end(), 0);
}