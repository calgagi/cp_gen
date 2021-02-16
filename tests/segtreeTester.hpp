class segtreeTester {
private:
    static bool instantiate() {
        std::function<int (int,int)> f = [](int a, int b) -> int {
            return a + b;
        };
        segtree<int> item(10, 9, f);

        std::function<float (float, float)> f2 = [](float a, float b) -> float {
            return a - b;
        };
        segtree<float> item2(10, 0.9, f2);

        segtree<std::string> item3(10, "", [](std::string a, std::string b) -> std::string {
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
            cpassert(item.query(0, i) == i+1);
            cpassert(item.query(i, i) == 1);
            cpassert(item.query(i, 99) == 1);
        }
        return true;
    }

    static bool stress() {
        clock_t start = clock();
        segtree<int> item(100, 0, [&](int a, int b) -> int {
            return a + b;
        });
        std::vector<int> cnt(100, 0);
        for (int i = 0; i < 100000; i++) {
            int a = rand() % 100;
            cnt[a]++;
            item.update(a, cnt[a]);
            cpassert(item.query(a, a) == cnt[a]);
        }
        return (clock() - start) / (double) CLOCKS_PER_SEC <= 1.0;
    }

    static bool maxtree() {
        srand(time(NULL));
        segtree<float> item(10000, 0.0, [&](float a, float b) -> float {
            return std::max(a, b);
        });
        float mx = 0;
        for (int i = 0; i < 10000; i++) {
            float x = rand();
            mx = std::max(x, mx);
            item.update(i, x);
            cpassert(item.query(0, 9999) == mx);
        }
        return true;
    }

    static bool maxtree2() {
        srand(time(NULL));
        segtree<int64_t> item(100, 0, [&](int64_t a, int64_t b) -> int64_t {
            return std::max(a, b);
        });
        std::vector<int64_t> arr(100, 0);
        for (int i = 0; i < 10000; i++) {
            int64_t x = rand(), p = rand() % 100;
            arr[p] = x;
            item.update(p, x);
            int l = rand() % 50, r = (rand() % 50) + 50;
            int64_t ans = 0;
            for (int j = l; j <= r; j++) {
                ans = std::max(ans, arr[j]);
            }
            cpassert(item.query(l, r) == ans);
        }
        return true;
    }

    static bool customobj() {
        srand(time(NULL));
        struct X {
            int a = 0;
        };
        segtree<X> item(100, X(), [](X a, X b) -> X {
            return (a.a < b.a ? b : a);
        });
        std::vector<X> arr(100);
        for (int i = 0; i < 10000; i++) {
            int x = rand(), p = rand() % 100;
            arr[p].a = x;
            item.update(p, arr[p]);
            int l = rand() % 50, r = (rand() % 50) + 50;
            int ans = 0;
            for (int j = l; j <= r; j++) {
                ans = std::max(ans, arr[j].a);
            }
            cpassert(item.query(l, r).a == ans);
        }
        return true;
    }

    static bool maxandfreq() {
        srand(time(NULL));
        segtree<std::pair<int,int>> item(100, std::make_pair(0, 0), [](std::pair<int,int> a, std::pair<int,int> b) -> std::pair<int,int> {
            if (a.first == b.first) {
                return std::make_pair(a.first, b.second + a.second);
            }
            return (a.first < b.first ? b : a);
        });
        std::vector<std::pair<int,int>> cnt(100, std::make_pair(0, 0));
        for (int i = 0; i < 10000; i++) {
            int p = rand() % 100, a = rand() % 100;
            if (cnt[p].first == a) {
                cnt[p].second++;
            }
            else if (cnt[p].first < a) {
                cnt[p] = {a, 1};
            }
            item.update(p, cnt[p]);
            int l = rand() % 50, r = (rand() % 50) + 50;
            std::pair<int,int> ans = {0, 0};
            for (int j = l; j <= r; j++) {
                if (ans.first < cnt[j].first) {
                    ans = cnt[j];
                }
                else if (ans.first == cnt[j].first) {
                    ans.second += cnt[j].second;
                }
            }
            cpassert(ans == item.query(l, r));
        }
        return true;
    }

    static bool stress2() {
        srand(time(NULL));
        clock_t start = clock();
        segtree<std::pair<int,int>> item(1000000, std::make_pair(0, 0), [](std::pair<int,int> a, std::pair<int,int> b) -> std::pair<int,int> {
            if (a.first == b.first) {
                return std::make_pair(a.first, b.second + a.second);
            }
            return (a.first < b.first ? b : a);
        });
        for (int i = 0; i < 1000000; i++) {
            int p = rand() % 100, a = rand() % 100;
            item.update(p, std::make_pair(a, rand() % 10));
            item.query(rand() % 500000, (rand() % 500000) + 500000);
        }
        return (clock() - start) / (double) CLOCKS_PER_SEC <= 1.0;
    }

public:
    static bool runTests() {
        std::cout << "============ segtree ============" << std::endl;
        std::map<std::string, std::function<bool()>> tests = {
            {"instantiate", instantiate},
            {"add", add},
            {"stress", stress},
            {"maxtree", maxtree},
            {"maxtree2", maxtree2},
            {"customobj", customobj},
            {"maxandfreq", maxandfreq},
            {"stress2", stress2}
        };
        bool ans = true;
        for (const auto& test : tests) {
            bool result = tests[test.first]();
            std::cout << test.first << ": " << (result ? PASS : FAIL) << std::endl;
            if (!result) {
                ans = false;
            }
        }
        return ans;
    }
};
