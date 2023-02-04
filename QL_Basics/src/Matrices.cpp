//
// Created by appuprakhya on 4/2/23.
//
#include<iostream>
#include<ql/math/matrix.hpp>

using namespace QuantLib;

void ql_matrix_test() {
    auto arr1 = Matrix(10, 10);
    std::cout << arr1 << std::endl;

    auto arr2 = Matrix(10, 10, 1);
    std::cout << arr2 << std::endl;
}