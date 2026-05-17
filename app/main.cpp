#include <iostream>
#include "../lib/HashTable.hpp"
using namespace std;

int main() {
    HashTable<string, string> map;
    map.insert("Hoa", "Tran Van Tuan Anh");
    cout << map.find("Hoa") << endl;
    cout << map.find("Hung");
    return 0;
}