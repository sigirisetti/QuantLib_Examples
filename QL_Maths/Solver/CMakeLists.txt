add_library(Solver blackScholesPrice.cpp)

target_link_libraries(Solver QuantLib)

target_include_directories(Solver INTERFACE .)