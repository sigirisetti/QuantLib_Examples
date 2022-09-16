add_library(DateTime BasicCalendarExamples.cpp BasicDatesExamples.cpp DateTimeExAll.hpp)
target_include_directories(DateTime PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/DateTime/src"
        )