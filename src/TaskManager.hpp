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
    AVL<TaskById> allTasks;
    Scheduler scheduler;
    Search search;
    History history;
    FileManager fileManager;
    long long nextId;
    string file;
public:
    // Constructor: load dữ liệu từ file CSV, nạp vào Scheduler + SearchEngine
    TaskManager(const string &filename) {
        file = filename;
        vector<Task> arr = fileManager.load(file);
        for(int i = 0; i < arr.size(); i++) {
            TaskByPriority P(arr[i]);
            TaskById I(arr[i]);
            allTasks.insert(TaskById(arr[i]));
            scheduler.addUrgent(P);
            search.addTask(I);
        }
    };
    // Destructor: tự động gọi save() trước khi object bị hủy
    ~TaskManager() {
        save();
    };

    // Thêm task vào AVL (key = deadline) và HashTable (key = id)
    void index(Task t) {

    };
    // Tạo Task mới, thêm vào Scheduler và SearchEngine, record vào History
    void addTask(long long id, int p, string title, string deadline) {
        Task tmp(id, p, title, deadline);
        TaskById I(tmp);
        TaskByPriority P(tmp);
        allTasks.insert(I);
        search.addTask(I);
        scheduler.addUrgent(P);
    };

    // Đánh dấu task là DONE, cập nhật trong SearchEngine, record vào History
    void completeTask(long long id) {
        TaskById* tmp = search.findById(id);
        if(!tmp) return;
        Operation update("COMPLETE", tmp->task);
        history.record(update);
    };

    // Xóa task khỏi Scheduler và SearchEngine, record vào History
    void deleteTask(long long id) {
        search.remove(id);
        allTasks.remove(*search.findById(id));
    };

    // Gọi Scheduler.getNext() để lấy task ưu tiên cao nhất hiện tại
    Task* getNextTask() {
        return &scheduler.getNext()->task;
    };
    // Gọi SearchEngine.findById()
    Task searchById(long long id) {
        return search.findById(id)->task;
    };
    // Lấy toàn bộ task, dùng Algorithms để sort theo priority rồi in ra
    void listAll() {
        vector<TaskById> arr;
        arr = allTasks.toVector();
        vector<TaskByPriority> ar;
        for(TaskById &t : arr) ar.push_back(TaskByPriority(t.task));
        quickSort(ar, 0, ar.size() - 1);
        vector<Task> taskList;
        for(TaskByPriority &t : ar) taskList.push_back(t.task);
        vector<vector<Task>> table = builtPage(taskList);
        int size_page = table.size();
        while(true) {
            printValidPage(size_page);
            string s;
            cout << "[!] Enter page number to view or any non-digit to exit : ";
            getline(cin, s);
            if(isAllDigits(s)) {
                int choice = stoi(s);
                if(choice <= 0 || choice > size_page) {
                    clearScreen();
                    return;
                }
                printPage(choice, table);
                pauseScreen();
                clearScreen();
            } else {
                clearScreen();
                return;
            }
        }
    };
    // Gọi History.undo(), thực hiện thao tác ngược lại, cập nhật DS tương ứng
    void undo() {

    };

    // Gọi FileManager.save() để ghi toàn bộ task xuống file
    void save() {
        fileManager.save(allTasks, file);
    };
};
#endif