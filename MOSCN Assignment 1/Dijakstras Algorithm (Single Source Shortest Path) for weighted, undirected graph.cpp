#include <iostream>
#include <climits>
using namespace std;

#define V 4  // Number of vertices (change this as needed)

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[], int src) {
    cout << "Vertex \t Distance from Source " << src << endl;
    for (int i = 0; i < V; i++)
        cout << i << " \t\t " << dist[i] << endl;
}

// Dijkstra's algorithm implementation
void dijkstra(int graph[V][V], int src) {
    int dist[V];      // Output array: dist[i] will hold the shortest distance from src to i
    bool sptSet[V];   // sptSet[i] will be true if vertex i is included in shortest path tree

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist[] of the adjacent vertices
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Print the constructed distance array
    printSolution(dist, src);
}

int main() {
    int graph[V][V] = {
        {0, 5, 10, 0},
        {5, 0, 3, 20},
        {10, 3, 0, 2},
        {0, 20, 2, 0}
    };

    int src;
    cout << "Enter the source vertex (0-" << V - 1 << "): ";
    cin >> src;

    dijkstra(graph, src);

    return 0;
}

