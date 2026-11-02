cmake_minimum_required(VERSION 3.10.0)
project(P1_Cruise_Control VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Load CMake's FetchContent module
include(FetchContent)
# Declare the external dependency

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
)

# Download and configure the dependency
FetchContent_MakeAvailable(googletest)

# Create your executable
add_executable(P1_Cruise_Control src/main.cpp  src/vehicle.cpp)
add_library(vehicle src/vehicle.cpp src/pid.cpp)
target_include_directories(vehicle PUBLIC include)
add_executable(vehicle_tests 
    tests/vehicle_test.cpp 
    tests/pid_test.cpp 
    tests/closed_loop_test.cpp)

# Link the library to your executable
target_link_libraries(vehicle_tests PRIVATE vehicle GTest::gtest_main)

enable_testing()

include(GoogleTest)

gtest_discover_tests(vehicle_tests)

# add_executable(cruise_sim app/cruise_sim.cpp)
# target_link_libraries(cruise_sim PRIVATE vehicle)
