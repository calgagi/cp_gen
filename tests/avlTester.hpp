#include "../lib/avl.hpp"
class avlTester {
private:
    static bool count() {
        avl<int> item;
        srand(time(NULL));
        for (int i = 0; i < 100; i++) {
            item.insert(i);
            cpassert(item.count(i) == 1);
        }
        for (int i = 99; i >= 0; i--) {
            item.insert(i);
            cpassert(item.count(i) == 2);
        }
        for (int i = 0; i < 1000; i++) {
            int j = (rand() % (INT_MAX - 1000)) + 1000;
            cpassert(item.count(j) == 0);
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
            cpassert(item.count(j) == vals[j]);
        }
        return true;
    }

    static bool instantiate() {
        avl<int> item;
        avl<float> item2;
        avl<int64_t> item3;
        avl<string> item4;
        return true;
    }

    static bool balance() {
        avl<int> item;
        cpassert(abs(item.get_balance(item.root)) <= 1);
        item.insert(0);
        cpassert(abs(item.get_balance(item.root)) <= 1);
        for (int i = 0; i < 3; i++) {
            item.insert(i);
        }
        cpassert(abs(item.get_balance(item.root)) <= 1);
        return true;
    }

    static bool balance2() {
        avl<int> item;
        for (int i = 0; i < 100; i++) {
            item.insert(i);
        }
        cpassert(abs(item.get_balance(item.root)) <= 1);
        for (int i = 100; i < 100000; i++) {
            item.insert(i);
        }
        cpassert(abs(item.get_balance(item.root)) <= 1);
        return true;
    }

    static bool remove() {
        avl<int> item;
        for (int i = 0; i < 2000; i++) {
            item.insert(i);
        }
        cpassert(item.size() == 2000);
        for (int i = 0; i < 2000; i++) {
            item.insert(i);
        }
        cpassert(item.size() == 4000);
        for (int i = 0; i < 2000; i++) {
            item.remove(i);
            item.remove(i);
            cpassert(item.size() == 4000 - 2 * (i + 1));
        }
        cpassert(item.size() == 0);
        return true;
    }

    static bool remove2() {
        avl<int> item;
        for (int i = 0; i < 100000; i++) {
            item.insert(i);
        }
        for (int i = 0; i < 100000; i++) {
            item.remove(i);
            cpassert(item.size() == 100000-i-1); 
            cpassert(abs(item.get_balance(item.root)) <= 1);
        }
        return true;
    }

    static bool singleval() {
        avl<int> item;
        for (int i = 0; i < 10000; i++) {
            item.insert(0);
        }
        cpassert(abs(item.get_balance(item.root)) <= 1);
        cpassert(item.size() == 10000);
        for (int i = 0; i < 9999; i++) {
            item.remove(0);
        }
        cpassert(abs(item.get_balance(item.root)) <= 1);
        cpassert(item.size() == 1);
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
        srand(time(NULL));
        avl<int> item;
        for (int i = 0; i < 10000; i++) {
            item.insert(i);
        }
        for (int i = 0; i < 10000; i++) {
            cpassert(item.size_before(i) == i);
        }
        for (int i = 0; i < 10000; i++) {
            int x = rand() % 10000;
            cpassert(item.size_before(x) == x);
        }
        return true;
    }

    static bool closestgt() {
        avl<int> item;
        srand(time(NULL));
        for (int i = 0; i < 100000; i++) {
            item.insert(i);
            cpassert(item.closest_gt(i) == NULL);
        }
        for (int i = 0; i < 100000-1; i++) {
            cpassert(*item.closest_gt(i) == i+1);
        }
        for (int i = 0; i < 100000; i++) {
            int x = rand() % 99999;
            cpassert(*item.closest_gt(x) == x+1);
        }
        return true;
    }

    static bool closestlt() {
        avl<int> item;
        srand(time(NULL));    
        set<int> s;
        for (int i = 0; i < 100; i++) {
            int x = rand() % 1000;
            item.insert(x);
            s.insert(-x);
        }
        for (int i = 0; i < 100000; i++) {
            int x = (rand() % 1000);
            if (s.upper_bound(-x) != s.end()) {
                cpassert(*item.closest_lt(x) != x);
                cpassert(*item.closest_lt(x) == -(*s.upper_bound(-x)));
            }
        }
        return true;
    }

    static bool at() {
        avl<int> tree;
        vector<int> a;
        srand(time(NULL));
        for (int i = 0; i < 1000000; i++) {
            int x = rand() % INT_MAX;
            a.push_back(x);
            tree.insert(x);
        } 
        sort(a.begin(), a.end());
        for (int i = 0; i < 1000000; i++) {
            cpassert(tree.at(i) == a[i]);
        }
        return true;
    }

public:
    static bool runTests() {
        cout << "============ avl ============" << endl;
        map<string, function<bool()>> tests = {
            {"instantiate", instantiate},
            {"balance", balance},
            {"balance2", balance2},
            {"remove", remove},
            {"remove2", remove2},
            {"singleval", singleval},
            {"stress", stress},
            {"stress2", stress2},
            {"before", before},
            {"closestgt", closestgt},
            {"closestlt", closestlt},
            {"at", at},
            {"count", count},
            {"count2", count2}
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
