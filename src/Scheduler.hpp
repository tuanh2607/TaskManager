#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include "Task.hpp"
#include "../lib/PriorityQueue.hpp"
#include "../lib/Queue.hpp"
class Scheduler {
private:
    PriorityQueue<TaskByPriority> pq;
    Queue<TaskByPriority> q;
public:
    void addUrgent(TaskByPriority &t) {
        pq.insert(t);
    };
    void addNormal(TaskByPriority &t) {
        q.enqueue(t);
    };

    TaskByPriority* getNext() {
        if(!pq.empty()) return pq.peek();
        else return q.front();
    };
    bool empty() {
        return pq.empty() && q.empty();
    };
    int size() {
        return pq.size() + q.size();
    };
};
#endif