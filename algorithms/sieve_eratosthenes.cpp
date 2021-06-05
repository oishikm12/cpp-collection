#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void generateSeries(vector<bool> &, int);

int main() {
    /**
     * Sieve of Eratostenes allows us to generate a list of primes in a sequence 
     * very quickly by crossibg out multiples of a selected number in a list
     * The resulting list only contains primes. This allows checking in O(1) time
     */ 
    cout << "\nThis program finds out sequence of primes.\n" << endl;
    int range;
    cout << "Enter till where you would like to find primes : ";
    cin >> range;

    vector<bool> list(range + 1, true);

    generateSeries(list, range);

    cout << "\nPrimes in this range are," << endl;
    for (int i = 1; i <= range; i += 1) {
        if (list[i] == true) cout << i << " ";
    }

    cout << endl << endl;

    return 0;
}

void generateSeries(vector<bool> &list, int range) {
    // We first mark 0 & 1 as false, i.e. non prime
    list[0] = list[1] = false;

    // We then loop from 2 to range, marking non primes
    // NOTE: When finding factors of a number, all factors
    // will appear between the range of 2 and square root of number
    for (int i = 2; i <= sqrt(range); i += 1) {
        // If this number is prime, every multiple is wont be
        if (list[i] == true) {
            // NOTE: We do not need to start from 2 * i, because
            // it will already be covered primes from [1 ~ i) * i
            // instead we start from i * i
            for (int j = i * i; j <= range; j += i) list[j] = false;
        }
    }
}