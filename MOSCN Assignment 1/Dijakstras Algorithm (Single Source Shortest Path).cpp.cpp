#include <iostream>
#include <climits>
using namespace std;

// Function to find the vertex with minimum distance
int minDistance(int dist[], bool visited[], int V) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print the result
void printSolution(int dist[], int V, int src) {
    cout << "\nShortest distances from vertex " << src << ":\n";
    cout << "Vertex\tDistance\n";
    for (int i = 0; i < V; i++)
        cout << i << "\t" << dist[i] << endl;
}

// Dijkstra’s algorithm
void dijkstra(int **graph, int V, int src) {
    int *dist = new int[V];
    bool *visited = new bool[V];

    // Initialize distances and visited array
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        if (u == -1) break; // No reachable vertex left
        visited[u] = true;

        // Update distances
        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist, V, src);

    delete[] dist;
    delete[] visited;
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    // Dynamic adjacency matrix initialization
    int **graph = new int*[V];
    for (int i = 0; i < V; i++) {
        graph[i] = new int[V];
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;
    }

    cout << "\nEnter edges in the format (u v w):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w; // comment this line if graph is directed
    }

    int src;
    cout << "\nEnter source vertex: ";
    cin >> src;

    dijkstra(graph, V, src);

    // Free memory
    for (int i = 0; i < V; i++)
        delete[] graph[i];
    delete[] graph;

    return 0;
}

