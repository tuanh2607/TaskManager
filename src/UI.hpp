#ifndef UI_HPP
#define UI_HPP
#include <iostream>
#include "TaskManager.hpp"
#include "functions.hpp"
using namespace std;
class UI {
public:
    void showMenu() {
        cout << "╔════════════════════════════════╗\n";
        cout << "║          Task Manager          ║\n";
        cout << "╠════════════════════════════════╣\n";
        cout << "║ [1] Add task                   ║\n";
        cout << "║ [2] See next task              ║\n";
        cout << "║ [3] Complete task              ║\n";
        cout << "║ [4] Delete task                ║\n";
        cout << "║ [5] Search                     ║\n";
        cout << "║ [6] Undo                       ║\n";
        cout << "║ [7] View all tasks             ║\n";
        cout << "║ [8] Save file                  ║\n";
        cout << "║ [0] Exit                       ║\n";
        cout << "╚════════════════════════════════╝\n";
        cout << "[?] Choose an option : ";
    }
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
                    cout << "[?] Enter priority level (1 - 3) : ";
                    cin >> p;
                    cin.ignore();
                    if(!validPriority(p)) cout << "[!] Input is not valid\n";
                    else break;
                }
                cout << "[?] Enter title : ";
                getline(cin, t);
                cout << "[?] Enter deadline in format (HH-MM-DD-MM-YYYY) : ";
                getline(cin, d);
                string line = repeatStr("═", 103);
                long long id = extractDate(d);
                cout << line << endl;
                cout << left << setw(15) << "ID" << setw(15) << "Priority" << setw(42) << "Title" << setw(15) << "Status" << setw(15) << "Deadline" << endl;
                cout << line << endl;
                cout << left << setw(15) << id << setw(15) << p << setw(42) << t << setw(15) << "TODO" << setw(15) << convertDate(d) << endl;
                cout << line << endl;
                cout << "[?] Add task [y/n] : ";
                char choice;
                cin >> choice;
                cin.ignore();
                if(choice == 'y' || choice == 'Y') {
                    tm.addTask(id, p, t, d, true);
                    cout << "[!] Task added successfully\n";
                }
                pauseScreen();
                clearScreen();
            } else if(choice == "2") {
                if(tm.getNextTask()) {
                    Task t = *tm.getNextTask();
                    string line = repeatStr("═", 103);
                    cout << line << endl;
                    cout << left << setw(15) << "ID" << setw(15) << "Priority" << setw(42) << "Title" << setw(15) << "Status" << setw(15) << "deadline" << endl;
                    cout << line << endl;
                    cout << left << setw(15) << t.id << setw(15) << t.priority << setw(42) << t.title << setw(15) << t.status << setw(15) << convertDate(t.deadline) << endl;
                    cout << line << endl;
                } else {
                    cout << "[!] No tasks available\n";
                }
                pauseScreen();
                clearScreen();
            } else if(choice == "3") {
                long long id;
                cout << "[?] Enter task ID to complete : ";
                cin >> id;
                cin.ignore();
                tm.completeTask(id, true);
                cout << "[!] Task marked as DONE\n";
                pauseScreen();
                clearScreen();
            } else if(choice == "4") {
                cout << "[?] Enter deadline of task to delete in format (HH-MM-DD-MM-YYYY) : ";
                string d;
                getline(cin, d);
                long long id = extractDate(d);
                tm.deleteTask(id, true);
                cout << "[!] Task deleted successfully\n";
                pauseScreen();
                clearScreen();
            } else if(choice == "5") {

            } else if(choice == "6") {
                tm.undo();
                pauseScreen();
                clearScreen();
            } else if(choice == "7") {
                tm.listAll();
            } else if(choice == "8") {
                tm.save();
                cout << "[!] Saved successfully\n";
                pauseScreen();
                clearScreen();
            } else break;
        }
    };
};
#endif