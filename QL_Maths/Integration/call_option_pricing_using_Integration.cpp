#include <functional>
#include <ql/quantlib.hpp>
#include <boost/math/distributions.hpp>

using namespace QuantLib;

Real callFunc(Real spot, Real strike, Rate r, Volatility vol, Time tau, Real x) {
    Real mean = log(spot) + (r - 0.5 * vol * vol) * tau;
    Real stdDev = vol * sqrt(tau);
    boost::math::lognormal_distribution<> d(mean, stdDev);
    return (x - strike) * pdf(d, x) * exp(-r * tau);
}

using namespace std::placeholders;    // adds visibility of _1, _2, _3,...

void call_option_pricing_using_Integration() {
    Real spot = 100.0;
    Rate r = 0.03;
    Time tau = 0.5;
    Volatility vol = 0.20;
    Real strike = 110.0;
    Real a = strike, b = strike * 10.0;
    auto ptrF = std::bind(&callFunc, spot, strike, r, vol, tau, _1);
    Real absAcc = 0.00001;
    Size maxEval = 1000;
    SimpsonIntegral numInt(absAcc, maxEval);
    std::cout << " Call Value : " << numInt(ptrF, a, b) << std::endl;
}