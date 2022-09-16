cmake_minimum_required(VERSION 3.23)

project(QuantLib_Examples VERSION 1.0)

# specify the C++ standard. QuantLib compiles with c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

### Add source sub directories or modules
add_subdirectory(DateTime)
add_subdirectory(observer)
add_subdirectory(QL_Macro)
add_subdirectory(EqEuropeanOption)
add_subdirectory(RandomNumberGeneratorEx)

# Define Project executable
add_executable(QuantLib_Examples main.cpp)

# Link all libs built from sub directories
target_link_libraries(QuantLib_Examples QuantLib
        DateTime
        observer
        QL_Macro
        EqEuropeanOption
        RandomNumberGeneratorEx)

#target_include_directories(QuantLib_Examples PUBLIC "${PROJECT_BINARY_DIR}")
