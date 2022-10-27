add_library(Solver testSolvers.cpp)

target_link_libraries(Solver QuantLib common)

target_include_directories(Solver INTERFACE .)