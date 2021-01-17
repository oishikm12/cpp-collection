#include <iostream>
#include <vector>
using namespace std;

void printAll(vector<int>&, int);
void kadaneSum(vector<int>&, int, vector<int>&);
void maxCircularSum(vector<int>&, int);

int main() {
    /**
     * Subarrays are all possible combinations of an array, i.e. n! sub arrays
     */
    cout << "\nThis program generates sub array from given array.\n" << endl;
    int len;
    cout << "Enter length of array : ";
    cin >> len;

    vector<int> arr(len);

    cout << "Enter space seperated elements of array," << endl;
    for (int i = 0; i < len; i += 1) cin >> arr[i];

    printAll(arr, len);
    maxCircularSum(arr, len);

    cout << endl;

    return 0;
}

void printAll(vector<int> &arr, int len) {
    cout << "\nThe sub-arrays are," << endl;
    for (int i = 0; i < len; i += 1) {
        for (int j = i; j < len; j += 1) {
            // Each individual sub array will fall under range i : j
            // This logic functions the same way as basic bubble sort
            cout << "[";
            for (int k = i; k <= j; k += 1) {
                cout << arr[k];
                if (k == j) cout << "]";
                else cout<<", ";
            }
            if (j != len - 1) cout << ", ";
        }
        cout << endl;
    }
}

void kadaneSum(vector<int> &arr, int len, vector<int> &res) {
    // res has {maxSum, start index, end index}

    int currSum = 0;
    int maxElem = arr[0];
    int maxPos = 0, midPos = 0;

    for (int i = 0; i < len; i += 1) {
        // Kadane's Algorithm works in a manner such that whenever
        // the current cumulative sum goes into negative, we consider
        // the next element to be start of a new max sum subarray
        // Note - we rest current sum to 0 whenever negative is found

        currSum = currSum + arr[i];

        if (currSum < 0) {
            midPos = i + 1;
            currSum = 0;
        } else if (res[0] < currSum) {
            res[0] = currSum;
            res[1] = midPos;
            res[2] = i;
        }

        // Max Elem stores the highest possible sub array sum
        if (maxElem < arr[i]) {
            maxElem = arr[i];
            maxPos = i;
        }
    }

    if (res[0] == 0) {
        // This scenario occurs in negative number, hence obv only 1 max
        res[0] = maxElem;
        res[1] = res[2] = maxPos;
    }
}

void maxCircularSum(vector<int> &arr, int len) {
    vector<int> normalSum = {0, 0, 0};
    kadaneSum(arr, len, normalSum);
    /**
     * Maximum sum of subarray finds out the subarray whose sum is
     * maximum, out of all possible combinations of an array
     */ 

    cout << "\nThe maximum subarray sum is : " << normalSum[0];
    cout << " [";
    for (int i = normalSum[1]; i <= normalSum[2]; i += 1) {
        cout << arr[i];
        if (i != normalSum[2]) cout << ", ";
    }
    cout << "]" << endl;

    /**
     * Circular Sum is a special case of subarray, where the last element
     * is connected to the first element 
     */
    int maxFront = normalSum[0];

    int sum = 0;
    for (int i = 0; i < len; i += 1) {
        // We find the cumulative sum, as well as negate the array
        sum += arr[i];
        arr[i] = -arr[i];
    }

    vector<int> reverseSum = {0, 0, 0};
    kadaneSum(arr, len, reverseSum);
    int maxBack = reverseSum[0];

    // this algorithm works because it explains the fact the array's sum
    // could have been maximum if the sum of minimum elements were
    // present in the cumulative sum : array-sum + max subarray sum of inverted array
    // Note - maximum sum of the inverted subarray is the minimum sum subarray
    int result = maxFront > maxBack + sum ? maxFront : maxBack + sum;

    cout << "The maximum circular subarray sum is : " << result << endl;
}