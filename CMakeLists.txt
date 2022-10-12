cmake_minimum_required(VERSION 3.23)

project(QuantLib_Examples VERSION 1.0)

# specify the C++ standard. QuantLib compiles with c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

#find_package(Boost ${QL_BOOST_VERSION} COMPONENTS ALL)

### Add source sub directories or modules
add_subdirectory(QL_Basics)
add_subdirectory(QL_Macro)
add_subdirectory(DateTime)
add_subdirectory(observer)
add_subdirectory(Options)
add_subdirectory(QL_Maths)
add_subdirectory(Bonds)
add_subdirectory(stochastic_processes)

# Define Project executable
add_executable(QuantLib_Examples main.cpp)

# Link all libs built from sub directories
target_link_libraries(QuantLib_Examples
        QuantLib
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
        )
