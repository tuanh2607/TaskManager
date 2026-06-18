#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include "Task.hpp"
#include "../lib/LinkedList.hpp"
using namespace std;
namespace sys {
    void clearScreen() {
    #ifdef _WIN32
        system("chcp 65001 > nul");
        system("cls");
    #else
        system("clear");
    #endif
    }
    void pauseScreen() {
        cout << "\n[Press Enter to continue...]";
        string s;
        do {
            getline(cin, s);
        } while (!s.empty());
    }
    void pause() {
        pauseScreen();
        clearScreen();
    }
}

namespace tks {
    bool isAllDigits(const string& str) {
        if (str.empty()) return false;
        for (char c : str) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }
    long long getID(string s) {
        string hh = s.substr(0, 2);
        string mm = s.substr(3, 2);
        string dd = s.substr(6, 2);
        string mon = s.substr(9, 2);
        string yyyy = s.substr(12, 4);
        string result = yyyy + mon + dd + hh + mm;
        return stoll(result);
    }
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    int dayInMonth(int month, int year) {
        int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
        if (month == 2 && isLeapYear(year)) return 29;
        return days[month - 1];
    }
    long long UTC_VN(string date) {
        int hour = stoi(date.substr(0, 2));
        int minute = stoi(date.substr(3, 2));
        int day = stoi(date.substr(6, 2));
        int month = stoi(date.substr(9, 2));
        int year = stoi(date.substr(12, 4));

        long long days = 0;
        for (int y = 1970; y < year; y++) days += isLeapYear(y) ? 366 : 365;
        for (int m = 1; m < month; m++) days += dayInMonth(m, year);
        days += day - 1;
        long long res = days * 24 * 3600 + hour * 3600 + minute * 60 - 7 * 3600;
        return res;
    }
    bool isValidDate(int hour, int minutes, int day, int month, int year) {
        if (year < 1) return false;
        if (month < 1 || month > 12) return false;
        if (hour < 0 || hour > 23) return false;
        if (minutes < 0 || minutes > 59) return false;
        if (day < 1 || day > dayInMonth(month, year)) return false;
        return true;
    }
    bool checkDay(const string& date) {
        if (date.length() != 16) return false;
        if (date[2] != '-' || date[5] != '-' || date[8] != '-' || date[11] != '-') return false;
        string hourStr = date.substr(0, 2);
        string minuteStr = date.substr(3, 2);
        string dayStr = date.substr(6, 2);
        string monthStr = date.substr(9, 2);
        string yearStr = date.substr(12, 4);
        if (!isAllDigits(hourStr) || !isAllDigits(minuteStr) || !isAllDigits(dayStr) || !isAllDigits(monthStr) || !isAllDigits(yearStr)) return false;
        int hour = stoi(hourStr);
        int minute = stoi(minuteStr);
        int day = stoi(dayStr);
        int month = stoi(monthStr);
        int year = stoi(yearStr);
        return isValidDate(hour, minute, day, month, year);
    }
    string convertDate(const string& date) {
        string hour = date.substr(0, 2);      
        string minute = date.substr(3, 2);    
        string day = date.substr(6, 2);       
        string month = date.substr(9, 2);     
        string year = date.substr(12, 4);    
        string output = hour + ":" + minute + "-" + day + "/" + month + "/" + year;
        return output;
    }
    bool validPriority(int num){
        if(num < 1 || num > 3) return false;
        return true;
    }
}

namespace dpt {
    string repeatStr(const string &s, int n) {
        string result;
        for (int i = 0; i < n; i++)
            result += s;
        return result;
    }
    void printTask(const Task& task) {
        string line = repeatStr("═", 90);
        cout << "╔" << line << "╗" << endl;
        cout << "║ " << left <<  setw(15) << "Priority" << setw(42) << "Title" << setw(15) << "Status" << setw(15) << "Deadline" << "  ║" << endl;
        cout << "╠" << line << "╣" << endl;
        cout << "║ " << left <<  setw(15) << task.priority << setw(42) << task.title << setw(15) << task.status << setw(15) << tks::convertDate(task.deadline) << " ║" << endl;
        cout << "╚" << line << "╝" << endl;
    }
    void printTasksByQueue(Queue<Task> &q, int limit) {
        string line = repeatStr("═", 90);
        cout << "╔" << line << "╗" << endl;
        cout << "║ " << left <<  setw(15) << "Priority" << setw(42) << "Title" << setw(15) << "Status" << setw(15) << "Deadline" << "  ║" << endl;
        cout << "╠" << line << "╣" << endl;
        while(!q.empty() && limit > 0) {
            Task* task = q.front();
            cout << "║ " << left <<  setw(15) << task->priority << setw(42) << task->title << setw(15) << task->status << setw(15) << tks::convertDate(task->deadline) << " ║" << endl;
            q.dequeue();
            limit--;
        }
        cout << "╚" << line << "╝" << endl;
    }
    Task parseTask(string s, Task &task){
        vector<string> v;
        string cur = "";

        for (char c : s) {
            if (c == '|') {
                v.push_back(cur);
                cur = "";
            } else cur += c;
        }
        v.push_back(cur);
        task.id = stoll(v[0]);
        task.priority = stoi(v[1]);
        task.title = v[2];
        task.status = v[3];
        task.deadline = v[4];
        return task;
    }
    bool stringFind(string &str) {
        for(char c : str) {
            if(c == '|') return true;
        }
        return false;
    }
    void printValidPage(int n) {
        if(n == 0) {
            cout << "[!] No tasks to display\n";
            return;
        }
        if(n <= 5) {
            cout << "[!] Valid pages: ";
            for(int i = 1; i <= n; i++) {
                cout << "[" << i << "]";
            }
        } else cout << "[!] Valid pages: [1][2][3]...[" << n << "]\n";
    }
    vector<vector<Task*>> builtPage(vector<Task*> arr){
        vector<vector<Task*>> res;
        int i = 0;
        while(i < arr.size()) {
            vector<Task*> page;
            int cnt = 0;
            while(i < arr.size() && cnt < 20) {
                page.push_back(arr[i]);
                i++;
                cnt++;
            }
            res.push_back(page);
        }    
        return res;
    }
    void printPage(int pagenum, vector<vector<Task*>> &a) {
        string line = repeatStr("═", 90);
        cout << "╔" << line << "╗" << endl;
        cout << "║ " << left <<  setw(15) << "Priority" << setw(42) << "Title" << setw(15) << "Status" << setw(15) << "Deadline" << "  ║" << endl;
        cout << "╠" << line << "╣" << endl;
        vector<Task*> page = a[pagenum - 1];
        for(int i = 0; i < page.size(); i++) {
            cout << "║ " << left <<  setw(15) << page[i]->priority << setw(42) << page[i]->title << setw(15) << page[i]->status << setw(15) << tks::convertDate(page[i]->deadline) << " ║" << endl;
        }
        cout << "╚" << line << "╝" << endl;
    }
}
#endif