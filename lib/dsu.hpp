class dsu {
private:
    std::vector<int> link;
    std::vector<int> size;
    int num_components;

public:
    dsu(int N) {
        num_components = N;
        size.assign(N, 1);
        link.assign(N, 0);
        for (int i = 0; i < N; i++)
            link[i] = i;
        return;
    }

    int find(int a) {
        assert (a >= 0 && a < link.size());
        while (a != link[a])
            a = link[a];
        return a;
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (size[a] > size[b])
            std::swap(a, b);
        link[a] = b;
        size[b] += size[a];
        num_components--;
        return true;
    }

    int components() {
        return num_components;
    }
};
