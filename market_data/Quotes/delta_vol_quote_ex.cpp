//
// Created by appuprakhya on 4/2/23.
//
#include<iostream>
#include<ql/quantlib.hpp>
#include<ql/experimental/fx/deltavolquote.hpp>
#include<ql/quote.hpp>

using namespace QuantLib;

void ql_fx_delta_quote_test() {
    ext::shared_ptr<Quote> p1(new SimpleQuote(0.08));
    ext::shared_ptr<Quote> p2(new SimpleQuote(0.075));
    ext::shared_ptr<Quote> p3(new SimpleQuote(0.095));

    auto atmDeltaQuote = DeltaVolQuote(Handle<Quote>(p1), DeltaVolQuote::Fwd, 1.0, DeltaVolQuote::AtmFwd);
    auto vol25DeltaPutQuote = DeltaVolQuote(Handle<Quote>(p2), DeltaVolQuote::Fwd, 1.0, DeltaVolQuote::AtmFwd);
    auto vol25DeltaCallQuote = DeltaVolQuote(Handle<Quote>(p3), DeltaVolQuote::Fwd, 1.0, DeltaVolQuote::AtmFwd);
}