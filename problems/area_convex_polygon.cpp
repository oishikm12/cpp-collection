#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Polygon {
    private:
        vector<pair<double, double>> points;

    public:
        void insert(double, double);
        double distance(int, int);
        double area();
};

void Polygon :: insert(double x, double y) {
    // We use this function to insert a polygon coordinate into store
    points.push_back(make_pair(x, y));
}

double Polygon :: distance(int start, int end) {
    // Base case for invalid points
    if (start < 0 || start >= points.size() || end < 0 || end >= points.size()) return 0.0;
    
    // Distance between two coordinates is calculated via 
    // Manhattan formulae = sqRoot. (x2 - x1) ^ 2 + (y2 - y1) ^ 2
    auto &[x1, y1] = points[start];
    auto &[x2, y2] = points[end];

    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double Polygon :: area() {
    // Base case for polygon
    if (points.size() <= 2) return 0.0;

    // Area of a polygon is calculated using the shoelace formulae
    // wherein area = [SumOf. xi*yi+1 - xi+1*yi] / 2, wherein xi & yi
    // represent the distance of a coordinate from start
    // [Note] - Here we subtract from Point at 0, because we are using 
    //          it as base of reference, not [0, 0]
    double ans = 0;

    for (int i = 1; i < points.size() - 1; i += 1) {
        double x1 = points[i].first - points[0].first;
        double y1 = points[i].second - points[0].second;
        double x2 = points[i + 1].first - points[0].first;
        double y2 = points[i + 1].second - points[0].second;
        ans += (x1 * y2 - x2 * y1);
    }

    return abs(ans / 2);
}

int main() {
    /**
     * In order to find out the distance between two points in a polygon
     * we will use manhatten distance formulae, for the area of convex 
     * polygon we will use shoelace formulae
     */
    cout << "\nThis program finds out the distance between two points & the area of a convex polygon\n" << endl; 
    int n;
    cout << "Enter the number of sides this polygon has: ";
    cin >> n;

    Polygon poly;
    cout << "Enter space seperated, line-delimited coordinates of the vertices of the poygon," << endl;
    for (int i = 0; i < n; i += 1) {
        double x, y;
        cin >> x >> y;
        poly.insert(x, y);
    }

    int c1, c2;
    cout << "\nEnter the index of the first point: ";
    cin >> c1;
    cout << "Enter the index of the second point: ";
    cin >> c2;

    cout << "\nThe distance between those two points are, " << poly.distance(c1, c2) << endl;
    cout << "The area of this polygon is, " << poly.area() << endl;

    cout << endl;

    return 0;
}