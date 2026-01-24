add_executable(test_random random/test_string_generator.cpp)
target_link_libraries(
  test_random
  PRIVATE project_warnings
          project_options
          Catch2::Catch2WithMain
          random_lib)

catch_discover_tests(test_random)

add_library(mock_random INTERFACE)

target_link_libraries(mock_random INTERFACE random_lib trompeloeil::trompeloeil)
target_include_directories(mock_random INTERFACE .)
