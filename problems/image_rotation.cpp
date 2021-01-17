#include <iostream>
#include <vector>
using namespace std;

void rotation(vector<vector<int>>&, int);
void print(vector<vector<int>>&, int);

int main() {
    /**
     * Image rotation is simply interchanging rows & cols in O(1) space 
     */
    cout << "\nThis program rotates a matrix anti-clockwise.\n" << endl;
    int len;
    cout << "Enter height & width of image : ";
    cin >> len;

    vector<vector<int>> arr(len, vector<int>(len));

    cout << "Enter space seperated, line delimited elements of matrix," << endl;
    for (int i = 0; i < len; i += 1) {
        for (int j = 0; j < len; j += 1) cin >> arr[i][j];
    }

    rotation(arr, len);

    cout << endl;

    return 0;
}

void rotation(vector<vector<int>> &arr, int len) {
    // We just need to shift each corner element by 1
    for (int x = 0; x < len / 2; x += 1) { 
        // Consider elements in group of 4s
        // i.e. square has 4 corners
        for (int y = x; y < len - x - 1; y += 1) { 
            int temp = arr[x][y]; 
  
            arr[x][y] = arr[y][len - 1 - x]; 
            arr[y][len - 1 - x] = arr[len - 1 - x][len - 1 - y]; 
            arr[len - 1 - x][len - 1 - y] = arr[len - 1 - y][x]; 
            arr[len - 1 - y][x] = temp; 
        } 
    } 

    cout << "\nThe rotated matrix is," << endl;
    print(arr, len);
}

void print(vector<vector<int>> &arr, int len) {
    for (int i = 0; i < len; i += 1) {
        for (int j = 0; j < len; j += 1) {
            cout << arr[i][j];
            if (j != len - 1) cout << " ";
        }
        cout << endl;
    }
}