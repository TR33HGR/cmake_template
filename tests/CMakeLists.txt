include(CTest)

project(CmakeConfigPackageTests LANGUAGES CXX)

enable_testing()

include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

add_subdirectory(random_lib)
add_subdirectory(user_lib)
add_subdirectory(restaurant_lib)