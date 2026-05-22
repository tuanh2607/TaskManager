#ifndef AVL_HPP
#define AVL_HPP
#include "Algorithms.hpp"
using namespace std;
template<typename T>
class AVL {
private:
    struct Node {
        T data;
        int h;
        Node *l;
        Node *r;
        Node(T val) : data(val), l(nullptr), r(nullptr), h(1) {}
    };
    Node* root;
    int height (Node* root) {
        return root ? root->h : 0;
    }
    void UpdateHeight (Node* root) {
        root->h = 1 + Max(height(root->l), height(root->r));
    }
    Node* RotateLeft(Node* root) {
        Node* rChild = root->r;
        root->r = rChild->l;
        rChild->l = root;
        UpdateHeight(root);
        UpdateHeight(rChild);
        return rChild;
    }
    Node* RotateRight(Node* root) {
        Node* lChild = root->l;
        root->l = lChild->r;
        lChild->r = root;
        UpdateHeight(root);
        UpdateHeight(lChild);
        return lChild;
    }
    Node* RotateLeftRight(Node* root) {
        root->l = RotateLeft(root->l);
        return RotateRight(root);
    }
    Node* RotateRightLeft(Node* root) {
        root->r = RotateRight(root->r);
        return RotateLeft(root);
    }
    Node* insert(Node* root, T val) {
        if(!root) return new Node(val);
        if(root->data < val) root->r = insert(root->r, val);
        else if(root->data > val) root->l = insert(root->l, val);
        else return root;
        UpdateHeight(root); 
        Node* node_l = root->l;
        Node* node_r = root->r;
        int bf = height(node_l) - height(node_r);
        if(bf == 2) {
            if(height(node_l->l) >= height(node_l->r)) {
                root = RotateRight(root);
            } else
                root = RotateLeftRight(root);
        } else if(bf == -2) {
            if (height(node_r->l) <= height(node_r->r)){
                root = RotateLeft(root);
            } else root = RotateRightLeft(root);
        }
        return root;
    }
    Node* remove (Node* root, T val) {
        if(!root) return nullptr;
        if(root->data < val) root->r = remove(root->r, val);
        else if(root->data > val) root->l = remove(root->l, val);
        else {
            if(!root->l && !root->r) {
                delete root;
                return nullptr;
            }
            if(!root->l) {
                Node* tmp = root->r;
                delete root;
                return tmp;
            }
            if(!root->r) {
                Node* tmp = root->l;
                delete root;
                return tmp;
            }
            Node* tmp = root->r;
            while(tmp->l) tmp = tmp->l;
            root->data = tmp->data;
            root->r = remove(root->r, tmp->data);
        }
        UpdateHeight(root);
        Node* node_l = root->l;
        Node* node_r = root->r;
        int bf = height(node_l) - height(node_r);
        if(bf == -2) {
            if(height(node_r->r) >= height(node_r->l)) {
                root = RotateLeft(root);
            } else {
                root = RotateRightLeft(root);
            }  
        } else if(bf == 2) {
            if(height(node_l->l) >= height(node_l->r)) {
                root = RotateRight(root);
            } else root = RotateLeftRight(root);
        }
        return root;
    }
    void NLR(Node* node) {
        if(!node) return;
        cout << node->data << " ";
        NLR(node->l);
        NLR(node->r);
    } 
    void LNR(Node* node) {
        if(!node) return;
        LNR(node->l);
        cout << node->data << " ";
        LNR(node->r);
    }
    void LRN(Node* node) {
        if(!node) return;
        LRN(node->l);
        LRN(node->r);
        cout << node->data << " ";
    }
    void deleteALL(Node* root) {
        if(!root) return;
        deleteALL(root->l);
        deleteALL(root->r);
        delete root;
    }
    void toVector(Node* root, vector<T> &a) {
        if(!root) return;
        toVector(root->l, a);
        toVector(root->r, a);
        a.push_back(root->data);
    }
public:
    AVL() : root(nullptr) {}
    ~AVL() {
        deleteALL(root);
    }
    void insert(T val) {
        root = insert(root, val);
        return;
    }
    void remove(T val) {
        root = remove(root, val);
        return;
    }
    void NLR() {
        NLR(root);
    }
    void LNR() {
        LNR(root);
    }
    void LRN() {
        LRN(root);
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
    void deleteALL() {
        deleteALL(root);
        root = nullptr;
    }
    
    T* searchForHashMap(T val) {
        if(!root) return nullptr;
        Node* tmp = root;
        while(tmp) {
            if(tmp->data == val) return &tmp->data;
            else if(tmp->data > val) tmp = tmp->l;
            else tmp = tmp->r;
        }
        return nullptr;
    }
    vector<T> toVector() {
        vector<T> res;
        toVector(root, res);
        return res;
    }
};
#endif