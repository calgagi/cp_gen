template<class T>
class segtree {
private:
    std::vector<T> tree;
    std::function<T (T, T)> combine;
    T identity; // mathematical identity element for the object T under the binary operation combine
    int n;

    void updateHelper(int v, int tl, int tr, int pos, const T& val) {
        if (tl == tr)
            tree[v] = val;
        else {
            int tm = tl + (tr - tl) / 2;
            if (pos <= tm)
                updateHelper(2*v, tl, tm, pos, val);
            else
                updateHelper(2*v+1, tm+1, tr, pos, val);
            tree[v] = combine(tree[2*v], tree[2*v+1]);
        }
        return;
    }

    T queryHelper(int v, int tl, int tr, int left, int right) {
        if (left > right)
            return identity;
        if (tl == left && tr == right)
            return tree[v];
        int tm = tl + (tr - tl) / 2;
        return combine(
                queryHelper(2*v, tl, tm, left, std::min(tm, right)),
                queryHelper(2*v+1, tm+1, tr, std::max(tm+1, left), right)
        );
    }

public:
    segtree(int pn, T i, std::function<T (T, T)> c) : n(pn), combine(c), identity(i) {
        tree.assign(4*pn, i);
    }

    void update(int pos, T val) {
        assert(pos < n);
        assert(pos >= 0);
        updateHelper(1, 0, n-1, pos, val);
        return;
    }

    T query(int left, int right) {
        assert(left >= 0);
        assert(left <= right);
        assert(right < n);
        return queryHelper(1, 0, n-1, left, right);
    }
};
