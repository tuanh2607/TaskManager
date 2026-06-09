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
    Task() {}
    Task(long long i, int p, string t, string d) : id(i), priority(p), title(t), status("TODO"), deadline(d) {}  
};

struct TaskById {
    Task* task;
    TaskById() : task(nullptr) {}
    TaskById(Task* t) : task(t) {}
    bool operator<(const TaskById &other) const {
        return task->id < other.task->id;
    }
    bool operator>(const TaskById &other) const {
        return task->id > other.task->id;
    }
    bool operator==(const TaskById &other) const {
        return task->id == other.task->id;
    }
};
struct TaskByPriority {
    Task* task;
    TaskByPriority() : task(nullptr) {}
    TaskByPriority(Task* t) : task(t) {}
    bool operator<(const TaskByPriority &other) const {
        return task->priority < other.task->priority;
    }
    bool operator>(const TaskByPriority &other) const {
        return task->priority > other.task->priority;
    }
    bool operator==(const TaskByPriority &other) const {
        return task->priority == other.task->priority;
    }
};
struct TaskByTitle {
    Task* task;
    TaskByTitle() : task(nullptr) {}
    TaskByTitle(Task* t) : task(t) {}
    bool operator<(const TaskByTitle &other) const {
        return task->title < other.task->title;
    }
    bool operator>(const TaskByTitle &other) const {
        return task->title > other.task->title;
    }
    bool operator==(const TaskByTitle &other) const {
        return task->title == other.task->title;
    }
};
struct TaskIdPriority {
    Task* task;
    TaskIdPriority() : task(nullptr) {}
    TaskIdPriority(Task* t) : task(t) {}
    bool operator<(const TaskIdPriority &other) const {
        if(task->priority != other.task->priority) return task->priority < other.task->priority;
        return task->id > other.task->id;
    }
    bool operator>(const TaskIdPriority &other) const {
        if(task->priority != other.task->priority) return task->priority > other.task->priority;
        return task->id < other.task->id;
    }
    bool operator==(const TaskIdPriority &other) const {
        return task->id == other.task->id && task->priority == other.task->priority;
    }
};
#endif