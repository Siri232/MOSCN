#include <iostream>
using namespace std;

#define INF 100
#define MAX 10

int main() {
    int cost[MAX][MAX];
    int distance[MAX][MAX];
    int nextHop[MAX][MAX];
    int nodes;

    cout << "Enter the number of nodes: ";
    cin >> nodes;

    cout << "Enter the cost matrix (Enter 100 for INF):\n";
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            cin >> cost[i][j];
            cost[i][j] = (cost[i][j] == INF) ? INF : cost[i][j];
            distance[i][j] = cost[i][j];
            nextHop[i][j] = j;
        }
    }

    // Distance Vector Routing (Bellman-Ford simulation)
    for (int k = 0; k < nodes; k++) {
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                if (distance[i][j] > cost[i][k] + distance[k][j]) {
                    distance[i][j] = cost[i][k] + distance[k][j];
                    nextHop[i][j] = nextHop[i][k];
                }
            }
        }
    }

    cout << "\n--- Distance Vector Tables ---\n";
    for (int i = 0; i < nodes; i++) {
        cout << "\nRouting table for node " << i + 1 << ":\n";
        cout << "Destination\tNext Hop\tDistance\n";
        for (int j = 0; j < nodes; j++) {
            if (i == j) continue;
            cout << j + 1 << "\t\t" << nextHop[i][j] + 1 << "\t\t" << distance[i][j] << endl;
        }
    }

    return 0;
}


