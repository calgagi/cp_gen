template<class T>
class segtree {
private:
    vector<T> tree;
    function<T (T, T)> combine;
    T identity; // mathematical identity element for the object T under the binary operation combine
    int n;

    void updateHelper(int v, int tl, int tr, int pos, const T& val) {
        if (tl == tr) {
            tree[v] = val;
        } 
        else {
            int tm = tl + (tr - tl) / 2;
            if (pos <= tm) {
                updateHelper(2*v, tl, tm, pos, val);
            }
            else {
                updateHelper(2*v+1, tm+1, tr, pos, val);
            }
            tree[v] = combine(tree[2*v], tree[2*v]+1);
        }
        return;
    }

    T queryHelper(int v, int tl, int tr, int left, int right) {
        if (tr < tl) {
            return identity;
        }
        if (tl == left && tr == right) {
            return tree[v];
        }
        int tm = tl + (tr - tl) / 2;
        return combine(
                queryHelper(2*v, tl, tm, left, min(tm, right)),
                queryHelper(2*v+1, tm+1, tr, max(tm+1, left), right)
        );
    }

public:
    segtree(int pn, function<T (T, T)> c) : n(pn), combine(c) {
        tree.assign(4*n, identity);
    }

    void update(int pos, T val) {
        updateHelper(1, 0, n-1, pos, val);
        return;
    }

    T query(int left, int right) {
        assert(left >= 0);
        assert(right < n);
        return queryHelper(1, 0, n-1, left, right);
    }
};