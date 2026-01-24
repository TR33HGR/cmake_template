add_library(random_lib random/string_generator.cpp)
target_link_libraries(random_lib PRIVATE project_options project_warnings)

target_link_system_libraries(random_lib PRIVATE)

target_include_directories(random_lib PUBLIC .)
