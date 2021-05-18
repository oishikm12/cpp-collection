#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    /**
     * In order to find cartesion area of rectangles rooted at
     * center, we only need to find area of a quarter and multiply
     * by 4. We only need to store x & y coords as pairs
     */ 
    cout << "\nThis program finds out area covered by rectangles in cartesian plane.\n" << endl;
    int n;
    cout << "Enter number of rectangles to consider: ";
    cin >> n;

    vector<pair<int, int>> grid(n + 1);
    // Origin Center
    grid[0] = make_pair(0, 0);

    cout << "\nEnter space seperated line delimted x & y coords of each rectangle." << endl;
    for (int i = 0; i < n; i += 1) {
        int x, y;
        cin >> x >> y;
        // Dividing length & breadth by 2 gives us a quarter
        grid[i] = make_pair(x / 2, y / 2);
    }

    // We sort the rectangles in descending order of breadths
    // this way the longest rectangle in x axis comes first
    // later we can compare their y axis to check how much area covered
    sort(grid.begin(), grid.end(), greater<pair<int, int>>());

    int quadArea = 0, maxSoFar = 0;

    for (int i = 0; i < n; i += 1) {
        // Comparing y axis to check current height 
        // being covered in the grid
        maxSoFar = max(maxSoFar, grid[i].second);
        // Area remains same till the next rectangle
        quadArea += maxSoFar * (grid[i].first - grid[i + 1].first);
    }

    int fullArea = quadArea * 4;

    cout << "\nThe area covered by the rectangles are: " << fullArea << endl;

    cout << endl;

    return 0;
}