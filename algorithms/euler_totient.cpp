#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int getEulerTotient(int);
vector<int> calculatePhi(int, int);

int main() {
    /**
     * φ(n) of a function works on the principle that φ(ab) = φ(a) * φ(b)
     * Thus when every number can be represented as product of primes, we
     * can say φ(n) = φ(p1^a) * φ(p2^b) ... and so on. Similarly, for a 
     * multiple of prime numbers, the only numbers it is not co-prime with
     * are the multiples of prime before it, hence φ(p1^a) can be represented
     * as p1^a - p1^a-1, since p1^a-1 are the multiples of prime before it
     * Expanding this, we get φ(n) = n * (1 - 1/p1) * (1 - 1/p2) and so on
     */ 
    cout << "\nThis program finds out euler's totient of a number.\n" << endl;
    int start, end;
    cout << "Enter the starting range to consider: ";
    cin >> start;
    cout << "Enter the ending range to consider: ";
    cin >> end;

    if (start == end) {
        cout << "\nThe Euler Totient of " << start << " is " << getEulerTotient(start) << "." << endl;
    } else {
        vector<int> result = calculatePhi(start, end);
        cout << "\nThe Euler Totients are," << endl;
        for (int i = start; i <= end; i += 1) {
            cout << "φ(" << i << ") = " << result[i - start] << endl;
        }
    }

    cout << endl;

    return 0;
}

vector<int> calculatePhi(int start, int end) {
    vector<int> totient(end + 1);

    // Initially we consider each number to have exactly that
    // many numbers coprime to it
    for (int i = 0; i <= end; i += 1) totient[i] = i;
    
    // phi(n) => phi(p1^a1)*phi(p2^a2)*phi(p3^a3)..
    // hence we simply iterate over primes, and
    for (int i = 2; i <= end; i += 1) {
        // If the number is equal to its positional value, it
        // represents that the number is a prime, and thus has
        // n - 1 numbers coprime to it
        if (totient[i] != i) continue;
        
        totient[i] -= 1;
        
        for (int j = 2 * i; j <= end; j += i) {
            //  multiply its multiples via (p - 1) / p
            // i.e. removinf count of those which are not coprime
            totient[j] = (totient[j] * (i - 1)) / i;
        }
    }

    vector<int> desired;
    for (int i = start; i <= end; i += 1) desired.push_back(totient[i]);

    return desired;
}

int getEulerTotient(int num) {
    int coprimeCnt = num;

    for (int i = 2; i <= sqrt(num); i += 1) {
        // Since we have to reduce a number to a product of
        // its primes, we simply find a prime that divides it,
        // remove all multiples of that prime from the number
        if (num % i == 0) {
            while (num % i == 0) num = num / i;

            // And simply use the formulae n * (i - 1) / i
            coprimeCnt = (coprimeCnt * (i - 1)) / i;
        }
    } 

    // The last number remaining, would be the last prime
    // hence we use the same formulae for it
    if (num > 1) coprimeCnt = (coprimeCnt * (num - 1)) / num;

    return coprimeCnt;
}