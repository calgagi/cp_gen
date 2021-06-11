#pragma once
class graph {
public:
    vector<vector<pair<int, ll>>> adj;
    
    graph(int n) {
        adj = vector<vector<pair<int, ll>>>(n);
    }

    void add_directed_edge(int u, int v, ll w = 0) {
        adj[u].push_back({v, w});
    }

    void add_edge(int u, int v, ll w = 0) {
        add_directed_edge(u, v, w);
        add_directed_edge(v, u, w);
    }
};
