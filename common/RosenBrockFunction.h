//
// Created by appuprakhya on 17/10/22.
//

#ifndef QUANTLIB_EXAMPLES_ROSENBROCKFUNCTION_H
#define QUANTLIB_EXAMPLES_ROSENBROCKFUNCTION_H
#include <ql/quantlib.hpp>

using namespace QuantLib;

class RosenBrockFunction : public CostFunction {
public :
    Real value(const Array &x) const override;
    Array values(const Array &x) const override;
};
#endif //QUANTLIB_EXAMPLES_ROSENBROCKFUNCTION_H
