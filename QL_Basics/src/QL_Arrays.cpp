//
// Created by appuprakhya on 4/2/23.
//
#include<iostream>
#include<ql/quantlib.hpp>
#include<ql/math/array.hpp>

using namespace QuantLib;

void ql_arrays_test() {
    auto arr1 = Array(10, 10);
    std::cout << arr1 << std::endl;

    auto arr2 = Array(10, 10, 1);
    std::cout << arr2 << std::endl;
}