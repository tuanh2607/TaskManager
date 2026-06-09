#ifndef UI_HPP
#define UI_HPP
#include <iostream>
#include "TaskManager.hpp"
#include "functions.hpp"
using namespace std;
using namespace sys;
using namespace tks;
class UI {
private:
    void choice1 (TaskManager &tm) {
        string priority, title, date;

        while(true) {
            cout << "[?] Enter priority level (1 - 3) : ";
            getline(cin, priority);
            if(priority.empty() || !isAllDigits(priority) || !validPriority(stoi(priority))) cout << "[!] Input is not valid\n";
            else break;
        }
        int prio = stoi(priority);

        while(true) {
            cout << "[?] Enter title : ";
            getline(cin, title);
            if(title.length() < 1 || title.length() > 25) cout << "[!] Title must be between 1 and 25 characters\n";
            else break;
        }

        while(true) {
            cout << "[?] Enter deadline in format (HH-MM-DD-MM-YYYY) : ";
            getline(cin, date);
            if(checkDay(date)) break;
            else cout << "[!] Invalid date format\n";
        }
        long long id = getID(date);

        printTask(Task(id, prio, title, date));
        cout << "[?] Add task [y/n] : ";
        string confirm;
        getline(cin, confirm);

        if(confirm == "y" || confirm == "Y") {
            tm.addTask(id, prio, title, date, true);
            cout << "[!] Task added successfully\n";
        }
        pause();
    }
    void choice2(TaskManager &tm) {
        Task* task = tm.getNextTask();
        if(task) printTask(*task);
        else cout << "[!] No tasks available\n";
        pause();
    }
    void choice3(TaskManager &tm) {
        long long id;
        cout << "[?] Complete task by [1] Deadline or [2] Title : ";
        string searchChoice;
        getline(cin, searchChoice);

        if(searchChoice == "1") {
            cout << "[?] Enter deadline of task to complete in format (HH-MM-DD-MM-YYYY) : ";
            string date;
            getline(cin, date);
            if(!checkDay(date)) {
                cout << "[!] Invalid date\n";
                pause();
                return;
            }
            id = getID(date);

        } else if(searchChoice == "2") {
            cout << "[?] Enter name of task to complete : ";
            string title;
            getline(cin, title);
            Task* task = tm.searchByTitle(title);

            if(task) id = task->id;
            else {
                cout << "[!] Task not found\n";
                pause();
                return;
            }
        } else {
            cout << "[!] Invalid choice\n";
            pause();
            return;
        }
        tm.completeTask(id, true);
        cout << "[!] Task marked as DONE\n";
        pause();
    }
    void choice4(TaskManager &tm) {
        long long id;
        cout << "[?] Delete by [1] Deadline or [2] Title : ";
        string searchChoice;
        getline(cin, searchChoice);

        if(searchChoice == "1") {
            cout << "[?] Enter deadline of task to delete in format (HH-MM-DD-MM-YYYY) : ";
            string d;
            getline(cin, d);
            if(!checkDay(d)) {
                cout << "[!] Invalid date\n";
                pause();
                return;
            }
            id = getID(d);

        } else if(searchChoice == "2") {
            cout << "[?] Enter name of task to delete : ";
            string title;
            getline(cin, title);
            Task* task = tm.searchByTitle(title);
            if(task) id = task->id;
            else {
                cout << "[!] Task not found\n";
                pause();
                return;
            }

        } else {
            cout << "[!] Invalid choice\n";
            pause();
            return;
        }
        tm.deleteTask(id, true);
        cout << "[!] Task deleted successfully\n";
        pause();
    }
    void choice5(TaskManager &tm) {
        cout << "[?] Search by [1] Deadline or [2] Title : ";
        string searchChoice;
        getline(cin, searchChoice);

        if(searchChoice == "1") {
            cout << "[?] Enter deadline of task to search in format (HH-MM-DD-MM-YYYY) : ";
            string date;
            getline(cin, date);
            if(!checkDay(date)) {
                cout << "[!] Invalid date format\n";
                pause();
                return;
            }
            long long id = getID(date);
            Task* task = tm.searchById(id);
            if(task) printTask(*task);
            else cout << "[!] Task not found\n";
        
        } else if(searchChoice == "2") {
            cout << "[?] Enter title of task to search : ";
            string title;
            getline(cin, title);
            Task* task = tm.searchByTitle(title);
            if(task) printTask(*task);
            else cout << "[!] Task not found\n";

        } else cout << "[!] Invalid choice\n";
        pause();
    }
    void choice8(TaskManager &tm) {
        cout << "[?] Edit by [1] Deadline or [2] Title : ";
        string searchChoice;
        Task* taskToEdit = nullptr;
        getline(cin, searchChoice);

        if(searchChoice == "1") {
            cout << "[?] Enter deadline of task to edit in format (HH-MM-DD-MM-YYYY) : ";
            string date;
            getline(cin, date);
            if(!checkDay(date)) {
                cout << "[!] Invalid date format\n";
                pause();
                return;
            }
            long long id = getID(date);
            taskToEdit = tm.searchById(id);
            if(!taskToEdit) {
                cout << "[!] Task not found\n";
                pause();
                return;
            }

        }else if(searchChoice == "2") {
            cout << "[?] Enter title of task to edit : ";
            string title;
            getline(cin, title);
            taskToEdit = tm.searchByTitle(title);
            if(!taskToEdit) {
                cout << "[!] Task not found\n";
                pause();
                return;
            }

        } else {
            cout << "[!] Invalid choice\n";
            pause();
            return;
        }

        string newTitle, newDeadline, newPriority;
        while(true) {
            cout << "[?] Enter new priority level (1 - 3) : ";
            getline(cin, newPriority);
            if(newPriority.empty() || !isAllDigits(newPriority) || !validPriority(stoi(newPriority))) cout << "[!] Input is not valid\n";
            else break;
        }           
        int newPrio = stoi(newPriority);

        while(true) {
            cout << "[?] Enter new title : ";
            getline(cin, newTitle);
            if(newTitle.length() < 1 || newTitle.length() > 25) cout << "[!] Title must be between 1 and 25 characters\n";
            else break;
        }

        while(true) {
            cout << "[?] Enter new deadline in format (HH-MM-DD-MM-YYYY) : ";
            getline(cin, newDeadline);
            if(checkDay(newDeadline)) break;
            else cout << "[!] Invalid date format\n";
        }
        long long id = getID(newDeadline);
        clearScreen();

        printTask(*taskToEdit);
        cout << "                                           ⬇⬇⬇" << endl;
        printTask(Task(id, newPrio, newTitle, newDeadline));
        cout << "[?] Edit task [y/n] : ";
        string confirm;
        getline(cin, confirm);
        if(confirm == "y" || confirm == "Y") {
            tm.editTask(taskToEdit, id, newPrio, newTitle, newDeadline, true);
            cout << "[!] Task edited successfully\n";

        } else cout << "[!] Edit cancelled\n";

        pause();
    }
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
        cout << "║ [8] Edit task                  ║\n";
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
                choice1(tm);
            } else if(choice == "2") { 
                choice2(tm);
            } else if(choice == "3") {
                choice3(tm);
            } else if(choice == "4") {
                choice4(tm);
            } else if(choice == "5") {
                choice5(tm);
            } else if(choice == "6") {
                tm.undo();
                pause();
            } else if(choice == "7") {
                tm.listAll();
            } else if(choice == "8") {
                choice8(tm);
            } else break;
        }
    };
};
#endif