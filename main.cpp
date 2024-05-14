#include <iostream>
#include <wchar.h>
#include <string>
#include <vector>
#include "tree_creation.h"

int main() {
    try {
        wchar_t string[100] = L"tests/Markov6.IN";
        tree_creation(string);
    } catch (const std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
