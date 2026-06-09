#include <iostream>
#include "../src/UI.hpp"
#include "../src/TaskManager.hpp"
#include "string"
using namespace std;
using namespace sys;
int main(int argc, char **argv) {
    string dataFile = (argc > 1) ? argv[1] : "data.txt";
    TaskManager program(dataFile);
    UI prog;
    clearScreen();
    prog.runLoop(program);
    program.save();
    return 0;
}