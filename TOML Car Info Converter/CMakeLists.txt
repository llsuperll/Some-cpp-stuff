cmake_minimum_required(VERSION 3.12)

project(lab1)

set(CMAKE_CXX_COMPILER "clang++")

add_executable(lab1
    main.cpp
    ui.cpp
    func.cpp
)

set_target_properties(lab1
    PROPERTIES 
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

if(ENABLE_SANITIZERS)
    target_compile_options(lab1 PRIVATE -fsanitize=address,undefined)
    target_link_options(lab1 PRIVATE -fsanitize=address,undefined)
    message(STATUS "Sanitizers enabled: AddressSanitizer and UndefinedBehaviorSanitizer")
endif()
