/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*!
 Copyright (C) 2005, 2006, 2007, 2009 StatPro Italia srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
#if !defined(BOOST_ALL_NO_LIB) && defined(BOOST_MSVC)
#  include <ql/auto_link.hpp>
#endif

#include <ql/instruments/vanillaoption.hpp>
#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/pricingengines/vanilla/analyticeuropeanengine.hpp>
#include <ql/pricingengines/barrier/analyticbarrierengine.hpp>

#include <ql/time/calendars/target.hpp>
#include <ql/utilities/dataformatters.hpp>
#include <ql/models/shortrate/onefactormodels/vasicek.hpp>

#include <iostream>
#include <iomanip>
#include <ql/time/daycounters/actual360.hpp>

using namespace QuantLib;

#if defined(QL_ENABLE_SESSIONS)
namespace QuantLib {

    ThreadKey sessionId() { return {}; }

}
#endif


void test_up_and_out_barrier_option_pricing() {

    try {

        std::cout << std::endl;

        // set up dates
        Calendar calendar = TARGET();
        Date todaysDate(28, Feb, 2020);
        Date settlementDate(28, Feb, 2020);
        Date maturity(29, Feb, 2024);

        Settings::instance().evaluationDate() = todaysDate;

        // our options
        Option::Type type(Option::Call);
        Real underlying = 100;
        Real strike = 100;
        Real barrier = 150;
        Real rebate = 50;
        Spread dividendYield = 0.00;
        Rate riskFreeRate = 0.01;
        Volatility volatility = 0.30;
        DayCounter dayCounter = Actual360();
        //DayCounter dayCounter = Actual365Fixed();

        std::cout << "Option type = " << type << std::endl;
        std::cout << "Maturity = " << maturity << std::endl;
        std::cout << "Underlying price = " << underlying << std::endl;
        std::cout << "Strike price = " << strike << std::endl;
        std::cout << "barrier = " << barrier << std::endl;
        std::cout << "Risk-free interest rate = " << io::rate(riskFreeRate) << std::endl;
        std::cout << "Dividend yield = " << io::rate(dividendYield) << std::endl;
        std::cout << "Volatility = " << io::volatility(volatility) << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        std::string method;

        // write column headings
        int widths[] = {35, 14, 14, 14};
        std::cout << std::setw(widths[0]) << std::left << "Method"
                  << std::setw(widths[1]) << std::left << "European"
                  << std::setw(widths[2]) << std::left << "Bermudan"
                  << std::setw(widths[3]) << std::left << "American"
                  << std::endl;

        ext::shared_ptr<Exercise> europeanExercise(new EuropeanExercise(maturity));

        Handle<Quote> underlyingH(ext::shared_ptr<Quote>(new SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        Handle<YieldTermStructure> flatTermStructure(
                ext::shared_ptr<YieldTermStructure>(
                        new FlatForward(settlementDate, riskFreeRate, dayCounter)));
        Handle<YieldTermStructure> flatDividendTS(
                ext::shared_ptr<YieldTermStructure>(
                        new FlatForward(settlementDate, dividendYield, dayCounter)));
        Handle<BlackVolTermStructure> flatVolTS(
                ext::shared_ptr<BlackVolTermStructure>(
                        new BlackConstantVol(settlementDate, calendar, volatility,
                                             dayCounter)));

        ext::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));
        ext::shared_ptr<BlackScholesMertonProcess> bsmProcess(
                new BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                              flatTermStructure, flatVolTS));

        // options
        BarrierOption europeanOption(Barrier::UpOut, barrier, rebate, payoff, europeanExercise);

        // Analytic formulas:

        // Black-Scholes for European
        method = "Black-Scholes";

        europeanOption.setPricingEngine(ext::shared_ptr<PricingEngine>(new AnalyticBarrierEngine(bsmProcess)));

        std::cout << std::setw(widths[0]) << std::left << method
                  << std::fixed
                  << std::setw(widths[1]) << std::left << europeanOption.NPV()
                  << std::setw(widths[2]) << std::left << "N/A"
                  << std::setw(widths[3]) << std::left << "N/A"
                  << std::endl;

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
    }
}
