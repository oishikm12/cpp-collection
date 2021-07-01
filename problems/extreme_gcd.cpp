#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

vector<int> calculatePhi(int);
int getGCDSum(int);

int main() {
    /**
     * In order to find GCD of elements cumulative to each other, we
     * can reorganize, the values to instead calculate repetition of
     * divisors via Eulers's totient function
     */
    cout << "\nThis program calculates sum of GCD such that, Sum[g(i, j)] where j = i + 1, and i, j < N.\n" << endl; 
    int range;
    cout << "Enter the upper limit of the range: ";
    cin >> range;

    int sumOfGCD = getGCDSum(range);

    cout << "\nSum of GCD pattern for " << range << " is " << sumOfGCD << "." << endl;

    cout << endl;

    return 0;
}

vector<int> calculatePhi(int range) {
    vector<int> totient(range + 1);

    // Initially we consider each number to have exactly that
    // many numbers coprime to it
    for (int i = 0; i <= range; i += 1) totient[i] = i;
    
    // phi(n) => phi(p1^a1)*phi(p2^a2)*phi(p3^a3)..
    // hence we simply iterate over primes, and
    for (int i = 2; i <= range; i += 1) {
        // If the number is equal to its positional value, it
        // represents that the number is a prime, and thus has
        // n - 1 numbers coprime to it
        if (totient[i] != i) continue;
        
        totient[i] -= 1;
        
        for (int j = 2 * i; j <= range; j += i) {
            //  multiply its multiples via (p - 1) / p
            // i.e. removinf count of those which are not coprime
            totient[j] = (totient[j] * (i - 1)) / i;
        }
    }

    return totient;
}

int getGCDSum(int num) {
    // This will be the maximum value of possible GCD, we will consider
    int lim = num * num;

    // We store the result in a seperate vector, and use a seperate
    // vector for caluclating totient for 1 to the number itself
    vector<int> phi = calculatePhi(lim);
    vector<int> result(lim, 0);

    // For GCD(i, i + 1 ... n) where i + 1 ... n is represented via j
    // we can instead find out how many times j is repeated for each
    // value of i, and thereby store it in the result itself
    for (int i = 1; i < num; i += 1) {
        for (int j = 2; i * j < lim; j += 1) {
            result[i * j] += (i * phi[j]);
        }
    }

    // Our cumulative GCD is stored between first, to nth number
    auto start = result.begin();
    auto end = result.begin();
    advance(end, num + 1);

    int sum = accumulate(start, end, 0);

    return sum;
}