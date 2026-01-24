add_executable(test_user user/test_creator.cpp)
target_link_libraries(
  test_user
  PRIVATE project_warnings
          project_options
          Catch2::Catch2WithMain
          user_lib
          mock_random)

catch_discover_tests(test_user)
