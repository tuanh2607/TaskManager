#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include "Task.hpp"
#include "../lib/PriorityQueue.hpp"
#include "../lib/Queue.hpp"
class Scheduler {
private:
    PriorityQueue<TaskIdPriority> pq;
public:
    void addTask(TaskIdPriority &t) {
        pq.insert(t);
    };
    TaskIdPriority* getNext() {
        if(!pq.empty()) return pq.peek();
        else return nullptr;
    };
    void deleteTask(TaskIdPriority &t) {
        pq.deleteValue(t);
    };
    bool empty() {
        return pq.empty();
    };
};
#endif