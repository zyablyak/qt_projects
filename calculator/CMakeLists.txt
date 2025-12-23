cmake_minimum_required(VERSION 3.16)
project(calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Qml)

add_executable(calculator
    main.cpp
    login_form.hpp
    login_form.cpp
    calculator_form.hpp
    calculator_form.cpp
)

target_link_libraries(calculator PRIVATE Qt6::Widgets Qt6::Qml)