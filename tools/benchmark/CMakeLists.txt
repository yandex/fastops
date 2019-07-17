set(FMATH_DIR "${PROJECT_SOURCE_DIR}/contrib/libs/fmath")
set(FMATH_INCLUDE_DIR "${FMATH_DIR}")

include_directories("${FMATH_INCLUDE_DIR}")

add_executable(benchmark benchmark.cpp opts_tclap.cpp)
target_link_libraries(benchmark fastops)

install(TARGETS benchmark DESTINATION bin)
