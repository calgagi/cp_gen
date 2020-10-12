#include "../lib/dsu.hpp"

class dsuTester {
private:
    static bool instantiate() {
        dsu DSU(10);
        return true;
    }

public:
    static void runTests() {
        map<string, function<bool()>> tests = {
            {"instantiate", instantiate}
        };
        cout << "====== dsu ======" << endl;
        for (const auto& test : tests) {
            cout << test.first << ": " << (tests[test.first]() ? PASS : FAIL) << endl;
        }
        return;
    }
};