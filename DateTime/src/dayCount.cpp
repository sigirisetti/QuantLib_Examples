//
// Created by appuprakhya on 3/2/23.
//
#include<iostream>
#include<ql/time/date.hpp>
#include<ql/time/daycounters/simpledaycounter.hpp>
#include<ql/time/daycounters/thirty360.hpp>

using namespace QuantLib;

void dayCounterTesting1() {
    DayCounter dc = Thirty360(Thirty360::USA);
    Date d1(1, Oct, 2009);
    Date d2 = d1 + 2 * Months;
    std::cout << " Days Between d1/ d2:" << dc.dayCount(d1, d2) << std::endl;
    std::cout << " Year Fraction d1 /d2:" << dc.yearFraction(d1, d2) << std::endl;
}