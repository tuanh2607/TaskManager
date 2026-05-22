#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include "AVL.hpp"
#include <vector>
#include <string>
#include <sstream>
using namespace std;
template<typename A, typename B>
struct Pair {
    A key;
    B val;
    Pair() {}
    Pair(A k, B v) : key(k), val(v) {}
    bool operator < (const Pair &other) const {
        return key < other.key;
    }
    bool operator > (const Pair &other) const {
        return key > other.key;
    }
    bool operator == (const Pair &other) const {
        return key == other.key;
    }
};
template<typename A, typename B>
class HashTable {
private:
    const int base = 31;
    const long long mod = 1e9 + 7;
    const int bucket_size = 37;
    int _size;
    vector<AVL<Pair<A, B>>> bucket;
    long long hashFunc(A key) {
        stringstream ss;
        ss << key;
        string s = ss.str();
        long long hash_val = 0;
        long long pow = 1;
        for(char c:s) {
            hash_val = (hash_val + (c - ' ' + 1) * pow) % mod;
            pow = (pow * base) % mod; 
        }
        return hash_val % bucket_size;
    }
public:
    HashTable() : bucket(bucket_size), _size(0) {}
    void insert(A key, B value) {
        if(!contains(key)) {
            Pair<A,B> key_val = {key, value};
            bucket[hashFunc(key)].insert(key_val);
            _size++;
        }
    }
    void remove(A key) {
        Pair<A, B> dummy = {key, B{}};
        if (bucket[hashFunc(key)].search(dummy)){
            bucket[hashFunc(key)].remove(dummy);
            _size--;
        } else return;
    }
    B* find(A key) {
        int idx = hashFunc(key);
        Pair<A, B> dummy = {key, B{}};
        Pair<A, B>* res =  bucket[idx].searchForHashMap(dummy);
        if(res) return &res->val;
        return nullptr;
    }
    bool contains(A key) {
        Pair<A, B> dummy = {key, B{}};
        return bucket[hashFunc(key)].search(dummy);
    }
    int size() {
        return _size;
    }
    void clear(){
        for(int i = 0; i < bucket_size; i++) {
            bucket[i].deleteALL();
        }
        _size = 0;
    }
};
#endif