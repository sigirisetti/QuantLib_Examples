add_library(Options EqEuropeanOption.cpp)

target_link_libraries(Options QuantLib)

target_include_directories(Options INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})