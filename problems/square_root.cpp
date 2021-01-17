#include <iostream>
using namespace std;

double sq_root(int, int);

int main() {
    /**
     * In order to find square root as fast as possible, we use binary search to
     * get the most plausible number
     */ 
    cout << "\nThis program finds out the square root of a number.\n" << endl;
    int num, prec;
    cout << "Enter the number to find square root of : ";
    cin >> num;
    cout << "Enter precision, you want to calculate to : ";
    cin >> prec;

    double srt = sq_root(num, prec);

    cout << "\nThe square root of " << num << " is " << srt << "." << endl;

    cout << endl;

    return 0;
}

double sq_root(int num, int prec) {
    // The logic is the same however this time, we store the answer in a 
    // seperate variable, and the mid value in another
    int low = 1;
    int high = num;
    int mid;
    double res;

    while (low < high) {
        mid = (low + high) / 2;

        if (mid * mid == num) {
            res = (double)mid;
            break;
        } else if (mid * mid < num) {
            low = mid + 1;
            res = (double)mid;
        } else {
            high = mid - 1;
        }
    }


    // Now that we have our integer part, the fractional part is simply linear
    double inc = 0.1;

    for (int i = 0; i < prec; i += 1) {
        while (res * res <= num) res += inc;
        res -= inc;
        inc /= 10;
    }

    return res;
}