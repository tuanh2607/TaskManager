#ifndef UI_HPP
#define UI_HPP
#include <iostream>
#include "TaskManager.hpp"
#include "functions.hpp"
using namespace std;
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
    // Vòng lặp chính: showMenu → getChoice → switch/case gọi các handle
    void runLoop(TaskManager &tm) {
        string choice;
        while(true) {
            showMenu();
            getline(cin, choice);
            cout << endl;
            clearScreen();
            if(choice == "1") {
                int p; string t; string s; string d;
                while(true) {
                    cout << "[?] Nhập mức độ ưu tiên (1 - 3) : ";
                    cin >> p;
                    cin.ignore();
                    if(!validPriority(p)) cout << "[!] Nhập khác với yêu cầu\n";
                    else break;
                }
                cout << "[?] Nhập tiêu đề : ";
                getline(cin, t);
                cout << "[?] Nhập deadline theo dạng (HH-MM-DD-MM-YYYY) : ";
                getline(cin, d); 
                string line = repeatStr("═", 103);
                long long id = extractDate(d);
                cout << line << endl;
                cout << left << setw(15) << "ID" << setw(15) << "Priority" << setw(42) << "Title" << setw(15) << "Status" << setw(15) << "deadline" << endl;
                cout << line << endl;
                cout << left << setw(15) << id << setw(15) << p << setw(42) << t << setw(15) << "TODO" << setw(15) << d << endl;
                cout << "[!] Thêm task [y/n] : ";
                char choice;
                cin >> choice;
                if(tolower(choice) == 'y') {
                    tm.addTask(id, p, t, d);
                    cout << "[!] Thêm thành công\n";
                    continue;
                } else continue;
            } else if(choice == "2") {

            } else if(choice == "3") {

            } else if(choice == "4") {
                
            } else if(choice == "5") {

            } else if(choice == "6") {

            } else if(choice == "7") {
                tm.listAll();
            } else break;
        }
    };
};
#endif