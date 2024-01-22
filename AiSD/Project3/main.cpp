#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

const string FILE_NAME = "graph.txt";

int main() {
    ifstream file(FILE_NAME);
    if (!file.is_open()) {
        cout << "The file cannot be opened." << endl;
        return 1;
    }

    int n;
    file >> n;

    int **graph = new int *[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
        for (int j = 0; j < n; j++) {
            file >> graph[i][j];
        }
    }
    file.close();

    int start, end;
    cout << "Enter starting node: ";
    cin >> start;
    cout << "Enter target node: ";
    cin >> end;

    int *dist = new int[n];
    bool *visited = new bool[n];
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;

        visited[u] = true;

        for (int v = 0; v < n; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    cout << "The shortest path from a node " << start << " to node " << end << " is " << dist[end] << endl;

    for (int i = 0; i < n; i++)
        delete[] graph[i];
    delete[] graph;
    delete[] dist;
    delete[] visited;

    return 0;
}