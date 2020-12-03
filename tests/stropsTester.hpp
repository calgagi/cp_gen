class stropsTester {
private:
    static bool until() {
        string x = "hi-my-name-is-calvin";
        for (int c = 0, i = 0; i < (int) x.length(); i++) {
            string word = get_until(x, i, '-');
            switch (c) {
                case 0:
                    if (word != "hi")
                        return false;
                    break;
                case 1:
                    if (word != "my")
                        return false;
                    break;
                case 2:
                    if (word != "name")
                        return false;
                    break;
                case 3:
                    if (word != "is")
                        return false;
                    break;
                case 4:
                    if (word != "calvin")
                        return false;
                    break;
                default:
                    return false;
            }
            c++;
        }
        return true;
    }
    
public:
    static bool runTests() {
        cout << "============ strops ============" << endl;
        map<string, function<bool()>> tests = {
            {"until", until}
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
