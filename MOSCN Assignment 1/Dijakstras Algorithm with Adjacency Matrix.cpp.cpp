#include <iostream>
#include <climits>
using namespace std;

#define V 6  // Number of vertices

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool visited[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[]) {
    cout << "Vertex \t Distance from Source\n";
    for (int i = 0; i < V; i++)
        cout << i << " \t\t " << dist[i] << endl;
}

// Implementation of Dijkstra’s algorithm for adjacency matrix
void dijkstra(int graph[V][V], int src) {
    int dist[V];     // Output array: dist[i] holds the shortest distance from src to i
    bool visited[V]; // visited[i] will be true if vertex i’s shortest distance is finalized

    // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, visited[i] = false;

    // Distance from source to itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = true;

        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist);
}

// Driver code
int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 10},
        {4, 0, 3, 0, 0, 0},
        {0, 3, 0, 2, 4, 0},
        {0, 0, 2, 0, 1, 0},
        {0, 0, 4, 1, 0, 5},
        {10, 0, 0, 0, 5, 0}
    };

    dijkstra(graph, 0); // Start from vertex 0
    return 0;
}

