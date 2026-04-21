add_executable(test_restaurant restaurant/test_restaurant.cpp)
target_link_libraries(
  test_restaurant
  PRIVATE project_warnings
          project_options
          Catch2::Catch2WithMain
          customer_lib
          restaurant_lib)

catch_discover_tests(test_restaurant)
