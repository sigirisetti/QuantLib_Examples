//
// Created by appuprakhya on 22/9/22.
//

#include <iostream>
#include <fstream>
#include <ql/quantlib.hpp>
#include <boost/format.hpp>
#include <boost/function.hpp>

using namespace QuantLib;

void gbmEx1() {

    Real startingPrice = 20.16; //closing price for INTC on 12/7/2012
    Real mu = 0.2312; //INTC one year historical annual return
    Volatility sigma = 0.2116; //INTC one year historical volatility
    Size timeSteps = 255; //trading days in a year (U.S.)
    Time length = 1; //one year

    //instantiate Geometric Brownian Motion (GBM) stochastic process
    const boost::shared_ptr<StochasticProcess> &gbm =
            boost::shared_ptr<StochasticProcess>(new GeometricBrownianMotionProcess(startingPrice,
                                                                                    mu, sigma));

    MersenneTwisterUniformRng unifMt(12345);
    BoxMullerGaussianRng<MersenneTwisterUniformRng> bmGauss(unifMt);
    RandomSequenceGenerator<BoxMullerGaussianRng<MersenneTwisterUniformRng>> gsg(timeSteps, bmGauss);

    //generate simulated path of stock price using GBM stochastic process
    PathGenerator<RandomSequenceGenerator<BoxMullerGaussianRng<MersenneTwisterUniformRng>>> gbmPathGenerator(gbm,
                                                                                                             length,
                                                                                                             timeSteps,
                                                                                                             gsg,
                                                                                                             false);
    const Path &samplePath = gbmPathGenerator.next().value;

    //calculate simulated sample returns using C++11 lambda expression
    boost::function2<Real, Real, Real> calcLogReturns = [](Real x, Real y) { return std::log(y / x); };
    std::vector<Real> logReturns;
    Path::iterator samplePathBegin = samplePath.begin();
    Path::iterator samplePathEnd = samplePath.end();
    Path::iterator endMinusOne = std::prev(samplePathEnd);
    Path::iterator beginPlusOne = std::next(samplePathBegin);

    std::transform(samplePathBegin, endMinusOne, beginPlusOne,
                   std::back_inserter(logReturns), calcLogReturns);

    //calculate some general statistics
    GeneralStatistics statistics;

    //returns statistics
    statistics.addSequence(logReturns.begin(), logReturns.end());
    std::cout << boost::format("Standard deviation of simulated returns (Normal): %.4f") %
                 (statistics.standardDeviation() * std::sqrt(255)) << std::endl;

    //price statistics
    statistics.reset();
    statistics.addSequence(samplePath.begin(), samplePath.end());
    std::cout << boost::format("Price statistics: mean=%.2f, min=%.2f, max=%.2f") %
                 statistics.mean() % statistics.min() % statistics.max() << std::endl;


    //write simulated path to a file for charting with gnuplot
    std::ofstream gbmFile;
    gbmFile.open("/tmp/gbm.dat", std::ios::out);
    for (Size i = 0; i < timeSteps; ++i) {
        gbmFile << boost::format("%d %.4f") % i % samplePath.at(i) << std::endl;
    }

    gbmFile.close();


    /* gnuplot script to chart stock price path
    set key bottom center
    set key bottom box
    set xlabel "Time Step (Days)"
    set ylabel "Stock Price"
    plot "/tmp/gbm.dat" using 1:2 w lines t "INTC simulated stock price"
    */

}