#include <iostream>
using namespace std;

int fastPow(int, unsigned int);

int main() {
    /**
     * Fast Power divides the power of a element by 2 until we reach a power
     * of 0 where we return 1. This reduces time to compute to log n
     */ 
    cout << "\nThis program finds out power of number.\n" << endl;
    int base, pwr;
    cout << "Enter base number : ";
    cin >> base;
    cout << "Enter power to raise : ";
    cin >> pwr;

    cout << endl << base << " raised to " << pwr << " is : " << fastPow(base, pwr) << endl;

    cout << endl;

    return 0;
}

int fastPow(int base, unsigned int power) {
    // We simply recurse till the value of power is 0
    if (power == 0) return 1;

    // Each time we reduce power by 2, we have to multiply it to itself
    int tempPow = fastPow(base, power / 2);
    tempPow *= tempPow;

    // Odd powers cannot be divide into exact halves
    if (power & 1) return base * tempPow;
    else return tempPow;
}