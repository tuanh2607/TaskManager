#include <iostream>
#include "../lib/HashTable.hpp"
#include "UI.hpp"
#include "string"
using namespace std;

int main() {
    string s; 
    while(true) {
        cout << "-=-=-=-=-=Menu=-=-=-=-=-\n";
        cout << "[1] Quan ly benh nhan\n";
        cout << "[2] Hang doi kham\n";
        cout << "[3] Ho so benh an\n";
        cout << "[4] Thong ke\n";
        cout << "[0] Thoat\n";
        cout << "-=-=-=-=-=-=-=-=-=-=-=-=-\n";
        cout << "[?] Chon: ";
        getline(cin, s);
        if(s == "1") {
            clearScreen();

        } else if(s == "2") {
            clearScreen();

        } else if(s == "3") {
            clearScreen();

        } else if(s == "4") {
            clearScreen();

        } else break;
    }
    return 0;
}