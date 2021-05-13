class rlambTester {
public:
    static bool factorial() {
        auto fact = rlamb([&](auto&& recurse, int x) -> ll {
            if (x == 1) {
                return 1;
            }
            return x * recurse(x - 1);
        });
        ll cur = 1;
        for (ll i = 1; i < 10; i++) {
            cur *= i;
            cpassert(cur == fact((int) i));
        }
        return true;
    }

    static bool fibonacci() {
        vector<ll> dp(10000);
        auto fib = rlamb([&](auto&& re, int x) -> ll {
                if (dp[x] != 0) {
                    return dp[x];
                }
                if (x <= 2) {
                    return x;
                }
                dp[x] = re(x - 1) + re(x - 2);
                return dp[x];
        });
        vector<ll> cur(10000);
        cur[1] = 1, cur[2] = 2;
        for (int i = 3; i < 10000; i++) {
            cur[i] = cur[i-1] + cur[i-2];
            cpassert(cur[i] == fib(i));
        }
        return true;
    }

    static bool runTests() {
        cout << "============ rlamb ============" << endl;
        map<string, function<bool()>> tests = {
            {"factorial", factorial},
            {"fibonacci", fibonacci}
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
