//
// Created by appuprakhya on 4/2/23.
//
#include<iostream>
#include<ql/quantlib.hpp>
#include<ql/quotes/compositequote.hpp>
#include<ql/quote.hpp>

using namespace QuantLib;

void ql_composite_quote_test() {
    ext::shared_ptr<Quote> q1(new SimpleQuote(0.01));
    ext::shared_ptr<Quote> q2(new SimpleQuote(0.03));
    ext::shared_ptr<Quote> eurusdSpot(new SimpleQuote(1.23456));

    auto handle1 = Handle<Quote>(q1);
    auto handle2 = Handle<Quote>(q2);
    auto f1 = [](double x, double y) { return x + y; };
    auto compositeQuote = CompositeQuote<std::function<double(double, double)>>(handle1, handle2, f1);

    std::cout << compositeQuote.value() << std::endl;
}