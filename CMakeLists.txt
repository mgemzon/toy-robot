cmake_minimum_required(VERSION 3.14)
project(toy_robot LANGUAGES CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    lib/Table.cpp
    lib/Robot.cpp
    lib/Controller.cpp
    main.cpp)

set(HEADERS
    lib/Direction.h
    lib/Table.h
    lib/Robot.h
    lib/RobotInterface.h
    lib/Controller.h)

include_directories(lib)

add_executable(${PROJECT_NAME} ${SOURCES})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TESTING-SOURCES
    lib/unit_test/ControllerTest.cpp
    lib/unit_test/RobotTest.cpp
    lib/unit_test/TableTest.cpp)

add_library(${PROJECT_NAME}-Lib ${SOURCES} ${HEADERS})

add_executable(${PROJECT_NAME}-Tests ${TESTING-SOURCES})
target_link_libraries(${PROJECT_NAME}-Tests gtest_main gmock_main ${PROJECT_NAME}-Lib)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-Tests)
