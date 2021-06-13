#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<pair<int, int>> getPrimeFactors(int);
int magicCount(vector<int> &, int);

int main() {
    /**
     * In order to find out how many subarrays there are whose products are
     * divisible by a certain number, we simply use a 2 pointer approach
     * with a lagging pointer which increments when product is divisible and
     * a fast pointer which increments when product is not divisible. This
     * approach works on a principle that if a product is divisble by a  
     * number, every number added to this product subarray would also remain divisible
     */
    cout << "\nThis program finds out how many possible subarrays exist in a deck of card, wherein the product of the selected cards are divisible by a certain number.\n" << endl; 
    int n, k;
    cout << "Enter the number of cards to consider: ";
    cin >> n;
    cout << "Enter the number which should divide the product of chosen cards: ";
    cin >> k;

    vector<int> cards(n);
    cout << "Enter space sperated numbers, written on the cards," << endl;
    for (int i = 0; i < n; i += 1) cin >> cards[i];

    int pairCnt = magicCount(cards, k);

    cout << "\nFor these cards there are " << pairCnt << " possible sub-selections whose product is divisible by " << k << "." << endl;

    cout << endl;

    return 0;
}

vector<pair<int, int>> getPrimeFactors(int num) {
    // We will store the factors in pairs of, the factor itself
    // and the number of times it is present in the number
    vector<pair<int, int>> factors;

    // All of factors of a number are present between the square root
    // of a number till 1
    for (int i = 2; i <= sqrt(num); i += 1) {
        if ((num % i) != 0) continue;
    
        int cnt = 0;
        // By repeatedly dividing a number by the same factor, we
        // find out how many times it is divided, as well as remove
        // any multiples of that prime
        while ((num % i) == 0) {
            cnt += 1;
            num = num / i;
        }
        
        factors.push_back(make_pair(i, cnt));
    }

    // The number itself, i.e. whatever is remaining after
    // division by all primes is a prime factor
    if (num != 1) factors.push_back(make_pair(num, 1));

    return factors;
}

int magicCount(vector<int> &arr, int k) {
    int n = arr.size();

    // First we find out count of prime factors inside k, this will
    // allow us to find if number divides another product or not
    vector<pair<int, int>> kPrimes = getPrimeFactors(k);

    // We will calculate wether the subarray product we calculate,
    // has at least the same count as kPrime, if so, its divisible by k
    vector<pair<int, int>> ourPrimes;
    for (auto &[x, y] : kPrimes) ourPrimes.push_back(make_pair(x, 0));

    int ans = 0;
    int j = 0;

    for (int i = 0; i < n; i += 1) {
        for (auto &[x, y] : ourPrimes) {
            // We check if the current element is divisible by one of
            // the primes which divides k
            if (arr[i] % x == 0) {
                int num = arr[i];
                int prime = x;

                // If so we find out the count, i.e. how many times it divides
                int cnt = 0;
                while ((num % prime) == 0) {
                    cnt += 1;
                    num = num / prime;
                }

                // We update the count for this prime
                y += cnt;
            }
        }

        while (j <= i) {
            bool flag = true;

            for(int x = 0; x < kPrimes.size(); x += 1) {
                if(ourPrimes[x].second < kPrimes[x].second) {
                    // If th count of primes, in our current product is not
                    // divisible by k, then we simply continue to next element
                    flag = false;
                    break;
                }
            }

            // We need to multiply with next value of i
            if (!flag) break;

            // If the current produt is divisible by k, so will it be
            // after multiplying every element remaining from i to n
            ans += n - i;

            // Whenever we increment our start pointer, we remove
            // all contributions by it to our prime count
            for (auto &[x, y] : ourPrimes) {
                if (arr[j] % x == 0) {
                    int num = arr[j];
                    int prime = x;

                    // If so we find out the count, i.e. how many times it divides
                    int cnt = 0;
                    while ((num % prime) == 0) {
                        cnt += 1;
                        num = num / prime;
                    }

                    // We deduct the count for this prime
                    y -= cnt;
                }
            }
            
            j += 1;
        }
    }

    return ans;
}