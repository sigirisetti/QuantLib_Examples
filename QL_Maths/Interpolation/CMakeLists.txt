add_library(Interpolation LinearInterpolationExample.cpp CubicNaturalSplineExample.cpp CubicInterpolationExample.cpp)

target_link_libraries(Interpolation QuantLib)

target_include_directories(Interpolation INTERFACE .)