#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int partition(vector<int>&, int, int);
int randPvt(vector<int>&, int, int);
void qsort(vector<int>&, int, int);

int main() {
    /**
     * QSort has an average complexity of nlog n, thereby making it more
     * efficient than others. It works on the priniciple of moving an element
     * to its sorted position in an array
     */ 
    cout << "\nThis program sorts a given array via quick sort.\n" << endl;
    int len;
    cout << "Enter length of array : ";
    cin >> len;

    vector<int> arr(len);

    cout << "Enter space seperated elements of array," << endl;
    for (int i = 0; i < len; i += 1) cin >> arr[i];

    qsort(arr, 0, len - 1);

    cout << "\nThe sorted array is," << endl;
    for (int i = 0; i < len; i += 1) {
        cout << arr[i];
        if (i == len - 1) cout << endl;
        else cout << ", ";
    }

    cout << endl;

    return 0;
}

void qsort(vector<int> &arr, int low, int high) {
    // We partion the array, and call qs on the partioned array
    // While low is less than high, the array is not sorted yet
    if (low < high) {
        int pivot = randPvt(arr, low, high);
        qsort(arr, low, pivot - 1);
        qsort(arr, pivot + 1, high);
    }
}

int randPvt(vector<int> &arr, int low, int high) {
    // Random Pivoting ensures nlogn complexity even when array 
    // is presorted or almost sorted
    srand(time(NULL));

    int random = low + rand() % (high - low);
    swap(arr[random], arr[high]);

    return partition(arr, low, high);
}

int partition(vector<int> &arr, int low, int high) {
    // i th index represents all elements less than pivot
    int i = low - 1;
    // We are taking the pivot to be last element
    int pivot = arr[high];

    for (int j = low; j <= high - 1; j += 1) {
        if (arr[j] <= pivot) {
            i += 1;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]); // Place the pivot in its correct position
    return i + 1; // Return Index of pivot
}