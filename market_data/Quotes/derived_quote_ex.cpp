//
// Created by appuprakhya on 4/2/23.
//
#include<iostream>
#include<ql/quantlib.hpp>
#include<ql/quotes/derivedquote.hpp>
#include<ql/quote.hpp>

using namespace QuantLib;

void ql_derived_quote_test() {
    ext::shared_ptr<Quote> quote(new SimpleQuote(0.01));
    auto handle = Handle<Quote>(quote);
    auto derivedQuote = DerivedQuote<std::function<double(double)>>(handle, [](double q) { return q * 10000; });
    std::cout << derivedQuote.value() << std::endl;
}