#include <iostream>
#include "UI.hpp"
#include "../lib/AVL.hpp"
#include "../lib/HashTable.hpp"
#include "../system/PatientInformation.hpp"
#include "string"
using namespace std;

int main(int argc, char **argv) {
    system("chcp 65001 > nul");
    string dataFile = argv[1];
    AVL<Pair<int, Patient>> Object;
    clearScreen();
    UI sys;
    string s; 
    while(true) {
        cout << "╔══════════════════════════╗\n";
        cout << "║           Menu           ║\n";
        cout << "╠══════════════════════════╣\n";
        cout << "║ [1] Quan ly benh nhan    ║\n";
        cout << "║ [2] Hang doi kham        ║\n";
        cout << "║ [3] Ho so benh an        ║\n";
        cout << "║ [4] Thong ke             ║\n";
        cout << "║ [0] Thoat                ║\n";
        cout << "╚══════════════════════════╝\n";
        cout << "[?] Chon: ";
        getline(cin, s);
        cout << endl;
        clearScreen();
        if(s == "1") {
            sys.PatientMenu(dataFile);
        } else if(s == "2") {
            sys.QueueMenu(dataFile);
        } else if(s == "3") {
            sys.RecordMenu(dataFile);
        } else if(s == "4") {
            sys.ReportMenu(dataFile);
        } else break;
    }
    return 0;
}