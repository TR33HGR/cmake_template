include(${CMAKE_SOURCE_DIR}/cmake/SystemLink.cmake)

add_subdirectory(random_lib)
add_subdirectory(user_lib)
add_subdirectory(customer_lib)
add_subdirectory(restaurant_lib)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE project_options project_warnings)

target_link_system_libraries(
  main
  PRIVATE
  CLI11::CLI11
  fmt::fmt
  spdlog::spdlog
  customer_lib
  restaurant_lib
  )
