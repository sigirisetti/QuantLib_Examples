add_library(QL_Basics
        MoneyExchangeEx.cpp)

target_link_libraries(QL_Basics QuantLib)

target_include_directories(QL_Basics INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})