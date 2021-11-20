#include <iostream>
using namespace std;

bool isCollinear(pair<int, int> &, pair<int, int> &, pair<int, int> &);
pair<double, double> getIntersectionPoint(pair<int, int> *);

int main() {
    /**
     * In order to find out if any three lines are collinear or not, we
     * find out the area of the triangle formed by it, collinear points 
     * give us an area of 0. Then for intersection point, we simply use
     * line formulaes :
     * x = (c1b2 - c2b1)/determinant and y = (a1c2 - a2c1)/determinant
     */
    cout << "\nThis program finds out if any 3 coordinates out of 4 are collinear, if not it finds the intersection point of the two lines formed\n" << endl; 
    pair<int, int> points[4];

    cout << "Enter space seperated line delimited 4 coordinates to consider," << endl;
    for (int i = 0; i < 4; i += 1) cin >> points[i].first >> points[i].second;

    bool collinearFirst = isCollinear(points[0], points[1], points[2]);
    bool collinearSecond = isCollinear(points[1], points[2], points[3]);
    bool isCollinear = collinearFirst || collinearSecond;

    if (isCollinear) cout << "\n3 points in the system are collinear, hence no intersection could be found." << endl;
    else {
        auto [x, y] = getIntersectionPoint(points);
        if (x == __DBL_MAX__ && y == __DBL_MAX__) cout << "\nThe lines do not intersect." << endl;
        else cout << "\nThe lines intersect at, [" << x << ", " << y << "]." << endl;
    }

    cout << endl;

    return 0;
}

bool isCollinear(pair<int, int> &p1, pair<int, int> &p2, pair<int, int> &p3) {
    // Calculating the area of triangle, if the result is 0, then the points are
    // collinear. We have skipped multiplication with 0.5 to avoid floating computations
    auto &[x1, y1] = p1;
    auto &[x2, y2] = p2;
    auto &[x3, y3] = p3;

    return (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) == 0;
}

pair<double, double> getIntersectionPoint(pair<int, int> *points) {
    // Let the given lines be : [a1x + b1y = c1] & [a2x + b2y = c2]
    // We have to now solve these 2 equations to find the point of intersection. 
    // To solve, we multiply 1. by b2 and 2 by b1 This gives us,
    // [a1b2x + b1b2y = c1b2] & [a2b1x + b2b1y = c2b1] Subtracting these we get,
    // [(a1b2 – a2b1) x = c1b2 – c2b1]. Thus if the determinant is not 0
    // x = (c1b2 - c2b1)/determinant and y = (a1c2 - a2c1)/determinant
    auto &[x1, y1] = points[0];
    auto &[x2, y2] = points[1];
    auto &[x3, y3] = points[2];
    auto &[x4, y4] = points[3];

    // Line AB represented as a1x + b1y = c1
    double a1 = y2 - y1;
    double b1 = x1 - x2;
    double c1 = a1 * x1 + b1 * y1;
  
    // Line CD represented as a2x + b2y = c2
    double a2 = y4 - y3;
    double b2 = x3 - x4;
    double c2 = a2 * x3 + b2 * y3;
  
    double determinant = a1 * b2 - a2 * b1;
  
    if (determinant == 0) {
        // The lines are parallel, hence we return a pair of DBL_MAX
        return make_pair(__DBL_MAX__, __DBL_MAX__);
    } else {
        double x = (b2 * c1 - b1 * c2) / determinant;
        double y = (a1 * c2 - a2 * c1) / determinant;
        return make_pair(x, y);
    }
}