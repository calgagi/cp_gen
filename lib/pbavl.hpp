template <class T> 
class pbavl {
private:
    struct Node {
        T val;
        Node* left = nullptr, * right = nullptr;
        int height = 1;
        int treeSize = 1;
        int ref = 1;
        int treeRef = 1;
        Node(T v) : val(v) {};
        Node() {};
    };

    // Note: this is an AVL tree
    Node* root = nullptr;

    int getHeight(Node* cur) {
        if (!cur) {
            return 0;
        }
        return 1 + max(
            (cur->left ? cur->left->height : 0),
            (cur->right ? cur->right->height : 0)
        );
    }

    int getTreeRef(Node* cur) {
        if (!cur) {
            return 0;
        }
        return cur->ref + (cur->left ? cur->left->treeRef : 0) + (cur->right ? cur->right->treeRef : 0);
    }

    int getTreeSize(Node* cur) {
        if (!cur) {
            return 0;
        }
        return 1 + (cur->left ? cur->left->treeSize : 0) + (cur->right ? cur->right->treeSize : 0);
    }

    int getBalance(Node* cur) {
        return (!cur ? 0 : getHeight(cur->left) - getHeight(cur->right));
    }

    Node* rightRotate(Node* cur) {
        assert(cur != nullptr);
        assert(cur->left != nullptr);
        Node* newRoot = cur->left;
        Node* temp = newRoot->right;
        newRoot->right = cur;
        cur->left = temp;
        cur->height = getHeight(cur);
        cur->treeSize = getTreeSize(cur);
        cur->treeRef = getTreeRef(cur);
        newRoot->height = getHeight(newRoot);
        newRoot->treeSize = getTreeSize(newRoot);
        newRoot->treeRef = getTreeRef(newRoot);
        return newRoot;
    }

    Node* leftRotate(Node* cur) {
        assert(cur != nullptr);
        assert(cur->right != nullptr);
        Node* newRoot = cur->right;
        Node* temp = newRoot->left;
        newRoot->left = cur;
        cur->right = temp;
        cur->height = getHeight(cur);
        cur->treeSize = getTreeSize(cur);
        cur->treeRef = getTreeRef(cur);
        newRoot->height = getHeight(newRoot);
        newRoot->treeSize = getTreeSize(newRoot);
        newRoot->treeRef = getTreeRef(newRoot);
        return newRoot;
    }

    Node* insertHelper(Node* cur, T val) {
        if (!cur) {
            return new Node(val);
        } 
        if (val == cur->val) {
            cur->ref++;
        }
        else if (val < cur->val) {
            cur->left = insertHelper(cur->left, val);
        } 
        else {
            cur->right = insertHelper(cur->right, val);
        }
        cur->height = getHeight(cur);
        cur->treeSize = getTreeSize(cur);
        cur->treeRef = getTreeRef(cur);
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

    Node* removeHelper(Node* cur, T val) {
        if (!cur) {
            return nullptr;
        }
        if (val == cur->val) {
            cur->ref--;
            if (cur->ref == 0) {
                if (!cur->left && !cur->right) {
                    delete cur;
                    return nullptr;
                }
                else if (!cur->left || !cur->right) {
                    Node* temp = (cur->left ? cur->left : cur->right);
                    delete cur;
                    cur = temp;
                } 
                else {
                    Node* temp = cur->right;
                    while (temp->left) {
                        temp = temp->left;
                    }
                    cur->val = temp->val;
                    cur->ref = temp->ref;
                    temp->ref = 1;
                    cur->right = removeHelper(cur->right, temp->val);
                }
            }
        }
        else if (val < cur->val) {
            cur->left = removeHelper(cur->left, val);
        } 
        else {
            cur->right = removeHelper(cur->right, val);
        }
        cur->treeSize = getTreeSize(cur);
        cur->height = getHeight(cur);
        cur->treeRef = getTreeRef(cur);
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

    int countHelper(Node* cur, T val) {
        if (!cur) { 
            return 0;
        }
        if (val == cur->val) {
            return cur->ref;
        }
        else if (val < cur->val) {
            return countHelper(cur->left, val);
        }
        else {
            return countHelper(cur->right, val);
        }
        assert(false); // should never make it this far
        return 0;
    }

    int beforeHelper(Node* cur, T val) {
        if (!cur) {
            return 0;
        }
        if (val == cur->val) {
            return (cur->left ? cur->left->treeRef : 0);
        }
        else if (cur->val < val) {
            return cur->ref + (cur->left ? cur->left->treeRef : 0) + beforeHelper(cur->right, val);
        }
        else {
            return beforeHelper(cur->left, val);
        }
        assert(false); // should never make it this far
        return 0;
    }
             
public:
    ~pbavl() {
        stack<Node*> s;
        s.push(root);
        while (!s.empty()) {
            Node* cur = s.top();
            s.pop();
            if (!cur) continue;
            s.push(cur->left), s.push(cur->right);
            delete cur;
        }
        return;
    }

    int before(T val) {
        return beforeHelper(root, val);
    }

    int height() {
        return getHeight(root);
    }

    int size() {
        return getTreeRef(root);
    }

    void insert(T val) {
        root = insertHelper(root, val);
        return;
    }     

    void remove(T val) {
        root = removeHelper(root, val);    
        return;
    }

    int count(T val) {
        return countHelper(root, val);
    }
};
