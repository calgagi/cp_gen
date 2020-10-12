#include "../lib/pbavl.hpp"

class pbavlTester {
private:
    static bool instantiate() {
        pbavl<int> item;
        pbavl<float> item2;
        pbavl<int64_t> item3;
        pbavl<string> item4;
        return true;
    }

    static bool count() {
        pbavl<int> item;
        srand(time(NULL));
        for (int i = 0; i < 100; i++) {
            item.insert(i);
            if (item.count(i) != 1) {
                return false;
            }
        }
        for (int i = 99; i >= 0; i--) {
            item.insert(i);
            if (item.count(i) != 2) {
                return false;
            }
        }
        for (int i = 0; i < 1000; i++) {
            int j = (rand() % (INT_MAX - 1000)) + 1000;
            if (item.count(j) != 0) {
                return false;
            }
        }
        return true;
    }

    static bool count2() {
        pbavl<int> item;
        srand(time(NULL));
        map<int,int> vals;
        for (int i = 0; i < 100000; i++) {
            int j = rand() % INT_MAX;
            vals[j]++;
            item.insert(j);
            if (item.count(j) != vals[j]) {
                return false;
            }
        }
        return true;
    }

    static bool balance() {
        pbavl<int> item;
        if (item.height() != 0) {
            return false;
        }
        item.insert(0);
        if (item.height() != 1) {
            return false;
        }
        for (int i = 0; i < 3; i++) {
            item.insert(i);
        }
        return item.height() == 2;
    }

    static bool balance2() {
        pbavl<int> item;
        for (int i = 0; i < 100; i++) {
            item.insert(i);
        }
        if (item.height() > ceil(log(100)/log(2))) {
            return false;
        }
        for (int i = 100; i < 100000; i++) {
            item.insert(i);
        }
        return item.height() <= ceil(log(100000)/log(2));
    }

public:
    static void runTests() {
        map<string, function<bool()>> tests = {
            {"instantiate", instantiate},
            {"count", count},
            {"count2", count2},
            {"balance", balance},
            {"balance2", balance2}
        };
        cout << "====== pbval ======" << endl;
        for (const auto& test : tests) {
            cout << test.first << ": " << (tests[test.first]() ? PASS : FAIL) << endl;
        }
        return;
    }
};