class numTester {
public:
    static bool testcrt() {
        vector<long long> n = {5, 6, 7};
        vector<long long> a = {3, 2, 4};
        cpassert(crt(n, a) == 158);
        n = {7,13,59,31,19};
        a = {0,12,55,25,12};
        cpassert(crt(n,a) == 1068781);
        n = {17,41,523,13,19,23,787,37,29};
        a = {0,34,-17,-35,-36,-40,-48,-54,-77};
        cpassert(crt(n,a) == 825305207525452LL);
        return true;
    }

    static bool norm() {
        cpassert(normalize(-10, 1) == 0);
        cpassert(normalize(-10) == 999999997);
        cpassert(normalize(-31) == 999999976);
        cpassert(normalize((long long) -(1e9 + 7)) == 0);
        cpassert(normalize(10, 7) == 3);
        cpassert(normalize(7, 10) == 7);
        return true;
    }

    static bool testgcd() {
        cpassert(gcd(1, 1) == 1);    
        cpassert(gcd(10, 2) == 2);
        cpassert(gcd(7, 31) == 1);
        cpassert(gcd(36, 24) == 12);
        cpassert(gcd(-7, -7) == 7);
        cpassert(gcd(-6, 3) == 3);
        cpassert(gcd(3, -6) == 3);
        cpassert(gcd(-3, 6) == 3);
        return true;
    }

    static bool testmodpow() {
        cpassert(modpow(0, 0) == 1);
        cpassert(modpow(0, 1) == 0);
        cpassert(modpow(10, 0) == 1);
        cpassert(modpow(10, 2) == 100);
        cpassert(modpow(1000, 100000) == 849079858);
        cpassert(modpow(31, 162413613, 101) == 58);
        cpassert(modpow(31, 162413613) == 5637460);
        return true;
    }

    static bool runTests() {
        cout << "============ num ============" << endl;
        map<string, function<bool()>> tests = {
            {"testcrt", testcrt},
            {"norm", norm},
            {"testgcd", testgcd},
            {"testmodpow", testmodpow}
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
