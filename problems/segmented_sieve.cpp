#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const long long MAX = 1e10;

vector<int> generateSeries(int);
vector<int> primesInRange(int, int);

int main() {
    /**
     * In order to segment sieve of erastosthenes, we simply have to
     * find primes till the square root of the upper limit, the rest
     * of the primes can be calculated via multiples of those
     */ 
    cout << "\nThis program finds out primes between two given ranges.\n" << endl;
    int low, high;
    cout << "Enter the lower range to consider: ";
    cin >> low;
    cout << "Enter the upper range to consider: ";
    cin >> high;

    vector<int> primes = primesInRange(low, high);

    cout << "\nPrime numbers between " << low << " and " << high << " are," << endl;
    for (int i = (low == 1 ? 1 : 0); i <= high - low; i += 1) {
        if (primes[i]) {
            cout << low + i << " ";
        }
    }

    cout << endl << endl;

    return 0;
}

vector<int> generateSeries(int range) {
    vector<int> primes;
    vector<bool> list(range + 1, true);
    // We first mark 0 & 1 as false, i.e. non prime
    list[0] = list[1] = false;

    // We then loop from 2 to range, marking non primes
    // NOTE: When finding factors of a number, all factors
    // will appear between the range of 2 and square root of number
    for (int i = 2; i <= sqrt(range); i += 1) {
        // If this number is prime, every multiple is wont be
        if (list[i] == true) {
            primes.push_back(i);
            // NOTE: We do not need to start from 2 * i, because
            // it will already be covered primes from [1 ~ i) * i
            // instead we start from i * i
            for (int j = i * i; j <= range; j += i) list[j] = false;
        }
    }

    return primes;
}

vector<int> primesInRange(int low, int high) {
    // If we want to find primes till a range of 10^10, we can do
    // so by finding all primes till square root of that, and then
    // simply re-running sieve on the given range
    vector<int> basePrimes = generateSeries((int)sqrt(MAX));

    vector<int> isPrime(high - low + 1, true);

    // As with sieve, we only need to traverse till the square
    // root of the number, since any non primes after that point
    // will simply be multiples of primes before it
    for (int i = 0; basePrimes[i] * basePrimes[i] <= high; i += 1) {
        // In order to find the closest lower number divisible by another
        // we simply divide it by that number, get its floor & re-multiply
        int base = (low / basePrimes[i]) * basePrimes[i];
        if (base < low) base += basePrimes[i];

        for (int j = base; j <= high; j += basePrimes[i]) {
            // We simply iterate and make every element as multiple of primes
            isPrime[j - low] = false;
        }

        // Exception: when base is prime itself
        // eg (2/3)*3 will become 0
		// base + curr will become current prime
        if (base == basePrimes[i]) isPrime[base - low] = true;
    }

    return isPrime;
}