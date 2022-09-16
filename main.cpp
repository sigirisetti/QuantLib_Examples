#include <iostream>

#include <boost/preprocessor/stringize.hpp>
#include <boost/version.hpp>

#include "DateTimeExAll.hpp"
#include "ObserverObservableEx.h"
#include "QL_Macro_Ex_All.hpp"
#include "VanillaOptions_Ex_all.hpp"
#include "RandomNumberGeneratorExAll.hpp"

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

    //QL_Macro_Example(); //Will block for input
    //runExample(&QL_Macro_Example);//Will block for input
    runExample("basicDatesExamples", &basicDatesExamples);
    runExample("test_printDateInformation", &test_printDateInformation);
    runExample("observer_test", &observer_test);
    runExample("test_vanilla_option_pricing", &test_vanilla_option_pricing);
    runExample("testMersenneTwisterUniformRng", &testMersenneTwisterUniformRng);
    runExample("testRandomSeqGenUsingMTRng", &testRandomSeqGenUsingMTRng);
    return 0;
}

