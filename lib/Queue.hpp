#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "LinkedList.hpp"
template<typename T>
class Queue {
private:
    LinkedList<T> queue;
public:
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
    T* front() {
        return queue.getHead() ? &queue.getHead()->data : nullptr;
    }
};
#endif
