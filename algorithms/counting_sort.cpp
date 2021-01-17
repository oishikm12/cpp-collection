#include <iostream>
#include <vector>
using namespace std;

int main() {
    /**
     * Count sort sorts elements in O(1) time provided we know the upper
     * limit of values of elements & the elements are +ve (Natural Nos.)
     */ 
    cout << "\nThis program sorts a given array via counting sort.\n" << endl;
    int len;
    cout << "Enter length of array : ";
    cin >> len;
    int max;
    cout << "Enter maximum possible value of any element in array : ";
    cin >> max;

    // We initialize with 0, i.e. to say there are 0 elems of this value
    // Here each index represents the actual value, element at that index
    // represents it's count
    vector<int> arr(max, 0);

    cout << "Enter space seperated elements of array," << endl;
    for (int i = 0; i < len; i += 1) {
        int temp;
        cin >> temp;
        // We directly increment the value at index by 1, indicating
        // no of times the value appears
        arr[temp] += 1;
    }

    cout << "\nThe sorted list is," << endl;
    for (int i = 0; i < max; i += 1) {
        int val = arr[i];
        for (int j = 0; j < val; j += 1) {
            cout << i;
            if (i != max - 1) cout << " ";
        }
        if (i == max - 1) cout << endl;
    }

    cout << endl;

    return 0;
}