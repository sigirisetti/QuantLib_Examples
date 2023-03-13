//
// Created by appuprakhya on 18/2/23.
//
#include<iostream>
#include<ql/interestrate.cpp>
#include <ql/time/daycounters/actual360.hpp>

using namespace QuantLib;

void Interest_Rate_Ex() {

    InterestRate rate(0.05, Actual360(), QuantLib::Compounded, QuantLib::Annual);
    Date d1(15, Jun, 2020);
    Date d2(15, Jun, 2021);

    std::cout << "Rate : " << rate.rate() << std::endl;
    std::cout << "DayCount: " << rate.dayCounter() << std::endl;
    std::cout << "DiscountFactor: " << rate.discountFactor(1) << std::endl;
    std::cout << "DiscountFactor: " << rate.discountFactor(d1, d2) << std::endl;
    std::cout << "CompoundFactor: " << rate.compoundFactor(d1, d2) << std::endl;
    std::cout << "EquivalentRate: " << rate.equivalentRate(Actual360(), Compounded, Semiannual, d1, d2) << std::endl;
    Real factor = rate.compoundFactor(d1, d2);
    Real impliedRate = QuantLib::InterestRate::impliedRate(factor, Actual360(), Continuous, Annual, d1, d2);
    std::cout << "ImpliedRate: " << impliedRate << std::endl;
}