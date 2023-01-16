add_library(Indexes Euribor_Info.cpp)

target_link_libraries(Indexes QuantLib)

target_include_directories(Indexes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})