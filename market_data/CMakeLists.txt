add_library(MarketData BlackVolTermStructureEx.cpp)

target_link_libraries(MarketData QuantLib)

target_include_directories(MarketData INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})