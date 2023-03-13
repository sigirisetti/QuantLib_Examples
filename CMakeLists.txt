cmake_minimum_required(VERSION 3.23)

project(QuantLib_Examples VERSION 1.0)

# specify the C++ standard. QuantLib compiles with c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

#find_package(Boost ${QL_BOOST_VERSION} COMPONENTS ALL)

# Below is explicit reference to a specific QuantLib version.
# You can simply remove below two declarations to refer to installed lib
add_library(QuantLib SHARED IMPORTED patterns/patterns_ex_all.hpp patterns/singleton_ex.cpp)
set_target_properties(QuantLib PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES /home/appuprakhya/work/git/QL/QuantLib-v1.29
        IMPORTED_LOCATION /home/appuprakhya/work/git/QL/QuantLib-v1.29/cmake-build-debug/ql/libQuantLib.so.1.29.0
        )

### Add source sub directories or modules
add_subdirectory(common)
add_subdirectory(QL_Basics)
add_subdirectory(QL_Macro)
add_subdirectory(DateTime)
add_subdirectory(observer)
add_subdirectory(Options)
add_subdirectory(QL_Maths)
add_subdirectory(Bonds)
add_subdirectory(stochastic_processes)
add_subdirectory(Indexes)
add_subdirectory(market_data)
add_subdirectory(patterns)

# Define Project executable
add_executable(QuantLib_Examples main.cpp)

# Link all libs built from sub directories
target_link_libraries(QuantLib_Examples
        QuantLib
        common
        QL_Basics
        QL_Macro
        DateTime
        observer
        Options
        RandomNumberGeneratorEx
        Integration
        Bonds
        StochasticProcesses
        Solver
        Interpolation
        Matrix
        Optimizer
        Indexes
        MarketData
        Quotes
        Patterns
        )
