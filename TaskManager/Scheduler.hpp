#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include "Task.hpp"
#include "../lib/PriorityQueue.hpp"
#include "../lib/Queue.hpp"
class Scheduler {
private:
    PriorityQueue<Task> pq;
    Queue<Task> q;
public:
    // Thêm task vào PriorityQueue — dùng cho task HIGH/MED priority
    void addUrgent(Task &t) {
        pq.insert(t);
    };
    // Thêm task vào Queue FIFO — dùng cho task LOW priority
    void addNormal(Task &t) {
        q.enqueue(t);
    };

    // Lấy task tiếp theo: ưu tiên lấy từ PriorityQueue trước, Queue sau
    Task* getNext() {
        if(!pq.empty()) return pq.peek();
        else return q.front();
    };
    // Kiểm tra cả hai queue đều rỗng chưa
    bool empty() {
        return pq.empty() && q.empty();
    };
    // Tổng số task đang chờ trong cả hai queue
    int size() {
        return pq.size() + q.size();
    };
};
#endif