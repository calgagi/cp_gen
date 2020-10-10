template <class T> 
class pbset {
private:
    struct Node {
        T val;
        Node* left = NULL, * right = NULL;
        int leftHeight = 0, rightHeight = 0;
        Node(T v) : val(v) {};
        Node() {};
    };

    // Note: this is a AVL tree
    Node* root = NULL;

    Node* insertHelper(Node* cur, T val) {
        if (!cur) {
            return new Node(val);
        } 
        if (val < cur->val) {
            cur->left = insertHelper(cur->left, val);
        } else {
            cur->right = insertHelper(cur->right, val);
        }
        cur->leftHeight = (cur->left ? 1 + max(cur->left->leftHeight, cur->left->rightHeight) : 0);
        cur->rightHeight = (cur->right ? 1 + max(cur->right->leftHeight, cur->right->rightHeight) : 0);
        if (abs(cur->leftHeight - cur->rightHeight) == 2) {
            if (
            
        return cur;
    }

    Node* removeAll(Node* cur, T val) {
        if (!cur) {
            return NULL;
        }
        if (val < cur->val) {
            cur->left = removeHelper(cur->left, val);
        } else {
            cur->right = removeHelper(cur->right, val);
        }
        if (val == cur->val) {
            
        }
        return cur;
    }
             

public:
    void insert(T val) {
        root = insertHelper(root, val);
        return;
    }     

    void removeAll(T val) {
        root = removeHelper(root, val);    
        return;
    }
};
