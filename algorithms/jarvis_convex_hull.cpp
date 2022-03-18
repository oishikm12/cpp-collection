#include <iostream>
#include <vector>
using namespace std;

enum Orientation {COLINEAR, CLOCKWISE, ANTICLOCKWISE};

Orientation orientation(pair<int, int> &, pair<int, int> &, pair<int, int> &);
 
void convexHull(vector<pair<int, int>> &);

int main() {
    /**
     * The idea of Jarvis’s Algorithm is simple, we start from the 
     * leftmost point (or point with minimum x coordinate value) and 
     * we keep wrapping points in counterclockwise direction, by 
     * using orientation of the next point
     */
    cout << "\nThis program finds out the convex hull of a set of coordinates\n" << endl; 
    int n;
    cout << "Enter the number of coordinates to consider: ";
    cin >> n;

    vector<pair<int, int>> points(n);
    cout << "\nEnter space seperated line delimited coordinates of points to consider," << endl;
    for (auto &[x, y] : points) cin >> x >> y;

    cout << "\nThe coordinates of the convex hull are," << endl;
    convexHull(points);

    cout << endl;

    return 0;
}

Orientation orientation(pair<int, int> &p, pair<int, int> &q, pair<int, int> &r) {
    // To find orientation of ordered triplet (p, q, r) The function returns
    // 0 --> p, q and r are colinear
    // 1 --> Clockwise
    // 2 --> Anticlockwise
    auto &[x1, y1] = p;
    auto &[x2, y2] = q;
    auto &[x3, y3] = r;

    int val = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2);

    if (val > 0) return CLOCKWISE;
    else if (val < 0) return ANTICLOCKWISE;
    else return COLINEAR;
}
 
void convexHull(vector<pair<int, int>> &points) {
    int n = points.size();

    // In order to find out the convex hull, there must be at least 3 points
    if (n < 3) return;
 
    // Initialize Result
    vector<pair<int, int>> hull;
 
    // We find the leftmost point
    int l = 0;
    for (int i = 0; i < n; i += 1) if (points[i].first < points[l].first) l = i;
 
    // Starting from leftmost point, we keep moving anticlockwise until reach the start point
    // again. This loop runs O(h) times where h is number of points in result or output
    int p = l, q;
    do {
        // Add current point to result
        hull.push_back(points[p]);
 
        // Search for a point 'q' such that orientation(p, q, x) is anticlockwise for all 
        // points 'x'. The idea is to keep track of last visited most anticlockwise point 
        // in q. If any point 'i' is more anticlockwise than q, then update q.
        q = (p + 1) % n;
        for (int i = 0; i < n; i += 1) {
           // If i is more anticlockwise than current q, then update q
           if (orientation(points[p], points[i], points[q]) == ANTICLOCKWISE) q = i;
        }
 
        // Now q is the most anticlockwise with respect to p Set p as q for next iteration, 
        // so that q is added to result 'hull'
        p = q;

    // While we don't come to first point
    } while (p != l);  
 
    // Finally we print the result
    for (auto &[x, y] : hull) cout << x << ' ' << y << endl;
}