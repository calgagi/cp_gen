#include "../lib/segtree.hpp"

class segtreeTester {
private:
    static bool instantiate() {
        function<int (int,int)> f = [](int a, int b) -> int {
            return a + b;
        };
        segtree<int> item(10, f);

        function<float (float, float)> f2 = [](float a, float b) -> float {
            return a - b;
        };
        segtree<float> item2(10, f2);

        segtree<string> item3(10, [](string a, string b) -> string {
            return a + b;
        });
        return true;
    }


public:
    static bool runTests() {
        cout << "============ segtree ============" << endl;
        map<string, function<bool()>> tests = {
            {"instantiate", instantiate}
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