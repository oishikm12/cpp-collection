#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool isInside(vector<pair<double, double>> &, pair<double, double> &);
int probability(vector<pair<double, double>> &, pair<double, double> &, pair<double, double> &);
double polygonArea(vector<pair<double, double>> &);
double crossProduct(pair<double, double> &, pair<double, double> &);
double manchesterDistance(pair<double, double> &, pair<double, double> &);

int main() {
    /**
     * In order to find out wether a person is in vicinity of bomb we simply
     * traverse each point to see if the current point is outside them, if so
     * we calculate its probablity based on distance from area of explosion
     */
    cout << "\nThis program finds out the probablity of each person in the vicinity of a bomb, to be the detonator\n" << endl;
    
    int vertices;
    cout << "Enter the number of coordinates defining the area of explosion: ";
    cin >> vertices; 

    vector<pair<double, double>> points(vertices);
    cout << "Enter space seperated line delimited coordinates of the vicinity of the bomb," << endl;
    for (auto &[x, y] : points) cin >> x >> y;

    pair<double, double> bomb;
    cout << "Enter space seperated approx coordinates of the bomb: ";
    cin >> bomb.first >> bomb.second;

    int n;
    cout << "Enter the number of people near the bomb: ";
    cin >> n;

    vector<pair<double, double>> people(n);
    cout << "Enter space seperated line delimited coordinates of the people near the bomb," << endl;
    for (auto &[x, y] : people) cin >> x >> y; 

    cout << "\nThe probablity for each of the person is," << endl;
    for (auto &curr : people) {
        cout << "[" << curr.first << ", " << curr.second << "] -> ";
        if (!isInside(points, curr)) {
            cout << "Person was outside blast radius & has a probablity of " << probability(points, curr, bomb) << "%, being the detonator." << endl; 
        } else {
            cout << "Person was inside the blast radius" << endl;
        }
    }

    cout << endl;

    return 0;
}

bool isInside(vector<pair<double, double>> &points, pair<double, double> &curr) {
    int n = points.size();
    int counter = 0;

    for (int i = 0; i < n; i += 1) {
        auto &[x1, y1] = points[i];
        auto &[x2, y2] = points[(i + 1) % n];

        // These two points represent a horizontal line, hence we cannot understand border
        if (y1 == y2) continue;

        // If the current point is outside the y axis boundings or, greater than x axis
        // boundings we do not consider this point
        if (curr.second <= min(y1, y2) || curr.second > max(y1, y2)) continue;
        if (curr.first > max(x1, x2)) continue;

        // We find out the x intersection point, and check if the current point lies in it
        double xIntersection = (curr.second - y1) * (x2 - x1) / (y2 - y1) + x1;

        if (x1 == x2 || curr.first <= xIntersection) counter += 1;
    }

    // If the number of points inside is even, then this person is inside the polygon
    if (counter % 2 == 0) return true;
    else return false;
}

int probability(vector<pair<double, double>> &points, pair<double, double> &curr, pair<double, double> &bomb) {
    // Probability of a person is given being the culprit is given by
    // 100 - (distance of current point from approx coordinates of bomb / total area of the vicinity).
    double area = polygonArea(points);
    double distance = manchesterDistance(curr, bomb);

    double probability = (distance / area) * 100.0;

    return 100 - abs(probability);
}

double polygonArea(vector<pair<double, double>> &points) {
    // Area of a polygon is calculated using the shoelace formulae
    // wherein area = [SumOf. xi*yi+1 - xi+1*yi] / 2, wherein xi & yi
    // represent the distance of a coordinate from start
    int n = points.size();
    double curr = 0.0;

    for (int i = 0; i < n - 1; i += 1) {
        curr += crossProduct(points[i], points[(i + 1) % n]);
    }

    return curr / 2;
}

double crossProduct(pair<double, double> &p1, pair<double, double> &p2) {
    // Crossing between two coordinates is x1*y2 - x2*y1
    return p1.first * p2.second - p1.second * p2.first; 
}

double manchesterDistance(pair<double, double> &p1, pair<double, double> &p2) {
    // Manchester distance represents the straight line distance between 
    // any to coordinates in 2D space, hence uses Pythagorean distance
    return sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
}