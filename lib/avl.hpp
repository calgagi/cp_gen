template <class T> 
class avl {
public:
    struct Node {
        T val;
        Node* left = NULL, * right = NULL;
        int height = 1, ref = 1, treeRef = 1;
        Node(T v) : val(v) {};
    };

    Node* root = NULL;

    int getHeight(Node* cur) {
        return (!cur ? 0 : 1 + std::max((cur->left ? cur->left->height : 0), (cur->right ? cur->right->height : 0)));
    }

    int getBalance(Node* cur) {
        return (!cur ? 0 : getHeight(cur->left) - getHeight(cur->right));
    }

    void refresh(Node* cur) {
        cur->height = getHeight(cur);
        cur->treeRef = cur->ref + (cur->left ? cur->left->treeRef : 0) + (cur->right ? cur->right->treeRef : 0);
        return;
    }

    Node* rightRotate(Node* cur) {
        Node* newRoot = cur->left;
        Node* temp = newRoot->right;
        newRoot->right = cur;
        cur->left = temp;
        refresh(cur);
        refresh(newRoot);
        return newRoot;
    }

    Node* leftRotate(Node* cur) {
        Node* newRoot = cur->right;
        Node* temp = newRoot->left;
        newRoot->left = cur;
        cur->right = temp;
        refresh(cur);
        refresh(newRoot);
        return newRoot;
    }

    Node* insert(Node* cur, T val) {
        if (!cur) {
            return new Node(val);
        }
        if (val == cur->val) {
            cur->ref++;
        }
        else if (val < cur->val) {
            cur->left = insert(cur->left, val);
        }
        else {
            cur->right = insert(cur->right, val);
        }
        refresh(cur);
        if (getBalance(cur) >= 2 && val < cur->left->val) {
            cur = rightRotate(cur);
        }
        else if (getBalance(cur) <= -2 && val > cur->right->val) {
            cur = leftRotate(cur);
        }
        else if (getBalance(cur) >= 2 && val > cur->left->val) {
            cur->left = leftRotate(cur->left);
            cur = rightRotate(cur);
        }
        else if (getBalance(cur) <= -2 && val < cur->right->val) {
            cur->right = rightRotate(cur->right);
            cur = leftRotate(cur);
        }
        return cur;
    }

    Node* remove(Node* cur, T val) {
        if (!cur) {
            return NULL;
        }
        if (val == cur->val) {
            cur->ref--;
            if (cur->ref == 0) {
                if (!cur->left && !cur->right) {
                    delete cur;
                    return NULL;
                }
                else if (!cur->left || !cur->right) {
                    Node* temp = (cur->left ? cur->left : cur->right);
                    delete cur;
                    cur = temp;
                } 
                else {
                    Node* temp = cur->right;
                    while (temp->left)
                        temp = temp->left;
                    cur->val = temp->val;
                    cur->ref = temp->ref;
                    temp->ref = 1;
                    cur->right = remove(cur->right, temp->val);
                }
            }
        }
        else if (val < cur->val) {
            cur->left = remove(cur->left, val);
        }
        else {
            cur->right = remove(cur->right, val);
        }
        refresh(cur);
        if (getBalance(cur) >= 2 && getBalance(cur->left) >= 0) {
            cur = rightRotate(cur);
        }
        else if (getBalance(cur) <= -2 && getBalance(cur->right) <= 0) {
            cur = leftRotate(cur);
        }
        else if (getBalance(cur) >= 2 && getBalance(cur->left) < 0) {
            cur->left = leftRotate(cur->left);
            cur = rightRotate(cur);
        }
        else if (getBalance(cur) <= -2 && getBalance(cur->right) > 0) {
            cur->right = rightRotate(cur->right);
            cur = leftRotate(cur);
        }
        return cur;
    }


    int size_before(Node* cur, T val) {
        if (!cur) {
            return 0;
        }
        if (val == cur->val) {
            return (cur->left ? cur->left->treeRef : 0);
        }
        else if (cur->val < val) {
            return cur->ref + (cur->left ? cur->left->treeRef : 0) + size_before(cur->right, val);
        }
        return size_before(cur->left, val);
    }

    T* closest_lt(Node* cur, T val) {
        if (!cur) {
            return NULL;
        }
        if (cur->val < val) {
            T* ans = new T(cur->val);
            T* ans2 = closest_lt(cur->right, val);
            if (ans2) {
                delete ans;
                ans = ans2;
            }
            return ans;
        }
        return closest_lt(cur->left, val);
    }
            
    T* closest_gt(Node* cur, T val) {
        if (!cur) {
            return NULL;
        }
        if (val < cur->val) {
            T* ans = new T(cur->val);
            T* ans2 = closest_gt(cur->left, val);
            if (ans2) {
                delete ans;
                ans = ans2;
            }
            return ans;
        }
        return closest_gt(cur->right, val);
    }

    T* at(Node* cur, int index) {
        if (!cur) {
            return NULL;
        }
        int before = (cur->left ? cur->left->treeRef : 0);
        if (index <= before) {
            return at(cur->left, index);
        }
        else if (index <= before + cur->ref) {
            return new T(cur->val);
        }
        return at(cur->right, index - (before + cur->ref));
    }

    T* closest_lt(T val) {
        return closest_lt(root, val);
    }

    T* closest_gt(T val) {
        return closest_gt(root, val);
    }

    int size_before(T val) {
        return size_before(root, val);
    }

    int size() {
        return (!root ? 0 : root->treeRef); 
    }

    void insert(T val) {
        root = insert(root, val);
        return;
    }     

    void remove(T val) {
        root = remove(root, val);    
        return;
    }

    T* at(int index) {
        return ((index >= size() || index < 0) ? NULL : at(root, index+1));
    }
};
