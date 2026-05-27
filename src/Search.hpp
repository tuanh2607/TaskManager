#ifndef SEARCH_HPP
#define SEARCH_HPP
#include "Task.hpp"
#include "../lib/HashTable.hpp"
#include <string>
using namespace std;
class Search {
private:
    HashTable<long long, TaskById> table;
    HashTable<string, TaskByTitle> titleTable;
public:
    void addTask(TaskById t) {
        TaskByTitle T(t.task);
        table.insert(t.task->id, t);
        titleTable.insert(t.task->title, T);
    }
    void remove(long long id) {
        TaskById* taskToRemove = table.find(id);
        titleTable.remove(taskToRemove->task->title);
        table.remove(id);
    }
    TaskById* findById(long long id) {
        return table.find(id);
    }
    TaskByTitle* findByTitle(string title) {
        return titleTable.find(title);
    }
    void clear() {
        table.clear();
        titleTable.clear();
    }
};
#endif