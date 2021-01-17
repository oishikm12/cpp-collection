#include <iostream>
using namespace std;

int main() {
    /**
     * Our task is to find out the position of the given element in special
     * series, consisting of only 7s & 4s
     */ 
    cout << "\nThis program finds out the position of an element in special series.\n" << endl;
    int num;
    cout << "Enter the special number : ";
    cin >> num;

    int len = 1;
    int ans = 0;

    // First we calculate the length of the number itself
    while (num > 0) {
        // Here we already add on possible permutations to the number
        // If the digit is 7 then we do a 2^(pos) 
        // If the digit is 4 then we do a 2^(pos - 1)
        if (num % 10 == 7) ans += (1 << len);
        else ans += (1 << (len - 1));
        num /= 10;
        len += 1;
    }

    cout << "\nThe number's position is : " << ans << endl;

    cout << endl;

    return 0;
}