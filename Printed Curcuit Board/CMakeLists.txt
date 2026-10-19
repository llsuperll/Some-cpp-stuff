cmake_minimum_required(VERSION 3.14)

project(lab2)


include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(lab2
    lib/simple_class.cpp
    lib/board.cpp
    test/board_tests.cpp
)

set_target_properties(lab2
    PROPERTIES 
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)


target_compile_options(lab2 PRIVATE --coverage)
target_link_options(lab2 PRIVATE --coverage)
target_link_libraries(lab2 PRIVATE Catch2::Catch2WithMain)

# gcovr -r .. . -e CMakeFiles --html-details -o coverage.html