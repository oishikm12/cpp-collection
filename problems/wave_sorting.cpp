#include <iostream>
#include <vector>
using namespace std;

void wavify(vector<int>&, int);
void print(vector<int>&, int);

int main() {
    /**
     * In Wave sort we try to arrange elements in such a way that starting
     * element is bigger than the 2nd element. The 3rd element is bigger
     * than 2nd as well as 4th element. This creates a wave structure
     */ 
    cout << "\nThis program sorts an array in wave format.\n" << endl;
    int len;
    cout << "Enter number of elements to consider : ";
    cin >> len;
    
    vector<int> arr(len);

    cout << "Enter space seperated numbers," << endl;
    for (int i = 0; i < len; i += 1) cin >> arr[i];

    wavify(arr, len);
    cout << "\nThe wave sorted elements are," << endl;
    print(arr, len);

    cout << endl;
    return 0;
}

void wavify(vector<int> &arr, int len) {
    // This function simply loops over each even element to ensure
    // that elements on it's left & right are smaller than itself
    for (int i = 0; i < len; i += 2) {
        if (i - 1 > 0 && arr[i - 1] > arr[i]) swap(arr[i - 1], arr[i]);
        if (i + 1 < len && arr[i] < arr[i + 1]) swap(arr[i], arr[i + 1]);
    }
}

void print(vector<int> &arr, int len) {
    for (int i = 0; i < len; i += 2) {
        cout << arr[i];
        if (i < len - 1) cout << "  ";
    }
    cout << endl << "  ";
    for (int i = 1; i < len; i += 2) {
        cout << arr[i];
        if (i < len - 1) cout << "  ";
    }
    cout << endl;
}