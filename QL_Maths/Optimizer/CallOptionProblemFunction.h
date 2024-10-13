//
// Created by appuprakhya on 27/10/22.
//

#ifndef QUANTLIB_EXAMPLES_CALLOPTIONPROBLEMFUNCTION_H
#define QUANTLIB_EXAMPLES_CALLOPTIONPROBLEMFUNCTION_H

#include<ql/quantlib.hpp>

using namespace QuantLib;

class CallOptionProblemFunction : public CostFunction {

private:
    Real C1_, C2_, C3_, C4_, K1_, K2_, K3_, K4_;
    Rate rd_, rf_;
    Integer phi_;
    Time tau_;

public:
    CallOptionProblemFunction(const Rate &rd, const Rate &rf, const Time &tau, const Integer &phi,
                              const Real &K1, const Real &K2, const Real &K3, const Real &K4,
                              const Real &C1, const Real &C2, const Real &C3, const Real &C4)
            : C1_(C1), C2_(C2), C3_(C3), C4_(C4),
              K1_(K1), K2_(K2), K3_(K3), K4_(K4),
              rd_(rd), rf_(rf), phi_(phi), tau_(tau) {
    }

    Real value ( const Array & x ) const;

    Array values ( const Array & x ) const;
};


#endif //QUANTLIB_EXAMPLES_CALLOPTIONPROBLEMFUNCTION_H
