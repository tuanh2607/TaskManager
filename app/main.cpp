#include <iostream>
#include "../TaskManager/UI.hpp"
#include "../TaskManager/Taskmanager.hpp"
#include "string"
using namespace std;

int main(int argc, char **argv) {
    system("chcp 65001 > nul");
    string dataFile = argv[1];
    TaskManager program(dataFile);
    UI sys;
    sys.runLoop(program);
    program.save();
    return 0;
}