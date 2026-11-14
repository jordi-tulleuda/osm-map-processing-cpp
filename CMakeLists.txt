cmake_minimum_required(VERSION 3.16)
project(osm_map_processing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(osm_core
    src/MapaSolucio.cpp
    src/PuntDeInteresBase.cpp
    src/PuntDeInteresBotigaSolucio.cpp
    src/PuntDeInteresRestaurantSolucio.cpp
    src/Util.cpp
)
target_include_directories(osm_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(osm_example examples/example.cpp)
target_link_libraries(osm_example PRIVATE osm_core)

include(CTest)
if(BUILD_TESTING)
  add_executable(osm_tests tests/test_map.cpp)
  target_link_libraries(osm_tests PRIVATE osm_core)
  add_test(NAME osm_core_tests COMMAND osm_tests)
endif()
