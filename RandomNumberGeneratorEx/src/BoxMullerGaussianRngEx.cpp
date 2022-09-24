//
// Created by appuprakhya on 23/9/22.
//
#include <iostream>
#include <ql/math/randomnumbers/all.hpp>

using namespace std;
using namespace QuantLib;

void boxMullerGaussianRngEx() {
    BigInteger seed = 12324;
    MersenneTwisterUniformRng unifMt(seed);
    BoxMullerGaussianRng <MersenneTwisterUniformRng> bmGauss(unifMt);
    std::cout << bmGauss.next().value << std::endl;
    std::cout << bmGauss.next().value << std::endl;
    std::cout << bmGauss.next().value << std::endl;
    std::cout << bmGauss.next().value << std::endl;
    std::cout << bmGauss.next().value << std::endl;
}