add_library(restaurant_lib restaurant/restaurant.cpp)
target_link_libraries(restaurant_lib PRIVATE project_options project_warnings)

target_link_system_libraries(restaurant_lib PRIVATE
  fmt::fmt
  customer_lib)

target_include_directories(restaurant_lib PUBLIC .)
