#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP
#include <iostream>
#include "UI.hpp"
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
using namespace std;
class TaskManager {
private:
    AVL<Task> allTasks; // nguồn sự thật
    Scheduler scheduler;
    Search search;
    History history;
    FileManager fileManager;
    long long nextId;
    string filename;
public:
    // Constructor: load dữ liệu từ file CSV, nạp vào Scheduler + SearchEngine
    TaskManager(const string &filename) {
        vector<Task> arr = fileManager.load(filename);
        for(int i = 0; i < arr.size(); i++) {
            allTasks.insert(arr[i]);
            if(arr[i].priority == 1) scheduler.addNormal(arr[i]);
            else scheduler.addUrgent(arr[i]);
            search.addTask(arr[i]);
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
    void addTask(string title, int p, string deadline) {

    };

    // Đánh dấu task là DONE, cập nhật trong SearchEngine, record vào History
    void completeTask(long long id) {
        Task* tmp = search.findById(id);
        if(!tmp) return;
        Operation update;
        update.type = "COMPLETE";
        update.task = *tmp;
        history.record(update);
    };

    // Xóa task khỏi Scheduler và SearchEngine, record vào History
    void deleteTask(int id) {

    };

    // Gọi Scheduler.getNext() để lấy task ưu tiên cao nhất hiện tại
    Task* getNextTask() {
        return scheduler.getNext();
    };
    // Gọi SearchEngine.findById()
    Task *searchById(long long id) {
        return search.findById(id);
    };

    // Gọi SearchEngine.findByTitle()
    Task *searchByTitle(const string &title);

    // Lấy toàn bộ task, dùng Algorithms để sort theo priority rồi in ra
    void listAll() {
        vector<Task> arr;
        arr = allTasks.toVector();
        quickSort(arr,0, arr.size() - 1);
        vector<vector<Task>> table = builtPage(arr);
        int size_page = table.size();
        printValidPage(size_page);
        while(true) {
            int choice;
            cout << "[!] Chọn trang (Chọn ngoài khoảng để thoát) : ";
            cin >> choice;
            if(!isdigit(choice) || choice < 0 || choice > 0) return;
            clearScreen();
            printPage(choice, table);
        }
    };

    // Gọi History.undo(), thực hiện thao tác ngược lại, cập nhật DS tương ứng
    void undo() {

    };

    // Gọi FileManager.save() để ghi toàn bộ task xuống file
    void save() {
        vector<Task> arr;
        arr = allTasks.toVector();
        fileManager.save(arr, filename);
    };
};
#endif