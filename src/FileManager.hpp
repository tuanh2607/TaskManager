#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP
#include "Task.hpp"
#include "functions.hpp"
#include <vector>
#include <fstream>
using namespace std;
class FileManager {
public:
    void save(AVL<TaskById>& tasks, const string& filename) {
        ofstream f(filename);
        vector<TaskById> arr = tasks.toVector();
        f << "id,priority,title,status,deadline\n";
        for(TaskById &t : arr) {
            Task ts = t.task;
            f << ts.id << ',' << ts.priority << ',' << ts.title << ',' << ts.status << ',' << ts.deadline << endl;
        }
    };
    vector<Task> load(const string& filename) {
        ifstream f(filename);
        vector<Task> arr;
        string s;
        getline(f, s);
        while(getline(f,s)) {
            Task object;
            arr.push_back(parseTask(s, object));
        }
        return arr;
    }
};
#endif