template<class T>
class segtree {
public:
    T identity; // mathematical identity element for the object T under the binary operation combine
    std::function<T (T, T)> combine;
    int64_t n;

    struct node {
        T val;
        node* left = NULL, * right = NULL;
    };

    node* root = NULL;

    node* update(node* cur, int tl, int tr, int pos, const T& val) {
        if (!cur) {
            cur = new node;
        }
        if (tl == tr) {
            cur->val = val;
        }
        else {
            int tm = tl + (tr - tl) / 2;
            if (pos <= tm) {
                cur->left = update(cur->left, tl, tm, pos, val);
            }
            else {
                cur->right = update(cur->right, tm+1, tr, pos, val);
            }
            cur->val = combine((cur->right ? cur->right->val : identity), (cur->left ? cur->left->val : identity));
        }
        return cur;
    }

    T query(node* cur, int tl, int tr, int left, int right) {
        if (!cur || left > right) {
            return identity;
        }
        if (tl == left && tr == right) {
            return cur->val;
        }
        int tm = tl + (tr - tl) / 2;
        return combine(query(cur->left, tl, tm, left, std::min(tm, right)),
                       query(cur->right, tm+1, tr, std::max(tm+1, left), right));
    }

    segtree(int64_t p, T i, std::function<T (T, T)> c) : n(p), combine(c), identity(i) {}

    void update(int pos, T val) {
        root = update(root, 0, n-1, pos, val);
        return;
    }

    T query(int left, int right) {
        return query(root, 0, n-1, left, right);
    }
};
