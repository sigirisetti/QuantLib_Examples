//
// Created by appuprakhya on 4/2/23.
//
#include<iostream>
#include<ql/quantlib.hpp>
#include<ql/quotes/simplequote.hpp>

using namespace QuantLib;

void ql_quotes_test() {
    SimpleQuote quote = SimpleQuote(0.01);
    std::cout << quote.value() << std::endl;
}