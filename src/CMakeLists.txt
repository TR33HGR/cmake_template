include(${CMAKE_SOURCE_DIR}/cmake/SystemLink.cmake)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE project_options project_warnings)

target_link_system_libraries(
  main
  PRIVATE
  CLI11::CLI11
  fmt::fmt
  spdlog::spdlog)

target_include_directories(main PRIVATE "${CMAKE_SOURCE_DIR}/configured_files/include")
