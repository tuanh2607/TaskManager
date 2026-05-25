#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include "Task.hpp"
#include "../lib/PriorityQueue.hpp"
#include "../lib/Queue.hpp"
class Scheduler {
private:
    PriorityQueue<TaskByPriority> pq;
public:
    void addUrgent(TaskByPriority &t) {
        pq.insert(t);
    };
    TaskByPriority* getNext() {
        if(!pq.empty()) return pq.peek();
        else return nullptr;
    };
    void deleteTask(TaskByPriority &t) {
        pq.deleteValue(t);
    };
    bool empty() {
        return pq.empty();
    };
    int size() {
        return pq.size();
    };
};
#endif