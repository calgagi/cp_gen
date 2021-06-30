#pragma once
class graph {
public:
    vector<vector<pair<int, ll>>> adj;
    int n;
    
    graph(int sz) {
        n = sz;
        adj = vector<vector<pair<int, ll>>>(n);
    }

    void add_edge(int u, int v, ll w = 0) {
        adj[u].push_back({v, w});
    }
};
