add_executable(test_random random/test_string_gen.cpp)
target_link_libraries(
  test_random
  PRIVATE project_warnings
          project_options
          random_lib
          Catch2::Catch2WithMain)

catch_discover_tests(test_random)
