#include "LinkedList.hpp"
template<typename T>
struct Queue {
    LinkedList<T> queue;
    int size() {
        return queue.size();
    }
    bool empty() {
        return queue.size() == 0;
    }
    void enqueue(T val) {
        queue.insertBack(val);
    }
    void dequeue() {
        if(queue.empty()) return;
        queue.removeAt(0);
    }
    T front() {
        return queue.head ? queue.head->data : T{};
    }
};
