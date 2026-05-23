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
    // Xóa task khỏi AVL và HashTable theo id
    void remove(long long id) {
        table.remove(id);
    };
    // Tra cứu O(1) theo id qua HashTable
    TaskById* findById(long long id) {
        return table.find(id);
    };
    // Xóa toàn bộ index, dùng khi reset hoặc load lại từ file
    void clear() {
        table.clear();
    };
};
#endif