template <class T> 
class pbavl {
private:
    struct Node {
        T val;
        Node* left = nullptr, * right = nullptr;
        int height = 1;
        int treeSize = 1;
        int ref = 1;
        Node(T v) : val(v) {};
        Node() {};
    };

    // Note: this is an AVL tree
    Node* root = nullptr;
    int num_refs = 0; 

    int getHeight(Node* cur) {
        if (!cur) {
            return 0;
        }
        return 1 + max(
            (cur->left ? cur->left->height : 0),
            (cur->right ? cur->right->height : 0)
        );
    }

    int getTreeSize(Node* cur) {
        if (!cur) {
            return 0;
        }
        return 1 + (cur->left ? cur->left->treeSize : 0) + (cur->right ? cur->right->treeSize : 0);
    }

    Node* rightRotate(Node* cur) {
        assert(cur != nullptr);
        assert(cur->left != nullptr);
        Node* newRoot = cur->left;
        cur->left = newRoot->right;
        newRoot->right = cur;
        cur->height = getHeight(cur);
        cur->treeSize = getTreeSize(cur);
        newRoot->height = getHeight(newRoot);
        newRoot->treeSize = getTreeSize(newRoot);
        return newRoot;
    }

    Node* leftRotate(Node* cur) {
        assert(cur != nullptr);
        assert(cur->right != nullptr);
        Node* newRoot = cur->right;
        cur->right = newRoot->left;
        newRoot->left = cur;
        cur->height = getHeight(cur);
        cur->treeSize = getTreeSize(cur);
        newRoot->height = getHeight(newRoot);
        newRoot->treeSize = getTreeSize(newRoot);
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
        if (getHeight(cur->left) - getHeight(cur->right) >= 2 && val < cur->left->val) {
            cur = rightRotate(cur);
        } 
        else if (getHeight(cur->left) - getHeight(cur->right) <= -2 && val > cur->right->val) {
            cur = leftRotate(cur);
        }
        else if (getHeight(cur->left) - getHeight(cur->right) >= 2 && val > cur->left->val) {
            cur->left = leftRotate(cur->left);
            cur = rightRotate(cur);
        }
        else if (getHieght(cur->left) - getHeight(cur->right) <= -2 && val < cur->right->val) {
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
            num_refs--;
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
        if (getHeight(cur->left) - getHeight(cur->right) >= 2 && val < cur->left->val) {
            cur = rightRotate(cur);
        } 
        else if (getHeight(cur->left) - getHeight(cur->right) <= -2 && val > cur->right->val) {
            cur = leftRotate(cur);
        }
        else if (getHeight(cur->left) - getHeight(cur->right) >= 2 && val > cur->left->val) {
            cur->left = leftRotate(cur->left);
            cur = rightRotate(cur);
        }
        else if (getHieght(cur->left) - getHeight(cur->right) <= -2 && val < cur->right->val) {
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
        return false;
    }
             
public:
    int size() {
        return num_refs;
    }

    void insert(T val) {
        num_refs++;
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
