#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>
using namespace std;

class Cell {
    // Utility Class to represent each cell of grid
    // and to hold A* value of the cell itself
    public:
        pair<int, int> parent;
        // f(x) = g(x) + h(x), i.e. current cost = cost to reach here + cost to reach dest from here 
        double fOx, gOx, hOx;
        // Contructor for default values
        Cell() : parent({-1, -1}), fOx(-1), gOx(-1), hOx(-1) {};
};

void aStarSearch(vector<vector<char>> &, pair<int, int> &, pair<int, int> &);
bool valid(vector<vector<char>> &, pair<int, int> &);
bool blocked(vector<vector<char>> &, pair<int, int> &);
double calculateHeuristics(pair<int, int> &, pair<int, int> &);
void tracePath(vector<vector<Cell>> &, pair<int, int> &);

int main() {
    /**
     * A* algorithm unlike other search algorithms, uses a heuristic search
     * function to estimate the best possible move to make. In practical
     * sense, the destination is already known, so is the cost to reach it
     */ 
    cout << "\nThis program finds a certain element from a starting point, in a grid of obstacles.\n" << endl;
    int row, col;
    cout << "Enter space seperated dimensions of the grid to consider," << endl;
    cin >> row >> col;

    pair<int, int> source, destination;
    vector<vector<char>> grid(row, vector<char>(col));

    cout << "Represent the grid as `0`s for open cell, `1`s for obstacle," << endl;
    for (auto &x : grid) for (auto &y : x) cin >> y;

    cout << "\nEnter space seperated coordinates for start," << endl;
    cin >> source.first >> source.second;

    cout << "\nEnter space seperated coordinates for end," << endl;
    cin >> destination.first >> destination.second;

    aStarSearch(grid, source, destination);

    cout << endl;

    return 0;
}

void aStarSearch(vector<vector<char>> &grid, pair<int, int> &src, pair<int, int> &dest) {
    if (!valid(grid, src)) {
        cout << "\nInvalid Starting Point" << endl;
        return;
    }

    if (!valid(grid, dest)) {
        cout << "\nInvalid Ending Point" << endl;
        return;
    }

    if (blocked(grid, src) || blocked(grid, dest)) {
        cout << "\nThere is no way in or out of either source or destination" << endl;
        return;
    }

    if (src == dest) {
        cout << "\nWe are already at destination" << endl;
        return;
    }

    int r = grid.size();
    int c = grid[0].size();

    // We use a closed list to keep track of visited cells
    vector<vector<bool>> closedList(r, vector<bool>(c, false));

    // Similarly we create a 2D grid of cell information
    vector<vector<Cell>> cellDetails(r, vector<Cell>(c));

    // Initialising the parameters of the starting node
    cellDetails[src.first][src.second].fOx = 0.0;
    cellDetails[src.first][src.second].gOx = 0.0;
    cellDetails[src.first][src.second].hOx = 0.0;
    // We set the parent of source to source itself
    cellDetails[src.first][src.second].parent = { src.first, src.second };

    // OpenList stores all the cells, yet to visit, in increasing order of cost
    // <f, <i, j>> where f = g + h,  and i, j are the row and column index of that cell
    priority_queue<tuple<double, int, int>, vector<tuple<double, int, int>>, greater<tuple<double, int, int>>> openList;

    // We enter the starting cell, and set its f(x) as 0.0
    openList.push({0.0, src.first, src.second});

    // To keep track of iterations
    int iterations = 1000;

    // We then continue to loop, till we reach the destination
    while ((--iterations) && !openList.empty()) {
        auto [cost, i, j] = openList.top();

        // Removed from openlist, and added to closed, since visited
        openList.pop();
        closedList[i][j] = true;

        // There are 8 possible movements from this cell onwards
        // namely N, NE, E, SE, S, SW, W, NW
        vector<pair<int, int>> movements = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

        for (auto &[addX, addY] : movements) {
            pair<int, int> neighbour = {i + addX, j + addY}; 

            if (!valid(grid, neighbour)) continue;

            if (neighbour == dest) {
                // This is the destination cell itself, hence we update the records
                cellDetails[neighbour.first][neighbour.second].parent = { i, j };
                
                cout << "\nThe optimal path to take from source to destination is," << endl;
                tracePath(cellDetails, dest);

                return;
            } else if (!closedList[neighbour.first][neighbour.second] && !blocked(grid, neighbour)) {
                // This is a possible path we might consider for route
                // f(x) for this node is [g(x) of parent + 1] + [calcHeuristics(curr, dest)]
                double gNew = cellDetails[i][j].gOx + 1.0;
                double hNew = calculateHeuristics(neighbour, dest);
                double fNew = gNew + hNew;

                // If it isn’t on the open list, add it to the open list. Make the
                // current square the parent of this square. Record the f, g, and h
                // costs of the square cell
                //             OR
                // If it is on the open list already, check to see if this
                // path to that square is better, using 'f' cost as the measure.
                if (cellDetails[neighbour.first][neighbour.second].fOx == -1 || cellDetails[neighbour.first][neighbour.second].fOx > fNew) {
                    openList.push({fNew, neighbour.first, neighbour.second});

                    // We then update the details of the cell
                    cellDetails[neighbour.first][neighbour.second].fOx = fNew;
                    cellDetails[neighbour.first][neighbour.second].gOx = gNew;
                    cellDetails[neighbour.first][neighbour.second].hOx = hNew;
                    cellDetails[neighbour.first][neighbour.second].parent = { i, j };
                }
            }
        }
    }

    // If we reach here, then there is likely no solution
    cout << "\nThere is no way to reach destination" << endl;
}

bool valid(vector<vector<char>> &grid, pair<int, int> &coords) {
    // If the given coordinates exceed limits, or 
    // grid is not initialized, then we return as invalid
    if (grid.size() == 0 || grid[0].size() == 0) return false;

    if (coords.first < 0 || coords.first >= grid.size()) return false;

    if (coords.second < 0 || coords.second >= grid[0].size()) return false;

    return true;
}

bool blocked(vector<vector<char>> &grid, pair<int, int> &coords) {
    // Returns true if the cell itself is closed
    if (!valid(grid, coords)) return true;

    if (grid[coords.first][coords.second] != '0') return true;

    return false;
}

double calculateHeuristics(pair<int, int> &src, pair<int, int> &dest) {
    // h is estimated with the two points distance formula, i.e. euclidean distance
    return sqrt(pow((src.first - dest.first), 2.0) + pow((src.second - dest.second), 2.0));
}

void tracePath(vector<vector<Cell>> &cellDetails, pair<int, int> &dest) {
    int r = cellDetails.size();
    int c = cellDetails[0].size();

    // We will use this as a visual display of path, hence we use `.` as placeholder
    vector<vector<char>> tempGrid(r, vector<char>(c, '.'));

    // Variables to iterate over the path
    int i = dest.first;
    int j = dest.second;
    Cell curr = cellDetails[i][j];

    // We set the source as 'S' & destination as 'D'
    tempGrid[i][j] = 'D';

    while (curr.parent != make_pair(i, j)) {
        i = curr.parent.first;
        j = curr.parent.second;
        tempGrid[i][j] = '+';
        curr = cellDetails[i][j];
    }

    // When the parent matches itself, we are at source node
    tempGrid[i][j] = 'S';

    for (auto &x : tempGrid) {
        for (auto &y : x) cout << y << ' ';
        cout << endl;
    }
}