#include <iostream>
using namespace std;

int getBits(int);
int fastSetBits(int);
int setiThBit(int, int);
int unsetiThBit(int, int);
int clearFromMSB(int, int);
int xorTillN(int);
bool isTwoPow(int);

int main() {
    /**
     * We use simple bit manipulation to get the no. of bits set in a
     * given integer, similarly we use bitwise operators for all
     * change in numerical values
     */ 
    cout << "\nThis program performs a set of bit manipulation.\n" << endl;
    int num;
    cout << "Enter the no. you would want to find about : ";
    cin >> num;

    bool flag = true;

    while (true) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Find number of bits" << endl;
        cout << "2. Find number of set bits" << endl;
        cout << "3. Set 'i'th bit to 1" << endl;
        cout << "4. Unset 'i'th bit to 0" << endl;
        cout << "5. Clear all bits from MSB till 'i'" << endl;
        cout << "6. Find XOR of all natural numbers till " << num << endl;
        cout << "7. Check if " << num << " is a power of 2" << endl;
        cout << "8.Exit" << endl;
        int choice;
        cin >> choice;

        int i;
        bool powr;

        switch(choice) {
            case 1:
                i = getBits(num);
                cout << "\nThe number has " << i << " bits." << endl;
                break;
            case 2:
                i = fastSetBits(num);
                cout << "\n" << num << " has " << i << " bits are set." << endl;
                break;
            case 3:
                cout << "\nEnter the bit position to set: ";
                cin >> i;
                num = setiThBit(num, i);
                cout << "\nThe number after setting " << i << "th bit is " << num << "." << endl;
                break;
            case 4:
                cout << "\nEnter the bit position to unset: ";
                cin >> i;
                num = unsetiThBit(num, i);
                cout << "\nThe number after unsetting " << i << "th bit is " << num << "." << endl;
                break;
            case 5:
                cout << "\nEnter the bit position till which to clear from MSB: ";
                cin >> i;
                num = clearFromMSB(num, i);
                cout << "\nThe number after clearing till " << i << "th bit is " << num << "." << endl;
                break;
            case 6:
                i = xorTillN(num);
                cout << "\nThe XOR of natural numbers from 1 to " << num << " is " << i << "." << endl;
                break;
            case 7:
                powr = isTwoPow(num);
                if (powr) cout << num << " is a power of 2." << endl;
                else cout << num << " is not a power of 2." << endl;
                break;
            case 8:
                cout << "\nGoodbye !!!" << endl;
                flag = !flag;
                break;
            default:
                cout << "\nPlease try again" << endl;
                break;
        }
    }

    cout << endl;

    return 0;
}

int setiThBit(int num, int pos) {
    // We first find the power of 2 that is equal to pos
    // OR-ing that number with ours, sets that ith bit to 1
    int modif = (1 << pos);
    int res = num | modif;
    return res;
}

int unsetiThBit(int num, int pos) {
    // We first find the power of 2 that is equal to pos
    // We then invert this number, such that ith bit is
    // unset but rest is set, AND-ing that number with ours,
    // sets that ith bit to 0
    int modif = ~(1 << pos);
    int res = num & modif;
    return res;
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

int clearFromMSB(int num, int pos) {
    // In order to clear a number of set bits till a certain position
    // we simply need to `&` it with 0s uptil that position and 1s afterward
    // The way to get this number is simply to find the first power of
    // 2 upto that position & subtract 1 from it
    int modif = (1 << (pos)) - 1;
    int newNum = num & modif;
    return newNum;
}

int xorTillN(int num) {
    // When natural numbers are XORed, a sequence is repeated
    // every 4 turns, hence we XOR the number with 4
    int val = num % 4;
    
    // If the number is divisible by 4, XOR till then is the number
    if (val == 0) return num;
    // If the number is just after a number divisible by 4, the result is 1
    else if (val == 1) return 1;
    // Midway through the numbers the result is 1 greater than it
    else if (val == 2) return num + 1;
    // The one just before a number divisiblt by 4 is 0
    else return 0;
}

bool isTwoPow(int num) {
    // Special property of powers of 2 is that, `&` of the number
    // and any number smaller than it is always 0
    return (num & (num - 1)) == 0;
}