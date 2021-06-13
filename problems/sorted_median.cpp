#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getMatrixMedian(vector<vector<int>> &, int, int);

int main() {
    /**
     * Since the arrays are itself sorted row wise in the matrix, and are of
     * odd length in total, we can use binary search to pick the middle element,
     * as in case of odd length, exactly n / 2 elements appear before the median
     */ 
    cout << "\nThis program finds out the median in a row wise sorted matrix.\n" << endl;
    int row, col;
    cout << "Enter the number of rows to consider: ";
    cin >> row;
    cout << "Enter the number of columns to consider: ";
    cin >> col;

    vector<vector<int>> matrix(row, vector<int>(col));
    cout << "Enter space seperated, line delimited row wise sorted elements of the matrix," << endl;
    for (int i = 0; i < row; i += 1) for (int j = 0; j < col; j += 1) cin >> matrix[i][j];

    int median = getMatrixMedian(matrix, row, col);

    cout << "\nThe median of this matrix is " << median << "." << endl;

    cout << endl;

    return 0;
}

int getMatrixMedian(vector<vector<int>> &matrix, int row, int col) {
    // Since we intend to perform binary traversal over the matrix,
    // we need to find out the lowest possible value for median,
    // and the highest possible value of median
    // The lowest element is minimum of first element of every row
    // The highest element is maximum of last element of every row
    int low = matrix[0][0];
    int high = matrix[0][col - 1];

    for (int i = 1; i < row; i += 1) {
        low = min(low, matrix[i][0]);
        high = max(high, matrix[i][col - 1]);
    }

    // Total number of elements in the matrix, median in middlemost
    int n = row * col;
    // Hence we will want at least half elements to be equal or less
    int desired = (n + 1) / 2;

    while (low < high) {
        // We assume the middle most value to be the median
        int mid = low + (high - low) / 2;

        // We need to find the count of elements lesser than or
        // equal to our chosen median value, as such we use upper_bound
        int lessCount = 0;
        // We repeat this for all rows in the matrix
        for (int i = 0; i < row; i += 1) {
            lessCount += (upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin()); 
        }

        // There are n / 2 elements before median in odd range
        // If the elements lower than median is less, we increment
        // low, thereby increasing mid, i.e increasing no. of elements
        // smaller than mid, & vice versa for greater, till we get the
        // minimal value of low, for which median is valid
        if (lessCount < desired) low = mid + 1;
        else high = mid;
    }

    return low;
}