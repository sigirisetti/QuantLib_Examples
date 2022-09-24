//
// Created by appuprakhya on 18/9/22.
//
#include <ql/qldefines.hpp>

#ifdef BOOST_MSVC
#  include <ql/auto_link.hpp>
#endif

#include <ql/instruments/bonds/zerocouponbond.hpp>
#include <ql/instruments/bonds/floatingratebond.hpp>
#include <ql/pricingengines/bond/discountingbondengine.hpp>
#include <ql/cashflows/couponpricer.hpp>
#include <ql/termstructures/yield/piecewiseyieldcurve.hpp>
#include <ql/termstructures/yield/bondhelpers.hpp>
#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>
#include <ql/indexes/ibor/euribor.hpp>
#include <ql/indexes/ibor/usdlibor.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/time/calendars/unitedstates.hpp>
#include <ql/time/daycounters/actualactual.hpp>
#include <ql/time/daycounters/actual360.hpp>
#include <ql/time/daycounters/thirty360.hpp>

#include <iostream>
#include <iomanip>

using namespace QuantLib;

#if defined(QL_ENABLE_SESSIONS)
namespace QuantLib {

    ThreadKey sessionId() { return {}; }

}
#endif


void run_bond_ex() {

    try {
        Calendar calendar = TARGET();
        Date settlementDate(18, September, 2008);
        // must be a business day
        settlementDate = calendar.adjust(settlementDate);

        Integer fixingDays = 3;
        Natural settlementDays = 3;

        Date todaysDate = calendar.advance(settlementDate, -fixingDays, Days);
        // nothing to do with Date::todaysDate
        Settings::instance().evaluationDate() = todaysDate;
        std::cout << "Today: " << todaysDate.weekday() << ", " << todaysDate << std::endl;
        std::cout << "Settlement date: " << settlementDate.weekday() << ", " << settlementDate << std::endl;



        // Building of the bonds discounting yield curve

        /*********************
         ***  RATE HELPERS ***
         *********************/

        // RateHelpers are built from the above quotes together with
        // other instrument dependant infos.  Quotes are passed in
        // relinkable handles which could be relinked to some other
        // data source later.

        // Common data

        // ZC rates for the short end
        Rate zc3mQuote = 0.0096;
        Rate zc6mQuote = 0.0145;
        Rate zc1yQuote = 0.0194;

        ext::shared_ptr<Quote> zc3mRate(new SimpleQuote(zc3mQuote));
        ext::shared_ptr<Quote> zc6mRate(new SimpleQuote(zc6mQuote));
        ext::shared_ptr<Quote> zc1yRate(new SimpleQuote(zc1yQuote));

        DayCounter zcBondsDayCounter = Actual365Fixed();

        ext::shared_ptr<RateHelper> zc3m(new DepositRateHelper(
                Handle<Quote>(zc3mRate),
                3 * Months, fixingDays,
                calendar, ModifiedFollowing,
                true, zcBondsDayCounter));
        ext::shared_ptr<RateHelper> zc6m(new DepositRateHelper(
                Handle<Quote>(zc6mRate),
                6 * Months, fixingDays,
                calendar, ModifiedFollowing,
                true, zcBondsDayCounter));
        ext::shared_ptr<RateHelper> zc1y(new DepositRateHelper(
                Handle<Quote>(zc1yRate),
                1 * Years, fixingDays,
                calendar, ModifiedFollowing,
                true, zcBondsDayCounter));


        /**
         * setup bonds
         */
        Real redemption = 100.0;

        const Size numberOfBonds = 5;

        Date issueDates[] = {
                Date(15, March, 2005),
                Date(15, June, 2005),
                Date(30, June, 2006),
                Date(15, November, 2002),
                Date(15, May, 1987)
        };

        Date maturities[] = {
                Date(31, August, 2010),
                Date(31, August, 2011),
                Date(31, August, 2013),
                Date(15, August, 2018),
                Date(15, May, 2038)
        };

        Real couponRates[] = {
                0.02375,
                0.04625,
                0.03125,
                0.04000,
                0.04500
        };

        Real marketQuotes[] = {
                100.390625,
                106.21875,
                100.59375,
                101.6875,
                102.140625
        };

        std::vector<ext::shared_ptr<SimpleQuote> > quote;
        for (double marketQuote: marketQuotes) {
            ext::shared_ptr<SimpleQuote> cp(new SimpleQuote(marketQuote));
            quote.push_back(cp);
        }

        RelinkableHandle<Quote> quoteHandle[numberOfBonds];
        for (Size i = 0; i < numberOfBonds; i++) {
            quoteHandle[i].linkTo(quote[i]);
        }

        // Definition of the rate helpers
        std::vector<ext::shared_ptr<BondHelper> > bondsHelpers;

        for (Size i = 0; i < numberOfBonds; i++) {

            Schedule schedule(issueDates[i], maturities[i], Period(Semiannual),
                              UnitedStates(UnitedStates::GovernmentBond),
                              Unadjusted, Unadjusted, DateGeneration::Backward, false);

            ext::shared_ptr<FixedRateBondHelper> bondHelper(new FixedRateBondHelper(
                    quoteHandle[i],
                    settlementDays,
                    100.0,
                    schedule,
                    std::vector<Rate>(1, couponRates[i]),
                    ActualActual(ActualActual::Bond),
                    Unadjusted,
                    redemption,
                    issueDates[i]));

            // the above could also be done by creating a
            // FixedRateBond instance and writing:
            //
            // ext::shared_ptr<BondHelper> bondHelper(
            //         new BondHelper(quoteHandle[i], bond));
            //
            // This would also work for bonds that still don't have a
            // specialized helper, such as floating-rate bonds.


            bondsHelpers.push_back(bondHelper);
        }

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
    }
}
