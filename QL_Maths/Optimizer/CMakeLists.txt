add_library(Optimizer optimizer_example.cpp RosenBrockFunction.cpp)

target_link_libraries(Optimizer QuantLib)

target_include_directories(Optimizer INTERFACE .)