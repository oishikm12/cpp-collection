#include <iostream>
using namespace std;

int getBits(int);
int fastSetBits(int);

int main() {
    /**
     * We use simple bit manipulation to get the no. of bits set in a
     * given integer
     */ 
    cout << "\nThis program finds out set bits in a number.\n" << endl;
    int num;
    cout << "Enter the no. you would want to find about : ";
    cin >> num;

    int allBits = getBits(num);
    int setBits = fastSetBits(num);

    cout << "\nThe number has " << allBits << " bits, out of which " << setBits << " bits are set." << endl;

    cout << endl;

    return 0;
}

int getBits(int num) {
    // We simply right shift a number till the result is 0, that way we get bit count
    int count = 0;
    
    while (num > 0) {
        count += 1;
        num = num >> 1;
    }

    return count;
}

int fastSetBits(int num) {
    // We simply [AND] with the previous value till we get to 0, each iteration
    // gives us 1 bit of set count
    int count = 0;

    while (num > 0) {
        count += 1;
        num = num & (num - 1);
    }

    return count;
} 