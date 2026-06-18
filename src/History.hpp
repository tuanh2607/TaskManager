#ifndef HISTORY_HPP
#define HISTORY_HPP
#include "Task.hpp"
#include "../lib/Stack.hpp"
#include "functions.hpp"
#include <vector>
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
    void record(const Operation& op) {
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
    void printHistory() {
        vector<Operation> ops = s.toVector();
        string line = dpt::repeatStr("═", 105);
        cout << "╔" << line << "╗" << endl;
        cout << "║ " << left << setw(15) << "Operation" << setw(15) << "Priority" << setw(42) << "Title" << setw(15) << "Status" << setw(15) << "Deadline" << "  ║" << endl;
        cout << "╠" << line << "╣" << endl;
        for (int i = 0; i < ops.size(); i++) {
            Operation op = ops[i];
            if(op.type == "ADD") {
                cout << "║ " << left << setw(15) << op.type << setw(15) << op.oldTask.priority << setw(42) << op.oldTask.title << setw(15) << op.oldTask.status << setw(15) << tks::convertDate(op.oldTask.deadline) << " ║" << endl;
            } else if(op.type == "DELETE") {
                cout << "║ " << left << setw(15) << op.type << setw(15) << op.oldTask.priority << setw(42) << op.oldTask.title << setw(15) << op.oldTask.status << setw(15) << tks::convertDate(op.oldTask.deadline) << " ║" << endl;
            } else if(op.type == "COMPLETE") {
                cout << "║ " << left << setw(104) << op.type << "║" << endl;
                cout << "║ " << left << setw(15) << "   ~From:" << setw(15) << op.oldTask.priority << setw(42) << op.oldTask.title << setw(15) << op.oldTask.status << setw(15) << tks::convertDate(op.oldTask.deadline) << " ║" << endl;
                cout << "║ " << left << setw(15) << "   ~To:" << setw(15) << op.oldTask.priority << setw(42) << op.oldTask.title << setw(15) << "DONE" << setw(15) << tks::convertDate(op.oldTask.deadline) << " ║" << endl;
            } else if(op.type == "EDIT") {
                cout << "║ " << left << setw(104) << op.type << "║" << endl;
                cout << "║ " << left << setw(15) << "   ~From:" << setw(15) << op.oldTask.priority << setw(42) << op.oldTask.title << setw(15) << op.oldTask.status << setw(15) << tks::convertDate(op.oldTask.deadline) << " ║" << endl;
                cout << "║ " << left << setw(15) << "   ~To:" << setw(15) << op.newTask.priority << setw(42) << op.newTask.title << setw(15) << op.newTask.status << setw(15) << tks::convertDate(op.newTask.deadline) << " ║" << endl;
            }
        }
        cout << "╚" << line << "╝" << endl;
    }
};
#endif