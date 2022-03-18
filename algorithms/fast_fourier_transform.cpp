#include <iostream>
#include <complex>
#include <vector>
using namespace std;

typedef complex<double> base;
typedef long long int ll;

const double PI = acos(-1.0);

void getRecursiveFFT(vector<base> &, bool);
void getIterativeFFT(vector<base> &, bool);
vector<ll> multiplyPoly(vector<ll> &, vector<ll> &, bool);
void printPoly(vector<ll> &, ll);

int main() {
    /**
     * FFT simply converts coefficient representation of a 
     * polynomial into value representation (x, P(x)) for a 
     * series of points wherein n + 1 points are required to
     * plot a line represented by an equation of degree n
     * These value representation of two polynomials can then
     * be individually multiplied to get the value form of the
     * resulting polynomial. Inverse FFT then gives us the ans
     */
    cout << "\nThis program uses Fast Fourier Transform to find out the multiplication of two Polynomials\n" << endl; 

    int len;
    cout << "Enter the size of the polynomials to consider: ";
    cin >> len;

    vector<ll> one(len), two(len);
    cout << "Enter space seperated numerical co-efficients of the first polynomial," << endl;
    for (auto &x : one) cin >> x;
    cout << "Enter space seperated numerical co-efficients of the second polynomial," << endl;
    for (auto &y : two) cin >> y;

    bool recursively = true;
    cout << "\nEnter 1 for recursive computation, 0 for iterative: ";
    cin >> recursively;

    vector<ll> result = multiplyPoly(one, two, recursively);

    // The exponent of each polynomial starts from 0, hence we send size - 1
    // For the resulting polynomial it is the sum of maximum power on both polynomials
    // Hence it is sizeofA - 1 + sizeofB - 1 = 2 * size / result.size - 2
    cout << "\nThe multiplications of the polynomials, [";
    printPoly(one, one.size() - 1);
    cout << "] * [";
    printPoly(two, two.size() - 1);
    cout << "] are, " << endl;
    printPoly(result, result.size() - 2);

    cout << endl << endl;

    return 0;
}

void getRecursiveFFT(vector<base> &arr, bool isInverse) {
    // The difference between fft & inverse fft are so minimal
    // that we can use a boolean to represent the switch
    ll n = arr.size();

    // One element represents a degree of 0
    if (n == 1) return;

    // Even equations are added, while odd ones are subtracted, hence 
    // we recurse, in the end all are represnted as powers of i ~ complex no.
    ll half = n / 2;
    vector<base> arrEven(half);
    vector<base> arrOdd(half);

    for (ll i = 0; i < half; i += 1) {
        // A(x) = A0(x^2) + x*A1(x^2)
        arrEven[i] = arr[2 * i];
        arrOdd[i] = arr[2 * i + 1];
    }

    // Recursive calls
    getRecursiveFFT(arrEven, isInverse);
    getRecursiveFFT(arrOdd, isInverse);

    // Angle to consider ~ Omega, i.e. cube root of 1, this can also be represnted
    // as e ^ 2 * PI / n ~ cos<th> - i * sin<th>
    double angle = 2 * PI / n;
    // Inverse FFT is simply reversing the angle and dividing by normalization
    if (isInverse) angle *= -1;
    base omega(1), omegaN(cos(angle), sin(angle));

    for (ll i = 0; i < half; i += 1) {
        // Since complex numbers can be represnted as a circle, for the first half
        // we have even[i] + omega * odd[i] & other even[i] - omega * odd[i]
        arr[i] = arrEven[i] + omega * arrOdd[i];
        arr[i + half] = arrEven[i] - omega * arrOdd[i];

        if (isInverse) {
            // Inverse includes division by [n / 2], since in
            // a loop, no need to exclusively state n
            arr[i] /= 2;
            arr[i + half] /= 2;
        }

        // Each point we multiply by cos<th>, sin<th>
        omega *= omegaN;
    }
}

void getIterativeFFT(vector<base> &arr, bool isInverse) {
    // The difference between fft & inverse fft is minimal
    ll n = arr.size();

    for (int i = 1, j = 0; i < n; i += 1) {
        int bit = n >> 1;

        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;

        if (i < j) swap(arr[i], arr[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        // Angle to consider
        double angle = 2 * PI / len;
        if (isInverse) angle *= -1;

        // Omega
        base omegaLen(cos(angle), sin(angle));

        for (int i = 0; i < n; i += len) {
            base omega(1);
            
            for (int j = 0; j < len / 2; j += 1) {
                base u = arr[i + j];
                base v = arr[i + j + len / 2] * omega;

                arr[i + j] = u + v;
                arr[i + j + len / 2] = u - v;

                omega *= omegaLen;
            }
        }
    }

    if (isInverse) {
        for (base &x : arr) x /= n;
    }
}

vector<ll> multiplyPoly(vector<ll> &first, vector<ll> &second, bool useRecursive) {
    vector<base> firstFFT(first.begin(), first.end());
    vector<base> secondFFT(second.begin(), second.end());

    // Here we find out the number of points needed to reconstruct the coefficient form of
    // result, i.e. n + 1 where n is the sum of max power of both polynomials
    // However since we recurs log n times, it is better to find an n which is power of 2
    ll n = 1;
    while (n < first.size() + second.size()) n = n << 1;

    firstFFT.resize(n);
    secondFFT.resize(n);

    // Function alias, for switching between recursive & iterative implementation
    void (*getFFT)(vector<base>&, bool);
    if (useRecursive) getFFT = getRecursiveFFT;
    else getFFT = getIterativeFFT;

    getFFT(firstFFT, false);
    getFFT(secondFFT, false);

    for (int i = 0; i < n; i += 1) firstFFT[i] *= secondFFT[i];
    getFFT(firstFFT, true);

    // We round the results, to prevent this NTT can be used
    vector<ll> result(n);
    for (int i = 0; i < n; i += 1) result[i] = round(firstFFT[i].real());

    return result;
}

void printPoly(vector<ll> &polynomial, ll expo) {
    for (auto &x : polynomial) {
        // Simple variable coefficient representaion based on exponents
        if (x != 0) cout << x;
        if (expo > 0) cout << "(x^" << expo << ") + ";
        expo -= 1;
    }
}
