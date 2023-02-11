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
        Date tPlusOneDate(29, Feb, 2020);
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
        std::cout << std::setw(widths[0]) << std::left << "Measures"
                  << std::setw(widths[1]) << std::left << "European NPV"
                  << std::setw(widths[2]) << std::left << "Delta"
                  << std::setw(widths[3]) << std::left << "Gamma"
                  << std::setw(widths[3]) << std::left << "Vega"
                  << std::setw(widths[3]) << std::left << "Theta"
                  << std::setw(widths[3]) << std::left << "Rho"
                  << std::endl;

        ext::shared_ptr<Exercise> europeanExercise(new EuropeanExercise(maturity));
        auto simpleQuote = new SimpleQuote(underlying);
        Handle<Quote> underlyingH((ext::shared_ptr<SimpleQuote>(simpleQuote)));

        auto rate = new SimpleQuote(riskFreeRate);
        Handle<Quote> riskFreeRateH((ext::shared_ptr<SimpleQuote>(rate)));

        // bootstrap the yield/dividend/vol curves
        Handle<YieldTermStructure> flatTermStructure(
                ext::shared_ptr<YieldTermStructure>(
                        new FlatForward(0, calendar, riskFreeRateH, dayCounter)));
        Handle<YieldTermStructure> flatDividendTS(
                ext::shared_ptr<YieldTermStructure>(
                        new FlatForward(0, calendar, dividendYield, dayCounter)));

        auto volQ = new SimpleQuote(volatility);
        Handle<Quote> volH((ext::shared_ptr<SimpleQuote>(volQ)));

        Handle<BlackVolTermStructure> flatVolTS(
                ext::shared_ptr<BlackVolTermStructure>(
                        new BlackConstantVol(settlementDate, calendar, volH,
                                             dayCounter)));

        ext::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));
        ext::shared_ptr<BlackScholesMertonProcess> bsmProcess(
                new BlackScholesMertonProcess(underlyingH, flatDividendTS, flatTermStructure, flatVolTS));

        // options
        BarrierOption europeanOption(Barrier::UpOut, barrier, rebate, payoff, europeanExercise);

        // Analytic formulas:
        // Black-Scholes for European
        method = "Black-Scholes";

        europeanOption.setPricingEngine(ext::shared_ptr<PricingEngine>(new AnalyticBarrierEngine(bsmProcess)));

        /* Greeks Approximation */
        //Set initial value and define h
        Real u0 = underlying;
        Real h = 0.01;
        Real P0 = europeanOption.NPV();

        //Bump up the price by h
        simpleQuote->setValue(u0 + h);
        Real P_plus = europeanOption.NPV();

        //Bump down the price by h
        simpleQuote->setValue(u0 - h);
        Real P_minus = europeanOption.NPV();

        //Set the price back to its current value
        simpleQuote->setValue(u0);

        //Calculate Greeks: Delta, Gamma, Vega, Theta, Rho
        Real delta = (P_plus - P_minus) / (2 * h);
        Real gamma = (P_plus - 2 * P0 + P_minus) / (h * h);

        //Update quote for rho calculation
        Real r0 = rate->value();
        Real h1 = 0.0001;
        rate->setValue(r0 + h);
        P_plus = europeanOption.NPV();
        rate->setValue(r0);

        //Rho
        Real rho = (P_plus - P0) / h1;

        //Update quote for sigma calculation
        Real sigma0 = volQ->value();
        h = 0.0001;
        volQ->setValue(sigma0 + h);
        P_plus = europeanOption.NPV();
        volQ->setValue(sigma0);

        //Vega
        Real vega = (P_plus - P0) / h;

        //Update quote to calculate theta
        Settings::instance().evaluationDate() = tPlusOneDate;
        Real P1 = europeanOption.NPV();
        h = 1.0 / 365;

        //Theta
        Real theta = (P1 - P0) / h;

        //Delta, Gamma, Vega, Theta, Rho
        std::cout << std::setw(widths[0]) << std::left << method
                  << std::fixed
                  << std::setw(widths[1]) << std::left << europeanOption.NPV()
                  << std::setw(widths[2]) << std::left << delta
                  << std::setw(widths[3]) << std::left << gamma
                  << std::setw(widths[3]) << std::left << vega
                  << std::setw(widths[3]) << std::left << theta
                  << std::setw(widths[3]) << std::left << rho
                  << std::endl;

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
    }
}
