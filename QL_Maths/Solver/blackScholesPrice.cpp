//
// Created by appuprakhya on 8/10/22.
//
#include<iostream>
#include<boost/math/distributions.hpp>
#include<ql/quantlib.hpp>
#include <boost/bind.hpp>

using namespace QuantLib;

Real blackScholesPrice(const Real &spot, const Real &strike, const Rate &rd, const Rate &rf,
                       const Volatility &vol, const Time &tau, const Integer &phi) {

    boost::math::normal_distribution<> d(0.0, 1.0);
    Real dp, dm, fwd, stdDev, res, domDf, forDf;
    domDf = std::exp(-rd * tau);
    forDf = std::exp(-rf * tau);
    fwd = spot * forDf / domDf;
    stdDev = vol * std::sqrt(tau);
    dp = (std::log(fwd / strike) + 0.5 * stdDev * stdDev) / stdDev;
    dm = (std::log(fwd / strike) - 0.5 * stdDev * stdDev) / stdDev;
    res = phi * domDf * (fwd * cdf(d, phi * dp) - strike * cdf(d, phi * dm));
    return res;
}

Real impliedVolProblem(const Real &spot, const Real &strike, const Rate &rd, const Rate &rf,
                       const Volatility &vol, const Time &tau, const Integer &phi, const Real &price) {
    return blackScholesPrice(spot, strike, rd, rf, vol, tau, phi) - price;
}

void testSolvers() {
    // setup of market parameters
    Real spot = 100.0, strike = 110.0;
    Rate rd = 0.002, rf = 0.01, tau = 0.5;
    Integer phi = 1;
    Real vol = 0.1423;

    // calculate corresponding Black Scholes price
    Real price = blackScholesPrice(spot, strike, rd, rf, vol, tau, phi);

    // setup a solver
    Bisection mySolv1;
    Brent mySolv2;
    Ridder mySolv3;

    Real accuracy = 0.00001, guess = 0.25;
    Real min = 0.0, max = 1.0;

    // setup a boost function
    boost::function<Real(Volatility)> myVolFunc;

    // bind the boost function to all market parameters , keep vol as variant
    myVolFunc = boost::bind(&impliedVolProblem, spot, strike, rd, rf, _1, tau, phi, price);

    // solve the problem
    Real res1 = mySolv1.solve(myVolFunc, accuracy, guess, min, max);
    Real res2 = mySolv2.solve(myVolFunc, accuracy, guess, min, max);
    Real res3 = mySolv3.solve(myVolFunc, accuracy, guess, min, max);

    std::cout << " Input Volatility : " << vol << std::endl;
    std::cout << " Implied Volatility Bisection: " << res1 << std::endl;
    std::cout << " Implied Volatility Brent : " << res2 << std::endl;
    std::cout << " Implied Volatility Ridder: " << res3 << std::endl;
}