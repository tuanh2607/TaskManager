#ifndef UI_HPP
#define UI_HPP
#include <iostream>
#include "TaskManager.hpp"
using namespace std;
void clearScreen() {
    system("cls");
}
class UI {
public:
    // In menu ra màn hình
    void showMenu() {
        cout << "╔════════════════════════════════╗\n";
        cout << "║          Task Maneger          ║\n";
        cout << "╠════════════════════════════════╣\n";
        cout << "║ [1] Thêm task                  ║\n";
        cout << "║ [2] Xem task tiếp theo         ║\n";
        cout << "║ [3] Hoàn thành task            ║\n";
        cout << "║ [4] Xóa task                   ║\n";
        cout << "║ [5] Tìm kiếm                   ║\n";
        cout << "║ [6] Undo                       ║\n";
        cout << "║ [7] Xem tất cả                 ║\n";
        cout << "║ [0] Thoat                      ║\n";
        cout << "╚════════════════════════════════╝\n";
        cout << "[?] Chon: ";
    }
    // Đọc số từ cin, validate input
    int getChoice();

    // Hỏi người dùng nhập title, priority, deadline rồi gọi tm.addTask()
    void handleAdd(TaskManager &tm);

    // Hỏi người dùng chọn tìm theo id hay title rồi gọi hàm tương ứng
    void handleSearch(TaskManager &tm);

    // Vòng lặp chính: showMenu → getChoice → switch/case gọi các handle
    void runLoop(TaskManager &tm);
};
#endif