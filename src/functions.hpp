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
void clearScreen() {
#ifdef _WIN32
    system("chcp 65001 > nul");
    system("cls");
#else
    system("clear");
#endif
}
void pauseScreen() {
    cout << "\n  [Press Enter to continue...]";
    cin.get();
}
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool isValidDate(int day, int month, int year) {
    if (year < 1) return false;
    if (month < 1 || month > 12) return false;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) daysInMonth[1] = 29;
    if (day < 1 || day > daysInMonth[month - 1]) return false;
    return true;
}
string convertDate(string date) {
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
long long extractDate(string d) {
    string s;
    for(char c:d) {
        if(c != '-') s += c;
    }
    return stoll(s);
}
Task parseTask(string s, Task &o){
    vector<string> v;
    string cur = "";

    for (char c : s) {
        if (c == ',') {
            v.push_back(cur);
            cur = "";
        } else cur += c;
    }
    v.push_back(cur);
    o.id = stoll(v[0]);
    o.priority = stoi(v[1]);
    o.title = v[2];
    o.status = v[3];
    o.deadline = v[4];
    return o;
}
void printValidPage(int n) {
    cout << "[!] Valid pages: ";
    for(int i = 0; i < n; i++) {
        cout << "(" << i + 1 << ")~>";
    }
    cout << "end\n";
}
string repeatStr(const string &s, int n) {
    string result;
    for (int i = 0; i < n; i++)
        result += s;
    return result;
}
vector<vector<Task>> builtPage(vector<Task> arr){
    vector<vector<Task>> res;
    int i = 0;
    while(i < arr.size()) {
        vector<Task> page;
        int cnt = 0;
        while(i < arr.size() && cnt < 10) {
            page.push_back(arr[i]);
            i++;
            cnt++;
        }
        res.push_back(page);
    }    
    return res;
}
void printPage(int pagenum, vector<vector<Task>> &a) {
    string line = repeatStr("═", 103);
    cout << line << endl;
    cout << left << setw(15) << "ID" << setw(15) << "Priority" << setw(42) << "Title" << setw(15) << "Status" << setw(15) << "Deadline" << endl;
    cout << line << endl;
    vector<Task> page = a[pagenum - 1];
    for(int i = 0; i < page.size(); i++) {
        cout << left << setw(15) << page[i].id << setw(15) << page[i].priority << setw(42) << page[i].title << setw(15) << page[i].status << setw(15) << convertDate(page[i].deadline) << endl;
    }
    cout << line << endl;
}
bool isAllDigits(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
#endif