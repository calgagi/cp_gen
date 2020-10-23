#include "../lib/segtree.hpp"

class segtreeTester {
private:
    static bool instantiate() {
        function<int (int,int)> f = [](int a, int b) -> int {
            return a + b;
        };
        segtree<int> item(10, 9, f);

        function<float (float, float)> f2 = [](float a, float b) -> float {
            return a - b;
        };
        segtree<float> item2(10, 0.9, f2);

        segtree<string> item3(10, "", [](string a, string b) -> string {
            return a + b;
        });
        return true;
    }

    static bool add() {
        segtree<int> item(100, 0, [](int a, int b) -> int {
            return a + b;
        });
        for (int i = 0; i < 100; i++) {
            item.update(i, 1);
            if (item.query(0, i) != i+1) {
                return false;
            }
        }
        return true;
    }

    static bool add2() {
        segtree<int> item(1000, 0, [&](int a, int b) -> int)
    }

public:
    static bool runTests() {
        cout << "============ segtree ============" << endl;
        map<string, function<bool()>> tests = {
            {"instantiate", instantiate},
            {"add", add}
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