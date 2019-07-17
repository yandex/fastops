set(LIBTCLAP_DIR "${PROJECT_SOURCE_DIR}/contrib/libs/tclap/include")
set(LIBTCLAP_INCLUDE_DIR "${LIBTCLAP_DIR}")

include_directories("${LIBTCLAP_INCLUDE_DIR}")

add_subdirectory(benchmark)
add_subdirectory(eval)
