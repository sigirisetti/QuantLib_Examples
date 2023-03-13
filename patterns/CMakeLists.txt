add_library(Patterns singleton_ex.cpp)
target_include_directories(Patterns PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}"
        )