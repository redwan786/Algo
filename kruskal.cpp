#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Disjoint Set (Union-Find) data structure
struct DisjointSets {
    vector<int> parent, rank;

    // Constructor: creates and initializes sets of n items
    DisjointSets(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find the representative of the set containing x
    int findSet(int x) {
        if (parent[x] != x) {
            parent[x] = findSet(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Union of sets containing x and y
    void unionSets(int x, int y) {
        int rootX = findSet(x);
        int rootY = findSet(y);

        if (rootX != rootY) {
            // Union by rank
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Edge structure
struct Edge {
    int u, v, weight;
};

// Comparator for sorting edges by weight
bool compareEdges(const Edge &a, const Edge &b) {
    return a.weight < b.weight;
}

// Kruskal's algorithm
vector<Edge> kruskal(int V, vector<Edge> &edges) {
    vector<Edge> A; // This will store the resulting MST
    DisjointSets ds(V);

    // Sort edges in increasing order by weight
    sort(edges.begin(), edges.end(), compareEdges);

    for (const Edge &edge : edges) {
        int u = edge.u;
        int v = edge.v;

        if (ds.findSet(u) != ds.findSet(v)) {
            A.push_back(edge);
            ds.unionSets(u, v);
        }
    }

    return A;
}

int main() {
    int V = 4; // Number of vertices
    vector<Edge> edges = { {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4} };

    vector<Edge> mst = kruskal(V, edges);

    cout << "Edges in the MST:" << endl;
    for (const Edge &edge : mst) {
        cout << edge.u << " -- " << edge.v << " == " << edge.weight << endl;
    }

    return 0;
}
