#ifndef HISTORY_HPP
#define HISTORY_HPP
#include "Task.hpp"
#include "../lib/Stack.hpp"
#include <string>
using namespace std;
struct Operation {
    string type;
    Task task; 
    Operation(string t, Task ts) : type(t) , task(ts) {}
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