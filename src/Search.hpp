#ifndef SEARCH_HPP
#define SEARCH_HPP
#include "Task.hpp"
#include "../lib/HashTable.hpp"
#include <string>
using namespace std;
class Search {
private:
    HashTable<long long, TaskById> table;
public:
    void addTask(TaskById t) {
        table.insert(t.task->id, t);
    }
    void remove(long long id) {
        table.remove(id);
    }
    TaskById* findById(long long id) {
        return table.find(id);
    }
    void clear() {
        table.clear();
    }
};
#endif