//
// Created by appuprakhya on 14/9/22.
//
#include <iostream>
#include <ql/math/randomnumbers/all.hpp>

using namespace std;
using namespace QuantLib;

void testRandomSeqGenUsingMTRng() {
    RandomSequenceGenerator<MersenneTwisterUniformRng>
            generator(100, 12345);
    std::vector<Real> values = generator.nextSequence().value;
    for (double value : values) {
        std::cout << value << std::endl;
    }
}
