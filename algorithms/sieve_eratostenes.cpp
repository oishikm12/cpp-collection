#include <iostream>
#include <vector>
using namespace std;

void generateSeries(vector<int>&, int);

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

    vector<int> list(range + 1, 0);

    generateSeries(list, range);

    cout << "\nPrimes in this range are," << endl;
    for (int i = 1; i <= range; i += 1) {
        if (list[i] == 1) cout << i << " ";
    }

    cout << endl << endl;

    return 0;
}

void generateSeries(vector<int> &list, int range) {
    // First we mark 2 as prime
    list[2] = 1;

    // Now we mark all odds as prime, since even cannot be prime
    for (int i = 3; i <= range; i += 2) list[i] = 1;

    // Next we individually select each odd to mark their multiples as non prime
    for (int i = 3; i <= range; i += 2) {
        if (list[i] == 1) {
            // We start from i^2 because, 2*i, 3*i, ... are multiples of 2, 3, ...
            // We increment by 2 multiples of i, since that is where next
            // multiple is at
            for (int j = i * i; j <= range; j += (2 * i)) list[j] = 0;
        }
    }
}