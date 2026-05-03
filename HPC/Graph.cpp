/*
Design and implement Parallel Depth First Search based on existing 
algorithms using OpenMP. Use a Tree or an undirected graph for DFS
*/
#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;
    vector<bool> visited;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
        visited.resize(V, false);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected graph
    }

    void dfs(int node);
    void parallelDFS(int start);
};

// DFS function
void Graph::dfs(int node) {
    visited[node] = true;

    #pragma omp critical
    cout << node << " ";

    #pragma omp parallel for
    for (int i = 0; i < (int)adj[node].size(); i++) {
        int next = adj[node][i];

        if (!visited[next]) {
            #pragma omp critical
            {
                if (!visited[next]) {
                    dfs(next);
                }
            }
        }
    }
}

// Start DFS
void Graph::parallelDFS(int start) {
    cout << "\nParallel DFS Traversal: ";
    dfs(start);
    cout << endl;
}

int main() {
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;
    cout << "Enter starting node: ";
    cin >> start;

    g.parallelDFS(start);

    return 0;
}

/*
To implement Depth First Search (DFS) on a graph using parallel programming (OpenMP) so that different branches of the graph can be explored simultaneously.

🌐 Concept Used
DFS is a graph traversal technique that explores a node and then goes deep into its neighbors.
Normally DFS is recursive and sequential.
In this program, we use OpenMP to parallelize neighbor exploration.
🧱 Graph Representation
The graph is stored using an adjacency list:
vector<vector<int>> adj
Each index represents a node.
Each list contains its connected neighbors.
📥 User Input

The program takes input from the user:

Number of vertices (V)
Number of edges (E)
Edge pairs (u, v)
Starting node for DFS

This makes the program dynamic and flexible.

🔁 DFS Working
Step-by-step process:
Start from the given node.
Mark it as visited.
Print the node.
Explore all its neighbors.
⚡ Parallelization (OpenMP)
The key idea is:
Each node may have multiple neighbors.
These neighbors can be explored simultaneously.
OpenMP is used in:
#pragma omp parallel for
What it does:
Splits loop iterations across multiple threads.
Each thread processes one neighbor.
🔒 Synchronization (Critical Section)

Used here:

#pragma omp critical
Purpose:
Prevents race conditions
Ensures:
Only one thread prints at a time
Prevents multiple threads visiting same node simultaneously
🔄 Traversal Flow

Example graph:

0 → 1 → 3, 4
0 → 2 → 5

DFS starts at 0:

0 → 1 → 3 → 4 → 2 → 5
📤 Output
Displays nodes in DFS order
Example:
Parallel DFS Traversal: 0 1 3 4 2 5
⚠️ Important Points
Output order may slightly vary due to parallel execution
DFS is naturally sequential, so parallelization is limited
Best performance occurs in large graphs with many branches
🎯 Conclusion

This program demonstrates how Depth First Search can be enhanced using OpenMP by allowing multiple branches of a graph to be explored simultaneously, improving performance in large-scale graph processing.
*/