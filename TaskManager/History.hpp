#ifndef HISTORY_HPP
#define HISTORY_HPP
#include "Task.hpp"
#include "../lib/Stack.hpp"
#include <string>
using namespace std;
struct Operation {
    string type;  // "ADD", "DELETE", "COMPLETE"
    Task task;  // snapshot của task tại thời điểm thao tác
    Operation(string t, Task ts) : type(t) , task(ts) {}
};

class History {
private: 
    Stack<Operation> s;
public:
    // Đẩy operation vừa thực hiện lên Stack để có thể undo sau
    void record(Operation op) {
        s.push(op);
    };

    // Lấy operation trên cùng Stack ra để TaskManager thực hiện ngược lại
    Operation* undo() {
        return s.top();
    };

    // Kiểm tra Stack còn operation để undo không
    bool canUndo() {
        return s.empty();
    };
};
#endif