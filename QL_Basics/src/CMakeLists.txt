add_library(QL_Basics
        MoneyExchangeEx.cpp QL_Version.cpp QL_Arrays.cpp Matrices.cpp Interest_Rate_Ex.cpp cashflow_examples.cpp)

target_link_libraries(QL_Basics QuantLib)

target_include_directories(QL_Basics INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})