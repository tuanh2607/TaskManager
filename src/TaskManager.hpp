#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP
#include <iostream>
#include "Task.hpp"
#include "Scheduler.hpp"
#include "Search.hpp"
#include "History.hpp"
#include "functions.hpp"
#include "FileManager.hpp"
#include "DeadlineQueue.hpp"
#include "../lib/AVL.hpp"
#include "../lib/HashTable.hpp"
#include "../lib/PriorityQueue.hpp"
#include "../lib/Algorithms.hpp"
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
using namespace sys;
using namespace tks;
class TaskManager {
private:
    long long nextId;
    string file;
    AVL<TaskById> allTasks;
    Scheduler scheduler;
    Search search;
    History history;
    FileManager fileManager;
public:
    TaskManager(const string &filename) {
        file = filename;
        vector<Task> arr = fileManager.load(file);
        for(int i = 0; i < arr.size(); i++) {
            Task* task = new Task(arr[i]);
            TaskIdPriority P(task); 
            TaskById I(task);
            allTasks.insert(I);
            scheduler.addTask(P);
            search.addTask(I);
        }
    };
    
    ~TaskManager() {
        save();
        vector<TaskById> arr = allTasks.toVector();
        for(TaskById &tmp : arr) delete tmp.task;
    };

    void addTask(long long id, int p, string title, string deadline, bool record) {
        Task* tmp = new Task(id, p, title, deadline);
        TaskById I(tmp);
        TaskIdPriority P(tmp);
        Operation op("ADD", *tmp);
        allTasks.insert(I);
        search.addTask(I);
        scheduler.addTask(P);
        if(record) history.record(op);
    };

    void completeTask(long long id, bool record) {
        TaskById* tmp = search.findById(id);
        if(!tmp || !tmp->task) return;

        tmp->task->status = "DONE";
        Operation update("COMPLETE", *tmp->task);
        if(record) history.record(update);
    };

    void deleteTask(long long id, bool record) {
        TaskById* tmp = search.findById(id);
        if(!tmp) return;

        Task* taskPtr = tmp->task;
        TaskIdPriority taskToDelete(taskPtr);
        Operation del("DELETE", *taskPtr);

        allTasks.remove(*tmp);
        search.remove(id);
        scheduler.deleteTask(taskToDelete);
        if(record) history.record(del);
        delete taskPtr;
    };

    Task* getNextTask() {
        TaskIdPriority* tmp = scheduler.getNext();
        if(!tmp || !tmp->task) return nullptr;
        return tmp->task;
    };

    Task* searchById(long long id) {
        TaskById* tmp = search.findById(id);
        if(!tmp || !tmp->task) return nullptr;
        return tmp->task;
    };
    
     Task* searchByTitle(string title){   
        TaskByTitle* tmp = search.findByTitle(title);
        if(!tmp || !tmp->task) return nullptr;
        return tmp->task;
    }

    void listAll() {
        string choice;
        vector<TaskById> allTasksArr = allTasks.toVector();
        cout << "[?] Sort by [1] Deadline or [2] Priority : ";
        getline(cin, choice);

        vector<Task*> taskList;

        if(choice == "1") {
            quickSort(allTasksArr, 0, allTasksArr.size() - 1);
            for(TaskById &tmp : allTasksArr) taskList.push_back(tmp.task);
        } else if(choice == "2") {
            vector<TaskByPriority> tasksByPriority;
            for(TaskById &tmp : allTasksArr) tasksByPriority.push_back(TaskByPriority(tmp.task));
            quickSort(tasksByPriority, 0, tasksByPriority.size() - 1, greater<TaskByPriority>{});
            for(TaskByPriority &tmp : tasksByPriority) taskList.push_back(tmp.task);
        } else {
            cout << "[!] Invalid choice\n";
            pause();
            return;
        }

        vector<vector<Task*>> pages = builtPage(taskList);
        while(true) {
            clearScreen();
            printValidPage(pages.size());
            string input;
            cout << "[?] Enter page number to view or any non-digit to exit : ";
            getline(cin, input);
            if(!isAllDigits(input) || input.empty()) break;
            int pageNum = stoi(input);
            if(pageNum <= 0 || pageNum > pages.size()) {
                clearScreen();
                break;
            }
            printPage(pageNum, pages);
            pause();
        }
        clearScreen();
    }

    void undo() {
        if(!history.canUndo()) {
            cout << "[!] No operations to undo\n";
            return;
        }
        Operation* operation = history.lastOperation();
        if(!operation) return;
        if(operation->type == "ADD") {
            deleteTask(operation->oldTask.id, false);
            cout << "[!] Undo add task successful\n";
        } else if(operation->type == "DELETE") {
            addTask(operation->oldTask.id, operation->oldTask.priority, operation->oldTask.title, operation->oldTask.deadline, false);
            cout << "[!] Undo delete task successful\n";
        } else if(operation->type == "COMPLETE") {
            TaskById* tmp = search.findById(operation->oldTask.id);
            if(tmp && tmp->task) {
                tmp->task->status = operation->oldTask.status;
                cout << "[!] Undo complete task successful\n";
            }
        } else if(operation->type == "EDIT") {
            editTask(&operation->newTask, operation->oldTask.id, operation->oldTask.priority, operation->oldTask.title, operation->oldTask.deadline, false);
            cout << "[!] Undo edit task successful\n";
        }
        history.pop();
    }
    void editTask(Task* oldTask, long long newId, int newPriority, string newTitle, string newDeadline, bool record) {
        Task savedOldTask = *oldTask; 
        deleteTask(oldTask->id, false);
        addTask(newId, newPriority, newTitle, newDeadline, false);
        if(record) {
            Operation op("EDIT", savedOldTask, Task(newId, newPriority, newTitle, newDeadline));
            history.record(op);
        }
    }

    void showOverDueTasksAndUpcomingTasks() {
            DeadlineQueue dq;
            vector<TaskById> allTasksArr = allTasks.toVector();
            for(TaskById &tmp : allTasksArr) {
                if(tmp.task->status == "TODO") dq.addTask(*tmp.task);
            }
            dq.showAll();
            pause();
    }
    void save() {
        fileManager.save(allTasks, file);
    }
};
#endif
