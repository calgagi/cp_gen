template <class T> 
class avl {
public:
    struct node {
        T val;
        node* left = NULL, * right = NULL;
        int height = 1, ref = 1, treeRef = 1;
        node(T v) : val(v) {};
    };

    node* root = NULL;

    int get_height(node* cur) {
        return (!cur ? 0 : 1 + max((cur->left ? cur->left->height : 0), (cur->right ? cur->right->height : 0)));
    }

    int get_balance(node* cur) {
        return (!cur ? 0 : get_height(cur->left) - get_height(cur->right));
    }

    void refresh(node* cur) {
        cur->height = get_height(cur), cur->treeRef = cur->ref + (cur->left ? cur->left->treeRef : 0) + (cur->right ? cur->right->treeRef : 0);
    }

    node* right_rotate(node* cur) {
        node* newRoot = cur->left, * temp = newRoot->right;
        newRoot->right = cur, cur->left = temp;
        refresh(cur), refresh(newRoot);
        return newRoot;
    }

    node* left_rotate(node* cur) {
        node* newRoot = cur->right, * temp = newRoot->left;
        newRoot->left = cur, cur->right = temp;
        refresh(cur), refresh(newRoot);
        return newRoot;
    }

    node* insert(node* cur, T val) {
        if (!cur) return new node(val);
        if (val == cur->val) cur->ref++;
        else if (val < cur->val) cur->left = insert(cur->left, val);
        else cur->right = insert(cur->right, val);
        refresh(cur);
        if (get_balance(cur) >= 2 && val < cur->left->val) cur = right_rotate(cur);
        else if (get_balance(cur) <= -2 && val > cur->right->val) cur = left_rotate(cur);
        else if (get_balance(cur) >= 2 && val > cur->left->val) {
            cur->left = left_rotate(cur->left);
            cur = right_rotate(cur);
        }
        else if (get_balance(cur) <= -2 && val < cur->right->val) {
            cur->right = right_rotate(cur->right);
            cur = left_rotate(cur);
        }
        return cur;
    }


    node* remove(node* cur, T val) {
        if (!cur) return NULL;
        if (val == cur->val) {
            cur->ref--;
            if (cur->ref == 0) {
                if (!cur->left && !cur->right) {
                    delete cur;
                    return NULL;
                }
                else if (!cur->left || !cur->right) {
                    node* temp = (cur->left ? cur->left : cur->right);
                    delete cur;
                    cur = temp;
                } 
                else {
                    node* temp = cur->right;
                    while (temp->left)
                        temp = temp->left;
                    cur->val = temp->val;
                    cur->ref = temp->ref;
                    temp->ref = 1;
                    cur->right = remove(cur->right, temp->val);
                }
            }
        }
        else if (val < cur->val) cur->left = remove(cur->left, val);
        else cur->right = remove(cur->right, val);
        refresh(cur);
        if (get_balance(cur) >= 2 && get_balance(cur->left) >= 0) cur = right_rotate(cur);
        else if (get_balance(cur) <= -2 && get_balance(cur->right) <= 0) cur = left_rotate(cur);
        else if (get_balance(cur) >= 2 && get_balance(cur->left) < 0) {
            cur->left = left_rotate(cur->left);
            cur = right_rotate(cur);
        }
        else if (get_balance(cur) <= -2 && get_balance(cur->right) > 0) {
            cur->right = right_rotate(cur->right);
            cur = left_rotate(cur);
        }
        return cur;
    }

    int size_before(node* cur, T val) {
        if (!cur) return 0;
        if (val == cur->val) return (cur->left ? cur->left->treeRef : 0);
        else if (cur->val < val) return cur->ref + (cur->left ? cur->left->treeRef : 0) + size_before(cur->right, val);
        return size_before(cur->left, val);
    }

    int count(node* cur, T val) {
        return (!cur ? 0 : (cur->val == val ? cur->ref : (val < cur->val ? count(cur->left, val) : count(cur->right, val))));
    }

    T at(node* cur, int index) {
        if (!cur) return T();
        int before = (cur->left ? cur->left->treeRef : 0);
        if (index <= before) return at(cur->left, index);
        else if (index <= before + cur->ref) return cur->val;
        return at(cur->right, index - (before + cur->ref));
    }

    int count(T val) {
        return count(root, val);
    }

    int size() {
        return (!root ? 0 : root->treeRef); 
    }

    void insert(T val) {
        root = insert(root, val);
    }     

    void remove(T val) {
        root = remove(root, val);    
    }

    int size_before(T val) {
        return size_before(root, val);
    }

    T at(int index) {
        return at(root, index+1);
    }

    T* closest_lt(T val) {
        int before = size_before(val);
        return (before - 1 < 0 ? NULL : new T(at(before - 1)));
    }

    T* closest_gt(T val) {
        int before = size_before(val), cnt = count(val);
        return (before + cnt < size() ? new T(at(before + cnt)) : NULL);
    }
};
