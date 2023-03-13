//
// Created by appuprakhya on 25/2/23.
//
#include<iostream>
#include<ql/quantlib.hpp>
#include<ql/time/date.hpp>

using namespace QuantLib;

void cashflow_examples() {
    Real amount = 105;
    Date date(15, QuantLib::Jun, 2020);

    SimpleCashFlow simpleCashFlow(amount, date);
    std::cout << simpleCashFlow.date() << std::endl;
    std::cout << simpleCashFlow.exCouponDate() << std::endl;
    std::cout << simpleCashFlow.amount() << std::endl;
    std::cout << simpleCashFlow.tradingExCoupon() << std::endl;

    Redemption redemption(amount, date);
    std::cout << redemption.date() << std::endl;
    std::cout << redemption.exCouponDate() << std::endl;
    std::cout << redemption.amount() << std::endl;
    std::cout << redemption.tradingExCoupon() << std::endl;

    AmortizingPayment amortizingPayment(amount, date);
    std::cout << redemption.date() << std::endl;
    std::cout << redemption.exCouponDate() << std::endl;
    std::cout << redemption.amount() << std::endl;
    std::cout << redemption.tradingExCoupon() << std::endl;
}