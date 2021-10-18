#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {
    // Auxillary structure to store state of board at each iteration
    public:
        // Link to previous state, to derive result 
        Node *parent;
        // Current state of the board
        vector<vector<char>> board;
        // Coordinates of the blank tiles
        int x, y;
        // Misplaced tiles & distnace from source
        int cost, level;

        Node(int i, int j, int lvl, Node *par, vector<vector<char>> &state) {
            x = i;
            y = j;

            cost = INT_MAX;
            level = lvl;

            parent = par;
            board = state;
        }
};

// Comparison object to be used to order the heap
struct comp {
    bool operator()(const Node *lhs, const Node *rhs) const {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};

// Comparison function to compare two states of board
bool operator == (Node &x, Node &y) {
    for (int i = 0; i < x.board.size(); i += 1) {
        for (int j = 0; j < x.board[i].size(); j += 1) {
            if (x.board[i][j] != y.board[i][j]) return false;
        }
    }

    return true;
}

void solve(vector<vector<char>> &, vector<vector<char>> &, int, int);
int calculateHeuristicCost(vector<vector<char>> &, vector<vector<char>> &);
bool isSafe(int, int, int, int);
void printPath(Node *);

int main() {
    /**
     * In order to reach the final configuration we can slide any tile
     * next to the empty tile in all 4 directions, this holds recursively
     * As such the we use A* heuristic to determine best cost, and thus
     * solve the grid in a least cost branch and bound method
     */ 
    cout << "\nThis program solves an 8 puzzle board.\n" << endl;

    vector<vector<char>> start(3, vector<char>(3));
    cout << "\nEnter space seperated line delimited starting state of board, with empty tile denoted by _," << endl;
    for (auto &x : start) for (auto &y : x) cin >> y;

    vector<vector<char>> end(3, vector<char>(3));
    cout << "\nEnter space seperated line delimited ending state of board, with empty tile denoted by _," << endl;
    for (auto &x : end) for (auto &y : x) cin >> y;

    int x = -1, y = -1;
    for (int i = 0; i < 3; i += 1) {
        for (int j = 0; j < 3; j += 1) {
            if (start[i][j] == '_') {
                x = i, y = j;
                break;
            }
        }
    }

    if (x == -1) {
        cout << "\nThere is no empty tile to swap" << endl;
    } else {
        solve(start, end, x, y);
    }

    cout << endl;

    return 0;
}

void solve(vector<vector<char>> &start, vector<vector<char>> &end, int x, int y) {
    // Here we store the live nodes of the tree
    priority_queue<Node*, vector<Node*>, comp> states;

    // Creating a root node, and caclulating its cost
    Node *root = new Node(x, y, 0, NULL, start);
    // f(x) = g(x) + h(x) is the basic A* search function to determine cost
    root->cost = root->level + calculateHeuristicCost(root->board, end);

    states.push(root);

    // Maximum tries to allow
    int iterations = 100;

    // We find a live node with least cost, add its childrens 
    // to list of live nodes and finally deletes it from the list
    while ((--iterations) && !states.empty()) {
        // Find a live node with least estimated cost
        Node *min = states.top();
        // The found node is deleted from the list of live nodes
        states.pop();
 
        // if min is an answer node
        if (min->board == end) {
            // Printing the path from root to destination;
            cout << "It took " << min->cost << " units to reach destination" << endl; 
            cout << "The steps to reach from source to destination are,\n" << endl;
            printPath(min);
            return;
        }

        // There are 4 possible swaps for this child
        vector<pair<int, int>> moves = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

        // For each possible child of min, there are 4 new nodes
        for (auto &[addX, addY] : moves) {
            int newX = min->x + addX;
            int newY = min->y + addY;

            if (!isSafe(newX, newY, min->board.size(), min->board[0].size())) continue;

            // Creating a child node and calculate its cost
            vector<vector<char>> newBoard = min->board;
            swap(newBoard[min->x][min->y], newBoard[newX][newY]);
            Node *child = new Node(newX, newY, min->level + 1, min, newBoard);
            child->cost = child->level + calculateHeuristicCost(child->board, end);

            // Add child to list of live nodes
            states.push(child);
        }
    }

    cout << "\nThere is no way to solve this board" << endl;
}

int calculateHeuristicCost(vector<vector<char>> &curr, vector<vector<char>> &last) {
    int displacementCount = 0;

    // We loop over all elements to check how many tiles do not
    // match with where they should be in ending state
    for (int i = 0; i < curr.size(); i += 1) {
        for (int j = 0; j < curr[i].size(); j += 1) {
            if (curr[i][j] != last[i][j]) displacementCount += 1;
        }
    }

    return displacementCount;
}

bool isSafe(int x, int y, int limX, int limY) {
    // Checks if this exists inside the board grid
    return x >= 0 && x < limX && y >= 0 && y < limY;
}

void printPath(Node *curr) {
    // Recursive base case
    if (!curr) return;

    // We want to print in ascending order of board moves
    printPath(curr->parent);

    for (auto &x : curr->board) {
        for (auto &y : x) cout << y << ' ';
        cout << endl;
    }

    cout << endl;
}