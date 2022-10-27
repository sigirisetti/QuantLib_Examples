//
// Created by appuprakhya on 27/10/22.
//

#ifndef QUANTLIB_EXAMPLES_COMMON_ALL_HPP
#define QUANTLIB_EXAMPLES_COMMON_ALL_HPP

#include<ql/quantlib.hpp>

using namespace QuantLib;

Real blackScholesPrice(const Real &spot, const Real &strike, const Rate &rd, const Rate &rf,
                       const Volatility &vol, const Time &tau, const Integer &phi);
#endif //QUANTLIB_EXAMPLES_COMMON_ALL_HPP
