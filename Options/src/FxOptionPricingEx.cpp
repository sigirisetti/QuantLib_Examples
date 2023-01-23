//
// Created by appuprakhya on 16/1/23.
//
#include <iostream>

#include <ql/quantlib.hpp>

struct OptionInputs {
    QuantLib::Real S;
    QuantLib::Real K;
    /// Foreign rate
    QuantLib::Spread f;
    /// Domestic rate
    QuantLib::Rate r;
    QuantLib::Volatility vol;
    QuantLib::Date maturity;
    QuantLib::DayCounter dayCounter;
};

double
CRRPricing(QuantLib::VanillaOption &o,
           const boost::shared_ptr<QuantLib::GarmanKohlagenProcess>& process,
           QuantLib::Size timeSteps) {

    using namespace QuantLib;
    boost::shared_ptr<PricingEngine> pe(new BinomialVanillaEngine<CoxRossRubinstein>(process, timeSteps));
    o.setPricingEngine(pe);
    return o.NPV();
}

void FxOptEx(const OptionInputs &in,
             const QuantLib::Date &todaysDate,
             const QuantLib::Date &settlementDate) {
    using namespace QuantLib;

    // set up dates
    Calendar calendar = TARGET();
    Settings::instance().evaluationDate() = todaysDate;

    boost::shared_ptr<Exercise>
            americanExercise(new AmericanExercise(settlementDate,
                                                  in.maturity));

    Handle<Quote>
            underlyingH(boost::shared_ptr<Quote>(new SimpleQuote(in.S)));

    Handle<YieldTermStructure>
            rTS(boost::shared_ptr<YieldTermStructure>(new FlatForward(settlementDate,
                                                                      in.r,
                                                                      in.dayCounter)));
    Handle<YieldTermStructure>
            fTS(boost::shared_ptr<YieldTermStructure>(new FlatForward(settlementDate,
                                                                      in.f,
                                                                      in.dayCounter)));
    Handle<BlackVolTermStructure>
            flatVolTS(boost::shared_ptr<BlackVolTermStructure>(new BlackConstantVol(settlementDate,
                                                                                    calendar,
                                                                                    in.vol,
                                                                                    in.dayCounter)));

    boost::shared_ptr<StrikedTypePayoff>
            payoff(new PlainVanillaPayoff(Option::Call,
                                          in.K));

    boost::shared_ptr<GarmanKohlagenProcess>
            process(new GarmanKohlagenProcess(underlyingH,
                                              fTS,
                                              rTS,
                                              flatVolTS));

    VanillaOption amerOpt(payoff,
                          americanExercise);

    double npv = CRRPricing(amerOpt,
                            process,
                            100);

    std::cout << "Option value:"
              << npv
              << std::endl;
}


void test_fx_option_pricing() {
    using namespace QuantLib;

    OptionInputs in;
    in.S = 100;
    in.K = 100;
    in.f = 0.05;
    in.r = 0.02;
    in.vol = 0.20;
    in.maturity = Date(17, May, 1999);
    in.dayCounter = Actual365Fixed();

    FxOptEx(in,
            Date(15, May, 1998),
            Date(17, May, 1998));
}