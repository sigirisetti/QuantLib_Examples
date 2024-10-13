#include <iostream>

#include <boost/version.hpp>

#include "DateTimeExAll.hpp"
#include "ObserverObservableEx.h"
#include "QL_Macro_Ex_All.hpp"
#include "VanillaOptions_Ex_all.hpp"
#include "RandomNumberGeneratorExAll.hpp"
#include "Integration_All.hpp"
#include "QL_Basics_All.hpp"
#include "Bonds_All.hpp"
#include "stochastic_processes_all.hpp"
//#include "Solver_All.hpp"
#include "Interpolation_All.hpp"
#include "Matrix_All.hpp"
#include "Optimizer_All.h"
#include "Indexes_All.hpp"
#include "MarketData_All.hpp"
#include "Quotes_Ex_All.hpp"


using namespace std;

void runExample(const char* name, void (*fun) ()) {
    cout << "=========================================" << endl;
    cout << "Running Example : " << name << endl;
    fun();
}

int main()
{
    std::cout << "Using Boost "
              << BOOST_VERSION / 100000     << "."  // major version
              << BOOST_VERSION / 100 % 1000 << "."  // minor version
              << BOOST_VERSION % 100                // patch level
              << std::endl;

    /* Arrays */
    //runExample("ql_arrays_test", &ql_arrays_test);
    //runExample("ql_matrix_test", &ql_matrix_test);

    /* Macros */
    //QL_Macro_Example(); //Will block for input
    //runExample(&QL_Macro_Example);//Will block for input

    /* Dates */
    //runExample("basicDatesExamples", &basicDatesExamples);
    //runExample("test_printDateInformation", &test_printDateInformation);
    //runExample("dateArthematic", &dateArthematic);

    /* Calendar */
    //runExample("calendarTesting", &calendarTesting);
    //runExample("holidaySetup", &holidaySetup);

    /* Business Day Adjustment */
    //runExample("businessDayAdjustment", &businessDayAdjustment);

    /* Daycount */
    //runExample("dayCounterTesting1", &dayCounterTesting1);

    /* Schedules */
    //runExample("dateScheduleGen", &dateScheduleGen);
    //runExample("dateScheduleGen_NextAndPrevious", &dateScheduleGen_NextAndPrevious);
    //runExample("makeScheduleFlowApiHelper", &makeScheduleFlowApiHelper);

    /* Observable */
    //runExample("observer_test", &observer_test);

    /* Money */
    //runExample("moneyExchangeEx", &moneyExchangeEx);

    /* Interest Rates */
    //runExample("Interest_Rate_Ex", &Interest_Rate_Ex);

    /* Cashflow examples*/
    runExample("cashflow_examples", &cashflow_examples);

    /* MC examples */
    //runExample("testMersenneTwisterUniformRng", &testMersenneTwisterUniformRng);
    //runExample("testRandomSeqGenUsingMTRng", &testRandomSeqGenUsingMTRng);
    //runExample("boxMullerGaussianRngEx", &boxMullerGaussianRngEx);
    //runExample("inverseCumulativeRsgExample", &inverseCumulativeRsgExample);

    /* Stochastic Process */
    //runExample("gbmEx1", &gbmEx1);

    /* Numerical Examples */
    // Interpolators
    //runExample("linearInterpolationExample", &linearInterpolationExample);
    //runExample("cubicNaturalSplineExample", &cubicNaturalSplineExample);
    //runExample("cubicInterpolationExample", &cubicInterpolationExample);
    //runExample("gauss_chebyshev", &gauss_chebyshev);
    // Matrices
    //runExample("matrix_inverse_example", &matrix_inverse_example);
    //runExample("MatrixDecomposition", &MatrixDecomposition);
    // Solvers and Optimizers
    //runExample("testSolvers", &testSolvers);
    //runExample("optimizer_example", &optimizer_example);
    //runExample("testLmOptimizer", &testLmOptimizer);

    /* Indexes */
    //runExample("euribor_index_info", &euribor_index_info);

    /* Bonds */
    //runExample("run_bond_ex", &run_bond_ex);

    /* Options */
    //runExample("call_option_pricing_using_Integration", &call_option_pricing_using_Integration);
    //runExample("testingBlackVolSurface", &testingBlackVolSurface);
    //runExample("test_vanilla_option_pricing", &test_vanilla_eq_option_pricing);
    //runExample("test_fx_option_pricing", &test_fx_option_pricing);
    //runExample("test_up_and_out_barrier_option_pricing", &test_up_and_out_barrier_option_pricing);

    /* Quotes */
    //runExample("ql_quotes_test", &ql_quotes_test);
    //runExample("ql_derived_quote_test", &ql_derived_quote_test);
    //runExample("ql_composite_quote_test", &ql_composite_quote_test);
    //runExample("ql_fx_delta_quote_test", &ql_fx_delta_quote_test);

    return 0;
}
