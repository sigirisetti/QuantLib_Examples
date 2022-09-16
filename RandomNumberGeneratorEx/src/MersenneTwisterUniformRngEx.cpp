//
// Created by appuprakhya on 14/9/22.
//
#include <iostream>
#include <ql/math/randomnumbers/all.hpp>

using namespace std;
using namespace QuantLib;

void testMersenneTwisterUniformRng() {
    MersenneTwisterUniformRng generator(12345);
    for (int i=0; i<100; ++i) {
        cout << generator.next().value << std::endl;
    }
}
