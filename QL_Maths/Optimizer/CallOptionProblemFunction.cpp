//
// Created by appuprakhya on 27/10/22.
//

#include "CallOptionProblemFunction.h"

#include<ql/quantlib.hpp>
#include "common_All.hpp"

using namespace QuantLib;

Real CallOptionProblemFunction::value(const Array &x) const {
    Array tmpRes = values(x);
    Real res = tmpRes[0] * tmpRes[0];
    res += tmpRes[1] * tmpRes[1];
    res += tmpRes[2] * tmpRes[2];
    res += tmpRes[3] * tmpRes[3];
    return res;
}

Array CallOptionProblemFunction::values(const Array &x) const {
    Array res(4);
    res[0] = blackScholesPrice(x[0], K1_, rd_, rf_, x[1], tau_, phi_) - C1_;
    res[1] = blackScholesPrice(x[0], K2_, rd_, rf_, x[1], tau_, phi_) - C2_;
    res[2] = blackScholesPrice(x[0], K3_, rd_, rf_, x[1], tau_, phi_) - C3_;
    res[3] = blackScholesPrice(x[0], K4_, rd_, rf_, x[1], tau_, phi_) - C4_;
    return res;

}
