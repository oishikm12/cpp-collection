#include <iostream>
#include <vector>
using namespace std;

void staircase(vector<vector<int>>&, int, int, int);

int main() {
    /**
     * Staircase search is the best method for finding an element in 2d
     * sorted matrix
     */
    cout << "\nThis program finds an element in a matrix.\n" << endl;
    int row, col;
    cout << "Enter the number of rows : ";
    cin >> row;
    cout << "Enter the number of columns : ";
    cin >> col;

    vector<vector<int>> arr(row, vector<int>(col));

    cout << "Enter space seperated, line delimited elements of matrix," << endl;
    for (int i = 0; i < row; i += 1) {
        for (int j = 0; j < col; j += 1) cin >> arr[i][j];
    }

    int key;
    cout << "\nEnter the element you wish to search : ";
    cin >> key;

    staircase(arr, row, col, key);

    cout << endl;

    return 0;
}

void staircase(vector<vector<int>> &arr, int row, int col, int key) {
    // Since the array is sorted we only need to check diagonals to understand
    // how far we are from desired value's position 
    int i = 0;
    int j = col - 1;

    while (i < row && j >= 0) {
        if (arr[i][j] == key) {
            cout << "The element " << key << " was found at [" << i << ", " << j << "]." << endl;
            return;
        } else if (arr[i][j] > key) {
            j -= 1;
        } else {
            i += 1;
        }
    }

    cout << "The element " << key << " was not found." << endl;
}