//
// Created by appuprakhya on 4/10/22.
//

#include<iostream>
#include<boost/math/distributions.hpp>
#include <ql/quantlib.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>

using namespace boost::math;
using namespace QuantLib;

double normalPdf(const double &x, const double &a, double &b) {
    const boost::math::normal_distribution<> d;
    double t1 = 0.5 * (b - a), t2 = 0.5 * (b + a);
    return t1 * pdf(d, t1 * x + t2);
}

double normalCdf(const double &x, const double &a, double &b) {
    const boost::math::normal_distribution<> d;
    double t1 = 0.5 * (b - a), t2 = 0.5 * (b + a);
    return t1 * cdf(d, t1 * x + t2);
}

void gauss_chebyshev() {
    double a = -1.96, b = 1.96;
    boost::function<double(double)> myPdf;
    boost::function<double(double)> myCdf;
    myPdf = boost::bind(normalPdf, _1, a, b);
    myCdf = boost::bind(normalCdf, _1, a, b);
    GaussChebyshevIntegration gChebInt(64);// ( -1 ,1)
    double analytical = myPdf(b) - myPdf(a);
    std::cout << " Analytical : " << analytical << std::endl;
    std::cout << " Chebyshev : " << gChebInt(myPdf) << std::endl;
}