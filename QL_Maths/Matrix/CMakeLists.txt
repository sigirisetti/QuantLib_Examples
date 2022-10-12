add_library(Matrix MatrixInverse.cpp MatrixDecomposition.cpp)

target_link_libraries(Matrix QuantLib)

target_include_directories(Matrix INTERFACE .)