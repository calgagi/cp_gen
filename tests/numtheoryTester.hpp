class numtheoryTester {
private:

public:
    static bool runTests() {
        cout << "============ numtheory ============" << endl;
        map<string, function<bool()>> tests = {
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
