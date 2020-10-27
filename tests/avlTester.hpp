#include "../lib/avl.hpp"

class avlTester {
private:
    static bool instantiate() {
        avl<int> item;
        avl<float> item2;
        avl<int64_t> item3;
        avl<string> item4;
        return true;
    }

    static bool count() {
        avl<int> item;
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
        avl<int> item;
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
        avl<int> item;
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
        avl<int> item;
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

    static bool remove() {
        avl<int> item;
        for (int i = 0; i < 2000; i++) {
            item.insert(i);
        }
        if (item.size() != 2000) {
            return false;
        }
        for (int i = 0; i < 2000; i++) {
            item.insert(i);
        }
        if (item.size() != 4000) {
            return false;
        }
        for (int i = 0; i < 2000; i++) {
            item.remove(i);
            item.remove(i);
            if (item.size() != 4000 - 2 * (i + 1)) {
                return false;
            }
        }
        if (item.size() != 0) {
            return false;
        }
        return true;
    }

    static bool remove2() {
        avl<int> item;
        for (int i = 0; i < 100000; i++) {
            item.insert(i);
        }
        for (int i = 0; i < 100000; i++) {
            item.remove(i);
            if (item.size() != 100000-i-1 || item.height() > 2 * max(1.0, ceil(log(100000 - i - 1) / log(2)))) {
                return false;
            }
        }
        return true;
    }

    static bool singleval() {
        avl<int> item;
        for (int i = 0; i < 10000; i++) {
            item.insert(0);
        }
        if (item.size() != 10000 && item.height() != 1) {
            return false;
        }
        for (int i = 0; i < 9999; i++) {
            item.remove(0);
        }
        if (item.size() != 1 && item.height() != 1) {
            return false;
        }
        return true;
    }

    static bool stress() {
        clock_t start = clock();
        avl<int> item;
        for (int i = 0; i < 500000; i++) {
            item.insert(i);
        }
        for (int i = 0; i < 500000; i++) {
            item.remove(i);
        }
        return (clock() - start) / (double) CLOCKS_PER_SEC <= 1.0;
    }

    static bool stress2() {
        clock_t start = clock();
        avl<int> item;
        map<int,int> inserted;
        for (int i = 0; i < 100000; i++) {
            int j = rand(); 
            inserted[j]++;
            item.insert(j);
        }
        for (auto it = inserted.begin(); it != inserted.end(); ++it) {
            while (it->second > 0) {
                item.remove(it->first);
                it->second--;
            }
        }
        return (clock() - start) / (double) CLOCKS_PER_SEC <= 1.0;
    }

    static bool before() {
        avl<int> item;
        for (int i = 0; i < 10000; i++) {
            item.insert(i);
        }
        for (int i = 0; i < 10000; i++) {
            if (item.before(i) != i) {
                return false;
            }
        }
        return true;
    }

public:
    static bool runTests() {
        cout << "============ avl ============" << endl;
        map<string, function<bool()>> tests = {
            {"instantiate", instantiate},
            {"count", count},
            {"count2", count2},
            {"balance", balance},
            {"balance2", balance2},
            {"remove", remove},
            {"remove2", remove2},
            {"singleval", singleval},
            {"stress", stress},
            {"stress2", stress2},
            {"before", before}
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
