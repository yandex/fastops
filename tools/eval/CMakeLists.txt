add_executable(eval eval.cpp opts_tclap.cpp)
target_link_libraries(eval fastops)

install(TARGETS eval DESTINATION bin)
