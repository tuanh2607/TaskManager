#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP
#include "Algorithms.hpp"
#include <vector>
using namespace std;
template<typename T>
class PriorityQueue {
private:
    vector<T> heap;
public:
    void insert(T val) {
        heap.push_back(val);
        int i = heap.size() - 1;
        while(i > 0 && heap[(i - 1)/2] < heap[i]) {
            Swap(heap[i], heap[(i - 1)/2]);
            i = (i - 1)/2;
        }
    }
    void extract(){
        if(heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        heapify(heap, heap.size(), 0);
    }
    T* peek() {
        return heap.empty() ? nullptr : &heap[0];
    }
    bool empty() {
        return heap.size() == 0;
    }
    int size() {
        return heap.size();
    }
};
#endif