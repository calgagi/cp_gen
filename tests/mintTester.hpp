#include "../lib/mint.hpp"

class NullStream : public ostream {
public:
    NullStream() : ostream(nullptr) {}
    NullStream(const NullStream &) : ostream(nullptr) {}
};

template <class T>
const NullStream &operator<<(NullStream &&os, const T &value) { 
    return os;
}

class mintTester {
private:
static bool instantiate() {
        mint a = 1000;
        int x = 10;
        a = x;
        mint b = x;
        long c = x;
        mint d;
        ll e = a;
        return true;
    }

    static bool add() {
        mint a = 100 + 1000;
        mint b = a + 10;
        mint c = 10 + a;
        mint d = b + c;
        if (a != 1100 || b != 1110 || c != 1110 || d != 2220) {
            return false;
        }
        a = 10;
        if (a != 10) {
            return false;
        }
        a = b + d;
        if (a != 3330) {
            return false;
        }
        return true;
    }

    static bool add2() {
        mint a = 10;
        a += 1000;
        if (a != 1010) {
            return false;
        }
        mint b = -a;
        if (b != 999998997) {
            return false;
        }
        b += 1010;
        if (b != 0) {
            return false;
        }
        b += a;
        if (b != a) {
            return false;
        }
        return true;
    }

    static bool subtract() {
        mint a = -10;
        a -= 1000;
        if (a != 999998997) {
            return false;
        }
        mint b = -a;
        if (b != 1010) {
            return false;
        }
        b -= 1010;
        if (b != 0) {
            return false;
        }
        b -= a;
        if (b != -a) {
            return false;
        }
        return true;
    }

    static bool stdsort() {
        srand(time(NULL));
        vector<mint> A(10000);
        for (mint& x : A) {
            x = rand();
        }
        sort(A.begin(), A.end());
        for (int i = 1; i < 10000; i++) {
            if (A[i] < A[i-1]) {
                return false;
            }
            if (A[i-1] > A[i]) {
                return false;
            }
            ll a = A[i];
            if (a < A[i-1]) {
                return false;
            }
            if (A[i-1] > a) {
                return false;
            }
        }
        sort(A.begin(), A.end(), greater<mint>());
        for (int i = 1; i < 10000; i++) {
            if (A[i] > A[i-1]) {
                return false;
            }
            if (A[i-1] < A[i]) {
                return false;
            }
            ll a = A[i];
            if (a > A[i-1]) {
                return false;
            }
            if (A[i-1] < a) {
                return false;
            }
        }
        return true;
    }

    static bool stream() {
        mint test = 10;
        auto null = NullStream();
        null << test << endl;
        return true;
    }

public:
    static bool runTests() {
        cout << "============ mint ============" << endl;
        map<string, function<bool()>> tests = {
            {"instantiate", instantiate},
            {"add", add},
            {"add2", add2},
            {"subtract", subtract},
            {"stdsort", stdsort},
            {"stream", stream}
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