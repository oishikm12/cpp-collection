#include <iostream>
#include <vector>
using namespace std;

int getSetPos(int);
void getUnique(vector<int>&, int);
void getTwoUniques(vector<int>&, int);
void getUniqueInTriplets(vector<int>&, int);

int main() {
    /**
     * In order to find a unique value in a list we simply XOR every element,
     * since XOR of same elements is 0
     */ 
    cout << "\nThis program finds out unique values.\n" << endl;
    int len, type;
    cout << "Enter length of array : ";
    cin >> len;
    cout << "Enter the type of this array,\n1. Array has 1 unique value, others occur twice\n2. Array has 2 unique value, others occur twice\n3. Array has 1 unique value, others occur thrice." << endl;
    cin >> type;
    type = type % 3;

    vector<int> arr(len);

    cout << "Enter space seperated elements of array," << endl;
    for (int i = 0; i < len; i += 1) cin >> arr[i];

    switch (type) {
        case 0:
            getUniqueInTriplets(arr, len);
            break;
        case 1:
            getUnique(arr, len);
            break;
        case 2:
            getTwoUniques(arr, len);
            break;
        default:
            getUnique(arr, len);
            break;
    }
    
    cout << endl;

    return 0;
}

void getUnique(vector<int> &arr, int len) {
    // If we XOR all elements, the dupes cancel to 0
    // Hence we are left with non dupe item
    int res = 0;

    for (int i = 0; i < len; i += 1) res = res ^ arr[i];

    cout << "\nThe unique no. is " << res << endl;
}

void getTwoUniques(vector<int> &arr, int len) {
    // We first XOR all elements two get uniques
    int res = 0;

    for (int i = 0; i < len; i += 1) res = res ^ arr[i];

    // Next we find the rightmost set bit in the result
    int setPos = getSetPos(res);
    // This becomes our mask for the value we want to scan for
    int mask = 1 << setPos;

    // Now we simply find out our nos. using XOR method
    int first = 0;
    for (int i = 0; i < len; i += 1) {
        if (mask & arr[i]) first = first ^ arr[i];
    }
    int second = res ^ first;

    cout << "\nThe first no. is " << first << " , the second no. is " << second << endl;
}

int getSetPos(int val) {
    // We simply rightshift & AND with 1 to check if a bit is set or not
    int pos = 0;

    while (val > 0) {
        if (val & 1) return pos;

        pos += 1;
        val = val >> 1;
    }

    return -1;
}

void getUniqueInTriplets(vector<int> &arr, int len) {
    // In order to find out our triplet, we consider a bit counter array
    // A 64 bit integer
    vector<int> counter(64, 0);

    for (int i = 0; i < len; i += 1) {
        // We add to counter bits from every element in array
        int pos = 0;
        int num = arr[i];

        while (num > 0) {
            counter[pos] += (num & 1);
            pos += 1;
            num = num >> 1;
        }
    }

    // Since each number is repeated thrice, if we take mod 3 of each bit
    // It should result in 0, the remainig set bits would indicate unique no.
    int pwr = 1;
    int ans = 0;

    for (int i = 0; i < 64; i += 1) {
        counter[i] = counter[i] % 3;
        ans += (counter[i] * pwr);
        pwr = pwr << 1;
    }

    cout << "\nThe unique no. is " << ans << endl;
}