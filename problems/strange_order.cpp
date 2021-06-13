#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

void sieve(vector<int> &, int);
vector<int> getOrder(int);

int main() {
    /**
     * In order for us to find all numbers which share a non-one common
     * factor, we will use sieve, to mark what the lowest prime divisor
     * of every number is.
     */ 
    cout << "\nThis program prints numbers in specific order such that number which share a prime factor appear before others.\n" << endl;
    int n;
    cout << "Enter the upper limit till which to print: ";
    cin >> n;

    vector<int> order = getOrder(n);

    cout << "The numbers from 1 to " << n << " printed in strange order are," << endl;
    for (int i = 0; i < n; i += 1) {
        cout << order[i];
        if (i != n - 1) cout << " ";
    }
    cout << endl;

    cout << endl;

    return 0;
}

void sieve(vector<int> &divisors, int n) {
    // We first initialize each number as its own lowest 
    // divisors, this case will always be true for primes
    for (int i = 0; i <= n; i += 1) divisors[i] = i;
    
    for (int i = 2; i <= sqrt(n); i += 1) {
        if (divisors[i] == i) {
            // If the current number is prime, every one of its
            // multiple will have that prime as its lowest prime divisor
            for (int j = 2 * i; j <= n; j += i) divisors[j] = i;
        }
    }
}

vector<int> getOrder(int n) {
    // We use this to store the resultant order
    vector<int> result;

    // We then find out minimal prime divisors for
    // all numbers in that given range
    vector<int> divisors(n + 1);
    sieve(divisors, n);

    // This will be used to mark already visited numbers from 1 .. n
    vector<bool> marked(n + 1, false);

    for (int i = n; i > 0; i -= 1) {
        // All numbers which share a non-1 GCD with the current value of
        // i will be stored in this vector
        vector<int> temp;
        
        // We only visit a number if it has not been visited before
        if (!marked[i]) {
            int num = i;
            marked[num] = true;
            temp.push_back(num);
            
            while (num > 1) {
                int curr = i;
                int lowestPrimeDiv = divisors[num];
                
                while (curr != lowestPrimeDiv) {
                    // We then find out all the numbers which are divisible
                    // by the same lowest Prime divisors, since their GCD
                    // with i, is likely to be the prime divisor itself
                    curr = curr - lowestPrimeDiv;
                    
                    if (!marked[curr]) {
                    	marked[curr] = true;
                    	temp.push_back(curr);
                    }
                }
                
                // In order to find the next lowest prime divisor, we divide
                // the number with the current LPD, till it is no longer divisible
                // that way the end result will have a different LPD
                while (num % lowestPrimeDiv == 0) num = num / lowestPrimeDiv;
            }
        }
        
        // We sort the numbers for current in descending order and 
        // store them into result
        sort(temp.begin(), temp.end(), greater<int>());
        for (auto &x : temp) result.push_back(x);
    }

    return result;
}