#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP
#include "Task.hpp"
#include "functions.hpp"
#include <vector>
#include <fstream>
using namespace std;
class FileManager {
public:
    // Ghi toàn bộ vector<Task> xuống file CSV, ghi đè nếu file đã tồn tại
    void save(const vector<Task>& tasks, const string& filename) {
        ofstream f(filename);
        f << "id,priority,title,status,deadline\n";
        for(int i = 0; i < tasks.size(); i++) {
            f << tasks[i].id << ',' << tasks[i].title << ',' << tasks[i].priority << ',' << tasks[i].deadline << ',' << tasks[i].status << ',' << endl;
        }
    };

    // Đọc file CSV, parse từng dòng thành Task, trả về vector để TaskManager nạp vào
    vector<Task> load(const string& filename) {
        ifstream f(filename);
        vector<Task> arr;
        string s;
        getline(f, s);
        while(getline(f,s)) {
            Task o;
            arr.push_back(parseTask(s, o));
        }
        return arr;
    }
};
#endif