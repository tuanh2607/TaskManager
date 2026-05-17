template<typename T>
class BST {
private:
    struct Node{
        T data;
        Node* l;
        Node* r;
        Node(T val) : data(val), l(nullptr), r(nullptr) {}
    };
    Node* root;
public:
    BST() : root(nullptr) {}
    void insert(T val) {
        Node* tmp = new Node(val);
        if(!root) {
            root = tmp;
            return;
        }
        Node *p = root;
        while(true) {
            if(p->data < val) {
                if(!p->r) {
                    p->r = tmp;
                    return;
                }
                p = p->r;
            } else if(p->data > val) {
                if(!p->l) {
                    p->l = tmp;
                    return;
                }
                p = p->l;
            }
        }
    }
    static Node* remove(Node* node, T val) {
        if(!node) return nullptr;
        if(node->data > val) {
            node->l = remove(node->l, val);
        } else if(node->data < val) {
            node->r = remove(node->r, val);
        } else {
            if(!node->l && !node->r) {
                delete node;
                return nullptr;
            }
            if(!node->l) {
                Node* tmp = node->r;
                delete node;
                return tmp;
            }
            if(!node->r) {
                Node* tmp = node->l;
                delete node;
                return tmp;
            }
            Node* tmp = node->r;
            while(tmp->l) tmp = tmp->l;
            node->data = tmp->data;
            node->r = remove(node->r, tmp->data);
        }
        return node;
    }
    void remove(T val) {
        root = remove(root, val);
        return;
    }
    bool search(T val) {
        if(!root) return false;
        Node* tmp = root;
        while(tmp) {
            if(tmp->data == val) return true;
            else if(tmp->data > val) tmp = tmp->l;
            else tmp = tmp->r;
        }
        return false; 
    }
    static void NLR(Node* node) {
        if(!node) return;
        cout << node->data << " ";
        NLR(node->l);
        NLR(node->r);
    } 
    void NLR() {
        NLR(root);
    }
    static void LNR(Node* node) {
        if(!node) return;
        LNR(node->l);
        cout << node->data << " ";
        LNR(node->r);
    }
    void LNR() {
        LNR(root);
    }
    static void LRN(Node* node) {
        if(!node) return;
        LRN(node->l);
        LRN(node->r);
        cout << node->data << " ";
    }
    void LRN() {
        LRN(root);
    }
};
// xong