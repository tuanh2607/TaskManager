#ifndef SEARCH_HPP
#define SEARCH_HPP
#include "Task.hpp"
#include "../lib/HashTable.hpp"
#include <string>
using namespace std;
class Search {
private:
    HashTable<long long, Task> table;
public:
    void addTask(Task t) {
        table.insert(t.id, t);
    }
    // Xóa task khỏi AVL và HashTable theo id
    void remove(int id) {

    };
    // Tra cứu O(1) theo id qua HashTable
    Task* findById(long long id) {
        return table.find(id);
    };

    // Tìm task theo title, duyệt qua AVL
    Task* findByTitle(const string& title);

    // Xóa toàn bộ index, dùng khi reset hoặc load lại từ file
    void clear();
};
#endif