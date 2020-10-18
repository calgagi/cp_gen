#include "../lib/dsu.hpp"

class dsuTester {
private:
    static bool instantiate() {
        dsu DSU(10);
        return true;
    }

public:
    static bool runTests() {
        map<string, function<bool()>> tests = {
            {"instantiate", instantiate}
        };
        cout << "====== dsu ======" << endl;
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