#pragma once
class lca : public graph {
public:
    lca(int n) : graph(n) { }

    vector<int> height;
    vector<vector<int>> lift;
    int exp = 1;
    
    void build(int root) {
        height.assign(n, 0);
        lift.assign(n, {0});
        rlamb([&](auto&& dfs, int u, int p, int h) -> void {
            height[u] = h, lift[u][0] = p;
            for (auto [v, _] : adj[u]) if (v != p) dfs(v, u, h + 1);
        })(root, -1, 0);
        for (bool go = true; go; exp++) {
            go = false;
            for (int i = 0; i < n; i++) {
                if (lift[i][exp - 1] != -1) lift[i].push_back(lift[lift[i][exp - 1]][exp - 1]);
                else lift[i].push_back(-1);
                if (lift[i].back() != -1) go = true;
            }
        }
    }

    int get_lca(int u, int v) {
        if (height[u] > height[v]) swap(u, v);
        int height_diff = height[v] - height[u];
        return 0;
    }
};
