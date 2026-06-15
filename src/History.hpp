#ifndef HISTORY_HPP
#define HISTORY_HPP
#include "Task.hpp"
#include "../lib/Stack.hpp"
#include <string>
using namespace std;
struct Operation {
    string type;
    Task oldTask; 
    Task newTask;
    Operation(string t, Task ot) : type(t), oldTask(ot) {}
    Operation(string t, Task ot, Task nt) : type(t), oldTask(ot), newTask(nt) {}
};

class History {
private: 
    Stack<Operation> s;
public:
    void record(Operation op) {
        s.push(op);
    };
    Operation* lastOperation() {
        return s.top();
    };
    bool canUndo() {
        return !s.empty();
    };
    void pop() {
        s.pop();
    };
};
#endif