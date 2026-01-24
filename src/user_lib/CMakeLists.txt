add_library(user_lib user/creator.cpp)
target_link_libraries(user_lib PRIVATE project_options project_warnings)

target_link_system_libraries(user_lib PRIVATE random_lib)

target_include_directories(user_lib PUBLIC .)
