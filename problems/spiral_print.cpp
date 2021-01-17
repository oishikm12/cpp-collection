#include <iostream>
#include <vector>
using namespace std;

void spiral(vector<vector<int>>&, int);
void print(vector<int>&, int);

int main() {
    /**
     * Spiral printing is going through a matrix spirally
     */
    cout << "\nThis program prints a matrix spirally.\n" << endl;
    int len;
    cout << "Enter height & width of image : ";
    cin >> len;

    vector<vector<int>> arr(len, vector<int>(len));

    cout << "Enter space seperated, line delimited elements of matrix," << endl;
    for (int i = 0; i < len; i += 1) {
        for (int j = 0; j < len; j += 1) cin >> arr[i][j];
    }

    spiral(arr, len);

    cout << endl;

    return 0;
}

void spiral(vector<vector<int>> &arr, int len) {
    // This basically iterates over borders & moves to next
    vector<int> spir(len * len);

    int row_start = 0, col_start = 0;
    int row_end = len, col_end = len;
    int i = 0, j = 0;
    // k - starting row index 
    // m - ending row index 
    // l - starting column index 
    // n - ending column index 
  
    while (row_start < row_end && col_start < col_end) { 
        for (i = col_start; i < col_end; i += 1) {
            spir[j] = arr[row_start][i];
            j += 1;
        } 
        row_start++; 
  
        for (i = row_start; i < row_end; i += 1) { 
            spir[j] = arr[i][col_end - 1]; 
            j += 1;
        } 
        col_end--; 
  
        if (row_start < row_end) { 
            for (i = col_end - 1; i >= col_start; i -= 1) { 
                spir[j] = arr[row_end - 1][i]; 
                j += 1;
            } 
            row_end--; 
        } 
  
        if (col_start < col_end) { 
            for (i = row_end - 1; i >= row_start; i -= 1) { 
                spir[j] = arr[i][col_start]; 
                j += 1;
            } 
            col_start++; 
        } 
    } 

    cout << "\nThe spiral array for this matrix is," << endl;
    print(spir, len * len);
}

void print(vector<int> &arr, int len) {
    for (int i = 0; i < len; i += 1) {
        cout << arr[i];
        if (i != len - 1) cout << " ";
    }
    cout << endl;
}