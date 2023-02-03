#include<iostream>
#include<ql/errors.hpp>

using namespace QuantLib;

int find(const char *array, int size, char val) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == val) return i;
    }
    QL_FAIL("Value not found in array of size " << size);
}

void testingMacros1() {
    double x = 0.0;
    QL_REQUIRE (x != 0, " Zero number !");
}

void QL_Macro_Example() {
    char array[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    try {
        char c;
        std::cin >> c;
        int pos = find(array, 10, c);
        std::cout << "Position is " << pos << std::endl;
    }
    catch (Error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
