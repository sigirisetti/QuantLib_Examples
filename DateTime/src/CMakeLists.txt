add_library(DateTime BasicCalendarExamples.cpp BasicDatesExamples.cpp DateTimeExAll.hpp dayCount.cpp ScheduleGeneration.cpp)
target_include_directories(DateTime PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/DateTime/src"
        )