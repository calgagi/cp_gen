class graph {
public:
    vector<vector<array<int,2>>> adj;

    graph(int n) {
        adj.resize(n);
        return;
    }
    
    void add_directed(int u, int v, int w) {
        assert(u >= 0 && u < (int) adj.size()), assert(v >= 0 && v < (int) adj.size());
        adj[u].push_back({v, w});
        return;
    }

    void add_undirected(int u, int v, int w) {
        add_directed(u, v, w), add_directed(v, u, w);
        return;
    }
};
