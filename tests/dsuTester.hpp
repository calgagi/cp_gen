class dsuTester {
private:
    static bool instantiate() {
        dsu DSU(10);
        return true;
    }

    static bool nounite() {
        dsu item(1000);
        for (int i = 0; i < 1000; i++) {
            if (item.find(i) != i) {
                return false;
            }
        }
        return item.components() == 1000;
    }

    static bool uniteeach() {
        dsu item(100000);
        for (int i = 1; i < 100000; i++) {
            item.unite(0, i);
            if (item.components() != 100000-i) {
                return false;
            }
        }
        return true;
    }

    static bool uniterand() {
        dsu item(100000);
        int c = 100000;
        for (int i = 0; i < 100000; i++) {
            int a = rand() % 100000, b = rand() % 100000;
            if (item.find(a) != item.find(b)) {
                c--;
                item.unite(a, b);
            }
            if (c != item.components() || item.find(a) != item.find(b)) {
                return false;
            }
        }
        return true;
    }

    static bool stress() {
        clock_t start = clock();
        dsu item(300000);
        for (int i = 0; i < 300000; i++) {
            int a = rand() % 300000, b = rand() % 300000;
            item.unite(a, b);
            a = item.find(a), b = item.find(b);
        }
        return (clock() - start) / (double) CLOCKS_PER_SEC <= 1.0;
    }

public:
    static bool runTests() {
        cout << "============ dsu ============" << endl;
        map<string, function<bool()>> tests = {
            {"instantiate", instantiate},
            {"nounite", nounite},
            {"uniteeach", uniteeach},
            {"uniterand", uniterand},
            {"stress", stress}
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
