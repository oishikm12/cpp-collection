#include <iostream>
#include <vector>
using namespace std;

int main() {
    /**
     * In order to find out 3 cycles we will use 3 pointers for the
     * three points in the graph, and then run them through a loop
     * to check if they are connected. Since 3! = 6, each cycle will
     * be counted six times, hence we divide the count by six
     */ 
    cout << "\nThis program counts the number of 3 cycles in a graph.\n" << endl;
    int n, m;
    cout << "Enter the number of vertices to consider in the graph: ";
    cin >> n;
    cout << "Enter the number of edges to consider in the graph: ";
    cin >> m;

    vector<pair<int, int>> edges(m);
    cout << "Enter space seperated line delimited edges to connect," << endl;
    for (auto &[x, y] : edges) cin >> x >> y;

    vector<vector<bool>> graph(n, vector<bool>(n, false));
    for (auto &[x, y] : edges) {
        graph[x - 1][y - 1] = true;
        graph[y - 1][x - 1] = true;
    }

    // We will store the count of such cycles here
    int count = 0;
    
    // Each of the three vertices are represented by i, j & k
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            // These points are not connected
            if (!graph[i][j]) continue;

            for (int k = 0; k < n; k += 1) {
                // If j is connecte to k & k to i, then a three cycle is complete
                if (graph[j][k] && graph[k][i]) count += 1;
            }
        }
    }

    // Divide by six to account for repeatations
    cout << "\nThere are " << (count / 6) << " three-cycles present" << endl;

    cout << endl;

    return 0;
}