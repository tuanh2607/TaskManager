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
    int inputPriority() {
        string priority;
        while(true) {
            cout << "[?] Enter priority level (1 - 3) : ";
            getline(cin, priority);
            if(priority.empty() || !isAllDigits(priority) || !validPriority(stoi(priority)))
                cout << "[!] Input is not valid\n";
            else return stoi(priority);
        }
    }

    string inputTitle(TaskManager &tm, bool checkDuplicate = false) {
        string title;
        while(true) {
            cout << "[?] Enter title : ";
            getline(cin, title);
            if(title.length() < 1 || title.length() > 25)
                cout << "[!] Title must be between 1 and 25 characters\n";
            else if(checkDuplicate && tm.searchByTitle(title))
                cout << "[!] Task with this title already exists\n";
            else return title;
        }
    }

    string inputDeadline(TaskManager &tm, bool checkDuplicate = false) {
        string date;
        while(true) {
            cout << "[?] Enter deadline in format (HH-MM-DD-MM-YYYY) : ";
            getline(cin, date);
            if(!checkDay(date))
                cout << "[!] Invalid date format\n";
            else if(checkDuplicate && tm.searchById(getID(date)))
                cout << "[!] Task with this deadline already exists\n";
            else return date;
        }
    }

    Task* findTaskByChoice(TaskManager &tm, string prompt) {
        cout << prompt;
        string searchChoice;
        getline(cin, searchChoice);

        if(searchChoice == "1") {
            cout << "[?] Enter deadline in format (HH-MM-DD-MM-YYYY) : ";
            string date;
            getline(cin, date);
            if(!checkDay(date)) { 
                cout << "[!] Invalid date format\n"; 
                return nullptr; 
            }
            Task* t = tm.searchById(getID(date));
            if(!t) cout << "[!] Task not found\n";
            return t;

        } else if(searchChoice == "2") {
            cout << "[?] Enter title : ";
            string title;
            getline(cin, title);
            Task* t = tm.searchByTitle(title);
            if(!t) cout << "[!] Task not found\n";
            return t;

        } else {
            cout << "[!] Invalid choice\n";
            return nullptr;
        }
    }

    void choice1(TaskManager &tm) {
        int prio = inputPriority();
        string title = inputTitle(tm, true);
        string date = inputDeadline(tm, true);
        long long id = getID(date);

        printTask(Task(id, prio, title, date));
        cout << "[?] Add task [y/n] : ";
        string confirm; getline(cin, confirm);
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
        Task* task = findTaskByChoice(tm, "[?] Complete task by [1] Deadline or [2] Title : ");
        if(!task) { 
            pause(); 
            return; 
        }
        tm.completeTask(task->id, true);
        cout << "[!] Task marked as DONE\n";
        pause();
    }

    void choice4(TaskManager &tm) {
        Task* task = findTaskByChoice(tm, "[?] Delete by [1] Deadline or [2] Title : ");
        if(!task) {
            pause();
            return; 
        }
        tm.deleteTask(task->id, true);
        cout << "[!] Task deleted successfully\n";
        pause();
    }

    void choice5(TaskManager &tm) {
        Task* task = findTaskByChoice(tm, "[?] Search by [1] Deadline or [2] Title : ");
        if(task) printTask(*task);
        pause();
    }

    void choice8(TaskManager &tm) {
        Task* taskToEdit = findTaskByChoice(tm, "[?] Edit by [1] Deadline or [2] Title : ");
        if(!taskToEdit) {
            pause();
            return;
        }

        int newPrio = inputPriority();
        string newTitle = inputTitle(tm, false);   
        string newDeadline = inputDeadline(tm, false);
        long long id = getID(newDeadline);
        clearScreen();

        printTask(*taskToEdit);
        cout << "                                           ⬇⬇⬇\n";
        printTask(Task(id, newPrio, newTitle, newDeadline));
        cout << "[?] Edit task [y/n] : ";
        string confirm; getline(cin, confirm);
        if(confirm == "y" || confirm == "Y") {
            tm.editTask(taskToEdit, id, newPrio, newTitle, newDeadline, true);
            cout << "[!] Task edited successfully\n";
        } else cout << "[!] Edit cancelled\n";
        pause();
    }
 public:
    void showMenu() {
        cout << "╔═════════════════════════════════════════════════════════════╗\n";
        cout << "║                        Task Manager                         ║\n";
        cout << "╠═════════════════════════════════════════════════════════════╣\n";
        cout << "║ [1] Add task              [6] Undo                          ║\n";
        cout << "║ [2] See next task         [7] View all tasks                ║\n";
        cout << "║ [3] Complete task         [8] Edit task                     ║\n";
        cout << "║ [4] Delete task           [9] Show overdue/upcoming tasks   ║\n";
        cout << "║ [5] Search                [0] Exit                          ║\n";
        cout << "╚═════════════════════════════════════════════════════════════╝\n";
        cout << " [?] Choose an option : ";
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
            } else if(choice == "9") {
                tm.showOverDueTasksAndUpcomingTasks();
            } else break;
        }
    };
};
#endif