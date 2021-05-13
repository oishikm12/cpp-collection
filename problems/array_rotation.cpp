#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void rotateArr(vector<int>&, int, int);

int main() {
    /**
     * In order to rotate an array in linear time we simply replace every element
     * after desired distance to rotate by. This continues till we are able to
     * reach the first index we swapped
     */ 
    cout << "\nThis program rotates an array to left in linear time\n" << endl;
    int n, d;
    cout << "Enter size of array: ";
    cin >> n;
    cout << "Enter by how much to rotate: ";
    cin >> d;

    vector<int> arr(n);
    cout << "\nEnter space delimited elements to rotate" << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    rotateArr(arr, n, d);

    cout << "\nThe array after rotation is" << endl;
    for (int i = 0; i < n; i += 1) cout << arr[i] << " ";

    cout << endl;

    return 0;
}

void rotateArr(vector<int> &arr, int n, int d) {
    // HCF of the number and the rotation degree represents how many times
    // the starting index and index after distance will meet
    // d % n handles a case where we may be asked to rotate more than size
    int hcf = __gcd(n, d % n);

    for (int i = 0; i < hcf; i += 1) {
        // We first backup current element
        int temp = arr[i];
        int j = i;

        bool loop = true;

        while (loop) {
            // next element to replace
            int k = j + d;

            // round off incase we shift past length
            if (k >= n)  k -= n;
            // if we reached the staring element then rotation is completed
            if (k == i) {
                loop = false;
                break;
            }

            // shift element to its new place
            arr[j] = arr[k];
            j = k;
        }

        // restoring first value from temp
        arr[j] = temp;
    }
}
