#include <iostream>
#include "../src/UI.hpp"
#include "../src/TaskManager.hpp"
#include "string"
using namespace std;

int main(int argc, char **argv) {
    string dataFile = argv[1];
    TaskManager program(dataFile);
    UI sys;
    sys.runLoop(program);
    program.save();
    return 0;
}