#include <iostream>
#include "../lib/AVL.hpp"
#include "UI.hpp"
#include <cstdlib>
using namespace std;
// Khởi tạo TaskManager với tên file, gọi runLoop
int  main(int argc, char **argv) {
    system("chcp 65001 > nul");
    string File = argv[1];
    AVL<Task> root;
    UI sys;
    while(true) {
        sys.showMenu();
        string s;
        if(s == "1") {

        } else if(s == "2") {

        } else if(s == "3") {

        } else if(s == "4") {
            
        } else if(s == "5") {

        } else if(s == "6") {

        } else if(s == "7") {

        } else break;
    }
    return 0;
};