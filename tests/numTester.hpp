class numTester {
private:
    static bool testcrt() {
        vector<ll> n = {5, 6, 7};
        vector<ll> a = {3, 2, 4};
        cpassert(crt(n, a) == 158);
        n = {7,13,59,31,19};
        a = {0,12,55,25,12};
        cpassert(crt(n,a) == 1068781);
        n = {17,41,523,13,19,23,787,37,29};
        a = {0,34,-17,-35,-36,-40,-48,-54,-77};
        cpassert(crt(n,a) == 825305207525452LL);
        return true;
    }

public:
    static bool runTests() {
        cout << "============ num ============" << endl;
        map<string, function<bool()>> tests = {
            {"testcrt", testcrt}
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
