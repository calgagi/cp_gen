#include "../lib/graph.hpp"
#include "../lib/rlamb.hpp"
#include "../lib/lca.hpp"
class lcaTester {
private:
    static bool undirectedbuild() {
        /*    
         *  -- 0 --
         * /   |   \
         * 1   2    3
         * | \  \
         * 4  5  6
         */
        vector<vector<int>> adj = {
            { 1, 2, 3 },
            { 0, 4, 5 },
            { 0, 6 },
            { 0 },
            { 1 },
            { 1 },
            { 2 }
        };
        int n = adj.size();
        lca tree(n);
        for (int i = 0; i < n; i++) {
            for (int& v : adj[i]) {
                tree.add_edge(i, v);
            }
        }
        tree.build(0);
        cpassert(tree.height[0] == 0);
        cpassert(tree.height[1] == 1);
        cpassert(tree.height[3] == 1);
        cpassert(tree.height[5] == 2);
        cpassert(tree.height[6] == 2);
        cpassert(tree.lift[0][0] == -1);
        for (int i = 1; i < 7; i++) {
            cpassert(tree.lift[i][0] == adj[i][0]);
            cpassert(tree.lift[i][2] == -1);
            if (i < 4) {
                cpassert(tree.lift[i][1] == -1);
            }
        }
        cpassert(tree.lift[4][1] == 0 && tree.lift[5][1] == 0 && tree.lift[6][1] == 0);
        return true;
    }

    static bool directedbuild() {
        /*    
         *  -- 0 --
         * /   |   \
         * 1   2    3
         * | \  \
         * 4  5  6
         */
        vector<vector<int>> adj = {
            { 1, 2, 3 },
            { 4, 5 },
            { 6 },
            { },
            { },
            { },
            { }
        };
        int n = adj.size();
        lca tree(n);
        for (int i = 0; i < n; i++) {
            for (int& v : adj[i]) {
                tree.add_edge(i, v);
            }
        }
        tree.build(0);
        cpassert(tree.height[0] == 0);
        cpassert(tree.height[1] == 1);
        cpassert(tree.height[3] == 1);
        cpassert(tree.height[5] == 2);
        cpassert(tree.height[6] == 2);
        cpassert(tree.lift[0][0] == -1);
        for (int i = 1; i < 7; i++) {
            cpassert(tree.lift[i][2] == -1);
            if (i < 4) {
                cpassert(tree.lift[i][1] == -1);
            }
        }
        cpassert(tree.lift[4][1] == 0 && tree.lift[5][1] == 0 && tree.lift[6][1] == 0);
        return true;
    }

public:
    static bool runTests() {
        cout << "============ lca ============" << endl;
        map<string, function<bool()>> tests = {
            {"undirectedbuild", undirectedbuild},
            {"directedbuild", directedbuild}
        };
        bool ans = true;
        for (const auto& test : tests) {
            bool result = tests[test.first]();
            cout << test.first << ": " << (result ? PASS : FAIL) << endl;
            if (!result) {
                ans = false;
            }
        }
        return ans;
    }
};
