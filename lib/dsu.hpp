class dsu {
public:
    vector<int> link;
    vector<int> size;
    int num_components;

    dsu(int sz) {
        num_components = sz;
        size.assign(n, 1);
        for (int i = 0; i < sz; i++) {
            link[i] = i;
        }
        return;
    }

    int find(int a) {
        while (a != link[a]) {
            a = link[a];
        }
        return a;
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (size[a] > size[b]) {
            swap(a, b);
        }
        link[a] = b;
        size[b] += size[a];
        num_components--;
        return;
    }
};
