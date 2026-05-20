#ifndef TASK_HPP
#define TASK_HPP
#include <string>
using namespace std;

struct Task {
    long long id;
    int priority;
    string title;
    string status;
    string deadline;

    // So sánh theo priority để PriorityQueue hoạt động đúng
    bool operator < (const Task& other) const {
        return priority < other.priority;
    };
    bool operator > (const Task &other) const {
        return priority > other.priority;
    };
    // So sánh theo id để AVL và HashTable tìm đúng node
    bool operator == (const Task& other) const {
        return id == other.id;
    };
};
#endif