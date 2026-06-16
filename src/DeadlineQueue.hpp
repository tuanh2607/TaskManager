#ifndef DEADLINEQUEUE_HPP
#define DEADLINEQUEUE_HPP
#include "Task.hpp"
#include "../lib/Queue.hpp"
#include "functions.hpp"
#include <ctime>
#include <string>
using namespace std;
using namespace tks;
using namespace sys;
using namespace dpt;

class DeadlineQueue {
private:
    Queue<Task> tasksOverdue;
    Queue<Task> tasksUpcoming;
public:
    void addTask(Task &task) {
        if(isOverdue(task.deadline)) tasksOverdue.enqueue(task);
        else tasksUpcoming.enqueue(task);
    }
    bool isOverdue(string deadline) {
        long long now = time(0);
        long long taskTime = UTC_VN(deadline);
        return taskTime < now;
    }
    void showAll() {
        cout << "[?] Show [1] Overdue tasks or [2] Upcoming tasks : ";
        string choice;
        getline(cin, choice);
        if(choice == "1") { 
            if(tasksOverdue.empty()) {
                cout << "[!] No overdue tasks\n";
                return;
            }
            clearScreen();
            cout << "Overdue tasks : \n";
            printTasksByQueue(tasksOverdue, 20);
        } else if(choice == "2") {
            if(tasksUpcoming.empty()) {
                cout << "[!] No upcoming tasks\n";
                return;
            }
            clearScreen();
            cout << "Upcoming tasks : \n";
            printTasksByQueue(tasksUpcoming, 20);
        } else {
            cout << "[!] Invalid choice\n";
            return;
        }
    }
};
#endif
