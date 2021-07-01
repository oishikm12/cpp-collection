#include <iostream>
#include <vector>
using namespace std;

typedef long long int ll;

const ll MOD = 1e9 + 7;

int modMul(ll a, ll b) {
    return ((a + MOD) % MOD * (b + MOD) % MOD) % MOD;
}

int modAdd(ll a, ll b) {
    return ((a + MOD) % MOD + (b + MOD) % MOD) % MOD;
}

int modSub(ll a, ll b) {
    return ((a % MOD - b % MOD) + MOD) % MOD;
}

vector<vector<int>> matrixMultiply(vector<vector<int>> &, vector<vector<int>> &);
vector<vector<int>> matPow(vector<vector<int>> &, ll);
int getFibonacciSum(ll);

int main() {
    /**
     * In order to find nth fibonacci number faster than linear time,
     * we use matrix exponentiation on the recurrence relation of 
     * fibonacci number, i.e. F(n) = F(n - 1) + F(n - 2)
     */ 
    cout << "\nThis program finds out the sum of fibnonacci number lying inside a range.\n" << endl;
    ll start, end;
    cout << "Enter the starting range of the series: ";
    cin >> start;
    cout << "Enter the ending range of the series: ";
    cin >> end;

    // We can rewrite the relation F(n+1) = F(n) + F(n-1) as below
    // F(end - 1)    = F(end + 1)  -  F(end), Similarly
    // F(end - 2)    = F(end)    -  F(end - 1), and so on
    // F(start)      = F(start + 2)    -  F(start + 1)
    // Adding all the equations, on left side, we have 
    // F(start) + F(start + 1) + … F(end - 1) which is Sum(end - 1).
    // Therefore, Sum(end - 1) = F(end + 1) – F(start + 1) 
    int lowerFibSum = getFibonacciSum(start + 1);
    int upperFibSum = getFibonacciSum(end + 2);

    // => Sum(end) = F(end + 2) - F(start + 1)
    int fibSum = modSub(upperFibSum, lowerFibSum);

    cout << "\nSum of "<< start << "th fibonacci number to " << end << "th fibonacci number is " << fibSum << "." << endl;

    cout << endl;

    return 0;
}

vector<vector<int>> matrixMultiply(vector<vector<int>> &first, vector<vector<int>> &second) {
    int n1 = first.size();
    int m1 = first[0].size();
    
    int n2 = second.size();
    int m2 = second[0].size();
    
    // The resultant matrix of product of two matrices has the same
    // number of rows as the first matrix, and same number of columsn
    // as the second matrix
    vector<vector<int>> result(n1, vector<int>(m2, 0));
    
    for (int i = 0; i < n1; i += 1) {
        for (int j = 0; j < m2; j += 1) {
            for (int k = 0; k < m1; k += 1) {
                // We traverse columnwise for the first matrix, 
                // and row wise from the second matrix
                result[i][j] = modAdd(result[i][j], modMul(first[i][k], second[k][j]));
            }
        }
    }
    
    return result;
}

vector<vector<int>> matPow(vector<vector<int>> &mat, ll pow) {
    // Base case, since power of 0 or 1 for matrices is same
    if (pow == 0 || pow == 1) return mat;
    
    // Recursive function for calculating power of a number
    vector<vector<int>> subMat = matPow(mat, pow / 2);
    // Since x^4 = x^2 * x^2, we simply multiply it with itself
    vector<vector<int>> result = matrixMultiply(subMat, subMat);
    
    // Condition for odd power
    if (pow & 1) return matrixMultiply(result, mat);
    else return result;
}

int getFibonacciSum(ll n) {
    if (n == 0) return 0;
    
    // Exponentiation for fibonacci can be derived in the form of matrices
    // F(n) = F(n - 1) + F(n - 2)
    // | a b |  x  | F(n)     |  => | aF(n) + bF(n - 1) |
    // | c d |     | F(n - 1) |     | cF(n) + dF(n - 1) |
    // If we place the values of a & b as 1, we get F(n) + F(n - 1) => F(n + 1)
    // Similarly if we set values of c & d as 1 & 0, we get F(n)
    // In other words,
    // | 1 1 | ^ k - 1  * | F(1) | = | F(k)     |
    // | 1 0 |            | F(0) | = | F(k - 1) |
    vector<vector<int>> base = {{1, 1}, {1, 0}};
    vector<vector<int>> init = {{1}, {0}};
    
    vector<vector<int>> result = matPow(base, n - 1);
    
    int ans = matrixMultiply(result, init)[0][0];
    
    return ans;
}