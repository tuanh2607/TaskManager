#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP
#include <iostream>
#include "Task.hpp"
#include "Scheduler.hpp"
#include "Search.hpp"
#include "History.hpp"
#include "functions.hpp"
#include "FileManager.hpp"
#include "../lib/AVL.hpp"
#include "../lib/HashTable.hpp"
#include "../lib/PriorityQueue.hpp"
#include "../lib/Algorithms.hpp"
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
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
            Task* t = new Task(arr[i]);
            TaskByPriority P(t);
            TaskById I(t);
            allTasks.insert(I);
            scheduler.addUrgent(P);
            search.addTask(I);
        }
    };
    ~TaskManager() {
        save();
        vector<TaskById> arr = allTasks.toVector();
        for(TaskById &t : arr) delete t.task;
    };
    // Tạo Task mới, thêm vào Scheduler và SearchEngine, record vào History
    void addTask(long long id, int p, string title, string deadline, bool record) {
        Task* tmp = new Task(id, p, title, deadline);
        TaskById I(tmp);
        TaskByPriority P(tmp);
        Operation op("ADD", *tmp);
        allTasks.insert(I);
        search.addTask(I);
        scheduler.addUrgent(P);
        if(record) history.record(op);
    };

    // Đánh dấu task là DONE, cập nhật trong SearchEngine, record vào History
    void completeTask(long long id, bool record) {
        TaskById* tmp = search.findById(id);
        if(!tmp || !tmp->task) return;

        tmp->task->status = "DONE";
        Operation update("COMPLETE", *tmp->task);
        if(record) history.record(update);
    };

    // Xóa task khỏi Scheduler và SearchEngine, record vào History
    void deleteTask(long long id, bool record) {
        TaskById* tmp = search.findById(id);
        if(!tmp) return;

        TaskByPriority taskToDelete(tmp->task);
        Operation del("DELETE", *tmp->task);

        allTasks.remove(*tmp);
        search.remove(id);
        scheduler.deleteTask(taskToDelete);
        if(record) history.record(del);
        delete tmp->task;
    };

    // Gọi Scheduler.getNext() để lấy task ưu tiên cao nhất hiện tại
    Task* getNextTask() {
        TaskByPriority* tmp = scheduler.getNext();
        if(!tmp || !tmp->task) return nullptr;
        return tmp->task;
    };
    // Gọi SearchEngine.findById()
    Task* searchById(long long id) {
        TaskById* tmp = search.findById(id);
        if(!tmp || !tmp->task) return nullptr;
        return tmp->task;
    };
    
    // Task* searchByTitle(string title){   
    // }
    // Lấy toàn bộ task, dùng Algorithms để sort theo priority rồi in ra
    void listAll() {
        vector<TaskById> allTasksArr = allTasks.toVector();
        vector<TaskByPriority> tasksByPriority;

        for(TaskById &t : allTasksArr) tasksByPriority.push_back(TaskByPriority(t.task));
        quickSort(tasksByPriority, 0, tasksByPriority.size() - 1);
        
        vector<Task> taskList;
        for(TaskByPriority &t : tasksByPriority) taskList.push_back(*t.task);

        vector<vector<Task>> pages = builtPage(taskList);
        while(true) {
            printValidPage(pages.size());
            string input;
            cout << "[!] Enter page number to view or any non-digit to exit : ";
            getline(cin, input);    
            if(!isAllDigits(input)) break;    
            int pageNum = stoi(input);
            if(pageNum <= 0 || pageNum > pages.size()) {
                clearScreen();
                break;
            }    
            printPage(pageNum, pages);
            pauseScreen();
            clearScreen();
        }
        clearScreen();
    }

    void undo() {
        if(!history.canUndo()) {
            cout << "[!] No operations to undo\n";
            return;
        }
        Operation* op = history.lastOperation();
        if(!op) return;
        if(op->type == "ADD") {
            deleteTask(op->task.id, false);
            cout << "[!] Undo add task successful\n";
        } else if(op->type == "DELETE") {
            addTask(op->task.id, op->task.priority, op->task.title, op->task.deadline, false);
            cout << "[!] Undo delete task successful\n";
        } else if(op->type == "COMPLETE") {
            TaskById* tmp = search.findById(op->task.id);
            if(tmp && tmp->task) {
                tmp->task->status = "TODO";
                cout << "[!] Undo complete task successful\n";
            }

        }
        history.pop();

        // here 
    };
    void save() {
        fileManager.save(allTasks, file);
    };
};
#endif
