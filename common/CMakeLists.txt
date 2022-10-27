add_library(common blackScholesPrice.cpp)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})