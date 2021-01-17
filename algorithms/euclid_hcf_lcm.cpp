#include <iostream>
using namespace std;

int hcf(int, int);
int lcm(int, int);

int main() {
    /**
     * Euclid's Method consists of finding modulo of the bigger number with
     * the smaller number repeatedly, till one of the number becomes 0, 
     * the number then left is the hcf of the two. Thereby multipliying the
     * two numbers & dividing by their hcf gives us the lcm
     */ 
    cout << "\nThis program implements Euclid's Algorithm.\n" << endl;
    int len;
    cout << "How many numbers do you want to consider : ";
    cin >> len;
    if (len < 2) len = 2;
    int *arr = new int[len];

    cout << "Enter space seperated elements to compute," << endl;
    for (int i = 0; i < len; i += 1) cin >> arr[i];

    int highest_cf = hcf(arr[0], arr[1]);
    int lowest_cm = lcm(arr[0], arr[1]);

    for (int i = 2; i < len; i += 1) {
        highest_cf = hcf(highest_cf, arr[i]);
        lowest_cm = lcm(lowest_cm, arr[i]);
    }

    cout << "\nThe HCF of these numbers is " << highest_cf <<endl;
    cout << "The LCM of these numbers is " << lowest_cm << endl;

    cout << endl;

    return 0;
}

int hcf(int a, int b) {
    // To compute GCD we simply modulo a % b till one of the values is 0
    // NOTE: c++17 includes gcd function as part of numeric header
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

int lcm(int a, int b) {
    // To compute LCM we simply multiply the two, and divide by their HCF
    // NOTE: c++17 includes lcm function as part of numeric header
    return a * b / hcf(a, b);
}